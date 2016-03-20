/*
 * main.cpp
 *
 *  Created on: Feb 26, 2016
 *      Author: hans
 */

#include <iostream>
#include <cstring>
#include <cstdio>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

#include "prepare.h"
#include "process.h"
typedef int stime_t;
typedef struct WaitIO {
	int beg;
	int end;
} WaitIO;
bool compare(WaitIO a, WaitIO b) {
	return a.beg == b.beg ? a.end < b.end : a.beg < b.beg;
}
int main(int argc, char* argv[]) {
	Prepare prepare;
	Scheduler* sched;
	std::vector<Process> processes;
	std::vector<WaitIO> wait;

	if (!prepare.parseCommand(argc, argv)) {
		exit(0);
	}
	processes = prepare.getProcesses();
	sched = prepare.getScheduler();

	// put all the processes into readyqueue
	for (int i = 0; i < processes.size(); i++) {
		prepare.putEvent(
				Event(processes[i].at, processes[i].at, processes[i].PID, 1));
	}

	// stores the current time
	int clock = processes[0].at;
	Event cur = Event(0, 0, 0, 0);
	int pid, cb;

	// record the finish time of last running process
	int lr = 0;
	while (!prepare.isEmpty()) {
		cur = prepare.getEvent();
//		printf("%d\n", 1);
		pid = cur.PID;
		clock = std::max(clock, cur.timestamp);
		switch (cur.transition) { // which state to transition to
		// created -> ready
		case 1:
			processes[pid].lastReady = clock;
			prepare.putEvent(
					Event(processes[pid].at, processes[pid].at, pid, 2));
			// added to the run queue
			sched->putProcess(processes[pid]);
			break;

			// ready -> running
		case 2:
			// if a process is running right now
			if (cur.timestamp < lr) {
				cur.timestamp = lr;
				prepare.putEvent(cur);
				continue;
			}

			pid = sched->getProcess().PID;

			processes[pid].cw = processes[pid].cw + clock
					- processes[pid].lastReady;
			cur.timeCreated = processes[pid].lastReady;
			// if LCLS, FCFS, SJF
			if (sched->getName() != "RR" && sched->getName() != "PRIO") {
				// generate a random CB
				processes[pid].remainingCB = prepare.myRandom(
						processes[pid].cb);
				cb = processes[pid].remainingCB;

				// remain time <= cpu burst
				if (processes[pid].remainTime <= cb) {

					// finished
					lr = clock + processes[pid].remainTime;
					prepare.putEvent(
							Event(clock + processes[pid].remainTime, clock, pid,
									6));
					processes[pid].remainTime = 0;

					// remain time > cpu burst, after the burst, blocked
				} else {
					prepare.putEvent(Event(clock + cb, clock, pid, 3));

					lr = clock + cb;
					processes[pid].remainTime = processes[pid].remainTime - cb;
				}
			} else if (sched->getName() == "RR" || sched->getName() == "PRIO") {
				// whether new cb should be generated
				if (processes[pid].remainingCB == 0) {
					processes[pid].remainingCB = prepare.myRandom(
							processes[pid].cb);
				}
//				if(pid == 1)
//					printf("%d %d ", processes[pid].remainTime, processes[pid].remainingCB);
				// quantum <= remaining cb
				if (sched->quantum <= processes[pid].remainingCB) {
					// after running, put into block/ready
					if (processes[pid].remainTime > sched->quantum) {

						prepare.putEvent(
								Event(clock + sched->quantum, clock, pid,
										processes[pid].remainingCB
												== sched->quantum ? 3 : 5));

						lr = clock + sched->quantum;
						processes[pid].remainingCB -= sched->quantum;
						processes[pid].remainTime -= sched->quantum;

						// process will finish
					} else {
//						printf("%d %d ", processes[pid].remainTime, processes[pid].remainingCB);

						prepare.putEvent(
								Event(clock + processes[pid].remainTime, clock,
										pid, 6));
						lr = clock + processes[pid].remainTime;
						processes[pid].remainTime = 0;
					}

					// quantum > remaining cb
				} else {
					// process will finish
					if (processes[pid].remainTime
							<= processes[pid].remainingCB) {
						prepare.putEvent(
								Event(clock + processes[pid].remainTime, clock,
										pid, 6));
						lr = clock + processes[pid].remainTime;
						processes[pid].remainTime = 0;

						// put into blocked
					} else {
						prepare.putEvent(
								Event(clock + processes[pid].remainingCB, clock,
										pid, 3));
						lr = clock + processes[pid].remainingCB;
						processes[pid].remainTime -= processes[pid].remainingCB;
					}
					processes[pid].remainingCB = 0;
				}
			}

			break;

			// running -> blocked
		case 3: {
			int timeToBlock = prepare.myRandom(processes[pid].io);

			// create IO wait
			WaitIO io;
			io.beg = clock;
			io.end = clock + timeToBlock;
			wait.push_back(io);

			// add new event
			processes[pid].it = processes[pid].it + timeToBlock;
			prepare.putEvent(Event(clock + timeToBlock, clock, pid, 4));

			if (sched->getName() == "PRIO") {
				processes[pid].dynamic_prio = processes[pid].static_prio - 1;
			}

			break;
		}
			// block -> ready
		case 4:
			processes[pid].lastReady = clock;

			prepare.putEvent(Event(clock, clock, pid, 2));
			sched->putProcess(processes[pid]);
			if (sched->getName() == "PRIO") {
				if (processes[pid].dynamic_prio == -1) {
					processes[pid].dynamic_prio = processes[pid].static_prio
							- 1;
				}
			}
			break;

			// running -> ready, only for RR and PRIO
		case 5:
			processes[pid].lastReady = clock;
			prepare.putEvent(Event(clock, clock, pid, 2));
			if (sched->getName() == "PRIO") {
				processes[pid].dynamic_prio--;
			}
			sched->putProcess(processes[pid]);
			if (processes[pid].dynamic_prio == -1) {
				processes[pid].dynamic_prio = processes[pid].static_prio - 1;
			}
			break;

			//finished
		case 6:
			processes[pid].ft = clock;
			break;
		}
	}

	// for the result
	stime_t maxfintime = 0;
	double cpu_util = 0.0;
	double Tol_turnaround = 0.0;
	double io_util = 0.0;
	double Tol_waittime = 0.0;

	std::sort(wait.begin(), wait.end(), compare);
	stime_t end;
	for (int i = 0; i < wait.size(); ++i) {
		if (i == 0 || end <= wait[i].beg) {
			io_util += wait[i].end - wait[i].beg;
			end = wait[i].end;
		} else if (end < wait[i].end) {
			io_util += wait[i].end - end;
			end = wait[i].end;
		}
	}

	std::cout << sched->getName();
	if (sched->getName() == "RR" || sched->getName() == "PRIO") {
		printf(" %d", sched->quantum);
	}
	printf("\n");
	for (int i = 0; i < processes.size(); i++) {
		Process p = processes[i];
		printf("%04d: %4d %4d %4d %4d %1d | %5d %5d %5d %5d\n", p.PID, p.at,
				p.tc, p.cb, p.io, p.static_prio, p.ft, p.ft - p.at, p.it, p.cw);
		if (p.ft > maxfintime) {
			maxfintime = p.ft;
		}
		Tol_turnaround += p.ft - p.at;
		Tol_waittime += p.cw;
		cpu_util += p.tc;
	}
	printf("SUM: %d %.2lf %.2lf %.2lf %.2lf %.3lf\n", maxfintime,
			cpu_util * 100 / maxfintime, io_util * 100 / maxfintime,
			Tol_turnaround / processes.size(), Tol_waittime / processes.size(),
			(double) processes.size() * 100 / maxfintime);

	return 0;
}
