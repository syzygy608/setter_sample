#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <random>
#include <filesystem>
#include <chrono>

using namespace std;
namespace fs = std::filesystem;

// ================= 設定區 =================
const int N = 10; // 測資筆數
const string OUTPUT_DIR = "../data/secret/";

// 亂數引擎
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

// 整數亂數 [l, r]
long long rand_ll(long long l, long long r) {
    return uniform_int_distribution<long long>(l, r)(rng);
}

// 浮點數亂數 [l, r)
double rand_double(double l, double r) {
    return uniform_real_distribution<double>(l, r)(rng);
}

// ================= 生成邏輯區 =================
void generate(ofstream &out, int case_id) {
    // 設定輸出小數點位數 (固定顯示小數點後 2 位)
    // 如果這題全是小數，可以在這裡設一次；如果混用，建議在輸出前設定
    // out << fixed << setprecision(2);

    if (case_id <= 3) {
        int val = rand_ll(1, 100); // 整數測資：生成 1 ~ 100 之間的亂數
        out << val << "\n";
    } 
    else if (case_id == N) {
        long long val = 1'000'000'000'000'000'000;
        out << val << "\n";
    } 
    else {
        long long val = rand_ll(1, 1'000'000'000'000'000'000); // 大整數測資
        out << val << "\n";
    }
}

// ================= 主程式 (無須更動) =================
int main() {
    if (!fs::exists(OUTPUT_DIR)) {
        fs::create_directories(OUTPUT_DIR);
        cerr << "Created directory: " << OUTPUT_DIR << endl;
    }

    int width = to_string(N).length() + 1;

    for (int i = 1; i <= N; i++) {
        stringstream ss;
        ss << setfill('0') << setw(width) << i << ".in";
        string filename = ss.str();
        string path = OUTPUT_DIR + filename;

        ofstream fout(path);
        if (!fout) {
            cerr << "Error opening " << path << endl;
            return 1;
        }

        generate(fout, i);
        cerr << "Generated: " << filename << endl;
        fout.close();
    }
    return 0;
}