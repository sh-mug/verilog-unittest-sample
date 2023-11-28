`timescale 1ns / 1ps

module alu (
    input rst_n,
    input clk,
    input [2:0] inst,
    input [31:0] a,
    input [31:0] b,
    output logic [31:0] rslt
);
  logic [4:0] shamt;
  logic alu_lt;
  logic alu_ltu;
  logic [31:0] alu_add;
  logic [31:0] alu_sll;
  logic [31:0] alu_xor;
  logic [31:0] alu_srl;
  logic [31:0] alu_or;
  logic [31:0] alu_and;

  always_comb begin
    shamt   = b[4:0];

    alu_lt  = $signed(a) < $signed(b);
    alu_ltu = a < b;
    alu_add = a + b;
    alu_sll = a << shamt;
    alu_xor = a ^ b;
    alu_srl = a >> shamt;
    alu_or  = a | b;
    alu_and = a & b;

    case (inst)
      3'b000:  rslt = alu_add;
      3'b001:  rslt = alu_sll;
      3'b010:  rslt = {31'b0, alu_lt};
      3'b011:  rslt = {31'b0, alu_ltu};
      3'b100:  rslt = alu_xor;
      3'b101:  rslt = alu_srl;
      3'b110:  rslt = alu_or;
      3'b111:  rslt = alu_and;
      default: rslt = 0;
    endcase
  end
endmodule : alu
