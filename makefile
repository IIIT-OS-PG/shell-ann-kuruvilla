
shellcompile: myshell.o  intial.o new.o
	gcc -o shellcompile myshell.o intial.o new.o

intial.o: intial.c intial.h	
	gcc -c intial.c 

new.o: new.cpp new.h
	g++ -c new.cpp	

myshell.o: myshell.c 
	gcc -c myshell.c

clean:
	rm *.o shellcompile	









