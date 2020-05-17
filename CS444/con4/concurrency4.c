#define _REENTRANT

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include <pthread.h>
#include <semaphore.h>

#define TOT_CUSTOMERS 25

// Prototypes
void *customer(void *num);
void *barber(void *);

void randwait(int secs);

sem_t waitingRoom;   
sem_t barberChair;
sem_t barberPillow;
sem_t seatBelt;
int allDone = 0;

int main(int argc, char *argv[]) {
    pthread_t btid;
    pthread_t tid[TOT_CUSTOMERS];
    long RandSeed;
    int i, numCustomers, numChairs;
    int Number[TOT_CUSTOMERS];

    if (argc != 4) {
    printf("Use: Int customers Int chairs Int seed>\n");
    exit(-1);
    }

    numCustomers = atoi(argv[1]);
    numChairs = atoi(argv[2]);
    RandSeed = atol(argv[3]);

    if (numCustomers > TOT_CUSTOMERS) {
    printf("The maximum number of Customers is %d.\n", TOT_CUSTOMERS);
    exit(-1);
    }

    printf("\nSleepBarber.c\n\n");
    printf("A solution to the sleeping barber problem using semaphores.\n");

    srand48(RandSeed);

    for (i=0; i<TOT_CUSTOMERS; i++) {
    Number[i] = i;
    }

    sem_init(&waitingRoom, 0, numChairs);
    sem_init(&barberChair, 0, 1);
    sem_init(&barberPillow, 0, 0);
    sem_init(&seatBelt, 0, 0);

    pthread_create(&btid, NULL, barber, NULL);

    for (i=0; i<numCustomers; i++) {
    pthread_create(&tid[i], NULL, customer, (void *)&Number[i]);
    }

    for (i=0; i<numCustomers; i++) {
    pthread_join(tid[i],NULL);
    }

    allDone = 1;
    sem_post(&barberPillow);  
    pthread_join(btid,NULL);    
}

void *customer(void *number) {
    int num = *(int *)number;

    printf("%d leaving for barber shop.\n", num);
    randwait(5);
    printf("%d arrived at barber shop.\n", num);

    sem_wait(&waitingRoom);
    printf("%d entering waiting room.\n", num);

    sem_wait(&barberChair);

    sem_post(&waitingRoom);

    printf("%d waking barber.\n", num);
    sem_post(&barberPillow);

    sem_wait(&seatBelt);

    sem_post(&barberChair);
    printf("%d leaving barber shop.\n", num);
}

void *barber(void *junk) {
    while (!allDone) {

    printf("The barber is sleeping\n");
    sem_wait(&barberPillow);

    if (!allDone) {

        printf("The barber is cutting hair\n");
        randwait(3);
        printf("The barber has finished cutting hair.\n");

        sem_post(&seatBelt);
    }
    else {
        printf("The barber is going home for the day.\n");
    }
    }
}

void randwait(int secs) {
    int len;
    len = (int) ((drand48() * secs) + 1);
    sleep(len);
}

