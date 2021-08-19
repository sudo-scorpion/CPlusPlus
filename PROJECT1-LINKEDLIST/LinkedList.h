#pragma once
#include <iostream>
#include <vector>
using namespace std;

template<typename T>
class LinkedList {
public:
    struct Node {
        T data;
        Node *next;
        Node *prev;
    };
private:
    Node *head;
    Node *tail;
    unsigned int nodeCount;

    // Function prototypes

public:
    // Default constructor
    LinkedList();

    // Destructor
    ~LinkedList();

    //  This node function returns new node
    Node *GetNewNode(const T &data);

    // Setting value to default
    void setDefault();

    // This function print node's value in forward
    void PrintForward() const;

    // This function print node's value in reverse
    void PrintReverse() const;

    // This function inserts node at the beginning of the list
    void AddHead(const T &data);

    // This function inserts node at the end of the list
    void AddTail(const T &data);

    // This function adds node at the beginning while maintaining original order
    void AddNodesHead(const T *data, unsigned int count);

    // This function adds node at the end while maintaining original order
    void AddNodesTail(const T *data, unsigned int count);

    // This functions returns how many elements added or deleted from the list
    unsigned int NodeCount() const;

    // This function deallocates memory
    void Clear();

    // This function returns head of the list
    Node *Head();

    // This function returns head just for view only
    const Node *Head() const;

    // This function returns tail pointer
    Node *Tail();

    // This function returns tail pointer for only read
    const Node *Tail() const;

    // Returns pointer to the index only for read
    const Node *GetNode(unsigned int index) const;

    // Returns pointer to the index
    Node *GetNode(unsigned int index);

    // Operator assignment constant
    const T &operator[](unsigned int index) const;

    // operator assignment
    T &operator[](unsigned int index);

    // equality assignment
    bool operator==(const LinkedList<T> &rhs) const;

    // copy constructor
    LinkedList(const LinkedList<T> &list);

    // copy assignment
    LinkedList<T> &operator=(const LinkedList<T> &rhs);

    // This function finds first value only for read
    const Node *Find(const T &data) const;

    // This function finds first value
    Node *Find(const T &data);

    //store values of all matched values
    void FindAll(vector<Node *> &outData, const T &value) const;

    // This functions insert element before
    void InsertBefore(Node *node, const T &data);

    // This functions insert element after
    void InsertAfter(Node *node, const T &data);

    // This functions insert element at the given index
    void InsertAt(const T &data, unsigned int index);

    // This helper function for inserting element
    void Switch(Node *node, const T &data, unsigned int token);

    // This functions return if head element is removed
    bool RemoveHead();

    // This functions return if tail element is removed
    bool RemoveTail();

    // This function removes element from the list
    unsigned int Remove(const T &data);

    // This function removes element at the given index from the list
    bool RemoveAt(unsigned int index);

    // This recursive print function which prints in forward
    void PrintForwardRecursive(const Node *node) const;

    // This recursive print function which prints in reverse without reversing it
    void PrintReverseRecursive(const Node *node) const;

    // This functions sets head and tail to nullptr and decrement the number of nodes
    void setDecrement();
};

// function implementation begins here

template<typename T>
LinkedList<T>::LinkedList() {
    head = nullptr;
    tail = nullptr;
    nodeCount = 0;
}

template<typename T>
void LinkedList<T>::AddHead(const T &data) {
    // invoking GetNewNode() to get the new node was passed
    Node *tempNode = GetNewNode(data);
    // checking validity of the head and tail pointer to add node at the head
    if (head == nullptr && tail == nullptr) {
        head = tempNode;
        tail = tempNode;
        head->next = nullptr;
        head->prev = nullptr;
    } else {
        head->prev = tempNode;
        tempNode->next = head;
        head = tempNode;
    }
    nodeCount++;
}

template<typename T>
void LinkedList<T>::AddTail(const T &data) {
    Node *tempNode = GetNewNode(data);
    if (head == nullptr && tail == nullptr) {
        head = tempNode;
        tail = tempNode;
        tail->next = nullptr;
        tail->prev = nullptr;
    } else {
        tail->next = tempNode;
        tempNode->prev = tail;
        tempNode->next = nullptr;
        tail = tempNode;
    }
    nodeCount++;
}

template<typename T>
void LinkedList<T>::AddNodesHead(const T *data, unsigned int count) {
    unsigned int i = count - 1;
    while (i >= 0 && --i)
        AddHead(data[i]);
}

template<typename T>
void LinkedList<T>::AddNodesTail(const T *data, unsigned int count) {
    unsigned int i = 0;
    while (i < count && ++i)
        AddHead(data[i]);
}


template<typename T>
unsigned int LinkedList<T>::NodeCount() const {
    return nodeCount;
}

