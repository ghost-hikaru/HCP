#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Structure pour représenter un objet
struct Item {
    int weight;
    int value;
};

// Structure pour représenter la solution du sac à dos
struct Solution {
    int *selected; // Tableau binaire pour indiquer quels objets sont sélectionnés
    int totalValue; // Valeur totale de la solution
};

// Fonction pour initialiser une solution
struct Solution initializeSolution(int numItems) {
    struct Solution sol;
    sol.selected = (int *)malloc(numItems * sizeof(int));
    sol.totalValue = 0;
    for (int i = 0; i < numItems; i++) {
        sol.selected[i] = 0;
    }
    return sol;
}

// Fonction pour libérer la mémoire de la solution
void freeSolution(struct Solution sol) {
    free(sol.selected);
}

// Fonction pour résoudre le sac à dos en utilisant l'algorithme de recherche tabou
struct Solution tabuSearch(struct Item *items, int numItems, int maxWeight, int numIterations) {
    struct Solution currentSolution = initializeSolution(numItems);
    struct Solution bestSolution = currentSolution;

    int *tabuList = (int *)malloc(numItems * sizeof(int)); // Liste tabou pour les mouvements
    int tabuTenure = 10; // Durée de vie de la liste tabou

    for (int iter = 0; iter < numIterations; iter++) {
        int bestNeighborValue = -1;
        int bestNeighborIndex = -1;

        // Générer des voisins et trouver le meilleur voisin non tabou
        for (int i = 0; i < numItems; i++) {
            if (currentSolution.selected[i] == 0) {
                currentSolution.selected[i] = 1;
                int neighborValue = 0; // Initialisation de la valeur du voisin

            for (int i = 0; i < numItems; i++) {
                if (currentSolution.selected[i] == 1) {
                    // Ajouter la valeur de l'objet sélectionné
                    neighborValue += items[i].value;
                }
            }

                // Vérifier si le voisin est tabou
                bool isTabu = tabuList[i] > 0;

                if (neighborValue > bestNeighborValue || bestNeighborIndex == -1) {
                    if ((!isTabu || neighborValue > currentSolution.totalValue) && neighborValue <= maxWeight) {
                        bestNeighborValue = neighborValue;
                        bestNeighborIndex = i;
                    }
                }

                // Annuler la modification pour passer au voisin suivant
                currentSolution.selected[i] = 0;
            }
        }

        // Mettre à jour la liste tabou
        for (int i = 0; i < numItems; i++) {
            if (i == bestNeighborIndex) {
                tabuList[i] = tabuTenure;
            } else {
                tabuList[i] = (tabuList[i] > 0) ? tabuList[i] - 1 : 0;
            }
        }

        // Mettre à jour la solution actuelle
        currentSolution.selected[bestNeighborIndex] = 1;
        currentSolution.totalValue = bestNeighborValue;

        // Mettre à jour la meilleure solution si nécessaire
        if (bestNeighborValue > bestSolution.totalValue) {
            bestSolution = currentSolution;
        }
    }

    free(tabuList);
    return bestSolution;
}

int main() {
    // Exemple d'utilisation de l'algorithme de recherche tabou
    int numItems = 5;
    struct Item items[] = {{2, 3}, {3, 4}, {4, 8}, {5, 8}, {9, 10}};
    int maxWeight = 38;
    int numIterations = 100000;

    struct Solution bestSolution = tabuSearch(items, numItems, maxWeight, numIterations);

    printf("Objets sélectionnés : \n");
    for (int i = 0; i < numItems; i++) {
        if (bestSolution.selected[i] == 1) {
            printf("Objet %d - Poids : %d, Valeur : %d\n", i, items[i].weight, items[i].value);
        }
    }
    printf("\nValeur maximale : %d\n", bestSolution.totalValue);

    // Libérer la mémoire
    freeSolution(bestSolution);

    return 0;
}
