#include <stdio.h>

// Fonction pour résoudre le problème du sous-ensemble et afficher les sous-ensembles possibles
void subsetSum(int set[], int n, int target) {
    int dp[n + 1][target + 1];
    int subset[n + 1][target + 1];

    for (int i = 0; i <= n; i++) {
        dp[i][0] = 1;
        for (int j = 0; j <= target; j++) {
            subset[i][j] = 0;
        }
    }

    for (int j = 1; j <= target; j++) {
        dp[0][j] = 0;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= target; j++) {
            if (j < set[i - 1]) {
                dp[i][j] = dp[i - 1][j];
                subset[i][j] = 0;
            } else {
                dp[i][j] = dp[i - 1][j] || dp[i - 1][j - set[i - 1]];
                if (dp[i][j] == 1) {
                    subset[i][j] = 1;
                }
            }
        }
    }

    if (dp[n][target] == 0) {
        printf("Aucun sous-ensemble avec la somme cible n'existe.\n");
    } else {
        printf("Sous-ensembles possibles avec la somme cible :\n");
        int i = n, j = target;
        while (i > 0 && j > 0) {
            if (subset[i][j] == 1) {
                printf("%d ", set[i - 1]);
                j -= set[i - 1];
            }
            i--;
        }
        printf("\n");
    }
}

int main() {
    int A[] = {1, 3, 7, 11, 2};
    int n = sizeof(A) / sizeof(A[0]);
    int target = 10;

    subsetSum(A, n, target);

    return 0;
}
