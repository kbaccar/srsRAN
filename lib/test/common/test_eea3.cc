/**
 *
 * \section COPYRIGHT
 *
 * Copyright 2013-2020 Software Radio Systems Limited
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the distribution.
 *
 */

#include <stdio.h>
#include <stdlib.h>

#include "srslte/common/liblte_security.h"
#include "srslte/common/test_common.h"
#include "srslte/srslte.h"

int32 arrcmp(uint8_t const* const a, uint8_t const* const b, uint32 len)
{
  uint32 i = 0;

  for (i = 0; i < len; i++) {
    if (a[i] != b[i]) {
      return a[i] - b[i];
    }
  }
  return 0;
}

/*
 * Tests
 *
 * Document Reference: Specification of the 3GPP Confidentiality and Integrity Algorithms 128-EEA3 & 128-EIA3: Document
 * 3: Implementor’s Test Data https://www.gsma.com/aboutus/wp-content/uploads/2014/12/eea3eia3testdatav11.pdf
 *
 */

int test_set_1()
{
  LIBLTE_ERROR_ENUM err_lte = LIBLTE_ERROR_INVALID_INPUTS;
  int32             err_cmp = 0;

  uint8_t  key[]     = {0x17, 0x3d, 0x14, 0xba, 0x50, 0x03, 0x73, 0x1d, 0x7a, 0x60, 0x04, 0x94, 0x70, 0xf0, 0x0a, 0x29};
  uint32_t count     = 0x66035492;
  uint8_t  bearer    = 0xf;
  uint8_t  direction = 0;
  uint32_t len_bits  = 193;
  uint32_t len_bytes = (len_bits + 7) / 8;

  uint8_t msg[] = {0x6c, 0xf6, 0x53, 0x40, 0x73, 0x55, 0x52, 0xab, 0x0c, 0x97, 0x52, 0xfa, 0x6f, 0x90,
                   0x25, 0xfe, 0x0b, 0xd6, 0x75, 0xd9, 0x00, 0x58, 0x75, 0xb2, 0x00, 0x00, 0x00, 0x00};

  uint8_t ct[] = {0xa6, 0xc8, 0x5f, 0xc6, 0x6a, 0xfb, 0x85, 0x33, 0xaa, 0xfc, 0x25, 0x18, 0xdf, 0xe7,
                  0x84, 0x94, 0x0e, 0xe1, 0xe4, 0xb0, 0x30, 0x23, 0x8c, 0xc8, 0x00, 0x00, 0x00, 0x00};

  uint8_t* out = (uint8_t*)calloc(len_bytes, sizeof(uint8_t));

  // encryption
  err_lte = liblte_security_encryption_eea3(key, count, bearer, direction, msg, len_bits, out);
  TESTASSERT(err_lte == LIBLTE_SUCCESS);

  // compare cipher text
  err_cmp = arrcmp(ct, out, len_bytes);

  if (err_cmp == 0) {
    printf("Test Set 1 Encryption: Success\n");
  } else {
    printf("Test Set 1 Encryption: Failed\n");
  }

  TESTASSERT(err_cmp == 0);

  // decryption
  err_lte = liblte_security_decryption_eea3(key, count, bearer, direction, ct, len_bits, out);
  TESTASSERT(err_lte == LIBLTE_SUCCESS);

  // compare cipher text
  err_cmp = arrcmp(msg, out, len_bytes);
  TESTASSERT(err_cmp == 0);

  if (err_cmp == 0) {
    printf("Test Set 1 Decryption: Success\n");
  } else {
    printf("Test Set 1 Decryption: Failed\n");
  }

  free(out);
  return SRSLTE_SUCCESS;
}

