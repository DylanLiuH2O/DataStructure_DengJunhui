typedef int Rank;
#define DEFAULT_CAPACITY 3

template <typename T> class Vector
{
private:
	Rank 	_size;
	int 	_capacity;
	T* 		_elem;
	
protected:
	void copyFrom(const T* A, Rank lo, Rank hi);
	void expand();
	void shrink();
	bool bubble(Rank lo, Rank hi);
	void bubbleSort(Rank lo, Rank hi);
	Rank max(Rank lo, Rank hi);
	void selectionSort(Rank lo, Rank hi);
	void mergeSort(Rank lo, Rank mid, Rank hi);
	void partition(Rank lo, Rank hi);
	void quickSort(Rank lo, Rank hi);
	void heapSort(Rank lo, Rank hi);
public:
	//general constructor
	Vector(int cap = DEFAULT_CAPACITY, int size = 0, T val = 0) 
		: _capacity(cap), _size(size)
	{
		_elem = new T[c];
		for (int i = 0; i < _size; i++) 
		{
			_elem[i] = v;
		}
	}
	//copy constructor
	Vector(const Vector<T>& V)
	{ copyFrom(V._elem, 0, V._size); }
	Vector(const Vector<T>& V, Rank lo, Rank hi)
	{ copyFrom(V._elem, lo, hi); }
	//operator overload = 
	Vector<T>& operator=(const Vector<T>&);
	//copy from c-array
	Vector(const T* A, Rank lo, Rank hi)
	{ copyFrom(A, lo, hi); }
	Vector(const T* A, n)
	{ copyFrom(A, 0, n); }

	//destructor
	~Vector()
	{ delete[] _elem; }


	
};
template <typename T>
  void
  Vector<T>::copyFrom(const T* A, Rank lo, Rank hi)
  {
	_capacity = 2 * (hi - lo);
	_size = 0;
	_elem = new T[_capacity];
	for (int i = lo; i < hi; i++)
	{
		_elem[i] = A[i];
	}
  }
template <typename T>
  Vector<T>&
  Vector<T>::operator=(const Vector<T>& V)
  { 
	if (this == &V)
		return *this;

	delete[] _elem;
	_elem = new T[V._size];
	copyFrom(V._elem, 0, V._size) 

	return *this;
  }
