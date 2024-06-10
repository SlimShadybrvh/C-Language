#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<stdbool.h>


// Define a struct to hold trial data
typedef struct {
    bool stress;
    bool exposure;
    bool cold;
    bool flu;
    bool x1;
    bool x2;
    bool x3;
    bool x4;
    bool x5;
} TrialData;

// Probability functions
float probStress() {
    return 0.5;
}

float probExposure() {
    return 0.1;
}

float probCold(int s, int e) {
    if (s == 0 && e == 0) return 0.01;
    if (s == 0 && e == 1) return 0.2;
    if (s == 1 && e == 0) return 0.3;
    if (s == 1 && e == 1) return 0.7;
    return 0;
}

float probFlu(int s, int e) {
    if (s == 0 && e == 0) return 0.01;
    if (s == 0 && e == 1) return 0.5;
    if (s == 1 && e == 0) return 0.1;
    if (s == 1 && e == 1) return 0.8;
    return 0;
}

float probSymptom(int i, int f, int c) {
    static const float symptom_dict[5][4] = {
        {0.03, 0.20, 0.80, 0.60},
        {0.05, 0.70, 0.60, 0.80},
        {0.03, 0.50, 0.50, 0.90},
        {0.02, 0.30, 0.90, 0.50},
        {0.01, 0.80, 0.80, 0.60}
    };
    int bin_val = 2 * f + c;
    return symptom_dict[i-1][bin_val];
}

// Bernoulli trial
int bern(float prob) {
    return ((float)rand() / RAND_MAX) < prob ? 1 : 0;
}

// Main simulation function
float inferProbFlu(int ntrials) {
    TrialData* trials = (TrialData*)malloc(ntrials * sizeof(TrialData));
    if (trials == NULL) {
        printf("Memory allocation failed\n");
        return -1;
    }

    int filtered_count = 0;
    int flu_count = 0;

    for (int i = 0; i < ntrials; i++) {
        trials[i].stress = bern(probStress());
        trials[i].exposure = bern(probExposure());
        trials[i].cold = bern(probCold(trials[i].stress, trials[i].exposure));
        trials[i].flu = bern(probFlu(trials[i].stress, trials[i].exposure));
        trials[i].x1 = bern(probSymptom(1, trials[i].flu, trials[i].cold));
        trials[i].x2 = bern(probSymptom(2, trials[i].flu, trials[i].cold));
        trials[i].x3 = bern(probSymptom(3, trials[i].flu, trials[i].cold));
        trials[i].x4 = bern(probSymptom(4, trials[i].flu, trials[i].cold));
        trials[i].x5 = bern(probSymptom(5, trials[i].flu, trials[i].cold));

        if (trials[i].exposure  && trials[i].x2 ) {
            filtered_count++;
            if (trials[i].flu) {
                flu_count++;
            }
        }
    }

    float result = filtered_count > 0 ? (float)flu_count / filtered_count : 0;

    free(trials);
    return result;
}

int main() {
    srand(time(0));  // Seed the random number generator

    printf("Calling inferProbFlu:\n");
    printf("\tReturn value was: %f\n", inferProbFlu(1000000));
    printf("Done!\n");

    return 0;
}
