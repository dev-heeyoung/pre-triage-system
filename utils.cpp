#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <cstring>
#include "utils.h"
#include "Time.h"
using namespace std;
namespace sdds {
   bool debug = false; 
   int getTime() {  
      int mins = -1;
      if (debug) {
         Time t(0);
         cout << "Enter current time: ";
         do {
            cin.clear();
            cin >> t;   

            if (!cin) {
               cout << "Invlid time, try agian (HH:MM): ";
               cin.clear();
            }
            else mins = int(t);
            cin.ignore(1000, '\n');
         } while (mins < 0);
      }
      else {
         time_t t = time(NULL);
         tm lt = *localtime(&t);
         mins = lt.tm_hour * 60 + lt.tm_min;
      }
      return mins;
   }

   int getInt(const char* prompt) {
       int number;
       char ch;
       bool valid = false;

       if (prompt) cout << prompt;
       
       do {
           cin >> number;
           ch = cin.get();
                    
           if (cin.fail() || ch != '\n') {
               if (cin.fail()) 
                   cout << "Bad integer value, try again: ";
               else 
                   cout << "Enter only an integer, try again: ";
               
               cin.clear();
               cin.ignore(10000, '\n');
           }
           else valid = true;
       } while (valid == false);

       return number;
   }

   int getInt(int min, int max, const char* prompt, const char* errorMessage, bool showRangeAtError) {
       int number;
       number = getInt(prompt);
       do {    
           if (number < min || number > max){
               if (errorMessage != nullptr) cout << errorMessage;
               if(showRangeAtError) cout << "[" << min << " <= value <= " << max << "]: ";
           number = getInt();
           }
       } while (number < min || number > max);
       return number;
   }

   char* getcstr(const char* prompt, std::istream& istr, char delimiter) {
       char* cstring = nullptr;
       char str[10000];
       int limit = 10000;

       if (prompt)
           cout << prompt;

       istr.getline(str, limit, delimiter);
       cstring = new char[strlen(str) + 1];
       strncpy(cstring, str, strlen(str));
       cstring[strlen(str)] = '\0';

       return cstring;
   }



}