#include <iostream>

using namespace std;

struct Car{
	int age;
	string tag;
};

int main(){
	Car ur = {25, "cat"};
	Car* my = new Car{20, "sky"};
	Car* we = &ur;
	ur.tag = "hat";
	cout << we -> tag << endl;
	delete my;
	delete we;
}
