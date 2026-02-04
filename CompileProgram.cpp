#include <bits/stdc++.h>
#include <filesystem>
#include <cstdlib>

using namespace std;
namespace fs = std::filesystem;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        throw runtime_error("you must provide exactly 1 file/directory");
    }

    string path = argv[1];
    fs::path patht = fs::path(path);
    fs::file_status pst = fs::status(path);

    ofstream out = (ofstream((fs::is_directory(pst)) ? "fullprogram.hack" : (fs::path(path).parent_path() / "fullprogram.hack")));
    ofstream outVM = (ofstream((fs::is_directory(pst)) ? "fullprogramVM.hack" : (fs::path(path).parent_path() / "fullprogramVM.hack")));

    if (fs::is_directory(pst)) {
        out = ofstream(patht / "fullprogram.hack");
        outVM = ofstream(patht / "fullprogramVM.hack");
    } else {
        out = ofstream(patht.parent_path() / "fullprogram.hack");
        outVM = ofstream(patht.parent_path() / "fullprogramVM.hack");
    }

    for (fs::directory_entry entry: fs::directory_iterator("./OS/")) {
        if (entry.path().extension() == ".hack" and entry.path().filename() != "fullprogram.hack") {
            ifstream in = ifstream(entry.path().string());

            out << in.rdbuf();
        }

        if (entry.path().extension() == ".vm" and entry.path().filename() != "fullprogramVM.hack") {
            ifstream in = ifstream(entry.path().string());

            outVM << in.rdbuf();
        }
    }

    string compileJackCM = "JackCompiler\\JackCompiler.exe " + path;
    string translateVMCM = "VMtranslator\\translator.exe " + path;
    string compileAssemblyCM = "AssemblerCompilerCpp\\AssemblyCompiler.exe " + path;

    system(compileJackCM.c_str());
    system(translateVMCM.c_str());
    system(compileAssemblyCM.c_str());

    if (fs::is_directory(pst)) {
        for (fs::directory_entry entry: fs::directory_iterator(path)) {
            if (entry.path().extension() == ".hack" and entry.path().filename() != "fullprogram.hack") {
                cout << "WRITING: " << entry.path().string();

                ifstream in = ifstream(entry.path().string());
    
                out << in.rdbuf();
            }

            if (entry.path().extension() == ".vm" and entry.path().filename() != "fullprogramVM.hack") {
                ifstream in = ifstream(entry.path().string());
    
                outVM << in.rdbuf();
            }
        }
    } else {
        ifstream in = ifstream(path);

        out << in.rdbuf();
        outVM << in.rdbuf();
    }
}