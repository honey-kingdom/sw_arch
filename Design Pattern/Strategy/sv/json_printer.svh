class json_printer extends uvm_printer;
   function new();
      super.new();
   endfunction: new

   virtual function string emit();
      string s;
      string comma = "";
      string space = { 100 { " " } };
      string indent;
      int    next_level;

      s = "{\n"; // begin JSON

      foreach ( m_rows[i] ) begin
         uvm_printer_row_info row = m_rows[i];

         indent = space.substr( 1, ( row.level + 1 ) * knobs.indent );
         s = { s, comma, indent };

         if ( i == m_rows.size() - 1 ) begin // last row
            next_level = 0;
         end else begin // not last row
            next_level = m_rows[ i + 1 ].level;
            if ( row.level < next_level ) begin // next level is deepr
               s = { s, "\"", row.name, "\": {\n" }; // begin nested JSON object
               comma = "";
               continue;
            end
         end
         s = { s, "\"", row.name, "\": \"", row.val, "\"" }; // name-value pair
         comma = ",\n";

         if ( next_level < row.level ) begin // next level is shallower
            for ( int l = row.level; l > next_level; l-- ) begin
               indent = space.substr( 1, l * knobs.indent );
               s = { s, "\n", indent, "}" }; // end nested JSON object
            end
         end
      end // foreach ( m_rows[i] )

      emit = { s, "\n}" }; // end JSON
      m_rows.delete();
   endfunction: emit
endclass: json_printer
