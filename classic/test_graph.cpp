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

TEST(MatrixGraphTest, BFSTest) {
  // undirected: chain 0-1-2-3, star 0-4, disconnected 5-6
  MatrixGraph<int, 8> gu(false, false);
  gu.insert_node(10);
  gu.insert_node(20);
  gu.insert_node(30);
  gu.insert_node(40);
  gu.insert_node(50);
  gu.insert_node(60);
  gu.insert_node(70);
  gu.insert_edge(0, 1, true);
  gu.insert_edge(1, 2, true);
  gu.insert_edge(2, 3, true);
  gu.insert_edge(0, 4, true);
  gu.insert_edge(5, 6, true);

  std::vector<int> order;
  bfs(gu, 0, [&](int node) { order.push_back(node); });
  ASSERT_EQ(order.size(), 7u);
  EXPECT_EQ(order[0], 10);
  EXPECT_EQ(order[1], 20);
  EXPECT_EQ(order[2], 50);
  EXPECT_EQ(order[3], 30);
  EXPECT_EQ(order[4], 40);
  EXPECT_EQ(order[5], 60);
  EXPECT_EQ(order[6], 70);

  // directed: 0→1→2, start from 0
  MatrixGraph<int, 4> gd(false, true);
  gd.insert_node(1);
  gd.insert_node(2);
  gd.insert_node(3);
  gd.insert_edge(0, 1, true);
  gd.insert_edge(1, 2, true);
  order.clear();
  bfs(gd, 0, [&](int node) { order.push_back(node); });
  EXPECT_EQ(order, (std::vector<int>{1, 2, 3}));

  // directed: 0→1, start from 1 (no back edge, fallback visits 0)
  order.clear();
  bfs(gd, 1, [&](int node) { order.push_back(node); });
  ASSERT_EQ(order.size(), 3u);
  EXPECT_EQ(order[0], 2);
  EXPECT_EQ(order[1], 3);
  EXPECT_EQ(order[2], 1);
}

TEST(MatrixGraphTest, DFSTest) {
  // undirected: chain 0-1-2-3, star 0-4, disconnected 5-6
  MatrixGraph<int, 8> gu(false, false);
  gu.insert_node(10);
  gu.insert_node(20);
  gu.insert_node(30);
  gu.insert_node(40);
  gu.insert_node(50);
  gu.insert_node(60);
  gu.insert_node(70);
  gu.insert_edge(0, 1, true);
  gu.insert_edge(1, 2, true);
  gu.insert_edge(2, 3, true);
  gu.insert_edge(0, 4, true);
  gu.insert_edge(5, 6, true);

  std::vector<int> order;
  dfs(gu, 0, [&](int node) { order.push_back(node); });
  ASSERT_EQ(order.size(), 7u);
  EXPECT_EQ(order[0], 10);
  EXPECT_EQ(order[1], 20);
  EXPECT_EQ(order[2], 30);
  EXPECT_EQ(order[3], 40);
  EXPECT_EQ(order[4], 50);
  EXPECT_EQ(order[5], 60);
  EXPECT_EQ(order[6], 70);

  // directed: 0→1→2
  MatrixGraph<int, 4> gd(false, true);
  gd.insert_node(1);
  gd.insert_node(2);
  gd.insert_node(3);
  gd.insert_edge(0, 1, true);
  gd.insert_edge(1, 2, true);

  order.clear();
  dfs(gd, 0, [&](int node) { order.push_back(node); });
  EXPECT_EQ(order, (std::vector<int>{1, 2, 3}));

  order.clear();
  dfs(gd, 1, [&](int node) { order.push_back(node); });
  ASSERT_EQ(order.size(), 3u);
  EXPECT_EQ(order[0], 2);
  EXPECT_EQ(order[1], 3);
  EXPECT_EQ(order[2], 1);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
