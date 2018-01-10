// Copyright 2012 Google Inc. All Rights Reserved.

#ifndef WVCDM_CORE_LICENSE_H_
#define WVCDM_CORE_LICENSE_H_

#include <set>

#include "initialization_data.h"
#include "scoped_ptr.h"
#include "wv_cdm_types.h"

namespace video_widevine_server {
namespace sdk {
class SignedMessage;
}
}  // namespace video_widevine_server

namespace wvcdm {

class Clock;
class CryptoSession;
class PolicyEngine;

class CdmLicense {
 public:
  CdmLicense();
  virtual ~CdmLicense();

  virtual bool Init(const std::string& token, CryptoSession* session,
                    PolicyEngine* policy_engine);

  virtual bool PrepareKeyRequest(const InitializationData& init_data,
                                 const CdmLicenseType license_type,
                                 const CdmAppParameterMap& app_parameters,
                                 const CdmSessionId& session_id,
                                 CdmKeyMessage* signed_request,
                                 std::string* server_url);
  virtual bool PrepareKeyUpdateRequest(bool is_renewal,
                                       CdmKeyMessage* signed_request,
                                       std::string* server_url);
  virtual CdmResponseType HandleKeyResponse(
      const CdmKeyResponse& license_response);
  virtual CdmResponseType HandleKeyUpdateResponse(
      bool is_renewal, const CdmKeyResponse& license_response);

  virtual bool RestoreOfflineLicense(
      const CdmKeyMessage& license_request,
      const CdmKeyResponse& license_response,
      const CdmKeyResponse& license_renewal_response);
  virtual bool RestoreUsageLicense(const CdmKeyMessage& license_request,
                                   const CdmKeyResponse& license_response);
  virtual bool HasInitData() { return !stored_init_data_.empty(); }
  virtual bool IsKeyLoaded(const KeyId& key_id);

  virtual std::string provider_session_token() {
    return provider_session_token_;
  }

 private:
  bool PrepareServiceCertificateRequest(CdmKeyMessage* signed_request,
                                        std::string* server_url);
  CdmResponseType HandleServiceCertificateResponse(
      const video_widevine_server::sdk::SignedMessage& signed_message);

  CdmResponseType HandleKeyErrorResponse(
      const video_widevine_server::sdk::SignedMessage& signed_message);

  template <typename T>
  bool PrepareContentId(const CdmLicenseType license_type,
                        const std::string& request_id, T* content_id);

  CryptoSession* session_;
  PolicyEngine* policy_engine_;
  std::string server_url_;
  std::string token_;
  std::string service_certificate_;
  std::string stored_init_data_;
  bool initialized_;
  std::set<KeyId> loaded_keys_;
  std::string provider_session_token_;

  // Used for certificate based licensing
  CdmKeyMessage key_request_;

  scoped_ptr<Clock> clock_;

  // For testing
  CdmLicense(Clock* clock);  // CdmLicense takes ownership of the clock.
#if defined(UNIT_TEST)
  friend class CdmLicenseTest;
#endif

  CORE_DISALLOW_COPY_AND_ASSIGN(CdmLicense);
};

}  // namespace wvcdm

#endif  // WVCDM_CORE_LICENSE_H_
