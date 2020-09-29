#include "pch.h"

#include <gtest/gtest.h>

#include "LinkListNodes.hpp"

class DoublyLinkListNodeTest : public ::testing::Test {

protected:
	
	DoublyLinkListNode<int>* nodeInitilized;
	DoublyLinkListNode<int>* nodeUnInitilized;

	DoublyLinkListNodeTest() { }

	void SetUp() override {
		nodeInitilized = new DoublyLinkListNode<int>(2);
		nodeUnInitilized = new DoublyLinkListNode<int>();
	}

	void TearDown() override {
		delete nodeInitilized;
		delete nodeUnInitilized;
	}

};


TEST_F(DoublyLinkListNodeTest, CONSTRUCTOR_TEST) {
	EXPECT_EQ(nodeInitilized->getValue(), 2);

	EXPECT_EQ(nodeInitilized->getBack(), nullptr);
	EXPECT_EQ(nodeInitilized->getNext(), nullptr);

	nodeUnInitilized->setValue(3);
	EXPECT_EQ(nodeUnInitilized->getValue(), 3);

}

TEST_F(DoublyLinkListNodeTest, NEXT_NODE_TEST) {

	nodeInitilized->getNext() = new DoublyLinkListNode<int>(4);
	EXPECT_EQ(nodeInitilized->getNext()->getValue(), 4);
}

TEST_F(DoublyLinkListNodeTest, BACK_NODE_TEST) {
	nodeInitilized->getBack() = new DoublyLinkListNode<int>(5);
	EXPECT_EQ(nodeInitilized->getBack()->getValue(), 5);
}
