#include <iostream>
#include "IOAble.h"

using namespace std;
namespace sdds {
	ostream& operator<<(ostream& ostr, IOAble& I) {
		return I.write(ostr);
	}

	istream& operator>>(istream& istr, IOAble& I) {
		return I.read(istr);
	}
	
}
