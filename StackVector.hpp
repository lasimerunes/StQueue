#pragma once
#include <iostream>
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
class StackVector final : public Stack<T> {
public:
    // Конструкторы
    StackVector();
    explicit StackVector(const std::size_t &size);
    // Копирование
    StackVector(const StackVector & other);
    StackVector & operator=(const StackVector & other);
    // Перемещение
    StackVector(StackVector && other) noexcept;
    StackVector & operator=(StackVector && other) noexcept;
    // Деструктор
    ~StackVector() override;


    // МЕТОДЫ
    void push(const T& e) override;
    T pop() override;
    bool isEmpty() override;

    void swap(const T& other);
    void out(bool r = false) const;

private:
    std::size_t size_;              // На сколько элементов создан массив
    std::size_t top_;               // Количество значащих элементов / Индекс ЗА последним элементом
    T*  data_;     // Сам массив
};

// Класс исключений
class StackUnderflow final : public std::exception{
public:
    StackUnderflow() : reason_("Stack Underflow") {}
    [[nodiscard]] const char* what() const noexcept override { return reason_; }
private:
    const char * reason_; // ! const
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
StackVector<T>::StackVector(const std::size_t &size) : size_(size), top_(0), data_(new T[size_]) {}
// Копирование
template<class T>
StackVector<T>::StackVector(const StackVector &other) {
    // TODO: вот это вот все надо
    size_ = other.size_;
    top_ = other.top_;
    data_ = new T[size_];
    for (std::size_t i = 0; i < top_; ++i) {
        data_[i] = other.data_[i];
    }
}
// Оператор копирующего присваивания
template<class T>
StackVector<T> &StackVector<T>::operator=(const StackVector &other) {
    if (this != &other) {
        StackVector<T> tmp(other);
        delete[] data_;
        swap(tmp);
    }
    return *this;
}
// Перемещение
template<class T>
StackVector<T>::StackVector(StackVector &&other) noexcept {
    size_ = other.size_;
    top_ = other.top_;
    data_ = other.data_;
    other.data_ = nullptr;
}
// Оператор перемещающего присваивания
template<class T>
StackVector<T> &StackVector<T>::operator=(StackVector &&other) noexcept {
    if (this != &other) {
        delete[] data_;
        StackVector<T> tmp(other);
        swap(tmp); 
    }
    return *this;
}
// Деструктор
template<class T>
StackVector<T>::~StackVector() {
    delete[] data_;
}




// МЕТОДЫ
template<class T>
void StackVector<T>::push(const T &e) {
    if (top_ == size_) {
        // Увеличиваем размер
        size_ *= 2;
        // Создаем и заполняем временный массив из нынешнего
        T* tmp {new T[size_]};
        for (std::size_t i = 0; i < top_; ++i) {
            tmp[i] = data_[i];
        }
        // Удаляем нынешний и заменяем его на новый
        delete[] data_;
        data_ = tmp;
    }
    data_[top_] = e;
    ++top_;
}

template<class T>
T StackVector<T>::pop() {
    if (top_) {
        // Запоминаем последний элемент, удаляем его из массива и возвращаем
        T tmp = data_[top_-1];
        data_[top_-1] = T();
        --top_;
        return tmp;
    }
    throw StackUnderflow();
}

template<class T>
bool StackVector<T>::isEmpty() {
    // TODO: хз, если это вообще правильно, но пока что пофиг
    return top_ == 0;
}

template<class T>
void StackVector<T>::swap(const T& other) {
    std::swap(size_, other.size_);
    std::swap(top_, other.top_);
    std::swap(data_, other.data_);
}

template<class T>
void StackVector<T>::out(const bool r) const {
    if (!top_){
        std::cout << "Empty";
    }
    else if (r){
        std::cout << "Out: ";
        for(std::size_t i = top_; i > 0; --i){
            std::cout << i-1 << ": " << data_[i-1] << " ";
        }
    }
    else {
        std::cout << "Out: ";
        for (std::size_t i = 0; i < top_; ++i) {
            std::cout << i << ": " << data_[i] << " ";
        }
    }
    std::cout << "\n";
}

