#include <bits/stdc++.h>
#include <cctype>

using namespace std;

ifstream in;
ofstream outt("Tokens.xml");
ofstream outf;

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

class CompilationEngine {
    vector<string> typesTks = {"int", "char", "boolean"};

    int currtk = 0;
    typetoken tk;
    typetoken pk;

    vector<string> tokenlist;

    int indentnum = 0;

    stack<string> position;

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

        void compileVarDec() {
            enter("varDec");

            check(tk.value, "var");

            if (!wordChecker(typesTks, tk.value) and tk.type != "identifier") {
                throw runtime_error("Expected a type, got " + tk.value);
            }

            write(tk.fullt);
            next();

            check(tk.type, "identifier");

            while (tk.value == ",") {
                write(tk.fullt);
                next();

                check(tk.type, "identifier");
            }

            check(tk.value, ";");

            exit();
        }

        void compileClassVarDec() {
            enter("classVarDec");

            if (!(tk.value == "field" or tk.value == "static")) {
                throw runtime_error("Expected a field or a static varable declaration, got " + tk.value);
            }

            write(tk.fullt);
            next();

            if (!wordChecker(typesTks, tk.value) and tk.type != "identifier") {
                throw runtime_error("Expected a type, got " + tk.value);
            }

            write(tk.fullt);
            next();

            check(tk.type, "identifier");

            while (tk.value == ",") {
                write(tk.fullt);
                next();

                check(tk.type, "identifier");
            }

            check(tk.value, ";");

            exit();
        }

        void compileSubroutineDec() {
            enter("subroutineDec");

            if (!wordChecker({"method", "constructor", "function"}, tk.value)) {
                throw runtime_error("Expected a subroutine declaration, got " + tk.value);
            }

            write(tk.fullt);

            next();

            if (wordChecker(vector<string>({"int", "char", "boolean", "void"}), tk.value) or tk.type == "identifier") {
                write(tk.fullt);
            } else {
                throw runtime_error("Expected a type, got " + tk.value);
            }

            next();

            check(tk.type, "identifier");
            check(tk.value, "(");

            compileParameterList();

            check(tk.value, ")");

            compileSubroutineBody();

            exit();
        }

        void compileParameterList() {
            enter("parameterList");

            if ((wordChecker(typesTks, tk.value) or tk.type == "identifier")) {
                write(tk.fullt);
                next();

                check(tk.type, "identifier");
            }

            while (tk.value == ",") {
                write(tk.fullt);
                next();

                if ((wordChecker(typesTks, tk.value) or tk.type == "identifier")) {
                    write(tk.fullt);
                    next();
    
                    check(tk.type, "identifier");
                }
            }

            exit();
        }

        void compileSubroutineBody() {
            enter("subroutineBody");

            check(tk.value, "{");

            while (tk.value == "var") {
                compileVarDec();
            }

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
            compileStatements();
            check(tk.value, "}");

            if (tk.value == "else") {
                check(tk.value, "else");
                check(tk.value, "{");
                compileStatements();
                check(tk.value, "}");
            }

            exit();
        }

        void compileLetStatement() {
            enter("letStatement");

            check(tk.value, "let");
            check(tk.type, "identifier");

            if (tk.value == "[") {
                check(tk.value, "[");
                compileExpression();
                check(tk.value, "]");
            }

            check(tk.value, "=");
            compileExpression();
            check(tk.value, ";");

            exit();
        }

        void compileWhileStatement() {
            enter("whileStatement");

            check(tk.value, "while");
            check(tk.value, "(");
            compileExpression();
            check(tk.value, ")");
            check(tk.value, "{");
            compileStatements();
            check(tk.value, "}");

            exit();
        }

        void compileDoStatement() {
            enter("doStatement");

            check(tk.value, "do");
            compileSubroutineCall();
            check(tk.value, ";");

            exit();
        }

        void compileReturnStatement() {
            enter("returnStatement");

            check(tk.value, "return");

            if (tk.value != ";") {
                compileExpression();
            }

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

            while (tk.value == "-" or tk.value == "~") {
                write(tk.fullt);
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

                if (pk.value == "(" or pk.value == ".") {
                    compileSubroutineCall();
                } else if (pk.value == "[") {
                    write(tk.fullt);
                    next();

                    check(tk.value, "[");

                    compileExpression();

                    check(tk.value, "]");
                } else {
                    write(tk.fullt);
                    next();
                }
            } else {
                write(tk.fullt);
                next();
            }

            exit();
        }

        void compileExpression() {
            enter("expression");

            compileTerm();

            vector<string> ops = {"+", "-", "*", "/", "&", "|", "<", ">", "?", "="};

            while (wordChecker(ops, tk.value)) {
                write(tk.fullt);
                next();

                compileTerm();
            }

            exit();
        }

        void compileExpressionList() {
            enter("expressionList");
            
            if (tk.type != "symbol" or tk.value == "-" or tk.value == "~") {
                compileExpression();

                while (tk.value == ",") {
                    check(tk.value, ",");

                    compileExpression();
                }
            }

            exit();
        }

        void compileSubroutineCall() {
            check(tk.type, "identifier");

            if (tk.value == ".") {
                check(tk.value, ".");

                check(tk.type, "identifier");
            }

            check(tk.value, "(");

            compileExpressionList();

            check(tk.value, ")");
        }

        // Main

        void compileClass() {
            enter("class");

            check(tk.value, "class");
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

int main(int argc, char* argv[]) {
    if (argc != 2) {
        throw runtime_error("Compiler didn't initialize, you must provide exactly 1 file");
    }

    string path = argv[1];

    in = ifstream(path);

    string line;

    vector<string> tokens;

    string tokenpath = path.substr(0, path.find_last_of(".")) + "TOKENS.xml";

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

    string parsepath = path.substr(0, path.find_last_of(".")) + ".xml";

    outf = ofstream(parsepath);

    CompilationEngine tests = CompilationEngine(tokens);
    
    tests.next();
    tests.compileClass();
}