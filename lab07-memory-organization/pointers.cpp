#include<iostream>

int main(){
   void* code = (void*)&main;
   void* stack = &code;
   void* heap = new long;

   std::cout << "code:\t" << code << '\n';
   std::cout << "stack:\t" << stack << '\n';
   std::cout << "heap:\t" << heap << '\n';
   return 0;
}
