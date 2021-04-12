
output: projectfinal.o
  g++ projectfinal.o -output 

projectfinal.o: projectfinal.c
  g++ -c projectfinal.c
  
clean:
  rm *.o output 
