#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include "Patient.h"
#include "utils.h"

using namespace std;
namespace sdds {
	Patient::Patient(int ticketNum, bool flag) {
		m_name = nullptr;
		m_ohip = 0;
		m_fileFlag = flag;
		m_ticket.setNumber(ticketNum);
	}

	Patient::~Patient() {
		delete[] m_name;
	}

	bool Patient::fileIO()const {
		return m_fileFlag;
	}

	Patient& Patient::fileIO(bool flag) {
		m_fileFlag = flag;
		return *this;
	}

	bool Patient::operator==(char ch)const {
		return type() == ch;
	}

	bool Patient::operator==(const Patient& I)const {
		return type() == I.type();
	}

	void Patient::setArrivalTime() {
		m_ticket.resetTime();
	}

	Patient::operator Time()const {
		return (Time)m_ticket;
	}
	
	int Patient::number()const {
		return m_ticket.number();
	}

	std::ostream& Patient::csvWrite(std::ostream& ostr) const {
		ostr << type() << "," << m_name << "," << m_ohip << ",";
		return m_ticket.csvWrite(ostr);
	}

	istream& Patient::csvRead(istream& istr) {
		char* str;
		str = getcstr(nullptr, istr, ',');
		delete[] m_name;
		m_name = new char[strlen(str) + 1];
		strcpy(m_name, str);
		m_name[strlen(str)] = '\0';
		delete[] str;

		istr >> m_ohip;
		istr.ignore(1, ',');
	
		return m_ticket.csvRead(istr);
	}

	ostream& Patient::write(ostream& ostr) const {
		char substrChar[26];
		m_ticket.write(ostr);
		cout << endl;
		strncpy(substrChar, m_name, 25);
		substrChar[25] = '\0';
		return ostr << substrChar << ", OHIP: " << m_ohip;
	}

	istream& Patient::read(istream& istr) {
		char* str;
		int tempOhip;
		cout << "Name: ";
		str = getcstr(nullptr, istr, '\n');
		delete[] m_name;
		m_name = new char[strlen(str) + 1];
		strcpy(m_name, str);
		delete[] str;
		cout << "OHIP: ";
		tempOhip = getInt(100000000, 999999999, nullptr, "Invalid OHIP Number, ");
		if (tempOhip >= 100000000 && tempOhip <= 999999999) m_ohip = tempOhip;
 
		return istr;
	}

}
