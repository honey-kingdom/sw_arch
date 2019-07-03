// Reference
//      Mentor : Does the factory say override? Successfully using the UVM factory
class env #(BITWIDTH = 128) extends uvm_component;
    `uvm_component_param_utils(env#(BITWIDTH))
    ...
endclass



class env_with_coverage #(BITWIDTH = 2048) extends env#(BITWIDTH)
    `uvm_component_param_utils(env_with_coverage#(BITWIDTH))
    ...
endclass



class test extends uvm_test;
    `uvm_component_utils(test)

    env#(128) e0;
    env#(256) e1;
    ...

    function void build_phase(uvm_phase phase);
        env#(128)::type_id::set_type_override( env_with_coverage#(128)::get_type());
        env#(256)::type_id::set_inst_override( env_with_coverage#(256)::get_type(), "uvm_test_top.e1");

        e0 = env#(128)::type_id::create("e0", this);
        e0 = env#(256)::type_id::create("e1", this);
    end function

    task run_phase(uvm_phase phase);
        uvm_root::get().print_topology();
        factory.print();
        ...
    endtask

endclass
