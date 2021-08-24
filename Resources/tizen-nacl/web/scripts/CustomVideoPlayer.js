"use strict";

CYIVideoPlayer.originalPrepare = CYIVideoPlayer.prepare;

CYIVideoPlayer.prepare = function prepare(url, maxBitrateKbps, drmConfiguration, startTimeMs) {
    CYIVideoPlayer.originalPrepare(url.replace("http://", "https://"), maxBitrateKbps, drmConfiguration, startTimeMs);
};

CYIVideoPlayer.addExternalTextTrack = function addExternalTextTrack(url, language, label, type, enable) {
    webapis.avplay.setExternalSubtitlePath(url);

    CYIMessaging.sendEvent({
        context: CYIVideoPlayer.name,
        name: "externalTextTrackAdded"
    });
};
