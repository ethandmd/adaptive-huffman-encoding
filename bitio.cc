#include "bitio.hh"
#include <cassert>
#include <iostream>

BitOutput::~BitOutput() {
    //Flush buffer on destruction.
    os_.put(buff_);
}

/*
*   This method for debugging only.
*/
void get_buff(const uint8_t buff) { 
    std::cout << "Printing in bits for, " << int(buff) << ": ";
    for (int i = 7; i > -1; i--) { 
      bool k = buff & (0x1 << i);
      std::cout << k << " ";
      }
      std::cout << "\n";
    }

/*
*   Read bits from least significant to most significant.
*/
bool
BitInput::input_bit() {
    //Bit count ranges from [0,8). If bit count is > 7, read in next byte from stream.
    if (bit_count_ > 7) {
        buff_ = is_.get();
        //get_buff(buff_);                  //Visualize the bits.
        bit_count_ = 0;                     //Reset bit count.
    }

    bool k = buff_ & (0x1 << bit_count_);   //Extract LSB from char buffer.
    bit_count_ += 1;                        //Increment bit counter.
    return k;
}

/*
*   Set / clear the k-th bit with bit ops. Clearing
*   a bit requires creating a mask of its complement.
*/
void
toggle_bit(uint8_t &buff, bool bit, int k) {
    if (bit) {
        buff |= 0x1 << k;       //Set the k-th bit.
    } else {
        buff &= ~(0x1 << k);    //Clear the k-th bit.
    }
}


/*
*   If buffer is full (from buffer count), write 8 bits to ostream.
*   Otherwise, set/clear bit from least to most significant. So if
*   you did:
*       output_bit(1);
*       output_bit(1);
*       output_bit(0);
*       output_bit(1);
*   
*   the buffer would look like:
*       00001011.
*/
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