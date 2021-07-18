#ifndef TREE_ASSETHANDLER_H
#define TREE_ASSETHANDLER_H

#include <android_native_app_glue.h>

class AssetHandler {
public:

    AssetHandler(AAssetManager* manager, const char* fileName, int mode = AASSET_MODE_UNKNOWN);
    ~AssetHandler();

    off_t length() const;
    const void* buffer() const;

private:
    AAsset* m_asset;
};

inline off_t AssetHandler::length() const {
    return AAsset_getLength(m_asset);
}

inline const void* AssetHandler::buffer() const {
    return AAsset_getBuffer(m_asset);
}

#endif //TREE_ASSETHANDLER_H
