#pragma once
#include "io/ISerializable.h"

/// <summary>
/// used to store text data
/// </summary>
class NoteSerializable: public ISerializable
{
	public:
	NoteSerializable();
	NoteSerializable(const std::vector<std::string>& text);

	void set_text(const std::vector<std::string>& text);
	std::vector<std::string> get_text();

	protected:
	std::vector<uint8_t> searialize() override;
	void desearialize(std::vector<uint8_t> bytes) override;
	size_t get_total_serialized_size() override;

	private:
	std::vector<std::string> _text;
};