
#ifndef _WB_SRAM_
#define _WB_SRAM_

#include <systemc.h>

SC_MODULE(wb_sram) {

  sc_in_clk clk;
  
  sc_in<bool> rst_i;
  sc_in<bool> cyc_i;
  sc_in<bool> stb_i;
  sc_in<bool> we_i;
  sc_out<bool> ack_o;
  sc_in<sc_uint<8> > addr_i;
  sc_in<sc_uint<8> > data_i;
  sc_out<sc_uint<8> > data_o;

  sc_signal<bool> sram_wr_en;
  sc_signal<sc_uint<8> > sram_addr;
  sc_signal<sc_uint<8> > sram_wr_data;
  sc_signal<sc_uint<8> > sram_rd_data;

  wb_slave_if * u_wb_slv;
  sram8x256   * u_sram;

  SC_CTOR(wb_sram) {

    u_wb_slv = new wb_slave_if("name_wb_slave_if");
    assert(u_wb_slv);

    u_sram = new sram8x256("name_sram8x256");
    assert(u_sram);

    u_wb_slv->clk         (clk         );
    u_wb_slv->rst_i       (rst_i       );
    u_wb_slv->stb_i       (stb_i       );
    u_wb_slv->cyc_i       (cyc_i       );
    u_wb_slv->we_i        (we_i        );
    u_wb_slv->ack_o       (ack_o       );
    u_wb_slv->addr_i      (addr_i      );
    u_wb_slv->data_i      (data_i      );
    u_wb_slv->data_o      (data_o      );

    u_wb_slv->sram_wr_en  (sram_wr_en  );
    u_wb_slv->sram_addr   (sram_addr   );
    u_wb_slv->sram_wr_data(sram_wr_data);
    u_wb_slv->sram_rd_data(sram_rd_data);

    u_sram->clk           (clk         );
    u_sram->wr_en         (sram_wr_en  );
    u_sram->addr          (sram_addr   );
    u_sram->wr_data       (sram_wr_data);
    u_sram->rd_data       (sram_rd_data);
  }

  ~wb_sram() {
    if(u_wb_slv) {
      delete u_wb_slv;
      u_wb_slv = 0;
    }
    if(u_sram) {
      delete u_sram;
      u_sram = 0;
    }
  }

};

#endif

