#include <iostream>
#include "StackVector.hpp"
#include "QueueList.hpp"

int main() {

    StackVector<int> arr(3);
    arr.push(12);
    arr.push(21);
    arr.push(3);
    arr.out(true);
    StackVector<int> arr2(6);
    std::cout << arr.pop() << " " << arr.pop()  << "\n";
    arr.push(31);
    arr.out(true);


}
