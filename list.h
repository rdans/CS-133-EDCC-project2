//-----------------------------------------------------------------------------
//   File: list.h
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//   Title: list Class
//   Description: This file contains the class definition for list
//
//   Programmer: Reinaldo Daniswara
// 
//   Date: 5/19/2016
//   Version: 1.0
//
//   Environment: Intel Core i7
//     Software: MS Windows 10 for execution;
//     Compiles under Microsoft Visual Studio 2015
//
//   class list:
//
//     Properties:
//       listelem *head -- front end of list
//       listelem *tail -- back end of list
//       unsigned m_size -- number of elements in the list
//
//     Methods:
// 
//       inline: 
//         list() -- construct the empty list
//         list(size_t n_elements, T datum) -- create a list of a specific size, all elements the same
//         ~list() { release(); } -- destructor
//         unsigned getSize()const  -- accessor, returns m_size
//         iterator begin()const -- returns address of first element
//         iterator end()const -- returns address of last element
//         T& front()const  -- returns first element data
//         T& back()const -- returns last element data
//         bool empty()const -- true if no elements
//
//       non-inline:
//         list(const list& x); -- copy constructor
//         list(iterator b, iterator e) -- constructor using iterators
//         void push_front(T datum) -- insert element at front of list
//         T pop_front(); -- removes front element and returns the data from that element
//         void push_back(T datum) -- insert element at back of list 
//         T pop_back() -- removes back element and returns the data from that element
//         void release() -- removes all items from list
//         list operator=(const list & rlist) -- returns a copy of rlist
//         T& operator[](int index) -- for l-value
//         const T& operator[](int index)const -- for r-value
//
//    Public Nested Structures:
//
//      struct listelem -- list cell
//
//        properties:
//          T data -- the actual datum
//          listelem *next -- forward link
//          listelem *prev -- backward link
//        constructor:
//          listelem(T c, listelem* p, listelem* n, listelem* p) -- struct constructor
//
//     class iterator
//        Public Methods
// 
//           inline: 
//            listelem* operator->() -- same as for pointer
//            T& operator*() -- same as for pointer
//            operator listelem*() -- conversion
//            iterator(listelem* p = nullptr) -- constructor
// 
//           non-inline: 
//            iterator operator++() -- pre-increment
//            iterator operator--() -- pre-decrement
//            iterator operator++(int) -- post-increment
//            iterator operator--(int) -- post-decrement
// 
//        Private Properties
//            listelem* ptr -- current listelem or NULL
//
//   History Log:
//			5/19/2016 RD completed version 1.0
//-----------------------------------------------------------------------------

#ifndef LIST_H 
#define LIST_H
#include <iostream>
#include <cassert>
#include <exception>
#include <cstdlib>

using namespace std;
// namespace std has its own list -- we won't use it here
namespace RD_ADT
{

	template <class T>

	class list
	{
	public:
		struct listelem; // forward declarations
		class iterator;
		// constructors
		list() : head(nullptr), tail(nullptr), m_size(0) {}
		list(size_t n_elements, T datum);
		list(const list& x);
		list(iterator b, iterator e);

		~list() { release(); }
		unsigned getSize() const { return m_size; }
		iterator begin() const { return head; }
		iterator end() const { return tail; }
		void push_front(T datum);
		T pop_front();
		void push_back(T datum);
		T pop_back();
		T& front() const { return head->data; }
		T& back() const { return tail->data; }
		bool empty()const { return head == nullptr || tail == nullptr; }
		void release() { while (head != nullptr) pop_front(); }
		list operator=(const list<T> & rlist);
		T& operator[](int index);
		const T& operator[](int index) const;


	private:
		listelem *head;
		listelem *tail;
		unsigned m_size; // number of elements in the list 
	public:
		struct listelem // list cell
		{
			T data;
			listelem *next;
			listelem *prev;
			listelem(T datum, listelem* p, listelem* n) : data(datum), prev(p), next(n) {} // struct constructor
		};
		// scoped within class list !
		class iterator
		{
		public:
			iterator(listelem* p = nullptr) : ptr(p) {}
			iterator operator++();
			iterator operator--();
			iterator operator++(int);
			iterator operator--(int);
			listelem* operator->() const { return ptr; }
			T& operator*() const { return ptr->data; }
			operator listelem*() const { return ptr; }
		private:
			listelem* ptr; //current listelem or nullptr
		};
	};

