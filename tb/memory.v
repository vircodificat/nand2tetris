`timescale 1ns/1ps

`define FN_ADD 1'd0
`define FN_AND 1'd1

module Memory_tb;
    Rom16k uut (
        .clock(clock),
        .address(address),
        .out(out)
    );

    wire [15:0] out;

    reg [13:0] address = 16'h0;
    reg clock = 1;
    reg [31:0] i = 0;

    task tick;
        begin
            #5 clock = ~clock;
            #5 clock = ~clock;
        end
    endtask

    initial begin
        $display("Starting Memory tests...");
        $dumpfile("build/memory.vcd");
        $dumpvars(0, Memory_tb);

        $readmemh("data/magic.hex", uut.memory, 0, 16);

        for (i = 0; i < 10; i++) begin
            tick();
            $display("Checking memory at %d (= %h)", address, out);
            address = address + 1;
        end

        $display("Memory tests complete.");
        $finish;
    end

endmodule
