#ifndef SDDS_MENU_H
#define SDDS_MENU_H

namespace sdds {
    class Menu {
        char* m_text; 
        int m_noOfSel;  
        void display()const;
        Menu& setEmpty();
    public:
        Menu();
        Menu(const char* MenuContent, int NoOfSelections);
        Menu(const Menu& I);
        virtual ~Menu();
        int& operator>>(int& Selection);
    };
}

#endif