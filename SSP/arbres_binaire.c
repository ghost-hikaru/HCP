#include <stdio.h>

void printSubset(int set[], int subset[], int n) {
    printf("Sous-ensemble trouvé : ");
    for (int i = 0; i < n; i++) {
        if (subset[i]) {
            printf("%d ", set[i]);
        }
    }
    printf("\n");
}

// Fonction récursive pour explorer l'arbre binaire
void findSubsets(int set[], int subset[], int n, int target, int currentIndex, int currentSum) {
    if (currentIndex == n) {
        if (currentSum == target) {
            printSubset(set, subset, n);
        }
        return;
    }

    // Inclure l'élément actuel dans le sous-ensemble
    subset[currentIndex] = 1;
    findSubsets(set, subset, n, target, currentIndex + 1, currentSum + set[currentIndex]);

    // Exclure l'élément actuel du sous-ensemble
    subset[currentIndex] = 0;
    findSubsets(set, subset, n, target, currentIndex + 1, currentSum);
}

int main() {
    int A[] = {1, 3, 7, 11, 2};
    int n = sizeof(A) / sizeof(A[0]);
    int target = 10;

    int subset[n];
    for (int i = 0; i < n; i++) {
        subset[i] = 0;
    }

    findSubsets(A, subset, n, target, 0, 0);

    return 0;
}
