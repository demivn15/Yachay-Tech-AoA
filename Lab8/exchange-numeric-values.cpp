#include <iostream>

int main(){
    int u = 10, v = 25;
    std::cout << "Before swap: u = " << u << ", v = " << v << std::endl;
    u = u ^ v;
    v = u ^ v;
    u = u ^ v;
    std::cout << "After swap:  u = " << u << ", v = " << v << std::endl;
    return 0;
}
