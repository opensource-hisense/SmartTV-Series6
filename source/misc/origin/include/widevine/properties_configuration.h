// Copyright 2013 Google Inc. All Rights Reserved.

#ifndef WVCDM_CDM_PROPERTIES_CONFIGURATION_H_
#define WVCDM_CDM_PROPERTIES_CONFIGURATION_H_

#include "wv_cdm_constants.h"
#include "properties.h"

namespace wvcdm {

// Set only one of the two below to true. If secure buffer
// is selected, fallback to userspace buffers may occur
// if L1/L2 OEMCrypto APIs fail.
// Note: This is managed in the build configuration.
const bool kPropertyOemCryptoUseSecureBuffers = PLATFORM_REQUIRES_SECURE_BUFFERS;
const bool kPropertyOemCryptoUseFifo = true;
const bool kPropertyOemCryptoUseUserSpaceBuffers = PLATFORM_USES_CLEAR_BUFFERS;

// If true, the unit tests require OEMCrypto to support usage tables.
const bool kPropertyOemCryptoRequireUsageTable = false;

// If false, keyboxes will be used as client identification
// and passed as the token in the license request.
// The default value of false for PLATFORM_CERTIFICATE_PROV is set in
// global_config.gypi.  It can be overridden to true in the platform specific
// .gypi files if you want your device to use certificates for provisioning.
const bool kPropertyUseCertificatesAsIdentification = PLATFORM_CERTIFICATE_PROV;

// If true, device files will be moved to the directory specified by
// Properties::GetDeviceFilesBasePath
const bool kSecurityLevelPathBackwardCompatibilitySupport = false;

} // namespace wvcdm

#endif  // WVCDM_CDM_PROPERTIES_CONFIGURATION_H_
