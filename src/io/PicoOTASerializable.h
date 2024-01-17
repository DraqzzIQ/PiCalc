#include "io/ISerializable.h"
#include <string.h>

/// <summary>
/// Config for PicoOTA
/// </summary>
class PicoOTASerializable: public ISerializable
{
	public:
	/// <summary>
	/// converts the object to a vector of bytes
	/// </summary>
	std::vector<uint8_t> searialize();
	/// <summary>
	/// converts a vector of bytes to the object
	/// IMPORTANT: data needs to be recovered in the same order as it was saved
	/// </summary>
	void desearialize(std::vector<uint8_t> bytes);
	/// <summary>
	/// returns the size of the object in bytes
	/// by adding the size of all members
	/// </summary>
	size_t get_total_serialized_size();

	std::string get_ssid();
	std::string get_password();
	bool get_ap();

	void set_ssid(std::string ssid);
	void set_password(std::string password);
	void set_ap(bool ap);

	void set_defaults();

	const std::string dir_name = "picowota";
	const std::string file_name = "picowota.conf";

	private:
	std::string _ssid;
	std::string _password;
	bool _ap; // access point mode
};