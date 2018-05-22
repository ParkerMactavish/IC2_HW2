module freqDevider(clk, rst, dclk);
	input clk, rst;
	
	output reg dclk;
	
	reg[24:0]count;
	
	always@(posedge clk, posedge rst)begin
		if(rst)begin
			dclk<=1'b0;
			count<=25'd0;
		end
		
		else if(count==25'd24000000)begin
			dclk<=~dclk;
			count<=25'd0;
		end
		
		else count<=count+25'd1;
		
	end

endmodule