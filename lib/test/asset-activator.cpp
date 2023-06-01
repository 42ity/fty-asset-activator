#include <catch2/catch.hpp>
#include "fty_asset_activator.h"
#include <fty_common_mlm.h>
#include <fty_asset_dto.h>

TEST_CASE("AssetActivator - fake")
{
    const uint32_t timeout = 1000; //ms
    mlm::MlmSyncClient client("asset-activator-test", "etn-licensing-credits-fake", timeout);
    fty::AssetActivator aa(client);

    fty::FullAsset::HashMap aux, ext;
    fty::FullAsset fa("ups-1234", "active", "device", "ups", "myUps", "room-1234", "1", aux, ext);

    CHECK_NOTHROW(aa.isActive("{}"));
    CHECK_NOTHROW(aa.isActive(fa));
    CHECK_THROWS(aa.isActiveIname("ups-1234"));

    CHECK_NOTHROW(aa.isActivable("{}"));
    CHECK_NOTHROW(aa.isActivable(fa));
    CHECK_THROWS(aa.isActivableIname("ups-1234"));

    CHECK_THROWS(aa.activate("{}"));
    CHECK_THROWS(aa.activate(fa));
    CHECK_THROWS(aa.activateIname({"ups-1234", "ups-4321"}));

    CHECK_THROWS(aa.deactivate("{}"));
    CHECK_THROWS(aa.deactivate(fa));
    CHECK_THROWS(aa.deactivateIname({"ups-1234", "ups-4321"}));
}
