#ifndef _VECTOR_H
#define _VECTOR_H

#include <cstdlib>  //rand()
#include <ctime>

typedef int Rank;
#define DEFAULT_CAPACITY 10

template <typename T>
class Vector
{
protected:
    Rank _size;
    int  _capacity;
    T*   _elem;

    void copyFrom(const T* A, Rank lo, Rank hi);
    void expand();
    void shrink();
    bool bubble(Rank lo, Rank hi);
    void bubblSort(Rank lo, Rank hi);
    Rank max(Rank lo, Rank hi);
    void selectionSort(Rank lo, Rank hi);
    void merge(Rank lo, Rank mid, Rank hi);
	void mergeSort(Rank lo, Rank hi);
	Rank partition(Rank lo, Rank hi);
	void quickSort(Rank lo, Rank hi);
	void heapSort(Rank lo, Rank hi);

public:
    Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0) {
		_elem = new T[_capacity = c];
		for (_size = 0; _size < s; _elem[_size++] = v);
	}
	Vector(const T* A, Rank lo, Rank hi) { 
		copyFrom(A, lo, hi);
	}
	Vector(const T* A, int n) {
		copyFrom(A, 0, n);
	}
	Vector(const Vector<T>& V, Rank lo, Rank hi) {
		copyFrom(V._elem, lo, hi);
	}
	//copy ctor
	Vector(const Vector<T>& V) {
		copyFrom(V._elem, 0, V._size);
	}

	~Vector() {
		delete[] _elem;
	}

    //read-only interface
    Rank size() const {
        return _size;
    }
    bool empty() cosnt {
        return !_size; 
    }
    int disordered() const;
    Rank find(const T& e) const {
        find(e, 0, _size);
    }
    Rank find(const T& e, Rank lo, Rank hi) const;
    Rank search(const T& e) const {
        return search(e, 0, _size); 
    }
    Rank search(const T& e, Rank lo, Rank hi) const;

    //writeable interface
    T& operator[](Rank r) const;
    Vector<T>&
    operator=(const Vector<T>& V);
    T remove(Rank r);
    int remove(Rank lo, Rank hi);
    Rank insert(const T& e) {
        insert(_size, e);
    }
    Rank insert(Rank r, const T& e);
    void sort() {
        sort(0, _size);
    }
    void sort(Rank lo, Rank hi);
    void unsort() {
        unsort(0, _size);
    }
    void unsort(Rank lo, Rank hi);
    int dedupicate();
    int uniquify();

    void traverse((void*)visit(T&));
    template <typename T>
    void traverse(VST&);
};
template <typename T>
void Vector<T>::copyFrom(const T* A, Rank lo, Rank hi) {
    _elem = new T[_capacity = 2 * (hi - lo)];
    _size = 0;
    while (lo < hi) {
        _elem[_size++] = A[lo++];
    }
}
template <typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& A) {
    if (_elem) {
        delete[] _elem;
    }
    copyFrom(A._elem, 0, _size);
    return *this;
}
template <typename T>
void Vector<T>::expand() {
    if (_size < _capacity) {
        return;
    }
    if (_capacity < DEFAULT_CAPACITY) {
        _capacity = DEFAULT_CAPACITY;
    }
    T* _oldElem = _elem;
    _capacity <<= 1;
    _elem = new T[_capacity];
    for (int i = 0; i < _size; i++) {
        _elem[i] = _oldElem[i];
    }
    delete[] _oldElem;
}
template <typename T>
void Vector<T>::shrink() {
    if (_capacity < (DEFAULT_CAPACITY << 1)) {
        return;
    }
    if ((_size << 2) > _capacity) {
        return;
    }
    _capacity >>= 1;
    T* _oldElem = _elem;
    _elem = new T[_capacity];
    for (int i = 0; i < _size; i++) {
        _elem[i] = _oldElem[i];
    }
    delete[] _oldElem;
}
template <typename T>
T& Vector<T>::operator[](Rank r) const {
    return _elem[r];
}
template <typename T>
void Vector<T>::unsort(Rank lo, Rank hi) {
    std::rand(std::time(nullptr));
    T* V = _elem + lo;
    for (Rank i = hi - lo; i > 0; i--) {
        swap(V[rand() % i], V[i - 1]);
    }
}
template <typename T>
Rank Vector<T>::find(const T& e, Rank lo, Rank hi) const {
    while ((lo < hi--) && (e != _elem[hi])) {
    }
    return hi;
}
template <typename T>
Rank Vector<T>::insert(Rank r, const T& e) {
    expand();
    for (int i = _size; i > r; i--) {
        _elem[i] = _elem[i - 1];
    }
    _elem[r] = e;
    ++_size;
    return r;
}
template <typename T>
Rank Vector<T>::remove(Rank lo, Rank hi) {
    if (lo == hi) {
        return 0;
    }
    while (hi < _size) {
        _elem[lo++] = _elem[hi++];
    }
    _size = lo;
    shrink();

    return hi - lo;
}
template <typename T>
int Vector<T>::dedupicate() {
    int oldsize = _size;
    Rank i = 1;
    while (i < _size) {
        find(_elem[i], 0, i) < 0 ? i++ : remove(i);
    }
    shrink();
    return oldSize - _size;
}

#endif