int test_set_2()
{
  LIBLTE_ERROR_ENUM err_lte = LIBLTE_ERROR_INVALID_INPUTS;
  int32             err_cmp = 0;

  uint8_t  key[]     = {0xe5, 0xbd, 0x3e, 0xa0, 0xeb, 0x55, 0xad, 0xe8, 0x66, 0xc6, 0xac, 0x58, 0xbd, 0x54, 0x30, 0x2a};
  uint32_t count     = 0x56823;
  uint8_t  bearer    = 0x18;
  uint8_t  direction = 1;
  uint32_t len_bits  = 800;
  uint32_t len_bytes = (len_bits + 7) / 8;

  uint8_t msg[] = {0x14, 0xa8, 0xef, 0x69, 0x3d, 0x67, 0x85, 0x07, 0xbb, 0xe7, 0x27, 0x0a, 0x7f, 0x67, 0xff, 0x50, 0x06,
                   0xc3, 0x52, 0x5b, 0x98, 0x07, 0xe4, 0x67, 0xc4, 0xe5, 0x60, 0x00, 0xba, 0x33, 0x8f, 0x5d, 0x42, 0x95,
                   0x59, 0x03, 0x67, 0x51, 0x82, 0x22, 0x46, 0xc8, 0x0d, 0x3b, 0x38, 0xf0, 0x7f, 0x4b, 0xe2, 0xd8, 0xff,
                   0x58, 0x05, 0xf5, 0x13, 0x22, 0x29, 0xbd, 0xe9, 0x3b, 0xbb, 0xdc, 0xaf, 0x38, 0x2b, 0xf1, 0xee, 0x97,
                   0x2f, 0xbf, 0x99, 0x77, 0xba, 0xda, 0x89, 0x45, 0x84, 0x7a, 0x2a, 0x6c, 0x9a, 0xd3, 0x4a, 0x66, 0x75,
                   0x54, 0xe0, 0x4d, 0x1f, 0x7f, 0xa2, 0xc3, 0x32, 0x41, 0xbd, 0x8f, 0x01, 0xba, 0x22, 0x0d};

  uint8_t ct[] = {0x13, 0x1d, 0x43, 0xe0, 0xde, 0xa1, 0xbe, 0x5c, 0x5a, 0x1b, 0xfd, 0x97, 0x1d, 0x85, 0x2c, 0xbf, 0x71,
                  0x2d, 0x7b, 0x4f, 0x57, 0x96, 0x1f, 0xea, 0x32, 0x08, 0xaf, 0xa8, 0xbc, 0xa4, 0x33, 0xf4, 0x56, 0xad,
                  0x09, 0xc7, 0x41, 0x7e, 0x58, 0xbc, 0x69, 0xcf, 0x88, 0x66, 0xd1, 0x35, 0x3f, 0x74, 0x86, 0x5e, 0x80,
                  0x78, 0x1d, 0x20, 0x2d, 0xfb, 0x3e, 0xcf, 0xf7, 0xfc, 0xbc, 0x3b, 0x19, 0x0f, 0xe8, 0x2a, 0x20, 0x4e,
                  0xd0, 0xe3, 0x50, 0xfc, 0x0f, 0x6f, 0x26, 0x13, 0xb2, 0xf2, 0xbc, 0xa6, 0xdf, 0x5a, 0x47, 0x3a, 0x57,
                  0xa4, 0xa0, 0x0d, 0x98, 0x5e, 0xba, 0xd8, 0x80, 0xd6, 0xf2, 0x38, 0x64, 0xa0, 0x7b, 0x01};

  uint8_t* out = (uint8_t*)calloc(len_bytes, sizeof(uint8_t));

  // encryption
  err_lte = liblte_security_encryption_eea3(key, count, bearer, direction, msg, len_bits, out);
  TESTASSERT(err_lte == LIBLTE_SUCCESS);
  // compare cipher text
  err_cmp = arrcmp(ct, out, len_bytes);

  if (err_cmp == 0) {
    printf("Test Set 2 Encryption: Success\n");
  } else {
    printf("Test Set 2 Encryption: Failed\n");
  }

  TESTASSERT(err_cmp == 0);

  // decryption
  err_lte = liblte_security_decryption_eea3(key, count, bearer, direction, ct, len_bits, out);
  TESTASSERT(err_lte == LIBLTE_SUCCESS);

  // compare cipher text
  err_cmp = arrcmp(msg, out, len_bytes);
  TESTASSERT(err_cmp == 0);

  if (err_cmp == 0) {
    printf("Test Set 2 Decryption: Success\n");
  } else {
    printf("Test Set 2 Decryption: Failed\n");
  }

  free(out);
  return SRSLTE_SUCCESS;
}

