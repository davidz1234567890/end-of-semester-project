#include <systemc.h>

SC_MODULE(queue) {
  sc_in<bool> clock;
  sc_in<bool> reset_n;
  sc_in<bool> get;
  sc_in<bool> put;
  sc_out<bool> full;
  sc_out<bool> empty;
  sc_out<bool> dReady;
  sc_in<sc_uint<8>> dIn;   // 8-bit input port
  sc_out<sc_uint<8>> dOut; // 8-bit output port

  sc_uint<4> count;
  sc_uint<8> Q[8];
  sc_uint<3> getPtr;
  sc_uint<3> putPtr;
  

  SC_CTOR(queue) {
        SC_THREAD(queue_thread);
        sensitive << clock.pos() << reset_n.neg();
   
  };

  void queue_thread() {
      if(reset_n.read() == false){
        count = 0;
        getPtr = 0;
        putPtr = 0;
        dReady.write(false);
        empty.write(true);
        full.write(false);
        std::cout << "Resetting module at time: " << sc_time_stamp() << std::endl;
      }
      else {
        full.write(count == 8);
        empty.write(count == 0);

        dReady.write(false);
        if(get.read() == 1 && count > 0){
          dOut.write(Q[getPtr]);
          std::cout << "entering get at time: " << sc_time_stamp() << std::endl;
          getPtr = getPtr + 1;
          count = count - 1;
          dReady.write(true);
        }
        else if(put.read() == 1 && count < 8){
          Q[putPtr] = dIn.read();
          std::cout << "entering PUT at time: " << sc_time_stamp() << std::endl;
          putPtr = putPtr + 1;
          count = count + 1;
        }
      }
    
  }
  
  
  

};
