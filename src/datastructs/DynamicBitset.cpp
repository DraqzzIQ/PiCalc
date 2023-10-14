#include "datastructs/DynamicBitset.h"


DynamicBitset::DynamicBitset()
{
	_bits = std::vector<uint8_t>();
	_bit_count = 0;
}

DynamicBitset::DynamicBitset(uint32_t count)
{
	_bits = std::vector<uint8_t>((count + 7) / 8);
	_bit_count = count;
}

DynamicBitset::DynamicBitset(uint32_t count, bool value)
{
	_bits = std::vector<uint8_t>((count + 7) / 8, value ? 0xFF : 0x00);
	_bit_count = count;
}

DynamicBitset::DynamicBitset(uint32_t count, std::vector<uint8_t> values)
{
	_bits = std::vector<uint8_t>(values.begin(), values.begin() + (count + 7) / 8);
	_bit_count = count;
}

DynamicBitset::DynamicBitset(uint32_t count, std::vector<bool> values)
{
	_bits = std::vector<uint8_t>();
	uint8_t byte_i = 0;
	uint8_t byte = 0;
	for (uint32_t i = 0; i < count; i++) {
		if (byte_i == 8) {
			_bits.push_back(byte);
			byte = 0;
			byte_i = 0;
		}
		byte |= values[i] << (7 - byte_i);
		byte_i++;
	}
	_bits.push_back(byte);
	_bit_count = count;
}

DynamicBitset::DynamicBitset(const DynamicBitset& other)
{
	_bits = other._bits;
	_bit_count = other._bit_count;
}

DynamicBitset::~DynamicBitset() {}


DynamicBitset DynamicBitset::from_bits(uint8_t bits, uint32_t count)
{
	DynamicBitset bs;
	bs._bits = std::vector<uint8_t>((count + 7) / 8, bits);
	bs._bit_count = count;
	return bs;
}


bool DynamicBitset::operator[](uint32_t i) const
{
#ifdef IS_DEBUG_BUILD
	if (i >= _bit_count) { throw std::out_of_range("DynamicBitset::operator[]"); }
#endif
	return (_bits[i / 8] & (1 << (7 - (i % 8)))) != 0;
}

bool DynamicBitset::operator==(const DynamicBitset& other) const
{
	return _bits == other._bits;
}

bool DynamicBitset::operator!=(const DynamicBitset& other) const
{
	return _bits != other._bits;
}

DynamicBitset& DynamicBitset::operator=(const DynamicBitset& other)
{
	_bits = other._bits;
	_bit_count = other._bit_count;
	return *this;
}

DynamicBitset DynamicBitset::operator+(const DynamicBitset& other)
{
	DynamicBitset res(*this);
	res.extend(other);
	return res;
}


bool DynamicBitset::at(uint32_t index) const
{
	return operator[](index);
}

uint32_t DynamicBitset::size() const
{
	return _bit_count;
}

std::vector<uint8_t> DynamicBitset::get_bytes() const
{
	return _bits;
}


void DynamicBitset::set(uint32_t index, bool value)
{
#ifdef IS_DEBUG_BUILD
	if (index >= _bit_count) { throw std::out_of_range("DynamicBitset::set"); }
#endif
	if (value) {
		_bits[index / 8] |= (1 << (7 - (index % 8)));
	} else {
		_bits[index / 8] &= ~(1 << (7 - (index % 8)));
	}
}

void DynamicBitset::set(uint32_t index, const DynamicBitset& bits)
{
#ifdef IS_DEBUG_BUILD
	if (index + bits.size() > _bit_count) { throw std::out_of_range("DynamicBitset::set"); }
#endif
	if (index % 8 == 0) {
		for (uint32_t i = 0; i < bits.size() / 8; i++) { _bits[index / 8 + i] = bits._bits[i]; }
		for (uint32_t i = 0; i < bits.size() % 8; i++) { set(index + bits.size() - bits.size() % 8 + i, bits[bits.size() - bits.size() % 8 + i]); }
		return;
	}

	for (uint32_t i = 0; i < bits.size(); i++) { set(index + i, bits[i]); }
}

