/*
 * A pair of simple classes to perform stream I/O on individual bits.
 */
#include <iostream>

// BitInput: Read a single bit at a time from an input stream.
// Before reading any bits, ensure your input stream still has valid inputs.
class BitInput {
 public:
  // Construct with an input stream
  BitInput(std::istream& is) : is_(is)
  {}

  BitInput(const BitInput&) = default;
  BitInput(BitInput&&) = default;
  BitInput& operator=(const BitInput&) = default;
  BitInput& operator=(BitInput&&) = default;

  // Read a single bit (or trailing zero)
  // Allowed to crash or throw an exception if called past end-of-file.
  bool input_bit() { return is_.get(); };

  private:
  std::istream& is_;
};

// BitOutput: Write a single bit at a time to an output stream
// Make sure all bits are written out by the time the destructor is done.
class BitOutput {
 public:
  // Construct with an output stream
  BitOutput(std::ostream& os) : os_(os)
  {}

  // Flushes out any remaining output bits and trailing zeros, if any:
  ~BitOutput() = default;

  BitOutput(const BitOutput&) = default;
  BitOutput(BitOutput&&) = default;
  BitOutput& operator=(const BitOutput&) = default;
  BitOutput& operator=(BitOutput&&) = default;

  // Output a single bit (buffered)
  void output_bit(bool bit) { os_ << bit; };

  private:
  std::ostream& os_;
};

