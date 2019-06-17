// Reference :
//      https://www.chipverify.com/uvm/uvm-printer
//      http://cluelogic.com/2016/05/uvm-tutorial-for-candy-lovers-defining-do_print/

virtual class uvm_object extends uvm_void;
  ...
  function void print (uvm_printer printer=null);
    if (printer==null)
        printer = uvm_default_printer;
      ...
  endfunction
  ...
endclass



/* Global Instances */
uvm_table_printer   uvm_default_table_printer = new();
uvm_tree_printer    uvm_default_tree_printer = new();
uvm_line_printer    uvm_default_line_printer = new();
/* ---------------- */



class my_data extends uvm_sequence_item; // Inherited from uvc_object
  bit [2:0] mode;
endclass

my_data obj0;
obj0.print ();                               // Calls table printer by default
obj0.print (uvm_default_line_printer);       // Calls line printer