	template <class T>
	ostream& operator<<(ostream& sout, const list<T>& x);

	//-----------------------------------------------------------------------------
	//    Class:			list<T>
	//	  Method:			list(size_t n_elements, T datum)
	//
	//	  Description:		Constructor for list<T>
	// 
	//    Calls:            none
	//    Called By:		main
	// 
	//    Parameters:		size_t n_elements, T datum
	//
	//    History Log:
	//                      5/19/2016 RD completed version
	//-----------------------------------------------------------------------------

	template <class T>
	list<T>::list(size_t n_elements, T datum)
		:m_size(0), head(nullptr), tail(nullptr)
	{
		if (n_elements <= 0)
			throw out_of_range("Empty list");
		for (size_t i = 0; i < n_elements; ++i)
			push_front(datum);
	}

	//-----------------------------------------------------------------------------
	//    Class:			list<T>
	//	  Method:			list(const list<T>& x)
	//
	//	  Description:		Copy constructor for list<T>
	// 
	//    Calls:            none
	//    Called By:		main
	// 
	//    Parameters:		const list<T>& x
	//
	//    History Log:
	//                      5/19/2016 RD completed version
	//-----------------------------------------------------------------------------

	template <class T>
	list<T>::list(const list<T>& x)
		: m_size(0), head(nullptr), tail(nullptr)
	{
		list<T>::iterator r_it = x.begin();
		while (r_it != x.end())
			push_back(*r_it++);
		push_back(*r_it++);

	}

	//-----------------------------------------------------------------------------
	//    Class:			list<T>
	//	  Method:			list(iterator b, iterator e)
	//
	//	  Description:		constructor using iterators, copies from b to one before e
	// 
	//    Calls:            none
	//    Called By:		main
	// 
	//    Parameters:		iterator b, iterator e
	//
	//    History Log:
	//                      5/19/2016 RD completed version
	//-----------------------------------------------------------------------------

	template <class T>
	list<T>::list(iterator b, iterator e)
		:m_size(0), head(nullptr), tail(nullptr)
	{
		while (b != e)
			push_back(*b++);
		push_back(*b++);
	}

	//-----------------------------------------------------------------------------
	//    Class:			list<T>
	//	  Function:			ostream& operator<<(ostream& sout, const list<T>& x)
	//	  Description:		displays elements to sout
	//
	//	  Input:			None	
	//				
	//	  Output:			elements to sout
	// 
	//    Calls:            none
	//    Called By:		main
	// 
	//    Parameters:		ostream& sout, const list<T>& x
	//	  Returns:          ostream & sout 
	//
	//    History Log:
	//                      5/19/2016 RD completed version
	//-----------------------------------------------------------------------------

	template <class T>
	ostream& operator<<(ostream& sout, const list<T>& x)
	{
		list<T>::iterator p = x.begin(); // gets x.h
		sout << "(";
		while (p != x.end())
		{
			sout << *p;
			if (p != nullptr)
				sout << ", ";
			++p; // advances iterator using next
		}
		if (p != nullptr)
			sout << *p;
		sout << ")\n";
		return sout;
	}

	//-----------------------------------------------------------------------------
	//    Class:			list<T>
	//	  Method:			push_front(T datum)
	//
	//	  Description:		insert element at front of list
	// 
	//    Calls:            none
	//    Called By:		main
	// 
	//    Parameters:		T datum
	//
	//    History Log:
	//                      5/19/2016 RD completed version
	//-----------------------------------------------------------------------------

	template <class T>
	void list<T>::push_front(T datum)
	{
		listelem* temp = new listelem(datum, tail, head);

		if (!empty())
		{ // was a nonempty list
			head->prev = temp;
			head = temp;
		}
		else
		{
			head = tail = temp;
			temp->next = tail;
			temp->next = head;
		}
		m_size++;
	}

