#pragma once
#include "graph.hpp"

template<typename G>
concept Graph = requires(G g) {
    // Type requirements
    typename G::INT;
    typename G::Node;
    typename G::EdgeInfo;
    
    // Property access
    { g.nodes_num } -> std::convertible_to<uint64_t>;
    { g.directed } -> std::convertible_to<bool>;
    
    // Node operations
    { g.insert_node(std::declval<typename G::Node>()) } -> std::convertible_to<typename G::INT>;
    { g.delete_node(std::declval<typename G::Node>()) } -> std::convertible_to<typename G::INT>;
    { g.get_node(std::declval<typename G::INT>()) } -> std::same_as<typename G::Node&>;
    
    // Edge operations
    { g.insert_edge(std::declval<typename G::INT>(), std::declval<typename G::INT>(), std::declval<typename G::EdgeInfo>()) } -> std::same_as<void>;
    { g.delete_edge(std::declval<typename G::INT>(), std::declval<typename G::INT>(), std::declval<typename G::EdgeInfo>()) } -> std::same_as<void>;
    { g.get_edge(std::declval<typename G::INT>(), std::declval<typename G::INT>()) } -> std::same_as<typename G::EdgeInfo>;
    
    // Traversal
    g.visit_nodes([](typename G::Node&){});
};


template <Graph G>
void bfs(G graph){
    auto first=graph.get_node();
}