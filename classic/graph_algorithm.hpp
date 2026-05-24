#pragma once
#include "graph.hpp"
#include <cstdint>
#include <queue>
#include <type_traits>
#include <functional>
#include <algorithm>

template<typename G>
concept Graph = requires(G g) {
    typename G::INT;
    typename G::Node;
    { G::MAX_SIZE } -> std::convertible_to<int64_t>;
    typename G::EdgeInfo;
    
    { g.size } -> std::convertible_to<typename G::INT>;
    { g.directed } -> std::convertible_to<bool>;
    
    { g.insert_node(std::declval<typename G::Node>()) } -> std::convertible_to<typename G::INT>;
    { g.delete_node(std::declval<typename G::INT>()) } -> std::convertible_to<typename G::INT>;
    { g.insert_edge(std::declval<typename G::INT>(), std::declval<typename G::INT>(), std::declval<typename G::EdgeInfo>()) } -> std::same_as<void>;
    { g.get_node_id(std::declval<typename G::Node>()) } ->std::convertible_to<typename G::INT>;
};

template <Graph G, typename F>
  requires std::invocable<F, typename G::Node&, typename G::INT> ||
           std::invocable<F, typename G::Node&>
void bfs(G &graph, typename G::INT start_id, F &&visit_func) {
  using INT = typename G::INT;
  static constexpr INT MAX_SIZE = G::MAX_SIZE;
  std::array<INT, MAX_SIZE> to_visit;
  std::array<bool, MAX_SIZE> visited{};
  INT to_visit_size = 0;
  to_visit[0] = start_id;
  to_visit_size++;
  auto to_visit_remove = [&](INT index) {
    for (INT i = index; i < to_visit_size - 1; i++) {
      to_visit[i] = to_visit[i + 1];
    }
    to_visit_size--;
  };
  auto to_visit_append = [&](INT id) {
    to_visit[to_visit_size++] = id;
  };
  visited[start_id] = true;
  while (to_visit_size) {
    while (to_visit_size) {
      visit_func(graph.nodes[to_visit[0]]);
      for (INT i = 0; i < graph.size; i++) {
        if (visited[i] == false && graph.edges[to_visit[0]][i] != graph.invalid_edge) {
          to_visit_append(i);
          visited[i] = true;
        }
      }
      to_visit_remove(0);
    }
    for (INT i = 0; i < graph.size; i++) {
      if (!visited[i]) {
        to_visit_append(i);
        visited[i] = true;
        break;
      }
    }
  }
}

template <Graph G, typename F>
  requires std::invocable<F, typename G::Node&, typename G::INT> ||
           std::invocable<F, typename G::Node&>
void dfs(G &graph, typename G::INT start_id, F &&visit_func) {
  using INT = typename G::INT;
  static constexpr INT MAX_SIZE = G::MAX_SIZE;
  std::array<INT, MAX_SIZE> to_visit_i;//the next iterater begin need to be visited
  std::array<INT, MAX_SIZE> to_visit;
  std::array<bool, MAX_SIZE> visited{};
  INT to_visit_size = 0;
  auto remove = [&](INT index,std::array<INT, MAX_SIZE> arr, INT arr_size) {
    for (INT i = index; i < arr_size - 1; i++) {
      arr[i] = arr[i + 1];
    }
    arr_size--;
  };
  auto append = [&](INT id,std::array<INT, MAX_SIZE> arr, INT arr_size) {
    arr[arr_size++] = id;
  };
  visit_func(graph.nodes[start_id]);
  visited[start_id]=true;
  to_visit_i[to_visit_size]=0; //the index of start_id
  to_visit[to_visit_size++]=start_id;//infact is visited stack
  while (to_visit_size) {
    while (to_visit_size) {
       if(to_visit_i[to_visit_size-1]==graph.size){
            to_visit_size--;
       }
      for (INT i = to_visit_i[to_visit_size-1]; i < graph.size; i++) {
        if (visited[i] == false && graph.edges[to_visit[to_visit_size-1]][i] != graph.invalid_edge) {
          visit_func(graph.nodes[i]);
          visited[i]=true;
          append(i,to_visit,to_visit_size);
          to_visit_i[to_visit_size]=0;
          break;
        }
      }
    }
    for (INT i = 0; i < graph.size; i++) {
      if (!visited[i]) {
        visit_func(graph.nodes[i]);
        visited[i]=true;
        to_visit_i[to_visit_size]=0; //the index of start_id
        to_visit[to_visit_size++]=i;//infact is visited stack
        break;
      }
    }
  }

}

template <Graph G>
std::array<typename G::INT,G::MAX_SIZE> shortest_path_bfs(G &graph, typename G::INT start_id, typename G::INT target_id) {
}
