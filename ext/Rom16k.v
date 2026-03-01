module Rom16k(
    input  wire [13:0] address,
    output wire [15:0] out
);
    reg [15:0] memory[0:16383];
    assign out = memory[address];
endmodule
