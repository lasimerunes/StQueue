#pragma once
#include <iostream>
#include <exception>


/*      -------------------------------
 *      |                             |
 *      |   Объявления/Declarations   |
 *      |                             |
 *      -------------------------------
 */

template <class T>
class Queue
{
public:
    virtual ~Queue () = default;
    virtual void enQueue(const T& e) = 0; // Добавление элемента в очередь
    virtual T deQueue() = 0; // Удаление элемента из очереди
    virtual bool isEmpty() = 0; // Проверка очереди на пустоту
};

template<class T>
class QueueList final : public Queue<T>{
public:
    // Конструктор
    QueueList();
    // Копирование
    QueueList(const QueueList & other);
    QueueList & operator=(const QueueList & other);
    // Перемещение
    QueueList(QueueList && other) noexcept ;
    QueueList & operator=(QueueList && other) noexcept;
    // Деструктор
    ~QueueList() override;

// Методы
    void enQueue(const T & e) override;
    T deQueue() override;
    bool isEmpty() override;

    void swap(QueueList & other) noexcept;
    void out();

private:
    struct Node{
        T data_;
        Node * next_;
        explicit Node(T val, Node *ptr = nullptr) : data_(val), next_(ptr) {}
    };
    Node * head_;
};

// Класс исключений
class QueueUnderflow final : public std::exception {
public:
    QueueUnderflow() : reason_("Queue Underflow") {};
    [[nodiscard]] const char* what() const noexcept override { return reason_.c_str(); }
private:
    const std::string& reason_; // ! const
};


/*      -------------------------------
 *      |                             |
 *      |   Определения/Definitions   |
 *      |                             |
 *      -------------------------------
 */


// Конструктор
template<class T>
QueueList<T>::QueueList(): head_(nullptr){}
// Копирование
template<class T>
QueueList<T>::QueueList(const QueueList<T> &other) {
    head_ = nullptr;
    Node * current = other.head_;
    // Просто заполняем пустой список
    while(current){
        QueueList<T>::enQueue(current->data_);
        current = current->next_;
    }
}
// Оператор копирующего присваивания
template<class T>
QueueList<T> & QueueList<T>::operator=(const QueueList &other) {
    if (this != &other){
        QueueList tmp(other);
        swap(tmp);
    }
    return *this;
}
// Перемещение
template<class T>
QueueList<T>::QueueList(QueueList<T> &&other) noexcept :
    head_(other.head_) {
        other.head_ = nullptr;
}
// Оператор перемещающего присваивания
template<class T>
QueueList<T> &QueueList<T>::operator=(QueueList<T> &&other)  noexcept {
    if (this != &other){
        QueueList tmp(std::move(other));
        swap(tmp);
    }
    return *this;
}
// Деструктор
template<class T>
QueueList<T>::~QueueList() {
    // Пока существует следующий
    while(head_){
        // Запоминаем следующий элемент, который станет головой
        Node * tmp = head_->next_;
        // Удаляем текущую голову и меняем ее на новую
        delete head_;
        head_ = tmp;
    }
}




// МЕТОДЫ

template<class T>
void QueueList<T>::enQueue(const T &e) {
    // Если очередь пуста
    if (!head_){
        head_ = new Node(e);
    }
    // Если новый элемент должен стоять вначале
    else if (e < head_->data_) {
        Node * node = new Node(e, head_);
        head_ = node;
    }
    else {
        Node * current = head_;
        while (current->next_) {
            if (e < current->next_->data_) {
                // Создаем новый узел
                Node * node = new Node(e);
                // Ссылаем его на следующий от текущего
                node->next_ = current->next_;
                // Теперь текущий должен ссылаться на новый
                current->next_ = node;
                return;
            }
            current = current->next_;
        }
        // Если элемент должен стоять в конце списка
        if (current->data_ != e){
            current->next_ = new Node(e);
        }
    }
}

template<class T>
T QueueList<T>::deQueue() {
    // Если очередь пуста
    if (!head_) {
        throw QueueUnderflow();
    }
    // Запоминаем данные в голове
    T tmp_data = head_->data_;
    // Запоминаем следующий элемент, который станет головой
    Node * new_head = head_->next_;
    // Удаляем текущую голову и меняем ее на новую
    delete head_;
    head_ = new_head;
    return tmp_data;
}

template<class T>
bool QueueList<T>::isEmpty() {
    return !head_;
}

template<class T>
void QueueList<T>::swap(QueueList<T> &other) noexcept {
    std::swap(head_, other.head_);
}

template<class T>
void QueueList<T>::out() {
    if (isEmpty()) {
        std::cout << "Empty\n";
    }
    else {
        std::cout << "Out: ";
        Node * current = head_;
        while (current){
            std::cout << current->data_ << " ";
            current = current->next_;
        }
        std::cout << "\n";
    }
}