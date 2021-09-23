#include "image_utils.h"

#include <cstdlib>
#include <cstring>
#include <memory>

template <typename T>
struct free_deleter {
    void operator() (T* ptr) {
        std::free(ptr);
    }
};

template <typename T>
using deleted_ptr = std::unique_ptr<T, free_deleter<T>>;

namespace image_utils {

wxImage image_to_wxImage(const image& img) {
    auto ptr = deleted_ptr<unsigned char>(static_cast<unsigned char*>(std::malloc(img.data().size())));
    std::memcpy(ptr.get(), img.data().data(), img.data().size());
    return wxImage(img.width(), img.height(), ptr.release(), true);
}

}

