// Authors: Arnaut.Leyre
// 09.12.2020/09:10

#ifndef TRAINING_H
#define TRAINING_H

// Gradient structure.
typedef struct Gradient
{
    float bias;         // gradient of bias.
    float* weights;     // gradient of Weights toward L-1.
    int size;           // Size of L-1.
} Gradient;

typedef struct GLayer
{
    Gradient* GradientList; // List of gradient in the Layer.
    int size;           // Number of gradient in the Layer.
} GLayer;

typedef struct GNetwork
{
    GLayer* LayerList;   // List of all GLayers of the GNetwork.
    int size;           // Number of GLayers.
} GNetwork;

GNetwork initGrad();
float derivativeWeights(Neuron n,float pnv);
float derivativeBias(Neuron n);
float derivativeValue(Neuron n,int k,Layer fl);
void printTry(NeuralNetwork nn, int* Input, int* Output);
struct GNetwork MakeGradient(GNetwork gn, NeuralNetwork nn, int* Output);
struct NeuralNetwork ApplyGradient(NeuralNetwork nn, GNetwork gn);
struct NeuralNetwork backpropagation(int* trainInput, int* trainOutput, int data, NeuralNetwork nn);

#endif