/**
 * @file 1lnn.h
 * @brief Machine learning functionality for a 1-layer neural network
 * @author Matt Lind
 * @date July 2015
 */


#include <stdio.h>

#define NUMBER_OF_INPUT_CELLS 784   ///< use 28*28 input cells (= number of pixels per MNIST image)
#define NUMBER_OF_OUTPUT_CELLS 10   ///< use 10 output cells to model 10 digits (0-9)

#define LEARNING_RATE 0.05          ///< Incremental increase for changing connection weights



typedef struct Cell Cell;
typedef struct Layer Layer;
typedef struct Vector Vector;




/**
 * @brief Core unit of the neural network (neuron and synapses)
 */

struct Cell{
    double input [NUMBER_OF_INPUT_CELLS];
    double weight[NUMBER_OF_INPUT_CELLS];
    double output;
    double bias;
};




/**
 * @brief The single (output) layer of this network (a layer is number cells)
 */

struct Layer{
    Cell cell[NUMBER_OF_OUTPUT_CELLS];
};




/**
 * @brief Data structure containing defined number of integer values (the output vector contains values for 0-9)
 */

struct Vector{
    int val[NUMBER_OF_OUTPUT_CELLS];
};




/**
 * @brief Returns an output vector with targetIndex set to 1, all others to 0
 * @param targetIndex Index of the output that is to be set to 1
 */

Vector getTargetOutput(int targetIndex);




/**
 * @brief Initialize layer by setting all weights to random values [0-1]
 * @param l A pointer to a NN layer
 */

void initLayer(Layer *l);




/**
 * @brief Returns the index of the cell with the hightest output
 * @param l A pointer to a NN layer
 */

int getLayerPrediction(Layer *l);


