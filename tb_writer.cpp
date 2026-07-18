#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

std::string toBinary(std::string num, int width) {
    int number = std::stoi(num);
    std::string binaryNum = "";

    while (number != 0) {
        if (number % 2 == 1) {
            binaryNum.insert(0, "1");
        } else {
            binaryNum.insert(0, "0");
        }
        number /= 2;
    }
    
    // pad with zeroes to match size after getting the actual number
    while (binaryNum.size() < width) {
        binaryNum.insert(0, "0");
    }

    return binaryNum;
}

int main() {
    int count = 0; // use for clock timing/repeats
    std::string file_name = "placeholder";
    std::string currentLine = "e";
    std::string byte = "e2";
    std::stringstream stream(currentLine);
    std::vector<std::string> bytes;
    std::string instr_count = "";
    std::string regNumber[2] = {"", ""};

    // get file name
    std::cout << "Enter file name & extension (.txt): ";
    std::cin >> file_name;

    std::ifstream input_file(file_name);
    std::ofstream compiled_file("testfile.v");

    // Initial/non-variable text befire instructions
    if (compiled_file.is_open()) {
        compiled_file << "`timescale 1ns/1ps\n\n";
        compiled_file << "module cpu_tb;"
                        "\n\treg [15:0] instr;"
                        "\n\treg clk;"
                        "\n\treg rst;"
                        "\n\twire [7:0] cpu_out;"
                        "\n\n\tcpu cpu_inst ("
                        "\n\t\t.clk(clk),"
                        "\n\t\t.reset(rst),"
                        "\n\t\t.instruction(instr),"
                        "\n\t\t.out(cpu_out)"
                        "\n\t);"
                        "\n\n\tinitial begin"
                        "\n\t\t$dumpfile(\"cpu_st.vcd\");"
                        "\n\t\t$dumpvars(0);"
                        "\n\n\t\tclk = 0;\n\t\trst = 0;\n\t\tinstr = 16'h0;";
    } else {
        std::cerr << "file to compile into not opened";
    }

    if (input_file.is_open()) {
        while (getline(input_file, currentLine)) {
            stream.clear();
            stream.str(currentLine);
            count++;

            // Place separate words into vector/array
            while (stream >> byte) {
                bytes.push_back(byte);
            }

            if (bytes[0] == "LOAD") {
                regNumber[0] = bytes[1][1];
                compiled_file << "\n\t\t#2 instr = 16'b" + toBinary("6", 4) + toBinary(regNumber[0], 4) + toBinary(bytes[2], 8) + ";";
            } else if (bytes[0] == "OUT") {
                regNumber[0] = bytes[1][1];
                compiled_file << "\n\t\t#2 instr = 16'b" + toBinary("7", 4) + toBinary(regNumber[0], 4) + toBinary("0", 8) + ";";
            } else if (bytes[0] == "LSHIFT") {
                regNumber[0] = bytes[1][1];
                compiled_file << "\n\t\t#2 instr = 16'b" + toBinary("8", 4) + toBinary(regNumber[0], 4) + toBinary(bytes[2], 8) + ";";
            } else if (bytes[0] == "RSHIFT") {
                regNumber[0] = bytes[1][1];
                compiled_file << "\n\t\t#2 instr = 16'b" + toBinary("9", 4) + toBinary(regNumber[0], 4) + toBinary(bytes[2], 8) + ";";
            } else if (bytes[0] == "INC") {
                regNumber[0] = bytes[1][1];
                compiled_file << "\n\t\t#2 instr = 16'b" + toBinary("10", 4) + toBinary(regNumber[0], 4) + toBinary("0", 8) + ";";
            } else if (bytes[0] == "DEC") {
                regNumber[0] = bytes[1][1];
                compiled_file << "\n\t\t#2 instr = 16'b" + toBinary("11", 4) + toBinary(regNumber[0], 4) + toBinary("0", 8) + ";";
            } else if (bytes[0] == "RST") {
                compiled_file << "\n\t\t#2 instr = 16'b" + toBinary("12", 4) + toBinary("0", 12) + ";";
            } else if (bytes[0] == "MOVE") {
                regNumber[0] = bytes[1][1];
                regNumber[1] = bytes[2][1];
                compiled_file << "\n\t\t#2 instr = 16'b" + toBinary("13", 4) + toBinary(regNumber[0], 4) + toBinary(regNumber[1], 4) + toBinary("0", 4) + ";";
            } else if (bytes[0] == "ADD") {
                regNumber[0] = bytes[1][1];
                regNumber[1] = bytes[2][1];
                compiled_file << "\n\t\t#2 instr = 16'b" + toBinary("0", 4) + toBinary(regNumber[0], 4) + toBinary(regNumber[1], 4) + toBinary("0", 4) + ";";
            } else if (bytes[0] == "SUB") {
                regNumber[0] = bytes[1][1];
                regNumber[1] = bytes[2][1];
                compiled_file << "\n\t\t#2 instr = 16'b" + toBinary("1", 4) + toBinary(regNumber[0], 4) + toBinary(regNumber[1], 4) + toBinary("0", 4) + ";";
            } else if (bytes[0] == "AND") {
                regNumber[0] = bytes[1][1];
                regNumber[1] = bytes[2][1];
                compiled_file << "\n\t\t#2 instr = 16'b" + toBinary("2", 4) + toBinary(regNumber[0], 4) + toBinary(regNumber[1], 4) + toBinary("0", 4) + ";";
            } else if (bytes[0] == "XOR") {
                regNumber[0] = bytes[1][1];
                regNumber[1] = bytes[2][1];
                compiled_file << "\n\t\t#2 instr = 16'b" + toBinary("3", 4) + toBinary(regNumber[0], 4) + toBinary(regNumber[1], 4) + toBinary("0", 4) + ";";
            } else if (bytes[0] == "OR") {
                regNumber[0] = bytes[1][1];
                regNumber[1] = bytes[2][1];
                compiled_file << "\n\t\t#2 instr = 16'b" + toBinary("4", 4) + toBinary(regNumber[0], 4) + toBinary(regNumber[1], 4) + toBinary("0", 4) + ";";
            } else if (bytes[0] == "CMP") {
                regNumber[0] = bytes[1][1];
                regNumber[1] = bytes[2][1];
                compiled_file << "\n\t\t#2 instr = 16'b" + toBinary("5", 4) + toBinary(regNumber[0], 4) + toBinary(regNumber[1], 4) + toBinary("0", 4) + ";";
            }
        }
    } else {
        std::cerr << "file to get text not opened";
    }

    instr_count = std::to_string(count * 4);

    compiled_file << "\n\tend"
                    "\n\n\tinitial begin"
                    "\n\t\trepeat (" + instr_count + ") begin"
                    "\n\t\t\t#0.5 clk = ~clk;"
                    "\n\t\tend"
                    "\n\tend"
                    "\nendmodule";
    return 0;
}