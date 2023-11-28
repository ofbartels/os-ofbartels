#include <iostream>
#include <cstring>
#include <openssl/evp.h>
#include <openssl/err.h>

using namespace std;

void handleErrors() {
    unsigned long errCode;
    while ((errCode = ERR_get_error())) {
        char *errMsg = ERR_error_string(errCode, NULL);
        cerr << "Error: " << errMsg << endl;
    }
    abort();
}

int main() {
    // Initialize OpenSSL
    ERR_load_crypto_strings();
    OpenSSL_add_all_algorithms();

    // Key and IV should be generated in a secure way
    unsigned char key[EVP_MAX_KEY_LENGTH] = "0123456789abcdef0123456789abcdef"; // Example key
    unsigned char iv[16];
    memcpy(iv, "1234567890abcdef", 16);

    
    // Message to encrypt
    const char *plaintext = "Hello, World!";
    unsigned char ciphertext[128];
    unsigned char decryptedtext[128];

    int decryptedtext_len, ciphertext_len;

    // Create and initialize the context for encryption
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if (!ctx) handleErrors();

    // Initialize the encryption operation
    if (1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv))
        handleErrors();

    // Provide the message to be encrypted and obtain the encrypted output
    if (1 != EVP_EncryptUpdate(ctx, ciphertext, &ciphertext_len, (unsigned char*)plaintext, strlen(plaintext)))
        handleErrors();

    // Finalize the encryption
    if (1 != EVP_EncryptFinal_ex(ctx, ciphertext + ciphertext_len, &ciphertext_len))
        handleErrors();

    // Clean up encryption context
    EVP_CIPHER_CTX_free(ctx);

    // Create and initialize the context for decryption
    ctx = EVP_CIPHER_CTX_new();
    if (!ctx) handleErrors();

    // Initialize the decryption operation
    if (1 != EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv))
        handleErrors();

    // Provide the message to be decrypted and obtain the plaintext output
    if (1 != EVP_DecryptUpdate(ctx, decryptedtext, &decryptedtext_len, ciphertext, ciphertext_len))
        handleErrors();

    // Finalize the decryption
    if (1 != EVP_DecryptFinal_ex(ctx, decryptedtext + decryptedtext_len, &decryptedtext_len))
        handleErrors();

    // Null-terminate the decrypted string
    decryptedtext[decryptedtext_len] = '\0';

    // Output the decrypted text
    cout << "Decrypted text is: " << decryptedtext << endl;

    // Clean up decryption context
    EVP_CIPHER_CTX_free(ctx);

    // Clean up OpenSSL
    EVP_cleanup();
    ERR_free_strings();

    return 0;
}