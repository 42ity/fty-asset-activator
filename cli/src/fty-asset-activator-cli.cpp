#include <libfty_asset_activator.h>
#include <fty/convert.h>
#include <fty_common_mlm.h>

#include <cstring>
#include <string>
#include <iostream>

using namespace fty;

void help()
{
    std::cout << "Usage: ./fty_asset_activator_cli <command> <asset iname>" << std::endl;
    std::cout << "Available commands:" << std::endl;
    std::cout << "\t- activate" << std::endl;
    std::cout << "\t- deactivate" << std::endl;
    std::cout << "\t- isactive" << std::endl;
    std::cout << "\t- isactivable" << std::endl;
}

int getOption(const std::string& op)
{
    // if(std::strcmp(op.c_str(), "activate")) {
    if(op == "activate") {
        return 1;
    } else if(op == "deactivate") {
        return 2;
    } else if(op == "isactive") {
        return 3;
    } else if(op == "isactivable") {
        return 4;
    }

    return 0;
}

int main(int argc, char** argv)
{
    if(argc < 3) {
        std::cout << "Invalid number of arguments" << std::endl;
        help();

        return 1;
    }

    std::string op(argv[1]);
    std::string iname(argv[2]);

    mlm::MlmSyncClient  client("asset-agent", "etn-licensing-credits");
    AssetActivator activator(client);
 
    bool ret;

    switch(getOption(op)) {
        case 1:
            activator.activateIname(iname);
            break;
        case 2:
            activator.deactivateIname(iname);
            break;
        case 3:
            ret = activator.isActiveIname(iname);
            std::cout << "Asset " << iname << (ret ? " is active" : " is not active") << std::endl;
            break;
        case 4:
            ret = activator.isActivableIname(iname);
            std::cout << "Asset " << iname << (ret ? " is activable" : " is not activable") << std::endl;
            break;
        default:
            std::cout << "Invalid option" << std::endl;
            help();
            break;
    }

    return 0;
}
