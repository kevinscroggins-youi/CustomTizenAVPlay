#ifndef _CUSTOM_TIZEN_NACL_VIDEO_PLAYER_H_
#define _CUSTOM_TIZEN_NACL_VIDEO_PLAYER_H_

#include <player/YiTizenNaClVideoPlayer.h>
#include <utility/YiString.h>

class CustomTizenNaClVideoPlayer : public CYITizenNaClVideoPlayer {
public:
    CustomTizenNaClVideoPlayer();
    virtual ~CustomTizenNaClVideoPlayer();

    void AddExternalTextTrack(const CYIString &url);

private:
    uint64_t m_externalTextTrackAddedEventHandlerId;

    YI_TYPE_BASES(CustomTizenNaClVideoPlayer, CYITizenNaClVideoPlayer);
};

#endif // _CUSTOM_TIZEN_NACL_VIDEO_PLAYER_H_
