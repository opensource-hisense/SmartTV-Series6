// Copyright 2013 Google Inc. All Rights Reserved.
//
// File - Platform independent interface for a File class
//
#ifndef WVCDM_CORE_FILE_STORE_H_
#define WVCDM_CORE_FILE_STORE_H_

#include "wv_cdm_types.h"

#include <stddef.h>
#include <stdlib.h>

namespace wvcdm {

// File class. The implementation is platform dependent.
class File {
 public:
  class Impl;

  // defines as bit flag
  enum OpenFlags {
    kNoFlags = 0,
    kBinary = 1,
    kCreate = 2,
    kReadOnly = 4,  // defaults to read and write access
    kTruncate = 8
  };

  File();
  virtual ~File();

  virtual bool Open(const std::string& file_path, int flags);
  virtual ssize_t Read(char* buffer, size_t bytes);
  virtual ssize_t Write(const char* buffer, size_t bytes);
  virtual void Close();

  virtual bool Exists(const std::string& file_path);
  virtual bool Remove(const std::string& file_path);
  virtual bool Copy(const std::string& old_path, const std::string& new_path);
  virtual bool List(const std::string& path, std::vector<std::string>* files);
  virtual bool CreateDirectory(const std::string dir_path);
  virtual bool IsDirectory(const std::string& dir_path);
  virtual bool IsRegularFile(const std::string& file_path);
  virtual ssize_t FileSize(const std::string& file_path);

 private:
  Impl* impl_;

  CORE_DISALLOW_COPY_AND_ASSIGN(File);
};

}  // namespace wvcdm

#endif  // WVCDM_CORE_FILE_STORE_H_
