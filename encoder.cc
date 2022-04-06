#include "huffman.hh"
#include "bitio.hh"
#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char *argv[]) {
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

    std::string output_fname = std::string(argv[1]) + ".comp";
    std::ofstream ofs (output_fname, std::ofstream::out | std::ios::app);
    BitOutput bito(ofs);
    Huffman encoder;
    //Read chars from input file and encode them.
    while (ifs.good()) {
        char c = ifs.get();
        //if (ifs.eof()) { std::cout << "EOF: "; std::cout << int(c) << "\n"; break; }  //Debugging.
        //std::cout << char(c) << ": "; //Debugging.
        Huffman::bits_t enc = encoder.encode(c);

        for (auto b : enc) {
            //std::cout << b << " ";    //Debugging.
            bito.output_bit(b);
        }
        //std::cout << "\n";            //Debugging.
    }
    ofs.close();

    return 0;
}