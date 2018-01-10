// Copyright 2013 Google Inc. All Rights Reserved.

#ifndef WVCDM_CDM_WV_CONTENT_DECRYPTION_MODULE_1_H_
#define WVCDM_CDM_WV_CONTENT_DECRYPTION_MODULE_1_H_

#include "cdm_client_property_set.h"
#include "cdm_engine.h"
#include "cdm_host_clock.h"
#include "cdm_host_file.h"

#include "clock.h"
#include "content_decryption_module.h"
#include "host_event_listener.h"

#include "wv_cdm_common.h"
#include "wv_cdm_types.h"
#include "wv_client_property_set.h"

namespace wvcdm {

class WvContentDecryptionModule_1 : public cdm::ContentDecryptionModule_1,
                                    public IFileFactory,
                                    public IClock {
 public:
  explicit WvContentDecryptionModule_1(cdm::Host_1* host);

  virtual ~WvContentDecryptionModule_1();

  // cdm::ContentDecryptionModule_1 implementation.
  virtual cdm::Status GenerateKeyRequest(const char* type, int type_size,
                                         const uint8_t* init_data,
                                         int init_data_size) OVERRIDE;

  virtual cdm::Status AddKey(const char* session_id, int session_id_size,
                             const uint8_t* key, int key_size,
                             const uint8_t* key_id, int key_id_size) OVERRIDE;

  virtual bool IsKeyValid(const uint8_t* key_id, int key_id_size) OVERRIDE;

  virtual cdm::Status CloseSession(const char* session_id,
                                   int session_id_size) OVERRIDE;

  virtual void TimerExpired(void* context) OVERRIDE;

  virtual cdm::Status Decrypt(const cdm::InputBuffer& encrypted_buffer,
                              cdm::DecryptedBlock* decrypted_buffer) OVERRIDE;

  virtual cdm::Status DecryptDecodeAndRenderFrame(
      const cdm::InputBuffer& encrypted_buffer) OVERRIDE;

  virtual cdm::Status DecryptDecodeAndRenderSamples(
      const cdm::InputBuffer& encrypted_buffer) OVERRIDE;

  virtual void Destroy() OVERRIDE;

  virtual cdm::Status GetProvisioningRequest(
      std::string* request, std::string* default_url) OVERRIDE;

  virtual cdm::Status HandleProvisioningResponse(
      std::string& response) OVERRIDE;

 private:
  void EnablePolicyTimer();
  void DisablePolicyTimer();

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
                                       size_t& offset,
                                       size_t& encrypted_offset,
                                       uint32_t& block_ctr);

  void SetSizesAndAllocate(size_t output_size,
                           CdmDecryptionParameters& parameters,
                           cdm::DecryptedBlock* decrypted_block);

  cdm::Host_1* const host_;
  HostEventListener host_event_listener_;

  CdmEngine cdm_engine_;
  WVClientPropertySet property_set_;
  bool timer_enabled_;

  CORE_DISALLOW_COPY_AND_ASSIGN(WvContentDecryptionModule_1);
};

}  // namespace wvcdm

#endif  // WVCDM_CDM_WV_CONTENT_DECRYPTION_MODULE_1_H_
