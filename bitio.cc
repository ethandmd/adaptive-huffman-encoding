#include "bitio.hh"
#include <cassert>

bool
BitInput::input_bit() {
    bool c = is_.get();
    chars_extracted_+= 1;
    
    assert(chars_extracted_ == is_.gcount());
    
    return c;
}


void
BitOutput::output_bit(bool bit) {
    os_.put(bit);
}