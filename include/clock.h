/*
On my honor, I pledge that I have neither received nor provided improper assistance in my completion on this assignment.
Signed: Kim Woo Bin   Student Number: 21600124
*/
#ifndef CLOCK_H
#define CLOCK_H
struct Clock{
	int hr, min, sec;
};
using pClock = Clock*;

void tick(pClock clk);
void show(pClock clk, char end = '\n');
void runs(pClock clk, char end = '\n');


#endif
