#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h> // Pour utiliser la fonction sleep

void * thread1(void * args)
{
    while(1)
    {
        printf("thread 1\n"); // Affiche message
        sleep(5); // Attendre
    }
    return NULL;
}

void *thread2(void * args)
{
    while(1)
    {
        printf("thread 2\n"); // Afficher message
        sleep(3); // Attendre
    }
    return NULL;
}

int main()
{
    pthread_t t1, t2; // Déclaration des threads

    pthread_create(&t1, NULL, thread2, NULL); // Crée le premier thread
    pthread_create(&t2, NULL, thread2, NULL); // Crée le deuxième thread

    pthread_join(t1, NULL); // Attente de la fin du premier thread
    pthread_join(t2, NULL); // Attente de la fin du deuxième thread

    return 0;
}
