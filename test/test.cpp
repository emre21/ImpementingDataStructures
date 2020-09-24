#include "pch.h"

#include "Node.hpp"
#include "LinkListNodes.hpp"
#include <iostream>

TEST(NodeTesting, NODE_INIT) {
	Node<int> node(12);
	EXPECT_EQ(12, node.getValue());
}
