/*
 * Huffman: a class to encode and decode symbols based on adaptive Huffman coding
 * https://en.wikipedia.org/wiki/Huffman_coding
 */

#pragma once

#include <climits>
#include <vector>

#include "htree.hh"
#include "hforest.hh"

class Huffman {
 public:
  // Maximum number of symbols we need to encode (a symbol fits in a char) + EOF
  static const int ALPHABET_SIZE = (1 << CHAR_BIT) + 1;  // (2 ** 8) + 1
  static const int HEOF = ALPHABET_SIZE - 1;  // Special symbol to denote end of file

  using bits_t = std::vector<bool>;

  Huffman();
  ~Huffman() = default;
  Huffman(const Huffman&) = delete;
  Huffman(Huffman&&) = delete;
  Huffman& operator=(const Huffman&) = delete;
  Huffman& operator=(Huffman&&) = delete;

  // Encode a symbol into a sequence of bits, then update frequency table.
  bits_t encode(int symbol);

  // Decode a single bit into a symbol. If no symbol can be unambiguously decoded
  // without additional bits, returns a negative value.
  // Subsequent calls with more bits should eventually resolve to either
  // a character symbol or HEOF.
  // Finally, updates the frequency table with this additional symbol.
  int decode(bool bit);

  private:
  int frequency_table_[ALPHABET_SIZE] = {};                             //Frequency table is initially all zeroes, set HEOF to 1 in constructor.
  HTree::tree_ptr_t build_huffman_tree_();                              //Build a Huffman tree from scratch.
  HTree::tree_ptr_t bit_to_child_(HTree::tree_ptr_t node, int bit);     //Helper function to advance through htree from single bit.
  HTree::tree_ptr_t tmp_node_ = nullptr;                                //Maintain state for decode operation. Initially nullptr (start from root).
};
