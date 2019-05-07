#include <iostream>

int main() {
   int rubies, sapphires, emeralds;
   int rubsap, sapem, emrub;

   std::cin >> rubies >> sapphires >> emeralds;
   std::cin >> rubsap >> sapem >> emrub;

   int ex_rub = 0;
   int ex_sap = 0;
   int ex_em = 0;

   while (rubies >= rubsap || sapphires >= sapem || emeralds >= emrub) {
       while (rubies >= rubsap) {
           rubies -= rubsap;
           ex_sap++;
           sapphires++;
       }
       while (sapphires >= sapem) {
           sapphires -= sapem;
           ex_em++;
           emeralds++;
       }
       while (emeralds >= emrub) {
           emeralds -= emrub;
           ex_rub++;
           rubies++;
       }
   }

   std::cout << (ex_rub + ex_sap + ex_em) << "\n";
}