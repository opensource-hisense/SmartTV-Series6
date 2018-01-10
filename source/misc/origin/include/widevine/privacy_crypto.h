// Copyright 2013 Google Inc. All Rights Reserved.
//
// Description:
//   Declaration of classes representing AES and RSA public keys used
//   for signature verification and encryption.
//
// AES encryption details:
//   Algorithm: AES-CBC
//
// RSA signature details:
//   Algorithm: RSASSA-PSS
//   Hash algorithm: SHA1
//   Mask generation function: mgf1SHA1
//   Salt length: 20 bytes
//   Trailer field: 0xbc
//
// RSA encryption details:
//   Algorithm: RSA-OAEP
//   Mask generation function: mgf1SHA1
//   Label (encoding paramter): empty string
//
#ifndef WVCDM_CORE_PRIVACY_CRYPTO_H_
#define WVCDM_CORE_PRIVACY_CRYPTO_H_

#include <string>

#include "wv_cdm_types.h"

namespace wvcdm {

class AesCbcKey {
 public:
  AesCbcKey();
  ~AesCbcKey();

  bool Init(const std::string& key);
  bool Encrypt(const std::string& in, std::string* out, std::string* iv);

 private:
  std::string key_;

  CORE_DISALLOW_COPY_AND_ASSIGN(AesCbcKey);
};

class RsaPublicKey {
 public:
  RsaPublicKey();
  ~RsaPublicKey();

  // Initializes an RsaPublicKey object using a DER encoded PKCS#1 RSAPublicKey
  bool Init(const std::string& serialized_key);

  // Encrypt a message using RSA-OAEP. Caller retains ownership of all
  // parameters. Returns true if successful, false otherwise.
  bool Encrypt(const std::string& plaintext, std::string* ciphertext);

  // Verify RSASSA-PSS signature. Caller retains ownership of all parameters.
  // Returns true if validation succeeds, false otherwise.
  bool VerifySignature(const std::string& message,
                       const std::string& signature);

 private:
  std::string serialized_key_;

  CORE_DISALLOW_COPY_AND_ASSIGN(RsaPublicKey);
};

}  // namespace wvcdm

#endif  // WVCDM_CORE_PRIVACY_CRYPTO_H_
