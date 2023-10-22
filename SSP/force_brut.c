#include <stdio.h>

// Fonction pour résoudre le problème du sac à dos en utilisant la méthode de Force Brute
void knapsackBruteforce(int elements[], int n, int capaciteMax) {
    int i, j;
    int maxValeur = 0; // Valeur maximale obtenue
    int combinaisonOptimale[n]; // Tableau pour stocker la combinaison optimale

    // Générer toutes les combinaisons possibles
    int combinaison[n];
    for (i = 0; i < n; i++) {
        combinaison[i] = 0;
    }

    while (1) {
        int poidsTotal = 0;
        int valeurTotale = 0;

        // Calculer le poids et la valeur de la combinaison actuelle
        for (i = 0; i < n; i++) {
            if (combinaison[i] == 1) {
                poidsTotal += elements[i];
                valeurTotale += elements[i];
            }
        }

        if(valeurTotale == capaciteMax){
            // Afficher la combinaison actuelle
            printf("Combinaison : ");
            for (i = 0; i < n; i++) {
                printf("%d ", combinaison[i]);
            }
            printf("\nValeur : %d\n", valeurTotale);
            printf("\n");
        }

        // Mettre à jour la combinaison optimale si nécessaire
        /**
            if (poidsTotal <= capaciteMax && valeurTotale > maxValeur) {
                maxValeur = valeurTotale;
                for (i = 0; i < n; i++) {
                    combinaisonOptimale[i] = combinaison[i];
                }
            }
        */
       
        
        // Générer la prochaine combinaison
        j = 0;
        while (j < n && combinaison[j] == 1) {
            combinaison[j] = 0;
            j++;
        }
        if (j == n) {
            break; // Toutes les combinaisons possibles ont été générées
        } else {
            combinaison[j] = 1;
        }
    }

    // Afficher la combinaison optimale
    /*
    printf("Combinaison optimale : ");
    for (i = 0; i < n; i++) {
        printf("%d ", combinaisonOptimale[i]);
    }
    printf("\nValeur maximale : %d\n", maxValeur);
    */
    
}

int main() {
    int A[] = {1, 3, 7, 11, 2};
    int n = sizeof(A) / sizeof(A[0]); // Taille de A
    int capaciteMax = 10;

    knapsackBruteforce(A, n, capaciteMax);

    return 0;
}
