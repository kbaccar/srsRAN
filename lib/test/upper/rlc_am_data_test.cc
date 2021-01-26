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

#include "srslte/common/test_common.h"
#include "srslte/upper/rlc_am_lte.h"
#include <iostream>

// Fixed header only
uint8_t  pdu1[]   = {0x88, 0x06};
uint32_t PDU1_LEN = 2;

// Fixed + 2 LI fields (each 1500)
uint8_t  pdu2[]   = {0x8C, 0x00, 0xDD, 0xC5, 0xDC};
uint32_t PDU2_LEN = 5;

// Fixed + 3 LI fields (each 1500)
uint8_t  pdu3[]   = {0x8C, 0x00, 0xDD, 0xCD, 0xDC, 0x5D, 0xC0};
uint32_t PDU3_LEN = 7;

// D/C = 1 = Data PDU
// RF  = 0 = AMD PDU
// P   = 0 = Status PDU is not requested
// FI  = 11 = First byte of the Data field does not corresponds to the first byte of a RLC SDU,
// Last byte of the Data field does not corresponds to the last byte of a RLC SDU
// E   = 1  = A set of E field and LI field follows from the octet following the fixed part of the header
// SN = 0000000010 -> SN 2
// E   = 1
// LI1 = 1010011 1110 (1342 Dec)
// E  = 0
// LI2 = 10111011100 (1500 Dec)
uint8_t  pdu4[]   = {0x9C, 0x02, 0xD3, 0xE5, 0xDC};
uint32_t PDU4_LEN = 5;

using namespace srslte;

int test1()
{
  srslte::rlc_amd_pdu_header_t h;
  srslte::byte_buffer_t        b1, b2;

  memcpy(b1.msg, &pdu1[0], PDU1_LEN);
  b1.N_bytes = PDU1_LEN;
  rlc_am_read_data_pdu_header(&b1, &h);
  TESTASSERT(RLC_DC_FIELD_DATA_PDU == h.dc);
  TESTASSERT(0x01 == h.fi);
  TESTASSERT(0 == h.N_li);
  TESTASSERT(0 == h.lsf);
  TESTASSERT(0 == h.p);
  TESTASSERT(0 == h.rf);
  TESTASSERT(0 == h.so);
  TESTASSERT(6 == h.sn);
  rlc_am_write_data_pdu_header(&h, &b2);
  TESTASSERT(b2.N_bytes == PDU1_LEN);
  for (uint32_t i = 0; i < b2.N_bytes; i++)
    TESTASSERT(b2.msg[i] == b1.msg[i]);
  return SRSLTE_SUCCESS;
}

int test2()
{
  srslte::rlc_amd_pdu_header_t h;
  srslte::byte_buffer_t        b1, b2;

  memcpy(b1.msg, &pdu2[0], PDU2_LEN);
  b1.N_bytes = PDU2_LEN;
  rlc_am_read_data_pdu_header(&b1, &h);
  TESTASSERT(RLC_DC_FIELD_DATA_PDU == h.dc);
  TESTASSERT(0x01 == h.fi);
  TESTASSERT(2 == h.N_li);
  TESTASSERT(1500 == h.li[0]);
  TESTASSERT(1500 == h.li[1]);
  TESTASSERT(0 == h.lsf);
  TESTASSERT(0 == h.p);
  TESTASSERT(0 == h.rf);
  TESTASSERT(0 == h.so);
  TESTASSERT(0 == h.sn);
  rlc_am_write_data_pdu_header(&h, &b2);
  TESTASSERT(b2.N_bytes == PDU2_LEN);
  for (uint32_t i = 0; i < b2.N_bytes; i++)
    TESTASSERT(b2.msg[i] == b1.msg[i]);
  return SRSLTE_SUCCESS;
}

int test3()
{
  srslte::rlc_amd_pdu_header_t h;
  srslte::byte_buffer_t        b1, b2;

  memcpy(b1.msg, &pdu3[0], PDU3_LEN);
  b1.N_bytes = PDU3_LEN;
  rlc_am_read_data_pdu_header(&b1, &h);
  TESTASSERT(RLC_DC_FIELD_DATA_PDU == h.dc);
  TESTASSERT(0x01 == h.fi);
  TESTASSERT(3 == h.N_li);
  TESTASSERT(1500 == h.li[0]);
  TESTASSERT(1500 == h.li[1]);
  TESTASSERT(1500 == h.li[2]);
  TESTASSERT(0 == h.lsf);
  TESTASSERT(0 == h.p);
  TESTASSERT(0 == h.rf);
  TESTASSERT(0 == h.so);
  TESTASSERT(0 == h.sn);
  rlc_am_write_data_pdu_header(&h, &b2);
  TESTASSERT(b2.N_bytes == PDU3_LEN);
  for (uint32_t i = 0; i < b2.N_bytes; i++)
    TESTASSERT(b2.msg[i] == b1.msg[i]);
  return SRSLTE_SUCCESS;
}

int test4()
{
  srslte::rlc_amd_pdu_header_t h;
  srslte::byte_buffer_t        b1, b2;

  memcpy(b1.msg, &pdu4[0], PDU4_LEN);
  b1.N_bytes = PDU4_LEN;
  rlc_am_read_data_pdu_header(&b1, &h);
  TESTASSERT(RLC_DC_FIELD_DATA_PDU == h.dc);
  TESTASSERT(0x03 == h.fi);
  TESTASSERT(2 == h.N_li);
  TESTASSERT(1342 == h.li[0]);
  TESTASSERT(1500 == h.li[1]);
  TESTASSERT(0 == h.lsf);
  TESTASSERT(0 == h.p);
  TESTASSERT(0 == h.rf);
  TESTASSERT(0 == h.so);
  TESTASSERT(2 == h.sn);
  rlc_am_write_data_pdu_header(&h, &b2);
  TESTASSERT(b2.N_bytes == PDU4_LEN);
  for (uint32_t i = 0; i < b2.N_bytes; i++)
    TESTASSERT(b2.msg[i] == b1.msg[i]);
  return SRSLTE_SUCCESS;
}

int main(int argc, char** argv)
{
  TESTASSERT(test1() == SRSLTE_SUCCESS);
  TESTASSERT(test2() == SRSLTE_SUCCESS);
  TESTASSERT(test3() == SRSLTE_SUCCESS);
  TESTASSERT(test4() == SRSLTE_SUCCESS);
  return SRSLTE_SUCCESS;
}
