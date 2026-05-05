//tree_traversal.hpp
#pragma once
#include "linked_binary_tree.hpp"
#include <queue>
#include <deque>

namespace dsac::tree {

template <typename Position, typename Container>
void preorder(Position p, Container& visited) {
    if (p.is_null()) return;
    visited.push_back(p);
    if (!p.left().is_null()) preorder(p.left(), visited);
    if (!p.right().is_null()) preorder(p.right(), visited);
}

template <typename Position, typename Container>
void postorder(Position p, Container& visited) {
    if (p.is_null()) return;
    if (!p.left().is_null()) postorder(p.left(), visited);
    if (!p.right().is_null()) postorder(p.right(), visited);
    visited.push_back(p);
}

template <typename Position, typename Container>
void breadthfirst(Position p, Container& visited) {
    if (p.is_null()) return;
    std::queue<Position> q;
    q.push(p);
    while (!q.empty()) {
        Position curr = q.front();
        q.pop();
        visited.push_back(curr);
        if (!curr.left().is_null()) q.push(curr.left());
        if (!curr.right().is_null()) q.push(curr.right());
    }
}

template <typename Position>
std::queue<Position> breadthfirst_2(Position p) {
    std::queue<Position> res;
    if (p.is_null()) return res;
    std::queue<Position> q;
    q.push(p);
    while (!q.empty()) {
        Position curr = q.front();
        q.pop();
        res.push(curr);
        if (!curr.left().is_null()) q.push(curr.left());
        if (!curr.right().is_null()) q.push(curr.right());
    }
    return res;
}

template <typename Position, typename Container>
void inorder(Position p, Container& visited) {
    if (p.is_null()) return;
    if (!p.left().is_null()) inorder(p.left(), visited);
    visited.push_back(p);
    if (!p.right().is_null()) inorder(p.right(), visited);
}

} // end namespace dsac::tree