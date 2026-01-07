#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>
#include <algorithm>

using namespace std;
namespace fs = std::filesystem;

const vector<string> TARGET_DIRS = {"../data/secret/", "../data/sample/"};

void error(const string &msg) {
    cerr << "\033[1;31m[FAIL] " << msg << "\033[0m" << endl;
    exit(1);
}

void validate(ifstream &in) {
    long long n;
    
    // 1. 檢查是否讀得到 N
    if (!(in >> n)) error("Format error: missing integer N");
    
    // 2. 檢查範圍
    if (n < 1 || n > 1'000'000'000'000'000'000) 
        error("Range error: N out of bounds (" + to_string(n) + ")");

    // 3. 檢查 EOF (確保沒有多餘資料)
    string dummy;
    if (in >> dummy) error("Format error: extra content at end of file");
}

// ================= 主程式 (不需修改) =================
int main() {
    vector<string> files;
    
    // 蒐集所有 .in 檔案
    for (const auto &dir : TARGET_DIRS) {
        if (!fs::exists(dir)) continue;
        for (const auto &entry : fs::directory_iterator(dir)) {
            if (entry.path().extension() == ".in") {
                files.push_back(entry.path().string());
            }
        }
    }
    sort(files.begin(), files.end());

    bool all_pass = true;
    for (const auto &path : files) {
        ifstream fin(path);
        if (!fin) {
            cerr << "Cannot open " << path << endl;
            continue;
        }

        cerr << "Checking " << path << "... ";
        validate(fin);
        cerr << "\033[1;32mOK\033[0m" << endl; 
        fin.close();
    }

    return 0;
}