template<typename T>
void LinkedList<T>::PrintForward() const {
    Node *headNode = head;
    // Checking validity of the head pointer to print out of the list
    while (headNode != nullptr) {
        cout << headNode->data << endl;
        headNode = headNode->next;
    }
}

template<typename T>
void LinkedList<T>::PrintReverse() const {
    Node *tailNode = tail;
    while (tailNode != nullptr) {
        cout << tailNode->data << endl;
        tailNode = tailNode->prev;
    }
}

template<typename T>
typename LinkedList<T>::Node *LinkedList<T>::Head() {
    return head;
}

template<typename T>
const typename LinkedList<T>::Node *LinkedList<T>::Head() const {
    return head;
}

template<typename T>
typename LinkedList<T>::Node *LinkedList<T>::Tail() {
    return tail;
}

template<typename T>
const typename LinkedList<T>::Node *LinkedList<T>::Tail() const {
    return tail;
}

template<typename T>
const typename LinkedList<T>::Node *LinkedList<T>::GetNode(unsigned int index) const {
    Node *indexPtr = head;
    // Throw out_of_range class exception if passed index is bigger than total number nodes
    if (index >= nodeCount) {
        throw std::out_of_range("Invalid Index!");
    } else {
        for (unsigned int i = 0; i != index; ++i)
            indexPtr = indexPtr->next;
        return indexPtr;
    }
}


template<typename T>
typename LinkedList<T>::Node *LinkedList<T>::GetNode(unsigned int index) {
    Node *indexPtr = head;
    if (index >= nodeCount) {
        throw std::out_of_range("Invalid Index!");
    } else {
        for (unsigned int i = 0; i != index; ++i)
            indexPtr = indexPtr->next;
        return indexPtr;

    }
}

template<typename T>
const T &LinkedList<T>::operator[](unsigned int index) const {
    Node *indexPtr = head;
    if (index >= nodeCount) {
        throw std::out_of_range("Invalid Index!");
    }
    for (unsigned int i = 0; i != index; ++i)
        indexPtr = indexPtr->next;
    return indexPtr->data;
}

template<typename T>
T &LinkedList<T>::operator[](unsigned int index) {
    Node *indexPtr = head;
    if (index >= nodeCount) {
        throw std::out_of_range("Invalid Index!");
    }
    for (int i = 0; i != index; ++i)
        indexPtr = indexPtr->next;
    return indexPtr->data;
}

template<typename T>
LinkedList<T>::LinkedList(const LinkedList<T> &list) {
    // invoking setDefault() to set head and tail pointer to nullptr and nodeCount to 0
    setDefault();
    for (unsigned int i = 0; i < list.NodeCount(); ++i) {
        AddTail(list.operator[](i));
    }
}

template<typename T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T> &rhs) {
    Clear();
    for (unsigned int i = 0; i < rhs.NodeCount(); ++i) {
        AddTail(rhs.operator[](i));
    }
    return *this;
}

template<typename T>
LinkedList<T>::~LinkedList() {
    Clear();
}

template<typename T>
void LinkedList<T>::Clear() {
    Node *headPtr = Head();
    Node *tempNode;
    while (headPtr != nullptr) {
        tempNode = headPtr->next;
        delete headPtr;
        headPtr = tempNode;
    }
    setDefault();
}

template<typename T>
typename LinkedList<T>::Node *LinkedList<T>::Find(const T &data) {
    Node *tempHead = head;
    while (tempHead->next != nullptr) {
        if (tempHead->data == data)
            return tempHead;
        tempHead = tempHead->next;
    }
    return nullptr;
}

template<typename T>
const typename LinkedList<T>::Node *LinkedList<T>::Find(const T &data) const {
    Node *tempHead = head;
    while (tempHead->next != nullptr) {
        if (tempHead->data == data)
            return tempHead;
        tempHead = tempHead->next;
    }
    return nullptr;
}


template<typename T>
void LinkedList<T>::FindAll(vector<Node *> &outData, const T &value) const {
    Node *tempHead = head;
    for (unsigned int i = 0; i < nodeCount; ++i) {
        if (tempHead->data == value)
            outData.push_back(tempHead);
        tempHead = tempHead->next;
    }
}


template<typename T>
void LinkedList<T>::InsertBefore(LinkedList::Node *node, const T &data) {
    Switch(node, data, 1);
}

template<typename T>
void LinkedList<T>::InsertAfter(LinkedList::Node *node, const T &data) {
    Switch(node, data, 2);
}

