#include "Graphics.h"

Graphics::Graphics()
{
}

Graphics::~Graphics()
{
}

render_plane Graphics::create_text(const std::string text) {
	render_plane Text = SYMBOLS_BIG.at(text.at(0));
	std::vector<bool> empty = std::vector<bool>(9, false);
	for (int i = 1; i < text.length(); i++) {
		Text.push_back(empty);
		Text.insert(Text.end(), SYMBOLS_BIG.at(text.at(i)).begin(), SYMBOLS_BIG.at(text.at(i)).end());
	}
	return Text;
}

render_plane Graphics::create_text(const std::wstring text) {
	render_plane Text = SYMBOLS_BIG.at(text.at(0));
	std::vector<bool> empty = std::vector<bool>(9, false);
	for (int i = 1; i < text.length(); i++) {
		Text.push_back(empty);
		Text.insert(Text.end(), SYMBOLS_BIG.at(text.at(i)).begin(), SYMBOLS_BIG.at(text.at(i)).end());
	}
	return Text;
}