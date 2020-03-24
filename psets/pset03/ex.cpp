
#include <iostream>
using namespace std;


long long powerN(int base, int n) {
	if(n <= 1) return base;
	return powerN(base, n - 1) * base;
}

int main(){
	cout << powerN(2,5) << endl;
	cout << powerN(3,1) << endl;
	cout << powerN(3,2) << endl;
	cout << powerN(3,3) << endl;
	cout << powerN(10,2) << endl;
	cout << powerN(10,3) << endl;

	return 0;
}
