/*
 * event.cpp
 *
 *  Created on: Feb 27, 2016
 *      Author: hans
 */
#include "event.h"

Event::Event(int e, int c, int p, int t) {
	// timestamp to execute
	PID = p;
	timestamp = e;
	transition = t;
	int timeCreated = c;
}

