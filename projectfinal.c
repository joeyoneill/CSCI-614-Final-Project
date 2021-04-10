#include <stdio.h>
#include <time.h>  
#include <stdlib.h>
#include <string.h>

/* Notes from class 
Timing in C for project 
clock_gettime()
clock_gettime(CLOCK_MONOTONIC, &t1);
Multiple accesses to memory 
Get average 
Put average times in array and find median 
Loops access memory 
Loop around them that are timing 1000 runs 
Data in array ints, characters exc 
Where do you declare array not inside function (heap malloc) 
DONT FORGET FREE */ 

#define ARR_SIZE 1000

int array[ARR_SIZE]; //array for time trials use to sort then find median  

//turn nanoseconds into sec easier readability
static long long ts_usecs(struct timespec t) { 
  return (t.tv_sec * 1000000000 + t.tv_nsec);
}

// 1. How big is a cache block?
void get_cache_block_size() {

}

// 2. How big is the cache?
void get_cache_size() {
    FILE *f;
    char s;

    // Gets the cache size from this file
    f = fopen("/sys/devices/system/cpu/cpu0/cache/index0/size","r");
    printf("Cache Size: ");
    while((s=fgetc(f))!=EOF) {
        printf("%c",s);
    }
    printf("\n");
    fclose(f);
}

char *funcA(void){
    //accessing memory 
    char *arr = malloc(sizeof(char) * 20); //make large enough for cache 32K
    strcpy(arr, "Hello");
    return arr;
}

void time_main_memory(void){
    struct timespec t0, t1;
    char *arr;
    int a = 0;
    //begin outer loop to record time 
    for (int i = 0; i < ARR_SIZE; i++) {
        //inner loop  
        clock_gettime(CLOCK_MONOTONIC, &t0);
        arr = funcA();
        while(a < 5){
            printf("%s\n",arr);

            // non print access needed

            a++;
        }

        clock_gettime(CLOCK_MONOTONIC, &t1);
        long long t_start = ts_usecs(t0);
        long long t_end = ts_usecs(t1);

        array[i]= (t_end - t_start); //add time taken to array 

        free(arr); //free space
    }
    arr = NULL;
}

void selectionSort(int arr[], int n){ //sorting the array of times 
    int i, j, min_n;
 
    for (i = 0; i < n - 1; i++) {
 
        // Find the minimum element in unsorted array
        min_n = i;
        for (j = i + 1; j < n; j++)
            if (arr[j] < arr[min_n])
                min_n = j;
 
        // Swap the found minimum element
        // with the first element
        long long hold = arr[i];
        arr[i] = arr[min_n];
        arr[min_n] = hold;
    }
}

int main () {
    time_main_memory();
    selectionSort(array, ARR_SIZE);
    printf("Main? Memory Reference time: %d\n", array[500]);

    //get_cache_block_size();
    get_cache_size();

    return 0;
}

