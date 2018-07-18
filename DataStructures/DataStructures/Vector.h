#ifndef VECTOR_H
#define VECTOR_H

#include <memory>
#include <algorithm>
#include <iostream>

template<class T> class Vector {
public:
	typedef std::size_t size_type;
	typedef T* iterator;
	typedef const T* const_iterator;
	typedef T value_type;

private:
	iterator m_begin;
	iterator m_end;
	iterator m_memoryEnd;
	std::allocator<T> alloc;

	void uncreate();
	void grow();

public:
	//constructors
	Vector();
	Vector(const Vector<T>& vec);
	Vector(Vector<T> &&vec) noexcept;
	Vector(std::initializer_list<T> ls);
	explicit Vector(const size_type& n, const T& elem = T());
	Vector(iterator begin, iterator end);

	// overloaded operators
	Vector<T>& operator=(const Vector<T>& rhs);
	Vector<T>& operator=(Vector<T> &&rhs) noexcept;

	T& operator[](const size_type& index);
	const T& operator[](const size_type& index) const;

	Vector<T>& operator+=(const Vector<T>& rhs);

	// member functions
	bool empty() const;
	size_type size() const;
	size_type reserved() const;

	iterator begin();
	iterator end();

	const_iterator begin() const;
	const_iterator end() const;

	const_iterator cbegin();
	const_iterator cend();

	void push_back(const T& elem);
	
	//destructor
	~Vector();
	};

// private functions

template<class T> inline void Vector<T>::uncreate() {
	if (m_begin) {
		// destory elements in reverse
		iterator iter = m_end;
		while (iter != m_begin)
			alloc.destroy(--iter);

		// deallocate vector's memory
		alloc.deallocate(m_begin, m_memoryEnd - m_begin);
		}
	// reset pointers
	m_memoryEnd = m_end = m_begin = nullptr;
	}

template<class T> inline void Vector<T>::grow() {
	// set allocated memory size to 1 if vector was previously empty or twice the current size
	const Vector<T>::size_type newAllocMemorySize = std::max(2 * (m_memoryEnd - m_begin), std::ptrdiff_t(1));
	// copy the elements into newly allocated memory
	iterator newBegin = alloc.allocate(newAllocMemorySize);
	iterator newEnd = std::uninitialized_copy(m_begin, m_end, newBegin); 
	// unallocate the old memory
	uncreate();
	// set members to point to the new memory
	m_begin = newBegin;
	m_end = newEnd;
	m_memoryEnd = m_begin + newAllocMemorySize;
	}

// constructors

template<class T> Vector<T>::Vector() : m_begin(nullptr), m_end(nullptr), m_memoryEnd(nullptr) {}

template<class T> Vector<T>::Vector(const Vector<T>& vec) {
	m_begin = alloc.allocate(vec.m_end - vec.m_begin);
	m_memoryEnd = m_end = std::uninitialized_copy(vec.m_begin, vec.m_end, m_begin);
	}

template<class T> Vector<T>::Vector(Vector<T>&& vec) noexcept {
	// steal the members from vec
	m_begin = vec.m_begin;
	m_end = vec.m_end;
	m_memoryEnd = vec.m_memoryEnd;
	// leave vec in a state where the destructor can be called
	vec.m_begin = vec.m_end = vec.m_memoryEnd = nullptr;
	}

template<class T> Vector<T>::Vector(std::initializer_list<T> ls) {
	m_begin = alloc.allocate(ls.size());
	m_memoryEnd = m_end = std::uninitialized_copy(ls.begin(), ls.end(), m_begin);
	}

template<class T> Vector<T>::Vector(const size_type& n, const T& elem) {
	m_begin = alloc.allocate(n);
	m_memoryEnd = m_end = m_begin + n;
	std::uninitialized_fill(m_begin, m_end, elem);
	}

template<class T> Vector<T>::Vector(iterator begin, iterator end) {
	m_begin = alloc.allocate(end - begin);
	m_memoryEnd = m_end = std::uninitialized_copy(begin, end, m_begin);
	}

// overloaded operators

template<class T> Vector<T>& Vector<T>::operator=(const Vector<T>& rhs) {
	if (this != &rhs) {
		uncreate();

		m_begin = alloc.allocate(rhs.m_end - rhs.m_begin);
		m_memoryEnd = m_end = std::uninitialized_copy(rhs.m_begin, rhs.m_end, m_begin);
		}
	return *this;
	}

template<class T> Vector<T>& Vector<T>::operator=(Vector<T> &&rhs) noexcept {
	if (this != &rhs) {
		// steal members from vector rhs
		m_begin = rhs.m_begin;
		m_end = rhs.m_end;
		m_memoryEnd = rhs.m_memoryEnd;
		// leave rhs in a state where the destructor can be called
		rhs.m_memoryEnd = rhs.m_end = rhs.m_begin = nullptr;
		}
	return *this;
	}

template<class T> T& Vector<T>::operator[](const size_type& index) {
	return m_begin[index];
	}

template<class T> const T& Vector<T>::operator[](const size_type& index) const {
	return m_begin[index];
	}

template<class T> Vector<T>& Vector<T>::operator+=(const Vector<T>& rhs) {
	for (Vector<T>::const_iterator iter = rhs.m_begin; iter != rhs.m_end; ++iter)
		push_back(*iter);

	return *this;
	}

// plus operator defined as non-member function

template<class T> Vector<T> operator+(const Vector<T>& lhs, const Vector<T>& rhs) {
	Vector<T> newVec = lhs;
	newVec += rhs;
	return newVec;
	}

// member functions

template<class T> bool Vector<T>::empty() const {
	return m_begin == m_end;
	}

template<class T> typename Vector<T>::size_type Vector<T>::size() const {
	return m_end - m_begin;
	}

template<class T> typename Vector<T>::size_type Vector<T>::reserved() const {
	return m_memoryEnd - m_end;
	}

template<class T> typename Vector<T>::iterator Vector<T>::begin() {
	return m_begin;
	}

template<class T> typename Vector<T>::iterator Vector<T>::end() {
	return m_end;
	}

template<class T> typename Vector<T>::const_iterator Vector<T>::begin() const {
	return m_begin;
	}

template<class T> typename Vector<T>::const_iterator Vector<T>::end() const {
	return m_end;
	}

template<class T> typename Vector<T>::const_iterator Vector<T>::cbegin() {
	return m_begin;
	}

template<class T> typename Vector<T>::const_iterator Vector<T>::cend() {
	return m_end;
	}

template<class T> void Vector<T>::push_back(const T& elem) {
	if (m_memoryEnd == m_end)
		grow();

	alloc.construct(m_end++, elem);
	}

template<class T> Vector<T>::~Vector() {
	uncreate();
	}

#endif // !VECTOR_H