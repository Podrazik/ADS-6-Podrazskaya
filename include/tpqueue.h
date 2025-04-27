// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_
#include <utility>

template<typename T>
class TPQueue {

  T* head;
  T* tail;

 public:
    TPQueue() : head(nullptr), tail(nullptr) {}
    ~TPQueue() {
        while (head != nullptr) {
            T* temp = head;
            head = head->nextCh;
            delete temp;
        }
    }

    void push(T&& item) {
        T* newItem = new T*(std::move(item));
        if (isEmpty()) {
            head = tail = newItem;
        }
     
        T* temp = head;
        while (temp != nullptr && temp->prior >= newItem->prior) {
            temp = temp->nextCh;
        }
        
        if (temp == nullptr) {
            tail->nextCh = newItem;
            newItem->prevCh = tail;
            tail = newItem;
        } else if (temp == head) {
            newItem->nextCh = head;
            head->prevCh = newItem;
            head = newItem;
        } else {
            newItem->nextCh = temp;
            newItem->prevCh = temp->prevCh;
            newItem->prevCh->nextCh = newItem;
            temp->prevCh = newItem;
        }
    }
    
    T pop() {
        if (head == tail) {
            head = tail = nullptr;
        }
        if (isEmpty()) {
            throw ("List is empty!");
        }

        T* temp = head;
        head = head->nextCh;
        head->prevCh = nullptr;

        return temp;
    }

    bool isEmpty() const {
        return head == nullptr;
    }
};

struct SYM {
  char ch;
  int prior;
  SYM* nextCh = nullptr;
  SYM* prevCh = nullptr;
};

#endif  // INCLUDE_TPQUEUE_H_
