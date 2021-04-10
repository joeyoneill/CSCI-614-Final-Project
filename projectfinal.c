#include <stdio.h>
#include <time.h>  
#include <stdlib.h>
#include <string.h>

#define BILLION  1000000000L;

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

int array[1000]; //array for time trials use to sort then find median

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

void funcB(void){
    struct timespec start, stop;
    double accum;
    char *arr;
    int a = 0;
    //begin outer loop to record time 
    for (int i = 0; i < 1000; i++) {
    //inner loop  
    	clock_gettime(CLOCK_REALTIME, &start);
    	arr = funcA();
        while(a < 5){
        	printf("%s\n",arr); 
        //access to a position in array NEEDED 
        	a++;
        }
        clock_gettime(CLOCK_REALTIME, &stop);
        accum = ( stop.tv_sec - start.tv_sec ) + ( stop.tv_nsec - start.tv_nsec ); // / BILLION;

        printf("%f\n", accum);

        array[i] = accum; //then take median
    	free(arr);
    }
    arr = NULL;
  
}

int main () {
    //funcB();

    //get_cache_block_size();
    get_cache_size();

    return 0;
}

