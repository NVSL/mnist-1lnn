/**
 * @file main.c
 *
 * @mainpage MNIST 1-Layer Neural Network
 *
 * @brief Main characteristics: Only 1 layer (= input layer), no hidden layer.  Feed-forward only.
 * No Sigmoid activation function. No back propagation.\n
 *
 * @details Learning is achieved simply by incrementally updating the connection weights based on the comparison
 * with the desired target output (supervised learning).\n
 *
 * Its performance (success rate) of 85% is far off the state-of-the-art techniques (surprise, surprise) 
 * but close the Yann Lecun's 88% when using only a linear classifier.
 *
 * @see [Simple 1-Layer Neural Network for MNIST Handwriting Recognition](http://mmlind.github.io/Simple_1-Layer_Neural_Network_for_MNIST_Handwriting_Recognition/)
 * @see http://yann.lecun.com/exdb/mnist/
 * @version [Github Project Page](http://github.com/mmlind/mnist-1lnn/)
 * @author [Matt Lind](http://mmlind.github.io)
 * @date July 2015
 *
 */
 
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "screen.h"
#include "mnist-utils.h"
#include "mnist-stats.h"
#include "1lnn.h"


/**
 * @details Trains a layer by looping through and training its cells
 * @param l A pointer to the layer that is to be training
 */

void trainLayer(Layer *l){
    
    // open MNIST files
    FILE *imageFile, *labelFile;
    imageFile = openMNISTImageFile(MNIST_TRAINING_SET_IMAGE_FILE_NAME);
    labelFile = openMNISTLabelFile(MNIST_TRAINING_SET_LABEL_FILE_NAME);
    
    
    // screen output for monitoring progress
    displayImageFrame(5,5);

    int errCount = 0;
    
    // Loop through all images in the file
    for (int imgCount=0; imgCount<MNIST_MAX_TRAINING_IMAGES; imgCount++){
        
        // display progress
        //displayLoadingProgressTraining(imgCount,3,5);
        
        // Reading next image and corresponding label
        MNIST_Image img = getImage(imageFile);
        MNIST_Label lbl = getLabel(labelFile);
        
        // set target ouput of the number displayed in the current image (=label) to 1, all others to 0
        Vector targetOutput;
        targetOutput = getTargetOutput(lbl);
        
        //displayImage(&img, 6,6);
     
        // loop through all output cells for the given image
        for (int out=0; out < NUMBER_OF_OUTPUT_CELLS; out++){
            Cell *out_cell = &l->cell[out];
            for (int in=0; in < NUMBER_OF_INPUT_CELLS; in++){
                out_cell->input[in] = ((&img)->pixel[in] ? 1 : 0);
            }
            out_cell->output=0;

            for (int in2=0; in2<NUMBER_OF_INPUT_CELLS; in2++){
                out_cell->output += ((&img)->pixel[in2] ? 1 : 0) * out_cell->weight[in2];
            }

            out_cell->output /= NUMBER_OF_INPUT_CELLS;             // normalize output (0-1)

            // learning (by updating the weights)
            double err1 = targetOutput.val[out] - out_cell->output;

            double err = err1;
            for (int in3=0; in3<NUMBER_OF_INPUT_CELLS; in3++){
                out_cell->weight[in3] += LEARNING_RATE * out_cell->input[in3] * err;
            }
        }
        
        int predictedNum = getLayerPrediction(l);
        if (predictedNum!=lbl) errCount++;
        
        printf("\n      Prediction: %d   Actual: %d ",predictedNum, lbl);

        displayProgress(imgCount, errCount, 3, 66);
        
    }
    
    // Close files
    fclose(imageFile);
    fclose(labelFile);

}




/**
 * @details Tests a layer by looping through and testing its cells
 * Exactly the same as TrainLayer() but WITHOUT LEARNING.
 * @param l A pointer to the layer that is to be training
 */

void testLayer(Layer *l){
    
    // open MNIST files
    FILE *imageFile, *labelFile;
    imageFile = openMNISTImageFile(MNIST_TESTING_SET_IMAGE_FILE_NAME);
    labelFile = openMNISTLabelFile(MNIST_TESTING_SET_LABEL_FILE_NAME);
    
    
    // screen output for monitoring progress
    displayImageFrame(7,5);
    
    int errCount = 0;
    
    // Loop through all images in the file
    for (int imgCount=0; imgCount<MNIST_MAX_TESTING_IMAGES; imgCount++){
        
        // display progress
       // displayLoadingProgressTesting(imgCount,5,5);
        
        // Reading next image and corresponding label
        MNIST_Image img = getImage(imageFile);
        MNIST_Label lbl = getLabel(labelFile);
        
        // set target ouput of the number displayed in the current image (=label) to 1, all others to 0
        Vector targetOutput;
        targetOutput = getTargetOutput(lbl);
        
        //displayImage(&img, 8,6);
        
        // loop through all output cells for the given image
        for (int i=0; i < NUMBER_OF_OUTPUT_CELLS; i++){
            Cell *out_cell = &l->cell[i];
            for (int i1=0; i1 < NUMBER_OF_INPUT_CELLS; i1++){
                out_cell->input[i1] = (&img)->pixel[i1] ? 1 : 0;
            }
            out_cell->output=0;

            for (int i2=0; i2<NUMBER_OF_INPUT_CELLS; i2++){
                out_cell->output += out_cell->input[i2] * out_cell->weight[i2];
            }

            out_cell->output /= NUMBER_OF_INPUT_CELLS;             // normalize output (0-1)
        }

        double maxOut = 0;
        int maxInd = 0;

        for (int i3=0; i3<NUMBER_OF_OUTPUT_CELLS; i3++){

            if (l->cell[i3].output > maxOut){
                maxOut = l->cell[i3].output;
                maxInd = i3;
            }
        }

        int predictedNum = maxInd;
        if (predictedNum!=lbl) errCount++;
        
        printf("\n      Prediction: %d   Actual: %d ",predictedNum, lbl);
        
        displayProgress(imgCount, errCount, 5, 66);
        
    }
    
    // Close files
    fclose(imageFile);
    fclose(labelFile);
    
}





/**
 * @details Main function to run MNIST-1LNN
 */

int main(int argc, const char * argv[]) {
    
    // remember the time in order to calculate processing time at the end
    time_t startTime = time(NULL);
    
    // clear screen of terminal window
    clearScreen();
    printf("    MNIST-1LNN: a simple 1-layer neural network processing the MNIST handwriting images\n");
    
    // initialize all connection weights to random values between 0 and 1
    Layer outputLayer;
    initLayer(&outputLayer);
    trainLayer(&outputLayer);

    printf("Done training\n");
    testLayer(&outputLayer);

    locateCursor(38, 5);
    
    // Calculate and print the program's total execution time
    time_t endTime = time(NULL);
    double executionTime = difftime(endTime, startTime);
    printf("\n    DONE! Total execution time: %.1f sec\n\n",executionTime);
    
    return 0;
}


