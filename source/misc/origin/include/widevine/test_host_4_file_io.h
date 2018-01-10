// Copyright 2013 Google Inc. All Rights Reserved.

#ifndef WVCDM_CDM_TEST_TEST_HOST_4_FILE_IO_H_
#define WVCDM_CDM_TEST_TEST_HOST_4_FILE_IO_H_

#include <string>

#include "content_decryption_module.h"
#include "test_host_4.h"
#include "wv_cdm_common.h"
#include "wv_cdm_types.h"

class TestHost_4_FileIO : public cdm::FileIO {
 public:
  TestHost_4_FileIO(TestHost_4* host, cdm::FileIOClient* client)
      : host_(host), client_(client) {}
  virtual ~TestHost_4_FileIO() {}

  // cdm::FileIO implementation.
  virtual void Open(const char* file_name, uint32_t file_name_size) OVERRIDE;
  virtual void Read() OVERRIDE;
  virtual void Write(const uint8_t* data, uint32_t data_size) OVERRIDE;
  virtual void Close() OVERRIDE;

 private:
  TestHost_4* host_;
  cdm::FileIOClient* client_;

  std::string file_name_;

  CORE_DISALLOW_COPY_AND_ASSIGN(TestHost_4_FileIO);
};

#endif  // WVCDM_CDM_TEST_TEST_HOST_4_FILE_IO_H_
