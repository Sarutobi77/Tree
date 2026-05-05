//tree/linked_binary_tree.hpp
#pragma once

#include <iostream>
#include <vector>
#include <queue>
#include <stdexcept>

#include "tree_traversal.hpp"

namespace dsac::tree {

template <typename E>
class LinkedBinaryTree {
    protected:
        class Node {
            public:
                E element;
                Node* parent;
                Node* left{nullptr};
                Node* right{nullptr};
                Node(E e, Node* p = nullptr) : element{e}, parent{p} {}
        }; // end of Node class

    protected:
        Node* rt{nullptr}; // root
        int sz{0};         // size

    public:
        class Position {
            private:
                Node* node;
                friend class LinkedBinaryTree;
            public:
                Position(Node* nd = nullptr) : node{nd} {}

                bool operator==(Position other) const { return node == other.node; }
                bool operator!=(Position other) const { return node != other.node; }
                bool is_null() const { return node == nullptr; }
                bool is_root() const { return node != nullptr && node->parent == nullptr; }
                bool is_external() const { return node != nullptr && node->left == nullptr && node->right == nullptr; }
                
                E& element() { return node->element; }
                const E& element() const { return node->element; }

                Position parent() const { return Position(node->parent); }
                Position left() const { return Position(node->left); }
                Position right() const { return Position(node->right); }
                
                std::vector<Position> children() const {
                    std::vector<Position> c;
                    if (node->left != nullptr) c.push_back(Position(node->left));
                    if (node->right != nullptr) c.push_back(Position(node->right));
                    return c;
                }

                int num_children() const {
                    int count = 0;
                    if (node->left != nullptr) count++;
                    if (node->right != nullptr) count++;
                    return count;
                }
        };  // end of Position class

        LinkedBinaryTree() = default;

        int size() const { return sz; }
        bool empty() const { return sz == 0; }
        Position root() const { return Position(rt); }

        std::vector<Position> positions() const {
            std::vector<Position> res;
            if (!empty()) {
                inorder(root(), res);
            }
            return res;
        }

        void add_root(const E& e = E()) {
            if (!empty()) throw std::runtime_error("Tree is not empty");
            rt = new Node(e);
            sz = 1;
        }

        void add_left(Position p, const E& e) {
            if (p.left().node != nullptr) throw std::runtime_error("Left child already exists");
            p.node->left = new Node(e, p.node);
            sz++;
        }

        void add_right(Position p, const E& e) {
            if (p.right().node != nullptr) throw std::runtime_error("Right child already exists");
            p.node->right = new Node(e, p.node);
            sz++;
        }

        void erase(Position p) {
            if (p.is_null()) throw std::invalid_argument("Position is null");
            Node* nd = p.node;
            if (nd->left != nullptr && nd->right != nullptr) {
                throw std::runtime_error("Cannot erase a node with two children");
            }
            Node* child = (nd->left != nullptr) ? nd->left : nd->right;
            if (child != nullptr) child->parent = nd->parent;
            
            if (nd == rt) {
                rt = child;
            } else {
                Node* parent = nd->parent;
                if (nd == parent->left) parent->left = child;
                else parent->right = child;
            }
            sz--;
            delete nd;
        }

        void attach(Position p, LinkedBinaryTree& left, LinkedBinaryTree& right) {
            if (!p.is_external()) throw std::runtime_error("Position must be a leaf");
            sz += left.sz + right.sz;
            if (!left.empty()) {
                p.node->left = left.rt;
                left.rt->parent = p.node;
                left.rt = nullptr;
                left.sz = 0;
            }
            if (!right.empty()) {
                p.node->right = right.rt;
                right.rt->parent = p.node;
                right.rt = nullptr;
                right.sz = 0;
            }
        }

    private:
        void tear_down(Node* nd) {
            if (nd != nullptr) {
                tear_down(nd->left);
                tear_down(nd->right);
                delete nd;
            }
        }

        static Node* clone(Node* model) {
            if (model == nullptr) return nullptr;
            Node* copy = new Node(model->element);
            copy->left = clone(model->left);
            if (copy->left != nullptr) copy->left->parent = copy;
            copy->right = clone(model->right);
            if (copy->right != nullptr) copy->right->parent = copy;
            return copy;
        }

    public:
        ~LinkedBinaryTree() { tear_down(rt); }
        
        LinkedBinaryTree(const LinkedBinaryTree& other) {
            rt = clone(other.rt);
            sz = other.sz;
        }

        LinkedBinaryTree& operator=(const LinkedBinaryTree& other) {
            if (this != &other) {
                tear_down(rt);
                rt = clone(other.rt);
                sz = other.sz;
            }
            return *this;
        }

        LinkedBinaryTree(LinkedBinaryTree&& other) {
            rt = other.rt;
            sz = other.sz;
            other.rt = nullptr;
            other.sz = 0;
        }

        LinkedBinaryTree& operator=(LinkedBinaryTree&& other) {
            if (this != &other) {
                tear_down(rt);
                rt = other.rt;
                sz = other.sz;
                other.rt = nullptr;
                other.sz = 0;
            }
            return *this;
        }

    // Assignment specific functions
    public:
        int count_left_leaves() const {
            if (empty()) return 0;
            int count = 0;
            
            // Internal recursive lambda helper
            auto helper = [&](auto& self, Node* n) -> void {
                if (n == nullptr) return;
                
                if (n->left != nullptr) {
                    // Check if the left child is a leaf
                    if (n->left->left == nullptr && n->left->right == nullptr) {
                        count++;
                    }
                    self(self, n->left);
                }
                
                if (n->right != nullptr) {
                    self(self, n->right);
                }
            };
            
            helper(helper, rt);
            return count;
        }

        int count_left_leaves_bfs() const {
            if (empty()) return 0;
            int count = 0;
            std::queue<Node*> q;
            q.push(rt);
            
            while (!q.empty()) {
                Node* curr = q.front();
                q.pop();
                
                if (curr->left != nullptr) {
                    // Check if the left child is a leaf
                    if (curr->left->left == nullptr && curr->left->right == nullptr) {
                        count++;
                    }
                    q.push(curr->left);
                }
                
                if (curr->right != nullptr) {
                    q.push(curr->right);
                }
            }
            return count;
        }
};

} // namespace dsac::tree