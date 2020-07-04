
#ifndef _TB_
#define _TB_

#include <systemc.h>

SC_MODULE(tb) {

  sc_in_clk clk_i;
  sc_in<bool> rst_i;

  sc_out<bool> cyc_o;
  sc_out<bool> stb_o;
  sc_out<bool> we_o;
  sc_in<bool> ack_i;
  sc_out<sc_uint<8> > addr_o;
  sc_out<sc_uint<8> > data_o;
  sc_in<sc_uint<8> > data_i;

  sc_uint<8> sig_addr;
  sc_uint<8> sig_data;
  unsigned int cnt;
  bool odd;

  void do_stim() {
    addr_o = 0;
    data_o = 0;
    cyc_o = false;
    stb_o = false;
    we_o = false;
    cnt = 0;
    odd = true;

    while(true) {
      wait();
      
      if(cnt<=512) {
        cout<<sc_simulation_time()<<"--------------------"<<"rst_i, cyc, stb, we, ack, addr, data = "<<rst_i<<", "<<cyc_o<<", "<<stb_o<<", "<< we_o<<", "<<ack_i<<", "<<addr_o<<", "<<data_o<<"."<<endl;
        if((!ack_i) && (!rst_i)) { // use ~ to replace ! cannot work
          stb_o = true;
          cyc_o = true;
          we_o = true;
          sig_addr = addr_o.read();
          sig_data = data_o.read();
          if(odd && (cnt>=2)) {
            sig_addr += 1;
            sig_data += 1;
          }
          addr_o.write(sig_addr); // direct use addr_o.write(addr_o.read()+1) cannot work
          data_o.write(sig_data);
          odd = !odd;
          cnt++;
        }
        else {
          stb_o = false;
          cyc_o = false;
          we_o = false;
        }
        cout<<sc_simulation_time()<<"--------------------"<<"rst_i, cyc, stb, we, ack, addr, data = "<<rst_i<<", "<<cyc_o<<", "<<stb_o<<", "<< we_o<<", "<<ack_i<<", "<<addr_o<<", "<<data_o<<"."<<endl;
      }
      else {
        if(cnt%4==0)
          sig_addr += 1;
        addr_o.write(sig_addr);
        data_o = 0;
        cyc_o = false;
        stb_o = false;
        we_o = false;
        cnt++;
      }
    }
  }

  SC_CTOR(tb) {
    SC_THREAD(do_stim);
    sensitive<<clk_i.pos();
  }

};

#endif

