/* -*- c++ -*- */
/*
 * Copyright 2020 gr-pduadd author.
 *
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "add_length_impl.h"

#include <algorithm>
#include <vector>
#include <string>

namespace gr {
  namespace pduadd {

    add_length::sptr add_length::make()
    {
      return gnuradio::get_initial_sptr(new add_length_impl());
    }


    /*
     * The private constructor
     */
    add_length_impl::add_length_impl()
      : gr::block("add_length",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(0, 0, 0))
    {
    message_port_register_out(pmt::mp("out"));
    message_port_register_in(pmt::mp("in"));
    set_msg_handler(pmt::mp("in"), [this](pmt::pmt_t msg) { this->msg_handler(msg); });
    }

    /*
     * Our virtual destructor.
     */
    add_length_impl::~add_length_impl() {}

    void
    add_length_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required) {}

    int
    add_length_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
      return 0;
    }
    
    void add_length_impl::msg_handler(pmt::pmt_t pmt_msg)
    {
    std::vector<uint8_t> msg = pmt::u8vector_elements(pmt::cdr(pmt_msg));
    std::vector<uint8_t> cut_msg = std::vector<uint8_t>(msg.begin(), msg.end());
    
    cut_msg.insert(cut_msg.begin(), cut_msg.size());
    
    message_port_pub(
        pmt::mp("out"),
        pmt::cons(pmt::car(pmt_msg), pmt::init_u8vector(cut_msg.size(), cut_msg)));
    }

  } /* namespace pduadd */
} /* namespace gr */

