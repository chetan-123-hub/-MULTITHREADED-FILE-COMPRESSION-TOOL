#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <mutex>
#include <zlib.h>
#include <algorithm>

const int CHUNK_SIZE = 1024 * 1024; 
std::mutex mtx;

struct CompressedBlock {
    int index;
    std::vector<unsigned char> data;
};

void compressBlock(const std::vector<char>& input, int index, std::vector<CompressedBlock>& output) {
    uLongf destSize = compressBound(input.size());
    std::vector<unsigned char> dest(destSize);

    if (compress(dest.data(), &destSize, reinterpret_cast<const Bytef*>(input.data()), input.size()) == Z_OK) {
        dest.resize(destSize);
        std::lock_guard<std::mutex> lock(mtx);
        output.push_back({ index, dest });
    } else {
        std::cerr << "Compression failed for block " << index << "\n";
    }
}

int main() {
    std::ifstream input("input.txt", std::ios::binary);
    if (!input) {
        std::cerr << "Input file not found.\n";
        return 1;
    }

    std::vector<CompressedBlock> outputBlocks;
    std::vector<std::thread> threads;

    int blockIndex = 0;
    while (!input.eof()) {
        std::vector<char> buffer(CHUNK_SIZE);
        input.read(buffer.data(), CHUNK_SIZE);
        size_t bytesRead = input.gcount();
        buffer.resize(bytesRead);

        threads.emplace_back(compressBlock, buffer, blockIndex++, std::ref(outputBlocks));
    }

    for (auto& t : threads) t.join();

    std::sort(outputBlocks.begin(), outputBlocks.end(), [](const auto& a, const auto& b) {
        return a.index < b.index;
    });

    std::ofstream output("output.comp", std::ios::binary);
    for (const auto& block : outputBlocks) {
        uint32_t size = block.data.size();
        output.write(reinterpret_cast<const char*>(&size), sizeof(size));
        output.write(reinterpret_cast<const char*>(block.data.data()), size);
    }

    std::cout << "Compression completed.\n";
    return 0;
}
