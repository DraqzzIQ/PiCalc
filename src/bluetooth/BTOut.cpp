#ifdef PICO
#include "bluetooth/BTOut.h"

BTOut::BTOut(BTManager* bt_manager)
{
	_bt_manager = bt_manager;
}

void BTOut::receive(char c)
{
	_bt_manager->send_char(c);
}

#endif
