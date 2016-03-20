/*
 * event.h
 *
 *  Created on: Feb 27, 2016
 *      Author: hans
 */

#ifndef EVENT_H_
#define EVENT_H_


class Event {
public:
	Event(int, int, int, int);
	int timestamp;
	int timeCreated;
	int PID;

	// 1: created -> ready
	// 2: ready -> running
	// 3: running -> blocked
	// 4: blocked->ready
	// 5: running-> ready
	// 6: finished
	int transition;

};


#endif /* EVENT_H_ */
