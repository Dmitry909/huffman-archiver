cmake_minimum_required(VERSION 3.20)
project(huffman_archiver)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra -g")

add_executable(huffman_archiver main.cpp constants.h BitWriter/BitWriter.cpp BitWriter/BitWriter.h BitReader/BitReader.cpp BitReader/BitReader.h HuffmanTrie/HuffmanTrie.h HuffmanTrie/HuffmanTrie.cpp Coder/Coder.h Coder/Coder.cpp Decoder/Decoder.h Decoder/Decoder.cpp PriorityQueue/PriorityQueue.h PriorityQueue/PriorityQueue.cpp Modifiers/Modifiers.h Modifiers/Modifiers.cpp)