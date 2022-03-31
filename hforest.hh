/*
 * HForest. A class that represents a collection of independent HTrees, where
            each HTree is the root of its own tree.
 */

#pragma once
#include <memory>
#include <vector>
#include <algorithm>
#include "htree.hh"

/*
Binary min-heap of pointers to HTRees.
Heap order is by root of each HTree.
*/
class HForest {
    public:
    /* Main types */
    using hforest_element_t = HTree::tree_ptr_t;
    using hforest_container_t = std::vector<hforest_element_t>;
    using hforest_t = std::shared_ptr<HForest>;
    using size_t = int;

    /* Constructor */
    HForest(hforest_container_t forest);

    /* Destructor */
    ~HForest() = default;

    /* Required Methods */
    size_t size() const;
    void add_tree(HTree::tree_ptr_t new_tree);
    hforest_element_t pop_tree();

    private:
    hforest_container_t forest_;

    struct compare_htrees;
    bool is_a_heap() const;
    void heapify();
};