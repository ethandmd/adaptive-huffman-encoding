#include "bitio.hh"
#include <cassert>
#include <iostream>

/*
*   Inputs a reference to char buffer with bits in R -> L order.
*   Takes each bit out and reverses order to be in L -> R order
*   in fmt char buffer.
*/
void
fmt_bits(char &fmt_buff, char &raw_buff) {
    //Iterate through each bit in raw buff.
    for (int i = 0; i < 8; i++) {
        bool lsb = raw_buff & 0x1;             //Extract input's LSB
        fmt_buff = fmt_buff << 0x1;            //Make room in buffer before
        fmt_buff |= lsb;                       //setting the buffer LSB.
        raw_buff = raw_buff >> 0x1;            //Get next bit in input byte.
    }
}

BitOutput::~BitOutput() {
    os_.put(buff_);
}

bool
BitInput::input_bit() {
    //Bit count ranges from [0,8). If bit count is > 7, read in next byte from stream.
    if (bit_count_ == 0) {
        //char raw_buff = is_.get();
        //fmt_bits(buff_, raw_buff);              //Read next byte from istream into buff_
        buff_ = is_.get();
        bool lsb = buff_ & 0x1;                 //Extract LSB from formatted buffer.
        buff_ = buff_ >> 0x1;                   //Shift fmt buffer right for next call.
        bit_count_ = 8;                         //Reset bit counter.

        return lsb;

    } else {
        bool lsb = buff_ & 0x1;                 //Extract LSB from char buffer.
        buff_ = buff_ >> 0x1;                   //Shift buff right by one.
        bit_count_ -= 1;                        //Decrement bit counter.
        return lsb;
    }
}

void
BitOutput::output_bit(bool bit) {
    //If bito char buff is full, write byte to ostream.
    if (bit_count_ > 7) {
        os_.put(buff_);                  //Write fmt buff to ostream.
        bit_count_ = 0;                  //Reset bit counter.

    } else {
        buff_ = buff_ << 0x1;            //Make room for setting next LSB.
        buff_ |= bit;                    //Set LSB in bito raw buff.
        bit_count_ += 1;                 //Increment bit counter.
    }
}