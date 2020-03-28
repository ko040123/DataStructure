/*
*  On my honor, I pledge that I have neither received nor provided improper assistance in my completion on this assignment.
*  Signed: Kim Woo Bin   Student Number: 21600124
*/
#include "clock.h"

int main(void){
	pClock clk = new Clock {11, 58, 56};
	for(int i = 0; i < 6; ++i){
		tick(clk);
		show(clk);
	}
	runs(clk, '\r');
	delete clk;
}
