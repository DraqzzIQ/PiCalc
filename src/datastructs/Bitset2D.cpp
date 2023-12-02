#include "datastructs/Bitset2D.h"

Bitset2D::Bitset2D()
{
	_plane = std::vector<DynamicBitset>(0);
	_width = 0;
	_height = 0;
}

Bitset2D::Bitset2D(uint32_t width, uint32_t height, bool value)
{
	_plane = std::vector<DynamicBitset>(width, DynamicBitset(height, value));
	_width = width;
	_height = height;
}

Bitset2D::Bitset2D(uint32_t width, const DynamicBitset& other)
{
	_plane = std::vector<DynamicBitset>(width, other);
	_width = width;
	_height = other.size();
}

Bitset2D::Bitset2D(uint32_t width, uint32_t height, const std::vector<std::vector<uint8_t>>& plane)
{
	_plane = std::vector<DynamicBitset>(width);
	for (uint32_t i = 0; i < width; i++) _plane[i] = DynamicBitset(height, plane[i]);
	_width = width;
	_height = height;
}

Bitset2D::Bitset2D(const Bitset2D& other)
{
	_plane = other._plane;
	_width = other._width;
	_height = other._height;
}

Bitset2D::~Bitset2D() {}


const DynamicBitset& Bitset2D::operator[](uint32_t index) const
{
#ifdef IS_DEBUG_BUILD
	if (index >= _width) throw(std::out_of_range("Bitset2D::operator[]"));
#endif
	return _plane.at(index);
}

bool Bitset2D::operator==(const Bitset2D& other) const
{
	if (other._width != _width || other._height != _height) return false;
	return _plane == other._plane;
}

bool Bitset2D::operator!=(const Bitset2D& other) const
{
	if (other._width != _width || other._height != _height) return true;
	return _plane != other._plane;
}

Bitset2D& Bitset2D::operator=(const Bitset2D& other)
{
	_plane = other._plane;
	_width = other._width;
	_height = other._height;
	return *this;
}

Bitset2D Bitset2D::operator+(const Bitset2D& other)
{
	Bitset2D res(*this);
	res.extend_right(other);
	return res;
}


const DynamicBitset& Bitset2D::at(uint32_t index) const
{
#ifdef IS_DEBUG_BUILD
	if (index >= _width) throw(std::out_of_range("Bitset2D::at"));
#endif
	return _plane.at(index);
}

uint32_t Bitset2D::width() const
{
	return _width;
}

uint32_t Bitset2D::height() const
{
	return _height;
}

bool Bitset2D::get_bit(uint32_t coord_x, uint32_t coord_y) const
{
#ifdef IS_DEBUG_BUILD
	if (coord_x >= _width || coord_y >= _height) throw(std::out_of_range("Bitset2D::get_bit"));
#endif
	return _plane.at(coord_x).at(coord_y);
}

Bitset2D& Bitset2D::copy(uint32_t x_start, uint32_t y_start, uint32_t width, uint32_t height, Bitset2D& destination) const
{
	destination.clear();
	for (uint32_t i = x_start; i < width + x_start; i++) destination.push_back(_plane[i].copy(y_start, height));
	destination._width = width;
	destination._height = height;
	return destination;
}


void Bitset2D::set(uint32_t coord_x, uint32_t coord_y, const Bitset2D& other, bool resize_if_needed)
{
#ifdef IS_DEBUG_BUILD
	if ((coord_x + other._width > _width || coord_y + other._height > _height) && !resize_if_needed) throw(std::out_of_range("Bitset2D::set"));
#endif
	if (resize_if_needed) {
		if (other._width + coord_x > _width) { extend_right(other._width + coord_x - _width, false); }
		if (other._height + coord_y > _height) { extend_down(other._height + coord_y - _height, false); }
	}
	for (uint32_t i = 0; i < other._width; i++) { _plane[i + coord_x].set(coord_y, other.at(i)); }
}

void Bitset2D::set_column(uint32_t coord_x, const DynamicBitset& other)
{
#ifdef IS_DEBUG_BUILD
	if (coord_x >= _width || other.size() != _height) throw(std::out_of_range("Bitset2D::set_column"));
#endif
	_plane[coord_x] = other;
}

void Bitset2D::set_bit(uint32_t coord_x, uint32_t coord_y, bool value)
{
#ifdef IS_DEBUG_BUILD
	if (coord_x >= _width || coord_y >= _height) throw(std::out_of_range("Bitset2D::set_bit"));
#endif
	_plane[coord_x].set(coord_y, value);
}

