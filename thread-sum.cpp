/******************************************************************************
It must be a program that calculates the average of a string consisting of 2-digit 10-element random numbers with 5 threads.
[Write Thread Number and ID on the screen]

10 ELEMANLI RASTGELE URETILMIS 2 BASAMAKLI SAYILARDAN OLUSAN BIR DIZININ 
ORTALAMSINI 5 ADET THREAD ILE HESAPLAYAN PROGRAMDIR. 
[Thread Numarasini ve ID sini ekranda yazsin]
*******************************************************************************/

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include <stdlib.h>

#define index 5 // 5 Threads is goint to used
#define numbers 10 // 10 numbers must be in the array

int total = 0 ;
int thno = 0 ;
int arr[numbers];
sem_t sem;

void* runner(void* id){
    int* myID = (int*) id;
    total = 0;
    for(int i = 0 ; i<numbers ; i++){
        sem_wait(&sem);
        total += arr[i];
        sem_post(&sem);
    }
    sem_wait(&sem);
    thno ++;
    sem_post(&sem);
    printf("ID: %d \t Thread No: %d \n", *myID, thno);
}

// int main(int argc, char* argv[])
int main()
{
    // if argc != 2 return -1;
    // int index = atoi(argv[1]);
    //if index<0 return -1;
    sem_init(&sem,0,1);
    pthread_t tids[index];
    srand(time(NULL));
    for(int i = 0 ; i<numbers ; i++){
        arr[i] = rand()%90+10; //2 Digit numbers
    }
    printf("My datas: ");
    for(int i = 0 ; i<numbers ; i++){
        printf("%d ",arr[i]);
    }
    printf("\n \n");
    
    for(int i =0 ; i<index ; i++){
        pthread_create(&tids[i],NULL,runner,(void*)&tids[i]);
    }
    for(int i =0 ; i<index ; i++){
        pthread_join(tids[i],NULL);
    }
    printf("Sum: %d \n", total);
    float avg = float((total*1.0)/numbers);
    printf("AVG: %.2f", avg);
    return 0;
}
