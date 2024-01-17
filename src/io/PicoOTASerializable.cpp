#include "PicoOTASerializable.h"


std::vector<uint8_t> PicoOTASerializable::searialize()
{
	std::vector<uint8_t> bytes = std::vector<uint8_t>(get_total_serialized_size());
	size_t offset = 0;

	memcpy(bytes.data() + offset, _ssid.c_str(), _ssid.size() + 1);
	offset += _ssid.size() + 1;

	memcpy(bytes.data() + offset, _password.c_str(), _password.size() + 1);
	offset += _password.size() + 1;

	bytes[offset] = _ap;
	offset += 1;

	return bytes;
}

void PicoOTASerializable::desearialize(std::vector<uint8_t> bytes)
{
	size_t offset = 0;

	_ssid = std::string((char*)bytes.data() + offset);
	offset += _ssid.size() + 1;

	_password = std::string((char*)bytes.data() + offset);
	offset += _password.size() + 1;

	_ap = bytes[offset];
	offset += 1;
}

size_t PicoOTASerializable::get_total_serialized_size()
{
	// +2 for the null terminators
	return _ssid.size() + _password.size() + 2 + 1;
}


std::string PicoOTASerializable::get_ssid()
{
	return _ssid;
}
std::string PicoOTASerializable::get_password()
{
	return _password;
}
bool PicoOTASerializable::get_ap()
{
	return _ap;
}

void PicoOTASerializable::set_ssid(std::string ssid)
{
	_ssid = ssid;
}
void PicoOTASerializable::set_password(std::string password)
{
	_password = password;
}
void PicoOTASerializable::set_ap(bool ap)
{
	_ap = ap;
}


void PicoOTASerializable::set_defaults()
{
	_ssid = "pico-ota";
	_password = "pico1234";
	_ap = true;
}