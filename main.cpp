#include <iostream>
#include <map>
#include "forward_list.h"
forward_list f(forward_list arg){
    auto result = arg;
    for(auto e: arg){
        result.push_back(e);
    }
    return result;
}
int main() {
    int arr[] = {3, 5, 7};
    forward_list list(std::begin(arr), std::end(arr));
    std::cout << *list.begin() << ".\n";
    forward_list fl3(20000);

    fl3.remove(++fl3.begin());
    auto l2 = f(list);

    for(auto element:l2){
        std::cout << element << ", ";
    }
}