template<typename T>
void LinkedList<T>::InsertAt(const T &data, unsigned int index) {
    if (index > nodeCount)
        throw std::out_of_range("Invalid Index!");
        // checking if given index is same as node's index is
    else if (index == nodeCount) {
        Node *tempNode = new Node();
        tempNode->data = data;
        tail->next = tempNode;
        tempNode->prev = tail;
        tempNode->next = nullptr;
        tail = tempNode;
        nodeCount++;
    } else {
        Node *tempNode = new Node();
        Node *tempHead = Head();
        tempNode->data = data;
        for (unsigned int i = 0; i != index; i++)
            tempHead = tempHead->next;
        tempNode->prev = tempHead->prev;
        tempNode->next = tempHead;
        if (tempHead->prev != nullptr)
            tempHead->prev->next = tempNode;
        else
            head = tempNode;
        tempHead->prev = tempNode;
        nodeCount++;
    }
}

template<typename T>
bool LinkedList<T>::operator==(const LinkedList<T> &rhs) const {
    if (nodeCount != rhs.nodeCount)
        return false;
    while (unsigned int i = 0 && i < nodeCount && ++i) {
        if (head->data != rhs.operator[](i)) {
            return false;
        }
    }
    return true;
}

template<typename T>
bool LinkedList<T>::RemoveHead() {
    if (head == nullptr)
        return false;
    else if (head->next == nullptr) {
        Node *tempNode = head;
        delete tempNode;
        setDecrement();
        return true;
    } else {
        Node *tempNode = head;
        head->next->prev = nullptr;
        head = head->next;
        delete tempNode;
        nodeCount--;
        return true;
    }
}

template<typename T>
bool LinkedList<T>::RemoveTail() {
    if (tail == nullptr)
        return false;
    else if (tail->prev == nullptr) {
        Node *tempNode = tail;
        delete tempNode;
        setDecrement();
        return true;
    } else {
        Node *tempNode = tail;
        tail->prev->next = nullptr;
        tail = tail->prev;
        delete tempNode;
        nodeCount--;
        return true;
    }
}

template<typename T>
unsigned int LinkedList<T>::Remove(const T &data) {
    Node *tempHead = head;
    Node* tempNext;
    unsigned int howManyObjRemoved = 0;
    while (tempHead != nullptr) {
        tempNext = tempHead->next;
        if (tempHead->data == data) {
            if (tempHead->next == nullptr)
                tempHead->prev->next = nullptr;
            else if (tempHead->prev == nullptr)
                tempHead->prev= nullptr;
            else {
                tempHead->prev->next = tempHead->next;
                tempHead->next->prev = tempHead->prev;
            }
            delete tempHead;
            howManyObjRemoved++;
        }
        tempHead = tempNext;
    }
    nodeCount = nodeCount - howManyObjRemoved;
    return howManyObjRemoved;
}

template<typename T>
bool LinkedList<T>::RemoveAt(unsigned int index) {
    Node *tempHead = head;
    if (index > nodeCount)
        return false;
    else {
        for (unsigned int i = 0; i != index; ++i)
            tempHead = tempHead->next;
        if (tempHead->next == nullptr)
            tempHead->prev->next = nullptr;
        else if (tempHead->prev == nullptr)
            tempHead->next->prev = nullptr;
        else {
            tempHead->prev->next = tempHead->next;
            tempHead->next->prev = tempHead->prev;
        }
        delete tempHead;
        nodeCount--;
        return true;
    }
}

template<typename T>
void LinkedList<T>::PrintForwardRecursive(const LinkedList::Node *node) const {
    if (node == nullptr)
        return;
    cout << node->data << endl;
    PrintForwardRecursive(node->next);

}

template<typename T>
void LinkedList<T>::PrintReverseRecursive(const LinkedList::Node *node) const {
    if (node == nullptr)
        return;
    cout << node->data << endl;
    PrintReverseRecursive(node->prev);
}

template<typename T>
void LinkedList<T>::setDefault() {
    head = nullptr;
    tail = nullptr;
    nodeCount = 0;
}

template<typename T>
void LinkedList<T>::setDecrement() {
    head = nullptr;
    tail = nullptr;
    nodeCount--;
}

template<typename T>
typename LinkedList<T>::Node *LinkedList<T>::GetNewNode(const T &data) {
    Node *tempNode = new Node();
    tempNode->data = data;
    tempNode->prev = nullptr;
    tempNode->next = nullptr;
    return tempNode;
}

template<typename T>
void LinkedList<T>::Switch(LinkedList::Node *node, const T &data, unsigned int token) {
    if (token == 1) {
        // inserting before
        Node *tempNode = new Node();
        tempNode->data = data;
        tempNode->next = node;
        tempNode->prev = node->prev;
        node->prev->next = tempNode;
        node->prev = tempNode;
        nodeCount++;
    }
        // inserting after
    else if (token == 2) {
        Node *tempNode = new Node();
        tempNode->data = data;
        tempNode->prev = node;
        tempNode->next = node->next;
        node->next->prev = tempNode;
        node->next = tempNode;
        nodeCount++;
    }
}