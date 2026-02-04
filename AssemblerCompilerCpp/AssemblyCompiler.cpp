#include <bits/stdc++.h>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

unordered_map<string, int> JUMPS = {
    {"", 0b000},
    {"JGT", 0b001},
    {"JEQ", 0b010},
    {"JGE", 0b011},
    {"JLT", 0b100},
    {"JNE", 0b101},
    {"JLE", 0b110},
    {"JMP", 0b111}
};

unordered_map<string, int> DESTS = {
    {"", 0b000},
    {"M", 0b001},
    {"D", 0b010},
    {"MD", 0b011},
    {"A", 0b100},
    {"AM", 0b101},
    {"AD", 0b110},
    {"AMD", 0b111}
};

unordered_map<string, int> COMP = {
    {"", 0b0000000},
    {"0", 0b0101010},
    {"1", 0b0111111},
    {"-1", 0b0111010},
    {"D", 0b0001100},
    {"A", 0b0110000},
    {"!D", 0b0001101},
    {"!A", 0b0110001},
    {"-D", 0b0001111},
    {"-A", 0b0110011},
    {"D+1", 0b0011111},
    {"A+1", 0b0110111},
    {"D-1", 0b0001110},
    {"A-1", 0b0110010},
    {"D+A", 0b0000010},
    {"D-A", 0b0010011},
    {"A-D", 0b0000111},
    {"D&A", 0b0000000},
    {"D|A", 0b0010101},

    {"M", 0b1110000},
    {"!M", 0b1110001},
    {"-M", 0b1110011},
    {"M+1", 0b1110111},
    {"M-1", 0b1110010},
    {"D+M", 0b1000010},
    {"D-M", 0b1010011},
    {"M-D", 0b1000111},
    {"D&M", 0b1000000},
    {"D|M", 0b1010101}
};

unordered_map<string, int> SymbolMap {
    {"R0", 0},
    {"R1", 1},
    {"R2", 2},
    {"R3", 3},
    {"R4", 4},
    {"R5", 5},
    {"R6", 6},
    {"R7", 7},
    {"R8", 8},
    {"R9", 9},
    {"R10", 10},
    {"R11", 11},
    {"R12", 12},
    {"R13", 13},
    {"R14", 14},
    {"R15", 15},

    {"SP", 0},
    {"LCL", 1},
    {"ARG", 2},
    {"THIS", 3},
    {"THAT", 4},
    {"SCREEN", 16384},
    {"KBD", 24576}
};

string nospaces(string inst) {
    string ret = "";

    for (int i = 0; i < inst.size(); ++i) {
        if (inst[i] == ' ') {
            continue;
        } else if (inst[i] == '/') {
            return ret;
        } else {
            ret += inst[i];
        }
    }

    return ret;
}

int currvarnum = 16;

bitset<16> A(string inst) {
    string trans = string(inst.begin() + 1, inst.end());

    int num;

    if ((int)trans[0] < 48 or (int)trans[0] > 57) {
        if (!SymbolMap.count(trans)) {
            SymbolMap[trans] = currvarnum;
            ++currvarnum;
        }

        num = SymbolMap[trans];
    } else {
        num = stoi(trans);
    }

    return bitset<16>(num);
}

bitset<16> C(string inst) {
    string jump = "";
    string comp = "";
    string dest = "";

    auto from = inst.begin();
    auto to = inst.end();

    if (*(inst.end() - 4) == ';') {
        jump = string(inst.end() - 3, inst.end());

        to = inst.end() - 4;
    }

    for (int i = 1; i < 4; ++i) {
        if (inst[i] == '=') {
            dest = string(inst.begin(), inst.begin() + i);

            from = inst.begin() + i + 1;
        }
    }

    comp = string(from, to);

    bitset<16> ret((0b111 << 13));

    ret |= (COMP[comp] << 6);
    ret |= (DESTS[dest] << 3);
    ret |= (JUMPS[jump]);

    return ret;
}

void compileAssembly(string path) {
    int currinstruction = 0;

    ifstream in;
    ofstream out;

    in = ifstream(path);
    out = ofstream(path.substr(0, path.find_last_of('.')) + ".hack");
    
    string inst;

    vector<string> insts;

    while (getline(in, inst)) {
        inst = nospaces(inst);

        if (inst == "") {
            continue;
        }

        if (inst[0] == '(') {
            SymbolMap[string(inst.begin() + 1, inst.end() - 1)] = currinstruction;
        } else {
            insts.push_back(inst);
            ++currinstruction;
        }
    }

    for (string in: insts) {
        if (in[0] == '@') {
            out << A(in);
        } else {
            out << C(in);
        }

        out << '\n';
    }
}

int main(int argc, char* argv[]) {

    if (argc != 2) {
        throw runtime_error("Assembly compiler didn't initiate, you must provide exactly 1 file");
    }

    string path = argv[1];

    fs::file_status pathst = fs::status(path);

    if (fs::is_directory(pathst)) {
        for (fs::directory_entry entry: fs::directory_iterator(path)) {
            if (entry.path().extension() == ".asm") {
                compileAssembly(entry.path().string());
            }
        }
    } else {
        compileAssembly(path);
    }
}