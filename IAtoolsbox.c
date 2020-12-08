// Authors: Arnaut.Leyre
// 07.12.2020/19:34

#include <math.h>

float sigmoid(float x)
{
    return 1 / (1 + exp(-x));
}

float sigmoid_derivative(float x)
{
    return x * (1 - x);
}