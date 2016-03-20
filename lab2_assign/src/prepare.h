/*
 * prepare.h
 *
 *  Created on: Feb 26, 2016
 *      Author: hans
 */

#ifndef PREPARE_H_
#define PREPARE_H_

#include <cstdio>
#include <vector>
#include <cstring>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <string.h>
#include <stdlib.h>
#include "process.h"
#include "scheduler.h"
#include "event.h"

class Prepare {
public:
	Prepare();
	~Prepare();
	// process file
	FILE* procFile;

	// random file
	FILE* randFile;

	// quantum
	int quantum;

	int typeOfSched;
	// event queue
	std::vector<Event> EventQueue;
    
	// parse the input
	bool parseCommand(int, char**);

	// get the collection of processes
	std::vector<Process> getProcesses();


	// return the scheduler parsed
	Scheduler* getScheduler();


	//add an event to the event queue
	void putEvent(Event);

	// pull an event from the event queue
	Event getEvent();

	int myRandom(int);
	int isEmpty();
};

#endif /* PREPARE_H_ */
