# CSCI2-HW8 -- Adaptive Huffman Encoding
#### Author: Ethan McDonald

## Design

### Huffman:
+ Frequency table: Array of length 256+1 of all zeroes. HEOF frequency is set to (1) during the constructor's call.
+ Encode(): 
    + Build a new huffman tree from freq table.
    + Get a const path to the target symbol.
    + Iterate through directions in path and append them to a vector of bool.
    + Update frequency table.
+ Decode():
    + Uses a ```tmp_node_``` private data member to maintain 'state' while decoding.
    + If tmp is a nullptr, then you are at a 'new' sequence in decoding and need to rebuild a huffman tree.
    + Otherwise, pickup your decoding where you left off by getting the appropriate child of the tmp node.
    + This method delineates between valid/invalid symbols by making the key of all 'synthetic' huffman tree internal nodes (-1).
    + Therefore, if a retrieved key is negative, this method returns -1, and updates the tmp node to reflect where the search left off.
+ These methods rely on a private method to build a new huffman tree from the frequency table, and a method for manipulating directions to bits.

### BitIO:
+ Both BitIO classes make use of a private buffer that is one character, a bit position counter, and private reference to the stream.
#### BitInput -- input_bit()
+ This method relies on the bit position counter, this way once all 8 bits have been read out from a single byte, a new byte from the stream is read in.
+ At each turn, this method returns the next least significant bit (LSB) from left to right.
+ The LSB is extracted using bit operations (a mask with the target bit shifted into position with ```bit_count_```).
+ After each bit is output, the internal bit count is then incremented.

#### BitOutput -- output_bit():
+ This method relies on a seperate function ```toggle_bit()```.
+ Toggle bit has the ability to either set or clear the k-th bit in a ```char``` or ```uint8_t```.
+ Using the bit toggle function, this method sets the k-th bit in the private buffer w.r.t. the input bit parameter.
+ Similar to the bit input function, this class maintains a private bit counter data member that tracks when the internal buffer is full.
+ When the buffer is full (all 8 bits are correct) the buffer is output to the stream, and reset to zero.
+ When the ```BitOutput``` class destructor is called, the buffer is flushed to the stream.

### Encoder:
Encoder initially does some basic conditions checks on the user CLI inputs. Next, it establishes an output file to write to, and enters the encoding loop:
+ First, read a new character from the stream.
+ Encode that character as a vector of booleans.
+ For each bit in that encoding, write the bits to the stream.

### Decoder: This is at a *reasonable* level of 'working'.
The issue is that the decoder is not entirely consistent. It can sometimes output extra characters beyond the original data.

## Example Compression Tests:

```
                            
File Name                      |    bitio.cc    |   Makefile    |   htree.cc    |   verses.txt  |   poem_words.txt
-------------------------------------------------------------------------------------------------------------------------
Raw File Size (Bytes)          |    2022        |   633         |   1499        |   11678       |   2597
-------------------------------------------------------------------------------------------------------------------------
Compressed File Size (Bytes)   |    1501        |   654         |   1118        |   7197        |   1748
-------------------------------------------------------------------------------------------------------------------------
Exact Match* (Using ```diff```)|    No          |   No          |   No          |   No**        |   No**
-------------------------------------------------------------------------------------------------------------------------
Time to Compress :(            |    13.9s       |   4s          |   9.5s        |   1m21s       |   16.85s
-------------------------------------------------------------------------------------------------------------------------
Time to Decompress :((         |    12.4s       |   4s          |   9.45s       |   1m19s       |   16.33s
```
*Mostly these failures to match exactly were for missing a final "end of line" character in the decompression file.
**This decompression was missing one byte.