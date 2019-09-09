
shellcompile: myshell.o  intial.o splitwrd.o pipedup.o make_background.o alarmset.o
	g++ -o shellcompile myshell.o intial.o splitwrd.o pipedup.o make_background.o alarmset.o

intial.o: intial.cpp intial.h
	g++ -c intial.cpp 

pipedup.o: pipedup.cpp pipedup.h
	g++ -c pipedup.cpp
splitwrd.o: splitwrd.cpp splitwrd.h
	g++ -c splitwrd.cpp	
make_background.o:make_background.cpp make_background.h
	g++ -c make_background.cpp	
alarmset.o:alarmset.cpp alarmset.h
	g++ -c alarmset.cpp	

myshell.o: myshell.cpp intial.cpp splitwrd.cpp make_background.cpp alarmset.o
	g++ -c myshell.cpp

clean:
	rm *.o shellcompile	









