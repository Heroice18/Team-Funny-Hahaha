#include <iostream>

using namespace std;

int main(){
   void* code = (void*)&main;
   void* stack = &code;
   void* heap = new long;

   cout << "code address: " << code << "\n";
   cout << "stack address: " << stack << "\n";
   cout << "heap address: " << heap << "\n";
   
   return 0;
}
