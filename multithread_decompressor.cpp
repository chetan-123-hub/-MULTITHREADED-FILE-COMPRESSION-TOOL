#include <cstdint>  
#include <iostream>
#include <fstream>
#include <vector>
#include <zlib.h>

void decompressBlock(std::ifstream& input, std::ofstream& output) {
    while (!input.eof()) {
        uint32_t compSize;
        input.read(reinterpret_cast<char*>(&compSize), sizeof(compSize));
        if (input.gcount() != sizeof(compSize)) break;

        std::vector<unsigned char> compData(compSize);
        input.read(reinterpret_cast<char*>(compData.data()), compSize);
        if (input.gcount() != compSize) break;

        
        uLongf decompSize = 1024 * 1024;
        std::vector<char> decompData(decompSize);

        int res = uncompress(reinterpret_cast<Bytef*>(decompData.data()), &decompSize,
                             compData.data(), compSize);

        if (res == Z_OK) {
            output.write(decompData.data(), decompSize);
        } else {
            std::cerr << "Decompression failed for a block.\n";
        }
    }
}

int main() {
    std::ifstream input("output.comp", std::ios::binary);
    if (!input) {
        std::cerr << "Compressed file not found.\n";
        return 1;
    }

    std::ofstream output("reconstructed.txt", std::ios::binary);
    if (!output) {
        std::cerr << "Cannot open output file.\n";
        return 1;
    }

    decompressBlock(input, output);

    std::cout << "Decompression completed. Output: reconstructed.txt\n";
    return 0;
}
