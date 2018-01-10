// Copyright 2013 Google Inc. All Rights Reserved.

#ifndef WVCDM_CDM_TEST_TEST_HOST_4_H_
#define WVCDM_CDM_TEST_TEST_HOST_4_H_

#include "content_decryption_module.h"
#include "gmock/gmock.h"
#include <queue>

#include "wv_cdm_common.h"
#include "wv_cdm_types.h"

class TestHost_4 : public cdm::Host_4 {
 public:
  // These structs are used to store the SessionMessages and SessionErrors
  // passed to this class' objects.

  struct SessionMessage {
    uint32_t session_id;
    std::string message;
    std::string default_url;
  };

  struct SessionError {
    uint32_t session_id;
    cdm::Status error_code;
    uint32_t system_code;
  };

  TestHost_4();
  virtual ~TestHost_4();

  // cdm::Host implementation.
  virtual cdm::Buffer* Allocate(uint32_t capacity) OVERRIDE;

  virtual void SetTimer(int64_t delay_ms, void* context) OVERRIDE;

  virtual double GetCurrentWallTimeInSeconds() OVERRIDE;

  virtual void OnSessionCreated(uint32_t session_id, const char* web_session_id,
                                uint32_t web_session_id_length) OVERRIDE;

  virtual void OnSessionMessage(uint32_t session_id, const char* message,
                                uint32_t message_length,
                                const char* destination_url,
                                uint32_t destination_url_length) OVERRIDE;

  virtual void OnSessionUpdated(uint32_t session_id) OVERRIDE;

  virtual void OnSessionClosed(uint32_t session_id) OVERRIDE;

  virtual void OnSessionError(uint32_t session_id, cdm::Status error_code,
                              uint32_t system_code) OVERRIDE;

  virtual cdm::FileIO* CreateFileIO(cdm::FileIOClient* client) OVERRIDE;

  // Methods only for this test.
  void FastForwardTime(double seconds);
  int SessionMessagesSize() const;
  int SessionErrorsSize() const;
  int NumTimers() const;

  // Returns Key{Message,Error} (replace Message with Error for SessionError).
  // It returns the most recent message passed to SendSessionMessage(). Another
  // call to this method without a new SendSessionMessage() call will return an
  // empty SessionMessage struct.
  SessionMessage GetLastSessionMessage();
  SessionError GetLastSessionError();

  SessionMessage GetSessionMessage(int index) const;
  SessionError GetSessionError(int index) const;

  void SetCdmPtr(cdm::ContentDecryptionModule_4* cdm);
  std::map<uint32_t, std::string> session_map;

  // Accessed by all FileIO objects.
  std::map<std::string, std::string> file_store;

 private:
  struct Timer {
    Timer(double expiry_time, void* context)
        : expiry_time(expiry_time), context(context) {}

    bool operator<(const Timer& other) const {
      // We want to reverse the order so that the smallest expiry times go to
      // the top of the priority queue.
      return expiry_time > other.expiry_time;
    }

    double expiry_time;
    void* context;
  };

  double current_time_;
  std::priority_queue<Timer> timers_;

  std::vector<SessionMessage> session_messages_;
  std::vector<SessionError> session_errors_;

  bool has_new_session_message_;
  bool has_new_session_error_;

  cdm::ContentDecryptionModule_4* cdm_;

  CORE_DISALLOW_COPY_AND_ASSIGN(TestHost_4);
};

#endif  // WVCDM_CDM_TEST_TEST_HOST_4_H_
