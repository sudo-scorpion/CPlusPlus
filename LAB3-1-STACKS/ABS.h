#pragma once
#include <iostream>
using namespace std;

template <typename T>
class ABS {
private:
    int _capacity; // maximum capacity of the array
    int _currentSize; // current size of the array
    int resizeCounter; // keep tracks how many times array get resized
    float _scale_factor;
    T *arrayStack;
public:
    // Default constructor
    ABS();
    // Parameterized constructor
    ABS(int capacity);
    // Copy Constructor
    ABS(const ABS& d);
    // Assignment operator
    ABS &operator=(const ABS &d);
    // Destructor
    ~ABS();
    // this function adds element on top of the stack and grow the array if needed
    void push(T data);
    // this function removes the item at the top of the stack and resizes if needed
    T pop();
    // this function returns the item at the top of the stack
    T peek ();
    // this function return current size of the array
    unsigned int getSize();
    // this function returns maximum capacity of the array
    unsigned int getMaxCapacity();
    // this function returns the stack array
    T* getData();
    // this function is responsible to resize the array whenever needed
    void resizeArray(int scaleFactor);
    // this function returns of how many resizes happened
    unsigned int getResizes();
};


    template <typename T>
    ABS<T>::ABS(){
        _capacity = 1;
    _currentSize = 0;
    _scale_factor = 2.0f;
    arrayStack = new T[_capacity];
    }

template <typename T>
ABS<T>::ABS(int capacity){
    _capacity = capacity;
    _currentSize = 0;
    _scale_factor = 2.0f;
    arrayStack = new T[_capacity];
}

    template <typename T>
    ABS<T>::ABS(const ABS& d){
        _capacity = d._capacity;
        _currentSize = d._currentSize;
        arrayStack = new T[_capacity];
        for (int i = 0; i < _currentSize; ++i) {
            arrayStack[i] = d.arrayStack[i];
        }

    }

    template <typename T>
    ABS<T> &ABS<T>::operator=(const ABS &d){
        if (this != &d){
            _capacity = d._capacity;
            _currentSize = d._currentSize;
            arrayStack = new T[_capacity];
            for (int i = 0; i < _currentSize; ++i) {
                arrayStack[i] = d.arrayStack[i];
        }
            }
        return *this;
    }

    template <typename T>
    ABS<T>::~ABS(){
        delete [] arrayStack;
    }

    template <typename T>
    void ABS<T>::push(T data){
        if (_capacity == _currentSize) {
            _capacity = _scale_factor * _capacity;
            resizeArray(_capacity);
        }
        arrayStack[_currentSize] = data;
        _currentSize++;
    }

    template <typename T>
    T ABS<T>::pop(){
        if (_currentSize == 0)
            throw runtime_error("An error has occurred! Stack array is empty!");
        T itemPop =  arrayStack[_currentSize - 1];
        _currentSize--;
            if (((float)_currentSize / _capacity) < 1.0f / _scale_factor) {
                _capacity = _capacity / _scale_factor;
                resizeArray(_capacity);
            }
        return itemPop;
    }

    template <typename T>
    T ABS<T>::peek (){
        if (_currentSize == 0)
            throw runtime_error("An error has occurred! Stack array is empty!");
        return arrayStack[_currentSize - 1];
    }

    template <typename T>
    unsigned int ABS<T>::getSize(){
        return _currentSize;
    }

    template <typename T>
    unsigned int ABS<T>::getMaxCapacity(){
        return _capacity;
    }

    template <typename T>
     T* ABS<T>::getData(){
         return arrayStack;
    }

template<typename T>
void ABS<T>::resizeArray(int scaleFactor) {
        T *tempArray = new T[scaleFactor];
        for (int i = 0; i < _currentSize; ++i) {
            tempArray[i] = arrayStack[i];
        }
        delete [] arrayStack;
        arrayStack = tempArray;
        resizeCounter++;
    }

template<typename T>
unsigned int ABS<T>::getResizes() {
    return resizeCounter;
}

