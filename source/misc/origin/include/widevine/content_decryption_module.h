// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef WVCDM_CDM_CONTENT_DECRYPTION_MODULE_H_
#define WVCDM_CDM_CONTENT_DECRYPTION_MODULE_H_

#if defined(_MSC_VER)
typedef unsigned char uint8_t;
typedef unsigned int uint32_t;
typedef int int32_t;
typedef __int64 int64_t;
#else
#include <stdint.h>
#endif

#include <string>
#include <vector>

// Define CDM_EXPORT so that functionality implemented by the CDM module
// can be exported to consumers.
#if defined(WIN32)

#if defined(CDM_IMPLEMENTATION)
#define CDM_EXPORT __declspec(dllexport)
#else
#define CDM_EXPORT __declspec(dllimport)
#endif  // defined(CDM_IMPLEMENTATION)

#else  // defined(WIN32)

#if defined(CDM_IMPLEMENTATION)
#define CDM_EXPORT __attribute__((visibility("default")))
#else
#define CDM_EXPORT
#endif

#endif  // defined(WIN32)

// We maintain this macro for backward compatibility only.
#define INITIALIZE_CDM_MODULE InitializeCdmModule

extern "C" {
CDM_EXPORT void InitializeCdmModule();

CDM_EXPORT void DeinitializeCdmModule();

// Returns a pointer to the requested CDM Host interface upon success.
// Returns NULL if the requested CDM Host interface is not supported.
// The caller should cast the returned pointer to the type matching
// |host_interface_version|.
typedef void* (*GetCdmHostFunc)(int host_interface_version, void* user_data);

// Returns a pointer to the requested CDM upon success.
// Returns NULL if an error occurs or the requested |cdm_interface_version| or
// |key_system| is not supported or another error occurs.
// The caller should cast the returned pointer to the type matching
// |cdm_interface_version|.
// Caller retains ownership of arguments and must call Destroy() on the returned
// object.
CDM_EXPORT void* CreateCdmInstance(
    int cdm_interface_version,
    const char* key_system, uint32_t key_system_size,
    GetCdmHostFunc get_cdm_host_func, void* user_data);

CDM_EXPORT const char* GetCdmVersion();
}

namespace cdm {

class Host_1;
class Host_4;

enum Status {
  kSuccess = 0,
  kNoKey = 2,  // The required decryption key is not available.
  kSessionError = 3,  // Session management error.
  kDecryptError = 4,  // Decryption failed.
  kDecodeError = 5,  // Error decoding audio or video.
  kRetry = 6,  // Buffer temporarily cannot be accepted, delay and retry.
  kNeedsDeviceCertificate = 7  // A certificate is required for licensing.
};

// This must be consistent with MediaKeyError defined in the
// Encrypted media Extensions (EME) specification: http://goo.gl/IBjNCP
enum MediaKeyError {
  kUnknownError = 1,
  kClientError = 2,
  kOutputError = 4,
};

// The type of session to create. The valid types are defined in the spec:
// http://goo.gl/vmc3pd
enum SessionType {
  kTemporary = 0,
  kPersistent = 1,
  kProvisioning = 2,
};

// The type of stream.  Used in DecryptDecodeAndRender.
enum StreamType {
  kStreamTypeAudio = 0,
  kStreamTypeVideo = 1
};

// An input buffer can be split into several continuous subsamples.
// A SubsampleEntry specifies the number of clear and cipher bytes in each
// subsample. For example, the following buffer has three subsamples:
//
// |<----- subsample1 ----->|<----- subsample2 ----->|<----- subsample3 ----->|
// |   clear1   |  cipher1  |  clear2  |   cipher2   | clear3 |    cipher3    |
//
// For decryption, all of the cipher bytes in a buffer should be concatenated
// (in the subsample order) into a single logical stream. The clear bytes should
// not be considered as part of decryption.
//
// Stream to decrypt:   |  cipher1  |   cipher2   |    cipher3    |
// Decrypted stream:    | decrypted1|  decrypted2 |   decrypted3  |
//
// After decryption, the decrypted bytes should be copied over the position
// of the corresponding cipher bytes in the original buffer to form the output
// buffer. Following the above example, the decrypted buffer should be:
//
// |<----- subsample1 ----->|<----- subsample2 ----->|<----- subsample3 ----->|
// |   clear1   | decrypted1|  clear2  |  decrypted2 | clear3 |   decrypted3  |
//
struct SubsampleEntry {
  SubsampleEntry(uint32_t clear_bytes, uint32_t cipher_bytes)
      : clear_bytes(clear_bytes), cipher_bytes(cipher_bytes) {}

