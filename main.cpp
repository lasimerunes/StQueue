#include <iostream>
#include "StackVector.hpp"
#include "QueueList.hpp"

int main() {

    StackVector<int> arr(3);
    arr.push(12);
    arr.push(21);
    arr.push(3);
    std::cout << arr.pop() << " " << arr.pop() << " " << arr.pop() << "\n";

}
