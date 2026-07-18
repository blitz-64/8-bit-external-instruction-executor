module adder_8(
    input [7:0] a,
    input [7:0] b,
    output [7:0] adder_result,
    output carry
);
    assign carry = (a + b > 255) ? 1 : 0;
    assign adder_result = a + b;
endmodule

module subtractor_8( 
    input [7:0] a,
    input [7:0] b,
    output [7:0] subtractor_result,
    output overflow
);

    assign overflow = (b - a < 0) ? 1 : 0;

    assign subtractor_result = b - a;
endmodule

module alu (
    input [3:0] op,
    input [7:0] a,
    input [7:0] b,
    output [7:0] alu_out, 
    output o_flag,
    output c_flag,
    output z_flag
);

    wire [7:0] add_result;
    wire [7:0] sub_result;
    reg [7:0] result;

    adder_8 add_inst (.a(a), .b(b), .adder_result(add_result), .carry(c_flag));
    subtractor_8 sub_inst (.a(a), .b(b), .subtractor_result(sub_result), .overflow(o_flag));

    always @(*) begin 
        case(op)
            4'h0: result = add_result; 
            4'h1: result = sub_result; 
            4'h2: result = a & b; 
            4'h3: result = a ^ b;
            4'h4: result = a | b;
            4'h5: begin
                if (a == b)
                    result = 8'h1;
                else
                    result = 8'h0;
            end
            default: result = 8'h0;
        endcase
    end

    assign z_flag = (result == 0) ? 1 : 0;
    assign alu_out = result;

endmodule

module cpu (
    input clk,
    input [15:0] instruction,
    output [7:0] out,
    output zf,
    output cf,
    output of
);
    reg [7:0] registers [7:0]; // For storing operands to do operations
    reg [15:0] IR;
    reg [7:0] reg_out;
    wire [7:0] alu_out_w;
    integer i = 0;
    
    initial begin // Initializing block
        IR [15:12] = 4'he; 
        IR [11:0] = 0;
        reg_out = 0;

        for (i = 0; i < 16; i++) begin
            registers[i] = 0;
        end
    end

    assign out = reg_out; 

    alu alu_inst (.op(IR [15:12]), .a(registers [IR [11:8]]), .b(registers [IR [7:4]]), .alu_out(alu_out_w), .o_flag(of), .z_flag(zf), .c_flag(cf)); 

    always @(posedge clk) begin
        IR <= instruction;
        // First byte/4 bits of instructions for operations directly in cpu dont matter
        casez (IR [15:12])
            4'h0, 4'h1, 4'h2, 4'h3, 4'h4, 4'h5: begin
                registers [IR [7:4]] <= alu_out_w;
                IR [15:12] <= 4'he;
            end
            4'h6: begin
                registers [IR [11:8]] <= IR [7:0];
                IR [15:12] <= 4'he;
            end // Load
            4'h7: begin
                reg_out <= registers [IR [11:8]];
                IR [15:12] <= 4'he;
            end // OUT
            4'h8: begin
                registers [IR [11:8]] <= registers [IR [11:8]] << IR [7:0];
                IR [15:12] <= 4'he;
            end // LSHIFT
            4'h9: begin
               registers [IR [11:8]] <= registers [IR [11:8]] >> IR [7:0];
               IR [15:12] <= 4'he;
            end // RSHIFT
            4'ha: begin
                registers [IR [11:8]] <= registers [IR [11:8]] + 1;
                IR [15:12] <= 4'he;
            end // INC 
            4'hb: begin
                registers [IR [11:8]] <= registers [IR [11:8]] - 1;
                IR [15:12] <= 4'he;
            end // DEC 
            4'hc: begin
                i = 0;
                IR [15:12] <= 4'he; 
                IR [11:0] <= 0; 
                reg_out <= 8'h0;

                for (i = 0; i < 16; i++) begin
                    registers[i] <= 0;
                end
            end // Reset
            4'hd: begin
                registers [IR[7:4]] <= registers [IR [11:8]];
                IR [15:12] <= 4'he;
            end // Move
            default: ; 
        endcase
    end
endmodule
