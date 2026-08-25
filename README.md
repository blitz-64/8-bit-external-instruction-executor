# 8-bit-external-instruction-executor
Simple project made to learn basics in verilog through designing a very simple 8-bit cpu. The cpu program does not include any RAM/instruction memory, so the cpu is given instructions externally.
This also lets you create a verilog file to input instructions into the cpu and test it, however it does not show the outputs to the terminal. The outputs can be seen by using a software to view the waveforms and signals.

## Operations

| Operation | Info | Syntax example |
| --- | --- | --- |
| ADD | Adds the value of the first register to the second register and places the result into the second register | ADD R1 R2 |
| SUB | Subtracts the value of the first register from the second register's value and places the result into the second register | SUB R1 R2 |
| AND | Bitwise AND operation on values in the registers; result goes into second register | AND R1 R2 |
| XOR | Bitwise XOR operation on values in the registers; result goes into second register | XOR R1 R2 |
| OR | Bitwise OR operation on values in the registers; result goes into second register | OR R1 R2 |
| CMP | Compare values in the registers, outputs 1 if same, 0 if not. Result goes into second register | CMP R1 R2 |
| LOAD | Store a number into a register | LOAD R5 37 |
| OUT | Output a register's stored value | OUT R3 |
| LSHIFT | Shift a register's value x bits to the left | LSHIFT R1 x |
| RSHIFT | Shift a register's value x bits to the right | RSHIFT R1 x |
| INC | Increase a register's value by 1 | INC R1 |
| DEC | Decrease a register's value by 1 | DEC R1 |
| MOVE | Move the first register's value into the second register | MOVE R4 R5 |
| RESET | Reset all registers to 0 & clear instruction | RESET |

## Compiling and running
The languages used are: [Icarus verilog](https://bleyer.org/icarus/), and C++. To run this, you need them both installed. To view the outputs, the [gtkwave software](https://gtkwave.sourceforge.net/) can be installed and used. All files should be contained inside the same folder.
#
For the verilog program, it is compiled and executed using command prompt/terminal:

Compilation: *iverilog -o <**simulation_file**>.vvp <**cpu_file**>.v <**test_file**>.v*. This command must be executed in the folder's path. Replace bolded text between <> with your actual file names if different.

Run: *vvp <**simulation_file**>.vvp*
#
For opening and viewing output in gtkwave (after compiling and running the verilog code): 

*gtkwave <**waves_file**>.vcd*
#
For C++, all you need is a compiler and something that can run the code. 
#
To make a verilog file that runs your own commands/instructions, **first** create a .txt file containing the operation commands (from the table above) so that a verilog file containing those instructions to be tested can actually be ran. After making the text file, run the C++ program to make the verilog file (which will be named test_file.v) by entering the text file name. Then, all you need to do to run the verilog test code (test_file.v) is compile it using the instructions from above for running verilog and gtkwave.

A text file is included as an example for how to format the commands if needed.
## Design notes:
- Since it contains no RAM, there are no operations that allow for jumping between instructions at different points. This design only executes instructions line by line as it is given in the provided file
- Also due to the simple external driven design, it requires a specific timing and so might not work properly if instructions were given to it at different intervals
- The program to create files for testing only runs instructions line by line, and does not thouroughly test all things (edge cases, timing, etc.) for my design
- It does not handle negative values and just overflows

Overall this design isn't the best and doesn't do things with more logical/better methods, but the goal was to learn how Verilog worked rather than making a good cpu design.
