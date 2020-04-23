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

/*
@header
    libfty_asset_activator - Interface for fty-asset-activator library
@discuss
@end
*/

#include "fty_asset_activator_classes.h"

namespace fty {

    AssetActivator::AssetActivator(fty::SyncClient & requestClient)
        : m_requestClient(requestClient)
    {}

    bool AssetActivator::isActive(const std::string & asset_json) const
    {
        std::vector<std::string> payload;
        try
        {
            payload = sendCommand (IS_ASSET_ACTIVE, {asset_json});
        }
        catch (const std::exception& e)
        {
            log_info ("asset activator returned '%s', treated as false", e.what());
            return false;
        }

        bool rv;
        std::istringstream isActiveStr (payload[0]);
        log_debug ("asset is active = %s", payload[0].c_str ());
        isActiveStr >> std::boolalpha >> rv;
        return rv;
    }

    bool AssetActivator::isActive (const fty::FullAsset &asset) const
    {
        return isActive (asset.toJson());
    }

    void AssetActivator::activate(const std::string & asset_json) const
    {
        std::vector<std::string> payload;
        payload = sendCommand (ACTIVATE_ASSET, {asset_json});
    }

    void AssetActivator::activate (const fty::FullAsset& asset) const
    {
        activate (asset.toJson());
    }

    void AssetActivator::deactivate(const std::string & asset_json) const
    {
        std::vector<std::string> payload;
        payload = sendCommand (DEACTIVATE_ASSET, {asset_json});
    }

    void AssetActivator::deactivate (const fty::FullAsset& asset) const
    {
        deactivate (asset.toJson());
    }

    bool AssetActivator::isActivable(const std::string & asset_json) const
    {
        std::vector<std::string> payload;

        try
        {
            payload = sendCommand (IS_ASSET_ACTIVABLE, {asset_json});
        }
        catch (const std::exception& e)
        {
            log_info ("asset activator returned '%s', treated as false", e.what());
            return false;
        }

        bool rv;
        std::istringstream isActivableStr (payload[0]);
        log_debug ("asset is activable = %s", payload[0].c_str ());
        isActivableStr >> std::boolalpha >> rv;
        return rv;
    }

    bool AssetActivator::isActivable (const fty::FullAsset& asset) const
    {
        return isActivable (asset.toJson());
    }

    std::vector<std::string> AssetActivator::sendCommand(const std::string & command, const std::vector<std::string> & frames) const
    {
        std::vector<std::string> payload = {command};
        std::copy(frames.begin(), frames.end(), back_inserter(payload));

        std::vector<std::string> receivedFrames = m_requestClient.syncRequestWithReply(payload);

        //check if the first frame we get is an error
        if(receivedFrames[0] == "ERROR")
        {
            //It's an error and we will throw directly the exceptions
            if(receivedFrames.size() == 2)
            {
                throw std::runtime_error(receivedFrames.at(1));
            }
            else
            {
                throw std::runtime_error("Missing data for error");
            }
        }

        return receivedFrames;
    }

} // end namespace
