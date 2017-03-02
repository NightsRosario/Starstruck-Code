#pragma systemFile

#ifndef LIB_H_
#define LIB_H_

void
clearLCDLines () {
	clearLCDLine(0);
	clearLCDLine(1);
}

void
waitForReleased7D () {
	while (vexRT[Btn7D]){} wait1Msec(25);
}

#endif
