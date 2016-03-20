/*
 * process.h
 *
 *  Created on: Feb 26, 2016
 *      Author: hans
 */

#ifndef PROCESS_H_
#define PROCESS_H_

#include <iostream>

class Process {
public:
	Process();
	Process(int, int, int, int, int, int);
//	Process getNewOne(Process, int);
	// process ID
	int PID;

	// remainTime: remaining time to finish
	// remainingCB: remaining CPU burst
	// lastReady: last time the process is in process status, helper
	int remainTime, remainingCB, lastReady;

	// ft: finish time
	// it: io time

	int at, tc, cb, io, it, cw, rt, ft;
	int static_prio;
	int dynamic_prio;
};

#endif /* PROCESS_H_ */
