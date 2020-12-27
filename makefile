output: main.o listFunctions.o doFunctions.o 
	gcc main.o listFunctions.o doFunctions.o -o Project4

main.o: main.c project4.h
	gcc -c main.c

doFunctions.o: doFunctions.c project4.h
	gcc -c doFunctions.c

listFunctions.o: listFunctions.c project4.h
	gcc -c listFunctions.c
		
target: dependencies
	action

clean: 
	rm *.o output

