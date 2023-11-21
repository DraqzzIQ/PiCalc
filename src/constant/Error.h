#pragma once
#include "Graphics.h"
#include "constant/Constants.h"
#include "datastructs/Bitset2D.h"

static class Error
{
	public:
	enum class ErrorType { MATH_ERROR,
		                   PUFFER_ERROR,
		                   SYNTAX_ERROR,
		                   ARGUMENT_ERROR,
		                   STORAGE_ERROR,
		                   TIME_ERROR,
		                   FINE };

	static void throw_error(ErrorType err);
	static bool error_thrown();
	static ErrorType get_error();
	static Bitset2D render_error();
	static void error_handled();

	private:
	static ErrorType _error;
};
