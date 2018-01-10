// Copyright 2014 Google Inc. All Rights Reserved.

#ifndef WVCDM_CDM_WV_CONTENT_DECRYPTION_MODULE_4_H_
#define WVCDM_CDM_WV_CONTENT_DECRYPTION_MODULE_4_H_

#include "content_decryption_module.h"

#include "cdm_client_property_set.h"
#include "cdm_engine.h"
#include "cdm_host_clock.h"
#include "cdm_host_file.h"
#include "clock.h"
#include "wv_cdm_common.h"
#include "wv_cdm_event_listener.h"
#include "wv_cdm_types.h"
#include "wv_client_property_set.h"

#if defined(UNIT_TEST)
# include "gtest/gtest_prod.h"
#endif

namespace wvcdm {

class WvContentDecryptionModule_4 : public cdm::ContentDecryptionModule_4,
                                    public IFileFactory,
                                    public IClock,
                                    public WvCdmEventListener {
 public:
  explicit WvContentDecryptionModule_4(cdm::Host_4* host);

  virtual ~WvContentDecryptionModule_4();

  virtual void CreateSession(uint32_t session_id,
                             const char* mime_type, uint32_t mime_type_size,
                             const uint8_t* init_data, uint32_t init_data_size,
                             cdm::SessionType session_type) OVERRIDE;

  virtual void LoadSession(uint32_t session_id, const char* web_session_id,
                           uint32_t web_session_id_length) OVERRIDE;

  virtual void UpdateSession(uint32_t session_id, const uint8_t* response,
                             uint32_t response_size) OVERRIDE;

  virtual bool IsKeyValid(const uint8_t* key_id, int key_id_size) OVERRIDE;

  virtual void ReleaseSession(uint32_t session_id) OVERRIDE;

  virtual void RemoveSession(uint32_t session_id, const char* web_session_id,
                             uint32_t web_session_id_length) OVERRIDE;

  virtual cdm::Status UsePrivacyMode() OVERRIDE;

  virtual cdm::Status SetServerCertificate(
      const uint8_t* server_certificate_data,
      uint32_t server_certificate_data_size) OVERRIDE;

  virtual void TimerExpired(void* context) OVERRIDE;

  virtual cdm::Status Decrypt(const cdm::InputBuffer& encrypted_buffer,
                              cdm::DecryptedBlock* decrypted_buffer) OVERRIDE;

  virtual cdm::Status DecryptDecodeAndRender(
      const cdm::InputBuffer& encrypted_buffer,
      cdm::StreamType stream_type) OVERRIDE;

  virtual void Destroy() OVERRIDE;

  // wvcdm::WvCdmEventListener implementation.
  virtual void OnEvent(const CdmSessionId& session_id,
                       CdmEventType cdm_event) OVERRIDE;

 private:
  class InternalSession {
   public:
    enum SessionType {
      kDecrypt = 1,
      kRelease = 2,
      kProvision = 3,
    };

    InternalSession() : webid_(), session_type_(kDecrypt) {}
    InternalSession(const std::string& webid, SessionType session_type)
        : webid_(webid), session_type_(session_type) {}

    const std::string& webid() const { return webid_; }
    bool is_decrypt() const { return session_type_ == kDecrypt; }
    bool is_release() const { return session_type_ == kRelease; }
    bool is_provision() const { return session_type_ == kProvision; }

   private:
    std::string webid_;
    SessionType session_type_;
  };

  void EnablePolicyTimer();
  void DisablePolicyTimer();

  void CreateProvisionSession(uint32_t session_id);
  void UpdateProvisionSession(uint32_t session_id, const uint8_t* response,
                              uint32_t response_size);

  bool CallOpenSession(uint32_t session_id);

  virtual File::Impl* NewFileImpl() OVERRIDE;

  virtual int64_t GetCurrentTimeInSeconds() OVERRIDE;

  /* |parameters| is expected to be initialized with anything not related to
   * subsample parsing.  |iv| is initialized by the caller, but may be modified
   * during decryption.  |decrypted_block| may be NULL for L1 decrypts, since
   * no data is passed back to the caller. */
  cdm::Status DoSubsampleDecrypt(CdmDecryptionParameters& parameters,
                                 std::vector<uint8_t>& iv,
                                 const cdm::InputBuffer& encrypted_buffer,
                                 cdm::DecryptedBlock* decrypted_block);
  cdm::Status DoDecrypt(CdmDecryptionParameters& parameters,
                        std::vector<uint8_t>& iv,
                        const cdm::InputBuffer& encrypted_buffer,
                        cdm::DecryptedBlock* decrypted_block);

  /* |parameters| is expected to be initialized with everything required by
   * DoSubsampleDecrypt and DoDecrypt, plus |is_encrypted| and
   * |subsample_flags|.  Counters and |iv| will be updated to prepare for
   * subsequent calls. */
  cdm::Status DecryptAndUpdateCounters(CdmDecryptionParameters& parameters,
                                       std::vector<uint8_t>& iv,
                                       const cdm::InputBuffer& encrypted_buffer,
                                       const size_t bytes,
                                       cdm::DecryptedBlock* decrypted_block,
                                       size_t& offset, size_t& encrypted_offset,
                                       uint32_t& block_ctr);

  void SetSizesAndAllocate(size_t output_size,
                           CdmDecryptionParameters& parameters,
                           cdm::DecryptedBlock* decrypted_block);

#if defined(UNIT_TEST)
  FRIEND_TEST(CdmApi4Test, UsePrivacyMode);
  FRIEND_TEST(CdmApi4Test, UsePrivacyModeFailsWithOpenSessions);
  FRIEND_TEST(CdmApi4Test, SetExplicitServerCertificate);
  FRIEND_TEST(CdmApi4Test, SetServerCertificateFailsWithOpenSessions);
#endif

  cdm::Host_4* const host_;
  WVClientPropertySet property_set_;
  CdmEngine cdm_engine_;
  std::map<uint32_t, InternalSession> session_map_;
  bool timer_enabled_;

  CORE_DISALLOW_COPY_AND_ASSIGN(WvContentDecryptionModule_4);
};

}  // namespace wvcdm

#endif  // WVCDM_CDM_WV_CONTENT_DECRYPTION_MODULE_4_H_