  uint32_t clear_bytes;
  uint32_t cipher_bytes;
};

// Represents an input buffer to be decrypted (and possibly decoded). It
// does not own any pointers in this struct.
struct InputBuffer {
  InputBuffer()
      : data(NULL),
        data_size(0),
        data_offset(0),
        key_id(NULL),
        key_id_size(0),
        iv(NULL),
        iv_size(0),
        subsamples(NULL),
        num_subsamples(0),
        timestamp(0) {}

  const uint8_t* data;  // Pointer to the beginning of the input data.
  uint32_t data_size;  // Size (in bytes) of |data|.

  uint32_t data_offset;  // Number of bytes to be discarded before decryption.

  const uint8_t* key_id;  // Key ID to identify the decryption key.
  uint32_t key_id_size;  // Size (in bytes) of |key_id|.

  const uint8_t* iv;  // Initialization vector.
  uint32_t iv_size;  // Size (in bytes) of |iv|.

  const struct SubsampleEntry* subsamples;
  uint32_t num_subsamples;  // Number of subsamples in |subsamples|.

  int64_t timestamp;  // Presentation timestamp in microseconds.
};

// Represents a buffer created by the Host.
class Buffer {
 public:
  // Destroys the buffer in the same context as it was created.
  virtual void Destroy() = 0;

  virtual int32_t Capacity() const = 0;
  virtual uint8_t* Data() = 0;
  virtual void SetSize(int32_t size) = 0;
  virtual int32_t Size() const = 0;

 protected:
  Buffer() {}
  virtual ~Buffer() {}

 private:
  Buffer(const Buffer&);
  void operator=(const Buffer&);
};

// Represents a key-value map.
// Both created and destroyed by the Host.
// Data is filled in by the CDM.
// Need not be implemented if QueryKeyStatus() is not called.
class KeyValueMap {
 public:
  virtual void Set(const char* key, void* value, size_t value_size) = 0;

 protected:
  KeyValueMap() {}
  virtual ~KeyValueMap() {}

 private:
  KeyValueMap(const KeyValueMap&);
  void operator=(const KeyValueMap&);
};

// Represents a decrypted block that has not been decoded.
class DecryptedBlock {
 public:
  virtual void SetDecryptedBuffer(Buffer* buffer) = 0;
  virtual Buffer* DecryptedBuffer() = 0;

  virtual void SetTimestamp(int64_t timestamp) = 0;
  virtual int64_t Timestamp() const = 0;

 protected:
  DecryptedBlock() {}
  virtual ~DecryptedBlock() {}
};

// The FileIO interface provides a way for the CDM to store data in a file in
// persistent storage. This interface aims only at providing basic read/write
// capabilities and should not be used as a full fledged file IO API.
//
// All methods that report their result via calling a method on FileIOClient
// (currently, this is Open, Read, and Write) must call into FileIOClient on the
// same thread they were called on and must do so before returning. This
// restriction may be lifted in the future.
//
// Each domain (e.g. "example.com") and each CDM has it's own persistent
// storage. All instances of a given CDM associated with a given domain share
// the same persistent storage.
//
// Note to implementors of this interface:
// Per-origin storage and the ability for users to clear it are important.
// See http://www.w3.org/TR/encrypted-media/#privacy-storedinfo.
class FileIO {
 public:
  // Opens the file with |file_name| for read and write.
  // FileIOClient::OnOpenComplete() will be called after the opening
  // operation finishes.
  // - When the file is opened by a CDM instance, it will be classified as "in
  //   use". In this case other CDM instances in the same domain may receive
  //   kInUse status when trying to open it.
  // - |file_name| should not include path separators.
  virtual void Open(const char* file_name, uint32_t file_name_size) = 0;

