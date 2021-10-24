#pragma once

#include "../constants.h"

template <class T>
class PriorityQueue {
public:
    size_t Size() const {
        return data.size();
    }

    T Top() const {
        if (data.empty()) {
            return {};
        }
        return data[0];
    }

    void Push(const T& new_element) {
        data.push_back(new_element);
        size_t position = data.size() - 1;
        while (position > 0 && data[GetParent(position)] > data[position]) {
            std::swap(data[GetParent(position)], data[position]);
            position = GetParent(position);
        }
    }

    void Pop() {
        if (data.empty()) {
            return;
        }
        data[0] = data.back();
        data.pop_back();
        size_t position = 0;
        while (GetLeftChild(position) < data.size()) {
            if (GetRightChild(position) < data.size()) {
                if (data[GetLeftChild(position)] < data[position] &&
                    data[GetLeftChild(position)] < data[GetRightChild(position)]) {
                    std::swap(data[position], data[GetLeftChild(position)]);
                    position = GetLeftChild(position);
                    continue;
                }
                if (data[GetRightChild(position)] < data[position] &&
                    data[GetRightChild(position)] < data[GetLeftChild(position)]) {
                    std::swap(data[position], data[GetRightChild(position)]);
                    position = GetRightChild(position);
                    continue;
                }
                break;
            }
            if (data[GetLeftChild(position)] < data[position]) {
                std::swap(data[position], data[GetLeftChild(position)]);
                position = GetLeftChild(position);
                continue;
            }
            break;
        }
    }

private:
    std::vector<T> data;

    static size_t GetParent(size_t vertex_id) {
        if (vertex_id == 0) {
            return 0;
        }
        return (vertex_id - 1) / 2;
    }

    static size_t GetLeftChild(size_t vertex_id) {
        return vertex_id * 2 + 1;
    }

    static size_t GetRightChild(size_t vertex_id) {
        return vertex_id * 2 + 2;
    }
};
