#pragma once
#ifdef PICO
#include "bluetooth/BTManager.h"
#include "stream_buffer/IStreamBufferReceiver.h"

/// <summary>
/// Receives characters from the stream buffer and sends them to the connected device
/// </summary>
class BTOut: public IStreamBufferReceiver
{
	public:
	BTOut(BTManager* bt_manager);
	void receive(char c);

	private:
	BTManager* _bt_manager;
};

#endif
