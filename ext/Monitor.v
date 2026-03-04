`ifdef VERILATOR
    import "DPI-C" function void monitor(
        input logic[15:0] pc,
        input logic[15:0] instr,
        input logic[15:0] a,
        input logic[15:0] d,
        input logic[15:0] m
    );
`endif

module Monitor(
    input wire clock,
    input wire reset,
    input wire [15:0] pc,
    input wire [15:0] instr,
    input wire [15:0] a,
    input wire [15:0] d,
    input wire [15:0] m
);

    always @(posedge clock) begin
        `ifdef VERILATOR
            monitor(pc, instr, a, d, m);
        `endif
    end

endmodule
