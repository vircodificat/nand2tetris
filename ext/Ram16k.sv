module \memory::Ram16k (
    input  wire clock,

    input  wire [15:0] in,
    input  wire        load,
    input  wire [13:0] address,

    output reg  [15:0] out
);
    reg [15:0] memory[1 << 14];

    assign out = memory[address];

    always @(posedge clock) begin
        if (load) begin
            memory[address] = in;
        end
    end
endmodule

module \memory::Rom16k (
    input  wire [13:0] address,

    output reg  [15:0] out
);
    reg [15:0] memory[1 << 14];

    assign out = memory[address];
endmodule
