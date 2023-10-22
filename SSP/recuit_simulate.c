#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Structure pour représenter un objet
struct Item {
    int weight;
    int value;
};

// Fonction pour calculer l'énergie d'une solution (ici, la valeur totale)
int calculateEnergy(struct Item *items, int *selected, int numItems, int maxWeight) {
    int totalWeight = 0;

    for (int i = 0; i < numItems; i++) {
        if (selected[i] == 1) {
            totalWeight += items[i].weight;
            if (totalWeight > maxWeight) {
                return 0; // Pénalité si la limite de poids est dépassée
            }
        }
    }

    return totalWeight;
}


int main() {
    int numItems = 7;
    struct Item items[] = {{2, 3}, {3, 4}, {4, 8}, {5, 8}, {9, 10}};
    int maxWeight = 10;
    
    double initialTemperature = 100.0;
    double coolingRate = 0.95;
    int iterations = 1000;

    int currentSolution[numItems]; // Solution actuelle (0 ou 1 pour chaque objet)
    int bestSolution[numItems]; // Meilleure solution trouvée
    int currentEnergy, bestEnergy;

    // Initialisation de la solution actuelle
    for (int i = 0; i < numItems; i++) {
        currentSolution[i] = rand() % 2; // Sélection aléatoire des objets
    }
    currentEnergy = calculateEnergy(items, currentSolution, numItems, maxWeight);
    
    // Initialisation de la meilleure solution
    for (int i = 0; i < numItems; i++) {
        bestSolution[i] = currentSolution[i];
    }
    bestEnergy = currentEnergy;

    double temperature = initialTemperature;

    for (int i = 0; i < iterations; i++) {
        int randomIndex = rand() % numItems; // Indice aléatoire pour modifier un objet

        // Génération d'un voisin en inversant un objet
        int neighborSolution[numItems];
        for (int j = 0; j < numItems; j++) {
            neighborSolution[j] = currentSolution[j];
        }
        neighborSolution[randomIndex] = 1 - neighborSolution[randomIndex];

        // Calcul de l'énergie du voisin
        int neighborEnergy = calculateEnergy(items, neighborSolution, numItems, maxWeight);

        // Calcul de la différence d'énergie entre le voisin et la solution actuelle
        int deltaEnergy = neighborEnergy - currentEnergy;

        // Acceptation du voisin avec une certaine probabilité
        if (deltaEnergy < 0 || exp(-deltaEnergy / temperature) > (rand() / (double)RAND_MAX)) {
            for (int j = 0; j < numItems; j++) {
                currentSolution[j] = neighborSolution[j];
            }
            currentEnergy = neighborEnergy;

            // Mise à jour de la meilleure solution si nécessaire
            if (currentEnergy > bestEnergy) {
                for (int j = 0; j < numItems; j++) {
                    bestSolution[j] = currentSolution[j];
                }
                bestEnergy = currentEnergy;
            }
        }

        // Refroidissement
        temperature *= coolingRate;
    }

    // Affichage de la meilleure solution
    printf("Objets sélectionnés : ");
    for (int i = 0; i < numItems; i++) {
        if (bestSolution[i] == 1) {
            printf("Objet %d - Poids : %d, Valeur : %d\n", i, items[i].weight, items[i].value);
    }
    }
    printf("\nValeur maximale : %d\n", bestEnergy);

    return 0;
}

