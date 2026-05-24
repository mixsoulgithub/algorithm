#include "graph.hpp"
#include <cstdint>
#include <gtest/gtest.h>
#include <sstream>
#include <vector>
#include <cstdio>
#include "graph_algorithm.hpp"
TEST(MatrixGraphTest, InsertNodes) {
  MatrixGraph<int,3> g(std::numeric_limits<int>::max(),false);
  EXPECT_EQ(g.insert_node(1), 1);
  EXPECT_EQ(g.insert_node(2), 2);
  EXPECT_EQ(g.insert_node(3), 3);
  EXPECT_EQ(g.size, 3);
}

TEST(MatrixGraphTest, GetNode) {
  MatrixGraph<int,3> g(std::numeric_limits<int>::max(),false);
  g.insert_node(10);
  g.insert_node(20);
  EXPECT_EQ(g.nodes[0], 10);
  EXPECT_EQ(g.nodes[1], 20);
}

TEST(MatrixGraphTest, VisitNodes) {
  MatrixGraph<int,4> g(std::numeric_limits<int>::max(),false);
  g.insert_node(1);
  g.insert_node(2);
  g.insert_node(3);

  std::vector<int> visited;
  g.visit_nodes([&](auto node) { if(visited.size()<g.size) visited.push_back(node); return true;});

  EXPECT_EQ(visited.size(), 3);
  EXPECT_EQ(visited, (std::vector<int>{1, 2, 3}));
}

TEST(MatrixGraphTest, DirectedFlag) {
  MatrixGraph<int, 2> g_true(std::numeric_limits<int>::max(),true);
  MatrixGraph<int, 1> g_false(std::numeric_limits<int>::max(),false);
  EXPECT_TRUE(g_true.directed);
  EXPECT_FALSE(g_false.directed);
}

TEST(MatrixGraphTest, EdgeInfoWithWeight) {
  MatrixGraph<int, 2,uint64_t, int> g(std::numeric_limits<int>::max(),false);
  g.insert_node(1);
  g.insert_node(2);
  g.insert_edge(0, 1, 42);

  EXPECT_EQ(g.edges[0][1], 42);
  // printf("g.edges = %d\n",g.edges[0][1]);
}

TEST(MatrixGraphTest, BFSTest) {
  MatrixGraph<int, 2> g(std::numeric_limits<int>::max(),false);
  g.insert_node(1);
  g.insert_node(2);
  g.insert_edge(0, 1, 42);

  bfs(g,0,[&](uint64_t node){
    printf("%x\n",node);
  });
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
