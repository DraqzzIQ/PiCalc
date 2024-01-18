#include "io/PaintingSerializable.h"

PaintingSerializable::PaintingSerializable(const Bitset2D& bitmap)
{
	_bmp = bitmap;
}

PaintingSerializable::PaintingSerializable()
{
}

void PaintingSerializable::set_bitmap(const Bitset2D& bitmap)
{
	_bmp = bitmap;
}

Bitset2D PaintingSerializable::get_bitmap()
{
	return _bmp;
}

std::vector<uint8_t> PaintingSerializable::searialize()
{
	std::vector bitmap = _bmp.to_bmp();
	size_t offset = 0;

	std::vector<uint8_t> bytes = bitmap;
	offset += bytes.size() + 1;

	return bytes;
}

void PaintingSerializable::desearialize(std::vector<uint8_t> bytes)
{
	size_t offset = 0;

	bytes.pop_back(); // remove null terminator
	_bmp.from_bmp(bytes);
}

size_t PaintingSerializable::get_total_serialized_size()
{
	// +1 for the null terminator
	return _bmp.to_bmp().size() + 1;
}