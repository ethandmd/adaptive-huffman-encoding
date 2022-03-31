/*
    Unit test for the HForest class.
*/

#include "hforest.hh"
#include <cassert>
#include <iostream>

using namespace std;

HForest::hforest_t create_test_hforest()
{
    cout << "Creating test forest...\n";
    /*
    *   Values in tree are :
    *       [5, 23, 2]
    */
    HForest::hforest_container_t forest = {
        make_shared<HTree>(126, 5),
        make_shared<HTree>(101, 23,
            make_shared<HTree>(-99, 2)),
        make_shared<HTree>(13, 2),
    };

    return make_shared<HForest>(forest);
}

void test_hforest(const HForest::hforest_t forest) 
{
    cout << "Testing size...\n";
    assert(forest->size() == 3);        //Initial size from constructor.

    cout << "Testing popping min value (root)...\n";
    assert((forest->pop_tree())->get_value() == 2);     //Check that popped tree is 'smallest' in heap.
    assert(forest->size() == 2);                        //Check that internal vector has been decremented.
    assert((forest->pop_tree())->get_value() == 5);     //Do it again.
    assert(forest->size() == 1);
    assert((forest->pop_tree())->get_value() == 23);
    assert((forest->size() == 0));
    assert(forest->pop_tree() == nullptr);              //Pop on empty tree gives null ptr.

    cout << "Testing adding new tree...\n";
    HTree::tree_ptr_t t1 = make_shared<HTree>(666, 29,
        make_shared<HTree>(111, 3, nullptr,
            make_shared<HTree>(888, 11))
    );
    forest->add_tree(t1);
    assert(forest->size() == 1);        //Check that size increased after adding a new tree.

    HTree::tree_ptr_t t2 = make_shared<HTree>(33, 13);
    forest->add_tree(t2);
    assert(forest->size() == 2);

    assert(forest->pop_tree()->get_value() == 13);

    cout << "Finished all tests.\n";
}


int main() {
    auto forest = create_test_hforest();
    test_hforest(forest);
}