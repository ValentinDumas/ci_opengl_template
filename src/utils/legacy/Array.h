//
// Created by ThomasBI on 30/01/2018.
//

#ifndef DREAMINENGINE_ARRAY_H
#define DREAMINENGINE_ARRAY_H

#include <stdexcept>
#include <iostream>
#include <malloc.h>

template <class T>
class Array {

private:
	T * m_array;
	unsigned int m_tot_size;
	unsigned int m_actual_size;

public:
	Array(unsigned int size);
	Array(std::initializer_list<T> t);
	Array(Array<T> const& paste);

	bool add(T var);
	const T& get(unsigned int index);
	bool remove(unsigned int index);
	void kill();

	unsigned int getActualSize() const;
	unsigned int getTotalSize() const;
	T* getArray() const;

	T& operator[](unsigned int index);
	Array<T>& operator=(Array<T> const& paste);
	Array<T>& operator=(std::initializer_list<T> const& paste);

	~Array();

};

//CONSTRUCTOR

template <class T>
Array<T>::Array(unsigned int size) : m_tot_size(size), m_actual_size(0) {
	m_array = (T*)malloc(size * sizeof(T));
}

template <class T>
Array<T>::Array(std::initializer_list<T> t) : m_tot_size(t.size()), m_actual_size(0) {
	m_array = (T*)malloc(m_tot_size * sizeof(T));
	for (auto n : t) {
		add(n);
	}
}

template <class T>
Array<T>::Array(Array<T> const &paste) : m_tot_size(paste.m_tot_size), m_actual_size(paste.m_actual_size) {
	m_array = new T(*(paste.m_array));
}

//METHODES PUBLIC

template <class T>
const T & Array<T>::get(unsigned int index) {
	if (index >= m_actual_size || index < 0)
		throw std::out_of_range("Index out of range");
	return m_array[index];
}

template <class T>
bool Array<T>::remove(unsigned int index) {
	if (index < m_actual_size && m_actual_size != 0) {
		m_actual_size--;
		m_array[index] = m_array[m_actual_size];

		return true;
	}
	return false;
}

template <class T>
bool Array<T>::add(T obj) {
	if (m_actual_size >= m_tot_size) {
		T *temp;
		temp = (T*)realloc(m_array, 5 * sizeof(T));
		m_array = temp;
		m_array[m_actual_size] = obj;
		m_actual_size++;
		m_tot_size += 5;
		return false;
	}
	else {
		m_array[m_actual_size] = obj;
		m_actual_size++;
		return true;
	}
}

template <class T>
void Array<T>::kill() {
	free(m_array);
}

//ACCESSOR

template <class T>
unsigned int Array<T>::getActualSize() const { return m_actual_size; }

template <class T>
unsigned int Array<T>::getTotalSize() const { return m_tot_size; }

template <class T>
T* Array<T>::getArray() const { return m_array; }


//OPERATOR

template <class T>
T& Array<T>::operator[](unsigned int index) { return m_array[index]; }

template <class T>
Array<T>& Array<T>::operator=(Array<T> const& paste) {
	if (this != &paste) {
		m_tot_size = paste.m_tot_size;
		m_actual_size = paste.m_actual_size;

		free(m_array);


	}
	return *this;
}

template <class T>
Array<T>& Array<T>::operator=(std::initializer_list<T> const& paste) {
	free(m_array);
	m_tot_size = paste.size();
	//m_actual_size = paste.size();
	m_array = (T*)malloc(m_tot_size * sizeof(T));
	for (auto n : paste) {
		add(n);
	}
	return *this;
}

//DESTRUCTOR
template <class T>
Array<T>::~Array() {
	free(m_array);
}

#endif //DREAMINENGINE_ARRAY_H