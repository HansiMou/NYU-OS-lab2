/*
 * prepare.cpp
 *
 *  Created on: Feb 26, 2016
 *      Author: hans
 */

#include "prepare.h"
Prepare::Prepare() {
	procFile = randFile = NULL;
	typeOfSched = quantum = 0;
}

Prepare::~Prepare() {
	if (randFile != NULL) {
		fclose(randFile);
	}
	if (procFile != NULL) {
		fclose(procFile);
	}
}

bool Prepare::parseCommand(int argc, char*argv[]) {
	if (argc < 3) {
		printf("Wrong number of arguments.\n");
		return false;
	}

	int c;
	 int index;
	bool first = true;
	while ((c = getopt(argc, argv, "vs:")) != -1)
		switch (c) {
		case 's':
			if (optarg[0] == 'F') {
				typeOfSched = 0;
			} else if (optarg[0] == 'L') {
				typeOfSched = 1;
			} else if (optarg[0] == 'S') {
				typeOfSched = 2;
			} else if (optarg[0] == 'R') {
				typeOfSched = 3;
				sscanf(optarg + 1, "%d", &quantum);
			} else if (optarg[0] == 'P') {
				typeOfSched = 4;
				sscanf(optarg+1, "%d", &quantum);
			}
			break;
		default:
			exit(1);
		}
	for (index = optind; index < argc; index++) {
		if (first) {
			procFile = fopen(argv[index], "r");
			first = false;
		} else {
			randFile = fopen(argv[index], "r");
		}
	}
	if (!procFile || !randFile) {
		printf("Unable to open file.\n");
		return false;
	}
	char buf[100];
	fgets(buf, 100, randFile);
	return true;
}

std::vector<Process> Prepare::getProcesses() {
	std::vector<Process> p;
	char buf[100];
	int counter = 0;

	while (fgets(buf, 100, procFile) != NULL) {
		int a, b, c, d;
		sscanf(buf, "%d%d%d%d", &a, &b, &c, &d);
		Process p1(counter++, a, b, c, d, myRandom(4));
		p1.dynamic_prio = p1.static_prio-1;
		p.push_back(p1);
	}
	return p;
}

Scheduler* Prepare::getScheduler() {
    std::vector<Process> proc = this->getProcesses();
    switch (typeOfSched) {
        case 0: return new FCFSScheduler();
        case 1: return new LCFSScheduler();
        case 2: return new SJFScheduler();
        case 3: return new RRScheduler(quantum);
        case 4: return new PRIOScheduler(quantum);
        default: return NULL;
    }
}

void Prepare::putEvent(Event e) {
   int index = EventQueue.size();
   for (int i = 0; i < EventQueue.size(); i++) {
       if (e.timestamp < EventQueue[i].timestamp) {
           index = i;
           break;
       }
   }
   EventQueue.insert(EventQueue.begin() + index, e);
}
int Prepare::isEmpty(){
	return EventQueue.empty();
}
Event Prepare::getEvent() {
    Event e = Event(-1, -1, -1, -1);
    if (!EventQueue.empty()) {
        e = EventQueue.front();
        EventQueue.erase(EventQueue.begin());
    }
    return e;
}
int Prepare::myRandom(int burst) {
    char buf[100];
    int res;

    fgets(buf, 100, randFile);
    // if reaches the end, wrap around
    if (feof(randFile)) {
        fseek(randFile, 0, SEEK_SET);
        fgets(buf, 100, randFile);
        fgets(buf, 100, randFile);
    }
    sscanf(buf, "%d", &res);
//    	printf("%d %d\n", res, burst);
    return 1 + res%burst;
//    return ret;
}
