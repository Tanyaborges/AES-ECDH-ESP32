using namespace std;
#include "SPIFFS.h"
#include <iostream>
#include "Crypto.h"
#include "AES.h"

// Define the elliptic curve parameters
const char *curve_name = "secp256r1";
const size_t curve_size = 256;

// Define the private and public keys
byte private_key[32];
byte public_key[64];

// Define the shared secret key
byte shared_secret[32];

// Define the plaintext and ciphertext
byte plaintext[] = "Hello World!";
byte ciphertext[sizeof(plaintext)];

void setup() {
  // Generate the private key
  CryptoKeyPair key_pair = Crypto.generateKeyPair(curve_name);
  CryptoPrivateKey private_key_obj = key_pair.private_key();
  private_key_obj.serialize(private_key, sizeof(private_key));

  // Extract the public key
  CryptoPublicKey public_key_obj = key_pair.public_key();
  public_key_obj.serialize(public_key, sizeof(public_key));

  // Generate the shared secret key
  CryptoECDH ecdh(curve_name);
  CryptoPublicKey remote_public_key = CryptoPublicKey(public_key, sizeof(public_key));
  ecdh.deriveSecret(shared_secret, sizeof(shared_secret), remote_public_key, private_key_obj);
  
  // Encrypt the plaintext using AES-256
  AES256 aes(shared_secret);
  aes.encrypt(plaintext, sizeof(plaintext), ciphertext);
}

void loop() {
  // Do something with the ciphertext
}
