#include <stdio.h>

void printSubset(int set[], int n, int subset[]) {
    printf("Sous-ensemble trouvé : ");
    for (int i = 0; i < n; i++) {
        if (subset[i]) {
            printf("%d ", set[i]);
        }
    }
    printf("\n");
}

// Fonction récursive pour résoudre le problème du sous-ensemble avec l'algorithme de Branch and Bound
void subsetSumBranchAndBound(int set[], int n, int target, int currentIndex, int currentSum, int currentSubset[]) {
    if (currentSum == target) {
        printSubset(set, n, currentSubset);
        return;
    }

    if (currentIndex == n || currentSum > target) {
        return;
    }

    currentSubset[currentIndex] = 1;
    subsetSumBranchAndBound(set, n, target, currentIndex + 1, currentSum + set[currentIndex], currentSubset);

    currentSubset[currentIndex] = 0;
    subsetSumBranchAndBound(set, n, target, currentIndex + 1, currentSum, currentSubset);
}

int main() {
    int A[] = {1, 3, 7, 11, 2};
    int n = sizeof(A) / sizeof(A[0]);
    int target = 10;

    int currentSubset[n];
    for (int i = 0; i < n; i++) {
        currentSubset[i] = 0;
    }

    subsetSumBranchAndBound(A, n, target, 0, 0, currentSubset);

    return 0;
}
