#include "WolframAlphaWindow.h"

WolframAlphaWindow::WolframAlphaWindow():
	_client(_base_url)
{
}

WolframAlphaWindow::~WolframAlphaWindow()
{
}

Bitset2D WolframAlphaWindow::update_window()
{
	if (Utils::us_since_boot() > _last_blink_time + 500000) {
		_last_blink_time = Utils::us_since_boot();
		_show_cursor = !_show_cursor;
	}

	clear_window();
	create_menu();

	corner_y = current_page * 4 * line_height;

	return get_render_canvas();
}

void WolframAlphaWindow::create_menu()
{
	for (uint32_t i = 0; i < text.size(); i++) {
		add_to_window(Graphics::create_text(text[i], Graphics::SYMBOLS_6_HIGH, text_spacing), 0, 1 + i * line_height);
	}
	if (_show_cursor) {
		if (text.size() == 0)
			add_to_window(Bitset2D(2, 9, true), 0, 0);
		else {
			uint16_t cursor_x = Utils::get_string_as_pixel_width(text.back(), Graphics::SYMBOLS_6_HIGH, text_spacing);
			uint16_t cursor_y = (text.size() - 1) * line_height;

			add_to_window(Bitset2D(2, 9, true), cursor_x, cursor_y);
		}
	}
}

bool WolframAlphaWindow::handle_key_down(KeyPress keypress)
{
	if (TextWindow::handle_key_down(keypress))
		return true;

	if (keypress.key_keyboard == Chars::CHAR_TO_KEYCODE.at("RETURN")) {
		add_text("...", false, false, false);
		request(_input);
		_input = "";
		text.push_back("");
		return true;
	}
	if (keypress.key_keyboard == Chars::CHAR_TO_KEYCODE.at("DEL")) {
		if (_input.size() > 0)
			_input.pop_back();
		remove_chars();
		return true;
	}

	std::string key = Chars::KEY_MAP[keypress.key_keyboard];
	if (key == "unknown")
		return false;

	_input += key;
	add_text(key, false, false, false);
	return true;
}

void WolframAlphaWindow::request(std::string query)
{
	Params params = _default_params;
	params.emplace("i", query);
	HttpResponse res = _client.get(_endpoint, HttpRequest(params));

	if (res.error()) {
		add_text("error: " + res.error_msg, true, true, false);
		text.push_back("");
		return;
	}

	add_text(res.body, true, true, false);
	text.push_back("");
}
