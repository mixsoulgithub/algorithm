#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>

#include <array>
#include <bitset>
#include <concepts>
#include <cstdint>
#include <stdexcept>
#include <type_traits>

template <typename Node, typename EdgeInfo = bool>
  requires std::equality_comparable<Node> && std::equality_comparable<EdgeInfo>
struct MatrixGraph {
  using node_type = Node;
  using edge_type = EdgeInfo;
  using INT = uint64_t;

  bool directed;
  EdgeInfo invalid_edge;
  std::vector<Node> nodes;
  std::vector<std::vector<EdgeInfo>> edges;

  static constexpr bool is_simple_edge_v = std::is_same_v<EdgeInfo, bool>;

  MatrixGraph(EdgeInfo invalid_edge, bool d = false)
      : invalid_edge(invalid_edge), directed(d) {
  }

  INT insert_node(Node node) {
    nodes.push_back(node);
    INT new_size = nodes.size();
    for (auto &row : edges) {
      row.resize(new_size, invalid_edge);
    }
    edges.resize(new_size, std::vector<EdgeInfo>(new_size, invalid_edge));
    return new_size - 1;
  }

  bool delete_node(std::vector<INT> nodes_index) {
    if (nodes_index.empty()) return false;
    
    INT size = nodes.size();
    std::vector<bool> node_bitmap(size, false);
    for (auto i : nodes_index) {
      if (i < size) node_bitmap[i] = true;
    }

    std::vector<Node> new_nodes;
    std::vector<std::vector<EdgeInfo>> new_edges;
    std::vector<INT> old_to_new(size, 0);

    for (INT i = 0; i < size; i++) {
      if (!node_bitmap[i]) {
        old_to_new[i] = new_nodes.size();
        new_nodes.push_back(nodes[i]);
      }
    }

    for (INT i = 0; i < size; i++) {
      if (!node_bitmap[i]) {
        std::vector<EdgeInfo> new_row;
        for (INT j = 0; j < size; j++) {
          if (!node_bitmap[j]) {
            new_row.push_back(edges[i][j]);
          }
        }
        new_edges.push_back(std::move(new_row));
      }
    }

    nodes = std::move(new_nodes);
    edges = std::move(new_edges);
    return true;
  }

  void insert_edge(INT from, INT to, EdgeInfo info) {
    if (from >= nodes.size() || to >= nodes.size()) return;
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

  Node &get_node(INT id) { return nodes[id]; }
  const Node &get_node(INT id) const { return nodes[id]; }

  INT get_node_id(Node node) const {
    for (INT i = 0; i < nodes.size(); i++) {
      if (nodes[i] == node) {
        return i;
      }
    }
    return static_cast<INT>(-1);
  }

  bool is_directed() const { return directed; }
  INT nodes_count() const { return nodes.size(); }

  template <typename F>
    requires std::invocable<F, Node&>
  void visit_nodes(F &&func) {
    for (auto &node : nodes) {
      func(node);
    }
  }

  template <typename F>
    requires std::invocable<F, const Node&>
  void visit_nodes(F &&func) const {
    for (const auto &node : nodes) {
      func(node);
    }
  }

  EdgeInfo get_edge(INT from, INT to) const {
    if (from >= edges.size() || to >= edges[from].size()) {
      return invalid_edge;
    }
    return edges[from][to];
  }

  bool has_edge(INT from, INT to) const {
    if constexpr (is_simple_edge_v) {
      return get_edge(from, to);
    } else {
      return get_edge(from, to) != invalid_edge;
    }
  }

  std::vector<INT> get_neighbors(INT node_id) const {
    std::vector<INT> neighbors;
    if (node_id >= edges.size()) return neighbors;
    for (INT i = 0; i < edges[node_id].size(); i++) {
      if (has_edge(node_id, i)) {
        neighbors.push_back(i);
      }
    }
    return neighbors;
  }
};

// 为你的图特化
#endif
