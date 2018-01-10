// Copyright 2013 Google Inc. All Rights Reserved.

#ifndef WVCDM_CORE_CDM_ENGINE_H_
#define WVCDM_CORE_CDM_ENGINE_H_

#include "certificate_provisioning.h"
#include "initialization_data.h"
#include "oemcrypto_adapter.h"
#include "scoped_ptr.h"
#include "wv_cdm_types.h"

namespace wvcdm {

class CdmClientPropertySet;
class CdmSession;
class CryptoEngine;
class WvCdmEventListener;

typedef std::map<CdmSessionId, CdmSession*> CdmSessionMap;
typedef std::map<CdmKeySetId, CdmSessionId> CdmReleaseKeySetMap;

class CdmEngine {
 public:
  CdmEngine();
  virtual ~CdmEngine();

  // Session related methods
  virtual CdmResponseType OpenSession(const CdmKeySystem& key_system,
                                      const CdmClientPropertySet* property_set,
                                      CdmSessionId* session_id);
  virtual CdmResponseType CloseSession(const CdmSessionId& session_id);

  virtual CdmResponseType OpenKeySetSession(const CdmKeySetId& key_set_id);
  virtual CdmResponseType CloseKeySetSession(const CdmKeySetId& key_set_id);

  // License related methods

  // Construct a valid license request. The arguments are used as follows:
  // session_id: The Session ID of the session the request is being generated
  //             for. This is ignored for license release requests.
  // key_set_id: The Key Set ID of the key set the request is being generated
  //             for. This is ignored except for license release requests.
  // init_data: The initialization data from the media file, which is used to
  //            build the key request. This is ignored for release and renewal
  //            requests.
  // license_type: The type of license being requested. Never ignored.
  // app_parameters: Additional, application-specific parameters that factor
  //                 into the request generation. This is ignored for release
  //                 and renewal requests.
  // key_request: This must be non-null and point to a CdmKeyMessage. The buffer
  //              will have its contents replaced with the key request.
  // server_url: This must be non-null and point to a string. The string will
  //             have its contents replaced with the default URL (if one is
  //             known) to send this key request to.
  // key_set_id_out: May be null. If it is non-null, the CdmKeySetId pointed to
  //                 will have its contents replaced with the key set ID of the
  //                 session. Note that for non-offline license requests, the
  //                 key set ID is empty, so the CdmKeySetId will be cleared.
  virtual CdmResponseType GenerateKeyRequest(
      const CdmSessionId& session_id, const CdmKeySetId& key_set_id,
      const InitializationData& init_data, const CdmLicenseType license_type,
      CdmAppParameterMap& app_parameters, CdmKeyMessage* key_request,
      std::string* server_url, CdmKeySetId* key_set_id_out);

  // Accept license response and extract key info.
  virtual CdmResponseType AddKey(const CdmSessionId& session_id,
                                 const CdmKeyResponse& key_data,
                                 CdmKeySetId* key_set_id);

  virtual CdmResponseType RestoreKey(const CdmSessionId& session_id,
                                     const CdmKeySetId& key_set_id);

  virtual CdmResponseType RemoveKeys(const CdmSessionId& session_id);

  // Construct valid renewal request for the current session keys.
  virtual CdmResponseType GenerateRenewalRequest(const CdmSessionId& session_id,
                                                 CdmKeyMessage* key_request,
                                                 std::string* server_url);

  // Accept renewal response and update key info.
  virtual CdmResponseType RenewKey(const CdmSessionId& session_id,
                                   const CdmKeyResponse& key_data);

  // Query system information
  virtual CdmResponseType QueryStatus(CdmQueryMap* info);

  // Query session information
  virtual CdmResponseType QuerySessionStatus(const CdmSessionId& session_id,
                                             CdmQueryMap* key_info);

  // Query license information
  virtual CdmResponseType QueryKeyStatus(const CdmSessionId& session_id,
                                         CdmQueryMap* key_info);

  // Query seesion control information
  virtual CdmResponseType QueryKeyControlInfo(const CdmSessionId& session_id,
                                              CdmQueryMap* key_info);

  // Provisioning related methods
  virtual CdmResponseType GetProvisioningRequest(
      CdmCertificateType cert_type, const std::string& cert_authority,
      CdmProvisioningRequest* request, std::string* default_url);

  virtual CdmResponseType HandleProvisioningResponse(
      CdmProvisioningResponse& response, std::string* cert,
      std::string* wrapped_key);

  virtual CdmResponseType Unprovision(CdmSecurityLevel security_level);

  // Usage related methods for streaming licenses
  virtual CdmResponseType GetUsageInfo(CdmUsageInfo* usage_info);
  virtual CdmResponseType ReleaseUsageInfo(
      const CdmUsageInfoReleaseMessage& message);

  // Decryption and key related methods
  // Accept encrypted buffer and return decrypted data.
  virtual CdmResponseType Decrypt(const CdmSessionId& session_id,
                                  const CdmDecryptionParameters& parameters);

  virtual size_t SessionSize() const { return sessions_.size(); }

  // Is the key known to any session?
  virtual bool IsKeyLoaded(const KeyId& key_id);
  virtual bool FindSessionForKey(const KeyId& key_id, CdmSessionId* sessionId);

  // Event listener related methods
  virtual bool AttachEventListener(const CdmSessionId& session_id,
                                   WvCdmEventListener* listener);
  virtual bool DetachEventListener(const CdmSessionId& session_id,
                                   WvCdmEventListener* listener);

  // Timer expiration method
  virtual void OnTimerEvent();

 private:
  // private methods
  bool ValidateKeySystem(const CdmKeySystem& key_system);

  void OnKeyReleaseEvent(const CdmKeySetId& key_set_id);

  // instance variables
  CdmSessionMap sessions_;
  CdmReleaseKeySetMap release_key_sets_;
  CertificateProvisioning cert_provisioning_;
  SecurityLevel cert_provisioning_requested_security_level_;

  static bool seeded_;

  // usage related variables
  scoped_ptr<CdmSession> usage_session_;
  int64_t last_usage_information_update_time;

  CORE_DISALLOW_COPY_AND_ASSIGN(CdmEngine);
};

}  // namespace wvcdm

#endif  // WVCDM_CORE_CDM_ENGINE_H_
