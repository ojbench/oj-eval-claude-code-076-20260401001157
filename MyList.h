#ifndef MYLIST_H
#define MYLIST_H

#include <stdexcept>

template<typename ValueType>
class MyList {
private:
    struct Node {
        ValueType value;
        Node* prev;
        Node* next;

        Node(const ValueType& val) : value(val), prev(nullptr), next(nullptr) {}
    };

    Node* head;
    Node* tail;
    int list_size;

public:
    MyList() : head(nullptr), tail(nullptr), list_size(0) {}

    MyList(MyList&& obj) noexcept {
        head = obj.head;
        tail = obj.tail;
        list_size = obj.list_size;
        obj.head = nullptr;
        obj.tail = nullptr;
        obj.list_size = 0;
    }

    MyList(const MyList& obj) : head(nullptr), tail(nullptr), list_size(0) {
        Node* current = obj.head;
        while (current != nullptr) {
            push_back(current->value);
            current = current->next;
        }
    }

    ~MyList() {
        clear();
    }

    MyList& operator=(const MyList& obj) {
        if (this != &obj) {
            clear();
            Node* current = obj.head;
            while (current != nullptr) {
                push_back(current->value);
                current = current->next;
            }
        }
        return *this;
    }

    MyList& operator=(MyList&& obj) noexcept {
        if (this != &obj) {
            clear();
            head = obj.head;
            tail = obj.tail;
            list_size = obj.list_size;
            obj.head = nullptr;
            obj.tail = nullptr;
            obj.list_size = 0;
        }
        return *this;
    }

    void push_back(const ValueType& value) {
        Node* new_node = new Node(value);
        if (tail == nullptr) {
            head = tail = new_node;
        } else {
            tail->next = new_node;
            new_node->prev = tail;
            tail = new_node;
        }
        list_size++;
    }

    void pop_back() {
        if (tail == nullptr) return;

        Node* to_delete = tail;
        if (head == tail) {
            head = tail = nullptr;
        } else {
            tail = tail->prev;
            tail->next = nullptr;
        }
        delete to_delete;
        list_size--;
    }

    void push_front(const ValueType& value) {
        Node* new_node = new Node(value);
        if (head == nullptr) {
            head = tail = new_node;
        } else {
            new_node->next = head;
            head->prev = new_node;
            head = new_node;
        }
        list_size++;
    }

    void pop_front() {
        if (head == nullptr) return;

        Node* to_delete = head;
        if (head == tail) {
            head = tail = nullptr;
        } else {
            head = head->next;
            head->prev = nullptr;
        }
        delete to_delete;
        list_size--;
    }

    ValueType& front() const {
        return head->value;
    }

    ValueType& back() const {
        return tail->value;
    }

    void insert(int index, const ValueType& value) {
        if (index == 0) {
            push_front(value);
            return;
        }
        if (index >= list_size) {
            push_back(value);
            return;
        }

        Node* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }

        Node* new_node = new Node(value);
        new_node->prev = current->prev;
        new_node->next = current;
        current->prev->next = new_node;
        current->prev = new_node;
        list_size++;
    }

    void erase(int index) {
        if (index < 0 || index >= list_size) return;

        if (index == 0) {
            pop_front();
            return;
        }
        if (index == list_size - 1) {
            pop_back();
            return;
        }

        Node* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }

        current->prev->next = current->next;
        current->next->prev = current->prev;
        delete current;
        list_size--;
    }

    int size() const {
        return list_size;
    }

    bool empty() const {
        return list_size == 0;
    }

    void clear() {
        while (head != nullptr) {
            Node* to_delete = head;
            head = head->next;
            delete to_delete;
        }
        tail = nullptr;
        list_size = 0;
    }

    void link(const MyList& obj) {
        Node* current = obj.head;
        while (current != nullptr) {
            push_back(current->value);
            current = current->next;
        }
    }

    MyList cut(int index) {
        MyList result;
        if (index <= 0 || index >= list_size) {
            return result;
        }

        Node* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }

        // current is now at position index
        result.head = current;
        result.tail = tail;
        result.list_size = list_size - index;

        // Update this list
        tail = current->prev;
        if (tail != nullptr) {
            tail->next = nullptr;
        }
        if (current->prev != nullptr) {
            current->prev = nullptr;
        }

        list_size = index;

        return result;
    }
};

#endif // MYLIST_H
