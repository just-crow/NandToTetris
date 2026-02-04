#include <bits/stdc++.h>
#include <cctype>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

ifstream in;
ofstream outt;
ofstream outf;
ofstream outv;

fs::path hp;

int tokensize;

void printlist(vector<string> a) {
    for (string i: a) {
        cout << i << endl;
    }

    cout << endl;
}

unordered_map<string, string> LexEls = {
    {"class", "keyword"},
    {"constructor", "keyword"},
    {"function", "keyword"},
    {"method", "keyword"},
    {"field", "keyword"},
    {"static", "keyword"},
    {"var", "keyword"},
    {"int", "keyword"},
    {"char", "keyword"},
    {"boolean", "keyword"},
    {"void", "keyword"},
    {"true", "keyword"},
    {"false", "keyword"},
    {"null", "keyword"},
    {"this", "keyword"},
    {"let", "keyword"},
    {"do", "keyword"},
    {"if", "keyword"},
    {"else", "keyword"},
    {"while", "keyword"},
    {"return", "keyword"},

    {"{", "symbol"},
    {"}", "symbol"},
    {"(", "symbol"},
    {")", "symbol"},
    {"[", "symbol"},
    {"]", "symbol"},
    {".", "symbol"},
    {",", "symbol"},
    {";", "symbol"},
    {"+", "symbol"},
    {"-", "symbol"},
    {"*", "symbol"},
    {"/", "symbol"},
    {"&", "symbol"},
    {"|", "symbol"},
    {">", "symbol"},
    {"<", "symbol"},
    {"=", "symbol"},
    {"~", "symbol"},
};

vector<string> tokenizeLine(string s) {
    vector<string> ret;

    string currword = "";
    bool typefound = false;
    int type = 0;
    bool stringOpen = false;

    // TYPES: 0 - char/num-stream   1 - digitstream   2 - string

    s = s + " ";

    for (int i = 0; i < s.length(); ++i) {
        if (s[i] == '/' and s[i + 1] == '/' and !stringOpen) {
            if (currword != "") {
                cout << "deal with comments";
            }

            return ret;
        }

        if (!typefound) {
            if (s[i] == ' ') {
                continue;
            }

            if (isdigit(s[i])) {
                typefound = true;
                type = 1;
            } else if (isalpha(s[i]) or s[i] == '_') {
                typefound = true;
                type = 0;
            } else if (s[i] == '"') {
                if (!stringOpen) {
                    stringOpen = true;
                    typefound = true;
                    type = 2;

                    continue;
                }
            } else {
                if (LexEls.count(string(1, s[i])) and LexEls[string(1, s[i])] == "symbol") {
                    ret.push_back("<symbol>" + string(1, s[i]) + "</symbol>");
                    continue;
                } else {
                    cout << s[i] << " is not a valid JACK character";
                    break;
                }
            }
        }

        if (type == 1 and !isdigit(s[i])) {
            ret.push_back("<integerConstant>" + currword + "</integerConstant>");
            
            typefound = false;
            currword = "";
            --i;

            continue;
        }

        if (type == 0 and !isdigit(s[i]) and !isalpha(s[i]) and s[i] != '_') {
            if (LexEls.count(currword)) {
                ret.push_back("<" + LexEls[currword] + ">" + currword + "</" + LexEls[currword] + ">");
            } else {
                ret.push_back("<identifier>" + currword + "</identifier>");
            }

            typefound = false;
            currword = "";
            --i;

            continue;
        }

        if (type == 2 and s[i] == '"') {
            ret.push_back("<StringConstant>" + currword + "</StringConstant>");

            stringOpen = false;
            typefound = false;
            currword = "";

            continue;
        }

        currword += s[i];
    }

    return ret;
}


struct typetoken {
    string type;
    string value;
    string fullt;
};

struct tableel {
    string type;
    string kind;
    int index;

    tableel() = default;
    tableel(string t, string k, int i) : type(t), kind(k), index(i) {}
};

void printtable(unordered_map<string, tableel> t) {
    for (const auto& [key, value] : t) {
        cout << key << ": " << value.type << ", " << value.kind << ", " << value.index << endl;
    }
}

class VMwriter {
    public:
        void writePush(string seg, int ind) {
            outv << "push " << seg << " " << ind << endl;
        }

        void writePop(string seg, int ind) {
            outv << "pop " << seg << " " << ind << endl;
        }

        void writeLabel(string label) {
            outv << "label " << label << endl;
        }

        void writeIfGoto(string label) {
            outv << "if-goto " << label << endl;
        }

