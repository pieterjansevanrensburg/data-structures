#ifndef SINGLY_LINKED_LIST_H
#define SINGLY_LINKED_LIST_H

#include <algorithm>

// forward declaration
template<class T> class SinglyLinkedList;

template<class T> class Node {
private:
	T m_data;
	Node<T> *m_nextNode;

public:
	Node(const T& elem = T(), Node<T> *const nextNode = nullptr);

	friend class SinglyLinkedList<T>;

	};

template<class T> Node<T>::Node(const T& elem, Node<T> *const nextNode) : m_data(elem), m_nextNode(nextNode) {}



template <class T> class SinglyLinkedList {
public:
	typedef std::size_t size_type;

private:
	Node<T> *m_head;
	size_type m_size;

	void uncreate();

public:

	SinglyLinkedList();
	SinglyLinkedList(const SinglyLinkedList<T>& sll);
	SinglyLinkedList(SinglyLinkedList<T> &&sll) noexcept;
	SinglyLinkedList(std::initializer_list<T> ls);

	bool empty() const;
	size_type size() const;

	void push_back(T elem);
	void push_front(T elem);
	void insert(T elem, const size_type& index);

	void remove(const size_type& index);

	T& operator[](const size_type& index);
	const T& operator[](const size_type& index) const;

	SinglyLinkedList<T>& operator=(const SinglyLinkedList<T>& rhs);
	SinglyLinkedList<T>& operator=(SinglyLinkedList<T> &&rhs) noexcept;

	SinglyLinkedList<T>& operator+=(const SinglyLinkedList<T>& rhs);

	~SinglyLinkedList();


};

template<class T> inline void SinglyLinkedList<T>::uncreate() {
	Node<T> *curNode = m_head;
	Node<T> *delNode = nullptr;

	while (curNode != nullptr) {
		delNode = curNode;
		curNode = curNode->m_nextNode;
		delete delNode;
		}
	m_size = 0;
	}

template<class T> SinglyLinkedList<T>::SinglyLinkedList() : m_head(nullptr), m_size(size_type(0)) {}

template<class T> SinglyLinkedList<T>::SinglyLinkedList(const SinglyLinkedList<T>& sll) : m_size(size_type(0)) {
	for (size_type index = 0; index != sll.m_size; ++index)
		push_back(sll[index]);
	}

template<class T> SinglyLinkedList<T>::SinglyLinkedList(SinglyLinkedList<T> &&sll) noexcept {
	// steal members of sll
	m_head = sll.m_head;
	m_size = sll.m_size;
	// leave sll in state where destructor can be called
	sll.m_head = nullptr;
	sll.m_size = 0;
	}

template<class T> SinglyLinkedList<T>::SinglyLinkedList(std::initializer_list<T> ls) {

	auto iter = ls.begin();
	m_head = new Node<T>(*iter++, nullptr);

	Node<T> *curNode = m_head;

	while (iter != ls.end()) {
		curNode->m_nextNode = new Node<T>(*iter++, nullptr);
		curNode = curNode->m_nextNode;
		}

	m_size = ls.size();

	}

template<class T> bool SinglyLinkedList<T>::empty() const { return m_size == 0; }

template<class T> typename SinglyLinkedList<T>::size_type SinglyLinkedList<T>::size() const { return m_size; }

template<class T> void SinglyLinkedList<T>::push_back(T elem) {
	if (m_size == 0)
		m_head = new Node<T>(elem, nullptr);
	else {
		Node<T> *curNode = m_head;
		for (size_type index = 1; index != m_size; ++index)
			curNode = curNode->m_nextNode;

		curNode->m_nextNode = new Node<T>(elem, nullptr);
		}
	++m_size;
	}

template<class T> void SinglyLinkedList<T>::push_front(T elem) {
	Node<T>* newHeadNode = new Node<T>(elem, nullptr);
	newHeadNode->m_nextNode = m_head;
	m_head = newHeadNode;
	++m_size;
	}

template<class T> void SinglyLinkedList<T>::insert(T elem, const size_type& index) {
	
	if (index == size_type(0)) {
		push_front(elem);
		return;
		}

	Node<T> *curNode = m_head;

	for (size_type pos = 1; pos != index; ++pos)
		curNode = curNode->m_nextNode;

	Node<T>* tmp = nullptr;
	if (curNode->m_nextNode != nullptr)
		tmp = curNode->m_nextNode;
		
	curNode->m_nextNode = new Node<T>(elem, tmp);
	++m_size;
	}

template<class T> void SinglyLinkedList<T>::remove(const size_type& index) {
	if (index == 0 && m_head->m_nextNode == nullptr) {
		delete m_head;
		m_head = nullptr;
		}
	else if (index == 0 && m_head->m_nextNode) {
		Node<T> *tmp = m_head->m_nextNode;
		delete m_head;
		m_head = tmp;
		}
	else {
		Node<T> *curNode = m_head;
		Node<T> *prevNode = nullptr;
		for (size_type pos = 0; pos != index; ++pos) {
			prevNode = curNode;
			curNode = curNode->m_nextNode;
			}
		prevNode->m_nextNode = curNode->m_nextNode;
		delete curNode;
		}
	--m_size;
	}

template<class T> T& SinglyLinkedList<T>::operator[](const size_type& index) {
	Node<T>* curNode = m_head;
	for (size_type curPos = 0; curPos != index; ++curPos)
		curNode = curNode->m_nextNode;

	return curNode->m_data;
	}

template<class T> const T& SinglyLinkedList<T>::operator[](const size_type& index) const {
	Node<T>* curNode = m_head;
	for (size_type curPos = 0; curPos != index; ++curPos)
		curNode = curNode->m_nextNode;

	return curNode->m_data;
	}

template<class T> SinglyLinkedList<T>& SinglyLinkedList<T>::operator=(const SinglyLinkedList<T>& rhs) {
	if (this != &rhs) {
		uncreate();
		for (size_type index = 0; index != rhs.m_size; ++index)
			push_back(rhs[index]);
		}
	return *this;
	}

template<class T> SinglyLinkedList<T>& SinglyLinkedList<T>::operator=(SinglyLinkedList<T> &&rhs) noexcept {
	if (this != &rhs) {
		// steal members of rhs
		m_head = rhs.m_head;
		m_size = rhs.m_size;
		// leave rhs in a state where the destructor can be called
		rhs.m_head = nullptr;
		rhs.m_size = 0;
		}
	return *this;
	}

template<class T> SinglyLinkedList<T>& SinglyLinkedList<T>::operator+=(const SinglyLinkedList<T>& rhs) {
	for (size_type index = 0; index != rhs.m_size; ++index)
		push_back(rhs[index]);

	return *this;
	}

template<class T> SinglyLinkedList<T> operator+(const SinglyLinkedList<T>& lhs, const SinglyLinkedList<T>& rhs) {
	SinglyLinkedList<T> tmp = lhs;
	tmp += rhs;
	return tmp;
}

template<class T> SinglyLinkedList<T>::~SinglyLinkedList() {
	uncreate();
	}

#endif // !SINGLY_LINKED_LIST_H
