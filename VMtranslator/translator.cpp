#include <bits/stdc++.h>

using namespace std;

ifstream in;
ofstream out;

vector<string> split(string input) {
    string curr = "";

    vector<string> ret(3);

    int add = 0;

    for (int i = 0; i < input.length(); ++i) {
        if (input[i] == '/') {
            break;
        }

        if (input[i] == ' ') {
            if (input[i - 1] == ' ') {
                continue;
            }

            ret[add] = curr;

            ++add;

            curr = "";
        } else {
            curr += input[i];
        }
    }

    ret[2] = curr;

    return ret;
}

int eqcount = 0;
int gtcount = 0;
int ltcount = 0;

int line = 0;

class DefineFunction {
    private:
        string name;
        string lclvals;
    public:
        DefineFunction(string n, string lv) {
            this->name = n;
            this->lclvals = lv;

            out << "@fun_end_" << this->name << endl;
            out << "0;JMP" << endl;

            out << "(fun_" << this->name << ")" << endl;

            out << "@SP" << endl;
            out << "D=M" << endl;
            out << "@LCL" << endl;
            out << "M=D" << endl;

            out << "@" << this->lclvals << endl;
            out << "D=A" << endl;
            out << "@SP" << endl;
            out << "M=D+M" << endl;
        }

        void gotoreturn() {
            out << "@fun_return_" << this->name << endl;
            out << "0;JMP" << endl;
        }

        void endFunction() {
            out << "(fun_return_" << this->name << ")" << endl;


            // RESET THAT

            out << "@LCL" << endl;
            out << "A=M-1" << endl;
            out << "D=M" << endl;
            out << "@THAT" << endl;
            out << "M=D" << endl;

            // FIND RETURN ADDRESS (LCL - 5)

            out << "@LCL" << endl;
            out << "D=M" << endl;
            out << "@5" << endl;
            out << "D=D-A" << endl;
            out << "A=D" << endl;
            out << "D=M" << endl;

            
            out << "@LCL" << endl;
            out << "A=M-1" << endl;
            out << "M=D" << endl;

            // RESET SP AND ADD THE RETURN VALUE

            out << "@SP" << endl;
            out << "A=M-1" << endl;
            out << "D=M" << endl;
            out << "@ARG" << endl;
            out << "A=M" << endl;
            out << "M=D" << endl;
            out << "@ARG" << endl;
            out << "D=M+1" << endl;
            out << "@SP" << endl;
            out << "M=D" << endl;

            // RESET THIS

            out << "@LCL" << endl;
            out << "D=M" << endl;
            out << "@2" << endl;
            out << "D=D-A" << endl;
            out << "A=D" << endl;
            out << "D=M" << endl;
            out << "@THIS" << endl;
            out << "M=D" << endl;

            // RESET ARG

            out << "@LCL" << endl;
            out << "D=M" << endl;
            out << "@3" << endl;
            out << "D=D-A" << endl;
            out << "A=D" << endl;
            out << "D=M" << endl;
            out << "@ARG" << endl;
            out << "M=D" << endl;

            // RESET LCL AND RETURN

            // PUT THE RETURN VALUE IN SP

            out << "@LCL" << endl;
            out << "A=M-1" << endl;
            out << "D=M" << endl;
            out << "@SP" << endl;
            out << "A=M" << endl;
            out << "M=D" << endl;

            // RESET LCL

            out << "@LCL" << endl;
            out << "D=M" << endl;
            out << "@4" << endl;
            out << "D=D-A" << endl;
            out << "A=D" << endl;
            out << "D=M" << endl;
            out << "@LCL" << endl;
            out << "M=D" << endl;

            // RETURN

            out << "@SP" << endl;
            out << "A=M" << endl;
            out << "A=M" << endl;
            out << "0;JMP" << endl;

            out << "(fun_end_" << this->name << ")" << endl;
        }
};

stack<DefineFunction*> defining;

void add() {
    out << "@SP" << endl;
    out << "M=M-1" << endl;
    out << "A=M" << endl;
    out << "D=M" << endl;
    out << "A=A-1" << endl;
    out << "M=D+M" << endl;
}

void sub() {
    out << "@SP" << endl;
    out << "M=M-1" << endl;
    out << "A=M" << endl;
    out << "D=M" << endl;
    out << "A=A-1" << endl;
    out << "M=M-D" << endl;
}

void neg() {
    out << "@SP" << endl;
    out << "A=M" << endl;
    out << "A=A-1" << endl;
    out << "M=-M" << endl;
}

void eq() {
    out << "@SP" << endl;
    out << "M=M-1" << endl;
    out << "A=M" << endl;
    out << "D=M" << endl;
    out << "A=A-1" << endl;
    out << "D=M-D" << endl;
    out << "M=-1" << endl;
    out << "@eq_" << eqcount << endl;
    out << "D;JEQ" << endl;
    out << "@SP" << endl;
    out << "A=M" << endl;
    out << "A=A-1" << endl;
    out << "M=0" << endl;
    out << "(eq_" << eqcount << ")" << endl;

    ++eqcount;
}

