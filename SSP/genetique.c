#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define POPULATION_SIZE 100
#define MAX_GENERATIONS 100
#define MUTATION_RATE 0.1

int set[] = {1, 3, 7, 11, 2};
int n = sizeof(set) / sizeof(set[0]);
int target = 10;

// Structure représentant un individu de la population
typedef struct {
    int subset[6];
    int fitness;
} Individual;

// Fonction pour initialiser un individu aléatoire
void initializeIndividual(Individual *individual) {
    for (int i = 0; i < n; i++) {
        individual->subset[i] = rand() % 2;
    }
}

// Fonction pour évaluer la fitness d'un individu
void evaluateFitness(Individual *individual) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        if (individual->subset[i]) {
            sum += set[i];
        }
    }
    individual->fitness = abs(target - sum);
}

// Fonction pour sélectionner les meilleurs individus de la population
void select(Individual population[], Individual selected[], int tournamentSize) {
    for (int i = 0; i < POPULATION_SIZE; i++) {
        int bestIndex = rand() % POPULATION_SIZE;
        for (int j = 1; j < tournamentSize; j++) {
            int index = rand() % POPULATION_SIZE;
            if (population[index].fitness < population[bestIndex].fitness) {
                bestIndex = index;
            }
        }
        selected[i] = population[bestIndex];
    }
}

// Fonction pour effectuer une recombinaison (crossover) entre deux individus
void crossover(Individual parent1, Individual parent2, Individual *child) {
    int crossoverPoint = rand() % n;
    for (int i = 0; i < crossoverPoint; i++) {
        child->subset[i] = parent1.subset[i];
    }
    for (int i = crossoverPoint; i < n; i++) {
        child->subset[i] = parent2.subset[i];
    }
}

// Fonction pour effectuer une mutation sur un individu
void mutate(Individual *individual) {
    for (int i = 0; i < n; i++) {
        if ((double)rand() / RAND_MAX < MUTATION_RATE) {
            individual->subset[i] = 1 - individual->subset[i];
        }
    }
}

int main() {
    srand(time(NULL));

    Individual population[POPULATION_SIZE];
    Individual selected[POPULATION_SIZE];

    // Initialisation de la population
    for (int i = 0; i < POPULATION_SIZE; i++) {
        initializeIndividual(&population[i]);
    }

    for (int generation = 0; generation < MAX_GENERATIONS; generation++) {
        // Évaluation de la fitness de chaque individu
        for (int i = 0; i < POPULATION_SIZE; i++) {
            evaluateFitness(&population[i]);
        }

        // Sélection des meilleurs individus
        select(population, selected, 5);

        // Remplacement de la population par les individus sélectionnés
        for (int i = 0; i < POPULATION_SIZE; i++) {
            population[i] = selected[i];
        }

        // Recombinaison (crossover)
        for (int i = 0; i < POPULATION_SIZE; i += 2) {
            Individual child1, child2;
            crossover(selected[i], selected[i + 1], &child1);
            crossover(selected[i + 1], selected[i], &child2);
            population[i] = child1;
            population[i + 1] = child2;
        }

        // Mutation
        for (int i = 0; i < POPULATION_SIZE; i++) {
            mutate(&population[i]);
        }
    }

    // Recherche de la meilleure solution dans la population finale
    Individual bestSolution = population[0];
    for (int i = 1; i < POPULATION_SIZE; i++) {
        if (population[i].fitness < bestSolution.fitness) {
            bestSolution = population[i];
        }
    }

    printf("Meilleur sous-ensemble trouvé avec une somme de %d : ", target - bestSolution.fitness);
    for (int i = 0; i < n; i++) {
        if (bestSolution.subset[i]) {
            printf("%d ", set[i]);
        }
    }
    printf("\n");

    return 0;
}
