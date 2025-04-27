// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_

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

    void push(const T& item) {
        T* newItem = new T*(item);
        if (isEmpty()) {
            head = tail = newItem;
        }

        T* temp = head;
        while (temp != nullptr && temp.prior >= newItem.prior ) {
            temp = temp->nextCh;
        }
        
        if (temp == nullptr) {
            tail->nextCh = newItem;
            newItem->prev = tail;
            tail = newItem;
        }else if (temp == head) {
            newItem->nextCh = head;
            head->prev = newItem;
            head = newItem;
        }else {
            newItem->nextCh = temp;
            newItem->prev = temp.prev;
            newItem->prev->nextCh = newItem;
            temp->prev = newItem;
        }
    }
    

    T pop() {
        if (head==tail){
            head=tail=nullptr;
        }
        if (isEmpty()) {
            throw std::string("List is empty!");
        }

        T* temp = head;
        head = head->nextCh;
        head->prev = nullptr;

        delete temp;
    }

    bool isEmpty() const {
        return head == nullptr;
    }
};

struct SYM {
  char ch;
  int prior;
  SYM* nextCh = nullptr;
  SYM* prev = nulptr;
};

#endif  // INCLUDE_TPQUEUE_H_
