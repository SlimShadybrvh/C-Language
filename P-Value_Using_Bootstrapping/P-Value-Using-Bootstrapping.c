#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define DATASET_SIZE 100
#define SAMPLE_SIZE 20
#define NUM_SAMPLES 100000

// Function to calculate mean
double calculate_mean(int *array, int size) {
    double sum = 0.0;
    for (int i = 0; i < size; i++) {
        sum += array[i];
    }
    return sum / size;
}

// Function to calculate variance
double calculate_variance(int *array, int size, double mean) {
    double sum = 0.0;
    for (int i = 0; i < size; i++) {
        sum += (array[i] - mean) * (array[i] - mean);
    }
    return sum / (size - 1);
}

// Function to randomly sample from the dataset
void random_sample(int *dataset, int *sample, int dataset_size, int sample_size) {
    for (int i = 0; i < sample_size; i++) {
        int random_index = rand() % dataset_size;
        sample[i] = dataset[random_index];
    }
}

int main() {
    int dataset[DATASET_SIZE] = {13, 12, 7, 16, 9, 11, 7, 10, 9, 8, 9, 7, 16, 7, 9, 8, 13, 10, 
                                 11, 9, 13, 13, 10, 10, 9, 7, 7, 6, 7, 8, 12, 13, 9, 6, 9, 11,
                                 10, 8, 12, 10, 9, 10, 8, 14, 13, 13, 10, 11, 12, 9, 8, 8, 16, 
                                 16, 9, 13, 14, 13, 10, 12, 10, 6, 14, 8, 13, 14, 7, 13, 7, 8, 
                                 4, 11, 7, 12, 8, 9, 12, 8, 11, 10,12, 6, 10, 15, 11, 12, 3, 
                                 8, 11, 10, 10, 8, 12, 8, 11, 6, 7, 10, 8, 5};
    
    int sample1[SAMPLE_SIZE], sample2[SAMPLE_SIZE];
    double mean1, mean2, var1, var2;
    double variance_diffs[NUM_SAMPLES];
    double mean_diffs[NUM_SAMPLES];
    int prob = 0, demeanor = 0;

    // Initialize random number generator
    srand(time(NULL));

    // Generate samples and calculate variance and mean differences
    for (int i = 0; i < NUM_SAMPLES; i++) {
        random_sample(dataset, sample1, DATASET_SIZE, SAMPLE_SIZE);
        random_sample(dataset, sample2, DATASET_SIZE, SAMPLE_SIZE);

        mean1 = calculate_mean(sample1, SAMPLE_SIZE);
        mean2 = calculate_mean(sample2, SAMPLE_SIZE);
        var1 = calculate_variance(sample1, SAMPLE_SIZE, mean1);
        var2 = calculate_variance(sample2, SAMPLE_SIZE, mean1);

        mean_diffs[i] = fabs(mean1 - mean2);
        variance_diffs[i] = fabs(var1 - var2);

        if (variance_diffs[i] == 0) {
            prob++;
        }
        if (mean_diffs[i] == 0) {
            demeanor++;
        }
    }

    printf("Variance difference probability: %f\n", 1 - (double)prob / NUM_SAMPLES);
    printf("Mean difference probability: %f\n", (double)demeanor / NUM_SAMPLES);

    return 0;
}
