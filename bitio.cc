#include "bitio.hh"
#include <cassert>
#include <iostream>

BitOutput::~BitOutput() {
    /*
    while (bit_count_ <= 7) {
        output_bit(0);
    }
    */
   os_.put(buff_);
}

/*
*   Debugging.
*/
void get_buff(uint8_t buff) { 
    std::cout << "Printing in bits for, " << int(buff) << ": ";
    for (int i = 7; i > -1; i--) { 
      bool k = buff & (0x1 << i);
      std::cout << k << " ";
      }
      std::cout << "\n";
    }

bool
BitInput::input_bit() {
    //Bit count ranges from [0,8). If bit count is > 7, read in next byte from stream.
    if (bit_count_ > 7) {
        buff_ = is_.get();
        //get_buff(buff_);                  //Visualize the bits.
        bit_count_ = 0;
    }

    bool k = buff_ & (0x1 << bit_count_);   //Extract LSB from char buffer.
    bit_count_ += 1;                        //Increment bit counter.
    return k;
}

void
toggle_bit(uint8_t &buff, bool bit, int k) {
    if (bit) {
        buff |= 0x1 << k;       //Set the k-th bit.
    } else {
        buff &= ~(0x1 << k);    //Clear the k-th bit.
    }
}

void
BitOutput::output_bit(bool bit) {
    //If bito char buff is full, write byte to ostream.
    if (bit_count_ > 7) {
        os_.put(buff_);                     //Write buff to ostream.
        bit_count_ = 0;                     //Reset bit counter.
        buff_ = 0;                          //Zero out buffer.

    }
    toggle_bit(buff_, bit, bit_count_);     //Toggle k-th bit.
    bit_count_ += 1;                        //Increment bit counter.
}