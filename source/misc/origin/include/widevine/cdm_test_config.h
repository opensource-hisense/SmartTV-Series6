// Copyright 2014 Google Inc. All Rights Reserved.

#ifndef WVCDM_CDM_TEST_CDM_TEST_CONFIG_H_
#define WVCDM_CDM_TEST_CDM_TEST_CONFIG_H_

#include <string>

#include "config_test_env.h"

extern std::string g_client_auth;
extern std::string g_key_id;
extern std::string g_license_server;
extern std::string g_wrong_key_id;

static const wvcdm::LicenseServerId kLicenseServerId =
    wvcdm::kContentProtectionServer;

#endif  // WVCDM_CDM_TEST_CDM_TEST_CONFIG_H_
