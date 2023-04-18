# AES-ECDH-ESP32

The project aims to establish a security model for IoT devices using the ESP32 microcontroller and implementing Elliptic Curve Diffie Hellman (ECDH) and Advanced Encryption Standard (AES) algorithms for secure data transmission. The proposed approach aims to provide end-to-end encryption and authentication for IoT devices, making it suitable for a wide range of IoT applications.

To implement the proposed algorithm, the following steps are required:

Step 1: The client requests a file from the server, and the server chooses a file for encryption.

Step 2: The elliptic curve generates several private and public key pairs, and AES uses one of the key pairs produced by an elliptic curve to encrypt the text file. One key is kept secret with the server, and one key is kept hidden with the client from among the several key pairs.

Step 3: ECDH establishes a shared secret between the client and server, and Diffie-Hellman handles the key agreement while AES encrypts the input text file on the other side. The user can only decode the encrypted text file if the agreement is successful.

Step 4: The input text file is encrypted with AES using the ECC-generated key, and the encrypted content is uploaded to the server using the combined key or another key that has been received using DHKE as a shared secret. After both the client and the server have successfully established a secret key, the client obtains the encoded document from the server and decrypts it using the combined key created by ECC and DHKE.

Step 5: Upon successful completion of the decryption, the client receives the original file.

The most crucial stage of the project is the creation of a security framework that integrates the ECDH and AES algorithms on the ESP32 microcontroller. The proposed paradigm aims to be readily integrated with existing IoT networks and scalable. To confirm the model's efficacy in ensuring safe connectivity for IoT devices, it will be tested in a real-world environment.

The development of an ECDH and AES-based security model for IoT using ESP32 aims to provide a secure and dependable method of sending sensitive documents between IoT devices and the cloud storage server. The proposed architecture aims to offer end-to-end encryption for data exchanged between IoT applications and the cloud storage server, ensuring that secret and sensitive information is kept safe and secure.
