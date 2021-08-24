// © You i Labs Inc. 2000-2020. All rights reserved.

#include "CustomTizenAVPlayApp.h"

#include "player/CustomTizenNaClVideoPlayer.h"

#include <framework/YiFramework.h>
#include <logging/YiLogger.h>

#define LOG_TAG "CustomTizenAVPlayApp"

CustomTizenAVPlayApp::CustomTizenAVPlayApp() = default;

CustomTizenAVPlayApp::~CustomTizenAVPlayApp() = default;

bool CustomTizenAVPlayApp::UserInit()
{
    return true;
}

bool CustomTizenAVPlayApp::UserStart()
{
    return true;
}

void CustomTizenAVPlayApp::UserUpdate()
{
}
