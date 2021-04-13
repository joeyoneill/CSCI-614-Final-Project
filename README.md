# CSCI 614 Final Project

Joey O'Neill <oneillj1@g.cofc.edu>

Devin Keirnan <devink500@gmail.com>

1. How big is a cache block?

64 bits which can be show with the times at different sized arrays. It is similar times up until 16 meaning it is hitting its limits. 16 integers at 4 bytes a piece = 64. This answer can be confirmed with the procfile in which I reference in the output of the code.


2. How big is the cache?

The cache is 32k bytes. This can be seen with the times from the timing_for_cache_and_main() function implemented in our program and displayed by the print_12_to_26() which prints sized of 2^12 to 2^26 which is of sizes 4096 to 67,108,864 byte arrays which since it is an int array, the size of the array is the byte size divided my the sizeof(int) which is 4. Anyways, we can see that the cache (which we are talking about the L1 cache in this instance) sits at 32K bytes which is 2^15 as you can see the first large uptick in from times at size: 16K with a time: 3719203924 ns, then 32K with a time: 3761452094 ns, which are both relatively the same as the times prior shown in the printed output, into 64K which jumps to time: 3983240111 ns and then 128k with 4024861851 ns. 32K is the central point in difference between the time switch meaning it is the end of the cache. This answer can be confirmed with the procfile in which I reference in the output of the code.


3. How long does a reference to main memory take?

The times begin to level off again at size of bytes 4 million so I will averge the size of 4 million until 64 million which in the instance I am currently run I get an average (mean of the five measurements) time of 887362236 ns for the loop to execute.

4. How long does a reference that can be satisfied from the cache take to complete?

I averaged (using the mean) caching loop times from 1024 to 32k which are cache based timings that are all relatively the same. On the instance of the run I am currently running I get a time of 373836204 ns. A single reference to array (invidual iteration of a loop) was measuring at 3.2 ns.