# CSCI 614 Final Project

Joey O'Neill <oneillj1@g.cofc.edu>

Devin Keirnan <devink500@gmail.com>

Related Experimentation Lab: http://igoro.com/archive/gallery-of-processor-cache-effects/


1. How big is a cache block?

64 bits which can be show with the times at different sized arrays. It is similar times up until 16 meaning it is hitting its limits. 16 integers at 4 bytes a piece = 64 bits.


2. How big is the cache?

The cache is 32k bytes.


3. How long does a reference to main memory take?



4. How long does a reference that can be satisfied from the cache take to complete?

The cache remains relatively the same from array sizes 1-16, and the average (which we use the median from 1000 tries) of each can be taken and added together (times from arrays sized 1, 2, 4, 8), then divided by 4 to get the average cache reference to be completed. In the case I am running while writing this, I recieve a reference average of: 55 ns.