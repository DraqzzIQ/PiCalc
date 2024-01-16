#include "Error.h"

Error::ErrorType Error::_error = ErrorType::FINE;

void Error::throw_error(ErrorType err)
{
	if (_error == ErrorType::FINE) _error = err;
}

bool Error::error_thrown()
{
	return _error != ErrorType::FINE;
}

Error::ErrorType Error::get_error()
{
	return _error;
}

Bitset2D Error::render_error()
{
	Bitset2D error_rendered = Bitset2D(SCREEN_WIDTH, SCREEN_HEIGHT, false);
	switch (_error) {
	case ErrorType::MATH_ERROR:
		error_rendered.put_chars(1, 1, Graphics::SYMBOLS_6_HIGH, KEY_SET{ 22, 40, 59, 47, 81, 70, 15, 44, 47, 51, 44, 57 }, false);
		break;
	case ErrorType::PUFFER_ERROR:
		error_rendered.put_chars(1, 1, Graphics::SYMBOLS_6_HIGH, KEY_SET{ 25, 60, 45, 45, 44, 57, 45, 44, 47, 51, 44, 57 }, false);
		break;
	case ErrorType::SYNTAX_ERROR:
		error_rendered.put_chars(1, 1, Graphics::SYMBOLS_6_HIGH, KEY_SET{ 28, 64, 53, 59, 40, 63, 45, 44, 47, 51, 44, 57 }, false);
		break;
	case ErrorType::ARGUMENT_ERROR:
		error_rendered.put_chars(1, 1, Graphics::SYMBOLS_6_HIGH, KEY_SET{ 10, 57, 46, 60, 52, 44, 53, 59, 45, 44, 47, 51, 44, 57 }, false);
		break;
	case ErrorType::STORAGE_ERROR:
		error_rendered.put_chars(1, 1, Graphics::SYMBOLS_6_HIGH, KEY_SET{ 30, 53, 65, 60, 57, 81, 80, 28, 55, 44, 48, 42, 47 }, false);
		break;
	case ErrorType::TIME_ERROR:
		error_rendered.put_chars(1, 1, Graphics::SYMBOLS_6_HIGH, KEY_SET{ 35, 44, 48, 59, 45, 44, 47, 51, 44, 57 }, false);
		break;
	}
	error_rendered.put_chars(1, 16, Graphics::SYMBOLS_6_HIGH, KEY_SET{ 76, 10, 12, 77 }, false);
	error_rendered.put_chars(37, 16, Graphics::SYMBOLS_6_HIGH, KEY_SET{ 84, 10, 41, 41, 57, 60, 42, 47 }, false);
	error_rendered.put_chars(1, 24, Graphics::SYMBOLS_6_HIGH, KEY_SET{ 76, 181, 77, 76, 182, 77, 84, 32, 44, 48, 59, 44, 57 }, false);
	return error_rendered;
}

void Error::error_handled()
{
	_error = ErrorType::FINE;
}