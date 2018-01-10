// Copyright 2014 Google Inc. All Rights Reserved.

#ifndef CORE_INCLUDE_INITIALIZATION_DATA_H_
#define CORE_INCLUDE_INITIALIZATION_DATA_H_

#include <string>

#include "wv_cdm_types.h"

namespace wvcdm {

class WvCdmEngineTest;

class InitializationData {
 public:
  InitializationData(const std::string& type = std::string(),
                     const CdmInitData& data = CdmInitData());

  bool is_supported() const { return is_cenc_ || is_webm_; }
  bool is_cenc() const { return is_cenc_; }
  bool is_webm() const { return is_webm_; }

  bool IsEmpty() const { return data_.empty(); }

  const std::string& type() const { return type_; }
  const CdmInitData& data() const { return data_; }

 private:
  // Parse a blob of multiple concatenated PSSH atoms to extract the first
  // Widevine PSSH.
  bool ExtractWidevinePssh(const CdmInitData& init_data, CdmInitData* output);

  std::string type_;
  CdmInitData data_;
  bool is_cenc_;
  bool is_webm_;
  CORE_DISALLOW_COPY_AND_ASSIGN(InitializationData);
};

}  // namespace wvcdm

#endif  // CORE_INCLUDE_INITIALIZATION_DATA_H_
