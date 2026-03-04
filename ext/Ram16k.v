module Ram16k(
    input  wire        clock,
    input  wire [15:0] in,
    input  wire        load,
    input  wire [13:0] address,
    output wire [15:0] out
);
    reg [15:0] memory[0:16383];

    assign out = memory[address];

    always @(posedge clock) begin
        if (load) begin
//            $display("-------------------- STORE ---------------------");
//            $display("memory[%d] = %d", address, in);
            memory[address] <= in;


        end
        `ifdef VERILATOR
            log_ram_write(address);
        `endif
        $display("Uh oh");
    end

    integer i;

    initial begin
        for (i = 0; i < 16384; i++) begin
            memory[i] = 16'hxxxx;
        end
    end

endmodule
