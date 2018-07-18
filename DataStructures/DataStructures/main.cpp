#include <iostream>
#include <string>
#include <cstdlib>
#include <list>
#include "SinglyLinkedList.h"

int main(int argc, char **argv) {

	const SINGLY_LINKED_LIST_H::SinglyLinkedList<int> ccRefList{ 1,2,3,4,5 };

	SINGLY_LINKED_LIST_H::SinglyLinkedList<int> ccTestList(ccRefList);

	for (SINGLY_LINKED_LIST_H::SinglyLinkedList<int>::size_type index = 0; index != ccRefList.size(); ++index)
		std::cout << ccRefList[index] << "|" << ccTestList[index] << std::endl;

	system("pause");
	return EXIT_SUCCESS;
	}