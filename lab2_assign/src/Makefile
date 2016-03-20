sched: main.o process.o prepare.o scheduler.o event.o
	g++ -o sched main.o process.o prepare.o scheduler.o event.o 

main.o: main.cpp
	g++ -c main.cpp

process.o: process.cpp process.h
	g++ -c process.cpp

prepare.o: prepare.cpp prepare.h
	g++ -c prepare.cpp

scheduler.o: scheduler.cpp scheduler.h
	g++ -c scheduler.cpp

event.o: event.cpp event.h
	g++ -c event.cpp