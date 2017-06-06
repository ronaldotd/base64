#ifndef _BASE64_H_
#define _BASE64_H_

int base64_encode(const char* data, int data_len, char* encoded);
int base64_decode(const char* data, int data_len, char* decoded);

#endif
