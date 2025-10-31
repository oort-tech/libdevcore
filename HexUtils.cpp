// Olympus: mcp C++ client, tools and libraries.
// Licensed under the GNU General Public License, Version 3.

#include "HexUtils.h"

std::string dev::toCompactHexFromIntx(intx::uint256 value)
{
        std::ostringstream out;
        out << "0x";

        if (value == 0)
        {
                out << '0';
                return out.str();
        }

        std::string hex;
        hex.reserve(64);

        while (value != 0)
        {
                auto nibble = static_cast<unsigned>(value & intx::uint256{0xF});
                hex.push_back(nibble < 10 ? static_cast<char>('0' + nibble)
                                          : static_cast<char>('a' + (nibble - 10)));
                value >>= 4;
        }

        if (hex.size() % 2 != 0)
                hex.push_back('0');

        std::reverse(hex.begin(), hex.end());
        out << hex;
        return out.str();
}