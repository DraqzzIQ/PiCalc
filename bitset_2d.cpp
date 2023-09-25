#include "bitset_2d.h"

bitset_2d::bitset_2d() {
    _plane = std::vector<dynamic_bitset>(0);
    _width = 0;
    _height = 0;
}

bitset_2d::bitset_2d(uint32_t width, uint32_t height, bool value) {
    _plane = std::vector<dynamic_bitset>(width, dynamic_bitset(height, value));
    _width = width;
    _height = height;
}

bitset_2d::bitset_2d(uint32_t width, const dynamic_bitset &other) {
    _plane = std::vector<dynamic_bitset>(width, other);
    _width = width;
    _height = other.size();
}

bitset_2d::bitset_2d(uint32_t width, uint32_t height, const std::vector<std::vector<uint8_t>> &plane) {
    _plane = std::vector<dynamic_bitset>(width);
    for (uint32_t i = 0; i < width; i++) _plane[i] = dynamic_bitset(height, plane[i]);
    _width = width;
    _height = height;
}

bitset_2d::bitset_2d(const bitset_2d& other) {
    _plane = other._plane;
    _width = other._width;
    _height = other._height;
}

bitset_2d::~bitset_2d() {}


const dynamic_bitset& bitset_2d::operator[](uint32_t index) const {
#ifdef IS_DEBUG_BUILD
    if (index >= _width) throw(std::out_of_range("bitset_2d::operator[]"));
#endif
    return _plane.at(index);
}

bool bitset_2d::operator==(const bitset_2d &other) const {
    if (other._width != _width || other._height != _height) return false;
    return _plane == other._plane;
}

bool bitset_2d::operator!=(const bitset_2d &other) const {
    if (other._width != _width || other._height != _height) return true;
    return _plane != other._plane;
}

bitset_2d& bitset_2d::operator=(const bitset_2d &other) {
    _plane = other._plane;
    _width = other._width;
    _height = other._height;
    return *this;
}

bitset_2d bitset_2d::operator+(const bitset_2d& other)
{
    bitset_2d res(*this);
    res.extend_right(other);
    return res;
}


const dynamic_bitset& bitset_2d::at(uint32_t index) const {
#ifdef IS_DEBUG_BUILD
    if (index >= _width) throw(std::out_of_range("bitset_2d::at"));
#endif
    return _plane.at(index);
}

uint32_t bitset_2d::width() const {
    return _width;
}

uint32_t bitset_2d::height() const {
    return _height;
}

bool bitset_2d::get_bit(uint32_t coord_x, uint32_t coord_y) const {
#ifdef IS_DEBUG_BUILD
    if (coord_x >= _width || coord_ >= _height) throw(std::out_of_range("bitset_2d::get_bit"));
#endif
    return _plane.at(coord_x).at(coord_y);
}




void bitset_2d::set(uint32_t coord_x, uint32_t coord_y, const bitset_2d& other, bool resize_if_needed) {
#ifdef IS_DEBUG_BUILD
    if ((coord_x + other._width > _width || coord_y + other._height > _height) && !resize_if_needed) throw(std::out_of_range("bitset_2d::set"));
#endif
    if (resize_if_needed) {
        if (other._width + coord_x > _width) {
            extend_right(other._width + coord_x - _width, false);
        }
        if (other._height + coord_y > _height) {
            extend_down(other._height + coord_y - _height, false);
        }
    }
    for (uint32_t i = 0; i < other._width; i++) {
        _plane[i + coord_x].set(coord_y, other.at(i));
    }
}

void bitset_2d::set_column(uint32_t coord_x, const dynamic_bitset& other) {
#ifdef IS_DEBUG_BUILD
    if (coord_x >= _width || other._height != _height) throw(std::out_of_range("bitset_2d::set_column"));
#endif
    _plane[coord_x] = other;
}

void bitset_2d::set_bit(uint32_t coord_x, uint32_t coord_y, bool value) {
#ifdef IS_DEBUG_BUILD
    if (coord_x >= _width || coord_y >= _height) throw(std::out_of_range("bitset_2d::set_bit"));
#endif
    _plane[coord_x].set(coord_y, value);
}

// TODO:
// Insert-functions

