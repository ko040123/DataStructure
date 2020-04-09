/*
*  On my honor, I pledge that I have neither received nor provided improper assistance in my completion on this assignment.
*  Signed: Kim Woo Bin   Student Number: 21600124
*/

#include <iostream>
#include <iomanip>
#include <unistd.h>
#include "clock.h"


void tick(pClock clk){
	clk -> sec++;
	if(clk -> sec == 60){
		clk -> sec = 0;
		clk -> min++;
		if(clk -> min == 60){
			clk -> min = 0;
			clk -> hr++;
		}
	}
}

void show(pClock clk, char end /* default = '\n' */){
	std::cout.fill('0');
	std::cout	<< std::setw(2) << clk -> hr << " : "
						<< std::setw(2) << clk -> min << " : "
						<< std::setw(2) << clk -> sec << end;
}

void runs(pClock clk, char end /* default = '\n' */){
	while(true){
		sleep(1);
		tick(clk);
		show(clk, end);
	}
}
