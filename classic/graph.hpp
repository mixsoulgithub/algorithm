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
  bool directed;
  uint64_t nodes_num;
  EdgeInfo invalid_edge;
  // todo: if is not directed, use other structure to store node and edge, save
  // space
  std::vector<Node> nodes;
  static constexpr bool is_simple_edge = std::is_same_v<EdgeInfo, bool>;
  using INT = uint64_t;


  std::vector<std::vector<EdgeInfo>> edges;

  MatrixGraph(EdgeInfo invalid_edge, bool d = false)
      : invalid_edge(invalid_edge), directed(d), nodes_num(0)
        {
  }

  INT insert_node(Node node) {
    nodes.push_back(node);
    return nodes.size();
  }
  
  bool delete_node(std::vector<INT> nodes_index) {
    // trade off of lazy delete(this need)
    INT size=nodes.size();
    std::vector<bool> node_bitmap(size);
    for(auto i:nodes_index){
      node_bitmap[i]=true;
    }
    INT offset=0;
    for(INT i=0;i<size;){
      if(node_bitmap[i]==true){
        offset++;
      }
      if(!offset){
        nodes[i]=nodes[i+offset];
        edges[i]=edges[i+offset];
      }
    }

  }

  void insert_edge(INT from, INT to, EdgeInfo info) {
    if constexpr (is_simple_edge) {
      edges[from][to] = 0b1;
    } else {
      edges[from][to] = info;
    }
  }

  Node &get_node(INT id) { return nodes[id]; }
  INT get_node_id(Node node) {
    INT i = 0;
    for (auto &&cur : nodes) {
      if (cur == node) {
        return i;
      }
      i++;
    }
  }
  bool is_directed() { return directed; }

  template <typename F>
    requires std::invocable<F, Node>
  void visit_nodes(F &&func) {
    for (uint64_t i = 0; i < nodes_num; i++) {
      if (!func(nodes[i])) {
        return;
      }
    }
  }

  EdgeInfo get_edge(INT from, INT to) { return edges[from][to]; }
};

// 为你的图特化
#endif
