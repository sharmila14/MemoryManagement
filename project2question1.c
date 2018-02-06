#include<stdio.h>
#include<sys/types.h>
#include<stdlib.h>
#include<time.h>

/*
 * struct Process 
 *structure to hold the details of processes
 */


struct Process  {
        int id;
        int mem;
        int cyc;
        int flag;
        void *mem_ptr;
};

int memoryFootPrint(void);
void start_thread(int *i);
void *process (void *info);
        struct Process p[500];
        int a[500];
        int sum = 0;

int main() {

        int k, i , pid = 23458;
        int memory = 0, cycles = 0;
        clock_t start, end;
        int stop = 0;
// To enter the number of processes to be generated
        do {
        printf("\n Enter number of processes to be generated \n");
        scanf("%d", &k);
        if (k > 499)
        printf("\n Enter a number less than 500");
        } while (k > 499);

/*
 * used distribution to distribute the random numbers between 
 * given number of processes
 */
        for (i = 0; i < k/2; i++)

        {
                p[i].id = pid + 1;
                p[i].mem = memoryFootPrint();
                p[i].cyc = (rand() % (11000 - 1000)) + 1000;
                memory = memory + p[i].mem;
                cycles = cycles + p[i].cyc;
                pid++;

        }

        for (i = k/2; i < k; i++)

        {
                p[i].id = pid + 1;
                p[i].mem = memoryFootPrint();
                p[i].cyc = (rand() % (11000 - 1000)) + 1000;
                memory = memory + p[i].mem;
                cycles = cycles + p[i].cyc;
                pid++;
        }
        memory = memory / k;
        cycles = cycles / k;
        for (i = 0; i < k; i++)

        {
                printf("Process number %d", i + 1);
                printf("\n\t Process ID %d", p[i].id);
                printf("\n\t Memory in KB %d", p[i].mem);
                printf("\n\t Number of Cycles %d\n", p[i].cyc);
        }

        printf("\n Mean Memory is (in KB) = %d ", memory);
        printf("\n Mean of Cycles is = %d ", cycles);
        printf("\n");
/*
 * Noting down the clock time before starting to allocate the memory 
 */
start = clock();        
        for (i = 0; i < k; i++)
        {
            p[i].mem_ptr = malloc(p[i].mem * 1024);    // Allocating the memory using system malloc 
            p[i].flag = 0;
            a[i] = i;
            start_thread(&a[i]);       // Initiating Thread to run for execution for required amount of cycles
        }
        while(sum != k);   // Logic to wait for all threads to finish there  task 
end = clock();
        
        // Calculating the total number of time in seconds for total execution 
        printf("Total time for excution : %lf\n", (double)(end - start)/CLOCKS_PER_SEC);
       pthread_exit();
        return 0;
}

//Thread Handler function which will execute for required number of cycles
//and frees the memory
void *process (void *info){

    int value  = *(int*)info;
    printf("Process with %d pid : %d excuting\n ", value ,p[value].id);
    sleep(p[value].cyc/ 1000);
    printf("Process with pid : %d terminating\n ", p[value].id);
    if (p[value].mem_ptr != NULL)
        free(p[value].mem_ptr);
    p[value].flag = 1;
    sum += 1;
    return 0;
}


// start_thread function to create thread
void start_thread(int *value)
{
    pthread_t tid;
    if (pthread_create(&tid, NULL, process,(void*)value) < 0)
        printf("Error\n");
}


//To randomly allocate the  memory with in 10Mb
int memoryFootPrint() {

        if ((rand() % 1001) > (204))
           return (rand() % 204) + 1;
        else
           return (rand() % (1001 - 204)) + 204;
}

