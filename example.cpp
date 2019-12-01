#include <iostream>
#include <string>
#include "sum.h"

using namespace std; 

int main() {
	string x = "1234", y = "1234";
	Operation *t = new Operation(x, y);
	string r1 = t->subtract();
	cout << "r1 " << r1 << endl;
	string r2 = t->add();
	cout << "r2 " << r2 << endl;
	return 0;
}
