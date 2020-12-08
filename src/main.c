// Authors: Arnaut.Leyre
// 07.12.2020/19:15

#include <stdio.h>
#include "neuralnetwork.h"

int main() {
    struct NeuralNetwork nn = initNN();
    int r = nn.LayerList[2].size;
    printf("%d \n",r);
    return 0;
}
