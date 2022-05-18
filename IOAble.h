#include <iostream>
#ifndef SDDS_IOABLE_H
#define SDDS_IOABLE_H

namespace sdds {
	class IOAble {
	public:
		virtual ~IOAble() {};
		virtual std::ostream& csvWrite(std::ostream& ostr)const = 0;
		virtual std::istream& csvRead(std::istream& istr) = 0;
		virtual std::ostream& write(std::ostream& ostr)const = 0;
		virtual std::istream& read(std::istream& istr) = 0;
	};
	std::ostream& operator<<(std::ostream& ostr, IOAble& I);
	std::istream& operator>>(std::istream& istr, IOAble& I);
}


#endif