int test_set_3()
{
  LIBLTE_ERROR_ENUM err_lte = LIBLTE_ERROR_INVALID_INPUTS;
  int32             err_cmp = 0;

  uint8_t  key[]     = {0xd4, 0x55, 0x2a, 0x8f, 0xd6, 0xe6, 0x1c, 0xc8, 0x1a, 0x20, 0x09, 0x14, 0x1a, 0x29, 0xc1, 0x0b};
  uint32_t count     = 0x76452ec1;
  uint8_t  bearer    = 0x2;
  uint8_t  direction = 0x1;
  uint32_t len_bits  = 1570;
  uint32_t len_bytes = (len_bits + 7) / 8;

  uint8_t msg[] = {0x38, 0xf0, 0x7f, 0x4b, 0xe2, 0xd8, 0xff, 0x58, 0x05, 0xf5, 0x13, 0x22, 0x29, 0xbd, 0xe9, 0x3b, 0xbb,
                   0xdc, 0xaf, 0x38, 0x2b, 0xf1, 0xee, 0x97, 0x2f, 0xbf, 0x99, 0x77, 0xba, 0xda, 0x89, 0x45, 0x84, 0x7a,
                   0x2a, 0x6c, 0x9a, 0xd3, 0x4a, 0x66, 0x75, 0x54, 0xe0, 0x4d, 0x1f, 0x7f, 0xa2, 0xc3, 0x32, 0x41, 0xbd,
                   0x8f, 0x01, 0xba, 0x22, 0x0d, 0x3c, 0xa4, 0xec, 0x41, 0xe0, 0x74, 0x59, 0x5f, 0x54, 0xae, 0x2b, 0x45,
                   0x4f, 0xd9, 0x71, 0x43, 0x20, 0x43, 0x60, 0x19, 0x65, 0xcc, 0xa8, 0x5c, 0x24, 0x17, 0xed, 0x6c, 0xbe,
                   0xc3, 0xba, 0xda, 0x84, 0xfc, 0x8a, 0x57, 0x9a, 0xea, 0x78, 0x37, 0xb0, 0x27, 0x11, 0x77, 0x24, 0x2a,
                   0x64, 0xdc, 0x0a, 0x9d, 0xe7, 0x1a, 0x8e, 0xde, 0xe8, 0x6c, 0xa3, 0xd4, 0x7d, 0x03, 0x3d, 0x6b, 0xf5,
                   0x39, 0x80, 0x4e, 0xca, 0x86, 0xc5, 0x84, 0xa9, 0x05, 0x2d, 0xe4, 0x6a, 0xd3, 0xfc, 0xed, 0x65, 0x54,
                   0x3b, 0xd9, 0x02, 0x07, 0x37, 0x2b, 0x27, 0xaf, 0xb7, 0x92, 0x34, 0xf5, 0xff, 0x43, 0xea, 0x87, 0x08,
                   0x20, 0xe2, 0xc2, 0xb7, 0x8a, 0x8a, 0xae, 0x61, 0xcc, 0xe5, 0x2a, 0x05, 0x15, 0xe3, 0x48, 0xd1, 0x96,
                   0x66, 0x4a, 0x34, 0x56, 0xb1, 0x82, 0xa0, 0x7c, 0x40, 0x6e, 0x4a, 0x20, 0x79, 0x12, 0x71, 0xcf, 0xed,
                   0xa1, 0x65, 0xd5, 0x35, 0xec, 0x5e, 0xa2, 0xd4, 0xdf, 0x40, 0x00, 0x00, 0x00};

  uint8_t ct[] = {0x83, 0x83, 0xb0, 0x22, 0x9f, 0xcc, 0x0b, 0x9d, 0x22, 0x95, 0xec, 0x41, 0xc9, 0x77, 0xe9, 0xc2, 0xbb,
                  0x72, 0xe2, 0x20, 0x37, 0x81, 0x41, 0xf9, 0xc8, 0x31, 0x8f, 0x3a, 0x27, 0x0d, 0xfb, 0xcd, 0xee, 0x64,
                  0x11, 0xc2, 0xb3, 0x04, 0x4f, 0x17, 0x6d, 0xc6, 0xe0, 0x0f, 0x89, 0x60, 0xf9, 0x7a, 0xfa, 0xcd, 0x13,
                  0x1a, 0xd6, 0xa3, 0xb4, 0x9b, 0x16, 0xb7, 0xba, 0xbc, 0xf2, 0xa5, 0x09, 0xeb, 0xb1, 0x6a, 0x75, 0xdc,
                  0xab, 0x14, 0xff, 0x27, 0x5d, 0xbe, 0xee, 0xa1, 0xa2, 0xb1, 0x55, 0xf9, 0xd5, 0x2c, 0x26, 0x45, 0x2d,
                  0x01, 0x87, 0xc3, 0x10, 0xa4, 0xee, 0x55, 0xbe, 0xaa, 0x78, 0xab, 0x40, 0x24, 0x61, 0x5b, 0xa9, 0xf5,
                  0xd5, 0xad, 0xc7, 0x72, 0x8f, 0x73, 0x56, 0x06, 0x71, 0xf0, 0x13, 0xe5, 0xe5, 0x50, 0x08, 0x5d, 0x32,
                  0x91, 0xdf, 0x7d, 0x5f, 0xec, 0xed, 0xde, 0xd5, 0x59, 0x64, 0x1b, 0x6c, 0x2f, 0x58, 0x52, 0x33, 0xbc,
                  0x71, 0xe9, 0x60, 0x2b, 0xd2, 0x30, 0x58, 0x55, 0xbb, 0xd2, 0x5f, 0xfa, 0x7f, 0x17, 0xec, 0xbc, 0x04,
                  0x2d, 0xaa, 0xe3, 0x8c, 0x1f, 0x57, 0xad, 0x8e, 0x8e, 0xbd, 0x37, 0x34, 0x6f, 0x71, 0xbe, 0xfd, 0xbb,
                  0x74, 0x32, 0xe0, 0xe0, 0xbb, 0x2c, 0xfc, 0x09, 0xbc, 0xd9, 0x65, 0x70, 0xcb, 0x0c, 0x0c, 0x39, 0xdf,
                  0x5e, 0x29, 0x29, 0x4e, 0x82, 0x70, 0x3a, 0x63, 0x7f, 0x80, 0x00, 0x00, 0x00};

  uint8_t* out = (uint8_t*)calloc(len_bytes, sizeof(uint8_t));

  // encryption
  err_lte = liblte_security_encryption_eea3(key, count, bearer, direction, msg, len_bits, out);
  TESTASSERT(err_lte == LIBLTE_SUCCESS);
  int i;
  // compare cipher text
  err_cmp = arrcmp(ct, out, len_bytes);

  if (err_cmp == 0) {
    printf("Test Set 3 Encryption: Success\n");
  } else {
    printf("Test Set 3 Encryption: Failed\n");
  }

  TESTASSERT(err_cmp == 0);

  // decryption
  err_lte = liblte_security_decryption_eea3(key, count, bearer, direction, ct, len_bits, out);
  TESTASSERT(err_lte == LIBLTE_SUCCESS);

  // compare cipher text
  err_cmp = arrcmp(msg, out, len_bytes);
  TESTASSERT(err_cmp == 0);

  if (err_cmp == 0) {
    printf("Test Set 3 Decryption: Success\n");
  } else {
    printf("Test Set 3 Decryption: Failed\n");
  }

  free(out);
  return SRSLTE_SUCCESS;
}

