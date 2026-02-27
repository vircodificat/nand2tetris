`timescale 1ns/1ps

`define FN_ADD 1'd0
`define FN_AND 1'd1

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

    reg clk = 0;

    // Task to apply a test vector
    task run_test;
        input [30 * 8:0] name;
        input [15:0] tx, ty;
        input tzx, tnx, tzy, tny, tf, tno;
        input[15:0] expected_out;
        input expected_zr;
        input expected_ng;
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

            $display("%s:\n\n    x=%0d y=%0d zx=%b nx=%b zy=%b ny=%b f=%b no=%b | out=%0d zr=%b ng=%b\n",
                     name, x, y, zx, nx, zy, ny, f, no, out, zr, ng);

            if (out != expected_out || zr != expected_zr || ng != expected_ng) begin
                $display("Wrong answer. Expected | out=%0d zr=%b ng=%b\n",
                expected_out, expected_zr, expected_ng);

                $fatal;
            end
        end
    endtask

    always begin
        #5 clk = ~clk;
    end

    initial begin
        $display("Starting ALU tests...");
        $dumpfile("alu.vcd");
        $dumpvars(0, Alu_tb);

        run_test("1) x + y = 5 + 3 = 8", 16'd5, 16'd3, 0,0,0,0,`FN_ADD,0, 16'd8, 0,0);

        run_test("2) x - y = 7 - 2 = 5", 16'd7, 16'd2, 0,1,0,0,`FN_ADD,1, 16'd5, 0,0);

        run_test("3) y - x = 2 - 7 = -5 (two’s complement)", 16'd2, 16'd7, 0,0,0,1,`FN_ADD,1, 16'h5, 0,0);

        run_test("4) x & y", 16'b1010101010101010,
                 16'b1111000011110000,
                 0,0,0,0,`FN_AND,0,
                 16'b1010000010100000, 0,1);

        run_test("5) x | y", 16'b1010101010101010,
                 16'b0101010101010101,
                 0,1,0,1,`FN_AND, 1,
                 16'b1111111111111111, 0,1);

        run_test("6) Zero output", 16'd1234, 16'd5678,
                 1,0,1,0, `FN_AND,0,
                 16'd0, 1,0);

        run_test("7) Constant 0", 16'd0, 16'd0,
                 1,1,1,1,`FN_AND,1,
                 16'd0, 1,0);

        run_test("8) -1", 16'd0, 16'd0,
                 1,1,1,0,`FN_ADD,0,
                 16'hFFFF, 0,1);

        run_test("9) Pass x", 16'd42, 16'd999,
                 0,0,1,1,`FN_AND,0,
                 16'd42, 0,0);

        run_test("10) Pass y", 16'd999, 16'd42,
                 1,1,0,0,`FN_AND,0,
                 16'd42, 0,0);

        run_test("11) Negative result (3 - 10 = -7)", 16'd3, 16'd10,
                 0,1,0,0,`FN_ADD,1,
                 16'hFFF9, 0,1);

        run_test("12) Large values add (0x7FFF + 1 = 0x8000)", 16'h7FFF, 16'd1,
                 0,0,0,0,`FN_ADD,0,
                 16'h8000, 0,1);


        $display("ALU tests complete.");
        $finish;
    end

endmodule
