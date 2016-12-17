# Simple-C-public-private-key-cipher-and-check
To run: gcc cPrivPubCipher.c -o a.out, ./a.out -CHECK PUB_KEY PRIV_KEY MODULO, to encrypt: ./a.out -CIPHER test.txt KEY, output will be test.txt.CIPHER, to decrypt: ./a.out _CIPHER test.txt.CIPHER MATCHING_KEY, output will be decrypted test.txt.CIPHER.CIPHER, Example: ./a.out test.txt 73, ./a.out test.txt.CIPHER 249, modulo range is 256
