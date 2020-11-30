
a.out : interact.o message.o messages.o control.o lab12.o
	g++ interact.o message.o messages.o control.o lab12.o

message.o : message.h message.cpp
	g++ -c message.cpp

messages.o : messages.h messages.cpp
	g++ -c messages.cpp

interact.o : interact.h interact.cpp
	g++ -c interact.cpp

control.o : control.h control.cpp
	g++ -c control.cpp

lab12.o : control.h interact.h messages.h message.h lab12.cpp
	g++ -c lab12.cpp

clean :
	rm *.o a.out
