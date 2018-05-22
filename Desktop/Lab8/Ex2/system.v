module system(clk, rst, outLED, outSS);
	input clk, rst;
	output [2:0]outLED;
	output [6:0]outSS;
	
	wire dclk;
	wire [1:0]stateNow, stateNext;
	wire [2:0]count;
	
	freqDevider FD(.clk(clk), .rst(rst), .dclk(dclk));
	trafficLight TL(.clk(dclk), .rst(rst), .count(count), .stateNow(stateNow), .stateNext(stateNext), .out(outLED));
	counter CNT(.clk(dclk), .rst(rst),.count(count), .stateNow(stateNow), .stateNext(stateNext));
	sevenSeg SS(.in({1'b0, count}), .out(outSS));
	
endmodule