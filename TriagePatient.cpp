#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include "TriagePatient.h"
#include "utils.h"
using namespace std;

namespace sdds {
   int nextTriageTicket = 1;
   
   TriagePatient::TriagePatient(): Patient(nextTriageTicket) {
	   m_symtoms = nullptr;
	   nextTriageTicket++;
   }
   TriagePatient::~TriagePatient() {
	   delete[] m_symtoms;
   }
   char TriagePatient::type()const {
	   return 'T';
   }
   ostream& TriagePatient::csvWrite(ostream& ostr) const {
	   Patient::csvWrite(ostr);
	   ostr << ',' << m_symtoms;
	   return ostr;
   }
   istream& TriagePatient::csvRead(istream& istr) {
	   char* str;
	   delete[] m_symtoms;
	   Patient::csvRead(istr);
	   istr.ignore(1, ',');
	   str = getcstr(nullptr, istr, '\n');
	   m_symtoms = new char[strlen(str) + 1];
	   strcpy(m_symtoms, str);
	   delete[] str;
	   nextTriageTicket = number() + 1;
	   return istr;
   }
   ostream& TriagePatient::write(ostream& ostr) const {
	   if (fileIO()) csvWrite(ostr);
	   else {
		   ostr << "TRIAGE" << endl;
		   Patient::write(ostr) << endl;
		   ostr << "Symptoms: " << m_symtoms << endl;
	   }
	   return ostr;
   }
   istream& TriagePatient::read(istream& istr) {
	   char* str;
	   if (fileIO()) csvRead(istr);
	   else {
		   delete[] m_symtoms;
		   Patient::read(istr);
		   cout << "Symptoms: ";
		   str = getcstr(nullptr, istr, '\n');
		   m_symtoms = new char[strlen(str) + 1];
		   strcpy(m_symtoms, str);
		   delete[] str;
	   }
	   return istr;
   }

}