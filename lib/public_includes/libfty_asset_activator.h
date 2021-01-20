/*  =========================================================================
    libfty_asset_activator - Interface for fty-asset-activator library

    Copyright (C) 2019 - 2020 Eaton

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
    =========================================================================
*/

#ifndef LIBFTY_ASSET_ACTIVATOR_H_INCLUDED
#define LIBFTY_ASSET_ACTIVATOR_H_INCLUDED

#include <list>
#include <string>
#include <vector>

namespace fty
{
    class FullAsset;
    class SyncClient;

    class AssetActivator
    {
    public:
        /**
         * @brief Construct a new Accessor object
         *
         * @param Object implementing fty::SyncClient
         */
        explicit AssetActivator(fty::SyncClient & requestClient);

        bool isActive (const std::string& assetJson) const;
        bool isActive (const fty::FullAsset& asset) const;
        bool isActiveIname (const std::string& iname) const;
        void activate (const std::string& assetJson) const;
        void activate (const fty::FullAsset& asset) const;
        void activateIname (const std::list<std::string>& inamesList) const;
        void deactivate (const std::string& assetJson) const;
        void deactivate (const fty::FullAsset& asset) const;
        void deactivateIname (const std::list<std::string>& inamesList) const;
        bool isActivable (const std::string& assetJson) const;
        bool isActivable (const fty::FullAsset& asset) const;
        bool isActivableIname (const std::string& iname) const;

    private:
        fty::SyncClient & m_requestClient;

        std::vector<std::string> sendCommand(const std::string & command, const std::vector<std::string> & frames) const;
    };
}

#endif