        void writeNeg() {
            outv << "neg" << endl;
        }

        void writeGoto(string label) {
            outv << "goto " << label << endl;
        }

        void writeNot() {
            outv << "not" << endl;
        }

        void writeAdd() {
            outv << "add" << endl;
        }

        void writeFunction(string name, int lcl) {
            outv << "function " << name << " " << lcl << endl;
        }

        void writeCall(string name, int arg) {
            outv << "call " << name << " " << arg << endl; 
        }

        void writeReturn() {
            outv << "return" << endl;
        }

        void writeEq() {
            outv << "eq" << endl;
        }

        void writeGt() {
            outv << "gt" << endl;
        }

        void writeLt() {
            outv << "lt" << endl;
        }

        void writeAnd() {
            outv << "and" << endl;
        }

        void writeOr() {
            outv << "or" << endl;
        }

        void writeSub() {
            outv << "sub" << endl;
        }
};

class CompilationEngine {
    vector<string> typesTks = {"int", "char", "boolean"};

    string className = "N/A";

    int currtk = 0;
    typetoken tk;
    typetoken pk;

    vector<string> tokenlist;

    int indentnum = 0;

    VMwriter VM;

    int labelcount = 0;

    stack<string> position;

    unordered_map<string, tableel> classTable;
    unordered_map<string, int> classTableCounts = {
        {"field", 0},
        {"static", 0}
    };

    unordered_map<string, tableel> subTable;
    int localcount = 0;

    unordered_map<string, string> functions;
    unordered_set<string> vfunctions;

    public:
        CompilationEngine(vector<string> paratokenlist) {
            tokenlist = paratokenlist;
        }

        void indent() {
            outf << string(indentnum * 2, ' ');
        }

        void enter(string where) {
            position.push(where);

            write("<" + where + ">");

            ++indentnum;
        }

        void exit() {
            --indentnum;
            
            write("</" + position.top() + ">");

            position.pop();
        }

        void write(string what) {
            indent();
            outf << what << endl;
        }

        void next(bool s = false) {
            string line = tokenlist[currtk];

            cout << "LINE " << line << endl;

            typetoken& set = (s ? pk : tk);

            int phase = 0;
            string extract = "";

            for (char i: line) {
                if (phase == 0) {
                    if (i == '<') {
                        continue;
                    } else if (i == '>') {
                        set.type = extract;

                        cout << "TYPE: " << extract << endl;
                        extract = "";
                        ++phase;
                    } else {
                        extract += i;
                    }
                } else {
                    extract += i;
                }
            }

            set.value = extract.substr(0, extract.length() - (set.type.length() + 3));
            set.fullt = line;

            cout << "VAL flex: " << extract << " substr: " << extract.substr(0, extract.length() - (set.type.length() + 3)) << endl;
            
            if (!s) {
                ++currtk;
            }
        }

        bool hasMoreTokens() {
            if (currtk == tokensize) {
                return false;
            } else if (currtk > tokensize) {
                throw runtime_error("Tokens overflowed");
            }
        }

        bool is_int(string s) {
            for (char i: s) {
                if ((char)i < '0' or (char)i > '9') {
                    return false;
                }
            }

            return true;
        }

        tableel findvar(string name) {
            if (subTable.find(name) != subTable.end()) {
                return subTable[name];
            } else if (classTable.find(name) != classTable.end()) {
                return classTable[name];
            } else {
                throw runtime_error("Identifier not initialized: " + name);
            }
        }

        // Program Structure

        bool wordChecker(vector<string> words, string word) {
            for (int i = 0; i < words.size(); ++i) {
                if (words[i] == word) {
                    return true;
                }
            }

            return false;
        }

        void check(string check, string expected) {
            if (check != expected) {
                throw runtime_error("Expected a " + expected + ", got " + check);
            }

            write(tk.fullt);

            next();
        }

        int compileVarDec() {
            enter("varDec");
            string name, type;

            int amt = 1;

            check(tk.value, "var");

            if (!wordChecker(typesTks, tk.value) and tk.type != "identifier") {
                throw runtime_error("Expected a type, got " + tk.value);
            }

            type = tk.value;

            write(tk.fullt);
            next();

            name = tk.value;

            check(tk.type, "identifier");

            subTable.emplace(name, tableel{type, "local", localcount});

            ++localcount;

            while (tk.value == ",") {
                write(tk.fullt);
                next();

                subTable.emplace(tk.value, tableel{type, "local", localcount});
                ++localcount;

                ++amt;

                check(tk.type, "identifier");
            }

            check(tk.value, ";");

            printtable(subTable);

            exit();

            return amt;
        }

