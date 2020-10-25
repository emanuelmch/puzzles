/*
 * Copyright (c) 2020 Emanuel Machado da Silva
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#pragma once

#include <memory>
#include <mutex>
#include <optional>

namespace bill {

template <typename T>
struct ThreadSafeQueue {

  ~ThreadSafeQueue() {
    while (front != nullptr) {
      auto dangling = front;
      front = front->next;
      delete dangling;
    }
  }

  struct Node {
    T object;
    Node *next;
  };

  [[nodiscard]] inline bool empty() { return front == nullptr; }

  inline void push(const T &object) { push_node(new Node{object, nullptr}); }

  inline void push(T &&object) { push_node(new Node{std::move(object), nullptr}); }

  template <typename... Args>
  inline void emplace(Args &&...args) {
    push_node(new Node{T(std::forward<Args>(args)...), nullptr});
  }

  template <typename Iterator>
  inline void push(const Iterator &begin, const Iterator &end) {
    push_nodes(begin, end);
  }

  [[nodiscard]] std::optional<T> pop() {
    std::unique_lock frontLock(frontMutex);
    if (front == nullptr) {
      return std::nullopt;
    }

    std::unique_ptr<Node> dangling{front};

    if (front->next != nullptr) {
      front = front->next;
    } else {
      std::unique_lock backLock(backMutex);
      front = nullptr;
      back = nullptr;
    }
    frontLock.unlock();

    return std::optional{dangling->object};
  }

private:
  std::mutex frontMutex, backMutex;
  Node *front = nullptr;
  Node *back = nullptr;

  void push_node(Node *node) {
    std::unique_lock backLock(backMutex);

    if (back == nullptr) {
      std::unique_lock frontLock(frontMutex);
      front = node;
      back = front;
      return;
    }

    assert(back != nullptr);
    assert(back->next == nullptr);
    back->next = node;
    back = node;
  }

  template <typename Iterator>
  void push_nodes(Iterator begin, const Iterator &end) {
    assert(begin != end);
    std::unique_lock backLock(backMutex);

    if (back == nullptr) {
      std::unique_lock frontLock(frontMutex);
      front = new Node{*begin, nullptr};
      back = front;

      ++begin;
    }

    assert(back != nullptr);
    assert(back->next == nullptr);

    while (begin != end) {
      auto newNode = new Node{*begin, nullptr};
      back->next = newNode;
      back = newNode;

      ++begin;
    }
  }
};
}
