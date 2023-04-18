using namespace std;
#include "SPIFFS.h"
#include <iostream>
#include "AES.h"
#include "base64.h"
#include "uECC.h"
#define KEY_LEN 32
AES aes;
const struct uECC_Curve_t *curve = uECC_secp256r1(); // Use the secp256r1 curve
uint8_t getrnd() {
    uint8_t really_random = *(volatile uint8_t *)0x3FF20E44;
    return really_random;
}

// Generate a random initialization vector
void gen_iv(byte  *iv) {
    for (int i = 0 ; i < N_BLOCK ; i++ ) {
        iv[i]= (byte) getrnd();
    }
}
    
void setup() {
    Serial.begin(115200);
    if(!SPIFFS.begin(true)){
      Serial.println("An Error has occurred while mounting SPIFFS");
      return;
    }
    File file = SPIFFS.open("/abc.txt");
    if(!file){
      Serial.println("Failed to open file for reading");
      return;
    }
    String msg="";
    
      while(file.available()){
     // Serial.write(file.read());
        msg += (char)file.read();
      }
    file.close();
    
    uint8_t private_key[KEY_LEN];
    uint8_t public_key[2 * KEY_LEN];
    uECC_make_key(public_key, private_key, uECC_secp256r1());

    // Send the public key to the other party

    // Receive the other party's public key
    uint8_t other_public_key[2 * KEY_LEN];

    // Derive the shared secret key using ECDH and store it
    uint8_t shared_secret[KEY_LEN];
    uECC_shared_secret(other_public_key, private_key, shared_secret, uECC_secp256r1());    
    // Print the shared secret to the serial console
    Serial.print("Shared secret key produced using ECDH: ");
    for (int i = 0; i < 32; i++) {
      Serial.print(shared_secret[i], HEX);
   }
    Serial.println();
    char b64data[200];
    byte cipher[1000];
    byte iv [N_BLOCK] ;
    char decoded[200];
    //Serial.println("Let's encrypt:");
    // Our AES key. Note that is the same that is used on the Node-Js side but as hex bytes.
    byte key[] = { 0x2B, 0x7E, 0x15, 0x16, 0x28, 0xAE, 0xD2, 0xA6, 0xAB, 0xF7, 0x15, 0x88, 0x09, 0xCF, 0x4F, 0x3C };
    
    // The unitialized Initialization vector
    byte my_iv[N_BLOCK] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    
    aes.set_key( shared_secret , sizeof(shared_secret));  // Get the globally defined key
    gen_iv( my_iv );                  // Generate a random IV
    
    // Print the IV
    base64_encode( b64data, (char *)my_iv, N_BLOCK);
  //  Serial.println(" IV b64: " + String(b64data));
    Serial.println("File Content:");
    Serial.println( msg );
 
    int b64len = base64_encode(b64data, (char *)msg.c_str(),msg.length());
    Serial.println ("Message in B64: " + String(b64data) );
    //Serial.println (" The lenght is:  " + String(b64len) );
    
    // For sanity check purpose
    //base64_decode( decoded , b64data , b64len );
    //Serial.println("Decoded: " + String(decoded));
    
    // Encrypt! With AES128, our ECDH key and IV, CBC and pkcs7 padding    
   // aes.do_aes_encrypt((byte *)b64data, b64len , cipher, key, 128, my_iv);
    aes.do_aes_encrypt((byte *)b64data, b64len , cipher, shared_secret, 128, my_iv);
  
    Serial.println("Encryption done!");
    
    Serial.println("Cipher size: " + String(aes.get_size()));
    
    base64_encode(b64data, (char *)cipher, aes.get_size() );
    Serial.println ("Encrypted data: " + String(b64data) );
    
    Serial.println("Done...");
      
}

void loop() {
  // put your main code here, to run repeatedly:

}
