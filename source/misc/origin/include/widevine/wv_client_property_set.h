// Copyright 2013 Google Inc. All Rights Reserved.

#ifndef WVCDM_CDM_WV_CLIENT_PROPERTY_SET_H_
#define WVCDM_CDM_WV_CLIENT_PROPERTY_SET_H_

#include "cdm_client_property_set.h"

#include "wv_cdm_types.h"

namespace wvcdm {

class WVClientPropertySet : public CdmClientPropertySet {
 public:
  WVClientPropertySet()
    : use_privacy_mode_(false) {}

  virtual ~WVClientPropertySet() {}

  void set_security_level(const std::string& securityLevel) {
    security_level_ = securityLevel;
  }

  virtual const std::string& security_level() const {
    return security_level_;
  }

  void set_use_privacy_mode(bool usePrivacyMode) {
    use_privacy_mode_ = usePrivacyMode;
  }

  virtual bool use_privacy_mode() const {
    return use_privacy_mode_;
  }

  void set_service_certificate(const std::string& serviceCertificate) {
    service_certificate_ = serviceCertificate;
  }

  virtual const std::string& service_certificate() const {
    return service_certificate_;
  }

  virtual bool is_session_sharing_enabled() const {
    return true;  // This is unused by common cdm but we need a definition
                  // for the pure virtual methods.
  }

  void set_is_session_sharing_enabled(bool shareKeys) {
    return;  // This is unused by common cdm but we need a definition
             // for the pure virtual methods.
  }

  virtual uint32_t session_sharing_id() const {
    return 1;  // This is unused by common cdm but we need a
               // definition for the pure virtual methods.
  }

  virtual void set_session_sharing_id(uint32_t id) {
    return;   // This is unused by common cdm but we need a
              // definition for the pure virtual methods.
  }

 private:
  CORE_DISALLOW_COPY_AND_ASSIGN(WVClientPropertySet);

  std::string security_level_;
  bool use_privacy_mode_;
  std::string service_certificate_;
};

}  // namespace wvcdm

#endif  // WVCDM_CDM_WV_CLIENT_PROPERTY_SET_H_
