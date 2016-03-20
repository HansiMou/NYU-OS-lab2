/*
 * process.cpp
 *
 *  Created on: Feb 26, 2016
 *      Author: hans
 */

#include "process.h"
Process::Process() {

}
Process::Process(int pid, int a, int b, int c, int d, int pr) {
    PID = pid;
    at = a;
    remainTime = tc = b;
    cb = c;
    io = d;
    remainingCB = lastReady = rt = ft = it = cw = 0;
    static_prio = pr;
}



