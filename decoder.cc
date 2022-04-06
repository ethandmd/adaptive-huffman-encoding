#include "huffman.hh"
#include "bitio.hh"
#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char* argv[]) {
    //Conditions check on number of CLI args passed in.
    if (argc < 2) {
        std::cerr << "Need exactly one argument: input filename\n";
        return -1;
    }

    //Conditions check that filename from CLI arg is valid.
    std::ifstream ifs (argv[1], std::ios::in);
    if (!ifs.is_open()) {
        std::cerr << "Can't open input file: " << argv[1] << "\n";
        return -1;
    }

    std::string output_fname = std::string(argv[1]) + ".plaintext";
    std::ofstream ofs (output_fname, std::ofstream::out | std::ios::app);
    Huffman decoder;
    BitInput biti(ifs);

    while (true) {
        int symbol = -1;
        while (symbol < 0) {
            symbol = decoder.decode(biti.input_bit());
            std::cout << char(symbol) << " ";
        }
        //bool bit = biti.input_bit();
        //int symbol = decoder.decode(bit);
        if (symbol == Huffman::HEOF) { 
            std::cout << char(symbol) << "\n";
            break; 
        } else {
            ofs.put(symbol);
        }
        //if (symbol > 0) { ofs.put(symbol); }
    };

    //Read bits from input file and decode them into chars.

    //Eitan's moodle code:
    /*
    while (true) {
        while (symbol > 0) {
            bool bit = biti.input_bit();
            symbol = decoder.decode(bit);
        }
        //std::cout << char(symbol) << "\n";
        if (symbol == Huffman::HEOF) { 
            break; 
        } else {
            ofs.put(symbol);
            symbol = -1;
        }   
    }
    */
}