#include "graph.hpp"
#include <cstdint>
#include <gtest/gtest.h>
#include <sstream>
#include <vector>
#include <cstdio>
#include "graph_algorithm.hpp"
TEST(MatrixGraphTest, InsertNodes) {
  MatrixGraph<int,3> g(false, false);
  EXPECT_EQ(g.insert_node(1), 1);
  EXPECT_EQ(g.insert_node(2), 2);
  EXPECT_EQ(g.insert_node(3), 3);
  EXPECT_EQ(g.size, 3);
}

TEST(MatrixGraphTest, GetNode) {
  MatrixGraph<int,3> g(false,false);
  g.insert_node(10);
  g.insert_node(20);
  EXPECT_EQ(g.nodes[0], 10);
  EXPECT_EQ(g.nodes[1], 20);
}

TEST(MatrixGraphTest, VisitNodes) {
  MatrixGraph<int,4> g(false,false);
  g.insert_node(1);
  g.insert_node(2);
  g.insert_node(3);

  std::vector<int> visited;
  g.visit_nodes([&](auto node) { if(visited.size()<g.size) visited.push_back(node); return true;});

  EXPECT_EQ(visited.size(), 3);
  EXPECT_EQ(visited, (std::vector<int>{1, 2, 3}));
}

TEST(MatrixGraphTest, DirectedFlag) {
  MatrixGraph<int, 2> g_true(false,true);
  MatrixGraph<int, 1> g_false(false,false);
  EXPECT_TRUE(g_true.directed);
  EXPECT_FALSE(g_false.directed);
}

TEST(MatrixGraphTest, EdgeInfoWithWeight) {
  MatrixGraph<int, 2,uint64_t, int> g(std::numeric_limits<int>::max(), false);
  g.insert_node(1);
  g.insert_node(2);
  g.insert_edge(0, 1, 42);

  EXPECT_EQ(g.edges[0][1], 42);
  // printf("g.edges = %d\n",g.edges[0][1]);
}

TEST(MatrixGraphTest, BFSTest_Simple) {
  MatrixGraph<int, 2> g(false, false);
  g.insert_node(1);
  g.insert_node(2);
  g.insert_edge(0, 1, true);
  testing::internal::CaptureStdout();
  bfs(g, 0, [&](uint64_t node) {
    printf("%x,", node);
  });
  EXPECT_EQ(testing::internal::GetCapturedStdout(), "1,2,");
}

TEST(MatrixGraphTest, BFSTest_LinearChain) {
  MatrixGraph<int, 6> g(false, false);
  g.insert_node(10);
  g.insert_node(20);
  g.insert_node(30);
  g.insert_node(40);
  g.insert_edge(0, 1, true);
  g.insert_edge(1, 2, true);
  g.insert_edge(2, 3, true);
  std::vector<int> order;
  bfs(g, 0, [&](int node) { order.push_back(node); });
  EXPECT_EQ(order, (std::vector<int>{10, 20, 30, 40}));
}

TEST(MatrixGraphTest, BFSTest_Star) {
  MatrixGraph<int, 6> g(false, false);
  g.insert_node(0);
  g.insert_node(1);
  g.insert_node(2);
  g.insert_node(3);
  g.insert_edge(0, 1, true);
  g.insert_edge(0, 2, true);
  g.insert_edge(0, 3, true);
  std::vector<int> order;
  bfs(g, 0, [&](int node) { order.push_back(node); });
  ASSERT_EQ(order.size(), 4u);
  EXPECT_EQ(order[0], 0);
}

TEST(MatrixGraphTest, BFSTest_Disconnected) {
  MatrixGraph<int, 6> g(false, false);
  g.insert_node(1);
  g.insert_node(2);
  g.insert_node(10);
  g.insert_node(20);
  g.insert_edge(0, 1, true);
  g.insert_edge(2, 3, true);
  std::vector<int> order;
  bfs(g, 0, [&](int node) { order.push_back(node); });
  ASSERT_EQ(order.size(), 4u);
  EXPECT_EQ(order[0], 1);
  EXPECT_EQ(order[1], 2);
}

TEST(MatrixGraphTest, BFSTest_Directed) {
  MatrixGraph<int, 6> g(false, true);
  g.insert_node(1);
  g.insert_node(2);
  g.insert_node(3);
  g.insert_edge(0, 1, true);
  g.insert_edge(1, 2, true);
  std::vector<int> order;
  bfs(g, 0, [&](int node) { order.push_back(node); });
  EXPECT_EQ(order, (std::vector<int>{1, 2, 3}));
}

TEST(MatrixGraphTest, BFSTest_DirectedNoBackEdge) {
  MatrixGraph<int, 4> g(false, true);
  g.insert_node(1);
  g.insert_node(2);
  g.insert_edge(0, 1, true);
  std::vector<int> order;
  bfs(g, 1, [&](int node) { order.push_back(node); });
  ASSERT_EQ(order.size(), 2u);
  EXPECT_EQ(order[0], 2);
  EXPECT_EQ(order[1], 1);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
