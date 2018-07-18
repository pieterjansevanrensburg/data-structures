#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\DataStructures\Vector.h"
#include <vector>
#include "..\DataStructures\SinglyLinkedList.h"
#include <list>
#include <iostream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DataStructuresTest
{		
	TEST_CLASS(VectorUnitTest)
	{
	public:
		
		TEST_METHOD(ConstructorTest) {
			// make vector using reference implementation
			std::vector<int> refVec{ 1,2,3,4,5,6,7,8,9,10 };

			// make vector of custom design
			VECTOR_H::Vector<int> initializerListTestVec{ 1,2,3,4,5,6,7,8,9,10 };

			// check to see if their elements are the same
			for (std::vector<int>::size_type index = 0; index != refVec.size(); ++index)
				Assert::AreEqual(refVec[index], initializerListTestVec[index]);

			// call another constructor to test
			VECTOR_H::Vector<int> vecReferenceTestVec(initializerListTestVec);
			
			// check to see if the elements are the same as the reference vector
			for (std::vector<int>::size_type index = 0; index != refVec.size(); ++index)
				Assert::AreEqual(refVec[index], vecReferenceTestVec[index]);

			//call another constructor to test
			VECTOR_H::Vector<int> iteratorTestVec(vecReferenceTestVec.begin(), vecReferenceTestVec.end());

			// check to see if the elements are the same as the reference vector
			for (std::vector<int>::size_type index = 0; index != refVec.size(); ++index)
				Assert::AreEqual(refVec[index], iteratorTestVec[index]);

			//call another constructor to test
			constexpr std::vector<int>::size_type refSize = 10;
			std::vector<int> fillRefVec(refSize, 1);

			constexpr VECTOR_H::Vector<int>::size_type testSize = 10;
			VECTOR_H::Vector<int> fillTestVec(testSize, 1);

			// check to see if the elements are the same as the reference vector
			for (std::vector<int>::size_type index = 0; index != fillRefVec.size(); ++index)
				Assert::AreEqual(fillRefVec[index], fillTestVec[index]);

			//call move constructor to test
			VECTOR_H::Vector<int> moveTestVec(std::move(fillTestVec));

			// check to see if the elements are the same as the reference vector
			for (std::vector<int>::size_type index = 0; index != fillRefVec.size(); ++index)
				Assert::AreEqual(fillRefVec[index], moveTestVec[index]);

			Assert::IsTrue(fillTestVec.empty());
			}

		TEST_METHOD(AssignmentOperatorTest) {

		VECTOR_H::Vector<int> refVec{ 1,2,3,4,5,6,7,8,9,10 };


		VECTOR_H::Vector<int> valVec{ 1,2,3,4,5,6,7,8,9,10 };
		VECTOR_H::Vector<int> testVec = valVec;
		
		

		for (VECTOR_H::Vector<int>::size_type index = 0; index != refVec.size(); ++index)
			Assert::AreEqual(refVec[index], testVec[index]);

		// check self assignment

		testVec = testVec;

		for (VECTOR_H::Vector<int>::size_type index = 0; index != refVec.size(); ++index)
			Assert::AreEqual(refVec[index], testVec[index]);

		testVec = Vector<int>();
		
		Assert::IsTrue(testVec.empty());

		testVec = std::move(valVec);

		for (VECTOR_H::Vector<int>::size_type index = 0; index != refVec.size(); ++index)
			Assert::AreEqual(refVec[index], testVec[index]);

		Assert::IsTrue(valVec.empty());

		// check self assignment

		testVec = std::move(testVec);

		for (VECTOR_H::Vector<int>::size_type index = 0; index != refVec.size(); ++index)
			Assert::AreEqual(refVec[index], testVec[index]);
		}

		TEST_METHOD(IndexOperatorTest) {

			// perform test for non-const
			VECTOR_H::Vector<int> testVec{0,1,2,3,4};

			for (int i = 0; i != testVec.size(); ++i)
				Assert::AreEqual(i, testVec[i]);

			// perform test for const
			const VECTOR_H::Vector<int> constTestVec{ 0,1,2,3,4 };
			for (int i = 0; i != constTestVec.size(); ++i)
				Assert::AreEqual(i, constTestVec[i]);

			}

		TEST_METHOD(AdditionOperatorTest) {

			VECTOR_H::Vector<int> refVec{ 1,2,3,4,5,6,7,8,9,10 };

			VECTOR_H::Vector<int> addVec1{ 1,2,3,4,5 };

			VECTOR_H::Vector<int> addVec2{ 6,7,8,9,10 };

			// test the += operator

			VECTOR_H::Vector<int> selfAddTestVec = addVec1;

			selfAddTestVec += addVec2;

			for (VECTOR_H::Vector<int>::size_type index = 0; index != refVec.size(); ++index)
				Assert::AreEqual(refVec[index], selfAddTestVec[index]);

			// test the + operator

			VECTOR_H::Vector<int> addTestVec;

			addTestVec = addVec1 + addVec2;

			for (VECTOR_H::Vector<int>::size_type index = 0; index != refVec.size(); ++index)
				Assert::AreEqual(refVec[index], addTestVec[index]);

			}

		TEST_METHOD(MemberFunctionsTest) {
			
			VECTOR_H::Vector<int> testVec;

			// check that the vector is empty and that no space is reserved
			Assert::IsTrue(testVec.empty());
			Assert::AreEqual(VECTOR_H::Vector<int>::size_type(0), testVec.size());
			Assert::AreEqual(VECTOR_H::Vector<int>::size_type(0), testVec.reserved());

			//check that begin and end are equal
			Assert::AreEqual(testVec.begin(), testVec.end());
			Assert::AreEqual(testVec.cbegin(), testVec.cend());

			testVec.push_back(1);
			testVec.push_back(2);
			// here the allocated member should double to 4 (and thus 1 place should be reserved)
			testVec.push_back(3);

			Assert::AreEqual(VECTOR_H::Vector<int>::size_type(3), testVec.size());

			Assert::AreEqual(VECTOR_H::Vector<int>::size_type(1), testVec.reserved());

			// check that begin and end are different
			Assert::AreNotEqual(testVec.begin(), testVec.end());
			Assert::AreNotEqual(testVec.cbegin(), testVec.cend());

			}

		};

	TEST_CLASS(SinglyLinkedListUnitTest) {

		TEST_METHOD(ConstructorTest) {
			// intializer list constructor test
			std::list<int> refList{ 1,2,3,4,5 };
			SINGLY_LINKED_LIST_H::SinglyLinkedList<int> testList{ 1,2,3,4,5 };

			SINGLY_LINKED_LIST_H::SinglyLinkedList<int>::size_type index = 0;
			for (const int& elem : refList)
				Assert::AreEqual(elem, testList[index++]);

			// copy constructor test

			SINGLY_LINKED_LIST_H::SinglyLinkedList<int> ccRefList{ 1,2,3,4,5 };

			SINGLY_LINKED_LIST_H::SinglyLinkedList<int> ccTestList(ccRefList);

			for (SINGLY_LINKED_LIST_H::SinglyLinkedList<int>::size_type index = 0; index != ccRefList.size(); ++index)
				Assert::AreEqual(ccRefList[index], ccTestList[index]);

			// move constructor test

			SINGLY_LINKED_LIST_H::SinglyLinkedList<int> moveFromList{ 1,2,3,4,5 };

			SINGLY_LINKED_LIST_H::SinglyLinkedList<int> mcTestList = std::move(moveFromList);

			for (SINGLY_LINKED_LIST_H::SinglyLinkedList<int>::size_type index = 0; index != ccRefList.size(); ++index)
				Assert::AreEqual(ccRefList[index], mcTestList[index]);

			Assert::IsTrue(moveFromList.empty());
			Assert::AreEqual(SINGLY_LINKED_LIST_H::SinglyLinkedList<int>::size_type(0), moveFromList.size());
			}

		TEST_METHOD(AssignmentOperatorTest) {
			// normal assignment operator
			SINGLY_LINKED_LIST_H::SinglyLinkedList<int> refList{ 1,2,3,4,5 };

			SINGLY_LINKED_LIST_H::SinglyLinkedList<int> testList = SINGLY_LINKED_LIST_H::SinglyLinkedList<int>();
			
			testList = refList;

			for (SINGLY_LINKED_LIST_H::SinglyLinkedList<int>::size_type index = 0; index != refList.size(); ++index)
				Assert::AreEqual(refList[index], testList[index]);

			Assert::AreEqual(SINGLY_LINKED_LIST_H::SinglyLinkedList<int>::size_type(5), refList.size());
			
			// check self assignment

			testList = testList;

			for (SINGLY_LINKED_LIST_H::SinglyLinkedList<int>::size_type index = 0; index != refList.size(); ++index)
				Assert::AreEqual(refList[index], testList[index]);

			// test move assignment

			testList = SINGLY_LINKED_LIST_H::SinglyLinkedList<int>();

			SINGLY_LINKED_LIST_H::SinglyLinkedList<int> moveList{ 1,2,3,4,5 };

			testList = std::move(moveList);

			Assert::IsTrue(moveList.empty());
			Assert::AreEqual(SINGLY_LINKED_LIST_H::SinglyLinkedList<int>::size_type(0), moveList.size());

			for (SINGLY_LINKED_LIST_H::SinglyLinkedList<int>::size_type index = 0; index != refList.size(); ++index)
				Assert::AreEqual(refList[index], testList[index]);

			// test self assignment

			testList = std::move(testList);
			for (SINGLY_LINKED_LIST_H::SinglyLinkedList<int>::size_type index = 0; index != refList.size(); ++index)
				Assert::AreEqual(refList[index], testList[index]);
			}

		TEST_METHOD(IndexOperatorTest) {

			const SINGLY_LINKED_LIST_H::SinglyLinkedList<int> refList{ 1,2,3,4,5 };

			const SINGLY_LINKED_LIST_H::SinglyLinkedList<int> constTestList{ 1,2,3,4,5 };

			SINGLY_LINKED_LIST_H::SinglyLinkedList<int> testList{ 1,2,3,4,5 };

			for (SINGLY_LINKED_LIST_H::SinglyLinkedList<int>::size_type index = 0; index != refList.size(); ++index) {
				Assert::AreEqual(refList[index], testList[index]);
				Assert::AreEqual(refList[index], testList[index]);
				}
			}

		TEST_METHOD(AdditionOperatorTest) {
			SINGLY_LINKED_LIST_H::SinglyLinkedList<int> refList{ 1,2,3,4,5,6,7,8,9,10 };

			SINGLY_LINKED_LIST_H::SinglyLinkedList<int> testList = SINGLY_LINKED_LIST_H::SinglyLinkedList<int>();

			SINGLY_LINKED_LIST_H::SinglyLinkedList<int> addList1{ 1,2,3,4,5 };

			SINGLY_LINKED_LIST_H::SinglyLinkedList<int> addList2{ 6,7,8,9,10 };

			testList += addList1;
			testList += addList2;

			for (SINGLY_LINKED_LIST_H::SinglyLinkedList<int>::size_type index = 0; index != refList.size(); ++index)
				Assert::AreEqual(refList[index], testList[index]);

			SINGLY_LINKED_LIST_H::SinglyLinkedList<int> testList2 = addList1 + addList2;

			for (SINGLY_LINKED_LIST_H::SinglyLinkedList<int>::size_type index = 0; index != refList.size(); ++index)
				Assert::AreEqual(refList[index], testList2[index]);
			}

		TEST_METHOD(MemberFunctionsTest) {
			SINGLY_LINKED_LIST_H::SinglyLinkedList<int> testList = SINGLY_LINKED_LIST_H::SinglyLinkedList<int>();

			Assert::IsTrue(testList.empty());

			Assert::AreEqual(SINGLY_LINKED_LIST_H::SinglyLinkedList<int>::size_type(0), testList.size());

			SINGLY_LINKED_LIST_H::SinglyLinkedList<int> refList{ 1,2,3,4,5 };

			testList.push_back(3);
			testList.push_front(2);
			testList.push_front(1);
			testList.push_back(4);
			testList.push_back(5);

			for (SINGLY_LINKED_LIST_H::SinglyLinkedList<int>::size_type index = 0; index != refList.size(); ++index)
				Assert::AreEqual(refList[index], testList[index]);

			testList = SINGLY_LINKED_LIST_H::SinglyLinkedList<int>();

			testList.push_front(1);

			Assert::AreEqual(1, testList[0]);

			testList.insert(0, 0);

			Assert::AreEqual(0, testList[0]);
			Assert::AreEqual(1, testList[1]);

			testList.insert(2, 1);

			Assert::AreEqual(2, testList[1]);

			testList.remove(1);

			Assert::AreEqual(1, testList[1]);

			testList.remove(1);

			testList.remove(0);

			Assert::IsTrue(testList.empty());

			}

		};
}