#include "pch.h"
#include <gtest/gtest.h>
#include "Node.hpp"

TEST(NodeTesting, NODE_INIT) {

	Node<int> node(12);
	Node<int> node2;
	node2.setValue(2);
	EXPECT_EQ(12, node.getValue());
	EXPECT_EQ(2, node2.getValue());
}

TEST(NodeTesting, NODE_COPY_CONSTRUCT)
{
	Node<int> nodeInit(13);
	Node<int> nodeUnInit(nodeInit);

	EXPECT_EQ(nodeInit.getValue(), nodeUnInit.getValue());
}

TEST(NodeTesting, NODE_EQUAL_OPERATOR) {

	Node<int> nodeUnInýt;
	Node<int> nodeInit(14);
	nodeUnInýt = nodeInit;


	EXPECT_EQ(nodeUnInýt.getValue(), nodeInit.getValue()) <<
		" NodeUnInit value : " << nodeUnInýt.getValue()
		<< " nodeInit value :  " << nodeInit.getValue();

}
