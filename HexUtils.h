// Olympus: mcp C++ client, tools and libraries.
// Licensed under the GNU General Public License, Version 3.

#pragma once

#include <intx/intx.hpp>
#include <string>
#include <algorithm>
#include <sstream>

namespace dev
{
    std::string toCompactHexFromIntx(intx::uint256 value);
}