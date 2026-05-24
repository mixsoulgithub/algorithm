#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <array>
#include <bitset>
#include <cassert>
#include <concepts>
#include <cstdint>
#include <stdexcept>
#include <type_traits>

template <typename Node, int64_t MAX_SIZE, typename INT = uint64_t,
          typename EdgeInfo = bool>
requires std::equality_comparable<Node> && std::equality_comparable<EdgeInfo>
struct MatrixGraph {
public:
  bool directed;
  INT size;
  EdgeInfo invalid_edge;
  std::array<Node, MAX_SIZE> nodes;
  std::array<std::array<EdgeInfo, MAX_SIZE>, MAX_SIZE> edges;

  static constexpr bool is_simple_edge_v = std::is_same_v<EdgeInfo, bool>;

  MatrixGraph(EdgeInfo invalid, bool d = false)
      : size(0), directed(d), invalid_edge(invalid) {
    for (INT i = 0; i < MAX_SIZE; i++) {
      for (INT j = 0; i < MAX_SIZE; i++) {
        edges[i][j] = invalid_edge;
      }
    }
  }

  INT insert_node(Node node) {
    assert(size <= MAX_SIZE);
    nodes[size] = node;
    size++;
    return size;
  }
  // if we want array, it will cause code bloat, although for every number
  // it will have better perf, but the size can be very large
  INT delete_node(INT index) {
    assert(index >= 0 && index < size);
    for (INT i = index; i < size - 1; i++) {
      nodes[i] = nodes[i + 1];
    }
    size--;
    return size;
  }

  void insert_edge(INT from, INT to, EdgeInfo info) {
    assert(from >= 0 && from < size);
    assert(to >= 0 && to < size);
    if constexpr (is_simple_edge_v) {
      edges[from][to] = EdgeInfo{true};
    } else {
      edges[from][to] = info;
    }
    if (!directed) {
      if constexpr (is_simple_edge_v) {
        edges[to][from] = EdgeInfo{true};
      } else {
        edges[to][from] = info;
      }
    }
  }

  INT get_node_id(Node node) const {
    for (INT i = 0; i < size; i++) {
      if (nodes[i] == node) {
        return i;
      }
    }
    assert(false);
  }

  template <typename F>
  requires std::invocable<F, Node &>
  void visit_nodes(F &&func) {
    for (auto &node : nodes) {
      func(node);
    }
  }
};

// 为你的图特化
#endif
