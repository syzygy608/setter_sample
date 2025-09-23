#include<fstream>
#include<iostream>
#include<random>
#include<ctime>
using namespace std;

const int N = 7;
const int len = to_string(N).length() + 1;

string fix_len(int t_case) {
    string s = to_string(t_case);
    while(s.length() < len)
        s = "0" + s;
    return s;
}

void open_input(ofstream &fout, int t_case) {
    string dir_path = "../data/secret/";
    string file_name = fix_len(t_case) + ".in";
    string input_path = dir_path + file_name;
    fout.open(input_path, ios::out | ios::trunc);
    if(!fout) {
        cerr << "cannot open file" << input_path << endl;
        exit(1);
    }
    cerr << "making file " << file_name << endl;
}

default_random_engine gen(time(NULL));
uniform_int_distribution<int> unif(0, numeric_limits<int>::max());
uniform_int_distribution<long long> unifll(0, numeric_limits<long long>::max());
uniform_real_distribution<double> unifd(0, 1);

void make_input(ofstream &fout, int t_case) {
    if(t_case <= 4) {
        // small
        int num1 = unif(gen) % 100 + 1;
        fout << num1 << '\n';
    } else if(t_case == 5) {
        // extreme
        fout << "1000000000000000000" << '\n';
    } else {
        // normal
        long long num1 = unifll(gen) % 1'000'000'000'000'000'000 + 1;
        fout << num1 << '\n';
    }
}
void close_input(ofstream &fout, int t_case) {
    fout.close();
}
int main() {
    for(int i = 1; i <= N; i++) {
        ofstream fout;
        open_input(fout, i);
        make_input(fout, i);
        close_input(fout, i);
    }
    return 0;
}
