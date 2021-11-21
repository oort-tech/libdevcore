/*
    This file is part of cpp-ethereum.

    cpp-ethereum is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    cpp-ethereum is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with cpp-ethereum.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <thread>
#include <libdevcore/db.h>
#include <libdevcore/Common.h>
#include "SHA3.h"
#include "OverlayDB.h"
#include "TrieDB.h"
#include <mcp/blockstore.hpp>

namespace dev
{
namespace
{
inline db::Slice toSlice(h256 const& _h)
{
    return db::Slice(reinterpret_cast<char const*>(_h.data()), _h.size);
}

inline db::Slice toSlice(std::string const& _str)
{
    return db::Slice(_str.data(), _str.size());
}

inline db::Slice toSlice(bytes const& _b)
{
    return db::Slice(reinterpret_cast<char const*>(&_b[0]), _b.size());
}

}  // namespace

OverlayDB::~OverlayDB() = default;

void OverlayDB::commit()
{
    for (auto const& i: m_main)
    {
        if (i.second.second)
        {
            store.contract_state_put(transaction, mcp::uint256_union(i.first), i.second.first);
            std::cout << "commit: " << mcp::uint256_union(i.first).to_string() << " string: " << i.second.first <<std::endl;
        }
    }

    for (auto const& i: m_aux)
    {
    }

    m_aux.clear();
    m_main.clear();
}

bytes OverlayDB::lookupAux(h256 const& _h) const
{
    /*
    bytes ret = StateCacheDB::lookupAux(_h);
    if (!ret.empty() || !m_db)
        return ret;

    bytes b = _h.asBytes();
    b.push_back(255);   // for aux
    std::string const v = m_db->lookup(toSlice(b));
    if (v.empty())
        cwarn << "Aux not found: " << _h;

    return asBytes(v);
    */

    throw std::runtime_error("lookupAux not Implemented");
}

void OverlayDB::rollback()
{
#if DEV_GUARDED_DB
    WriteGuard l(x_this);
#endif
    m_main.clear();
}

std::string OverlayDB::lookup(h256 const& _h) const
{
    std::string ret = StateCacheDB::lookup(_h);
    if (!ret.empty())
        return ret;

    std::string value;
    bool error = store.contract_state_get(transaction, mcp::uint256_union(_h), value);
    std::cout << "looktup: " << mcp::uint256_union(_h).to_string() << " string: " << value.size() << std::endl;
    return value;

    /*
    std::string ret = StateCacheDB::lookup(_h);
    if (!ret.empty() || !m_db)
        return ret;

    return m_db->lookup(toSlice(_h));
    */
}

bool OverlayDB::exists(h256 const& _h) const
{
    if (StateCacheDB::exists(_h))
        return true;

    std::string value;
    return !store.contract_state_get(transaction, mcp::uint256_union(_h), value);

    /*
    return m_db && m_db->exists(toSlice(_h));
    */
}

void OverlayDB::kill(h256 const& _h)
{
/*
#if ETH_PARANOIA || 1
    if (!StateCacheDB::kill(_h))
    {
        if (m_db)
        {
            if (!m_db->exists(toSlice(_h)))
            {
                // No point node ref decreasing for EmptyTrie since we never bother incrementing it
                // in the first place for empty storage tries.
                if (_h != EmptyTrie)
                    cnote << "Decreasing DB node ref count below zero with no DB node. Probably "
                             "have a corrupt Trie."
                          << _h;
                // TODO: for 1.1: ref-counted triedb.
            }
        }
    }
#else
    StateCacheDB::kill(_h);
#endif
*/
}

}
