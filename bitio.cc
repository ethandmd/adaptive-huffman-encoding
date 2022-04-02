#include "bitio.hh"
#include <cassert>
#include <iostream>

bool
BitInput::input_bit() {
    //Bit count ranges from (0,8]. If bit count is > 8, read in next byte from stream.
    if (bit_count_ > 8) {
        buff_ = is_.get();          //Read next byte from istream.
        bool lsb = buff_ & 0x1;     //Extract LSB from char buffer.
        buff_ = buff_ >> 0x1;       //Shift buff left by one.
        bit_count_++;
        return lsb;
    } else {
        bool lsb = buff_ & 0x1;     //Extract LSB from char buffer.
        buff_ = buff_ >> 0x1;       //Shift buff left by one.
        bit_count_++;
        return lsb;
    }
}


void
BitOutput::output_bit(bool bit) {
    os_.put(bit);
}