int test_set_4()
{
  LIBLTE_ERROR_ENUM err_lte = LIBLTE_ERROR_INVALID_INPUTS;
  int32             err_cmp = 0;

  uint8_t  key[]     = {0xdb, 0x84, 0xb4, 0xfb, 0xcc, 0xda, 0x56, 0x3b, 0x66, 0x22, 0x7b, 0xfe, 0x45, 0x6f, 0x0f, 0x77};
  uint32_t count     = 0xe4850fe1;
  uint8_t  bearer    = 0x10;
  uint8_t  direction = 0x1;
  uint32_t len_bits  = 2798;
  uint32_t len_bytes = (len_bits + 7) / 8;

  uint8_t msg[] = {
      0xe5, 0x39, 0xf3, 0xb8, 0x97, 0x32, 0x40, 0xda, 0x03, 0xf2, 0xb8, 0xaa, 0x05, 0xee, 0x0a, 0x00, 0xdb, 0xaf, 0xc0,
      0xe1, 0x82, 0x05, 0x5d, 0xfe, 0x3d, 0x73, 0x83, 0xd9, 0x2c, 0xef, 0x40, 0xe9, 0x29, 0x28, 0x60, 0x5d, 0x52, 0xd0,
      0x5f, 0x4f, 0x90, 0x18, 0xa1, 0xf1, 0x89, 0xae, 0x39, 0x97, 0xce, 0x19, 0x15, 0x5f, 0xb1, 0x22, 0x1d, 0xb8, 0xbb,
      0x09, 0x51, 0xa8, 0x53, 0xad, 0x85, 0x2c, 0xe1, 0x6c, 0xff, 0x07, 0x38, 0x2c, 0x93, 0xa1, 0x57, 0xde, 0x00, 0xdd,
      0xb1, 0x25, 0xc7, 0x53, 0x9f, 0xd8, 0x50, 0x45, 0xe4, 0xee, 0x07, 0xe0, 0xc4, 0x3f, 0x9e, 0x9d, 0x6f, 0x41, 0x4f,
      0xc4, 0xd1, 0xc6, 0x29, 0x17, 0x81, 0x3f, 0x74, 0xc0, 0x0f, 0xc8, 0x3f, 0x3e, 0x2e, 0xd7, 0xc4, 0x5b, 0xa5, 0x83,
      0x52, 0x64, 0xb4, 0x3e, 0x0b, 0x20, 0xaf, 0xda, 0x6b, 0x30, 0x53, 0xbf, 0xb6, 0x42, 0x3b, 0x7f, 0xce, 0x25, 0x47,
      0x9f, 0xf5, 0xf1, 0x39, 0xdd, 0x9b, 0x5b, 0x99, 0x55, 0x58, 0xe2, 0xa5, 0x6b, 0xe1, 0x8d, 0xd5, 0x81, 0xcd, 0x01,
      0x7c, 0x73, 0x5e, 0x6f, 0x0d, 0x0d, 0x97, 0xc4, 0xdd, 0xc1, 0xd1, 0xda, 0x70, 0xc6, 0xdb, 0x4a, 0x12, 0xcc, 0x92,
      0x77, 0x8e, 0x2f, 0xbb, 0xd6, 0xf3, 0xba, 0x52, 0xaf, 0x91, 0xc9, 0xc6, 0xb6, 0x4e, 0x8d, 0xa4, 0xf7, 0xa2, 0xc2,
      0x66, 0xd0, 0x2d, 0x00, 0x17, 0x53, 0xdf, 0x08, 0x96, 0x03, 0x93, 0xc5, 0xd5, 0x68, 0x88, 0xbf, 0x49, 0xeb, 0x5c,
      0x16, 0xd9, 0xa8, 0x04, 0x27, 0xa4, 0x16, 0xbc, 0xb5, 0x97, 0xdf, 0x5b, 0xfe, 0x6f, 0x13, 0x89, 0x0a, 0x07, 0xee,
      0x13, 0x40, 0xe6, 0x47, 0x6b, 0x0d, 0x9a, 0xa8, 0xf8, 0x22, 0xab, 0x0f, 0xd1, 0xab, 0x0d, 0x20, 0x4f, 0x40, 0xb7,
      0xce, 0x6f, 0x2e, 0x13, 0x6e, 0xb6, 0x74, 0x85, 0xe5, 0x07, 0x80, 0x4d, 0x50, 0x45, 0x88, 0xad, 0x37, 0xff, 0xd8,
      0x16, 0x56, 0x8b, 0x2d, 0xc4, 0x03, 0x11, 0xdf, 0xb6, 0x54, 0xcd, 0xea, 0xd4, 0x7e, 0x23, 0x85, 0xc3, 0x43, 0x62,
      0x03, 0xdd, 0x83, 0x6f, 0x9c, 0x64, 0xd9, 0x74, 0x62, 0xad, 0x5d, 0xfa, 0x63, 0xb5, 0xcf, 0xe0, 0x8a, 0xcb, 0x95,
      0x32, 0x86, 0x6f, 0x5c, 0xa7, 0x87, 0x56, 0x6f, 0xca, 0x93, 0xe6, 0xb1, 0x69, 0x3e, 0xe1, 0x5c, 0xf6, 0xf7, 0xa2,
      0xd6, 0x89, 0xd9, 0x74, 0x17, 0x98, 0xdc, 0x1c, 0x23, 0x8e, 0x1b, 0xe6, 0x50, 0x73, 0x3b, 0x18, 0xfb, 0x34, 0xff,
      0x88, 0x0e, 0x16, 0xbb, 0xd2, 0x1b, 0x47, 0xac, 0x00, 0x00};

  uint8_t ct[] = {
      0x4b, 0xbf, 0xa9, 0x1b, 0xa2, 0x5d, 0x47, 0xdb, 0x9a, 0x9f, 0x19, 0x0d, 0x96, 0x2a, 0x19, 0xab, 0x32, 0x39, 0x26,
      0xb3, 0x51, 0xfb, 0xd3, 0x9e, 0x35, 0x1e, 0x05, 0xda, 0x8b, 0x89, 0x25, 0xe3, 0x0b, 0x1c, 0xce, 0x0d, 0x12, 0x21,
      0x10, 0x10, 0x95, 0x81, 0x5c, 0xc7, 0xcb, 0x63, 0x19, 0x50, 0x9e, 0xc0, 0xd6, 0x79, 0x40, 0x49, 0x19, 0x87, 0xe1,
      0x3f, 0x0a, 0xff, 0xac, 0x33, 0x2a, 0xa6, 0xaa, 0x64, 0x62, 0x6d, 0x3e, 0x9a, 0x19, 0x17, 0x51, 0x9e, 0x0b, 0x97,
      0xb6, 0x55, 0xc6, 0xa1, 0x65, 0xe4, 0x4c, 0xa9, 0xfe, 0xac, 0x07, 0x90, 0xd2, 0xa3, 0x21, 0xad, 0x3d, 0x86, 0xb7,
      0x9c, 0x51, 0x38, 0x73, 0x9f, 0xa3, 0x8d, 0x88, 0x7e, 0xc7, 0xde, 0xf4, 0x49, 0xce, 0x8a, 0xbd, 0xd3, 0xe7, 0xf8,
      0xdc, 0x4c, 0xa9, 0xe7, 0xb7, 0x33, 0x14, 0xad, 0x31, 0x0f, 0x90, 0x25, 0xe6, 0x19, 0x46, 0xb3, 0xa5, 0x6d, 0xc6,
      0x49, 0xec, 0x0d, 0xa0, 0xd6, 0x39, 0x43, 0xdf, 0xf5, 0x92, 0xcf, 0x96, 0x2a, 0x7e, 0xfb, 0x2c, 0x85, 0x24, 0xe3,
      0x5a, 0x2a, 0x6e, 0x78, 0x79, 0xd6, 0x26, 0x04, 0xef, 0x26, 0x86, 0x95, 0xfa, 0x40, 0x03, 0x02, 0x7e, 0x22, 0xe6,
      0x08, 0x30, 0x77, 0x52, 0x20, 0x64, 0xbd, 0x4a, 0x5b, 0x90, 0x6b, 0x5f, 0x53, 0x12, 0x74, 0xf2, 0x35, 0xed, 0x50,
      0x6c, 0xff, 0x01, 0x54, 0xc7, 0x54, 0x92, 0x8a, 0x0c, 0xe5, 0x47, 0x6f, 0x2c, 0xb1, 0x02, 0x0a, 0x12, 0x22, 0xd3,
      0x2c, 0x14, 0x55, 0xec, 0xae, 0xf1, 0xe3, 0x68, 0xfb, 0x34, 0x4d, 0x17, 0x35, 0xbf, 0xbe, 0xde, 0xb7, 0x1d, 0x0a,
      0x33, 0xa2, 0xa5, 0x4b, 0x1d, 0xa5, 0xa2, 0x94, 0xe6, 0x79, 0x14, 0x4d, 0xdf, 0x11, 0xeb, 0x1a, 0x3d, 0xe8, 0xcf,
      0x0c, 0xc0, 0x61, 0x91, 0x79, 0x74, 0xf3, 0x5c, 0x1d, 0x9c, 0xa0, 0xac, 0x81, 0x80, 0x7f, 0x8f, 0xcc, 0xe6, 0x19,
      0x9a, 0x6c, 0x77, 0x12, 0xda, 0x86, 0x50, 0x21, 0xb0, 0x4c, 0xe0, 0x43, 0x95, 0x16, 0xf1, 0xa5, 0x26, 0xcc, 0xda,
      0x9f, 0xd9, 0xab, 0xbd, 0x53, 0xc3, 0xa6, 0x84, 0xf9, 0xae, 0x1e, 0x7e, 0xe6, 0xb1, 0x1d, 0xa1, 0x38, 0xea, 0x82,
      0x6c, 0x55, 0x16, 0xb5, 0xaa, 0xdf, 0x1a, 0xbb, 0xe3, 0x6f, 0xa7, 0xff, 0xf9, 0x2e, 0x3a, 0x11, 0x76, 0x06, 0x4e,
      0x8d, 0x95, 0xf2, 0xe4, 0x88, 0x2b, 0x55, 0x00, 0xb9, 0x32, 0x28, 0xb2, 0x19, 0x4a, 0x47, 0x5c, 0x1a, 0x27, 0xf6,
      0x3f, 0x9f, 0xfd, 0x26, 0x49, 0x89, 0xa1, 0xbc, 0x00, 0x00};

  uint8_t* out = (uint8_t*)calloc(len_bytes, sizeof(uint8_t));

  // encryption
  err_lte = liblte_security_encryption_eea3(key, count, bearer, direction, msg, len_bits, out);
  TESTASSERT(err_lte == LIBLTE_SUCCESS);
  int i;
  // compare cipher text
  err_cmp = arrcmp(ct, out, len_bytes);

  if (err_cmp == 0) {
    printf("Test Set 4 Encryption: Success\n");
  } else {
    printf("Test Set 4 Encryption: Failed\n");
  }

  TESTASSERT(err_cmp == 0);

  // decryption
  err_lte = liblte_security_decryption_eea3(key, count, bearer, direction, ct, len_bits, out);
  TESTASSERT(err_lte == LIBLTE_SUCCESS);

  // compare cipher text
  err_cmp = arrcmp(msg, out, len_bytes);
  TESTASSERT(err_cmp == 0);

  if (err_cmp == 0) {
    printf("Test Set 4 Decryption: Success\n");
  } else {
    printf("Test Set 4 Decryption: Failed\n");
  }

  free(out);
  return SRSLTE_SUCCESS;
}

