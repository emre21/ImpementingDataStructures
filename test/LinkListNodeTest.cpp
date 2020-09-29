#include "pch.h"
#include <gtest/gtest.h>
#include "LinkListNodes.hpp"


class LinkListNodeTest : public ::testing::Test {

protected:

	LinkListNode<int>* nodeInitized;
	LinkListNode<int>* nodeUnInitlized;

	virtual ~LinkListNodeTest(){}

	void SetUp() override {
		
		nodeInitized = new LinkListNode<int>(1);
		nodeUnInitlized = new LinkListNode<int>();

	}

	void TearDown() override{

		delete nodeInitized;
		delete nodeUnInitlized;
	}

};

TEST_F(LinkListNodeTest, CONSTRUCTOR_TEST)
{
	EXPECT_EQ(nodeInitized->getValue(), 1);
	EXPECT_EQ(nodeInitized->getNext(), nullptr);
	EXPECT_TRUE(nodeInitized->isLastNode());

	nodeUnInitlized->setValue(12);

	EXPECT_EQ(nodeUnInitlized->getValue(), 12);
	EXPECT_EQ(nodeUnInitlized->getNext(), nullptr);
	EXPECT_TRUE(nodeUnInitlized->isLastNode());

}

TEST_F(LinkListNodeTest, NEXT_NODE_TEST)
{
	nodeInitized->getNext() = new LinkListNode<int>(13);
	EXPECT_EQ(nodeInitized->getNext()->getValue(), 13);
	EXPECT_FALSE(nodeInitized->isLastNode());
	EXPECT_TRUE(nodeInitized->getNext()->isLastNode());

}
