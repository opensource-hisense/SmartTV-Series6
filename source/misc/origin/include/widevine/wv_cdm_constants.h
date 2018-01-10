// Copyright 2012 Google Inc. All Rights Reserved.

#ifndef WVCDM_CORE_WV_CDM_CONSTANTS_H_
#define WVCDM_CORE_WV_CDM_CONSTANTS_H_

#include <string>

namespace wvcdm {
static const size_t KEY_CONTROL_SIZE = 16;
static const size_t KEY_ID_SIZE = 16;
static const size_t KEY_IV_SIZE = 16;
static const size_t KEY_PAD_SIZE = 16;
static const size_t KEY_SIZE = 16;
static const size_t MAC_KEY_SIZE = 32;
static const size_t KEYBOX_KEY_DATA_SIZE = 72;

static const char SESSION_ID_PREFIX[] = "sid";
static const char KEY_SET_ID_PREFIX[] = "ksid";
static const char KEY_SYSTEM[] = "com.widevine";

// define query keys, values here
static const std::string QUERY_KEY_LICENSE_TYPE = "LicenseType";
                                                    // "Streaming", "Offline"
static const std::string QUERY_KEY_PLAY_ALLOWED = "PlayAllowed";
                                                    // "True", "False"
static const std::string QUERY_KEY_PERSIST_ALLOWED = "PersistAllowed";
                                                    // "True", "False"
static const std::string QUERY_KEY_RENEW_ALLOWED = "RenewAllowed";
                                                    // "True", "False"
static const std::string QUERY_KEY_LICENSE_DURATION_REMAINING =
    "LicenseDurationRemaining";                     // non-negative integer
static const std::string QUERY_KEY_PLAYBACK_DURATION_REMAINING =
    "PlaybackDurationRemaining";                    // non-negative integer
static const std::string QUERY_KEY_RENEWAL_SERVER_URL = "RenewalServerUrl";
                                                    // url
static const std::string QUERY_KEY_OEMCRYPTO_SESSION_ID = "OemCryptoSessionId";
                                                    // session id
static const std::string QUERY_KEY_SECURITY_LEVEL = "SecurityLevel";
                                                    // "L1", "L3"
static const std::string QUERY_KEY_DEVICE_ID = "DeviceID";
                                               // device unique id
static const std::string QUERY_KEY_SYSTEM_ID = "SystemID";
                                               // system id
static const std::string QUERY_KEY_PROVISIONING_ID = "ProvisioningID";
                                               // provisioning unique id

static const std::string QUERY_VALUE_TRUE = "True";
static const std::string QUERY_VALUE_FALSE = "False";
static const std::string QUERY_VALUE_STREAMING = "Streaming";
static const std::string QUERY_VALUE_OFFLINE = "Offline";
static const std::string QUERY_VALUE_SECURITY_LEVEL_L1 = "L1";
static const std::string QUERY_VALUE_SECURITY_LEVEL_L2 = "L2";
static const std::string QUERY_VALUE_SECURITY_LEVEL_L3 = "L3";
static const std::string QUERY_VALUE_SECURITY_LEVEL_UNKNOWN = "Unknown";

static const std::string ISO_BMFF_VIDEO_MIME_TYPE = "video/mp4";
static const std::string ISO_BMFF_AUDIO_MIME_TYPE = "audio/mp4";
static const std::string WEBM_VIDEO_MIME_TYPE = "video/webm";
static const std::string WEBM_AUDIO_MIME_TYPE = "audio/webm";
static const std::string CENC_INIT_DATA_FORMAT = "cenc";
static const std::string WEBM_INIT_DATA_FORMAT = "webm";
}  // namespace wvcdm

#endif  // WVCDM_CORE_WV_CDM_CONSTANTS_H_
