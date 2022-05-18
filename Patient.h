#ifndef SDDS_PATIENT_H_
#define SDDS_PATIENT_H_
#include "Ticket.h"
namespace sdds {
    class Patient : public IOAble {
        Ticket m_ticket;
        char* m_name;
        int m_ohip;
        bool m_fileFlag;
    public:
        Patient(int ticketNum = 0, bool flag = false);
        ~Patient();
        virtual char type()const = 0;
        bool fileIO()const;
        Patient& fileIO(bool flag);
        bool operator==(char ch)const;
        bool operator==(const Patient& I)const;
        void setArrivalTime();
        operator Time()const;
        int number()const;

        std::ostream& csvWrite(std::ostream& ostr) const;
        std::istream& csvRead(std::istream& istr);
        std::ostream& write(std::ostream& ostr) const;
        std::istream& read(std::istream& istr);
    };
}
#endif 
