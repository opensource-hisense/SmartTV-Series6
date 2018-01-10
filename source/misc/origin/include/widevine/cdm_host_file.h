// Copyright 2013 Google Inc. All Rights Reserved.

#ifndef WVCDM_CDM_CDM_HOST_FILE_H_
#define WVCDM_CDM_CDM_HOST_FILE_H_

#include "content_decryption_module.h"
#include "file_store.h"
#include "host_4_file_io_client.h"
#include "scoped_ptr.h"

namespace wvcdm {

class IFileFactory;

class IHostFile {
 public:
  virtual ~IHostFile() {}
  virtual bool Open(const std::string& name) = 0;
  virtual ssize_t Read(char* buffer, size_t bytes) = 0;
  virtual ssize_t Write(const char* buffer, size_t bytes) = 0;
  virtual bool Close() = 0;
  virtual bool Remove(const std::string& name) = 0;
  virtual ssize_t FileSize(const std::string& name) = 0;
};

class File1Impl : public IHostFile {
 public:
  explicit File1Impl(cdm::Host_1* const host_1) : host_1_(host_1) {}
  virtual ~File1Impl() {}
  virtual bool Open(const std::string& name) OVERRIDE;
  virtual ssize_t Read(char* buffer, size_t bytes) OVERRIDE;
  virtual ssize_t Write(const char* buffer, size_t bytes) OVERRIDE;
  virtual bool Close() OVERRIDE;
  virtual bool Remove(const std::string& name) OVERRIDE;
  virtual ssize_t FileSize(const std::string& name) OVERRIDE;
 private:
  cdm::Host_1* const host_1_;
  std::string fname_;
};

class File4Impl : public IHostFile {
 public:
  explicit File4Impl(cdm::Host_4* const host_4) :
      host_4_(host_4), host_4_file_io_client_(host_4) {}
  virtual ~File4Impl() {}
  virtual bool Open(const std::string& name) OVERRIDE;
  virtual ssize_t Read(char* buffer, size_t bytes) OVERRIDE;
  virtual ssize_t Write(const char* buffer, size_t bytes) OVERRIDE;
  virtual bool Close() OVERRIDE;
  virtual bool Remove(const std::string& name) OVERRIDE;
  virtual ssize_t FileSize(const std::string& name) OVERRIDE;
 private:
  cdm::Host_4* const host_4_;
  Host4FileIOClient host_4_file_io_client_;
};

class File::Impl {
 public:
  explicit Impl(cdm::Host_1* const host_1) :
      file_api_(new File1Impl(host_1)) {}

  explicit Impl(cdm::Host_4* const host_4) :
      file_api_(new File4Impl(host_4)) {}

  ~Impl() {}

  static void RegisterFileFactory(IFileFactory* factory) { factory_ = factory; }

  virtual bool Open(const std::string& name);
  virtual ssize_t Read(char* buffer, size_t bytes);
  virtual ssize_t Write(const char* buffer, size_t bytes);
  virtual bool Close();
  virtual bool Exists(const std::string& name);
  virtual bool Remove(const std::string& name);
  virtual ssize_t FileSize(const std::string& name);

 private:
  static IFileFactory* factory_;
  friend class File;

  scoped_ptr<IHostFile> file_api_;
};

class IFileFactory {
 protected:
  IFileFactory() { File::Impl::RegisterFileFactory(this); }

  virtual ~IFileFactory() {}

 public:
  virtual File::Impl* NewFileImpl() = 0;
};

}  // namespace wvcdm

#endif  // WVCDM_CDM_CDM_HOST_FILE_H_
