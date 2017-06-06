/*
MIT License

Copyright (c) 2017 Ronaldo Duarte

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef _BASE64_H_
#define _BASE64_H_

/**
  @brief Encodes a text buffer using base64 encoding.

  This function has two purposes:
  - calculate the length of the base64 encoded data
  - perform base64 encoding
  The caller may not know beforehand much buffer space to allocate for storing
  the encoded data. In this case, the function may be called with encoded=NULL.
  It always returns the length of the resulting encoded data, and the caller may
  allocate the buffer properly.

  @param data The text buffer to encode.
  @param data_len Length of the text buffer to encode.
  @param encoded Buffer where encoded data will be stored.
  @return Length of the encoded data.
*/
int base64_encode(const char* data, int data_len, char* encoded);

/**
  @brief Decodes base64 encoded data.

  This function has two purposes:
  - calculate the length of the decoded text data
  - perform base64 decoding
  The caller may not know beforehand much buffer space to allocate for storing
  the decoded data. In this case, the function may be called with decoded=NULL.
  It always returns the length of the resulting decoded data, and the caller may
  allocate the buffer properly.

  @param data The base64 encoded data..
  @param data_len Length of the buffer to decode.
  @param decoded Buffer where decoded data will be stored.
  @return Length of the decoded data.
*/
int base64_decode(const char* data, int data_len, char* decoded);

#endif
