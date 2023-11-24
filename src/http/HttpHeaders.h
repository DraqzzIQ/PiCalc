#pragma once
#include <map>
#include <string>

#ifdef PICO // httplib not available on PICO
namespace httplib
{
namespace detail
{
struct ci {
	bool operator()(const std::string& s1, const std::string& s2) const
	{
		return std::lexicographical_compare(s1.begin(), s1.end(), s2.begin(), s2.end(), [](unsigned char c1, unsigned char c2) {
			return ::tolower(c1) < ::tolower(c2);
		});
	}
};
} // namespace detail
} // namespace httplib
#else
#include <httplib/httplib.h>
#endif

using Headers = std::multimap<std::string, std::string, httplib::detail::ci>;