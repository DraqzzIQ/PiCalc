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
#if defined IS_DEBUG_BUILD && !defined PICO
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


const DynamicBitset& Bitset2D::at(uint32_t index) const
{
#if defined IS_DEBUG_BUILD && !defined PICO
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
#if defined IS_DEBUG_BUILD && !defined PICO
	if (coord_x >= _width || coord_y >= _height) throw(std::out_of_range("Bitset2D::get_bit"));
#endif
	return _plane.at(coord_x).at(coord_y);
}

Bitset2D& Bitset2D::copy(uint32_t x_start, uint32_t y_start, uint32_t width, uint32_t height, Bitset2D& destination) const
{
	destination.clear();
	if (x_start >= _width || y_start >= _height) return destination;
	width += x_start;
	if (width > _width) width = _width;
	if (y_start + height > _height) height = _height - y_start;
	destination._height = height;
	for (; x_start < width; x_start++) destination.push_back(_plane[x_start].copy_unsafe(y_start, height));
	return destination;
}


void Bitset2D::put_chars(uint32_t coord_x, uint32_t coord_y, FONT& font, KEY_SET text, bool resize_if_needed)
{
	// TODO: Same code, simplify
	uint32_t x = coord_x;
	uint32_t y = coord_y;
	for (uint32_t i = 0; i < text.size(); i++) {
		if (text[i] == '\n') {
			y += font.at(0).height();
			if (y >= _height) {
				if (resize_if_needed) extend_down(y - _height + 1, false);
				else return;
			}
			x = coord_x;
		} else {
			Bitset2D rendered = font.at(text[i]);
			set(x, y, rendered, resize_if_needed);
			x += rendered.width() + 1;
			if (x >= _width) return;
		}
	}
}

void Bitset2D::put_chars(uint32_t coord_x, uint32_t coord_y, FONT& font, const std::string& text, bool resize_if_needed)
{
	uint32_t x = coord_x;
	uint32_t y = coord_y;
	for (uint32_t i = 0; i < text.size(); i++) {
		if (text[i] == '\n') {
			y += font.at(0).height();
			if (y >= _height) {
				if (resize_if_needed) extend_down(y - _height + 1, false);
				else return;
			}
			x = coord_x;
		} else {
			KEY key = text[i];
			Bitset2D rendered = font.contains(key) ? font.at(key) : font.at(0);
			set(x, y, rendered, resize_if_needed);
			x += rendered.width() + 1;
			if (x >= _width) return;
		}
	}
}

void Bitset2D::put_number_aligned_right(uint32_t coord_x, uint32_t coord_y, FONT& font, uint16_t number)
{
	if (coord_x >= _width || coord_y >= _height || coord_x < 4) return;
	coord_x -= 4;
	if (number == 0) {
		set(coord_x, coord_y, font.at('0'), false);
		return;
	}

	uint8_t width = font.at('0').width();
	while (number > 0) {
		set(coord_x, coord_y, font.at((number % 10) + 48), false);
		number /= 10;
		if (coord_x < width) return;
		coord_x -= width;
	}
}

void Bitset2D::draw_vertical_line(uint32_t coord_x, uint32_t coord_y, uint32_t length, bool value)
{
	_plane[coord_x].set(coord_y, length, value);
}

void Bitset2D::set(uint32_t coord_x, uint32_t coord_y, const Bitset2D& other, bool resize_if_needed)
{
#if defined IS_DEBUG_BUILD && !defined PICO
	if ((coord_x + other._width > _width || coord_y + other._height > _height) && !resize_if_needed) throw(std::out_of_range("Bitset2D::set"));
#endif
	if (resize_if_needed) {
		if (other._width + coord_x > _width) { extend_right(other._width + coord_x - _width, false); }
		if (other._height + coord_y > _height) { extend_down(other._height + coord_y - _height, false); }
	}
	uint32_t len = other._width < _width - coord_x ? other._width : _width - coord_x;
	for (uint32_t i = 0; i < len; i++) { _plane[i + coord_x].set(coord_y, other.at(i)); }
}

void Bitset2D::set_column(uint32_t coord_x, const DynamicBitset& other)
{
#if defined IS_DEBUG_BUILD && !defined PICO
	if (coord_x >= _width || other.size() != _height) throw(std::out_of_range("Bitset2D::set_column"));
#endif
	_plane[coord_x] = other;
}

void Bitset2D::set_bit(uint32_t coord_x, uint32_t coord_y, bool value)
{
#if defined IS_DEBUG_BUILD && !defined PICO
	if (coord_x >= _width || coord_y >= _height) throw(std::out_of_range("Bitset2D::set_bit"));
#endif
	_plane[coord_x].set(coord_y, value);
}

