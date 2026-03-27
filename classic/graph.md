# Graph Data Structure Design Advice

## Strengths

1. **Modern C++23 features**: Good use of concepts, requires clauses, and `if constexpr` for compile-time optimization
2. **Memory efficiency**: Uses `bitset` for simple boolean edges, saving memory
3. **Type safety**: Template parameters allow flexible node and edge types
4. **Simple API**: `insert_node`, `insert_edge`, `visit_nodes`, `visit_edges` are intuitive

## Issues Found

### Critical Bugs

1. **visit_nodes iterates full array**: Fixed - was iterating `MAX_NODE_NUM` instead of `nodes_num`
2. **visit_edges may access uninitialized memory**: Should only iterate up to `nodes_num`
3. **No edge existence check**: `insert_edge` doesn't verify nodes exist
4. **Directed graph flag unused**: `directed` member is never initialized or used

### Design Concerns

1. **Fixed size at compile time**: `MAX_NODE_NUM` must be known at compile time. Consider dynamic allocation for flexibility
2. **O(MAX_NODE_NUM²) memory**: Adjacency matrix wastes memory for sparse graphs. Consider adjacency list
3. **Node lookup by value missing**: No method to find node ID by value
4. **No bounds checking**: `insert_node` can overflow if called more than `MAX_NODE_NUM` times
5. **Edge iteration unclear**: `visit_edges` compares against default-constructed `EdgeInfo` which may be unreliable

## Recommendations

### Short-term Fixes

```cpp
// Add bounds checking
INT insert_node(Node node) {
    if (nodes_num >= MAX_NODE_NUM) {
        throw std::overflow_error("Graph full");
    }
    nodes[nodes_num] = node;
    return nodes_num++;
}

// Fix visit_edges bounds
void visit_edges(F &&func) {
    for (INT from = 0; from < nodes_num; from++) {
        for (INT to = 0; to < nodes_num; to++) {
            // ... rest of logic
        }
    }
}
```

### Long-term Improvements

1. **Use `std::vector`** for dynamic sizing or document the limitation clearly
2. **Add adjacency list** representation for sparse graphs (O(V+E) vs O(V²))
3. **Initialize `directed`** in constructor: `Graph(bool d = false) : directed(d), nodes_num{} {}`
4. **Add `has_edge(from, to)`** query method
5. **Add `remove_node(id)`** and `remove_edge(from, to)` methods
6. **Consider separate Node/Edge ID types** to prevent mixing up indices

## Usage Notes

- Best for **dense graphs** with known maximum size
- Edge iteration is O(V²) regardless of actual edge count
- Node IDs are 0-indexed based on insertion order
