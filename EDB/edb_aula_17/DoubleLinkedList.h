#ifndef DOUBLE_LINKED_LIST_H
#define DOUBLE_LINKED_LIST_H
#include <iostream>

template<typename Item>
struct Node
{
    Node();
    Item info;
    
    Node<Item> *next;
    Node<Item> *prev;
};

template<typename Item>
class DoubleLinkedList
{
private:
    Node<Item>* head_;
    Node<Item>* last_;

public:
    DoubleLinkedList();

    void push_back(Item item);
    void push_front(Item item);
    void insert(Item item, size_t posititon);
    bool empty();

    void pop_back();
    void pop_front();
    void remove(size_t posititon);

    Item& front();
    Item& back();
    size_t size();
    Node<Item>* search(Item i);
    void invert();
    void traverse(void(*callback)(Item&));
    void traverseReverse(void (*callback)(Item&));

}; 
#endif // !DOUBLE_LINKED_LIST_H


template<typename Item>
Node<Item>::Node(){}

template<typename Item>
DoubleLinkedList<Item>::DoubleLinkedList(){}

template<typename Item>
void DoubleLinkedList<Item>::push_back(Item item){
    Node<Item> *new_node      = new Node<Item>();
    new_node->info = item;

    if (head_==nullptr&&last_==nullptr){
        head_ = new_node;
        last_ = new_node;
        return;
    }
    
    last_->next    = new_node;
    new_node->prev = last_;
    last_ = new_node;

}

template<typename Item>
void DoubleLinkedList<Item>::push_front(Item item){
    Node<Item> *new_node = new Node<Item>();
    new_node->info = item;
    
    if (head_==nullptr&&last_==nullptr){
        head_ = new_node;
        last_ = new_node;
        return;
    }

    head_->prev    = new_node;
    new_node->next = head_;
    head_          = new_node;
    

}

template<typename Item>
void DoubleLinkedList<Item>::insert(Item item, size_t position){
    Node<Item> *current       = head_;
    Node<Item> *previous      = nullptr;
    Node<Item> *new_node      = new Node<Item>();
               new_node->info = item;
    size_t     length         = size();

    if (position==0){
        push_front(item);
        return;
    }
    
    if (position == length)
    {
        push_back(item);
        return;
    }

    while (current!=nullptr)
    {
        
            previous->next = new_node;
            new_node->prev = previous;
            new_node->next = current;
            current->prev = new_node;
            
    }
}

template<typename Item>
bool DoubleLinkedList<Item>::empty(){
    return head_ == nullptr && last_ == nullptr;
}

template<typename Item>
void DoubleLinkedList<Item>::pop_back(){
    Node<Item> *tmp = last_;
    last_ = last_->prev;
    last_->next = nullptr;
    delete tmp;

}

template<typename Item>
void DoubleLinkedList<Item>::pop_front(){
    Node<Item> *tmp = head_;
    head_ = head_->next;
    head_->prev = nullptr;
    delete tmp;

}

template<typename Item>
void DoubleLinkedList<Item>::remove(size_t position){
    Node<Item> *current       = head_;
    Node<Item> *previous      = nullptr;
    size_t     length         = size();
    for (size_t i = 0; i < length; ++i){
        if (i==position){
            Node<Item> *tmp = nullptr;
            tmp = current->next;
            tmp->prev = previous;
            previous->next = tmp;
            delete current;

            return;
        }
        previous = current;
        current = current->next;
    }
}

template<typename Item>
Item& DoubleLinkedList<Item>::front(){
     return head_->info;
}

template<typename Item>
Item& DoubleLinkedList<Item>::back(){
    return last_->info;
}

template<typename Item>
size_t DoubleLinkedList<Item>::size(){
    Node<Item> *current = head_;
    size_t qtty = 0;

    while(current!=nullptr){
        Node<Item> *tmp = current->next;
        current = tmp;
        qtty++;
    }
    return qtty;
}

template<typename Item>
Node<Item>* DoubleLinkedList<Item>::search(Item i){
    Node<Item>* current = head_;
    while (current!=nullptr&&current->info!=i)
    {
        if (current==nullptr)
        {
            return nullptr;
        }
        
        Node<Item> *tmp    = current->next;
             current = tmp;
    }
    return current;
}

template<typename Item>
void DoubleLinkedList<Item>::invert(){
    Node<Item> *current = head_;
    Node<Item> *tmp = nullptr;
    while (current!=nullptr)
    {
        tmp           = current->next;
        current->next = current->prev;
        current->prev = tmp;
        current       = current->prev;
    }
    
    tmp = last_;
    last_ = head_;
    head_ = tmp;
}

template<typename Item>
void DoubleLinkedList<Item>::traverse(void(*callback)(Item&)){
    Node<Item> *current = head_;

    while (current!=nullptr)
    {
        callback(current->info);
        current  = current->next;
    }
    
}

template<typename Item>
void DoubleLinkedList<Item>::traverseReverse(void (*callback)(Item&)){
    Node<Item> *current = last_;

    while (current!=nullptr)
    {
        callback(current->info);
        current  = current->prev;
    }
}