#include "graph.hpp"
#include <gtest/gtest.h>
#include <sstream>
#include <vector>

TEST(MatrixGraphTest, InsertNodes) {
  MatrixGraph<16, int> g(false);
  EXPECT_EQ(g.insert_node(1), 0);
  EXPECT_EQ(g.insert_node(2), 1);
  EXPECT_EQ(g.insert_node(3), 2);
  EXPECT_EQ(g.nodes_num, 3);
}

TEST(MatrixGraphTest, GetNode) {
  MatrixGraph<16, int> g(false);
  g.insert_node(10);
  g.insert_node(20);
  EXPECT_EQ(g.get_node(0), 10);
  EXPECT_EQ(g.get_node(1), 20);
}

TEST(MatrixGraphTest, InsertEdges) {
  MatrixGraph<16, int> g(false);
  g.insert_node(1);
  g.insert_node(2);
  g.insert_node(3);
  g.insert_edge(0, 2,true);
  g.insert_edge(1, 2,true);

  EXPECT_TRUE(g.get_edge(0, 2));
  EXPECT_TRUE(g.get_edge(1, 2));
}

TEST(MatrixGraphTest, VisitNodes) {
  MatrixGraph<16, int> g(false);
  g.insert_node(1);
  g.insert_node(2);
  g.insert_node(3);

  std::vector<int> visited;
  g.visit_nodes([&](auto node) { visited.push_back(node); return true;});

  EXPECT_EQ(visited.size(), 3);
  EXPECT_EQ(visited, (std::vector<int>{1, 2, 3}));
}

TEST(MatrixGraphTest, DirectedFlag) {
  MatrixGraph<16, int, int> g_true(0,true);
  MatrixGraph<16, int, int> g_false(0,false);
  EXPECT_TRUE(g_true.is_directed());
  EXPECT_FALSE(g_false.is_directed());
}

TEST(MatrixGraphTest, EdgeInfoWithWeight) {
  MatrixGraph<16, int, int> g(false);
  g.insert_node(1);
  g.insert_node(2);
  g.insert_edge(0, 1, 42);

  EXPECT_EQ(g.get_edge(0, 1), 42);
}

TEST(MatrixGraphTest, MatrixGraphFullException) {
  MatrixGraph<2, int> g(false);
  g.insert_node(1);
  g.insert_node(2);
  EXPECT_THROW(g.insert_node(3), std::overflow_error);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
