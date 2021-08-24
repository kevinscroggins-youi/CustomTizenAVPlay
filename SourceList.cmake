# =============================================================================
# © You i Labs Inc. 2000-2020. All rights reserved.
set(SOURCE_TIZEN-NACL
)

set(HEADERS_TIZEN-NACL
)

set(YI_PROJECT_SOURCE
    src/CustomTizenAVPlayApp.cpp
    src/CustomTizenAVPlayAppFactory.cpp
    src/player/CustomTizenNaClVideoPlayer.cpp
    ${SOURCE_${YI_PLATFORM_UPPER}}
)

set(YI_PROJECT_HEADERS
    src/CustomTizenAVPlayApp.h
    src/player/CustomTizenNaClVideoPlayer.h
    ${HEADERS_${YI_PLATFORM_UPPER}}
)
