#include "Modifiers.h"

void Huffman::Modifiers::IncrementBoolVector(std::vector<bool>& v) {
    for (size_t i = 0; i < v.size(); ++i) {
        if (!v[v.size() - i - 1]) {
            v[v.size() - i - 1] = true;
            for (size_t j = 0; j < i; ++j) {
                v[v.size() - j - 1] = false;
            }
            return;
        }
    }
}

std::vector<std::pair<Letter, HuffmanCode>> Huffman::Modifiers::GetCanonicalCodes(
    std::vector<std::pair<size_t, Letter>>& codes_lengths) {
    std::vector<std::pair<Letter, HuffmanCode>> result;
    HuffmanCode current_sequence(codes_lengths[0].first, false);
    result.emplace_back(codes_lengths[0].second, current_sequence);
    for (size_t i = 1; i < codes_lengths.size(); ++i) {
        IncrementBoolVector(current_sequence);
        while (current_sequence.size() < codes_lengths[i].first) {
            current_sequence.push_back(false);
        }
        result.emplace_back(codes_lengths[i].second, current_sequence);
    }
    return result;
}

std::vector<size_t> Huffman::Modifiers::GetCountLengths(std::vector<std::pair<size_t, Letter>>& codes_lengths) {
    std::vector<size_t> result(codes_lengths.back().first);
    for (const auto& [symbol_code_size, symbol] : codes_lengths) {
        result[symbol_code_size - 1]++;
    }
    return result;
}

std::unordered_map<Letter, HuffmanCode> Huffman::Modifiers::GetMapCodesBySymbols(
    std::vector<std::pair<Letter, HuffmanCode>>& canonical_codes) {
    std::unordered_map<Letter, HuffmanCode> result;
    for (const auto& [symbol, code] : canonical_codes) {
        result[symbol] = code;
    }
    return result;
}