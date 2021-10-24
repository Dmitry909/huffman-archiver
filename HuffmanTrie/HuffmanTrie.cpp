#include "HuffmanTrie.h"
#include "../PriorityQueue/PriorityQueue.h"
#include "../Modifiers/Modifiers.h"
#include <algorithm>

Huffman::HuffmanTrie::HuffmanTrie(Letter letter)
    : letter(letter){

      };

Huffman::HuffmanTrie::HuffmanTrie(std::unordered_map<Letter, size_t>& symbols_count) {
    PriorityQueue<std::pair<size_t, HuffmanTrie*>> q;

    for (const auto& [symbol, symbol_count] : symbols_count) {
        q.Push({static_cast<int64_t>(symbol_count), new HuffmanTrie(symbol)});
    }
    while (q.Size() > 2) {
        auto new_node = new HuffmanTrie(Letter());

        int64_t new_size = 0;
        new_node->left = q.Top().second;
        new_size += q.Top().first;
        q.Pop();

        new_node->right = q.Top().second;
        new_size += q.Top().first;
        q.Pop();

        q.Push({new_size, new_node});
    }
    left = q.Top().second;
    q.Pop();
    right = q.Top().second;
    q.Pop();
}

Huffman::HuffmanTrie::HuffmanTrie(std::vector<Letter>& sorted_letters,
                                  std::vector<size_t> count_letters_by_code_length) {
    std::vector<std::pair<size_t, Letter>> codes_lengths(sorted_letters.size());
    size_t count_letters_by_code_length_index = 0;
    for (size_t i = 0; i < sorted_letters.size(); ++i) {
        while (count_letters_by_code_length[count_letters_by_code_length_index] == 0) {
            ++count_letters_by_code_length_index;
        }
        codes_lengths[i] = {count_letters_by_code_length_index + 1, sorted_letters[i]};
        --count_letters_by_code_length[count_letters_by_code_length_index];
    }
    auto canonical_codes = Modifiers::GetCanonicalCodes(codes_lengths);
    letter = Letter();
    for (const auto& [letter_to_add, canonical_code] : canonical_codes) {
        Add(canonical_code, letter_to_add);
    }
}

void Huffman::HuffmanTrie::Add(const HuffmanCode& code, const Letter& letter_to_add) {
    auto current_node = this;
    for (size_t i = 0; i < code.size(); ++i) {
        if (!code[i]) {
            if (i + 1 < code.size()) {
                if (current_node->left == nullptr) {
                    current_node->left = new HuffmanTrie(Letter());
                }
            } else {
                if (current_node->left == nullptr) {
                    current_node->left = new HuffmanTrie(letter_to_add);
                }
            }
            current_node = current_node->left;
            continue;
        }
        if (i + 1 < code.size()) {
            if (current_node->right == nullptr) {
                current_node->right = new HuffmanTrie(Letter());
            }
        } else {
            if (current_node->right == nullptr) {
                current_node->right = new HuffmanTrie(letter_to_add);
            }
        }
        current_node = current_node->right;
    }
}

std::vector<std::pair<size_t, Letter>> Huffman::HuffmanTrie::GetCodesLengths() const {
    std::vector<std::pair<size_t, Letter>> codes_sorted_by_length;
    RecursiveSearch(codes_sorted_by_length, this, 0);
    std::sort(codes_sorted_by_length.begin(), codes_sorted_by_length.end(),
              [](const std::pair<size_t, Letter>& a, const std::pair<size_t, Letter> b) {
                  if (a.first < b.first) {
                      return true;
                  }
                  if (a.first > b.first) {
                      return false;
                  }
                  for (size_t i = 0; i < LETTER_SIZE; ++i) {
                      if (a.second[LETTER_SIZE - i - 1] < b.second[LETTER_SIZE - i - 1]) {
                          return true;
                      }
                      if (a.second[LETTER_SIZE - i - 1] > b.second[LETTER_SIZE - i - 1]) {
                          return false;
                      }
                  }
                  return false;
              });
    return codes_sorted_by_length;
}

Letter Huffman::HuffmanTrie::ReadLetter(BitReader& reader) {
    auto current_node = this;
    while (!current_node->IsTerminal()) {
        if (!reader.Read()) {
            current_node = current_node->left;
        } else {
            current_node = current_node->right;
        }
    }
    return current_node->letter;
}

Huffman::HuffmanTrie::~HuffmanTrie() {
    if (IsTerminal()) {
        return;
    }
    delete left;
    delete right;
}

bool Huffman::HuffmanTrie::IsTerminal() const {
    return left == nullptr && right == nullptr;
}

void Huffman::HuffmanTrie::RecursiveSearch(std::vector<std::pair<size_t, Letter>>& to_add, const HuffmanTrie* node,
                                           size_t depth) const {
    if (node->IsTerminal()) {
        to_add.emplace_back(depth, node->letter);
        return;
    }
    RecursiveSearch(to_add, node->left, depth + 1);
    RecursiveSearch(to_add, node->right, depth + 1);
}
