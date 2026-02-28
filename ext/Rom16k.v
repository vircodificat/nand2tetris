module Rom16k(
    input  wire        clock,
    input  wire [13:0] address,
    output reg  [15:0] out
);
    always @(*) begin
        case (address[1:0]) 
            2'b00: begin
                out = 16'hc;
            end
            2'b01: begin
                out = 16'ha;
            end
            2'b10: begin
                out = 16'hf;
            end
            2'b11: begin
                out = 16'he;
            end
        endcase
    end
endmodule
