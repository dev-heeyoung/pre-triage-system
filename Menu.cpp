#define _CRT_SECURE_NO_WARNINGS
#include <ostream>
#include <cstring>
#include "Menu.h"
#include "utils.h"
using namespace std;
namespace sdds {

	Menu::Menu() {
		setEmpty();
	}

	Menu::Menu(const char* MenuContent, int NoOfSelections) {
		if (MenuContent != nullptr && NoOfSelections > 0) {
			m_noOfSel = NoOfSelections;
			m_text = new char[strlen(MenuContent) + 1];
			strcpy(m_text, MenuContent);
		}
		else setEmpty();
	}

	Menu::~Menu() {
		delete[] m_text;
	}

	Menu::Menu(const Menu& I){
		m_text = new char[strlen(I.m_text) + 1];
		strcpy(m_text, I.m_text);
		m_noOfSel = I.m_noOfSel;
	}

	Menu& Menu::setEmpty() {
		m_noOfSel = 0;
		m_text = nullptr;
		return *this;
	}

	void Menu::display()const {
		cout << m_text << endl;
		cout << "0- Exit" << endl;
	}

	int& Menu::operator>>(int& Selection) {
		display();
		cout << "> ";
		Selection = getInt(0, m_noOfSel, nullptr, "Invalid option ");
		return Selection;
	}
}
