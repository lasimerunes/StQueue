#pragma once
#include <iostream>
#include <memory>
#include <exception>


/*      -------------------------------
 *      |                             |
 *      |   Объявления/Declarations   |
 *      |                             |
 *      -------------------------------
 */

template<class T>
class Stack {
public:
    virtual ~Stack() = default;
    virtual void push(const T& e) = 0;  // Добавление элемента в стек
    virtual T pop() = 0;                // Удаление верхнего элемента
    virtual bool isEmpty() = 0;         // Проверка стека на пустоту
};



template<class T>
class StackVector: public Stack<T> {
public:
    // КОНСТРУКТОРЫ
    StackVector();
    explicit StackVector(const std::size_t &size);
    // Копирование
    StackVector(const StackVector & other);
    StackVector & operator=(const StackVector & other);
    // Перемещение
    StackVector(StackVector && other);
    StackVector & operator=(StackVector && other);
    // Деструктор
    ~StackVector() override;


    // МЕТОДЫ
    void push(const T& e) override;
    T pop() override;
    bool isEmpty() override;
    void out() const;



private:
    std::size_t size_;              // На сколько элементов создан массив
    std::size_t top_;               // Количество значащих элементов, индекс последнего элемента равен top_ - 1
    T* data_;     // Сам массив

};


/*      -------------------------------
 *      |                             |
 *      |   Определения/Definitions   |
 *      |                             |
 *      -------------------------------
 */

// КОНСТУКТОРЫ
template<class T>
StackVector<T>::StackVector(): size_(0), top_(0), data_(nullptr) {}
template<class T>
StackVector<T>::StackVector(const std::size_t &size) : size_(size), top_(0), data_(new T[](size_)) {}
// Копирование
template<class T>
StackVector<T>::StackVector(const StackVector &other) {
    // Насколько я понял, такой метод работы с массивами и shared_ptr работает только после C++17.
    // В C++17 и раньше надо было писать кастомный деструктор.
    size_ = other.size_;
    top_ = other.top_;
    // Здесь получается использовать идиому copy-and-swap.
    // TODO: перенос даты
}
// TODO: конструктор копирующего присваивания
// TODO: Перемещение
// Деструктор
template<class T>
StackVector<T>::~StackVector() = default;




// МЕТОДЫ
template<class T>
void StackVector<T>::push(const T &e) {
    if (top_ != size_) {
        data_[top_-1] = e;
        ++top_;
    }
    // TODO: сделать расширение массива при переполнении
}

template<class T>
T StackVector<T>::pop() {
    // TODO: чекнуть, че тут вообще, и дописать
    if (top_+1) {
        T tmp = data_[top_-1];
        data_[top_-1] = 0;
        --top_;
        return tmp;
    }
    else {
        throw std::out_of_range("Poop");
    }
}

template<class T>
bool StackVector<T>::isEmpty() {
    // TODO: хз, если это вообще правильно, но пока что пофиг
    return top_ == 0;
}

template<class T>
void StackVector<T>::out() const{
    for (std::size_t i = size_; i > 0; --i) {
        std::cout << data_[i-1] << " ";
    }
    std::cout << "\n";
}