void bitset_2d::erase_x(uint32_t coord_x) {
#ifdef IS_DEBUG_BUILD
    if (coord_x >= _width) throw(std::out_of_range("bitset_2d::erase_x"));
#endif
    _plane.erase(_plane.begin() + coord_x);
    _width--;
}

void bitset_2d::erase_y(uint32_t coord_y) {
#ifdef IS_DEBUG_BUILD
    if (coord_y >= _height) throw(std::out_of_range("bitset_2d::erase_y"));
#endif
    for (uint32_t i = 0; i < _width; i++) {
        _plane[i].erase(coord_y);
    }
    _height--;
}

void bitset_2d::clear() {
    _plane.clear();
    _width = 0;
    _height = 0;
}


void bitset_2d::push_back(const dynamic_bitset& other) {
    if (_height == 0) {
        _height = other.size();
    }
#ifdef IS_DEBUG_BUILD
    if (other.size() != _height) throw(std::out_of_range("bitset_2d::push_back"));
#endif
    _plane.push_back(other);
    _width++;
}

void bitset_2d::push_front(const dynamic_bitset& other) {
    if (_height == 0) {
        _height = other.size();
    }
#ifdef IS_DEBUG_BUILD
    if (other.size() != _height) throw(std::out_of_range("bitset_2d::push_back"));
#endif
    _plane.insert(_plane.begin(), other);
    _width++;
}

void bitset_2d::extend_right(const bitset_2d& other) {
    if (_height == 0) {
        _height = other._height;
    }
#ifdef IS_DEBUG_BUILD
    if (_height != other._height) throw(std::out_of_range("bitset_2d::extend_right"));
#endif
    _plane.insert(_plane.end(), other._plane.begin(), other._plane.end());
    _width += other._width;
}

void bitset_2d::extend_right(uint32_t length, bool value) {
    dynamic_bitset empty(_height, value);
    for (uint32_t i = 0; i < length; i++) {
        _plane.push_back(empty);
    }
    _width += length;
}

void bitset_2d::extend_down(const bitset_2d& other) {
#ifdef IS_DEBUG_BUILD
    if (_width != other._width) throw(std::out_of_range("bitset_2d::extend_down"));
#endif
    for (uint32_t i = 0; i < other._width; i++) {
        _plane[i].extend(other.at(i));
    }
    _height += other._height;
}

void bitset_2d::extend_down(uint32_t length, bool value) {
    for (uint32_t i = 0; i < _width; i++) {
        _plane[i].extend(length, value);
    }
    _height += length;
}

void bitset_2d::extend_left(const bitset_2d& other) {
#ifdef IS_DEBUG_BUILD
    if (_height != other._height) throw(std::out_of_range("bitset_2d::extend_left"));
#endif
    _plane.insert(_plane.begin(), other._plane.begin(), other._plane.end());
    _width += other._width;
}

void bitset_2d::extend_left(uint32_t length, bool value) {
    bitset_2d empty(length, _height, value);
    extend_left(empty);
}

void bitset_2d::extend_up(const bitset_2d& other) {
#ifdef IS_DEBUG_BUILD
    if (_width != other._width) throw(std::out_of_range("bitset_2d::extend_down"));
#endif
    for (uint32_t i = 0; i < other._width; i++) {
        _plane[i].extend_left(other.at(i));
    }
    _height += other._height;
}

void bitset_2d::extend_up(uint32_t length, bool value) {
    for (uint32_t i = 0; i < _width; i++) {
        _plane[i].extend_left(length, value);
    }
    _height += length;
}


std::string bitset_2d::to_string()
{
    std::string s = "";
    for (uint32_t i = 0; i < _plane.size(); i++)
    {
        s += _plane[i].to_string();
    }
    return s;
}

std::string bitset_2d::to_string_formatted()
{
    uint32_t max_size = 0;
    for (uint32_t i = 0; i < _plane.size(); i++)
    {
        if(_plane[i].size() > max_size)
        {
            max_size = _plane[i].size();
        }
    }

    std::string s = "";
    for(uint32_t i = 0; i < max_size; i++)
    {
        for(uint32_t j = 0; j < _plane.size(); j++)
        {
            if(i < _plane[j].size())
            {
                s += _plane[j][i] ? "1" : "0";
            }
            else
            {
                s += " ";
            }
        }
        s += "\n";
    }
    return s;
}