        void compileClassVarDec() {
            enter("classVarDec");

            string name, kind, type;

            if (!(tk.value == "field" or tk.value == "static")) {
                throw runtime_error("Expected a field or a static varable declaration, got " + tk.value);
            }

            kind = tk.value;

            write(tk.fullt);
            next();

            if (!wordChecker(typesTks, tk.value) and tk.type != "identifier") {
                throw runtime_error("Expected a type, got " + tk.value);
            }

            type = tk.value;

            write(tk.fullt);
            next();

            name = tk.value;

            check(tk.type, "identifier");

            if (kind == "field") {
                kind = "this";
            }

            classTable.emplace(name, tableel{type, kind, classTableCounts[kind]});
            ++classTableCounts[kind];

            while (tk.value == ",") {
                write(tk.fullt);
                next();

                classTable.emplace(tk.value, tableel{type, kind, classTableCounts[kind]});
                ++classTableCounts[kind];

                check(tk.type, "identifier");
            }

            printtable(classTable);

            check(tk.value, ";");

            exit();
        }

        void compileSubroutineDec() {
            enter("subroutineDec");

            int varnumber = 0;

            string kind, type, name;

            if (!wordChecker({"method", "constructor", "function"}, tk.value)) {
                throw runtime_error("Expected a subroutine declaration, got " + tk.value);
            }

            write(tk.fullt);

            kind = tk.value;

            next();

            if (wordChecker(vector<string>({"int", "char", "boolean", "void"}), tk.value) or tk.type == "identifier") {
                write(tk.fullt);
            } else {
                throw runtime_error("Expected a type, got " + tk.value);
            }

            type = tk.value;

            next();

            name = tk.value;

            functions[name] = kind;

            if (type == "void") {
                vfunctions.insert(name);
            }

            check(tk.type, "identifier");
            check(tk.value, "(");

            compileParameterList(kind == "method");

            check(tk.value, ")");

            // SUBROUTINE BODY STARTING

            enter("subroutineBody");

            check(tk.value, "{");

            int varnum = 0;

            while (tk.value == "var") {
                varnum += compileVarDec();
            }

            // SUBROUTINE BODY END, CONTINUING IN THE RESPECTIVE FUNCTION

            VM.writeFunction(className + "." + name, varnum);

            if (kind == "constructor") {
                VM.writePush("constant", classTableCounts["this"]);
                VM.writeCall("Memory.alloc", 1);
                VM.writePop("pointer", 0);
            }

            if (kind == "method") {
                VM.writePush("argument", 0);
                VM.writePop("pointer", 0);
            }

            compileSubroutineBody();

            subTable = {};
            localcount = 0;

            exit();
        }

        void compileParameterList(bool mtd) {
            enter("parameterList");

            string name, type;

            int argc = 0;

            if (mtd) {
                ++argc;
            }

            if ((wordChecker(typesTks, tk.value) or tk.type == "identifier")) {
                write(tk.fullt);

                type = tk.value;

                next();

                name = tk.value;

                check(tk.type, "identifier");

                subTable.emplace(name, tableel{type, "argument", argc});
            }

            ++argc;

            while (tk.value == ",") {
                write(tk.fullt);
                next();

                if ((wordChecker(typesTks, tk.value) or tk.type == "identifier")) {
                    write(tk.fullt);

                    type = tk.value;

                    next();

                    name = tk.value;
    
                    check(tk.type, "identifier");

                    subTable.emplace(name, tableel{type, "argument", argc});

                    ++argc;
                }
            }

            printtable(subTable);

            exit();
        }

        void compileSubroutineBody() {

            if (tk.value != "}") {
                compileStatements();
            } else {
                write(tk.fullt);
                next();
                return;
            }

            check(tk.value, "}");

            exit();
        }

        // Statement Compilation

        void compileIfStatement() {
            enter("ifStatement");

            check(tk.value, "if");
            check(tk.value, "(");

            compileExpression();
            check(tk.value, ")");
            check(tk.value, "{");

            int conserve = labelcount;
            ++labelcount;

            VM.writeNot();
            VM.writeIfGoto("if_label_end_" + to_string(conserve));

            compileStatements();

            VM.writeGoto("full_if_label_end_" + to_string(conserve));
            check(tk.value, "}");

            VM.writeLabel("if_label_end_" + to_string(conserve));

            if (tk.value == "else") {
                check(tk.value, "else");
                check(tk.value, "{");

                compileStatements();
                check(tk.value, "}");
            }

            VM.writeLabel("full_if_label_end_" + to_string(conserve));

            exit();
        }

