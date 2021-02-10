#ifndef _MYVECTOR_H
#define _MYVECTOR_H

#include <iostream>

using namespace std;

#define DEFAULT_CAPACITY 3
typedef int Index;

template <typename T>
class myVector {
protected:
    T*  _elem;
    int _size;
    int _capacity;

    //only for init new obj
    void copyElem(const T* elem, Index lo, Index hi) {
        _capacity = 2 * (hi - lo);
        _elem = new T[_capacity];
        _size = hi - lo;
        for (int i = 0; i < _size; i++) {
            _elem[i] = elem[i];
        }
    }

public:
    myVector(int sz = 0, T val = 0) : _size(sz) {
        _size = sz;
        _capacity = (_size == 0) ? DEFAULT_CAPACITY : 2 * _size;
        _elem = new T[_capacity];
        for (int i = 0; i < _size; i++) {
            _elem[i] = val;
        }
    }
    myVector(const myVector<T>& V) {
        copyElem(V._elem, 0, V._size);
    }
    myVector<T>&
    operator=(const myVector<T>& V) {
        delete[] _elem;
        copyElem(V._elem, 0, V._size);

        return *this;
    }


    T& operator[](Index i) const {
        return _elem[i];
    }
    int size() const {
        return _size;
    }
};
template <typename T>
ostream& operator<<(ostream& os, const myVector<T>& V) {

    cout << "[";
    for (int i = 0; i < V.size(); i++) {
        cout << V[i];
        if (i < V.size()-1)
            cout << ",";
    }
    cout << "]";
    
    return os;
}

#endif