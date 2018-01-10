// Copyright 2013 Google Inc. All Rights Reserved.

#ifndef WVCDM_CDM_TEST_TEST_UTIL_H_
#define WVCDM_CDM_TEST_TEST_UTIL_H_

#include "content_decryption_module.h"

#include "wv_cdm_common.h"
#include "wv_cdm_types.h"

// These classes below are naive implementation of the abstract classes defined
// in the CDM interface (content_decryptiom_module.h), which are used for tests
// only.

class TestBuffer : public cdm::Buffer {
 public:
  static TestBuffer* Create(uint32_t capacity);

  virtual void Destroy() OVERRIDE;

  virtual int32_t Capacity() const OVERRIDE;
  virtual uint8_t* Data() OVERRIDE;
  virtual void SetSize(int32_t size) OVERRIDE;
  virtual int32_t Size() const OVERRIDE;

 private:
  // TestBuffer can only be created by calling Create().
  explicit TestBuffer(uint32_t capacity);

  // TestBuffer can only be destroyed by calling Destroy().
  virtual ~TestBuffer();

  uint8_t* buffer_;
  int32_t capacity_;
  int32_t size_;

  CORE_DISALLOW_COPY_AND_ASSIGN(TestBuffer);
};

class TestDecryptedBlock : public cdm::DecryptedBlock {
 public:
  TestDecryptedBlock();
  virtual ~TestDecryptedBlock();

  virtual void SetDecryptedBuffer(cdm::Buffer* buffer) OVERRIDE;
  virtual cdm::Buffer* DecryptedBuffer() OVERRIDE;

  virtual void SetTimestamp(int64_t timestamp) OVERRIDE;
  virtual int64_t Timestamp() const OVERRIDE;

 private:
  cdm::Buffer* buffer_;
  int64_t timestamp_;

  CORE_DISALLOW_COPY_AND_ASSIGN(TestDecryptedBlock);
};

#endif  // WVCDM_CDM_TEST_TEST_UTIL_H_