void Bitset2D::erase_x(uint32_t coord_x)
{
#ifdef IS_DEBUG_BUILD
	if (coord_x >= _width) throw(std::out_of_range("Bitset2D::erase_x"));
#endif
	_plane.erase(_plane.begin() + coord_x);
	_width--;
}

void Bitset2D::erase_y(uint32_t coord_y)
{
#ifdef IS_DEBUG_BUILD
	if (coord_y >= _height) throw(std::out_of_range("Bitset2D::erase_y"));
#endif
	for (uint32_t i = 0; i < _width; i++) { _plane[i].erase(coord_y); }
	_height--;
}

void Bitset2D::pop_back_x()
{
	_plane.pop_back();
	_width--;
}

void Bitset2D::clear()
{
	_plane.clear();
	_width = 0;
	_height = 0;
}


void Bitset2D::push_back(const DynamicBitset& other)
{
	if (_height == 0) { _height = other.size(); }
#ifdef IS_DEBUG_BUILD
	if (other.size() != _height) throw(std::out_of_range("Bitset2D::push_back"));
#endif
	_plane.push_back(other);
	_width++;
}

void Bitset2D::push_front(const DynamicBitset& other)
{
	if (_height == 0) { _height = other.size(); }
#ifdef IS_DEBUG_BUILD
	if (other.size() != _height) throw(std::out_of_range("Bitset2D::push_back"));
#endif
	_plane.insert(_plane.begin(), other);
	_width++;
}

void Bitset2D::extend_right(const Bitset2D& other)
{
	if (_height == 0) { _height = other._height; }
#ifdef IS_DEBUG_BUILD
	if (_height != other._height) throw(std::out_of_range("Bitset2D::extend_right"));
#endif
	_plane.insert(_plane.end(), other._plane.begin(), other._plane.end());
	_width += other._width;
}

void Bitset2D::extend_right(uint32_t length, bool value)
{
	DynamicBitset empty(_height, value);
	for (uint32_t i = 0; i < length; i++) { _plane.push_back(empty); }
	_width += length;
}

void Bitset2D::extend_down(const Bitset2D& other)
{
#ifdef IS_DEBUG_BUILD
	if (_width != other._width) throw(std::out_of_range("Bitset2D::extend_down"));
#endif
	for (uint32_t i = 0; i < other._width; i++) { _plane[i].extend(other.at(i)); }
	_height += other._height;
}

void Bitset2D::extend_down(uint32_t length, bool value)
{
	for (uint32_t i = 0; i < _width; i++) { _plane[i].extend(length, value); }
	_height += length;
}

void Bitset2D::extend_left(const Bitset2D& other)
{
#ifdef IS_DEBUG_BUILD
	if (_height != other._height) throw(std::out_of_range("Bitset2D::extend_left"));
#endif
	_plane.insert(_plane.begin(), other._plane.begin(), other._plane.end());
	_width += other._width;
}

void Bitset2D::extend_left(uint32_t length, bool value)
{
	Bitset2D empty(length, _height, value);
	extend_left(empty);
}

void Bitset2D::extend_up(const Bitset2D& other)
{
#ifdef IS_DEBUG_BUILD
	if (_width != other._width) throw(std::out_of_range("Bitset2D::extend_down"));
#endif
	for (uint32_t i = 0; i < other._width; i++) { _plane[i].extend_left(other.at(i)); }
	_height += other._height;
}

void Bitset2D::extend_up(uint32_t length, bool value)
{
	for (uint32_t i = 0; i < _width; i++) { _plane[i].extend_left(length, value); }
	_height += length;
}


std::string Bitset2D::to_string()
{
	std::string s = "";
	for (uint32_t i = 0; i < _plane.size(); i++) { s += _plane[i].to_string(); }
	return s;
}

std::string Bitset2D::to_string_formatted()
{
	uint32_t max_size = 0;
	for (uint32_t i = 0; i < _plane.size(); i++) {
		if (_plane[i].size() > max_size) { max_size = _plane[i].size(); }
	}

	std::string s = "";
	for (uint32_t i = 0; i < max_size; i++) {
		for (uint32_t j = 0; j < _plane.size(); j++) {
			if (i < _plane[j].size()) {
				s += _plane[j][i] ? "1" : "0";
			} else {
				s += " ";
			}
		}
		s += "\n";
	}
	return s;
}
