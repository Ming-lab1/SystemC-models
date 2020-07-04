
#ifndef _MAIN_
#define _MAIN_

#include <systemc.h>

#include "sram8x256.h"
#include "wb_slave_if.h"
#include "wb_sram.h"
#include "tb.h"

int sc_main(int, char **) {

  sc_clock clk("CLK", 20, SC_NS, 0.5);

  wb_sram * u_wb_sram;
  tb * u_tb;

  sc_signal<bool> rst;
  sc_signal<bool> stb, cyc, we, ack;
  sc_signal<sc_uint<8> > addr;
  sc_signal<sc_uint<8> > data_tb2sram;
  sc_signal<sc_uint<8> > data_sram2tb;

  u_wb_sram = new wb_sram("name_wb_sram");
  u_tb = new tb("name_tb");

  (*u_wb_sram) (clk, rst, cyc, stb, we, ack, addr, data_tb2sram, data_sram2tb);
  (*u_tb)      (clk, rst, cyc, stb, we, ack, addr, data_tb2sram, data_sram2tb);

  rst.write(true); 
  sc_time time1(1000, SC_NS);
  sc_start(time1);
 
  rst.write(false);
  sc_time time2(40000, SC_NS); // 20ns*3 * 256, 20ns * 256 * 4
  sc_start(time2);
 
  cout<<sc_simulation_time()<<endl;
  return 0;

}

#endif