	//-----------------------------------------------------------------------------
	//    Class:			list<T>
	//	  Method:			list<T>::operator=(const list & rlist)
	//
	//	  Description:		returns a copy of rlist
	// 
	//    Calls:            none
	//    Called By:		n/a
	// 
	//    Parameters:		const list & rlist
	//	  Return:			*this
	//
	//    History Log:
	//                      5/19/2016 RD completed version
	//-----------------------------------------------------------------------------

	template <class T>
	list<T> list<T>::operator=(const list<T> & rlist)
	{
		if (&rlist != this)
		{
			list<T>::iterator r_it = rlist.begin();
			release();
			while (r_it != rlist.end())
				push_back(*r_it++);
			push_front(*r_it++);
		}
		return *this;
	}

	//-----------------------------------------------------------------------------
	//    Class:			list<T>
	//	  Method:			list<T>::iterator::operator++()
	//
	//	  Description:		pre-increment
	//	  Return:			*this
	// 
	//    Calls:            none
	//    Called By:		main, push_front()
	// 
	//    Parameters:		None
	//
	//    History Log:
	//                      5/19/2016 RD completed version
	//-----------------------------------------------------------------------------

	template <class T>
	typename list<T>::iterator list<T>::iterator::operator++()
	{
		if (ptr == nullptr)
			throw runtime_error("nullptr pointer");
		ptr = ptr->next;
		return *this;
	}

	//-----------------------------------------------------------------------------
	//    Class:			list<T>
	//	  Method:			list<T>::iterator::operator++(int)
	//
	//	  Description:		post-increment
	//	  Return:			temp
	// 
	//    Calls:            none
	//    Called By:		main, push_back
	// 
	//    Parameters:		int
	//
	//    History Log:
	//                      5/19/2016 RD completed version
	//-----------------------------------------------------------------------------

	template <class T>
	typename list<T>::iterator list<T>::iterator::operator++(int)
	{
		if (ptr == nullptr)
			throw runtime_error("nullptr pointer");
		iterator temp = *this;
		ptr = ptr->next;
		return temp;
	}


	//-----------------------------------------------------------------------------
	//    Class:			list<T>
	//	  Method:			list<T>::iterator::operator--()
	//
	//	  Description:		pre-decrement
	//	  Return:			*this
	// 
	//    Calls:            none
	//    Called By:		n/a
	// 
	//    Parameters:		none
	//
	//    History Log:
	//                      5/19/2016 RD completed version
	//-----------------------------------------------------------------------------

	template <class T>
	typename list<T>::iterator list<T>::iterator::operator--()
	{
		if (ptr == nullptr)
			throw runtime_error("nullptr pointer");
		ptr = ptr->prev;
		return *this;
	}

	//-----------------------------------------------------------------------------
	//    Class:			list<T>
	//	  Method:			list<T>::iterator::operator--(int)
	//
	//	  Description:		post-decrement
	//	  Return:			temp
	// 
	//    Calls:            none
	//    Called By:		pop_front(), pop_back()
	// 
	//    Parameters:		int
	//
	//    History Log:
	//                      5/19/2016 RD completed version
	//-----------------------------------------------------------------------------

	template <class T>
	typename list<T>::iterator list<T>::iterator::operator--(int)
	{
		if (ptr == nullptr)
			throw runtime_error("nullptr pointer");
		iterator temp = *this;
		ptr = ptr->prev;
		return temp;
	}

	//-----------------------------------------------------------------------------
	//    Class:			list<T>
	//	  Method:			list<T>::pop_front()
	//
	//	  Description:		removes front element and returns the data from that element
	//	  Return:			*temp if m_size == 1
	//						data
	// 
	//    Calls:            none
	//    Called By:		n/a
	// 
	//    Parameters:		none
	//
	//    History Log:
	//                      5/19/2016 RD completed version
	//-----------------------------------------------------------------------------

	template <class T>
	T list<T>::pop_front()
	{
		if (head == nullptr)
			throw runtime_error("Empty list");
		if (m_size == 1)
		{
			m_size--;
			T temp = head->data;
			delete head;
			head = tail = nullptr;
			return temp;
		}

		T data = head->data;
		iterator temp = begin();
		temp++;
		delete head;
		head = temp;
		if (!empty())
			head->prev = tail;
		else
			tail = nullptr;

		m_size--;
			return data;
	}

