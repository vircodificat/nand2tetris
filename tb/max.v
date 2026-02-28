`timescale 1ns/1ps

module Max_tb;
    Rom16k rom (
        .address(pc[13:0]),
        .out(instruction)
    );

    Ram16k ram (
        .clock(clock),
        .address(memory_addr[13:0]),
        .out(memory_in),
        .in(memory_out),
        .load(memory_write)
    );

    Cpu cpu(
        .clock(clock),
        .reset(reset),

        .instruction(instruction),

        .memory_in(memory_in),
        .memory_out(memory_out),
        .memory_addr(memory_addr),
        .memory_write(memory_write),

        .pc(pc)
    );

    wire [15:0] pc;
    wire [15:0] instruction;
    wire [15:0] memory_out;
    wire [15:0] memory_in;
    wire [15:0] memory_addr;
    wire        memory_write;

    reg cycle = 0;
    reg clock = 1;
    reg reset = 0;


    reg [31:0] i = 0;

    task tick;
        begin
            #5 clock = ~clock;
            #5 clock = ~clock;
            cycle = ~cycle;
        end
    endtask

    task reset_system;
        begin
            reset = 1;
            tick();
            reset = 0;
            tick();
        end
    endtask

    initial begin
        $display("Starting Max tests...");
        $dumpfile("build/max.vcd");
        $dumpvars(0, Max_tb);

        $readmemb("data/Max.hack", rom.memory, 0, 15);
        ram.memory[16'h0000] = 16'd7;
        ram.memory[16'h0001] = 16'd11;

        $display("RAM[0x0000] = %d", ram.memory[16'h0000]);
        $display("RAM[0x0001] = %d", ram.memory[16'h0001]);

        reset_system();
        for (i = 0; i < 50; i++) begin
            tick();
        end

        $display("RAM[0x0002] = %d", ram.memory[16'h0002]);
        if (ram.memory[16'h0002] !== 16'd11) begin
            $display("ERROR: Expected 11");
            $fatal;
        end

        $display("Max tests complete.");
        $finish;
    end

endmodule
