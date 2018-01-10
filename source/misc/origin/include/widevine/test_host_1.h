// Copyright 2013 Google Inc. All Rights Reserved.

#ifndef WVCDM_CDM_TEST_TEST_HOST_1_H_
#define WVCDM_CDM_TEST_TEST_HOST_1_H_

#include "content_decryption_module.h"

#include <map>
#include <queue>

#include "wv_cdm_common.h"
#include "wv_cdm_types.h"

class TestHost_1 : public cdm::Host_1 {
 public:
  // These structs are used to store the KeyMessages and KeyErrors passed to
  // this class' objects.
  struct KeyMessage {
    std::string session_id;
    std::string message;
    std::string default_url;
  };

  struct KeyError {
    KeyError() : error_code(cdm::kUnknownError), system_code(0) {}
    std::string session_id;
    cdm::MediaKeyError error_code;
    uint32_t system_code;
  };

  TestHost_1();
  virtual ~TestHost_1();

  // cdm::Host implementation.
  virtual cdm::Buffer* Allocate(int32_t capacity) OVERRIDE;

  virtual void SetTimer(int64_t delay_ms, void* context) OVERRIDE;

  virtual double GetCurrentWallTimeInSeconds() OVERRIDE;

  virtual void SendKeyMessage(const char* session_id, int32_t session_id_length,
                              const char* message, int32_t message_length,
                              const char* default_url,
                              int32_t default_url_length) OVERRIDE;

  virtual void SendKeyError(const char* session_id, int32_t session_id_length,
                            cdm::MediaKeyError error_code,
                            uint32_t system_code) OVERRIDE;

  virtual void GetPlatformString(const std::string& name,
                                 std::string* value) OVERRIDE;

  virtual void SetPlatformString(const std::string& name,
                                 const std::string& value) OVERRIDE;

  // Methods only for this test.
  void FastForwardTime(double seconds);
  int KeyMessagesSize() const;
  int KeyErrorsSize() const;
  int NumTimers() const;

  // Returns Key{Message,Error} (replace Message with Error for KeyError). It
  // returns the most recent message passed to SendKeyMessage(). Another call
  // to this method without a new SendKeyMessage() call will return an empty
  // KeyMessage struct.
  KeyMessage GetLastKeyMessage();
  KeyError GetLastKeyError();

  KeyMessage GetKeyMessage(int index) const;
  KeyError GetKeyError(int index) const;

  void SetCdmPtr(cdm::ContentDecryptionModule_1* cdm);

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

  std::vector<KeyMessage> key_messages_;
  std::vector<KeyError> key_errors_;

  bool has_new_key_message_;
  bool has_new_key_error_;

  std::map<std::string, std::string> platform_strings_;

  cdm::ContentDecryptionModule_1* cdm_;

  CORE_DISALLOW_COPY_AND_ASSIGN(TestHost_1);
};

#endif  // WVCDM_CDM_TEST_TEST_HOST_1_H_
