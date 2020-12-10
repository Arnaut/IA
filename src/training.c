// Authors: Arnaut.Leyre
// 08.12.2020/09:10

#include "IAtoolsbox.h"
#include "neuralnetwork.h"
#include "training.h"
#include <stdio.h>
// data
int sizeofListeT = 3;
int sizeofInputT = 2;
int InputListT[2] = {0, 0};
int sizesListT[3] = {8, 8, 1};

// Training Methods.
struct GNetwork initGradient()
{
    GLayer tab1[sizeofListeT];
    GNetwork Gn =
            {
                    .size = sizeofListeT,
                    .LayerList = tab1,
            };
    int psize = sizeofInputT;
    for (int i = 0; i < sizeofListeT; ++i)
    {
        int size = sizesListT[i];
        Gradient tab2[size];
        GLayer l =
                {
                        .size = size,
                        .GradientList = tab2,
                };
        for (int j = 0; j < size; ++j)
        {
            float tab3[psize];
            for (int k = 0; k < psize; ++k)
            {
                tab3[k] = 0;
            }
            Gradient g =
                    {
                            .size = psize,
                            .bias = 0,
                            .weights = tab3,
                    };
            l.GradientList[j] = g;
        }
        psize = size;
        Gn.LayerList[i] = l;
    }
    return Gn;
}

float derivativeWeights(Neuron n,float pnv)
{
    return pnv*sigmoid_derivative(sigmoid(n.net))*n.val;
}


float derivativeBias(Neuron n)
{
    return sigmoid_derivative(sigmoid(n.net))*n.val;
}


float derivativeValue(Neuron n,int k,Layer fl)
{
    float res = 0;
    for (int i = 0; i < fl.size; ++i)
    {
        Neuron fn = fl.NeuronList[i];
        res += fn.weights[k]*sigmoid_derivative(n.val)*fn.val;
    }
    return res;
}

void printTry(NeuralNetwork nn, int* Input, int* Output)
{
    printf("|");
    int l = sizeofListeT - 1;
    for (int n = 0; n < sizesListT[l]; ++n)
    {
        Neuron ner = nn.LayerList[l].NeuronList[n];
        printf("|");
        printf("%f",ner.val);
        printf("|");
    }
    printf(": [");
    for (int i = 0; i < sizeofInputT; ++i)
    {
        printf("%i",Input[i]);
        if (i != sizeofInputT-1)
        {
            printf(";");
        }
    }
    printf("] => [");
    for (int j = 0; j < sizesListT[sizeofListeT-1]; ++j)
    {
        printf("%i",Output[j]);
        if (j != sizesListT[sizeofListeT-1])
        {
            printf(";");
        }
    }
    printf("]\n");
}

struct GNetwork MakeGradient(GNetwork gn, NeuralNetwork nn, int* Output)
{
    int l = sizeofListeT-1;
    while (l >= 0)
    {
        for (int n = 0; n < sizesListT[l]; ++n)
        {
            Neuron ner = nn.LayerList[l].NeuronList[n];
            Gradient g = gn.LayerList[l].GradientList[n];
            if (l == sizeofListeT-1) ner.val = 2*(ner.val - Output[n]);
            else
            {
                ner.val = derivativeValue(ner,n,nn.LayerList[l+1]);
                g.bias = derivativeBias(ner);
                for (int w = 0; w < ner.size; ++w)
                {
                    if (l>0) g.weights[w] = derivativeWeights(ner,nn.LayerList[l-1].NeuronList[w].val);
                    else g.weights[w] = derivativeWeights(ner,nn.InputLayer[w]);
                }
            }
        }
        l-=1;
    }
    return gn;
}

struct NeuralNetwork ApplyGradient(NeuralNetwork nn, GNetwork gn)
{
    for (int l = 0; l < sizeofListeT; ++l)
    {
        for (int n = 0; n < sizesListT[l]; ++n)
        {
            Neuron ner = nn.LayerList[l].NeuronList[n];
            Gradient g = gn.LayerList[l].GradientList[n];
            ner.bias = ner.bias - g.bias;
            for (int w = 0; w < ner.size; ++w)
            {
                ner.weights[w] = ner.weights[w] - g.weights[w];
            }
        }
    }
    return nn;
}

struct NeuralNetwork backpropagation(int* trainInput, int* trainOutput, int data, NeuralNetwork nn)
{
    GNetwork gn = initGradient();
    for (int t = 0; t < data; ++t)
    {
        int Input[sizeofInputT];
        for (int i = 0; i < sizeofInputT; ++i)
        {
            Input[i] = trainInput[t*sizeofInputT + i];
        }
        int Output[sizesListT[sizeofListeT-1]];
        for (int u = 0; u < sizesListT[sizeofListeT-1]; ++u)
        {
            int index = t*sizesListT[sizeofListeT-1] + u;
            Output[u] = trainOutput[index];
        }
        printf("yup\n");
        RunNeuralNetwork(nn, Input);
        printf("yup\n");
        printTry(nn, Input, Output);
        printf("yup\n");
        gn = MakeGradient(gn, nn, Output);
        nn = ApplyGradient(nn, gn);
    }
    return nn;
}



