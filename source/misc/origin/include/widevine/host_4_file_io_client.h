// Copyright 2013 Google Inc. All Rights Reserved.

#ifndef WVCDM_HOST_4_FILE_IO_CLIENT_H_
#define WVCDM_HOST_4_FILE_IO_CLIENT_H_

#include "content_decryption_module.h"
#include "wv_cdm_common.h"
#include "wv_cdm_types.h"

namespace wvcdm {

class Host4FileIOClient : public cdm::FileIOClient {
 public:
  explicit Host4FileIOClient(cdm::Host_4* host)
      : host_(host),
        file_io_(NULL),
        status_(kSuccess),
        data_size_(0),
        buffer_(NULL),
        buffer_size_(0) {}
  ~Host4FileIOClient();

  bool Open(const std::string& name);
  bool Read(char* buffer, size_t buffer_size);
  bool ReadFileSize() { return Read(NULL, 0); }
  bool Write(const char* data, size_t data_size);
  bool Close();

  // cdm::FileIOClient implementation
  virtual void OnOpenComplete(Status status) OVERRIDE;
  virtual void OnReadComplete(Status status, const uint8_t* data,
                              uint32_t data_size) OVERRIDE;
  virtual void OnWriteComplete(Status status) OVERRIDE;

  // Get the result of the last operation
  Status status() const { return status_; }
  uint32_t data_size() const { return data_size_; }

 private:
  cdm::Host_4* host_;
  cdm::FileIO* file_io_;

  // These hold the result of the last operation
  Status status_;
  uint32_t data_size_;
  char* buffer_;
  size_t buffer_size_;

  CORE_DISALLOW_COPY_AND_ASSIGN(Host4FileIOClient);
};

}  // namespace wvcdm

#endif  // WVCDM_HOST_4_FILE_IO_CLIENT_H_
