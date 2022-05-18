#ifndef SDDS_TRIAGEPATIENT_H
#define SDDS_TRIAGEPATIENT_H
#include "Patient.h"
namespace sdds {
	class TriagePatient : public Patient {
		char* m_symtoms;
	public:
		TriagePatient();
		~TriagePatient();
		char type()const;
		std::ostream& csvWrite(std::ostream& ostr) const;
		std::istream& csvRead(std::istream& istr);
		std::ostream& write(std::ostream& ostr) const;
		std::istream& read(std::istream& istr);
	};

	extern int nextTriageTicket;
}
#endif // !SDDS_TRIAGEPATIENT_H


