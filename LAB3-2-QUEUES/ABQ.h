#pragma once
#include <iostream>
using namespace std;

template <typename T>
class ABQ {
private:
    int _capacity; // maximum capacity of the array
    int _currentSize; // current size of the array
    int resizeCounter; // keep tracks how many times array get resized
    float _scale_factor;
    T *queueArray;
public:
    // Default constructor
    ABQ();
    // Parameterized constructor
    ABQ(int capacity);
    // Copy Constructor
    ABQ(const ABQ &d);
    // Assignment operator
    ABQ &operator=(const ABQ &d);
    // Destructor
    ~ABQ();
    // this function adds element  and grow the array if needed
    void enqueue(T data);
    // this function removes the item and resizes if needed
    T dequeue();
    // this function returns the item
    T peek ();
    // this function return current size of the array
    unsigned int getSize();
    // this function returns maximum capacity of the array
    unsigned int getMaxCapacity();
    // this function returns the queue array
    T* getData();
    // this function is responsible to resize the array whenever needed
    void resizeArray(int scaleFactor);
    // this function shifts element the right to the left
    void itemShifter();
    // this function returns of how many resizes happened
    unsigned int getResizes();
};


template <typename T>
ABQ<T>::ABQ(){
    _capacity = 1;
    _currentSize = 0;
    _scale_factor = 2.0f;
    queueArray = new T[_capacity];
}

template <typename T>
ABQ<T>::ABQ(int capacity){
    _capacity = capacity;
    _currentSize = 0;
    _scale_factor = 2.0f;
    queueArray = new T[_capacity];
}

template <typename T>
ABQ<T>::ABQ(const ABQ &d){
    _capacity = d._capacity;
    _currentSize = d._currentSize;
    queueArray = new T[_capacity];
    for (int i = 0; i < _currentSize; ++i) {
        queueArray[i] = d.queueArray[i];
    }

}

template <typename T>
ABQ<T> &ABQ<T>::operator=(const ABQ &d){
    if (this != &d) {
        _capacity = d._capacity;
        _currentSize = d._currentSize;
        queueArray = new T[_capacity];
        for (int i = 0; i < _currentSize; ++i) {
            queueArray[i] = d.queueArray[i];
        }
    }
    return *this;
}

template <typename T>
ABQ<T>::~ABQ(){
    delete [] queueArray;
}

template <typename T>
void ABQ<T>::enqueue(T data){
    if (_capacity == _currentSize) {
        _capacity = _scale_factor * _capacity;
        resizeArray(_capacity);
    }
    queueArray[_currentSize] = data;
    _currentSize++;
}

template <typename T>
T ABQ<T>::dequeue(){
    if (_currentSize == 0)
        throw runtime_error("An error has occurred! Queue array is empty!");
    T itemPop =  queueArray[0];
    itemShifter();
    _currentSize--;
    if (((float)_currentSize / _capacity) < 1.0f / _scale_factor) {
        _capacity = _capacity / _scale_factor;
        resizeArray(_capacity);
    }
    return itemPop;
}

template <typename T>
T ABQ<T>::peek (){
    if (_currentSize == 0)
        throw runtime_error("An error has occurred! Queue array is empty!");
    return queueArray[0];
}

template <typename T>
unsigned int ABQ<T>::getSize(){
    return _currentSize;
}

template <typename T>
unsigned int ABQ<T>::getMaxCapacity(){
    return _capacity;
}

template <typename T>
T* ABQ<T>::getData(){
    return queueArray;
}

template<typename T>
void ABQ<T>::resizeArray(int scaleFactor) {
        T *tempArray = new T[scaleFactor];
        for (int i = 0; i < _currentSize; ++i) {
            tempArray[i] = queueArray[i];
        }
        delete [] queueArray;
        queueArray = tempArray;
        resizeCounter++;
    }
template<typename T>
void ABQ<T>::itemShifter() {
    for (int i = 0; i < _currentSize ; ++i) {
        queueArray[i] = queueArray[i + 1];
    }
}

template<typename T>
unsigned int ABQ<T>::getResizes() {
    return resizeCounter;
}



