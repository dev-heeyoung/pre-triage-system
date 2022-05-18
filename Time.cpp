#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include "Time.h"
#include "utils.h"

using namespace std;
namespace sdds {

	Time& Time::setToNow() {
		m_min = getTime();
		return *this;
	}

	Time::Time(unsigned int min) {
		if (min >= 0) m_min = min;
		else setEmpty();
	}

	Time& Time::setEmpty() {
		m_min = -1;
		return *this;
	}

	bool Time::isValid()const {
		return m_min >= 0;
	}

	ostream& Time::write(ostream& ostr)const {
		ostr.width(2);
		ostr.fill('0');
		ostr << m_min / 60;
		ostr << ":";
		ostr.width(2);
		ostr.fill('0');
		ostr << m_min % 60;
		return ostr;
	}

	istream& Time::read(istream& istr) {
		char del{};
		int hh = -1, mm = -1;
		
		istr >> hh;
		istr >> del;
		istr >> mm;
	
		if (!(del == ':') || hh < 0 || mm < 0) istr.setstate(ios::failbit);
		else m_min = mm + hh * +60;
		
		return istr;
	}

	Time& Time::operator-= (const Time& D) {
		int i = 0;
		if (isValid() && D.isValid()) {
			if (m_min < D.m_min) {
				while (m_min + 60 * 24 * i < D.m_min) i++;
				m_min += (60 * 24 * i);
			}
			m_min -= D.m_min;
		}
		return *this;
	}

	Time Time::operator-(const Time& D)const {
		int i = 0;
		Time newTime;
		if (isValid() && D.isValid()) {
			if (m_min < D.m_min) {
				while (m_min + 60 * 24 * i < D.m_min) i++;
			}
			newTime = (m_min + 60 * 24 * i) - D.m_min;
		}
		return newTime;
	}

	Time& Time::operator+=(const Time& D) {
		if (isValid() && D.isValid()) m_min += D.m_min;
		return *this;
	}

	Time Time::operator+(const Time& D)const {
		Time newTime;
		if (isValid() && D.isValid()) newTime = m_min + D.m_min;
		return newTime;
	}

	Time& Time::operator=(unsigned int val) {
		if (val >= 0) m_min = val;
		return *this;
	}

	Time& Time::operator *= (unsigned int val) {
		if (val > 0 && isValid()) m_min *= val;
		return *this;
	}

	Time Time::operator *(unsigned int val)const {
		Time newTime;
		if (val > 0 && isValid()) newTime = m_min * val;
		return newTime;
	}

	Time& Time::operator /= (unsigned int val) {
		if (val > 0 && isValid()) m_min /= val;
		return *this;
	}

	Time Time::operator /(unsigned int val)const {
		Time newTime;
		if (val > 0 && isValid()) newTime = m_min / val;
		return newTime;
	}

	Time::operator int()const {
		return (int)m_min;
	}
	
	Time::operator unsigned int()const {
		return m_min;
	}

	ostream& operator<<(ostream& ostr, const Time& D) {
		return D.write(ostr);
	}

	istream& operator>>(istream& istr, Time& D) {
		return D.read(istr);
	}

}