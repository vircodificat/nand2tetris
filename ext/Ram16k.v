module Ram16k(
    input  wire        clock,
    input  wire [15:0] in,
    input  wire        load,
    input  wire [13:0] address,
    output reg  [15:0] out
);
    reg [15:0] memory [0:16383];

    always @(posedge clock) begin
        if (load) begin
            $display("-------------------- STORE ---------------------");
            $display("memory[%d] = %d", address, in);
            memory[address] <= in;
        end

        out <= memory[address];
    end
endmodule
