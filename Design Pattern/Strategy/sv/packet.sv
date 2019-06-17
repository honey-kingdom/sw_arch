class v1_pack implements PackBehavior;
    virtual function Fields unpack(logic [13:0] raw);
       Fields fields    = new;
       fields.reserved  = raw[11];
       fields.addr      = raw[10:7];
       fields.data      = raw[6:3];
       fields.cmd       = raw[2:0];
       return fields;
    endfunction
...



class v1_packet extends base_packet;
    function new();
       v1_pack p = new();
       Crc c = new();

       setPackBehavior(p);
       setCheckBehavior(c);
    endfunction
endclass
