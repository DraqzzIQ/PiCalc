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
	Bitset2D error_rendered;
	switch (_error) {
	case ErrorType::MATH_ERROR:
		error_rendered = Graphics::create_text("Math Error");
		break;
	case ErrorType::PUFFER_ERROR:
		error_rendered = Graphics::create_text("Puffer Error");
		break;
	case ErrorType::SYNTAX_ERROR:
		error_rendered = Graphics::create_text("Syntax Error");
		break;
	case ErrorType::ARGUMENT_ERROR:
		error_rendered = Graphics::create_text("Argument Error");
		break;
	case ErrorType::STORAGE_ERROR:
		error_rendered = Graphics::create_text("Storage Error");
		break;
	case ErrorType::TIME_ERROR:
		error_rendered = Graphics::create_text("Time Error");
		break;
	case ErrorType::FINE:
		error_rendered = Graphics::create_text("Fine");
		break;
	}
	return error_rendered;
}

void Error::error_handled()
{
	_error = ErrorType::FINE;
}