void DynamicBitset::insert(uint32_t index, bool bit)
{
#ifdef IS_DEBUG_BUILD
	if (index > _bit_count) { throw std::out_of_range("DynamicBitset::insert"); }
#endif
	// If the last byte is full, add a new one
	if (_bit_count % 8 == 0) { _bits.push_back(0x00); }
	// Shift all bits after i one to the right
	for (uint32_t i = _bit_count; i > index; i--) {
		if (at(i - 1)) {
			_bits[i / 8] |= (1 << (7 - (i % 8)));
		} else {
			_bits[i / 8] &= ~(1 << (7 - (i % 8)));
		}
	}
	// Insert the new bit
	if (bit) {
		_bits[index / 8] |= (1 << (7 - (index % 8)));
	} else {
		_bits[index / 8] &= ~(1 << (7 - (index % 8)));
	}
	_bit_count++;
}

void DynamicBitset::insert(uint32_t index, const DynamicBitset& bits)
{
#ifdef IS_DEBUG_BUILD
	if (index > _bit_count) { throw std::out_of_range("DynamicBitset::insert"); }
#endif
	if (index % 8 == 0) {
		_bits.insert(_bits.begin() + index / 8, bits._bits.begin(), bits._bits.begin() + bits.size() / 8);
		for (uint32_t i = 0; i < bits.size() % 8; i++) { insert(index + bits.size() - bits.size() % 8 + i, bits[bits.size() - bits.size() % 8 + i]); }
		return;
	}

	for (uint32_t i = 0; i < bits.size(); i++) { insert(index + i, bits[i]); }
}

void DynamicBitset::erase(uint32_t index)
{
#ifdef IS_DEBUG_BUILD
	if (index >= _bit_count) { throw std::out_of_range("DynamicBitset::erase"); }
#endif
	// Shift all bits after i one to the left
	for (uint32_t i = index; i < _bit_count - 1; i++) {
		if (operator[](i + 1)) {
			_bits[i / 8] |= (1 << (7 - (i % 8)));
		} else {
			_bits[i / 8] &= ~(1 << (7 - (i % 8)));
		}
	}
	_bit_count--;
	// If the last byte is empty, remove it
	if (_bit_count % 8 == 0) { _bits.pop_back(); }
}

void DynamicBitset::resize(uint32_t count)
{
	_bits.resize((count + 7) / 8, 0x00);
	_bit_count = count;
}

void DynamicBitset::clear()
{
	_bits.clear();
	_bit_count = 0;
}


void DynamicBitset::push_back(bool bit)
{
	// If the last byte is full, add a new one
	if (_bit_count % 8 == 0) { _bits.push_back(0x00); }
	if (bit) {
		_bits[_bits.size() - 1] |= (1 << (7 - (_bit_count % 8)));
	} else {
		_bits[_bits.size() - 1] &= ~(1 << (7 - (_bit_count % 8)));
	}
	_bit_count++;
}

void DynamicBitset::pop_back()
{
#ifdef IS_DEBUG_BUILD
	if (_bit_count == 0) { throw std::out_of_range("DynamicBitset::pop_back"); }
#endif
	_bit_count--;
	// If the last byte is empty, remove it
	if (_bit_count % 8 == 0) { _bits.pop_back(); }
}

void DynamicBitset::extend(const DynamicBitset& other)
{
	if (_bit_count % 8 == 0) {
		_bits.insert(_bits.end(), other._bits.begin(), other._bits.end());
		_bit_count += other._bit_count;
		return;
	}

	for (uint32_t i = 0; i < other._bit_count; i++) { push_back(other[i]); }
}

void DynamicBitset::extend(uint32_t length, bool value)
{
	for (uint8_t i = 0; i < length; i++) { push_back(value); }
}

void DynamicBitset::extend_left(const DynamicBitset& other)
{
	DynamicBitset beginning(other);
	for (uint32_t i = 0; i < _bit_count; i++) { beginning.push_back(at(i)); }
	_bits = beginning._bits;
	_bit_count = beginning._bit_count;
}

void DynamicBitset::extend_left(uint32_t length, bool value)
{
	extend_left(DynamicBitset(length, value));
}


std::string DynamicBitset::to_string() const
{
	std::string str = "";
	for (uint32_t i = 0; i < _bit_count; i++) { str += operator[](i) ? "1" : "0"; }
	return str;
}

std::string DynamicBitset::to_string_formatted(uint32_t bytes_per_line) const
{
	std::string str = "";
	uint32_t bits_per_line = bytes_per_line * 8;
	for (uint32_t i = 0; i < _bit_count; i++) {
		str += operator[](i) ? "1" : "0";
		if (i % bits_per_line == bits_per_line - 1) {
			str += "\n";
		} else if (i % 8 == 7) {
			str += " ";
		}
	}
	return str;
}