        void compileLetStatement() {
            enter("letStatement");

            check(tk.value, "let");

            string name = tk.value;
            tableel info;

            check(tk.type, "identifier");

            info = findvar(name);

            bool arrass = false;

            if (tk.value == "[") {
                arrass = true;

                VM.writePush(info.kind, info.index);

                check(tk.value, "[");
                compileExpression();
                check(tk.value, "]");

                VM.writeAdd();
            }

            check(tk.value, "=");
            compileExpression();

            if (arrass) {
                VM.writePop("temp", 0);
                VM.writePop("pointer", 1);
                VM.writePush("temp", 0);
                VM.writePop("that", 0);
            } else {
                VM.writePop(info.kind, info.index);
            }

            check(tk.value, ";");

            exit();
        }

        void compileWhileStatement() {
            enter("whileStatement");

            check(tk.value, "while");
            check(tk.value, "(");

            string conserve = to_string(labelcount);
            ++labelcount;

            VM.writeLabel("while_start_" + conserve);

            compileExpression();

            VM.writeNot();
            VM.writeIfGoto("while_end_" + conserve);

            check(tk.value, ")");
            check(tk.value, "{");
            compileStatements();
            check(tk.value, "}");

            VM.writeGoto("while_start_" + conserve);

            VM.writeLabel("while_end_" + conserve);

            exit();
        }

        void compileDoStatement() {
            enter("doStatement");

            check(tk.value, "do");
            compileSubroutineCall();

            VM.writePop("temp", 0);

            check(tk.value, ";");

            exit();
        }

        void compileReturnStatement() {
            enter("returnStatement");

            check(tk.value, "return");

            if (tk.value != ";") {
                compileExpression();
            } else {
                VM.writePush("constant", 0);
            }

            VM.writeReturn();

            check(tk.value, ";");

            exit();
        }

        void compileStatement() {
            if (tk.value == "let") {
                compileLetStatement();
            } else if (tk.value == "if") {
                compileIfStatement();
            } else if (tk.value == "while") {
                compileWhileStatement();
            } else if (tk.value == "do") {
                compileDoStatement();
            } else if (tk.value == "return") {
                compileReturnStatement();
            } else {
                throw runtime_error("Expected a statement keyword, got " + tk.value);
            }
        }

        void compileStatements() {
            enter("statements");

            vector<string> stkeys = {"if", "let", "while", "do", "return"};

            while (wordChecker(stkeys, tk.value)) {
                compileStatement();
            }

            exit();
        }

        // Expressions

        void compileTerm() {
            enter("term");

            stack<string> urnops;

            while (tk.value == "-" or tk.value == "~") {
                write(tk.fullt);

                urnops.push(tk.value);

                next();
            }

            if (tk.type == "symbol" and tk.value != "(") {
                throw runtime_error("Expected an open bracket, constant, variable name or an urnary operator, got " + tk.value);
            } else if (tk.value == "(") {
                write(tk.fullt);
                next();

                compileExpression();

                check(tk.value, ")");
            } else if (tk.type == "identifier") {
                next(1);

                string name = tk.value;

                if (pk.value == "(" or pk.value == ".") {
                    compileSubroutineCall();
                } else {
                    tableel info = findvar(name);
                
                    if (pk.value == "[") {
                        write(tk.fullt);
                        next();

                        VM.writePush(info.kind, info.index);

                        check(tk.value, "[");

                        compileExpression();

                        check(tk.value, "]");

                        VM.writeAdd();
                        VM.writePop("pointer", 1);
                        VM.writePush("that", 0);
                    } else {
                        write(tk.fullt);

                        VM.writePush(info.kind, info.index);

                        next();
                    }
                }
            } else {
                write(tk.fullt);

                if (is_int(tk.value)) {
                    VM.writePush("constant", stoi(tk.value));
                } else if (tk.value == "true") {
                    VM.writePush("constant", 0);
                    VM.writeNot();
                } else if (tk.value == "false" or tk.value == "null") {
                    VM.writePush("constant", 0);
                } else if (tk.value == "this") {
                    VM.writePush("pointer", 0);
                } else {
                    VM.writePush("constant", tk.value.length());
                    VM.writeCall("String.new", 1);
                    
                    for (char i: tk.value) {
                        VM.writePush("constant", i);
                        VM.writeCall("String.appendChar", 2);
                    }
                }

                next();
            }

            while (!urnops.empty()) {
                string currop = urnops.top();
                urnops.pop();

                if (currop == "-") {
                    VM.writeNeg();
                } else {
                    VM.writeNot();
                }
            }

            exit();
        }

