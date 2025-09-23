#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
using namespace std;
namespace fs = std::filesystem;

void open_file(ifstream &finput, ofstream &foutput, const string &input_path, const string &output_path) {
    finput.open(input_path);
    foutput.open(output_path);
    if(!finput) {
        cerr << "cannot open input file " << input_path << endl;
        exit(1);
    }
    if(!foutput) {
        cerr << "cannot open output file " << output_path << endl;
        exit(1);
    }
    cerr << "generating file " << output_path << endl;
}

void solve(ifstream &finput, ofstream &foutput) {
    long long a;
    finput >> a;
    if(a % 4 == 0)
        foutput << a << '\n';
    else if(a % 4 == 1)
        foutput << 1 << '\n';
    else if(a % 4 == 2)
        foutput << a + 1 << '\n';
    else
        foutput << 0 << '\n';
}

void close_file(ifstream &finput, ofstream &foutput) {
    finput.close();
    foutput.close();
}

int main() {
    vector<string> directories = {"../data/secret/", "../data/sample/"};
    vector<string> input_files;

    for (const auto &dir : directories)
        for (const auto &entry : fs::directory_iterator(dir))
            if (entry.path().extension() == ".in")
                input_files.push_back(entry.path().string());

    for (const auto &input_path : input_files) {
        string output_path = input_path.substr(0, input_path.find_last_of('.')) + ".ans";
        ifstream finput;
        ofstream foutput;
        open_file(finput, foutput, input_path, output_path);
        solve(finput, foutput);
        close_file(finput, foutput);
    }

    return 0;
}