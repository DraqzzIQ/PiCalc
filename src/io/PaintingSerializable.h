#pragma once
#include "datastructs/Bitset2D.h"
#include "io/ISerializable.h"

/// <summary>
/// used to store paint files
/// </summary>
class PaintingSerializable: public ISerializable
{
	public:
	PaintingSerializable(const Bitset2D& bitmap);
	PaintingSerializable();

	void set_bitmap(const Bitset2D& bitmap);
	Bitset2D get_bitmap();

	protected:
	std::vector<uint8_t> searialize() override;
	void desearialize(std::vector<uint8_t> bytes) override;
	size_t get_total_serialized_size() override;

	private:
	Bitset2D _bmp;
};