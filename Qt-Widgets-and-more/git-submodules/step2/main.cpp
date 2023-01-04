#include <iostream>
#include <kdalgorithms.h>
#include <vector>

int main() {
    std::vector<int> vec{3,1,2};
    kdalgorithms::sort(vec);
  
    for (auto i: vec) 
        std::cout << i << ",";
    std::cout << std::endl;
}
