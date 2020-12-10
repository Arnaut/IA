// Authors: Arnaut.Leyre / Nicolas LE LAN
// 07.12.2020/19:15

#include <stdio.h>
#include "neuralnetwork.h"
#include "training.h"

int main() {
    struct NeuralNetwork nn = initNN();
    int tab1[8] = {0,0,0,1,1,0,1,1};
    int tab2[4] = {0,1,1,0};
    int nbtrain = 500;
    for (int i = 1; i <= nbtrain; ++i)
    {
        printf("===== training:%i =====\n",i);
        printf("%i\n",tab2[0]);
        nn = backpropagation(tab1, tab2, 4, nn);
    }
    return 0;
}
