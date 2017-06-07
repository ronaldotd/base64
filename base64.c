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

#include "base64.h"
#include <stddef.h>
#include <string.h>

/*

Data to be encoded by base64 rules must be grouped into 24-bit blocks.
This block is then broken into four 6-bit codes (retrieved from a standard code table).
If the last block is incomplete (less than three 8-bit chars), zeros are padded to the 
less signifcant bits, and '=' is used for a code comprised of only padding bits.

        -------------------------------------------------
        |       CH1     |       CH2     |       CH3     |  --> three char (8-bit) block
        -------------------------------------------------
        |7|6|5|4|3|2|1|0|7|6|5|4|3|2|1|0|7|6|5|4|3|2|1|0|  --> binary representation
        -------------------------------------------------
        |   EN1     |   EN2     |   EN3     |   EN4     |  --> four code (6-bit) block
        -------------------------------------------------

*/

static char _code_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

/* return the index of the code in the code table */
static int _index_get(char code)
{
  /* TODO: linear search in the code table, not good... */
  int i;
  for (i = 0; i < strlen(_code_table); i++)
  {
    if (code == _code_table[i])
      break;
  }
  return i;
}

int base64_encode(const char* data, int data_len, char* encoded)
{
  if (!data)
    return -1;

  /* number of complete three 8-bit char blocks */
  int num_blocks = data_len / 3;
  /* number of 8-bit chars in the eventual last (incomplete) block */
  int data_last_block = data_len % 3;
  /* length of encoded data (each block is encoded into 4 codes */
  int enc_len = num_blocks * 4 + (data_last_block ? 4 : 0);

  if (encoded)
  {
    const char* in_p = data;
    char* out_p = encoded;

    /* perform encoding on each complete block */
    int i;
    for (i = 0; i < num_blocks; i++)
    {
      out_p[0] = _code_table[in_p[0] >> 2];
      out_p[1] = _code_table[((in_p[0] & 0x3) << 4) | ((in_p[1] & 0xf0) >> 4)];
      out_p[2] = _code_table[((in_p[1] & 0xf) << 2) | ((in_p[2] & 0xc0) >> 6)];
      out_p[3] = _code_table[in_p[2] & 0x3f];

      in_p += 3;
      out_p += 4;
    }

    /* last block has only one 8-bit char */
    if (data_last_block == 1)
    {
      out_p[0] = _code_table[in_p[0] >> 2];
      out_p[1] = _code_table[(in_p[0] & 0x3) << 4];
      out_p[2] = '=';
      out_p[3] = '=';
    }
    /* last block has two 8-bit chars */
    else if (data_last_block == 2)
    {
      out_p[0] = _code_table[in_p[0] >> 2];
      out_p[1] = _code_table[((in_p[0] & 0x3) << 4) | ((in_p[1] & 0xf0) >> 4)];
      out_p[2] = _code_table[(in_p[1] & 0xf) << 2];
      out_p[3] = '=';
    }
  }

  return enc_len;
}

int base64_decode(const char* data, int data_len, char* decoded)
{
  if (!data)
    return -1;

  /* number of 6-bit code blocks */
  int num_blocks = data_len / 4;
  /* length of decoded data */
  int dec_len = num_blocks * 3;

  /* do not decode unpadded text */
  if (data_len % 4)
    return -1;

  int i;
  const char* in_p = data;
  char* out_p = decoded;
  for (i = 0; i < num_blocks; i++)
  {
    char code[4] = { 0, 0, 0, 0 };

    int j;
    for (j = 0; j < 4; j++)
    {
      if (in_p[j] != '=')
        code[j] = _index_get(in_p[j]);
      else
        /* padding code, will not be decoded */
        dec_len -= 1;
    }

    if (out_p)
    {
      out_p[0] = (code[0] << 2) | ((code[1] & 0x30) >> 4);
      out_p[1] = ((code[1] & 0xf) << 4) | ((code[2] & 0x3c) >> 2); 
      out_p[2] = ((code[2] & 0x3) << 6) | code[3];
    }

    in_p += 4;
    if (out_p)
      out_p += 3;
  }

  return dec_len;
}
