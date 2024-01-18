#include "io/NoteSerializable.h"

NoteSerializable::NoteSerializable()
{
}

NoteSerializable::NoteSerializable(const std::vector<std::string>& text)
{
	_text = text;
}

void NoteSerializable::set_text(const std::vector<std::string>& text)
{
	_text = text;
}

std::vector<std::string> NoteSerializable::get_text()
{
	return _text;
}

void NoteSerializable::desearialize(std::vector<uint8_t> bytes)
{
	std::string text = "";
	for (int i = 0; i < bytes.size(); i++) {
		if (bytes[i] == '\n') {
			_text.push_back(text);
			text = "";
		} else {
			text += bytes[i];
		}
	}
}

std::vector<uint8_t> NoteSerializable::searialize()
{
	std::vector<uint8_t> bytes;

	for (int i = 0; i < _text.size(); i++) {
		std::string text = _text[i];
		for (int j = 0; j < text.size(); j++) {
			bytes.push_back(text[j]);
		}
		bytes.push_back('\n');
	}

	return bytes;
}

size_t NoteSerializable::get_total_serialized_size()
{
	return size_t();
}
