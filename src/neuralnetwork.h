// Authors: Arnaut.Leyre
// 08.12.2020/18:49

#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

// NeuralNetwork structure.
typedef struct Neuron
{
    double net;          // Sum of weights times L-1 values + bias.
    double val;          // Sigmoid of net.
    double bias;         // Bias of the Neuron.
    double* weights;     // Weights toward L-1.
    int size;           // Size of L-1.
} Neuron;

typedef struct Layer
{
    Neuron* NeuronList; // List of Neuron in the Layer.
    int size;           // Number of Neuron in the Layer.
} Layer;

typedef struct NeuralNetwork
{
    int* InputLayer;    // Layer that the IA Input.
    Layer* LayerList;   // List of all Layers of the NeuralNetwork.
    int size;           // Number of Layers not including InputLayer.
} NeuralNetwork;

NeuralNetwork initNN();

#endif