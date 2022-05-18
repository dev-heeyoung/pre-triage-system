#include "CovidPatient.h"
using namespace std;
namespace sdds {
   int nextCovidTicket = 1;

   CovidPatient::CovidPatient(): Patient(nextCovidTicket) {
	   nextCovidTicket++;
   }
   char CovidPatient::type()const {
	   return 'C';
   }
   istream& CovidPatient::csvRead(istream& istr) {
	   Patient::csvRead(istr);
	   nextCovidTicket = number() + 1;
	   istr.ignore(1000, '\n');
	   return istr;
   }
   ostream& CovidPatient::write(ostream& ostr) const {
	   if (fileIO()) Patient::csvWrite(ostr);
	   else {
		   ostr << "COVID TEST" << endl;
		   Patient::write(ostr) << endl;
	   }
	   return ostr;
   }
   istream& CovidPatient::read(istream& istr) {
	   if (fileIO()) csvRead(istr);
	   else Patient::read(istr);
	   return istr;
   }

}