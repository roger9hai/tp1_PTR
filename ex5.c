#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_TASKS 3

typedef struct {
    int id;
    int period;  // en secondes
} TachePeriodique; // Renommer la structure

void *fonctionTache(void *arg) {
    TachePeriodique *tache = (TachePeriodique *)arg;

    while (1) {
        sleep(tache->period);
        printf("Tâche %d exécutée.\n", tache->id);
    }

    return NULL;
}

int main() {
    int PERIODES_TACHES[] = {1, 2, 3}; // Tableau des périodes des tâches
    pthread_t threads[NUM_TASKS];
    TachePeriodique taches[NUM_TASKS];
    int i;

    // Création des threads pour chaque tâche périodique
    for (i = 0; i < NUM_TASKS; ++i) {
        taches[i].id = i + 1;
        taches[i].period = PERIODES_TACHES[i];
        pthread_create(&threads[i], NULL, fonctionTache, (void *)&taches[i]);
    }

    sleep(10); // Attendre pendant 10 secondes

    // Annulation et attente de chaque thread
    for (i = 0; i < NUM_TASKS; ++i) {
        pthread_cancel(threads[i]);
        pthread_join(threads[i], NULL);
    }
    return 0;
}
