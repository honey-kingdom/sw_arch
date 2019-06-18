// Reference :
//      https://www.chipverify.com/uvm/tlm-analysis-port
//      http://cluelogic.com/2012/11/uvm-tutorial-for-candy-lovers-analysis-port/

class componentB extends uvm_component;
  `uvm_component_utils (componentB)

  // Create an analysis port by the name "ap" that can broadcast packets of type "simple_packet"
  uvm_analysis_port #(simple_packet) ap;

  function new (string name = "componentB", uvm_component parent = null);
    super.new (name, parent);
  endfunction

  virtual function void build_phase (uvm_phase phase);
    super.build_phase (phase);
    ap = new ("analysis_port", this);
  endfunction

  virtual task run_phase (uvm_phase phase);
    super.run_phase (phase);

    for (int i = 0; i < 5; i++) begin
        simple_packet pkt = simple_packet::type_id::create ("pkt");
        pkt.randomize();
           // Now pass it to other components via the analysis port write() method
          ap.write (pkt);
    end
  endtask
endclass





virtual class uvm_subscriber #(type T=int) extends uvm_component;
  typedef uvm_subscriber #(T) this_type;

  uvm_analysis_imp #(T, this_type) analysis_export;

  pure virtual function void write (T t);
endclass





class sub #(type T = simple_packet) extends uvm_subscriber #(T);
   `uvm_component_utils (sub)

   function new (string name = "sub", uvm_component parent = null);
      super.new (name, parent);
   endfunction

   virtual function void build_phase (uvm_phase phase);
      super.build_phase (phase);
   endfunction

   // Note that the class object name has to be "t" - anything else will result
   // in compilation error
   virtual function void write (T t);
      `uvm_info (get_full_name(), "Sub got transaction", UVM_MEDIUM)
   endfunction
endclass




class my_env extends uvm_env;
  ...
  virtual function void connect_phase (uvm_phase phase);
    super.connect_phase (phase);
    compB.ap.connect (sub1.analysis_export);
  endfunction
endclass
