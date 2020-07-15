// Please do not run in strict mode
// % clang++ recursion.cpp -o rec.exe 
// clang++ version: 10.0.0
#include <iostream>
int main(int argc, char** argv) {
    std::cout << argc << " ";
    main(argc+1,nullptr); 
}