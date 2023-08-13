#include "Graphics.h"
#include "Chars.h"
#include <map>

Graphics::Graphics()
{
}

Graphics::~Graphics()
{
}

render_plane Graphics::create_text(const std::string text, std::map<uint8_t, render_plane> table, int spacing) {
	std::string letter(1, text.at(0));
	render_plane Text = table.at(KEY_MAP.at(letter));
	std::vector<bool> empty = std::vector<bool>(Text.at(0).size(), false);
	for (size_t i = 1; i < text.length(); i++) {
		for (size_t i = 0; i < spacing; i++) {
			Text.push_back(empty);
		}
		letter = std::string(1, text.at(i));
		Text.insert(Text.end(), table.at(KEY_MAP.at(letter)).begin(), table.at(KEY_MAP.at(letter)).end());
	}
	return Text;
}