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
    //Open input stream in binary mode!
    std::ifstream ifs (argv[1], std::ios::in | std::ios::binary);
    if (!ifs.is_open()) {
        std::cerr << "Can't open input file: " << argv[1] << "\n";
        return -1;
    }

    std::string output_fname = std::string(argv[1]) + ".plaintext";
    std::ofstream ofs (output_fname, std::ofstream::out);
    Huffman decoder;
    BitInput biti(ifs);

    while (ifs.good()) {
        //Read bits until you get a valid ascii symbol.
        int symbol;
        do {
            symbol = decoder.decode(biti.input_bit());
        } while (symbol < 0);

        //If the symbol is EOF, stop reading from stream.
        if (symbol == Huffman::HEOF) { 
            std::cout << char(symbol) << "\n";
            break; 
        //Otherwise, write symbol to .plaintext ostream!
        } else {
            ofs.put(symbol);
        }
    }
    ofs.close();
}