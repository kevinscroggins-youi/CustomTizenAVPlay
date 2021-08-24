// © You i Labs Inc. All rights reserved.

#ifndef _CUSTOM_TIZEN_AVPLAY_H_
#define _CUSTOM_TIZEN_AVPLAY_H_

#include <framework/YiApp.h>

class CustomTizenAVPlayApp : public CYIApp
{
public:
    CustomTizenAVPlayApp();
    virtual ~CustomTizenAVPlayApp();

    virtual bool UserInit() override;
    virtual bool UserStart() override;
    virtual void UserUpdate() override;
};

#endif // _CUSTOM_TIZEN_AVPLAY_H_
