//
// Created by ThomasBI on 01/03/2018.
//

#ifndef DREAMINENGINE_ARRAY2_H
#define DREAMINENGINE_ARRAY2_H

#include <initializer_list>

template<typename T>
class Array2
{
public:
	typedef T* iterator;
	typedef const T* const_iterator;
private:
	iterator m_array;
	unsigned long m_total_size;
	unsigned long m_actual_size;
public:
	Array2()
		: m_array(nullptr)
		, m_actual_size(0)
		, m_total_size(0) {}
	Array2(const unsigned long &size);
	Array2(std::initializer_list<T> il);
	Array2(const Array2&);
	~Array2() { delete[] m_array; }

	void add(iterator obj);
	bool remove(unsigned int index);

	iterator begin() const { return m_array; }
	iterator end() const { return m_array != nullptr ? &m_array[m_actual_size] : nullptr; }
	iterator getArray() const { return m_array; }
	unsigned long getTotalSize() const { return m_total_size; };
	unsigned long getActualSize() const { return m_actual_size; };
	//unsigned long size() const { return m_actual_size; }

	Array2& operator=(const Array2&);
	T& operator[](const unsigned long&);
};

//CONSTRUCTOR

template<typename T>
Array2<T>::Array2(const unsigned long &size) : m_total_size(size), m_actual_size(0) {
	if (size > 0) {
		m_array = new T[size];
		m_array = nullptr;
	}
}

template <typename T>
Array2<T>::Array2(std::initializer_list<T> il)
{
	unsigned long size = il.size();
	m_array = new T[size];
	iterator pointer = getArray();
	for (const T& i : il) {
		*pointer++ = i;
		m_actual_size++;
		m_total_size++;
	}
}

template<typename T>
Array2<T>::Array2(const Array2<T> &rhs) : m_actual_size(rhs.m_actual_size), m_total_size(rhs.m_total_size)
{
	//m_array = new T[rhs.getTotalSize()];
	m_array = new T(*(rhs.m_array));
	//iterator pointer = getArray();
	//for (const_iterator i = rhs.getArray(); i != rhs.end(); i++)
	//    *pointer++ = *i;
}

//METHODES

template<typename T>
void Array2<T>::add(iterator obj) {
	if (m_actual_size >= m_total_size) {
		iterator temp[m_total_size + 3];
		for (unsigned long i = 0; i < m_actual_size; i++)
			temp[i] = m_array[i];
		m_array = temp;
		m_array[m_actual_size] = obj;
		m_actual_size++;
		m_total_size += 3;
	}
	else {
		m_array[m_actual_size] = obj;
		m_actual_size++;
	}
}

template<typename T>
bool Array2<T>::remove(unsigned int index) {
	if (index < m_actual_size && m_actual_size != 0) {
		m_actual_size--;
		m_array[index] = m_array[m_actual_size];
		return true;
	}
	return false;
}

//OPERATORS

template<typename T>
Array2<T>& Array2<T>::operator=(const Array2<T> &rhs)
{
	if (this != &rhs)
	{
		delete[] m_array;
		m_array = new T[rhs.getTotalSize()];
		iterator pointer = getArray();
		for (const_iterator i = rhs.begin(); i != rhs.end(); i++)
			*pointer++ = *i;
	}
	return *this;
}

template<typename T>
T& Array2<T>::operator[](const unsigned long &index)
{
	if (index < 1 || index > getTotalSize()) {
		// Add some error-handling here.
	}
	return m_array[index];
}

#endif //DREAMINENGINE_ARRAY2_H
