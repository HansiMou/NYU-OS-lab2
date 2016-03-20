/*
 * scheduler.h
 *
 *  Created on: Feb 26, 2016
 *      Author: hans
 */

#ifndef SCHEDULER_H_
#define SCHEDULER_H_

#include <iostream>
#include <sstream>
#include <vector>
#include <string>

#include "process.h"
class Scheduler {
public:
	int quantum;
	std::vector<Process> readyQueue;

	// returns the name of the scheduler
	virtual std::string getName() = 0;

	// return the the first process in the readyQueue according to type of scheduler
	virtual Process getProcess() = 0;

	// put an event into the ready queue
	virtual void putProcess(Process) = 0;
};

class FCFSScheduler: public Scheduler {
public:
	std::string getName();
	Process getProcess();
	void putProcess(Process);
};

class LCFSScheduler: public Scheduler {
public:
	std::string getName();
	Process getProcess();
	void putProcess(Process);
};

class SJFScheduler: public Scheduler {
public:
	std::string getName();
	Process getProcess();
	void putProcess(Process);
};

class RRScheduler: public Scheduler {
public:
	RRScheduler(int);

	std::string getName();
	Process getProcess();
	void putProcess(Process);
};

class PRIOScheduler: public Scheduler {
public:
	std::vector<Process> activeQueue;
	std::vector<Process> expireQueue;
	PRIOScheduler(int);

	std::string getName();
	Process getProcess();
	void putProcess(Process);
	Process getNewOne(Process, int);
};
#endif /* SCHEDULER_H_ */
