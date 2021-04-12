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

//turn nanoseconds into sec easier readability
static long long ts_usecs(struct timespec t) { 
  return (t.tv_sec * 1000000000 + t.tv_nsec);
}

// 1. How big is a cache block?
void get_cache_block_size() {
    // Cache Block Size is cache_alignment in the /proc/cpuinfo file
    FILE *f;
    char s;
    int count = 0;

    // Gets the cache size from this file
    f = fopen("/proc/cpuinfo","r");
    while((s=fgetc(f))!=EOF) {
        count = count + 1;
    }
    fclose(f);

    char cpuinfo[count];

    // Gets the cache size from this file
    f = fopen("/proc/cpuinfo","r");
    int index = 0;
    while((s=fgetc(f))!=EOF) {
        cpuinfo[index] = s;
        index++;
    }
    fclose(f);

    for(int i = 0; i < count; i++) {
        if(cpuinfo[i] == 'c' && cpuinfo[i+5] == '_' && cpuinfo[i+6] == 'a' && cpuinfo[i+14] == 't') {
            //for(int j = 0; j < 20; j++) {
            //    printf("%c", cpuinfo[i + j]);
            //}
            printf("Cache Block Size: %c", cpuinfo[i + 18]);
            printf("%c", cpuinfo[i + 19]);
            break;
        }
    }
    printf("\n");
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

// Sorting mechanism to find time in time_array
void selectionSort(int arr[], int n){
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

// Main Array for timing experimentation
int timing(int n) {
    // time array initialization
    const int time_array_size = 1000;
    int time_array[time_array_size];

    //
    for(int j = 0; j < 1000; j++) {
        // Testing
        const int int_arr_size = n;
        int int_array[int_arr_size];

        // Timing
        struct timespec start, stop;
        clock_gettime(CLOCK_MONOTONIC, &start);

        // Inner For Loop
        for (int i = 0; i < int_arr_size; i++) {
            // Access in memory
            int_array[i] = i * 3;
        }
        clock_gettime(CLOCK_MONOTONIC, &stop);

        //printf("%d: %lld\n", j+1, ts_usecs(stop) - ts_usecs(start));
        time_array[j] = ts_usecs(stop) - ts_usecs(start);
    }

    // Sort Time Array
    selectionSort(time_array, time_array_size);

    // Median Time of array
    int median = time_array[time_array_size/2];

    return median;
}

void print_timings() {
    int one = timing(1);
    int two = timing(2);
    int four = timing(4);
    int eight = timing(8);
    int total = one + two + four + eight;

    printf("Time at array size 1: %d ns\n", one);
    printf("Time at array size 2: %d ns\n", two);
    printf("Time at array size 4: %d ns\n", four);
    printf("Time at array size 8: %d ns\n", eight);
    printf("Time at array size 16: %d ns\n", timing(16));
    printf("Time at array size 32: %d ns\n", timing(32));
    printf("Time at array size 64: %d ns\n", timing(64));
    printf("Time at array size 128: %d ns\n", timing(128));
    printf("Time at array size 256: %d ns\n", timing(256));
    printf("Time at array size 512: %d ns\n", timing(512));
    printf("Time at array size 1024: %d ns\n", timing(1024));
    printf("Average Cache Reference Timing (mean of timing size 1, 2, 4, and 8): %d ns\n", total/4);
}

int main () {
    get_cache_block_size();
    get_cache_size();

    print_timings();

    return 0;
}

