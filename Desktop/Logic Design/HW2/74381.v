module SN74381(sel, A, B, Cn, F, G, P);
	input [2:0]sel;
	input [3:0]A, B;
	input Cn;
	
	output [3:0]F;
	output G, P;
	
	always@(*)begin
		case(sel)
			3'd0: begin F=4'd0; G=1'd0; P=1'd0; end
			3'd1:
		endcase
	end	
endmodule