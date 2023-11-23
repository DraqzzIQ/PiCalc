#include <map>
#include <string>

#ifndef CPPHTTPLIB_HTTPLIB_H
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
#endif

using Headers = std::multimap<std::string, std::string, httplib::detail::ci>;