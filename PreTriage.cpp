#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstring>
#include "PreTriage.h"
using namespace std;

namespace sdds {
	PreTriage::PreTriage(const char* dataFilename): m_appMenu("General Hospital Pre-Triage Application\n1- Register\n2- Admit", 2), m_pMenu("Select Type of Admittance:\n1- Covid Test\n2- Triage", 2){
		m_dataFilename = new char[strlen(dataFilename) + 1];
		strcpy(m_dataFilename, dataFilename);
		m_averCovidWait = 15;
		m_averTriageWait = 5;
		load();
	}
	PreTriage::~PreTriage() {
		if (m_dataFilename) {
			ofstream fileout(m_dataFilename);
			m_averCovidWait.write(fileout) << ",";
			m_averTriageWait.write(fileout) << endl;

			cout << "Saving Average Wait Times," << endl;
			cout << "   COVID Test: ";
			m_averCovidWait.write(cout) << endl;
			cout << "   Triage: ";
			m_averTriageWait.write(cout) << endl;
			cout << "Saving m_lineup..." << endl;

			for (int i = 0; i < m_lineupSize; i++) {
				m_lineup[i]->csvWrite(fileout) << endl;
			}

			for (int i = 0; i < m_lineupSize; i++) {
				cout << i + 1 << "- ";
				m_lineup[i]->csvWrite(cout) << endl;
			}
			
			for (int i = 0; i < m_lineupSize; i++) {
				delete m_lineup[i];
			}

			delete[] m_dataFilename;

			cout << "done!" << endl;
		}
	}
	const Time PreTriage::getWaitTime(const Patient& p)const {
		int count = 0;
		Time temp{};
		for (int i=0; i < m_lineupSize; i++) {
			if (*m_lineup[i] == p) count++;
			temp = count;
		}
		return temp;
	}
	void PreTriage::setAverageWaitTime(const Patient& p) {
		Time temp;
		if (p.type() == 'C') {
			m_averCovidWait = ((temp.setToNow() - p) + (m_averCovidWait * ((unsigned int)p.number() - 1))) / (unsigned int)p.number();
		}
		else {
			m_averTriageWait = ((temp.setToNow() - p) + (m_averTriageWait * ((unsigned int)p.number()- 1))) / (unsigned int)p.number();
		}
	}
	void PreTriage::removePatientFromLineup(int index) {
		removeDynamicElement(m_lineup, index, m_lineupSize);
	}

	int PreTriage::indexOfFirstInLine(char type) const {
		int index = -1;
		for (int i = 0; index <0 && i < m_lineupSize; i++) {
			if (m_lineup[i]->type() == type) index = i;
		}
		return index;
	}
	void PreTriage::load() {

		cout << "Loading data..." << endl;
		ifstream filein(m_dataFilename);

		if (!filein.fail()) {
			filein >> m_averCovidWait;
			filein.ignore(100, ',');
			filein >> m_averTriageWait;
			filein.ignore(100, '\n');
		}

		Patient* array[maxNoOfPatients]{};
 		for (int i = 0; !filein.fail() && i < maxNoOfPatients; i++) {
			char ch{};
			filein >> ch;
			filein.ignore(1, ',');
			if (ch == 'C') array[i] = new CovidPatient;
			else if (ch == 'T') array[i] = new TriagePatient;

			if (array[i]) {
				array[i]->fileIO(true);
				array[i]->read(filein);
				array[i]->fileIO(false);
				m_lineup[i] = array[i];

				m_lineupSize++;
			}
		}

		if (!filein.fail()) cout << "Warning: number of records exceeded " << maxNoOfPatients << endl;
		else if (m_lineup[0] == nullptr) cout << "No data or bad data file!" << endl;
		
		if (m_lineupSize > 0) cout << m_lineupSize << " Records imported..." << endl;

		cout << endl;
	}

	void PreTriage::reg() {
		int selection;
		if (m_lineupSize == maxNoOfPatients) cout << "Line up full!" << endl;
		else {
			m_pMenu >> selection;
			switch (selection)
			{
			case 0:
				break;
			case 1:
				m_lineup[m_lineupSize] = new CovidPatient;
				break;
			case 2:
				m_lineup[m_lineupSize] = new TriagePatient;
				break;
			default:
				break;
			}
			m_lineup[m_lineupSize]->setArrivalTime();

			cout << "Please enter patient information: " << endl;
			m_lineup[m_lineupSize]->fileIO(false);
			m_lineup[m_lineupSize]->read(cin);
			cout << endl;
			cout << "******************************************" << endl;
			m_lineup[m_lineupSize]->write(cout);
			cout << "Estimated Wait Time: ";
			cout << getWaitTime(*m_lineup[m_lineupSize]) << endl;
			cout << "******************************************" << endl << endl;

			m_lineupSize++;
		}
	}
	void PreTriage::admit() {
		int selection, index = -1;
		if (m_lineupSize == maxNoOfPatients) cout << "Line up full!" << endl;
		else {
			m_pMenu >> selection;
			switch (selection)
			{
			case 0:
				break;
			case 1:
				index = indexOfFirstInLine('C');
				break;
			case 2:
				index = indexOfFirstInLine('T');
				break;
			default:
				break;
			}

			if (index >= 0) {
				cout << endl;
				cout << "******************************************" << endl;
				m_lineup[index]->fileIO(false);
				cout << "Calling for ";
				m_lineup[index]->write(cout);
				cout << "******************************************" << endl << endl;
				setAverageWaitTime(*m_lineup[index]);
				removePatientFromLineup(index);
			}
		}
		
	}
	void PreTriage::run(void) {
		int selection;
		
		do {
			m_appMenu >> selection;

			switch (selection)
			{
			case 0:
				break;
			case 1:
				reg();
				break;
			case 2:
				admit();
				break;
			default:
				break;
			}
		} while (selection);
	}
}