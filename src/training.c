// Authors: Arnaut.Leyre
// 08.12.2020/09:10

#include "IAtoolsbox.h"
#include "data.h"
#include "neuralnetwork.h"
#include "training.h"
#include <stdio.h>

// data
int sizeoflist = 3;
int sizeofInput = 2;
int InputList[2] = {0, 0};
int sizesList[3] = {8, 8, 1};

// Training Methods.
struct GNetwork initGradient()
{
    GLayer tab1[sizeoflist];
    GNetwork Gn =
            {
                    .size = sizeoflist,
                    .LayerList = tab1,
            };
    int psize = sizeofInput;
    for (int i = 0; i < sizeoflist; ++i)
    {
        int size = sizesList[i];
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
    int l = sizeoflist - 1;
    for (int n = 0; n < sizesList[l]; ++n)
    {
        Neuron ner = nn.LayerList[l].NeuronList[n];
        printf("|");
        printf("%f",ner.val);
        printf("|");
    }
    printf(": [");
    for (int i = 0; i < sizeofInput; ++i)
    {
        printf("%i",Input[i]);
        if (i != sizeofInput-1)
        {
            printf(";");
        }
    }
    printf("] => [");
    for (int j = 0; j < sizesList[sizeoflist-1]; ++j)
    {
        printf("%i",Output[j]);
        if (j != sizesList[sizeoflist-1])
        {
            printf(";");
        }
    }
    printf("]\n");
}

struct GNetwork MakeGradient(GNetwork gn, NeuralNetwork nn, int* Output)
{
    int l = sizeoflist-1;
    while (l >= 0)
    {
        for (int n = 0; n < sizesList[l]; ++n)
        {
            Neuron ner = nn.LayerList[l].NeuronList[n];
            Gradient g = gn.LayerList[l].GradientList[n];
            if (l == sizeoflist-1) ner.val = 2*(ner.val - Output[n]);
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
    for (int l = 0; l < sizeoflist; ++l)
    {
        for (int n = 0; n < sizesList[l]; ++n)
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
        int Input[sizeofInput];
        for (int i = 0; i < sizeofInput; ++i)
        {
            Input[i] = trainInput[t*sizeofInput + i];
        }
        int Output[sizesList[sizeoflist-1]];
        for (int o = 0; o < sizesList[sizeoflist-1]; ++o)
        {
            Output[0] = trainOutput[t*sizesList[sizeoflist-1] + o];
        }
        RunNeuralNetwork(nn, Input);
        gn = MakeGradient(gn,nn,&Output[t]);
        printTry(nn,&Input[t],&Output[t]);
        nn = ApplyGradient(nn,gn);
    }
    return nn;
}



