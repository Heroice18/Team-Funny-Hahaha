a.out : ui.o sha256.o 
	g++ ui.o sha256.o 

ui.o : cipher.h cipher01.h cipher02.h cipher03.h cipher04.h cipher05.h cipher06.h cipher07.h ui.cpp
	g++ -c ui.cpp

sha256.o : sha256.h sha256.cpp
	g++ -c sha256.cpp

clean :
	rm *.o a.out
