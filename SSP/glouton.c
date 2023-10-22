#include <stdio.h>

// Fonction pour résoudre le problème du sous-ensemble
int subsetSum(int set[], int n, int target) {
    // Triez le tableau dans l'ordre décroissant
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (set[j] < set[j + 1]) {
                int temp = set[j];
                set[j] = set[j + 1];
                set[j + 1] = temp;
            }
        }
    }

    // Parcourez le tableau trié et vérifiez si vous pouvez former la somme cible
    int currentSum = 0;
    for (int i = 0; i < n; i++) {
        if (currentSum + set[i] <= target) {
            currentSum += set[i];
            printf("Ajoutez %d à la somme\n", set[i]);
        }
    }

    // Si la somme actuelle est égale à la somme cible, renvoyez 1 (vrai), sinon renvoyez 0 (faux)
    if (currentSum == target) {
        return 1;
    } else {
        return 0;
    }
}

int main() {
    int A[] = {1, 3, 7, 11, 2};
    int n = sizeof(A) / sizeof(A[0]); // Taille de A
    int target = 10;

    if (subsetSum(A, n, target)) {
        printf("Un sous-ensemble avec la somme cible existe.\n");
    } else {
        printf("Aucun sous-ensemble avec la somme cible n'existe.\n");
    }

    return 0;
}
