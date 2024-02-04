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
		error_rendered.put_chars(1, 1, Graphics::SYMBOLS_6_HIGH, "Math-Error", false);
		break;
	case ErrorType::PUFFER_ERROR:
		error_rendered.put_chars(1, 1, Graphics::SYMBOLS_6_HIGH, "Puffer-Error", false);
		break;
	case ErrorType::SYNTAX_ERROR:
		error_rendered.put_chars(1, 1, Graphics::SYMBOLS_6_HIGH, "Syntax-Error", false);
		break;
	case ErrorType::ARGUMENT_ERROR:
		error_rendered.put_chars(1, 1, Graphics::SYMBOLS_6_HIGH, "Argument-Error", false);
		break;
	case ErrorType::STORAGE_ERROR:
		error_rendered.put_chars(1, 1, Graphics::SYMBOLS_6_HIGH, "Storage-Error", false);
		break;
	case ErrorType::TIME_ERROR:
		error_rendered.put_chars(1, 1, Graphics::SYMBOLS_6_HIGH, "Time-Error", false);
		break;
	}
	error_rendered.put_chars(1, 16, Graphics::SYMBOLS_6_HIGH, "[AC]  :Abbruch", false);
	error_rendered.put_chars(0, 24, Graphics::SYMBOLS_6_HIGH, "[\272][\273]:Weiter", false);
	return error_rendered;
}

void Error::error_handled()
{
	_error = ErrorType::FINE;
}