
#ifndef _WB_SLAVE_IF_
#define _WB_SLAVE_IF_

#include <systemc.h>

SC_MODULE(wb_slave_if) {
  sc_in_clk clk;
  
  sc_in<bool> rst_i;
  sc_in<bool> stb_i;
  sc_in<bool> cyc_i;
  sc_in<bool> we_i;
  sc_out<bool> ack_o;
  sc_in<sc_uint<8> > addr_i;
  sc_in<sc_uint<8> > data_i;
  sc_out<sc_uint<8> > data_o;

  sc_in<sc_uint<8> > sram_rd_data;
  sc_out<sc_uint<8> > sram_wr_data;
  sc_out<sc_uint<8> > sram_addr;
  sc_out<bool> sram_wr_en;

  void do_direct_connection() {
    sram_addr = addr_i;
    sram_wr_data = data_i;
    sram_wr_en = we_i && cyc_i && stb_i && ack_o;
    
    data_o = sram_rd_data;
  }

  void do_gen_ack() {
    if(rst_i) ack_o = false;
    else ack_o = cyc_i && stb_i && !ack_o;
  }

  SC_CTOR(wb_slave_if) {
    SC_METHOD(do_direct_connection);
    sensitive<<addr_i<<data_i<<we_i<<ack_o<<sram_rd_data;
    SC_METHOD(do_gen_ack);
    sensitive<<clk.pos()<<rst_i.pos();
  }

  ~wb_slave_if() {
  }

};

#endif
