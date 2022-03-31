/*
 * test_tree: A simple unit test for the Tree data structure.
 */

#include "htree.hh"
#include <cassert>
#include <iostream>

using namespace std;

// Create example test tree:
HTree::tree_ptr_t create_test_tree()
{
  std::cout << "Creating test htree...\n";
  HTree::tree_ptr_t left_subtree = make_shared<HTree>(-5, 1, make_shared<HTree>(12, 1), make_shared<HTree>(6,99, make_shared<HTree>(9,1)));
  HTree::tree_ptr_t right_subtree = make_shared<HTree>(12,1, make_shared<HTree>(3,1));

  return make_shared<HTree>(126, 1, left_subtree, right_subtree);
}

void test_htree(const HTree::tree_ptr_t root)
{
  cout << "Testing paths for htree...\n";
  /* 
  * path_to() tests
  */ 
  assert(*(root->path_to(126)) == HTree::path_t({ }));     //Path to root is empty list
  assert(*(root->path_to(9)) == HTree::path_t({
    HTree::Direction::LEFT,
    HTree::Direction::RIGHT,
    HTree::Direction::LEFT}));                             //Path from root to "9"
  assert(*(root->path_to(3)) == HTree::path_t({
    HTree::Direction::RIGHT,
    HTree::Direction::LEFT}));
  assert(*(root->path_to(12)) == HTree::path_t({
    HTree::Direction::LEFT,
    HTree::Direction::LEFT}));                             //Path to key "12" is the left most path
  assert(root->path_to(1) == nullptr);                     //Nonexistant path returns nullptr

  cout << "Testing accessors for htree...\n";
  /*
  * Accessor tests
  */
  assert(root->get_child(HTree::Direction::LEFT)->get_key() == -5);   //Root's left child is "-5".
  assert((root->get_child(HTree::Direction::RIGHT))->get_key() == 12);    //Assert that right child of the root has key "12"
  assert((root->get_child(HTree::Direction::LEFT)->get_child(HTree::Direction::RIGHT))->get_value() == 99);   //From root, go left then right to node with key "6". Assert this node has value 99.
  assert((root->get_child(HTree::Direction::RIGHT)->get_child(HTree::Direction::LEFT))->get_key() == 3);    //Assert that right most leaf is "3"

  HTree::tree_ptr_t left_twelve = root->get_child(HTree::Direction::LEFT)->get_child(HTree::Direction::LEFT);     //Get key "12".
  assert(left_twelve->get_child(HTree::Direction::LEFT) == nullptr);                                              //Check that it's children are nullptr.

  cout << "Finished all unit tests for htree.\n";
}

int main()
{
  auto root = create_test_tree();
  test_htree(root);
  return 0;
}

