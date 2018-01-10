// Copyright 2013 Google Inc. All Rights Reserved.

#ifndef WVCDM_CORE_WV_CDM_TYPES_H_
#define WVCDM_CORE_WV_CDM_TYPES_H_

#include <map>
#include <stdint.h>
#include <string>
#include <vector>

namespace wvcdm {

typedef std::string CdmKeySystem;
typedef std::string CdmInitData;
typedef std::string CdmKeyMessage;
typedef std::string CdmKeyResponse;
typedef std::string KeyId;
typedef std::string CdmSessionId;
typedef std::string CdmKeySetId;
typedef std::string RequestId;
typedef uint32_t CryptoResult;
typedef uint32_t CryptoSessionId;
typedef std::string CryptoKeyId;
typedef std::map<std::string, std::string> CdmAppParameterMap;
typedef std::map<std::string, std::string> CdmQueryMap;
typedef std::vector<std::string> CdmUsageInfo;
typedef std::string CdmUsageInfoReleaseMessage;
typedef std::string CdmProvisioningRequest;
typedef std::string CdmProvisioningResponse;

enum CdmResponseType {
  NO_ERROR,
  UNKNOWN_ERROR,
  KEY_ADDED,
  KEY_ERROR,
  KEY_MESSAGE,
  NEED_KEY,
  KEY_CANCELED,
  NEED_PROVISIONING,
  DEVICE_REVOKED,
  INSUFFICIENT_CRYPTO_RESOURCES,
};

#define CORE_DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&);                    \
  void operator=(const TypeName&)

enum CdmEventType {
  LICENSE_EXPIRED_EVENT,
  LICENSE_RENEWAL_NEEDED_EVENT
};

enum CdmLicenseType {
  kLicenseTypeOffline,
  kLicenseTypeStreaming,
  kLicenseTypeRelease
};

enum CdmSecurityLevel {
  kSecurityLevelUninitialized,
  kSecurityLevelL1,
  kSecurityLevelL2,
  kSecurityLevelL3,
  kSecurityLevelUnknown
};

enum CdmCertificateType {
  kCertificateWidevine,
  kCertificateX509,
};

struct CdmDecryptionParameters {
  bool is_encrypted;
  bool is_secure;
  const KeyId* key_id;
  const uint8_t* encrypt_buffer;
  size_t encrypt_length;
  const std::vector<uint8_t>* iv;
  size_t block_offset;
  void* decrypt_buffer;
  size_t decrypt_buffer_length;
  size_t decrypt_buffer_offset;
  uint8_t subsample_flags;
  bool is_video;
  CdmDecryptionParameters()
      : is_encrypted(true),
        is_secure(true),
        key_id(NULL),
        encrypt_buffer(NULL),
        encrypt_length(0),
        iv(NULL),
        block_offset(0),
        decrypt_buffer(NULL),
        decrypt_buffer_length(0),
        decrypt_buffer_offset(0),
        subsample_flags(0),
        is_video(true) {}
  CdmDecryptionParameters(const KeyId* key, const uint8_t* encrypted_buffer,
                          size_t encrypted_length,
                          const std::vector<uint8_t>* initialization_vector,
                          size_t offset, void* decrypted_buffer)
      : is_encrypted(true),
        is_secure(true),
        key_id(key),
        encrypt_buffer(encrypted_buffer),
        encrypt_length(encrypted_length),
        iv(initialization_vector),
        block_offset(offset),
        decrypt_buffer(decrypted_buffer),
        decrypt_buffer_length(encrypted_length),
        decrypt_buffer_offset(0),
        subsample_flags(0),
        is_video(true) {}
};

// forward class references
class KeyMessage;
class Request;
class Key;

}  // namespace wvcdm

#endif  // WVCDM_CORE_WV_CDM_TYPES_H_
