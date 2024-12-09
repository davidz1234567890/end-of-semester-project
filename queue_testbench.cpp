#include "systemc.h"
#include "design.cpp"

int sc_main(int argc, char* argv[]) {
   sc_clock clock("clock", 1, SC_NS); 
  sc_signal<bool> reset_n;
  sc_signal<bool> get;
  sc_signal<bool> put;
  sc_signal<bool> full;
  sc_signal<bool> empty;
  sc_signal<bool> dReady;
  sc_signal<sc_uint<8>> dIn;   // 8-bit input port
  sc_signal<sc_uint<8>> dOut;
  
    queue abc("simple_module");
  
    abc.clock(clock);
    abc.reset_n(reset_n);
    abc.get(get);
    abc.put(put);
    abc.full(full);
    abc.empty(empty);
    abc.dReady(dReady);
    abc.dIn(dIn);
    abc.dOut(dOut);
  
  // Open VCD file
  sc_trace_file *wf = sc_create_vcd_trace_file("abc");

  sc_trace(wf, clock, "clock");
  
  // Assuming `sc_signal<sc_uint<8>> Q[8];` is defined
for (int i = 0; i < 8; i++) {
    std::string trace_name = "Q[" + std::to_string(i) + "]";
    sc_trace(wf, abc.Q[i], trace_name.c_str());
}

  
  sc_trace(wf, reset_n, "reset_n");
  
  sc_trace(wf, get, "get");
  sc_trace(wf, put, "put");
  sc_trace(wf, full, "full");
  sc_trace(wf, empty, "empty");
  sc_trace(wf, dReady, "dReady");
  sc_trace(wf, dIn, "dIn");
  sc_trace(wf, dOut, "dOut");
  
  sc_trace(wf, abc.count, "count");
  sc_trace(wf, abc.getPtr, "getPtr");
  sc_trace(wf, abc.putPtr, "putPtr");
 
    
    
  reset_n.write(false);
    
  
    
    sc_start(5, SC_NS); // Simulate 5 ns (to observe reset)
   
  
   
  reset_n.write(true);
 

    sc_start(1, SC_NS);

    dIn.write( 1);
    put.write(true);
      sc_start(0.5, SC_NS);
  
    sc_start(1, SC_NS);
    dIn.write(2);
  
    sc_start(1, SC_NS);

    // Close the trace file
    sc_close_vcd_trace_file(wf);

    return 0;
  

    
}
