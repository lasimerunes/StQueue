#include <iostream>
#include "StackVector.hpp"
#include "QueueList.hpp"

int main() {

    std::cout << "----->StackVector:\n";
    StackVector<int> arr(3);
    arr.push(12);
    arr.push(21);
    arr.push(3);
    arr.out();
    std::cout << arr.pop() << " " << arr.pop() << " " << arr.pop() << "\n";
    arr.out();
    try {
        arr.pop();
    }
    catch(StackUnderflow& e) {
        std::cout << e.what() << "\n";
    }


    std::cout << "\n----->QueueList:\n";
    QueueList<int> queue;
    queue.enQueue(12);
    queue.enQueue(3);
    queue.enQueue(41);
    queue.out();
    std::cout << queue.deQueue() << "\n";
    queue.out();
    std::cout << (queue.isEmpty() ? ("Empty\n") : ("Not empty\n"));
    std::cout << queue.deQueue() << ", " << queue.deQueue() << "\n";
    std::cout << (queue.isEmpty() ? ("Empty\n") : ("Not empty\n"));

    try {
        queue.deQueue();
    }
    catch(QueueUnderflow& e) {
        std::cout << e.what() << "\n";
    }

}
