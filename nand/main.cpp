
#ifndef _MAIN_CPP_
#define _MAIN_CPP_

#include <systemc.h>
#include "nand.cpp"
#include "tb.cpp"

int sc_main(int, char **) {

  sc_signal<bool > a, b, res;

  sc_time cycle(20, SC_NS);
  sc_clock clk("Clk", cycle);

  sc_time simulation_time(200, SC_NS);

  nand INST_NAND("Nand");
  INST_NAND.A(a);
  INST_NAND.B(b);
  INST_NAND.F(res);

  tb INST_TB("Tb");
  INST_TB.clk(clk);
  INST_TB.a(a);
  INST_TB.b(b);
  INST_TB.res(res);

  sc_start(simulation_time);
  return 0;

}

#endif

