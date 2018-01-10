// Copyright 2012 Google Inc. All Rights Reserved.

#ifndef WVCDM_CORE_CRYPTO_SESSSION_H_
#define WVCDM_CORE_CRYPTO_SESSSION_H_

#include <string>
#include <map>

#include "lock.h"
#include "oemcrypto_adapter.h"
#include "OEMCryptoCENC.h"
#include "wv_cdm_types.h"

namespace wvcdm {

class CryptoKey;
typedef std::map<CryptoKeyId, CryptoKey*> CryptoKeyMap;

class CryptoSession {
 public:
  // This enum should be kept in sync with the values specified for
  // HDCP capabilities in OEMCryptoCENC.h. (See comments for
  // OEMCrypto_GetHDCPCapability)
  typedef enum {
    kOemCryptoHdcpNotSupported = 0,
    kOemCryptoHdcpVersion1 = 1,
    kOemCryptoHdcpVersion2 = 2,
    kOemCryptoHdcpVersion2_1 = 3,
    kOemCryptoHdcpVersion2_2 = 4,
    kOemCryptoNoHdcpDeviceAttached = 0xff,
  } OemCryptoHdcpVersion;
  CryptoSession();
  virtual ~CryptoSession();

  virtual bool ValidateKeybox();
  virtual bool GetToken(std::string* token);
  virtual CdmSecurityLevel GetSecurityLevel();
  virtual bool GetDeviceUniqueId(std::string* device_id);
  virtual bool GetApiVersion(uint32_t* version);
  virtual bool GetSystemId(uint32_t* system_id);
  virtual bool GetProvisioningId(std::string* provisioning_id);

  virtual CdmResponseType Open() { return Open(kLevelDefault); }
  virtual CdmResponseType Open(SecurityLevel requested_security_level);
  virtual void Close();

  virtual bool IsOpen() { return open_; }
  virtual CryptoSessionId oec_session_id() { return oec_session_id_; }

  // Key request/response
  virtual bool GenerateRequestId(std::string* req_id_str);
  virtual bool PrepareRequest(const std::string& key_deriv_message,
                              bool is_provisioning, std::string* signature);
  virtual bool PrepareRenewalRequest(const std::string& message,
                                     std::string* signature);
  virtual CdmResponseType LoadKeys(const std::string& message,
                                   const std::string& signature,
                                   const std::string& mac_key_iv,
                                   const std::string& mac_key,
                                   const std::vector<CryptoKey>& key_array,
                                   const std::string& provider_session_token);
  virtual bool LoadCertificatePrivateKey(std::string& wrapped_key);
  virtual bool RefreshKeys(const std::string& message,
                           const std::string& signature, int num_keys,
                           const CryptoKey* key_array);
  virtual bool GenerateNonce(uint32_t* nonce);
  virtual bool GenerateDerivedKeys(const std::string& message);
  virtual bool GenerateDerivedKeys(const std::string& message,
                                   const std::string& session_key);
  virtual bool RewrapDeviceRSAKey(const std::string& message,
                                  const std::string& signature,
                                  const std::string& nonce,
                                  const std::string& enc_rsa_key,
                                  const std::string& rsa_key_iv,
                                  std::string* wrapped_rsa_key);

  // Media data path
  virtual CdmResponseType Decrypt(const CdmDecryptionParameters& parameters);

  virtual bool UsageInformationSupport(bool* has_support);
  virtual CdmResponseType UpdateUsageInformation();
  virtual CdmResponseType GenerateUsageReport(
      const std::string& provider_session_token, std::string* usage_report);
  virtual CdmResponseType ReleaseUsageInformation(
      const std::string& message, const std::string& signature,
      const std::string& provider_session_token);

  virtual bool GetHdcpCapabilities(OemCryptoHdcpVersion* current,
                                   OemCryptoHdcpVersion* max);
  virtual bool GetRandom(size_t data_length, uint8_t* random_data);

 private:
  void Init();
  void Terminate();
  void GenerateMacContext(const std::string& input_context,
                          std::string* deriv_context);
  void GenerateEncryptContext(const std::string& input_context,
                              std::string* deriv_context);
  bool GenerateSignature(const std::string& message, std::string* signature);
  bool GenerateRsaSignature(const std::string& message, std::string* signature);
  size_t GetOffset(std::string message, std::string field);
  bool SetDestinationBufferType();

  bool SelectKey(const std::string& key_id);

  static const size_t kSignatureSize = 32;  // size for HMAC-SHA256 signature
  static Lock crypto_lock_;
  static bool initialized_;
  static int session_count_;

  bool open_;
  CryptoSessionId oec_session_id_;

  OEMCryptoBufferType destination_buffer_type_;
  bool is_destination_buffer_type_valid_;
  SecurityLevel requested_security_level_;

  KeyId key_id_;

  uint64_t request_id_base_;
  static uint64_t request_id_index_;

  CORE_DISALLOW_COPY_AND_ASSIGN(CryptoSession);
};

};  // namespace wvcdm

#endif  // WVCDM_CORE_CRYPTO_SESSSION_H_
