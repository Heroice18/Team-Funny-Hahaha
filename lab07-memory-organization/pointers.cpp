#include<iostream>

int main(){
   void* code = main;
   void* stack = &code;
   void* heam = new long;
   return 0;
}
