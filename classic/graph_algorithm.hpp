#pragma once
#include "graph.hpp"
#include <queue>
#include <vector>
#include <type_traits>
#include <functional>
#include <algorithm>

template<typename G>
concept Graph = requires(G g) {
    typename G::INT;
    typename G::Node;
    typename G::EdgeInfo;
    typename G::node_type;
    typename G::edge_type;
    
    { g.nodes_count() } -> std::convertible_to<typename G::INT>;
    { g.is_directed() } -> std::convertible_to<bool>;
    
    { g.insert_node(std::declval<typename G::Node>()) } -> std::convertible_to<typename G::INT>;
    { g.get_node(std::declval<typename G::INT>()) } -> std::same_as<typename G::Node&>;
    { g.get_neighbors(std::declval<typename G::INT>()) } -> std::same_as<std::vector<typename G::INT>>;
    { g.has_edge(std::declval<typename G::INT>(), std::declval<typename G::INT>()) } -> std::same_as<bool>;
    { g.insert_edge(std::declval<typename G::INT>(), std::declval<typename G::INT>(), std::declval<typename G::EdgeInfo>()) } -> std::same_as<void>;
    { g.get_edge(std::declval<typename G::INT>(), std::declval<typename G::INT>()) } -> std::same_as<typename G::EdgeInfo>;
};

template <Graph G, typename F>
  requires std::invocable<F, typename G::Node&, typename G::INT> ||
           std::invocable<F, typename G::Node&>
void bfs(G &graph, typename G::INT start_id, F &&visit_func) {
    using Node = typename G::Node;
    using INT = typename G::INT;
    
    INT node_count = graph.nodes_count();
    if (start_id >= node_count) return;
    
    std::vector<bool> visited(node_count, false);
    std::queue<INT> q;
    
    q.push(start_id);
    visited[start_id] = true;
    
    while (!q.empty()) {
        INT current_id = q.front();
        q.pop();
        
        Node &current_node = graph.get_node(current_id);
        
        if constexpr (std::is_invocable_v<F, Node&, INT>) {
            std::invoke(visit_func, current_node, current_id);
        } else {
            std::invoke(visit_func, current_node);
        }
        
        std::vector<INT> neighbors = graph.get_neighbors(current_id);
        for (INT neighbor_id : neighbors) {
            if (!visited[neighbor_id]) {
                visited[neighbor_id] = true;
                q.push(neighbor_id);
            }
        }
    }
}

template <Graph G, typename F>
  requires std::invocable<F, typename G::Node&, typename G::INT> ||
           std::invocable<F, typename G::Node&>
void dfs(G &graph, typename G::INT start_id, F &&visit_func) {
    using Node = typename G::Node;
    using INT = typename G::INT;
    
    INT node_count = graph.nodes_count();
    if (start_id >= node_count) return;
    
    std::vector<bool> visited(node_count, false);
    
    auto dfs_helper = [&](auto &&self, INT current_id) -> void {
        visited[current_id] = true;
        
        Node &current_node = graph.get_node(current_id);
        
        if constexpr (std::is_invocable_v<F, Node&, INT>) {
            std::invoke(visit_func, current_node, current_id);
        } else {
            std::invoke(visit_func, current_node);
        }
        
        std::vector<INT> neighbors = graph.get_neighbors(current_id);
        for (INT neighbor_id : neighbors) {
            if (!visited[neighbor_id]) {
                self(self, neighbor_id);
            }
        }
    };
    
    dfs_helper(dfs_helper, start_id);
}

template <Graph G>
std::vector<typename G::INT> shortest_path_bfs(G &graph, typename G::INT start_id, typename G::INT target_id) {
    using INT = typename G::INT;
    
    INT node_count = graph.nodes_count();
    if (start_id >= node_count || target_id >= node_count) return {};
    
    std::vector<bool> visited(node_count, false);
    std::vector<INT> parent(node_count, static_cast<INT>(-1));
    std::queue<INT> q;
    
    q.push(start_id);
    visited[start_id] = true;
    
    while (!q.empty()) {
        INT current_id = q.front();
        q.pop();
        
        if (current_id == target_id) {
            std::vector<INT> path;
            for (INT cur = target_id; cur != static_cast<INT>(-1); cur = parent[cur]) {
                path.push_back(cur);
            }
            std::reverse(path.begin(), path.end());
            return path;
        }
        
        std::vector<INT> neighbors = graph.get_neighbors(current_id);
        for (INT neighbor_id : neighbors) {
            if (!visited[neighbor_id]) {
                visited[neighbor_id] = true;
                parent[neighbor_id] = current_id;
                q.push(neighbor_id);
            }
        }
    }
    
    return {};
}
