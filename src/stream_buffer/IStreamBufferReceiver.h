#pragma once

/// <summary>
/// Interface for receiving characters from a stream buffer.
/// </summary>
class IStreamBufferReceiver
{
	public:
	virtual ~IStreamBufferReceiver(){};
	virtual void receive(char c) = 0;
};
