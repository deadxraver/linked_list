#pragma once

#include <memory>
#include <stdexcept>
#include <iostream>

template<typename T>
class linked_list {
private:
  struct list_node {
    list_node(T val, std::unique_ptr<list_node> ptr)
      : value(val), next(std::move(ptr)) {}
    list_node(T val) : value(val), next(nullptr) {}
    list_node() : next(nullptr) {}
    T value;
    std::unique_ptr<list_node> next;
  };

  class linked_list_iterator {
  private:
    list_node* node_;

  public:
    using value_type = T;
    using reference = T&;
    using pointer = T*;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::forward_iterator_tag;

    explicit linked_list_iterator(list_node* node) : node_(node) {}

    reference operator*() {
      return node_->value;
    }

    pointer operator->() {
      return &node_->value;
    }

    linked_list_iterator& operator++() {
      node_ = node_->next.get();
      return *this;
    }

    linked_list_iterator operator++(int) {
      linked_list_iterator tmp(*this);
      ++(*this);
      return tmp;
    }

    bool operator==(const linked_list_iterator& other) const {
      return node_ == other.node_;
    }

    bool operator!=(const linked_list_iterator& other) const {
      return !(*this == other);
    }
  };

  std::unique_ptr<list_node> data_;

  void remove_next(list_node* node = nullptr) {
    if (node == nullptr) {
      if (this->data_.get() != nullptr)
        this->data_ = std::move(this->data_->next);
      return;
    }
    if (node->next == nullptr)
      return;
    node->next = std::move(node->next->next);
  }

public:
  using iterator = linked_list_iterator;

  linked_list_iterator begin() {
    return linked_list_iterator(this->data_.get());
  }

  linked_list_iterator end() {
    return linked_list_iterator(nullptr);
  }

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
    throw std::out_of_range(
        "index " + std::to_string(idx) +
        " out of range for size " +
        std::to_string(size())
        );
  }

  const T& operator[](std::size_t i) const {
    std::size_t idx = i;
    for (const list_node* p = this->data_.get();
        p != nullptr;
        p = p->next.get(), --i
        ) {
      if (i == 0)
        return p->value;
    }
    throw std::out_of_range(
        "index " + std::to_string(idx) +
        " out of range for size " +
        std::to_string(size())
        );
  }

  void push(const T& value) {
    this->data_ = std::make_unique<list_node>(value, std::move(this->data_));
  }

  T& top() {
    if (this->data_.get() == nullptr)
      throw std::out_of_range("cannot get top element from empty list");
    return this->data_->value;
  }

  const T& top() const {
    if (this->data_.get() == nullptr)
      throw std::out_of_range("cannot get top element from empty list");
    return this->data_->value;
  }

  void pop() {
    if (this->data_.get() == nullptr)
      throw std::out_of_range("cannot pop from empty list");
    remove_next();
  }

  void push_back(const T& val) {
    list_node* p = this->data_.get();
    if (p == nullptr) {
      this->data_ = std::make_unique<list_node>(val);
      return;
    }
    for (; p->next.get() != nullptr; p = p->next.get());
    p->next = std::make_unique<list_node>(val);
  }

  void remove_at(std::size_t index) {
    std::size_t i = 0;
    for (
        list_node* p = this->data_.get(), * prev = nullptr;
        p != nullptr;
        prev = p, p = p->next.get(), ++i
        ) {
      if (i == index) {
        remove_next(prev);
        return;
      }
    }
    throw std::out_of_range(
        "index " + std::to_string(index) +
        " out of bounds for size " +
        std::to_string(this->size())
        );
  }

  void remove(const T& value) {
    for (
        list_node* p = this->data_.get(), * prev = nullptr;
        p != nullptr;
        prev = p, p = p->next.get()
        ) {
      if (p->value == value) {
        remove_next(prev);
        return;
      }
    }
    throw std::logic_error("failed to remove: element not found");
  }
};
