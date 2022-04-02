#include "hforest.hh"
#include <cassert>
#include <iostream>

/*
*   std::make_heap() expects a compare function that will return a bool-convertible
*   type indicating if A is < B to create a max-heap. Inverting this logic, we get
*   a min-heap.
*/
struct 
HForest::compare_htrees{
    bool operator() (const hforest_element_t tree_a, const hforest_element_t tree_b) const
    {
        return tree_a->get_value() > tree_b->get_value();
    }
};

/*
*   Private helper function that relies on std::is_heap().
*/
bool
HForest::is_a_heap() const
{
    return std::is_heap(forest_.begin(), forest_.end(), compare_htrees{});
}

HForest::size_t
HForest::size() const 
{
    assert(is_a_heap());
    return forest_.size();
}

void
HForest::add_tree(HTree::tree_ptr_t new_tree)
{
    //Ensure new_tree is not nullptr.
    if (!new_tree) { return; }
    //Add ptr to new tree at the end of the vector.
    forest_.push_back(new_tree);
    //Call push_heap() to maintain min-heap invariant.
    std::push_heap(forest_.begin(), forest_.end(), compare_htrees{});
}

HTree::tree_ptr_t
HForest::pop_tree()
{
    //Safety check that the heap is not empty.
    if (size() < 1) { return nullptr; }

    //Get the root of the heap (min valued tree) from front of vector.
    HTree::tree_ptr_t target = forest_.front();
    //Remove this tree from the heap.
    std::pop_heap(forest_.begin(), forest_.end(), compare_htrees{});
    //Remove this tree from the vector.
    forest_.pop_back();
    
    return target;
}