  // Reads the contents of the file. FileIOClient::OnReadComplete() will be
  // called with the read status. Read() should not be called if a previous
  // Read() or Write() call is still pending; otherwise OnReadComplete() will
  // be called with kInUse.
  virtual void Read() = 0;

  // Writes |data_size| bytes of |data| into the file.
  // FileIOClient::OnWriteComplete() will be called with the write status.
  // All existing contents in the file will be overwritten. Calling Write() with
  // NULL |data| will clear all contents in the file. Write() should not be
  // called if a previous Write() or Read() call is still pending; otherwise
  // OnWriteComplete() will be called with kInUse.
  virtual void Write(const uint8_t* data, uint32_t data_size) = 0;

  // Closes the file if opened, destroys this FileIO object and releases any
  // resources allocated. The CDM must call this method when it finished using
  // this object. A FileIO object must not be used after Close() is called.
  virtual void Close() = 0;

 protected:
  FileIO() {}
  virtual ~FileIO() {}
};

// Responses to FileIO calls.
class FileIOClient {
 public:
  enum Status {
    kSuccess = 0,
    kInUse,
    kError
  };

  // Response to a FileIO::Open() call with the open |status|.
  virtual void OnOpenComplete(Status status) = 0;

  // Response to a FileIO::Read() call to provide |data_size| bytes of |data|
  // read from the file.
  // - kSuccess indicates that all contents of the file has been successfully
  //   read. In this case, 0 |data_size| means that the file is empty.
  // - kInUse indicates that there are other read/write operations pending.
  // - kError indicates read failure, e.g. the storage isn't open or cannot be
  //   fully read.
  virtual void OnReadComplete(Status status,
                              const uint8_t* data, uint32_t data_size) = 0;

  // Response to a FileIO::Write() call.
  // - kSuccess indicates that all the data has been written into the file
  //   successfully.
  // - kInUse indicates that there are other read/write operations pending.
  // - kError indicates write failure, e.g. the storage isn't open or cannot be
  //   fully written. Upon write failure, the contents of the file should be
  //   regarded as corrupt and should not used.
  virtual void OnWriteComplete(Status status) = 0;

 protected:
  FileIOClient() {}
  virtual ~FileIOClient() {}
};

// ContentDecryptionModule interface that all CDMs need to implement.
// CDM interfaces are versioned for backward compatibility.
// Note: ContentDecryptionModule implementations must use the Host
// to allocate any Buffer that needs to be passed back to the caller.
// Host implementations must call Buffer::Destroy() when a Buffer is created
// that will never be returned to the caller.

// Based on chromium's ContentDecryptionModule_1.
class ContentDecryptionModule_1 {
 public:
  static const int kVersion = 1002;
  typedef Host_1 Host;

  // Generates a |key_request| given |type| and |init_data|.
  //
  // Returns kSuccess if the key request was successfully generated, in which
  // case the CDM must send the key message by calling Host::SendKeyMessage().
  // Returns kSessionError if any error happened, in which case the CDM must
  // send a key error by calling Host::SendKeyError().
  virtual Status GenerateKeyRequest(
      const char* type, int type_size,
      const uint8_t* init_data, int init_data_size) = 0;

  // Adds the |key| to the CDM to be associated with |key_id|.
  //
  // Returns kSuccess if the key was successfully added, kSessionError
  // otherwise.
  virtual Status AddKey(const char* session_id, int session_id_size,
                        const uint8_t* key, int key_size,
                        const uint8_t* key_id, int key_id_size) = 0;

  // Tests whether |key_id| is known to any current session.
  virtual bool IsKeyValid(const uint8_t* key_id, int key_id_size) = 0;

  // Closes the session identified by |session_id| and releases all crypto
  // resources related to that session. After calling this, it is invalid to
  // refer to this session any more, because the session has been destroyed.
  //
  // Returns kSuccess if the session |session_id| was successfully closed and
  // all resources released, kSessionError otherwise.
  virtual Status CloseSession(const char* session_id, int session_id_size) = 0;

  // Performs scheduled operation with |context| when the timer fires.
  virtual void TimerExpired(void* context) = 0;