void Bitset2D::erase_x(uint32_t coord_x)
{
#if defined IS_DEBUG_BUILD && !defined PICO
	if (coord_x >= _width) throw(std::out_of_range("Bitset2D::erase_x"));
#endif
	_plane.erase(_plane.begin() + coord_x);
	_width--;
}

void Bitset2D::erase_y(uint32_t coord_y)
{
#if defined IS_DEBUG_BUILD && !defined PICO
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
#if defined IS_DEBUG_BUILD && !defined PICO
	if (other.size() != _height) throw(std::out_of_range("Bitset2D::push_back"));
#endif
	_plane.push_back(other);
	_width++;
}

void Bitset2D::push_front(const DynamicBitset& other)
{
	if (_height == 0) { _height = other.size(); }
#if defined IS_DEBUG_BUILD && !defined PICO
	if (other.size() != _height) throw(std::out_of_range("Bitset2D::push_back"));
#endif
	_plane.insert(_plane.begin(), other);
	_width++;
}

void Bitset2D::extend_right(const Bitset2D& other)
{
	if (_height == 0) { _height = other._height; }
#if defined IS_DEBUG_BUILD && !defined PICO
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
	if (_width < other._width) extend_right(other._width - _width, false);
	for (uint32_t i = 0; i < other._width; i++) { _plane[i].extend(other.at(i)); }
	if (_width > other._width) {
		for (uint32_t i = other._width; i < _width; i++) { _plane[i].extend(other._height, false); }
	}
	_height += other._height;
}

void Bitset2D::extend_down(uint32_t length, bool value)
{
	for (uint32_t i = 0; i < _width; i++) { _plane[i].extend(length, value); }
	_height += length;
}

void Bitset2D::extend_left(const Bitset2D& other)
{
#if defined IS_DEBUG_BUILD && !defined PICO
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
#if defined IS_DEBUG_BUILD && !defined PICO
	if (_width != other._width) throw(std::out_of_range("Bitset2D::extend_down"));
#endif
	for (uint32_t i = 0; i < other._width; i++) { _plane[i].extend_left(other.at(i)); }
	_height += other._height;
}

void Bitset2D::extend_up(uint32_t length, bool value)
{
	for (uint32_t i = 0; i < _width; i++) {
		_plane[i].extend_left(length, value);
	}
	_height += length;
}


std::string Bitset2D::to_string() const
{
	std::string s = "";
	for (uint32_t i = 0; i < _plane.size(); i++) { s += _plane[i].to_string(); }
	return s;
}

std::string Bitset2D::to_string_formatted() const
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
void Bitset2D::to_bmp(KEY_SET& bmp)
{
	uint32_t width = _width;
	uint32_t height = _height;
	uint32_t row_size = (width * 3 + 3) & (~3);
	uint32_t size = row_size * height + 54;
	bmp.resize(size);
	bmp[0] = 'B';
	bmp[1] = 'M';
	bmp[2] = size;
	bmp[3] = size >> 8;
	bmp[4] = size >> 16;
	bmp[5] = size >> 24;
	bmp[10] = 54;
	bmp[14] = 40;
	bmp[18] = width;
	bmp[19] = width >> 8;
	bmp[20] = width >> 16;
	bmp[21] = width >> 24;
	bmp[22] = height;
	bmp[23] = height >> 8;
	bmp[24] = height >> 16;
	bmp[25] = height >> 24;
	bmp[26] = 1;
	bmp[28] = 24;

	for (uint32_t i = 0; i < height; i++) {
		for (uint32_t j = 0; j < width; j++) {
			uint32_t index = 54 + (height - 1 - i) * row_size + j * 3;
			bmp[index] = _plane[j][i] ? 0 : 255;
			bmp[index + 1] = _plane[j][i] ? 0 : 255;
			bmp[index + 2] = _plane[j][i] ? 0 : 255;
		}
	}
}

void Bitset2D::from_bmp(const KEY_SET& bytes)
{
	if (bytes.empty()) {
		clear();
		return;
	}

	uint32_t width = bytes[18] | (bytes[19] << 8) | (bytes[20] << 16) | (bytes[21] << 24);
	uint32_t height = bytes[22] | (bytes[23] << 8) | (bytes[24] << 16) | (bytes[25] << 24);

	Bitset2D bitset(width, height, false);

	for (uint32_t i = 0; i < height; i++) {
		for (uint32_t j = 0; j < width; j++) {
			uint32_t index = 54 + (height - 1 - i) * ((width * 3 + 3) & (~3)) + j * 3;
			bool value = !(bytes[index] == 255 && bytes[index + 1] == 255 && bytes[index + 2] == 255);
			bitset.set_bit(j, i, value);
		}
	}

	*this = bitset;
}