	//-----------------------------------------------------------------------------
	//    Class:			list<T>
	//	  Method:			list<T>::push_back(T datum)
	//
	//	  Description:		insert element at last of list
	//	  Return:			none
	// 
	//    Calls:            none
	//    Called By:		n/a
	// 
	//    Parameters:		T datum
	//
	//    History Log:
	//                      5/19/2016 RD completed version
	//-----------------------------------------------------------------------------

	template<class T>
	void list<T>::push_back(T datum)
	{
		listelem* temp = new listelem(datum, tail, head);

		if (!empty())
		{
			tail->next = temp;
			tail = temp;
			head->prev = tail;
		}
		else
		{
			head = tail = temp;
			temp->next = tail;
			temp->prev = head;
		}

		m_size++;

	}

	//-----------------------------------------------------------------------------
	//    Class:			list<T>
	//	  Method:			list<T>::pop_back()
	//
	//	  Description:		remove last element of list
	//	  Return:			none
	// 
	//    Calls:            none
	//    Called By:		n/a
	// 
	//    Parameters:		T datum
	//
	//    History Log:
	//                      5/19/2016 RD completed version
	//-----------------------------------------------------------------------------

	template <class T>
	T list<T>::pop_back()
	{
		if (tail == nullptr)
			throw runtime_error("Empty list");

		if (m_size == 1)
		{
			m_size--;
			T temp = tail->data;
			delete tail;
			head = tail = nullptr;
			return temp;
		}

		m_size--;
		T data = tail->data;
		iterator temp = end();
		temp--;
		delete tail;
		tail = temp;

		if (empty())
			head = nullptr;
		else
			tail->next = head;

		return data;
	}

	//-----------------------------------------------------------------------------
	//    Class:			list<T>
	//	  Method:			list<T>::operator[](int index)
	//
	//	  Description:		[] operator -- l-value
	// 
	//    Calls:            getSize()
	//    Called By:		main
	// 
	//    Parameters:		int index
	//	  Return:			*it
	//
	//    History Log:
	//                      5/19/2016 RD completed version
	//-----------------------------------------------------------------------------

	template <class T>
	T& list<T>::operator[](int index)
	{
		iterator it;
		if (index >= 0)
		{
			if (index >= static_cast<int>(getSize()))
				throw out_of_range("index out-of-range");
			it = begin();
			for (int i = 0; i < index; i++)
				it++;
		}
		else
		{
			if (index < -(static_cast<int>(getSize())))
				throw out_of_range("index out-of-range");
			it = end();
			for (int i = -1; i > index; i--)
				it--;
		}
		return *it;
	}

	//-----------------------------------------------------------------------------
	//    Class:			list<T>
	//	  Method:			list<T>::operator[](int index)const
	//
	//	  Description:		[] operator -- r-value
	// 
	//    Calls:            getSize(), begin(), end()
	//    Called By:		main
	// 
	//    Parameters:		int index
	//	  Return:			*it
	//
	//    History Log:
	//                      5/19/2016 RD completed version
	//-----------------------------------------------------------------------------

	template <class T>
	const T& list<T>::operator[](int index)const
	{
		int middle = m_size / 2;
		iterator it;
		if (index >= 0)
		{
			if (index >= static_cast<int>(getSize()))
				throw out_of_range("index out-of-range");
			if (index <= middle)
			{
				it = begin();
				for (int i = 0; i < index; i++)
					it++;
			}
			else
			{
				it = end();
				for (int i = m_size; i > 0; i--)
					it--;
			}

		}
		else
		{
			if (index < -(static_cast<int>(getSize())))
				throw out_of_range("index out-of-range");
			int pos = m_size + index;// make the range positive

			if (pos >= middle)
			{
				it = end();
				for (int i = m_size; i > 0; i--)
					it--;
			}
			else
			{
				it = begin();
				for (int i = 0; i < pos; i++)
					it++;
			}
		}
		return *it;
	}
}
	 #endif 
