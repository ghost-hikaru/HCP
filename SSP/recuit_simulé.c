#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
// MARCHE PAS

// Fonction pour calculer la somme d'un sous-ensemble
int subsetSum(int set[], int subset[], int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        if (subset[i]) {
            sum += set[i];
        }
    }
    return sum;
}

// Fonction pour résoudre le problème du sous-ensemble avec l'algorithme de recuit simulé
void simulatedAnnealing(int set[], int n, int target, double temperature, double coolingRate, int maxIterations) {
    int currentSolution[n];
    int bestSolution[n];
    int currentSum, bestSum;
    double currentTemperature = temperature;

    // Initialisez la solution courante avec un sous-ensemble aléatoire
    for (int i = 0; i < n; i++) {
        currentSolution[i] = rand() % 2; // 0 pour exclure, 1 pour inclure
    }

    currentSum = subsetSum(set, currentSolution, n);
    bestSum = currentSum;
    for (int i = 0; i < n; i++) {
        bestSolution[i] = currentSolution[i];
    }

    srand(time(NULL));

    while (currentTemperature > 0.01 && maxIterations > 0) {
        // Générez un voisin aléatoire en modifiant une position dans le sous-ensemble
        int randomIndex = rand() % n;
        currentSolution[randomIndex] = 1 - currentSolution[randomIndex]; // Inversion de l'inclusion

        int neighborSum = subsetSum(set, currentSolution, n);

        // Calculez la variation de coût
        int delta = neighborSum - currentSum;

        // Si le voisin est meilleur ou accepté selon la probabilité de Boltzmann, mettez à jour la solution courante
        if (delta < 0 || exp(-delta / currentTemperature) > (double)rand() / RAND_MAX) {
            currentSum = neighborSum;
            if (currentSum > bestSum) {
                bestSum = currentSum;
                for (int i = 0; i < n; i++) {
                    bestSolution[i] = currentSolution[i];
                }
            }
        } else {
            // Annulez le changement (revenez à la solution précédente)
            currentSolution[randomIndex] = 1 - currentSolution[randomIndex];
        }

        // Réduisez la température
        currentTemperature *= 1 - coolingRate;
        maxIterations--;
    }

    printf("Meilleur sous-ensemble trouvé avec une somme de %d : ", bestSum);
    for (int i = 0; i < n; i++) {
        if (bestSolution[i]) {
            printf("%d ", set[i]);
        }
    }
    printf("\n");
}

int main() {
    int A[] = {1, 3, 7, 11, 2};
    int n = sizeof(A) / sizeof(A[0]);
    int target = 10;
    double temperature = 100.0;
    double coolingRate = 0.01;
    int maxIterations = 1000;

    simulatedAnnealing(A, n, target, temperature, coolingRate, maxIterations);

    return 0;
}
