/*  =========================================================================
    fty_asset_activator-cli - CLI over libfty-asset-activator

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

#include <cstring>
#include <fty/convert.h>
#include <fty_common_mlm.h>
#include <iostream>
#include <libfty_asset_activator.h>
#include <list>
#include <string>

static void usage()
{
    std::cout << "Usage: ./fty_asset_activator_cli <command> <iname> [<iname2> "
                 "... <inameN>]"
              << std::endl;
    std::cout << "Available commands:" << std::endl;
    std::cout << "\t- activate <iname1> [<iname2> ... <inameN>]" << std::endl;
    std::cout << "\t- deactivate <iname> [<iname2> ... <inameN>]" << std::endl;
    std::cout << "\t- isactive <iname>" << std::endl;
    std::cout << "\t- isactivable <iname>" << std::endl;
}

int main(int argc, const char* argv[])
{
    if (argc <= 2) {
        std::cerr << "Invalid number of arguments" << std::endl;
        usage();
        return EXIT_FAILURE;
    }

    std::string command(argv[1]);

    std::list<std::string> inames;
    for (int count = 2; count < argc; count++) {
        inames.push_back(argv[count]);
    }

    mlm::MlmSyncClient client("asset-activator-cli", "etn-licensing-credits");
    fty::AssetActivator activator(client);

    try {
        if (command == "activate") {
            activator.activateIname(inames);
        }
        else if (command == "deactivate") {
            activator.deactivateIname(inames);
        }
        else if (command == "isactive") {
            bool ret = activator.isActiveIname(inames.front());
            std::cout << "Asset " << inames.front() << (ret ? " is active" : " is not active") << std::endl;
        }
        else if (command == "isactivable") {
            bool ret = activator.isActivableIname(inames.front());
            std::cout << "Asset " << inames.front() << (ret ? " is activable" : " is not activable") << std::endl;
        }
        else {
            std::cerr << "Invalid command (" << command << ")" << std::endl;
            usage();
        }
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return EXIT_SUCCESS;
}
