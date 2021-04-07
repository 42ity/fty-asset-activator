#include <cstring>
#include <fty/convert.h>
#include <fty_common_mlm.h>
#include <iostream>
#include <libfty_asset_activator.h>
#include <list>
#include <string>

using namespace fty;

void help()
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

int getOption(const std::string& op)
{
    if (op == "activate") {
        return 1;
    } else if (op == "deactivate") {
        return 2;
    } else if (op == "isactive") {
        return 3;
    } else if (op == "isactivable") {
        return 4;
    }

    return 0;
}

int main(int argc, char** argv)
{
    if (argc < 3) {
        std::cout << "Invalid number of arguments" << std::endl;
        help();

        return 1;
    }

    std::string op(argv[1]);

    std::list<std::string> inames;
    for (int count = 2; count < argc; count++) {
        inames.push_back(std::string(argv[count]));
    }

    mlm::MlmSyncClient client("asset-agent", "etn-licensing-credits");
    AssetActivator     activator(client);

    bool ret;

    try {
        switch (getOption(op)) {
            case 1:
                activator.activateIname(inames);
                break;
            case 2:
                activator.deactivateIname(inames);
                break;
            case 3:
                ret = activator.isActiveIname(inames.front());
                std::cout << "Asset " << inames.front() << (ret ? " is active" : " is not active") << std::endl;
                break;
            case 4:
                ret = activator.isActivableIname(inames.front());
                std::cout << "Asset " << inames.front() << (ret ? " is activable" : " is not activable") << std::endl;
                break;
            default:
                std::cout << "Invalid option" << std::endl;
                help();
                break;
        }
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
