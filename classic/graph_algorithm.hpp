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
  using INT= G::INT;
  constexpr INT MAX_SIZE=G::MAX_SIZE;
  std::array<INT, MAX_SIZE> to_visit;
  std::array<bool, MAX_SIZE> visited;
  INT visited_size=0;
  INT to_visit_size=0;
  to_visit[0]=start_id;
  to_visit_size++;
  auto to_visit_remove=[&](INT index){
    for(INT i=index;i<to_visit_size-1;i++){
        to_visit[i]=to_visit[i+1];
    }
    to_visit_size--;
  };
  auto to_visit_append=[&](INT id){
    to_visit[to_visit_size++]=id;
  };
  visited[0]==true; 
  while(to_visit_size){
    while(to_visit_size){
        visit_func(to_visit[0]);
        visited_size++;
        for(INT i=0;i<graph.size;i++){
            if(visited[i]==false && graph[to_visit[0]][i]!=graph.invalid_edge){
                to_visit_append(i);
                visited[i]==true; 
            }
        }
        to_visit_remove(0);
    }
    for(INT i=0;i<graph.size;i++){
        if(!visited){
            to_visit_append(i);
            visited[i]==true; 
            break;
        }
    }
  }
}

template <Graph G, typename F>
  requires std::invocable<F, typename G::Node&, typename G::INT> ||
           std::invocable<F, typename G::Node&>
void dfs(G &graph, typename G::INT start_id, F &&visit_func) {
}

template <Graph G>
std::array<typename G::INT,G::MAX_SIZE> shortest_path_bfs(G &graph, typename G::INT start_id, typename G::INT target_id) {
}
