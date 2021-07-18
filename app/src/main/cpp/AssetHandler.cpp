#include <stdexcept>
#include <string>

#include "AssetHandler.h"

AssetHandler::AssetHandler(AAssetManager* manager, const char* fileName, int mode)
    : m_asset(AAssetManager_open(manager, fileName, mode)) {

    if (m_asset == nullptr) {
        throw std::runtime_error(std::string("Asset was not opened: ") + fileName);
    }
}

AssetHandler::~AssetHandler() {
    AAsset_close(m_asset);
}
