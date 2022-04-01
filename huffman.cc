#include "huffman.hh"
#include <cassert>

Huffman::Huffman() {
    frequency_table_[HEOF] = 1;
}

/*
*   Encode an ascii symbol by:
*       -Build new huffman tree from frequency list.
*       -Get the path to the input symbol.
*       -Create bit encoding from path representation*.
*   *Using LEFT = 0, RIGHT = 1.
*/
Huffman::bits_t
Huffman::encode(int symbol) {
    const auto L = HTree::Direction::LEFT;
    bits_t bit_encoding;

    //Build htree and get symbol path.
    HTree::tree_ptr_t htree = build_huffman_tree();
    HTree::possible_path_t path = htree->path_to(symbol);

    //Build bit-encoding from path.
    for (auto it = path->begin(); it != path->end(); it++) {
        if (*it == L) {
            bit_encoding.push_back(0);
        } else {
            bit_encoding.push_back(1);
        }
    }

    //Increment frequency table for symbol.
    frequency_table_[symbol]++;

    return bit_encoding;
}

int
Huffman::decode(bool bit) {
    
}

/*
* This function first creates a new hforest and adds all 257 possible
* characters to the hforest with their associated frequencies. Then
* iteratively merge HTrees in the forest until there is one tree left.
*/
HTree::tree_ptr_t
Huffman::build_huffman_tree() {    
    
    HForest hforest;
    //Iterate through every symbol in the alphabet and create 
    //a new HTree with key = (ascii) symbol, value = frequency.
    //Then, add this new tree to hforest.
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        hforest.add_tree(HTree::tree_ptr_t(new HTree(i, frequency_table_[i])));
    }

    while (hforest.size() > 1) {
        //Get the two least frequent symbols
        HTree::tree_ptr_t tree1 = hforest.pop_tree();
        HTree::tree_ptr_t tree2 = hforest.pop_tree();
        hforest.add_tree(HTree::tree_ptr_t(
            new HTree(
                -1, //Synthetic key for merged tree
                tree1->get_value() + tree2->get_value(), //Merged frequency is childs sum
                tree1,  //Left child is tree1
                tree2   //Right child is tree2
                )));
    }

    assert(hforest.size() == 1);        //Sanity check
    return hforest.pop_tree();
}

