//-----------------------------------------------------------------------------
//   File: Queue.h
//-----------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------
//    Class:			CQueue
//
//    File:             Queue.h
//
//    Title:            CQueue Class
//
//    Description:		This file contains the class definition for CQueue
//
//    Programmer:		Reinaldo Daniswara
//   
//    Date:             5/19/2016
// 
//    Version:          1.0
//  
//   Environment:		Intel COre i7
//						Software: MS Windows 10 for execution;
//						Compiles under Microsoft Visual Studio 2015
// 
//	  class CQueue:
//
//	  Methods:
//	
//		inline:	
//		CQueue() : list() {} -- constructor of the queue
//		CQueue(size_t size, T datum) -- create a list of a specific size, all elements the same
//		CQueue(const list<T>& other) -- copy constructor
//		CQueue(iterator b, iterator e) -- constructor using iterators
//
//		~CQueue() -- destructor
//		unsigned getSize() const -- accessor, returns m_size
//		iterator begin() const -- return list<T>::begin()
//		iterator end() const -- return list<T>::end()
//
//		bool empty()const -- return true if it is empty
//		void release() -- remove items from list
//		void push(T& element) -- insert item at the last element, 
//								parameter T& element
//		T pop() -- remove an item at the begining of the element, 
//
//		non-inline:
//			ostream& operator<<(ostream& sout, const CQueue<T>& x) 
//					-- print out elements
//    
//    History Log:
//                           5/19/2016  RD  completed version 1.0
// ----------------------------------------------------------------------------


#ifndef CQUEUE_H
#define CQUEUE_H
#include "list.h"

using namespace std;

namespace RD_ADT
{
	template <class T>
	class CQueue : protected list<T>
	{
	public:
		CQueue() : list() {}
		CQueue(size_t size, T datum) : list(size, datum) {}
		CQueue(const list<T>& other) : list(other) {}
		CQueue(iterator b, iterator e) : list(b, e) {}

		~CQueue() { release(); }
		unsigned getSize() const { return m_size; }
		iterator begin() const { return list<T>::begin(); }
		iterator end() const { return list<T>::end(); }

		bool empty()const { return list<T>::empty(); }
		void release() { list<T>::release(); }
		void push(T& element) { push_back(element); }
		T pop() { return pop_front(); }
	};

	//-----------------------------------------------------------------------------
	//    Class:			CQueue
	//	  Function:			ostream& operator<<(ostream& sout, const CQueue<T>& x)
	//	  Description:		displays elements to sout
	//
	//	  Input:			None	
	//				
	//	  Output:			elements to sout
	// 
	//    Calls:            none
	//    Called By:		main
	// 
	//    Parameters:		ostream& sout, const CQueue<T>& x
	//	  Returns:          ostream & sout 
	//
	//    History Log:
	//                      5/19/2016 RD completed version
	//-----------------------------------------------------------------------------

	template <class T>
	ostream& operator<<(ostream& sout, const CQueue<T>& x)
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
}

#endif
