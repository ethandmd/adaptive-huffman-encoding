/*
 * HTree: a class to represent a tree node with two values: a key
 * and a value.
 */

#include "htree.hh"

// Return an optional list of directions from root to a node of a given key.
// If key not contained in this tree, returns nullptr.
HTree::possible_path_t
HTree::path_to(key_t key) const
{
  //If current node is target key, return unique ptr to empty list.
  if (key == key_) {
    //Create an empty list
    path_t search_list =  {};
    return std::make_unique<path_t>(search_list);
  }

  //If this node is a leaf return nullptr.
  // if (!left_ && !right_) {
  //  return nullptr;
  //} 

  //If left child is not nullptr,
  //recurse down left subtree.
  if (left_) {
    auto left_result = left_->path_to(key);
    if (left_result) {
      left_result->push_front(Direction::LEFT);   //If result is not nullptr, append direction and return.
      return left_result;
    }
  }

  //If right child is not nullptr,
  //recurse down right subtree.
  if (right_) {
    auto right_result = right_->path_to(key);
    //If result is nullptr, the key is not in the tree,
    //return nullptr.
    if (!right_result) {
      return nullptr;
    } else {
      right_result->push_front(Direction::RIGHT);
      return right_result;
    }
    //If right child is nullptr, search has hit a leaf. Return nullptr.
  } else {
    return nullptr;
  }
}

HTree::tree_ptr_t
HTree::get_child(Direction dir) const
{
  if (dir == Direction::LEFT) {
    return left_;
  } else {
    return right_;
  }
}