int test_set_5()
{
  LIBLTE_ERROR_ENUM err_lte = LIBLTE_ERROR_INVALID_INPUTS;
  int32             err_cmp = 0;

  uint8_t  key[]     = {0xe1, 0x3f, 0xed, 0x21, 0xb4, 0x6e, 0x4e, 0x7e, 0xc3, 0x12, 0x53, 0xb2, 0xbb, 0x17, 0xb3, 0xe0};
  uint32_t count     = 0x2738cdaa;
  uint8_t  bearer    = 0x1a;
  uint8_t  direction = 0x0;
  uint32_t len_bits  = 4019;
  uint32_t len_bytes = (len_bits + 7) / 8;

  uint8_t msg[] = {
      0x8d, 0x74, 0xe2, 0x0d, 0x54, 0x89, 0x4e, 0x06, 0xd3, 0xcb, 0x13, 0xcb, 0x39, 0x33, 0x06, 0x5e, 0x86, 0x74, 0xbe,
      0x62, 0xad, 0xb1, 0xc7, 0x2b, 0x3a, 0x64, 0x69, 0x65, 0xab, 0x63, 0xcb, 0x7b, 0x78, 0x54, 0xdf, 0xdc, 0x27, 0xe8,
      0x49, 0x29, 0xf4, 0x9c, 0x64, 0xb8, 0x72, 0xa4, 0x90, 0xb1, 0x3f, 0x95, 0x7b, 0x64, 0x82, 0x7e, 0x71, 0xf4, 0x1f,
      0xbd, 0x42, 0x69, 0xa4, 0x2c, 0x97, 0xf8, 0x24, 0x53, 0x70, 0x27, 0xf8, 0x6e, 0x9f, 0x4a, 0xd8, 0x2d, 0x1d, 0xf4,
      0x51, 0x69, 0x0f, 0xdd, 0x98, 0xb6, 0xd0, 0x3f, 0x3a, 0x0e, 0xbe, 0x3a, 0x31, 0x2d, 0x6b, 0x84, 0x0b, 0xa5, 0xa1,
      0x82, 0x0b, 0x2a, 0x2c, 0x97, 0x09, 0xc0, 0x90, 0xd2, 0x45, 0xed, 0x26, 0x7c, 0xf8, 0x45, 0xae, 0x41, 0xfa, 0x97,
      0x5d, 0x33, 0x33, 0xac, 0x30, 0x09, 0xfd, 0x40, 0xeb, 0xa9, 0xeb, 0x5b, 0x88, 0x57, 0x14, 0xb7, 0x68, 0xb6, 0x97,
      0x13, 0x8b, 0xaf, 0x21, 0x38, 0x0e, 0xca, 0x49, 0xf6, 0x44, 0xd4, 0x86, 0x89, 0xe4, 0x21, 0x57, 0x60, 0xb9, 0x06,
      0x73, 0x9f, 0x0d, 0x2b, 0x3f, 0x09, 0x11, 0x33, 0xca, 0x15, 0xd9, 0x81, 0xcb, 0xe4, 0x01, 0xba, 0xf7, 0x2d, 0x05,
      0xac, 0xe0, 0x5c, 0xcc, 0xb2, 0xd2, 0x97, 0xf4, 0xef, 0x6a, 0x5f, 0x58, 0xd9, 0x12, 0x46, 0xcf, 0xa7, 0x72, 0x15,
      0xb8, 0x92, 0xab, 0x44, 0x1d, 0x52, 0x78, 0x45, 0x27, 0x95, 0xcc, 0xb7, 0xf5, 0xd7, 0x90, 0x57, 0xa1, 0xc4, 0xf7,
      0x7f, 0x80, 0xd4, 0x6d, 0xb2, 0x03, 0x3c, 0xb7, 0x9b, 0xed, 0xf8, 0xe6, 0x05, 0x51, 0xce, 0x10, 0xc6, 0x67, 0xf6,
      0x2a, 0x97, 0xab, 0xaf, 0xab, 0xbc, 0xd6, 0x77, 0x20, 0x18, 0xdf, 0x96, 0xa2, 0x82, 0xea, 0x73, 0x7c, 0xe2, 0xcb,
      0x33, 0x12, 0x11, 0xf6, 0x0d, 0x53, 0x54, 0xce, 0x78, 0xf9, 0x91, 0x8d, 0x9c, 0x20, 0x6c, 0xa0, 0x42, 0xc9, 0xb6,
      0x23, 0x87, 0xdd, 0x70, 0x96, 0x04, 0xa5, 0x0a, 0xf1, 0x6d, 0x8d, 0x35, 0xa8, 0x90, 0x6b, 0xe4, 0x84, 0xcf, 0x2e,
      0x74, 0xa9, 0x28, 0x99, 0x40, 0x36, 0x43, 0x53, 0x24, 0x9b, 0x27, 0xb4, 0xc9, 0xae, 0x29, 0xed, 0xdf, 0xc7, 0xda,
      0x64, 0x18, 0x79, 0x1a, 0x4e, 0x7b, 0xaa, 0x06, 0x60, 0xfa, 0x64, 0x51, 0x1f, 0x2d, 0x68, 0x5c, 0xc3, 0xa5, 0xff,
      0x70, 0xe0, 0xd2, 0xb7, 0x42, 0x92, 0xe3, 0xb8, 0xa0, 0xcd, 0x6b, 0x04, 0xb1, 0xc7, 0x90, 0xb8, 0xea, 0xd2, 0x70,
      0x37, 0x08, 0x54, 0x0d, 0xea, 0x2f, 0xc0, 0x9c, 0x3d, 0xa7, 0x70, 0xf6, 0x54, 0x49, 0xe8, 0x4d, 0x81, 0x7a, 0x4f,
      0x55, 0x10, 0x55, 0xe1, 0x9a, 0xb8, 0x50, 0x18, 0xa0, 0x02, 0x8b, 0x71, 0xa1, 0x44, 0xd9, 0x67, 0x91, 0xe9, 0xa3,
      0x57, 0x79, 0x33, 0x50, 0x4e, 0xee, 0x00, 0x60, 0x34, 0x0c, 0x69, 0xd2, 0x74, 0xe1, 0xbf, 0x9d, 0x80, 0x5d, 0xcb,
      0xcc, 0x1a, 0x6f, 0xaa, 0x97, 0x68, 0x00, 0xb6, 0xff, 0x2b, 0x67, 0x1d, 0xc4, 0x63, 0x65, 0x2f, 0xa8, 0xa3, 0x3e,
      0xe5, 0x09, 0x74, 0xc1, 0xc2, 0x1b, 0xe0, 0x1e, 0xab, 0xb2, 0x16, 0x74, 0x30, 0x26, 0x9d, 0x72, 0xee, 0x51, 0x1c,
      0x9d, 0xde, 0x30, 0x79, 0x7c, 0x9a, 0x25, 0xd8, 0x6c, 0xe7, 0x4f, 0x5b, 0x96, 0x1b, 0xe5, 0xfd, 0xfb, 0x68, 0x07,
      0x81, 0x40, 0x39, 0xe7, 0x13, 0x76, 0x36, 0xbd, 0x1d, 0x7f, 0xa9, 0xe0, 0x9e, 0xfd, 0x20, 0x07, 0x50, 0x59, 0x06,
      0xa5, 0xac, 0x45, 0xdf, 0xde, 0xed, 0x77, 0x57, 0xbb, 0xee, 0x74, 0x57, 0x49, 0xc2, 0x96, 0x33, 0x35, 0x0b, 0xee,
      0x0e, 0xa6, 0xf4, 0x09, 0xdf, 0x45, 0x80, 0x16, 0x00, 0x00};

  uint8_t ct[] = {
      0x94, 0xea, 0xa4, 0xaa, 0x30, 0xa5, 0x71, 0x37, 0xdd, 0xf0, 0x9b, 0x97, 0xb2, 0x56, 0x18, 0xa2, 0x0a, 0x13, 0xe2,
      0xf1, 0x0f, 0xa5, 0xbf, 0x81, 0x61, 0xa8, 0x79, 0xcc, 0x2a, 0xe7, 0x97, 0xa6, 0xb4, 0xcf, 0x2d, 0x9d, 0xf3, 0x1d,
      0xeb, 0xb9, 0x90, 0x5c, 0xcf, 0xec, 0x97, 0xde, 0x60, 0x5d, 0x21, 0xc6, 0x1a, 0xb8, 0x53, 0x1b, 0x7f, 0x3c, 0x9d,
      0xa5, 0xf0, 0x39, 0x31, 0xf8, 0xa0, 0x64, 0x2d, 0xe4, 0x82, 0x11, 0xf5, 0xf5, 0x2f, 0xfe, 0xa1, 0x0f, 0x39, 0x2a,
      0x04, 0x76, 0x69, 0x98, 0x5d, 0xa4, 0x54, 0xa2, 0x8f, 0x08, 0x09, 0x61, 0xa6, 0xc2, 0xb6, 0x2d, 0xaa, 0x17, 0xf3,
      0x3c, 0xd6, 0x0a, 0x49, 0x71, 0xf4, 0x8d, 0x2d, 0x90, 0x93, 0x94, 0xa5, 0x5f, 0x48, 0x11, 0x7a, 0xce, 0x43, 0xd7,
      0x08, 0xe6, 0xb7, 0x7d, 0x3d, 0xc4, 0x6d, 0x8b, 0xc0, 0x17, 0xd4, 0xd1, 0xab, 0xb7, 0x7b, 0x74, 0x28, 0xc0, 0x42,
      0xb0, 0x6f, 0x2f, 0x99, 0xd8, 0xd0, 0x7c, 0x98, 0x79, 0xd9, 0x96, 0x00, 0x12, 0x7a, 0x31, 0x98, 0x5f, 0x10, 0x99,
      0xbb, 0xd7, 0xd6, 0xc1, 0x51, 0x9e, 0xde, 0x8f, 0x5e, 0xeb, 0x4a, 0x61, 0x0b, 0x34, 0x9a, 0xc0, 0x1e, 0xa2, 0x35,
      0x06, 0x91, 0x75, 0x6b, 0xd1, 0x05, 0xc9, 0x74, 0xa5, 0x3e, 0xdd, 0xb3, 0x5d, 0x1d, 0x41, 0x00, 0xb0, 0x12, 0xe5,
      0x22, 0xab, 0x41, 0xf4, 0xc5, 0xf2, 0xfd, 0xe7, 0x6b, 0x59, 0xcb, 0x8b, 0x96, 0xd8, 0x85, 0xcf, 0xe4, 0x08, 0x0d,
      0x13, 0x28, 0xa0, 0xd6, 0x36, 0xcc, 0x0e, 0xdc, 0x05, 0x80, 0x0b, 0x76, 0xac, 0xca, 0x8f, 0xef, 0x67, 0x20, 0x84,
      0xd1, 0xf5, 0x2a, 0x8b, 0xbd, 0x8e, 0x09, 0x93, 0x32, 0x09, 0x92, 0xc7, 0xff, 0xba, 0xe1, 0x7c, 0x40, 0x84, 0x41,
      0xe0, 0xee, 0x88, 0x3f, 0xc8, 0xa8, 0xb0, 0x5e, 0x22, 0xf5, 0xff, 0x7f, 0x8d, 0x1b, 0x48, 0xc7, 0x4c, 0x46, 0x8c,
      0x46, 0x7a, 0x02, 0x8f, 0x09, 0xfd, 0x7c, 0xe9, 0x11, 0x09, 0xa5, 0x70, 0xa2, 0xd5, 0xc4, 0xd5, 0xf4, 0xfa, 0x18,
      0xc5, 0xdd, 0x3e, 0x45, 0x62, 0xaf, 0xe2, 0x4e, 0xf7, 0x71, 0x90, 0x1f, 0x59, 0xaf, 0x64, 0x58, 0x98, 0xac, 0xef,
      0x08, 0x8a, 0xba, 0xe0, 0x7e, 0x92, 0xd5, 0x2e, 0xb2, 0xde, 0x55, 0x04, 0x5b, 0xb1, 0xb7, 0xc4, 0x16, 0x4e, 0xf2,
      0xd7, 0xa6, 0xca, 0xc1, 0x5e, 0xeb, 0x92, 0x6d, 0x7e, 0xa2, 0xf0, 0x8b, 0x66, 0xe1, 0xf7, 0x59, 0xf3, 0xae, 0xe4,
      0x46, 0x14, 0x72, 0x5a, 0xa3, 0xc7, 0x48, 0x2b, 0x30, 0x84, 0x4c, 0x14, 0x3f, 0xf8, 0x5b, 0x53, 0xf1, 0xe5, 0x83,
      0xc5, 0x01, 0x25, 0x7d, 0xdd, 0xd0, 0x96, 0xb8, 0x12, 0x68, 0xda, 0xa3, 0x03, 0xf1, 0x72, 0x34, 0xc2, 0x33, 0x35,
      0x41, 0xf0, 0xbb, 0x8e, 0x19, 0x06, 0x48, 0xc5, 0x80, 0x7c, 0x86, 0x6d, 0x71, 0x93, 0x22, 0x86, 0x09, 0xad, 0xb9,
      0x48, 0x68, 0x6f, 0x7d, 0xe2, 0x94, 0xa8, 0x02, 0xcc, 0x38, 0xf7, 0xfe, 0x52, 0x08, 0xf5, 0xea, 0x31, 0x96, 0xd0,
      0x16, 0x7b, 0x9b, 0xdd, 0x02, 0xf0, 0xd2, 0xa5, 0x22, 0x1c, 0xa5, 0x08, 0xf8, 0x93, 0xaf, 0x5c, 0x4b, 0x4b, 0xb9,
      0xf4, 0xf5, 0x20, 0xfd, 0x84, 0x28, 0x9b, 0x3d, 0xbe, 0x7e, 0x61, 0x49, 0x7a, 0x7e, 0x2a, 0x58, 0x40, 0x37, 0xea,
      0x63, 0x7b, 0x69, 0x81, 0x12, 0x71, 0x74, 0xaf, 0x57, 0xb4, 0x71, 0xdf, 0x4b, 0x27, 0x68, 0xfd, 0x79, 0xc1, 0x54,
      0x0f, 0xb3, 0xed, 0xf2, 0xea, 0x22, 0xcb, 0x69, 0xbe, 0xc0, 0xcf, 0x8d, 0x93, 0x3d, 0x9c, 0x6f, 0xdd, 0x64, 0x5e,
      0x85, 0x05, 0x91, 0xcc, 0xa3, 0xd6, 0x2c, 0x0c, 0xc0, 0x00};

  uint8_t* out = (uint8_t*)calloc(len_bytes, sizeof(uint8_t));

  // encryption
  err_lte = liblte_security_encryption_eea3(key, count, bearer, direction, msg, len_bits, out);
  TESTASSERT(err_lte == LIBLTE_SUCCESS);
  int i;
  // compare cipher text
  err_cmp = arrcmp(ct, out, len_bytes);

  if (err_cmp == 0) {
    printf("Test Set 5 Encryption: Success\n");
  } else {
    printf("Test Set 5 Encryption: Failed\n");
  }

  TESTASSERT(err_cmp == 0);

  // decryption
  err_lte = liblte_security_decryption_eea3(key, count, bearer, direction, ct, len_bits, out);
  TESTASSERT(err_lte == LIBLTE_SUCCESS);

  // compare cipher text
  err_cmp = arrcmp(msg, out, len_bytes);
  TESTASSERT(err_cmp == 0);

  if (err_cmp == 0) {
    printf("Test Set 5 Decryption: Success\n");
  } else {
    printf("Test Set 5 Decryption: Failed\n");
  }

  free(out);
  return SRSLTE_SUCCESS;
}

int main(int argc, char* argv[])
{
  TESTASSERT(test_set_1() == SRSLTE_SUCCESS);
  TESTASSERT(test_set_2() == SRSLTE_SUCCESS);
  TESTASSERT(test_set_3() == SRSLTE_SUCCESS);
  TESTASSERT(test_set_4() == SRSLTE_SUCCESS);
  TESTASSERT(test_set_5() == SRSLTE_SUCCESS);
}
