/*
*  On my honor, I pledge that I have neither received nor provided improper assistance in my completion on this assignment.
*  Signed: Kim Woo Bin   Student Number: 21600124
*/

#include <iostream>
#include <iomanip>

struct Clock{
	int hr, min, sec;
};

using pClock = Clock*;
void tick(pClock ptr);
void show(pClock ptr);

int main(void){
	pClock ptr = new Clock {14, 38, 56};
	for(int i = 0; i < 6; ++i){
		tick(ptr);
		show(ptr);
	}
	delete ptr;
}

void tick(pClock ptr){
	ptr -> sec++;
	if(ptr -> sec == 60){
		ptr -> sec = 0;
		ptr -> min++;
		if(ptr -> min == 60){
			ptr -> min = 0;
			ptr -> hr++;
		}
	}

}

void show(pClock ptr){
	std::cout.fill('0');
	std::cout << std::setw(2) << ptr -> hr << " : "
						<< std::setw(2) << ptr -> min << " : "
						<< std::setw(2) << ptr -> sec << std::endl;
}
