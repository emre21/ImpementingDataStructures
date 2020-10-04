#include "pch.h"

#include <gtest/gtest.h>

#include "LinkLists.hpp"
#include <functional>




/*

	TEST CASES 
		Add Element ,Control Size , Control last Element,
		Delete Element with index ,Control Size ,Control first and last element
		add element with index 0 , control root node , control root next node, control size;
		Delete Element without index control size ,root node,last  node
*/

// FOR DELETE ELEMENT TEST , if you delete item without index you must add compare function in function
class PersonWithoutEquality_OP {   
public:

	PersonWithoutEquality_OP() {
		m_age = -1;
	};

	PersonWithoutEquality_OP(int age)
	: m_age(age)
	{ }

	int m_age;
};

bool compareFunc(PersonWithoutEquality_OP obj1, PersonWithoutEquality_OP obj2)
{
	return obj1.m_age == obj2.m_age ? true : false;
}

// FOR DELETE ELEMENT TEST , you can delete element without index
class PersonWithEquality_OP  : public PersonWithoutEquality_OP{ 
public:
	
	PersonWithEquality_OP()
		: PersonWithoutEquality_OP()
	{}

	PersonWithEquality_OP(int age)
		: PersonWithoutEquality_OP(age)
	{ }

	bool operator==(const PersonWithEquality_OP& person) {
		return person.m_age == this->m_age ? true : false;
	}

	
};



class LinkedListTest : public ::testing::Test
{
protected:

	LinkList<int>* list_1;
	LinkList<PersonWithoutEquality_OP>* list_2;
	LinkList<PersonWithEquality_OP>* list_3;
	

	void SetUp() override {
			
	}

	void TearDown() override {

	}
};



TEST_F(LinkedListTest, INTEGER_TEST) {
	
	list_1 = new LinkList<int>(0);
	EXPECT_EQ(list_1->getRoot(), 0);
	EXPECT_EQ(list_1->getSize(), 1);
	EXPECT_EQ(list_1->getElementByIndex(0), 0);
	
	list_1->add(1);
	list_1->add(2);
	list_1->add(3);
	list_1->add(4);

	EXPECT_EQ(list_1->getSize(), 5);

	list_1->addByIndex(2, 10);
	EXPECT_EQ(list_1->getElementByIndex(3), 10);
	EXPECT_EQ(list_1->getElementByIndex(4), 3);
	EXPECT_EQ(list_1->getSize(), 6);


	list_1->deleteElementByIndex(3);
	EXPECT_EQ(list_1->getElementByIndex(3), 3);
	EXPECT_EQ(list_1->getSize(), 5);
}

TEST_F(LinkedListTest, EQUALTY_OBJECT_DELETE_TEST) {

	PersonWithEquality_OP obj(0);
	list_3 = new LinkList<PersonWithEquality_OP>(obj);

	for (int i = 1; i < 4; i++)
	{
		PersonWithEquality_OP person(i);
		list_3->add(person);
	}

	EXPECT_EQ(list_3->getSize(), 4);

	PersonWithEquality_OP deleteObj(1);

	list_3->deleteElement(deleteObj);

	EXPECT_EQ(list_3->getElementByIndex(2).m_age, 2);
}


/*
TEST_F(LinkedListTest, NONEQUALTY_OBJECT_DELETE_TEST) {
	

	PersonWithoutEquality_OP obj(0);
	list_2 = new LinkList<PersonWithoutEquality_OP>(obj);

	for (int i = 1; i < 4; i++)
	{
		PersonWithoutEquality_OP person(i);
		list_2->add(person);
	}

	EXPECT_EQ(list_2->getSize(), 4);

	PersonWithoutEquality_OP deleteObj(1);
	
	std::function<bool(PersonWithoutEquality_OP,PersonWithoutEquality_OP)> lamdaFunc =
		[](PersonWithoutEquality_OP obj1,PersonWithoutEquality_OP obj2) -> bool 
	{
		return obj1.m_age == obj2.m_age ? true : false;
	};

	list_2->deleteElement(deleteObj,compareFunc);

	EXPECT_EQ(list_2->getElementByIndex(1).m_age, 2);

}
*/