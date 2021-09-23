#include "renderer.h"

#include <cassert>

renderer::renderer() : m_renderer(), m_enable_text_anti_aliasing(false), m_enable_doc_anti_aliasing(false) {

}

renderer::renderer(renderer_options options) : m_renderer(), m_enable_text_anti_aliasing(false), m_enable_doc_anti_aliasing(false) {
    parse_and_set_options(options);
}

renderer::renderer(std::initializer_list<renderer_options> options) : m_renderer(), m_enable_text_anti_aliasing(false), m_enable_doc_anti_aliasing(false) {
    for (auto option : options) {
        parse_and_set_options(option);
    }

}
    
image renderer::render_page(const document& doc, int page_index, int height, int width, double dpi) {
    (void)doc;
    (void)page_index;
    (void)height;
    (void)width;
    (void)dpi;
    throw std::runtime_error("");
}

image renderer::render_page(const document& doc, int page_index, int height, int width, double x_dpi, double y_dpi) {
    (void)doc;
    (void)page_index;
    (void)height;
    (void)width;
    (void)x_dpi;
    (void)y_dpi;
    throw std::runtime_error("");
}

void renderer::init_poppler_renderer() {
    // set format to a convenient format for consumption
    // if we need transparency we can always add it later
    m_renderer.set_image_format(poppler::image::format_enum::format_rgb24);

    m_renderer.set_render_hint(poppler::page_renderer::render_hint::text_antialiasing, m_enable_text_anti_aliasing);
    m_renderer.set_render_hint(poppler::page_renderer::render_hint::antialiasing, m_enable_doc_anti_aliasing);

    assert(m_renderer.can_render());
}

void renderer::parse_and_set_options(renderer_options options) {
    if (renderer_options_utils::contains_option(options, renderer_options::text_anti_aliasing)) {
        m_enable_text_anti_aliasing = true;
    }
}

