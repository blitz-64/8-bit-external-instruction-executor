# 8-bit-external-instruction-executor
Simple project made to learn basics in verilog through designing a very simple 8-bit cpu. The cpu program does not include any RAM/instruction memory, so the cpu is given instructions externally.
This also lets you create a verilog file to input instructions into the cpu and test it, however it does not show the outputs to the terminal. The outputs can be seen by using a software to view the waveforms and signals.

# Operations

#
Design Notes:
- Since it contains no RAM, there are no operations that allow for jumping between instructions at different points. This design only executes instructions line by line as it is given in the provided file
- Also due to the simple external driven design, it requires a specific timing and so might not work properly if instructions were given to it at different intervals
- The program to create files for testing only runs instructions line by line, and does not thouroughly test all things (edge cases, timing, etc.) for my design