  // Decrypts the |encrypted_buffer|.
  //
  // Returns kSuccess if decryption succeeded, in which case the callee
  // should have filled the |decrypted_buffer| and passed the ownership of
  // |data| in |decrypted_buffer| to the caller.
  // Returns kNoKey if the CDM did not have the necessary decryption key
  // to decrypt.
  // Returns kDecryptError if any other error happened.
  // If the return value is not kSuccess, |decrypted_buffer| should be ignored
  // by the caller.
  virtual Status Decrypt(const InputBuffer& encrypted_buffer,
                         DecryptedBlock* decrypted_buffer) = 0;

  // Decrypts the |encrypted_buffer|, decodes the decrypted buffer, and passes
  // the video frame or audio samples to the rendering FW/HW.  No data is
  // returned to the caller.
  //
  // Returns kSuccess if decryption, decoding, and rendering all succeeded.
  // Returns kNoKey if the CDM did not have the necessary decryption key
  // to decrypt.
  // Returns kRetry if |encrypted_buffer| cannot be accepted (e.g, video
  // pipeline is full). Caller should retry after a short delay.
  // Returns kDecryptError if any decryption error happened.
  // Returns kDecodeError if any decoding error happened.
  // If the return value is not kSuccess, |video_frame| should be ignored by
  // the caller.
  virtual Status DecryptDecodeAndRenderFrame(
      const InputBuffer& encrypted_buffer) = 0;

  // Decrypts the |encrypted_buffer|, decodes the decrypted buffer into a
  // video frame, and passes the frame to the rendering FW/HW.  No data
  // is returned.
  //
  // Returns kSuccess if decryption, decoding, and rendering all succeeded.
  // Returns kNoKey if the CDM did not have the necessary decryption key
  // to decrypt.
  // Returns kRetry if |encrypted_buffer| cannot be accepted (e.g., audio
  // pipeline is full). Caller should retry after a short delay.
  // Returns kDecryptError if any decryption error happened.
  // Returns kDecodeError if any decoding error happened.
  // If the return value is not kSuccess or kRetry, the audiostream has failed
  // and should be reset.
  virtual Status DecryptDecodeAndRenderSamples(
      const InputBuffer& encrypted_buffer) = 0;

  // Destroys the object in the same context as it was created.
  virtual void Destroy() = 0;

  // Provisioning-related methods.
  virtual Status GetProvisioningRequest(
      std::string* request, std::string* default_url) = 0;

  virtual Status HandleProvisioningResponse(
      std::string& response) = 0;

 protected:
  ContentDecryptionModule_1() {}
  virtual ~ContentDecryptionModule_1() {}
};

// Based on chromium's ContentDecryptionModule_4 and ContentDecryptionModule_5.
class ContentDecryptionModule_4 {
 public:
  static const int kVersion = 1004;
  typedef Host_4 Host;

  // The non-decryption methods on this class, such as CreateSession(),
  // get passed a |session_id| for a MediaKeySession object. It must be used in
  // the reply via Host methods (e.g. Host::OnSessionMessage()).
  // Note: |session_id| is different from MediaKeySession's sessionId attribute,
  // which is referred to as |web_session_id| in this file.

  // Creates a new session and generates a key request given |init_data| and
  // |session_type|.  OnSessionCreated() will be called with a web session ID
  // once the session exists.  OnSessionMessage() will subsequently be called
  // with the key request.  A session represents hardware crypto resources,
  // (if any exist for the platform), which may be in limited supply.
  // For sessions of type kProvisioning, |mime_type| and |init_data| will be
  // ignored and may be NULL.
  virtual void CreateSession(uint32_t session_id,
                             const char* mime_type, uint32_t mime_type_size,
                             const uint8_t* init_data, uint32_t init_data_size,
                             SessionType session_type) = 0;

  // Creates a new session and loads a previous persistent session into it that
  // has a web session ID of |web_session_id|.  OnSessionCreated() will be
  // called once the session is loaded.
  virtual void LoadSession(
      uint32_t session_id,
      const char* web_session_id, uint32_t web_session_id_length) = 0;

  // Updates the session with |response|.
  virtual void UpdateSession(
      uint32_t session_id,
      const uint8_t* response, uint32_t response_size) = 0;

  // Tests whether |key_id| is known to any current session.
  virtual bool IsKeyValid(const uint8_t* key_id, int key_id_size) = 0;

