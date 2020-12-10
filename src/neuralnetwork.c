// Authors: Arnaut.Leyre / Nicolas.Le-lan
// 07.12.2020/19:15

#include "IAtoolsbox.h"
#include "neuralnetwork.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// data
int sizeoflist = 3;
int sizeofInput = 2;
int InputList[2] = {0, 0};
int sizesList[3] = {8, 8, 1};

// NeuralNetwork Methods.
struct NeuralNetwork initNN()
{
    Layer tab1[sizeoflist];
    NeuralNetwork nn =
            {
                    .size = sizeoflist,
                    .inputsize = sizeofInput,
                    .InputLayer = InputList,
                    .LayerList = tab1,
            };
    int psize = sizeofInput;
    double a = 5.0;
    for (int i = 0; i < sizeoflist; ++i)
    {
        int size = sizesList[i];
        Neuron tab2[size];
        Layer l =
                {
                    .size = size,
                    .NeuronList = tab2,
                };
        for (int j = 0; j < size; ++j)
        {
            float tab3[psize];
            for (int k = 0; k < psize; ++k)
            {
                tab3[k] = ((float)rand()/(float)(RAND_MAX)) * a;
            }
            Neuron n =
                    {
                        .net = 0,
                        .val = 0,
                        .size = psize,
                        .bias = ((float)rand()/(float)(RAND_MAX)) * a,
                        .weights = tab3,
                    };
            l.NeuronList[j] = n;
        }
        psize = size;
        nn.LayerList[i] = l;
    }
    return nn;
}

// Methods:Propagation
void RunLayers(Layer L,Layer Lminus1){
    for(int i=0; i<L.size;i++)
    {
        L.NeuronList[i].net = L.NeuronList[i].bias;
        for(int j; j<Lminus1.size; j++)
        {
            L.NeuronList[i].net += Lminus1.NeuronList[j].val*L.NeuronList[i].weights[j];
        }
        L.NeuronList[i].val = sigmoid(L.NeuronList[i].net);
    }
}


void RunNeuralNetwork(NeuralNetwork nn, int* Input)
{
    nn.InputLayer = Input;
    //init first layer
    printf("i : %i",nn.LayerList[0].size);
    for (int i=0; i<nn.LayerList[0].size; i++)
    {
        nn.LayerList[0].NeuronList[i].net = nn.LayerList[0].NeuronList[i].bias;
        for (int j=0 ; j<nn.inputsize; j++)
        {
            nn.LayerList[0].NeuronList[i].net += Input[i]*nn.LayerList[0].NeuronList[i].weights[j];
        }
        nn.LayerList[0].NeuronList[i].val = sigmoid(nn.LayerList[0].NeuronList[i].net);
    }
    for (int l=1; l<nn.size; l++)
    {
        RunLayers(nn.LayerList[l],nn.LayerList[l-1]);
    }
}

