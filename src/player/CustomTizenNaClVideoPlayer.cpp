#include "CustomTizenNaClVideoPlayer.h"

#include <logging/YiLogger.h>
#include <platform/YiWebBridgeLocator.h>
#include <platform/YiWebMessagingBridge.h>
#include <utility/YiRapidJSONUtility.h>

#define LOG_TAG "CYITizenNaClVideoPlayer"

YI_TYPE_DEF(CustomTizenNaClVideoPlayer, CYITizenNaClVideoPlayer);

static constexpr const char *CUSTOM_TIZEN_VIDEO_PLAYER_CLASS_NAME = "CYIVideoPlayer";

static CYIWebMessagingBridge::FutureResponse CallCustomTizenVideoPlayerFunction(yi::rapidjson::Document &&message, const CYIString &functionName, yi::rapidjson::Value &&functionArgumentsValue = yi::rapidjson::Value(yi::rapidjson::kArrayType), bool *pMessageSent = nullptr)
{
    return CYIWebBridgeLocator::GetWebMessagingBridge()->CallStaticFunctionWithArgs(std::move(message), CUSTOM_TIZEN_VIDEO_PLAYER_CLASS_NAME, functionName, std::move(functionArgumentsValue), pMessageSent);
}

static uint64_t RegisterCustomTizenVideoPlayerEventHandler(const CYIString &eventName, CYIWebMessagingBridge::EventCallback &&eventCallback)
{
    return CYIWebBridgeLocator::GetWebMessagingBridge()->RegisterEventHandler(CUSTOM_TIZEN_VIDEO_PLAYER_CLASS_NAME, eventName, std::move(eventCallback));
}

static void UnregisterCustomTizenVideoPlayerEventHandler(uint64_t &eventHandlerId)
{
    CYIWebBridgeLocator::GetWebMessagingBridge()->UnregisterEventHandler(eventHandlerId);
    eventHandlerId = 0;
}

CustomTizenNaClVideoPlayer::CustomTizenNaClVideoPlayer()
    : CYITizenNaClVideoPlayer()
    , m_externalTextTrackAddedEventHandlerId(0) {
    static constexpr const char *EXTERNAL_TEXT_TRACK_ADDED_EVENT_NAME = "externalTextTrackAdded";

    m_externalTextTrackAddedEventHandlerId = RegisterCustomTizenVideoPlayerEventHandler(EXTERNAL_TEXT_TRACK_ADDED_EVENT_NAME, [this](yi::rapidjson::Document &&event) {
        if (!event.HasMember(CYIWebMessagingBridge::EVENT_DATA_ATTRIBUTE_NAME) || !event[CYIWebMessagingBridge::EVENT_DATA_ATTRIBUTE_NAME].IsObject())
        {
            YI_LOGE(LOG_TAG, "Invalid '%s' event data. JSON string for '%s' event: '%s'.", EXTERNAL_TEXT_TRACK_ADDED_EVENT_NAME, EXTERNAL_TEXT_TRACK_ADDED_EVENT_NAME, CYIRapidJSONUtility::CreateStringFromValue(event).GetData());
        }
        else
        {
            const yi::rapidjson::Value &eventDataValue = event[CYIWebMessagingBridge::EVENT_DATA_ATTRIBUTE_NAME];

            if (!eventDataValue.IsBool())
            {
                YI_LOGE(LOG_TAG, "Invalid '%s' event '%s' attribute value. JSON string for '%s' event: '%s'.", EXTERNAL_TEXT_TRACK_ADDED_EVENT_NAME, CYIWebMessagingBridge::EVENT_DATA_ATTRIBUTE_NAME, EXTERNAL_TEXT_TRACK_ADDED_EVENT_NAME, CYIRapidJSONUtility::CreateStringFromValue(event).GetData());
            }
            else
            {
                if (eventDataValue.GetBool())
                {
                    YI_LOGI(LOG_TAG, "External text track added!");
                }
                else
                {
                    YI_LOGI(LOG_TAG, "External text track not added.");
                }
            }
        }
    });
}

CustomTizenNaClVideoPlayer::~CustomTizenNaClVideoPlayer()
{
    UnregisterCustomTizenVideoPlayerEventHandler(m_externalTextTrackAddedEventHandlerId);
}

void CustomTizenNaClVideoPlayer::AddExternalTextTrack(const CYIString &url)
{
    static constexpr const char *FUNCTION_NAME = "addExternalTextTrack";

    yi::rapidjson::Document command(yi::rapidjson::kObjectType);
    yi::rapidjson::MemoryPoolAllocator<yi::rapidjson::CrtAllocator> &allocator = command.GetAllocator();

    yi::rapidjson::Value arguments(yi::rapidjson::kArrayType);
    yi::rapidjson::Value urlValue(url.GetData(), allocator);
    arguments.PushBack(urlValue, allocator);

    bool messageSent = false;
    CYIWebMessagingBridge::FutureResponse futureResponse = CallCustomTizenVideoPlayerFunction(std::move(command), FUNCTION_NAME, std::move(arguments), &messageSent);

    if (!messageSent)
    {
        YI_LOGE(LOG_TAG, "Failed to invoke %s function.", FUNCTION_NAME);
    }
    else
    {
        bool valueAssigned = false;
        CYIWebMessagingBridge::Response response = futureResponse.Take(CYIWebMessagingBridge::DEFAULT_RESPONSE_TIMEOUT_MS, &valueAssigned);

        if (!valueAssigned)
        {
            YI_LOGE(LOG_TAG, "%s did not receive a response from the web messaging bridge!", FUNCTION_NAME);
        }
        else if (response.HasError())
        {
            YI_LOGE(LOG_TAG, "%s", response.GetError()->GetMessage().GetData());
        }
    }
}