void gt() {
    out << "@SP" << endl;
    out << "M=M-1" << endl;
    out << "A=M" << endl;
    out << "D=M" << endl;
    out << "A=A-1" << endl;
    out << "D=M-D" << endl;
    out << "M=-1" << endl;
    out << "@gt_" << gtcount << endl;
    out << "D;JGE" << endl;
    out << "@SP" << endl << endl;
    out << "A=M" << endl;
    out << "A=A-1" << endl;
    out << "M=0" << endl;
    out << "(gt_" << gtcount << ")" << endl;

    ++gtcount;
}

void lt() {
    out << "@SP" << endl;
    out << "M=M-1" << endl;
    out << "A=M" << endl;
    out << "D=M" << endl;
    out << "A=A-1" << endl;
    out << "D=M-D" << endl;
    out << "M=-1" << endl;
    out << "@lt_" << ltcount << endl;
    out << "D;JLE" << endl;
    out << "@SP" << endl;
    out << "A=M" << endl;
    out << "A=A-1" << endl;
    out << "M=0" << endl;
    out << "(lt_" << ltcount << ")" << endl;

    ++ltcount;
}

void andt() {
    out << "@SP" << endl;
    out << "M=M-1" << endl;
    out << "A=M" << endl;
    out << "D=M" << endl;
    out << "A=A-1" << endl;
    out << "M=D&M" << endl;
}

void ort() {
    out << "@SP" << endl;
    out << "M=M-1" << endl;
    out << "A=M" << endl;
    out << "D=M" << endl;
    out << "A=A-1" << endl;
    out << "M=D|M" << endl;
}

void nott() {
    out << "@SP" << endl;
    out << "A=M" << endl;
    out << "A=A-1" << endl;
    out << "M=!M" << endl;
}

unordered_map<string, string> segorder = {
    {"local", "LCL"},
    {"argument", "ARG"},
    {"this", "THIS"},
    {"that", "THAT"},
    {"temp", "R5"},
    {"static", "R16"}
};

void pushval(string val) {
    out << "@" << val << endl;
    out << "D=A" << endl;
    out << "@SP" << endl;
    out << "M=M+1" << endl;
    out << "A=M-1" << endl;
    out << "M=D" << endl;
}

void pushsegval(string seg, string place) {
    out << "@" << segorder[seg] << endl;
    out << "D=M" << endl;
    out << "@" << place << endl;
    out << "A=D+A" << endl;
    out << "D=M" << endl;
    out << "@SP" << endl;
    out << "M=M+1" << endl;
    out << "A=M-1" << endl;
    out << "M=D" << endl;
}

void pushinstseg(string seg, string place) {
    out << "@" << segorder[seg] << endl;
    out << "D=A" << endl;
    out << "@" << place << endl;
    out << "D=D+A" << endl;
    out << "@SP" << endl;
    out << "M=M+1" << endl;
    out << "A=M-1" << endl;
    out << "M=D" << endl;
}

void popinstseg(string seg, string place) {
    out << "@" << segorder[seg] << endl;
    out << "D=A" << endl;
    out << "@" << place << endl;
    out << "D=D+A" << endl;
    out << "@SP" << endl;
    out << "M=M-1" << endl;
    out << "A=M" << endl;
    out << "M=D+M" << endl;
    out << "D=M-D" << endl;
    out << "M=M-D" << endl;
    out << "A=M" << endl;
    out << "M=D" << endl;
}

void pointerpush(string val) {
    if (val == "0") {
        out << "@THIS" << endl;
    } else {
        out << "@THAT" << endl;
    }
        out << "D=M" << endl;
        out << "@SP" << endl;
        out << "M=M+1" << endl;
        out << "A=M-1" << endl;
        out << "M=D" << endl;
}

void popsegval(string seg, string place) {
    out << "@" << segorder[seg] << endl;
    out << "D=M" << endl;
    out << "@" << place << endl;
    out << "D=D+A" << endl;
    out << "@SP" << endl;
    out << "M=M-1" << endl;
    out << "A=M" << endl;
    out << "M=D+M" << endl;
    out << "D=M-D" << endl;
    out << "M=M-D" << endl;
    out << "A=M" << endl;
    out << "M=D" << endl;
}

void pointerpop(string val) {
    out << "@SP" << endl;
    out << "M=M-1" << endl;
    out << "A=M" << endl;
    out << "D=M" << endl << endl;

    if (val == "0") {
        out << "@THIS" << endl;
    } else {
        out << "@THAT" << endl;
    }

    out << "M=D" << endl;
}

// BRANCHING

void label(string label) {
    out << "(." << label << ")" << endl;
}

