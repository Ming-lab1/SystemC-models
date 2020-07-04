
#ifndef _SRAM8X256_
#define _SRAM8X256_

#include <systemc.h>
#include <assert.h>

SC_MODULE(sram8x256) {
  sc_in_clk clk;
  sc_in<bool > wr_en;
  sc_in<sc_uint<8> > addr;
  sc_in<sc_uint<8> > wr_data;
  sc_out<sc_uint<8> > rd_data;

  void do_memory_access() {
    rd_data = mem[addr.read()]; // rd_data will use last cycle's addr data.
    cout<<sc_simulation_time()<<"--------------------"<<"rd data: addr = "<<addr<<", addr.read() = "<<addr.read()<<", data= "<<rd_data<<"."<<endl;
    if(wr_en) {
      mem[addr.read()] = wr_data;
      cout<<sc_simulation_time()<<"--------------------"<<"wr data: addr = "<<addr<<", data= "<<wr_data<<"."<<endl;
    }
  }

  SC_CTOR(sram8x256) {
    mem = new sc_uint<8>[256];
    assert(mem!=NULL);
    for(int i=0;i<256;i++) mem[i]=0;
    SC_METHOD(do_memory_access);
    sensitive<<clk.pos();
  }

  ~sram8x256() {
    if(mem) {
      delete mem;
      mem=0;
    }
  }

private:
  sc_uint<8> * mem;

};

#endif

