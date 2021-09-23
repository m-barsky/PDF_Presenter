#pragma once

#include <memory>

template <typename T>
struct null_deleter {
    void operator() ([[maybe_unused]]  T* ptr) { /* do nothing */ }
};

template<typename T>
using undeleted_ptr = std::unique_ptr<T, null_deleter<T>>;