void gotovm(string label) {
    out << "@." << label << endl;
    out << "0;JMP" << endl;
}

void ifgotovm(string label) {
    out << "@SP" << endl;
    out << "M=M-1" << endl;
    out << "A=M" << endl;
    out << "D=M" << endl;
    out << "@." << label << endl;
    out << "D;JNE" << endl;
}

// FUNCTIONS

// Call function (args)
// function name (lcl)

void runfunction(string name, string args) {
    out << "@fun_returnAddress_" << name << "_" << line << endl;
    out << "D=A" << endl;

    out << "@SP" << endl;
    out << "A=M" << endl;
    out << "M=D" << endl;

    // LCL

    out << "@LCL" << endl;
    out << "D=M" << endl;

    out << "@SP" << endl;
    out << "M=M+1" << endl;
    out << "A=M" << endl;
    out << "M=D" << endl;

    // ARG

    out << "@ARG" << endl;
    out << "D=M" << endl;

    out << "@SP" << endl;
    out << "M=M+1" << endl;
    out << "A=M" << endl;
    out << "M=D" << endl;

    // THIS

    out << "@THIS" << endl;
    out << "D=M" << endl;

    out << "@SP" << endl;
    out << "M=M+1" << endl;
    out << "A=M" << endl;
    out << "M=D" << endl;

    // THAT

    out << "@THAT" << endl;
    out << "D=M" << endl;

    out << "@SP" << endl;
    out << "M=M+1" << endl;
    out << "A=M" << endl;
    out << "M=D" << endl;

    // INC

    out << "@SP" << endl;
    out << "M=M+1" << endl;

    // ARGS = SP - 5 - ARGS

    out << "@SP" << endl;
    out << "D=M" << endl;
    out << "@5" << endl;
    out << "D=D-A" << endl;
    out << "@" << args << endl;
    out << "D=D-A" << endl;
    out << "@ARG" << endl;
    out << "M=D" << endl;

    // CALL THE FUNCTION

    out << "@fun_" << name << endl;
    out << "0;JMP" << endl;

    out << "(fun_returnAddress_" << name << "_" << line << ")" << endl;
}

int main(int argc, char* argv[]) {
    string input;

    vector<int> funreturns;
    int currindex = -1;

    if (argc != 2) {
        throw runtime_error("VM translator didn't initiate, you must provide exactly 1 file");
    }

    string path = argv[1];

    in = ifstream(path);
    out = ofstream(path.substr(0, path.find_last_of('.')) + ".asm");

    while (getline(in, input)) {
        vector<string> parsed = split(input);
        if (parsed[0] == "function") {
            ++currindex;
            funreturns.push_back(0);
        } else if (parsed[2] == "return") {
            ++funreturns[currindex];
        }
    }

    in.clear();
    in.seekg(0, ios::beg);

    currindex = -1;

    while (getline(in, input)) {
        if (input[0] == '/') {
            continue;
        }

        ++line;

        string c1, c2, c3;

        vector<string> sp = split(input);

        c1 = sp[0];
        c2 = sp[1];
        c3 = sp[2];

        cout << c1 << ":c1 " << c2 << ":c2 " << c3 << endl;

        out << "// " << input << endl;

        if (c1 == "push") {
            if (c2 == "temp" or c2 == "static") {
                pushinstseg(c2, c3);
            } else if (c2 == "constant") {
                pushval(c3);
            } else if (c2 == "pointer") {
                pointerpush(c3);
            } else {
                pushsegval(c2, c3);
            }
        } else if (c1 == "pop") {
            if (c2 == "temp" or c2 == "static") {
                popinstseg(c2, c3);
            } else if (c2 == "pointer") {
                pointerpop(c3);
            } else {
                popsegval(c2, c3);
            }
        } else if (c3 == "add") {
            add();
        } else if (c3 == "sub") {
            sub();
        } else if (c3 == "neg") {
            neg();
        } else if (c3 == "eq") {
            eq();
        } else if (c3 == "gt") {
            gt();
        } else if (c3 == "lt") {
            lt();
        } else if (c3 == "and") {
            andt();
        } else if (c3 == "or") {
            ort();
        } else if (c3 == "not") {
            nott();
        } else if (c1 == "label") {
            label(c3);
        } else if (c1 == "goto") {
            gotovm(c3);
        } else if (c1 == "if-goto") {
            ifgotovm(c3);
        }

        // FUNCTIONS

        if (c1 == "function") {
            defining.push(new DefineFunction(c2, c3));
            ++currindex;
        } else if (c3 == "return") {
            cout << "FOUND" << endl;

            --funreturns[currindex];

            if (funreturns[currindex] == 0) {
                defining.top()->endFunction();
                delete defining.top();
                defining.pop();
            } else {
                defining.top()->gotoreturn();
            }
        } else if (c1 == "call") {
            runfunction(c2, c3);
        }

        cout << defining.size() << endl;
    }
}