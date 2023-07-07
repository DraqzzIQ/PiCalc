#include "Graphics.h"

Graphics::Graphics()
{
}

Graphics::~Graphics()
{
}

/// <summary>
/// creates a big Text (height: 9px) with a spacing of one
/// </summary>
/// <param name="text">text Input</param>
/// <returns></returns>
render_plane Graphics::createText(std::string text) {
	render_plane Text = SYMBOLS_BIG[text.at(0)];
	std::vector<bool> empty = std::vector<bool>(9, false);
	for (int i = 1; i < text.length(); i++) {
		Text.push_back(empty);
		Text.insert(Text.end(), SYMBOLS_BIG[text.at(i)].begin(), SYMBOLS_BIG[text.at(i)].end());
	}
	return Text;
}