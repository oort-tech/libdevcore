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
/** @file OverlayDB.h
 * @author Gav Wood <i@gavwood.com>
 * @date 2014
 */

#pragma once

#include <memory>
#include <libdevcore/db.h>
#include <libdevcore/Common.h>
#include <libdevcore/Log.h>
#include <libdevcore/StateCacheDB.h>
#include <mcp/db/database.hpp>

namespace mcp
{
    class block_store;
}

namespace dev
{

class OverlayDB: public StateCacheDB
{
public:
    explicit OverlayDB(mcp::db::db_transaction & transaction_a, mcp::block_store &_store)
      : transaction(transaction_a), store(_store)
    {}

    ~OverlayDB();

    // Copyable
    OverlayDB(OverlayDB const&) = default;
    OverlayDB& operator=(OverlayDB const&) = default;
    // Movable
    OverlayDB(OverlayDB&&) = default;
    OverlayDB& operator=(OverlayDB&&) = default;

    void commit();
	void rollback();

	std::string lookup(h256 const& _h) const;
	bool exists(h256 const& _h) const;
	void kill(h256 const& _h);

	bytes lookupAux(h256 const& _h) const;

private:
	using StateCacheDB::clear;

    mcp::block_store &store;
    mcp::db::db_transaction &transaction;
};

}
