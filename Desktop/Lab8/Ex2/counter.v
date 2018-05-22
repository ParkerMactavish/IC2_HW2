module counter(clk, rst, stateNow, stateNext, count);
	input clk, rst;
	input [1:0]stateNow, stateNext;
	
	output reg [2:0]count;
	
	reg[2:0] countNext;
				
	//combinatorial component to determine the next state
	always@(*)begin
		if(stateNow==stateNext) countNext=count+3'd1;
		else countNext=3'd1;
	end
	
	//memory component to remember the current state
	always@(posedge clk or posedge rst)begin
		if(rst) count<=1;
		else	count<=countNext;
	end
	
endmodule