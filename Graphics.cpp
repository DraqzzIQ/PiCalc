#include "Graphics.h"
#include <map>

Graphics::Graphics()
{
}

Graphics::~Graphics()
{
}

render_plane Graphics::create_text(const std::string text, int spacing, std::map<wchar_t, render_plane> table) {
	render_plane Text = table.at(text.at(0));
	std::vector<bool> empty = std::vector<bool>(Text.at(0).size(), false);
	for (int i = 1; i < text.length(); i++) {
		Text.push_back(empty);
		Text.insert(Text.end(), table.at(text.at(i)).begin(), table.at(text.at(i)).end());
	}
	return Text;
}

render_plane Graphics::create_text(const std::wstring text, int spacing, std::map<wchar_t, render_plane> table) {
	render_plane Text = table.at(text.at(0));
	std::vector<bool> empty = std::vector<bool>(Text.at(0).size(), false);
	for (int i = 1; i < text.length(); i++) {
		Text.push_back(empty);
		Text.insert(Text.end(), table.at(text.at(i)).begin(), table.at(text.at(i)).end());
	}
	return Text;
}