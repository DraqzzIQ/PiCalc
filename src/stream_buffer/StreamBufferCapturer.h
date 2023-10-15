#pragma once
#include "stream_buffer/IStreamBufferReceiver.h"
#include <iostream>
#include <sstream>
#include <streambuf>

using int_type = std::streambuf::int_type;
using traits_type = std::streambuf::traits_type;

/// <summary>
/// Captures a stream buffer and forwards all characters to a receiver.
/// </summary>
class StreamBufferCapturer: public std::stringbuf
{
	public:
	StreamBufferCapturer(std::streambuf* originalBuffer, IStreamBufferReceiver* receiver);
	int_type overflow(int_type c = traits_type::eof());

	private:
	std::streambuf* _original_buffer;
	IStreamBufferReceiver* _receiver;
};
