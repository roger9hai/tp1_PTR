#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define ARRAY_SIZE 10  // Taille du tableau
#define NUM_THREADS 4   // Nombre de threads

int total_sum = 0;  // Somme totale

typedef struct {
    int *start;           // Début de la section du tableau à traiter
    int *end;             // Fin de la section du tableau à traiter
    pthread_mutex_t *lock;  // Mutex pour la synchronisation
} PartialSumArgs;         // Structure des arguments pour chaque thread

void *sum_partial(void *args) {
    PartialSumArgs *partial_args = (PartialSumArgs *)args;

    int partial_sum = 0;

    int *p;
    for (p = partial_args->start; p < partial_args->end; p++) {
        partial_sum += *p;
    }

    pthread_mutex_lock(partial_args->lock);

    total_sum += partial_sum;

    pthread_mutex_unlock(partial_args->lock);

    pthread_exit(NULL);
}

int main() {
    int array[ARRAY_SIZE];
    int i;

    // Remplissage du tableau avec des valeurs de test
    for (i = 0; i < ARRAY_SIZE; ++i) {
        array[i] = i + 1;
    }

    pthread_mutex_t lock;
    pthread_mutex_init(&lock, NULL);

    pthread_t threads[NUM_THREADS];             // Tableau pour stocker les identifiants des threads
    PartialSumArgs thread_args[NUM_THREADS];   // Tableau pour stocker les arguments des threads

    int section_size = ARRAY_SIZE / NUM_THREADS;  // Taille de chaque section du tableau

    // Création des threads et définition de leurs arguments
    for (i = 0; i < NUM_THREADS; ++i) {
        thread_args[i].start = (array + i * section_size);  // Début de la section
        thread_args[i].end = (array + ((i == NUM_THREADS - 1) ? ARRAY_SIZE : (i + 1) * section_size));  // Fin de la section
        thread_args[i].lock = &lock;  // Mutex partagé

        // Création du thread et gestion des erreurs
        if (pthread_create(&threads[i], NULL, sum_partial, (void *)&thread_args[i]) != 0) {
            fprintf(stderr, "Erreur lors de la création du thread %d\n", i);
            return 1;
        }
    }

    // Attente de la fin de tous les threads
    for (i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], NULL);
    }

    // Affichage du résultat final
    printf("Somme totale : %d\n", total_sum);

    pthread_mutex_destroy(&lock);  // Destruction du mutex

    return 0;
}
