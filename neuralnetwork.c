// Authors: Arnaut.Leyre
// 07.12.2020/19:15

#include "IAtoolsbox.h"
#include "neuralnetwork.h"

// data
int* InputList = [0, 0];
int* sizesList = [8, 8, 2];
int sizeoflist = 3;
int sizeofInput = 2;

// NeuralNetwork Methods.
struct NeuralNetwork initNN()
{
    Layer tab1[sizeoflist];
    NeuralNetwork nn =
            {
                    .size = sizeoflist,
                    .InputLayer = InputList,
                    .LayerList = tab1,
            };
    int psize = sizeofInput;
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
            double tab3[psize];
            for (int k = 0; k < psize; ++k)
            {
                tab3[k] = (double)rand()/RAND_MAX;
            }
            Neuron n =
                    {
                        .net = 0,
                        .val = 0,
                        .size = psize,
                        .bias = (double)rand()/RAND_MAX,
                        .weights = tab3,
                    };
        }
        psize = size;
        nn.LayerList[i] = l;
    }
    return nn;
}
