// Copyright 2013 Google Inc. All Rights Reserved.
//
#ifndef WVCDM_CORE_OEMCRYPTO_ADAPTER_H_
#define WVCDM_CORE_OEMCRYPTO_ADAPTER_H_

#include "OEMCryptoCENC.h"

namespace wvcdm {

enum SecurityLevel { kLevelDefault, kLevel3 };

/* This attempts to open a session at the desired security level.
   If one level is not available, the other will be used instead. */
OEMCryptoResult OEMCrypto_OpenSession(OEMCrypto_SESSION* session,
                                      SecurityLevel level);
OEMCryptoResult OEMCrypto_IsKeyboxValid(SecurityLevel level);
OEMCryptoResult OEMCrypto_GetDeviceID(uint8_t* deviceID, size_t* idLength,
                                      SecurityLevel level);
OEMCryptoResult OEMCrypto_GetKeyData(uint8_t* keyData, size_t* keyDataLength,
                                     SecurityLevel level);
OEMCryptoResult OEMCrypto_InstallKeybox(const uint8_t* keybox,
                                        size_t keyBoxLength,
                                        SecurityLevel level);
uint32_t OEMCrypto_APIVersion(SecurityLevel level);
const char* OEMCrypto_SecurityLevel(SecurityLevel level);
bool OEMCrypto_SupportsUsageTable(SecurityLevel level);
}  // namespace wvcdm

#endif  // WVCDM_CORE_OEMCRYPTO_ADAPTER_H_
