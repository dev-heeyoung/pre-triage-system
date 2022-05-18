#ifndef SDDS_UTILS_H_
#define SDDS_UTILS_H_
#include <iostream>
namespace sdds {
   extern bool debug; 

   int getTime();
   int getInt(const char* prompt = nullptr);
   int getInt(int min, int max, const char* prompt = nullptr, const char* errorMessage = nullptr, bool showRangeAtError = true);
   char* getcstr(const char* prompt = nullptr, std::istream& istr = std::cin, char delimiter = '\n');
   
   template <typename type>
   void removeDynamicElement(type* array[], int index, int& size) {
       delete array[index];
       for (int j = index; j < size; j++) {
           array[j] = array[j + 1];
       }
       size--;
   }
}
#endif

