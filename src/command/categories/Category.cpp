#include <aisaka/command/categories/Category.hpp>

Aisaka::Category::Category(std::string name) : name(std::move(name)) {}
Aisaka::Category::~Category() = default;
