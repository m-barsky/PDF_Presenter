#pragma once

#include <type_traits>
#include <initializer_list>

#include "poppler/cpp/poppler-page-renderer.h"

#include "document.h"
#include "image.h"

enum class renderer_options {
    text_anti_aliasing = 1,
    document_anti_aliasing = 2,
};

constexpr renderer_options operator| (renderer_options a, renderer_options b) {
    auto a_val = static_cast<std::underlying_type_t<renderer_options>>(a);
    auto b_val = static_cast<std::underlying_type_t<renderer_options>>(b);

    return static_cast<renderer_options>(a_val | b_val);
}

constexpr renderer_options operator& (renderer_options a, renderer_options b) {
    auto a_val = static_cast<std::underlying_type_t<renderer_options>>(a);
    auto b_val = static_cast<std::underlying_type_t<renderer_options>>(b);

    return static_cast<renderer_options>(a_val & b_val);
}

namespace renderer_options_utils {

constexpr bool contains_option(const renderer_options& options, const renderer_options& contains) {
    return static_cast<std::underlying_type_t<renderer_options>>(options & contains);
}

}

class renderer {
public:
    renderer();
    renderer(renderer_options options);
    renderer(std::initializer_list<renderer_options> options);

    renderer(const renderer&) = delete;
    renderer(renderer&&) = default;

    renderer& operator=(const renderer&) = delete;
    renderer& operator=(renderer&&) = default;

    ~renderer() = default;

    image render_page(const document& doc, int page_index, int height, int width, double dpi = 72.0);
    image render_page(const document& doc, int page_index, int height, int width, double x_dpi, double y_dpi);

private:
    void init_poppler_renderer();
    void parse_and_set_options(renderer_options options);


    poppler::page_renderer m_renderer;

    bool m_enable_text_anti_aliasing;
    bool m_enable_doc_anti_aliasing;
};

