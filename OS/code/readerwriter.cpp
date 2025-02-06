#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h> // For sleep()
#include <cstdint> 

sem_t mutex; // Mutex for reader count access
sem_t db;    // Semaphore for database access
int readercount = 0;

void *reader(void *p);
void *writer(void *p);

int main() {
    sem_init(&mutex, 0, 1);
    sem_init(&db, 0, 1);

    pthread_t readers[2], writers[2];

    // Create reader and writer threads
    for (int i = 0; i < 2; i++) {
        pthread_create(&readers[i], NULL, reader, (void *)(intptr_t)(i + 1));
        pthread_create(&writers[i], NULL, writer, (void *)(intptr_t)(i + 1));
    }

    // Wait for all threads to complete
    for (int i = 0; i < 2; i++) {
        pthread_join(readers[i], NULL);
        pthread_join(writers[i], NULL);
    }

    // Cleanup semaphores
    sem_destroy(&mutex);
    sem_destroy(&db);

    return 0;
}

void *reader(void *p) {
    printf("Reader %ld is trying to read\n", (intptr_t)p);
    sem_wait(&mutex); // Acquire mutex for reader count
    readercount++;
    if (readercount == 1) {
        sem_wait(&db); // First reader locks the database
    }
    sem_post(&mutex); // Release mutex for reader count

    printf("Reader %ld is reading\n", (intptr_t)p);
    sleep(1); // Simulate reading

    sem_wait(&mutex); // Acquire mutex for reader count
    readercount--;
    if (readercount == 0) {
        sem_post(&db); // Last reader unlocks the database
    }
    sem_post(&mutex); // Release mutex for reader count

    printf("Reader %ld finished reading\n", (intptr_t)p);
    return NULL;
}

void *writer(void *p) {
    printf("Writer %ld is trying to write\n", (intptr_t)p);
    sem_wait(&db); // Wait for database access

    printf("Writer %ld is writing\n", (intptr_t)p);
    sleep(1); // Simulate writing

    sem_post(&db); // Release database access
    printf("Writer %ld finished writing\n", (intptr_t)p);
    return NULL;
}