        void compileExpression() {
            enter("expression");

            compileTerm();

            vector<string> ops = {"+", "-", "*", "/", "&", "|", "<", ">", "="};

            while (wordChecker(ops, tk.value)) {
                write(tk.fullt);

                string op = tk.value;

                next();

                compileTerm();

                if (op == "+") {
                    VM.writeAdd();
                } else if (op == "-") {
                    VM.writeSub();
                } else if (op == "*") {
                    VM.writeCall("Math.multiply", 2);
                } else if (op == "/") {
                    VM.writeCall("Math.divide", 2);
                } else if (op == "&") {
                    VM.writeAnd();
                } else if (op == "|") {
                    VM.writeOr();
                } else if (op == "<") {
                    VM.writeLt();
                } else if (op == ">") {
                    VM.writeGt();
                } else {
                    VM.writeEq();
                }
            }

            exit();
        }

        int compileExpressionList() {
            enter("expressionList");

            int num = 0;
            
            if (tk.type != "symbol" or tk.value == "-" or tk.value == "~" or tk.value == "(") {
                compileExpression();

                ++num;

                while (tk.value == ",") {
                    check(tk.value, ",");

                    compileExpression();

                    ++num;
                }
            }

            exit();

            return num;
        }

        void compileSubroutineCall() {
            string name = tk.value;
            string funcname;

            check(tk.type, "identifier");

            bool mtd = false;

            if (tk.value == ".") {
                mtd = true;

                check(tk.value, ".");

                funcname = tk.value;

                check(tk.type, "identifier");
            }

            check(tk.value, "(");

            int argc = 0;

            tableel info;

            bool constr = false;

            if (mtd) {
                try {
                    info = findvar(name);
                    VM.writePush(info.kind, info.index);
                    ++argc;
                } catch (runtime_error _) {
                    cout << "Defaulted to constructor";
                    constr = true;
                }
            }

            argc += compileExpressionList();

            if (mtd) {
                if (constr) {
                    VM.writeCall(name + "." + funcname, argc);
                } else {
                    VM.writeCall(info.type + "." + funcname, argc);
                }
            } else {
                VM.writeCall(className + "." + name, argc);
            }

            check(tk.value, ")");
        }

        // Main

        void compileClass() {
            enter("class");

            check(tk.value, "class");

            className = tk.value;

            check(tk.type, "identifier");
            check(tk.value, "{");

            while (wordChecker(typesTks, tk.value) or tk.value == "static" or tk.value == "field" or tk.type == "identifier") {
                compileClassVarDec();
            }

            while (wordChecker(vector<string>({"function", "method", "constructor"}), tk.value)) {
                compileSubroutineDec();
            }

            check(tk.value, "}");

            exit();
        }
};

void compileFile(string path) {
    in = ifstream(path);

    string line;

    vector<string> tokens;

    fs::path ftpath = fs::path(path);

    string parsedfpath = (ftpath.parent_path() / "parsed" / ftpath.filename()).string();

    string tokenpath = parsedfpath.substr(0, parsedfpath.find_last_of(".")) + "TOKENS.xml";

    outt = ofstream(tokenpath);

    while (getline(in, line)) {
        vector<string> tknzdline = tokenizeLine(line);

        tokensize += tknzdline.size();

        for (string token: tknzdline) {
            outt << token << endl;
            tokens.push_back(token);
        }
    }

    tokens.push_back("OVERFLOW");

    string parsepath = parsedfpath.substr(0, parsedfpath.find_last_of(".")) + ".xml";

    outf = ofstream(parsepath);

    string VMpath = path.substr(0, path.find_last_of(".")) + ".vm";

    outv = ofstream(VMpath);

    CompilationEngine comp = CompilationEngine(tokens);
    
    comp.next();
    comp.compileClass();
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        throw runtime_error("Compiler didn't initialize, you must provide exactly 1 file/folder");
    }

    fs::file_status st = fs::status(argv[1]);

    if (fs::is_directory(st)) {
        fs::create_directory(fs::path(argv[1]) / "parsed");

        for (fs::directory_entry entry: fs::directory_iterator(argv[1])) {
            if (entry.path().string().find(".jack") != string::npos) {
                compileFile(entry.path().string());
            }
        }
    } else {
        fs::create_directory(fs::path(argv[1]).parent_path() / "parsed");

        compileFile(argv[1]);
    }
}