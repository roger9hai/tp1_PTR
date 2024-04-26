#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *fonctionTache1(void *arg) {
    int i = 0;
    while (i < 5) {
        printf("Tache 1\n");
        sleep(5);
        i++;
    }
    return NULL;
}

void *fonctionTache2(void *arg) {
    int j = 0;
    while (j < 3) {
        printf("Tache 2\n");
        sleep(3);
        j++;
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t thread1, thread2;


    /*
    pthread_create(&thread1, NULL, fonctionTache1, NULL);
    pthread_create(&thread2, NULL, fonctionTache2, NULL);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    return EXIT_SUCCESS;
    */

    pthread_create(&thread1, NULL, fonctionTache1, NULL);
    pthread_join(thread1, NULL);
    pthread_create(&thread2, NULL, fonctionTache2, NULL);
    pthread_join(thread2, NULL);
    return EXIT_SUCCESS;
}
