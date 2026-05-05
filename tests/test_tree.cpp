// tests/test_tree.cpp
#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "tree/linked_binary_tree.hpp"

using namespace dsac::tree;

TEST_CASE("LinkedBinaryTree_Functionality", "[LinkedBinaryTree]") {
    LinkedBinaryTree<int> tree;

    tree.add_root(10);
    auto root = tree.root();
    
    tree.add_left(root, 5);
    tree.add_right(root, 15);
    
    tree.add_left(root.left(), 2);
    tree.add_right(root.left(), 7);
    
    tree.add_left(root.right(), 12);
    tree.add_right(root.right(), 20);

    SECTION("Positions_Returns_All_Positions_Using_Inorder_Traversal") {
        std::vector<LinkedBinaryTree<int>::Position> pos = tree.positions();
        
        REQUIRE(pos.size() == 7);
        
        // Expected inorder sequence: 2, 5, 7, 10, 12, 15, 20
        REQUIRE(pos[0].element() == 2);
        REQUIRE(pos[1].element() == 5);
        REQUIRE(pos[2].element() == 7);
        REQUIRE(pos[3].element() == 10);
        REQUIRE(pos[4].element() == 12);
        REQUIRE(pos[5].element() == 15);
        REQUIRE(pos[6].element() == 20);
    }

    SECTION("Count_Left_Leaves_Counts_Left_Leaves_Recursively") {
        // Leaves are 2, 7, 12, 20.
        // Out of those, the left leaves are 2 and 12.
        REQUIRE(tree.count_left_leaves() == 2);
    }

    SECTION("Count_Left_Leaves_BFS_Counts_Left_Leaves_Using_Breadth_First_Search") {
        REQUIRE(tree.count_left_leaves_bfs() == 2);
    }
    
    SECTION("Empty_Tree_Edge_Case") {
        LinkedBinaryTree<int> empty_tree;
        REQUIRE(empty_tree.count_left_leaves() == 0);
        REQUIRE(empty_tree.count_left_leaves_bfs() == 0);
        REQUIRE(empty_tree.positions().empty() == true);
    }
}