  // Releases the resources for the session |session_id|.
  // After calling this, it is invalid to refer to this session any more.
  // If any hardware crypto resources were being used by this session, they will
  // be released.
  // If this session was a persistent session, this will NOT delete the
  // persisted data. The persisted data will be preserved so that the session
  // can be reloaded later with LoadSession(). To delete the persisted session,
  // use RemoveSession().
  virtual void ReleaseSession(uint32_t session_id) = 0;

  // Creates a new session and generates a key release request for the
  // existing persistent session identified by |web_session_id|.
  // OnSessionCreated() will be called once the session exists.
  // OnSessionMessage() will subsequently be called with the key release
  // request.
  virtual void RemoveSession(
      uint32_t session_id,
      const char* web_session_id, uint32_t web_session_id_length) = 0;

  // Signals to the CDM that it should use server certificates to protect the
  // privacy of the user. The primary use of this is when the application
  // driving the CDM is untrusted code, such as when a web browser allows a web
  // page's JavaScript to access the CDM. By using server certificates to
  // encrypt communication with the license server, device-identifying
  // information cannot be extracted from the license exchange process by a
  // malicious caller.
  // Unless you also call SetServerCertificate() to set a pre-cached server
  // certificate, the CDM will perform a certificate exchange with the server
  // prior to any key exchanges.
  // This method may not be called if any sessions are open. It is typically
  // called before any sessions have been opened, but may also be called if all
  // open sessions have been released.
  // Note that calling SetServerCertificate() implicitly calls this method as
  // well.
  virtual Status UsePrivacyMode() = 0;

  // Provides a server certificate to be used to encrypt messages to the
  // license server. Calling this is like calling UsePrivacyMode(), except that
  // because the certificate is provided up-front, the CDM does not have to
  // perform a certificate exchange with the server.
  // This method may not be called if any sessions are open. It is typically
  // called before any sessions have been opened, but may also be called if all
  // open sessions have been released.
  // Note that calling this method also implicitly calls UsePrivacyMode().
  virtual Status SetServerCertificate(
      const uint8_t* server_certificate_data,
      uint32_t server_certificate_data_size) = 0;

  // Performs scheduled operation with |context| when the timer fires.
  virtual void TimerExpired(void* context) = 0;

  // Decrypts the |encrypted_buffer|.
  //
  // Returns kSuccess if decryption succeeded, in which case the callee
  // should have filled the |decrypted_buffer| and passed the ownership of
  // |data| in |decrypted_buffer| to the caller.
  // Returns kNoKey if the CDM did not have the necessary decryption key
  // to decrypt.
  // Returns kDecryptError if any other error happened.
  // If the return value is not kSuccess, |decrypted_buffer| should be ignored
  // by the caller.
  virtual Status Decrypt(const InputBuffer& encrypted_buffer,
                         DecryptedBlock* decrypted_buffer) = 0;

  // Decrypts the |encrypted_buffer|, decodes the decrypted buffer, and passes
  // the video or audio frames to the rendering FW/HW.  No data is returned to
  // the caller.
  //
  // Returns kSuccess if decryption, decoding, and rendering all succeeded.
  // Returns kNoKey if the CDM did not have the necessary decryption key
  // to decrypt.
  // Returns kRetry if |encrypted_buffer| cannot be accepted (e.g, video
  // pipeline is full). Caller should retry after a short delay.
  // Returns kDecryptError if any decryption error happened.
  // Returns kDecodeError if any decoding error happened.
  virtual Status DecryptDecodeAndRender(const InputBuffer& encrypted_buffer,
                                        StreamType stream_type) = 0;

  // Destroys the object in the same context as it was created.
  virtual void Destroy() = 0;

 protected:
  ContentDecryptionModule_4() {}
  virtual ~ContentDecryptionModule_4() {}
};

// Host interface that the CDM can call into to access browser side services.
// Host interfaces are versioned for backward compatibility.

// Based on chromium's Host_1.
class Host_1 {
 public:
  static const int kVersion = 1002;

  // Returns a Buffer* containing non-zero members upon success, or NULL on
  // failure. The caller owns the Buffer* after this call. The buffer is not
  // guaranteed to be zero initialized. The capacity of the allocated Buffer
  // is guaranteed to be not less than |capacity|.
  virtual Buffer* Allocate(int32_t capacity) = 0;

