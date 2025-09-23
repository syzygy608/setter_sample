#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <filesystem>
#include <vector>
using namespace std;
namespace fs = std::filesystem;

void error(const string &message) {
    cerr << "\033[1;31m" << message << "\033[0m" << endl; // 使用紅色字體
    exit(0);
}

void open_file(ifstream &finput, const string &input_path) {
    finput.open(input_path, ios::in);
    if(!finput) 
        error("cannot open input file " + input_path);
}

void check(ifstream &finput, const string &input_path) {
    long long a;

    cerr << "checking file " << input_path << endl;

    if(!(finput >> a))
        error("input error, missing a");

    if(a < 1 || a > 1'000'000'000'000'000'000)
        error("a out of range");
    string check;
    if(finput >> check)
        error("too many input");
    cerr << "ok" << endl;
}

void close_file(ifstream &finput) {
    finput.close();
}

int main() {
    vector<string> directories = {"../data/secret/", "../data/sample/"};
    vector<string> input_files;

    for (const auto &dir : directories)
        for (const auto &entry : fs::directory_iterator(dir))
            if (entry.path().extension() == ".in")
                input_files.push_back(entry.path().string());

    for (const auto &input_path : input_files) {
        ifstream finput;
        open_file(finput, input_path);
        check(finput, input_path);
        close_file(finput);
    }

    return 0;
}