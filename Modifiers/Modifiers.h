#pragma once

#include "../constants.h"
#include <unordered_map>

namespace Huffman {
namespace Modifiers {
void IncrementBoolVector(std::vector<bool>& v);

std::vector<std::pair<Letter, HuffmanCode>> GetCanonicalCodes(std::vector<std::pair<size_t, Letter>>& codes_lengths);

std::vector<size_t> GetCountLengths(std::vector<std::pair<size_t, Letter>>& codes_lengths);

std::unordered_map<Letter, HuffmanCode> GetMapCodesBySymbols(
    std::vector<std::pair<Letter, HuffmanCode>>& canonical_codes);
}  // namespace Modifiers
}  // namespace Huffman
