/**
 *
 * \section COPYRIGHT
 *
 * Copyright 2013-2017 Software Radio Systems Limited
 *
 * \section LICENSE
 *
 * This file is part of srsLTE.
 *
 * srsLTE is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * srsLTE is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * A copy of the GNU Affero General Public License can be found in
 * the LICENSE file in the top-level directory of this distribution
 * and at http://www.gnu.org/licenses/.
 *
 */

/******************************************************************************
 * File:        hss.h
 * Description: Top-level HSS class. Creates and links all
 *              interfaces and helpers.
 *****************************************************************************/

#ifndef HSS_H
#define HSS_H

#include <cstddef>
#include "srslte/common/log.h"
#include "srslte/common/logger_file.h"
#include "srslte/common/log_filter.h"
#include "srslte/common/buffer_pool.h"
#include <fstream>

namespace srsepc{

typedef struct{
  std::string db_file;
}hss_args_t;

typedef struct{
    std::string name;
    uint64_t imsi;
    uint8_t key[16];
    uint8_t op[16];
    uint8_t amf[2];
}hss_ue_ctx_t;



class hss
{
public:
  static hss* get_instance(void);
  static void cleanup(void);
  int init(hss_args_t *hss_args, srslte::log_filter* hss_log);
  bool read_db_file(std::string db_file);

  void get_sqn(uint8_t sqn[6]);
  void gen_rand(uint8_t rand_[16]);
  bool get_k_amf_op(uint64_t imsi, uint8_t *k, uint8_t *amf, uint8_t *op);
  bool gen_auth_info_answer_milenage(uint64_t imsi, uint8_t *k_asme, uint8_t *autn, uint8_t *rand, uint8_t *xres);

  std::vector<std::string> split_string(const std::string &str, char delimiter);
  void get_uint_vec_from_hex_str(const std::string &key_str, uint8_t *key, uint len);

private:

  hss();
  virtual ~hss();
  static hss *m_instance;

  uint64_t                  m_sqn; //48 bits
  srslte::byte_buffer_pool *m_pool;
  std::ifstream m_db_file;

  std::map<uint64_t,hss_ue_ctx_t*> m_imsi_to_ue_ctx;

  /*Logs*/
  srslte::log_filter       *m_hss_log;
 
};

} // namespace srsepc

#endif // MME_H
