/*
 * scheduler.cpp
 *
 *  Created on: Feb 26, 2016
 *      Author: hans
 */

#include "scheduler.h"

std::string FCFSScheduler::getName() {
	return "FCFS";
}

Process FCFSScheduler::getProcess() {
	Process res;
	if (!readyQueue.empty()) {
		res = readyQueue.front();
		readyQueue.erase(readyQueue.begin());
	}
	return res;
}

void FCFSScheduler::putProcess(Process p) {
	readyQueue.push_back(p);
}

std::string LCFSScheduler::getName() {
	return "LCFS";
}

Process LCFSScheduler::getProcess() {
	Process res;
	if (!readyQueue.empty()) {
		res = readyQueue.back();
		readyQueue.pop_back();
	}
	return res;
}

void LCFSScheduler::putProcess(Process p) {
	readyQueue.push_back(p);
}

std::string SJFScheduler::getName() {
	return "SJF";
}

Process SJFScheduler::getProcess() {
	Process res;
	if (!readyQueue.empty()) {
		int min = readyQueue[0].remainTime;
		int index = 0;
		for (int i = 1; i < readyQueue.size(); i++) {
			if (readyQueue[i].remainTime < min) {
				min = readyQueue[i].remainTime;
				index = i;
			}
		}
		res = readyQueue[index];
		readyQueue.erase(readyQueue.begin() + index);
	}
	return res;
}

void SJFScheduler::putProcess(Process p) {
	readyQueue.push_back(p);
}

RRScheduler::RRScheduler(int q) {
	quantum = q;
}

std::string RRScheduler::getName() {
	return "RR";
}

Process RRScheduler::getProcess() {
	Process res;
	if (!readyQueue.empty()) {
		res = readyQueue.front();
		readyQueue.erase(readyQueue.begin());
	}
	return res;
}

void RRScheduler::putProcess(Process p) {
	readyQueue.push_back(p);
}

PRIOScheduler::PRIOScheduler(int q) {
	quantum = q;
}

std::string PRIOScheduler::getName() {
	return "PRIO";
}

Process PRIOScheduler::getProcess() {
	if (activeQueue.size() == 0) {
		std::vector<Process> tmp = activeQueue;
		activeQueue = expireQueue;
		expireQueue = tmp;
	}

	Process res;
	int max = activeQueue[0].dynamic_prio;
	int index = 0;
	for (int i = 1; i < activeQueue.size(); i++) {
		if (activeQueue[i].dynamic_prio > max) {
			max = activeQueue[i].dynamic_prio;
			index = i;
		}
	}
	res = activeQueue[index];
	activeQueue.erase(activeQueue.begin() + index);
	return res;
}

void PRIOScheduler::putProcess(Process p) {
	if (p.dynamic_prio == -1) {
		p.dynamic_prio = p.static_prio-1;
		expireQueue.push_back(p);
	} else
		activeQueue.push_back(p);
}


