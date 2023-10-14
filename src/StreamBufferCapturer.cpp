#include "StreamBufferCapturer.h"

StreamBufferCapturer::StreamBufferCapturer(std::streambuf* originalBuffer, IStreamBufferReceiver* receiver)
{
	this->_original_buffer = originalBuffer;
	this->_receiver = receiver;
}

int_type StreamBufferCapturer::overflow(int_type c)
{
	if (!traits_type::eq_int_type(c, traits_type::eof())) {
		_receiver->receive(traits_type::to_char_type(c));
		if (_original_buffer)
			return _original_buffer->sputc(c);
	}
	return traits_type::not_eof(c);
}