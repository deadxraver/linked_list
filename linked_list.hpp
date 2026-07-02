#pragma once

#include <memory>
#include <stdexcept>
#include <iostream>

template<typename T>
class linked_list {
private:
  struct list_node {
    list_node(T val) : value(val), next(nullptr) {}
    list_node() : next(nullptr) {}
    T value;
    std::unique_ptr<list_node> next;
  };
  std::unique_ptr<list_node> data_;
  static void remove_next(list_node* node) {
    if (node == nullptr || node->next == nullptr)
      return;
    node->next = std::move(node->next->next);
  }

public:
  explicit linked_list() : data_(nullptr) {}
  friend std::ostream& operator<<(std::ostream& os, const linked_list& ll) {
    os << "{";
    for (const list_node* p = ll.data_.get(); p != nullptr; p = p->next.get()) {
      os << p->value;
      os << ", ";
    }
    os << "}";
    return os;
  }

  std::size_t size() const {
    std::size_t sz = 0;
    for (const list_node* p = this->data_.get(); p != nullptr; p = p->next.get(), ++sz);
    return sz;
  }

  T& operator[](std::size_t i) {
    std::size_t idx = i;
    for (list_node* p = this->data_.get(); p != nullptr; p = p->next.get(), --i) {
      if (i == 0)
        return p->value;
    }
    throw std::out_of_range("index " + std::to_string(idx) + " out of range for size " + std::to_string(size()));
  }

  void push_back(T val) {
    list_node* p = this->data_.get();
    if (p == nullptr) {
      this->data_ = std::make_unique<list_node>(val);
      return;
    }
    for (; p->next.get() != nullptr; p = p->next.get());
    p->next = std::make_unique<list_node>(val);
  }

  void remove_at(std::size_t index) {
    // TODO:
    throw std::logic_error("remove_at not implemented yet");
  }

  void remove(T value) {
    for (list_node* p = this->data_.get(), * prev = nullptr; p != nullptr; prev = p, p = p->next.get()) {
      if (p->value == value) {
        remove_next(prev);
        return;
      }
    }
    throw std::logic_error("failed to remove: element not found");
  }
};
