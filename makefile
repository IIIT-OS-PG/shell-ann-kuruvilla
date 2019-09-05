
shellcompile: myshell.o  intial.o new.o pipeimple.o make_background.o
	g++ -o shellcompile myshell.o intial.o new.o pipeimple.o make_background.o

intial.o: intial.cpp intial.h
	g++ -c intial.cpp 

pipeimple.o: pipeimple.cpp pipeimple.h
	g++ -c pipeimple.cpp
new.o: new.cpp new.h
	g++ -c new.cpp	
make_background.o:make_background.cpp make_background.h
	g++ -c make_background.cpp	

myshell.o: myshell.cpp intial.cpp new.cpp
	g++ -c myshell.cpp

clean:
	rm *.o shellcompile	









