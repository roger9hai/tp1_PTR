#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// Fonction exécutée par le thread
void *thread_function(void *argument) {
    char *message = (char *) argument; // Réception de l'argument
    printf("Message = %s\n", message); // Affichage du message
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t thread; // Déclaration d'une variable de thread
    char *message = "Hello world!"; // Message à passer au thread

    // Création du thread
    pthread_create(&thread, NULL, thread_function, message);
    // Attente de la fin du thread
    pthread_join(thread, NULL);
		
    return 0;
}