  // Requests the host to call ContentDecryptionModule::TimerExpired() in
  // |delay_ms| from now with |context|.
  virtual void SetTimer(int64_t delay_ms, void* context) = 0;

  // Returns the current epoch wall time in seconds.
  virtual double GetCurrentWallTimeInSeconds() = 0;

  // Sends a keymessage event to the application.
  // Length parameters should not include null termination.
  virtual void SendKeyMessage(
      const char* session_id, int32_t session_id_length,
      const char* message, int32_t message_length,
      const char* default_url, int32_t default_url_length) = 0;

  // Sends a keyerror event to the application.
  // |session_id_length| should not include null termination.
  virtual void SendKeyError(const char* session_id,
                            int32_t session_id_length,
                            MediaKeyError error_code,
                            uint32_t system_code) = 0;

  // Version 1.3:
  // These virtual member functions extend the cdm::Host interface to allow
  // the CDM to query the host for various information.

  // Asks the host to persist a name-value pair.
  virtual void SetPlatformString(const std::string& name,
                                 const std::string& value) = 0;

  // Retrieves a value by name.  If there is no such value, the Host should
  // set value to an empty string.
  virtual void GetPlatformString(const std::string& name,
                                 std::string* value) = 0;

 protected:
  Host_1() {}
  virtual ~Host_1() {}
};

// Based on chromium's Host_4 and Host_5.
class Host_4 {
 public:
  static const int kVersion = 1004;

  // Returns a Buffer* containing non-zero members upon success, or NULL on
  // failure. The caller owns the Buffer* after this call. The buffer is not
  // guaranteed to be zero initialized. The capacity of the allocated Buffer
  // is guaranteed to be not less than |capacity|.
  virtual Buffer* Allocate(uint32_t capacity) = 0;

  // Requests the host to call ContentDecryptionModule::TimerFired() |delay_ms|
  // from now with |context|.
  virtual void SetTimer(int64_t delay_ms, void* context) = 0;

  // Returns the current epoch wall time in seconds.
  virtual double GetCurrentWallTimeInSeconds() = 0;

  // Called by the CDM when a session is created or loaded and the value for the
  // MediaKeySession's sessionId attribute is available (|web_session_id|).
  // This must be called before OnSessionMessage() or OnSessionUpdated() is
  // called for |session_id|. |web_session_id_length| should not include null
  // termination.
  // When called in response to LoadSession(), the |web_session_id| must be the
  // same as the |web_session_id| passed in LoadSession().
  virtual void OnSessionCreated(
      uint32_t session_id,
      const char* web_session_id, uint32_t web_session_id_length) = 0;

  // Called by the CDM when it has a message for session |session_id|.
  // Length parameters should not include null termination.
  virtual void OnSessionMessage(
      uint32_t session_id,
      const char* message, uint32_t message_length,
      const char* destination_url, uint32_t destination_url_length) = 0;

  // Called by the CDM when session |session_id| has been updated.
  virtual void OnSessionUpdated(uint32_t session_id) = 0;

  // Called by the CDM when session |session_id| is closed.
  virtual void OnSessionClosed(uint32_t session_id) = 0;

  // Called by the CDM when an error occurs in session |session_id|.
  virtual void OnSessionError(uint32_t session_id,
                              Status error_code,
                              uint32_t system_code) = 0;

  // Creates a FileIO object from the host to do file IO operation. Returns NULL
  // if a FileIO object cannot be obtained. Once a valid FileIO object is
  // returned, |client| must be valid until FileIO::Close() is called. The
  // CDM can call this method multiple times to operate on different files.
  virtual FileIO* CreateFileIO(FileIOClient* client) = 0;

 protected:
  Host_4() {}
  virtual ~Host_4() {}
};

typedef ContentDecryptionModule_1 ContentDecryptionModule;
const int kCdmInterfaceVersion = ContentDecryptionModule::kVersion;

typedef ContentDecryptionModule::Host Host;
const int kHostInterfaceVersion = Host::kVersion;

}  // namespace cdm

#endif  // WVCDM_CDM_CONTENT_DECRYPTION_MODULE_H_
