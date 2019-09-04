
shellcompile: myshell.o  intial.o new.o
	g++ -o shellcompile myshell.o intial.o new.o

intial.o: intial.c intial.h	
	g++ -c intial.cpp 

new.o: new.cpp new.h
	g++ -c new.cpp	

myshell.o: myshell.c 
	g++ -c myshell.cpp

clean:
	rm *.o shellcompile	









