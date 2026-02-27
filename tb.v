`timescale 1ns/1ps

`define FN_AND 1'd0
`define FN_ADD 1'd1

module Alu_tb;

    // Inputs
    reg  [15:0] x;
    reg  [15:0] y;
    reg         zx;
    reg         nx;
    reg         zy;
    reg         ny;
    reg         f;
    reg         no;

    // Outputs
    wire [15:0] out;
    wire        zr;
    wire        ng;

    // Instantiate the ALU
    Alu uut (
        .x(x),
        .y(y),
        .zx(zx),
        .nx(nx),
        .zy(zy),
        .ny(ny),
        .f(f),
        .no(no),
        .out(out),
        .zr(zr),
        .ng(ng)
    );

    // Task to apply a test vector
    task run_test;
        input [15:0] tx, ty;
        input tzx, tnx, tzy, tny, tf, tno;
        input[15:0] expected;
        begin
            x  = tx;
            y  = ty;
            zx = tzx;
            nx = tnx;
            zy = tzy;
            ny = tny;
            f  = tf;
            no = tno;
            #10;

            $display("x=%0d y=%0d zx=%b nx=%b zy=%b ny=%b f=%b no=%b | out=%0d zr=%b ng=%b",
                     x, y, zx, nx, zy, ny, f, no, out, zr, ng);
            if (out != expected) begin
                $display("Wrong answer");
                $fatal;
            end
        end
    endtask

    initial begin
        $display("Starting ALU tests...");
        $dumpfile("alu.vcd");
        $dumpvars(0, Alu_tb);

        // 1) x + y
        run_test(16'd5, 16'd5, 0, 0, 0, 0, `FN_ADD, 0, 10);

/*

        // 2) x - y
        run_test(16'd7, 16'd2, 0, 0, 0,1,1,1);

        // 3) y - x
        run_test(16'd2, 16'd7, 0,1, 0, 0,1,1);

        // 4) x & y
        run_test(16'b1010101010101010,
                 16'b1111000011110000,
                 0, 0, 0, 0, 0, 0);

        // 5) x | y
        run_test(16'b1010101010101010,
                 16'b0101010101010101,
                 0,1, 0,1, 0,1);

        // 6) Zero output
        run_test(16'd1234, 16'd5678, 1, 0,1, 0,1, 0);

        // 7) Constant 1
        run_test(16'd0, 16'd0, 1,1,1,1,1,1);

        // 8) -1
        run_test(16'd0, 16'd0, 1,1,1, 0,1, 0);

        // 9) Pass x
        run_test(16'd42, 16'd999, 0, 0,1,1, 0, 0);

        // 10) Pass y
        run_test(16'd999, 16'd42, 1,1, 0, 0, 0, 0);

        // 11) Negative result
        run_test(16'd3, 16'd10, 0, 0, 0,1,1,1);

        // 12) Large values add
        run_test(16'h7FFF, 16'd1, 0, 0, 0, 0,1, 0);
*/

        $display("ALU tests complete.");
        $finish;
    end

endmodule
