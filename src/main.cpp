#include "sstd.h"
#include <iostream>

bool test1(){

    dts::array<int, 5> arr(2);
    dts::array<int, 5> arr2 = arr;

    for(uint n_elem = 0; n_elem < 5; n_elem++){
        std::cout << arr2[n_elem] << " ";
    }
    std::cout << "\n";

    dts::array<int, 5> arr3(-2);
    arr3 = arr2;
    arr3[0] = 1;

    for(uint n_elem = 0; n_elem < 5; n_elem++){
        std::cout << arr3[n_elem] << " ";
    }
    std::cout << "\n";

    return true;
}
//----------------------------------------------------------------------------------------//

bool test2(){

    dts::vector<double>* v1 = new dts::vector<double>;

    v1->push_back(3.14);
    v1->push_back(1./3.14);

    dts::vector<double> v2 = *v1;

    while(!v2.empty()){
        std::cout << v2.pop_back() << " ";
    }

    std::cout << "\n";

    delete v1;
    return true;
}
//----------------------------------------------------------------------------------------//

bool test3(){
    dts::vector<int> vec(10);

    for(uint n_elem = 0; n_elem < 12; n_elem++){
        vec.push_back(n_elem + 1);
    }

    dts::vector<int> vec2 = vec;

    for(uint n_elem = 0; n_elem < vec2.size(); n_elem++){
        std::cout << vec2.pop_back() << " ";
    }
    std::cout << "\n";

    return true;
}
//----------------------------------------------------------------------------------------//

int main(){
    
    test2();
    return 0;
}
