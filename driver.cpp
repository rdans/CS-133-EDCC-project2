//-----------------------------------------------------------------------------
//   File: driver.cpp
//
//	 Function: main
//-----------------------------------------------------------------------------
#include "list.h"
#include "Queue.h"
#include <string>
//-------------------------------------------------------------------------------------------
//    Function:			main()
//
//    File:             driver.cpp
//
//    Title:            Circular Doubly-Linked List Queue
//
//    Description:		This file contains function main() which tests List
//	  
//
//    Programmer:		Reinaldo Daniswara
//   
//    Date:             5/19/2016
// 
//    Version:          1.0
//  
//    Environment:   Intel COre i7
//						Software: MS Windows 10 for execution;
//						Compiles under Microsoft Visual Studio 2015
// 
//    Input:			None
// 
//    Output:			Screen display of 
// 
//    Calls:            list classes and related functions
// 
//    Called By:		n/a
// 
//    Parameters:		None
// 
//    Returns:          EXIT_SUCCESS  = successful 
//					    EXIT_FAILURE = catch exception e
//
//    History Log:
//                          5/19/2016  PB  completed version 1.0
// ----------------------------------------------------------------------------

int main(void)
{
	using RD_ADT::list;
	using RD_ADT::CQueue;

	try
	{
		list<string> list1;
		list<string>::iterator it;

		cout << "Push front salmon" << endl;
		list1.push_front("salmon");
		cout << list1 << endl;

		cout << "Push front tuna and red snapper in front" << endl;
		list1.push_front("tuna");
		list1.push_front("red snapper");
		cout << list1 << endl;

		cout << "Add yellowtail at the end (push back)" << endl;
		list1.push_back("yellowtail");
		cout << list1 << endl;
		
		cout << "check the positive index" << endl;
		cout << "list1 [0] is " << list1[0] << endl;
		cout << "list1 [2] is " << list1[2] << endl;
		cout << "The negative index: " << endl;
		cout << "list1 [-1] is " << list1[-1] << endl;
		cout << "list1 [-3] is " << list1[-3] << endl << endl;
 
		list<string> list2(list1.begin(), list1.end());
		cout << "Iterator constructor test (list 2)" << endl; 
		cout << list2 << endl;

		list2.pop_back();
		list2.pop_back();
		list2.pop_back();
		list2.pop_back();
		cout << "Remove the all element of list 2 with using pop back : " << endl << list2;

		list<string> list3 = list1;
		cout << "Operator = test, copy list 1 into list 3" << endl;
		cout << list3 << endl;

		list3.pop_back();
		cout << "Remove the last element of list 3" << endl << list3;

		list3.pop_front();
		cout << "Remove the first element of list 3 after pop back" << endl;
		cout << list3 << endl;

		list3.pop_front();
		list3.pop_front();
		cout << "Remove all elements of list 3 using pop front" << endl;
		cout << list3 << endl;


		//test queue
		cout << "copy list 1 into queue 1" << endl;
		CQueue<string> queue1(list1);
		for (it = queue1.begin(); it != queue1.end(); ++it)
		{
			cout << *it << endl;
		}
		cout << *it << endl << endl ; //to print out the last element

		cout << "Iterator constructor test for queue 1" << endl;
		CQueue<string> queue2(queue1.begin(), queue1.end());
		for (it = queue2.begin(); it != queue2.end(); ++it)
		{
			cout << *it << endl;
		}
		cout << *it << endl << endl; //to print out the last element

		CQueue<string> queue3 = queue2;
		cout << "Operator = test for queue, queue3 = queue2 : " << endl;
		cout << queue3 << endl;
		
		cout << "Add an element at the end of the list" << endl;
		queue3.push(string("Sushi makes me hungry"));
		cout << queue3 << endl;

		cout << "Remove an element at the end of the list" << endl;
		queue3.pop();
		cout << queue3 << endl;

		cout << "Remove all element at the end of the list" << endl;
		queue3.pop();
		queue3.pop();
		queue3.pop();
		queue3.pop();
		cout << queue3;

		list1.release();
		queue1.release();
		queue2.release();
		cout << "List 1 after release : " << list1;
	}

	catch (exception e)
	{
		cerr << "program terminated: " << e.what() << endl;
		cin.get();
		return EXIT_FAILURE;
	}

	cin.get(); // keep windows open
	return EXIT_SUCCESS;
}