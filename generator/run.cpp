#include <iostream>
#include <filesystem>
#include <vector>
#include <string>
#include <cstdlib>

using namespace std;
namespace fs = std::filesystem;

// ================= 設定區 =================
const string SOL_DIR = "../submissions/accepted/";
const vector<string> DATA_DIRS = {"../data/secret/", "../data/sample/"};
const string TEMP_EXE = "temp_sol_exec"; // 暫存執行檔名

// ================= 主程式 =================
int main() {
    // 1. 尋找 Solution
    fs::path sol_path;
    bool found = false;

    if (fs::exists(SOL_DIR)) {
        for (const auto &entry : fs::directory_iterator(SOL_DIR)) {
            string ext = entry.path().extension().string();
            if (ext == ".cpp" || ext == ".c") {
                sol_path = entry.path();
                found = true;
                break;
            }
        }
    }

    if (!found) {
        cerr << "Error: No .c/.cpp found in " << SOL_DIR << endl;
        return 1;
    }
    cout << "Found solution: " << sol_path.filename() << endl;

    // 2. 編譯
    string cmd_compile;
    if (sol_path.extension() == ".cpp")
        cmd_compile = "g++ -O2 -std=c++20 \"" + sol_path.string() + "\" -o " + TEMP_EXE;
    else
        cmd_compile = "gcc -O2 -std=c17 \"" + sol_path.string() + "\" -o " + TEMP_EXE;

    if (system(cmd_compile.c_str()) != 0) {
        cerr << "Compilation failed." << endl;
        return 1;
    }

    // 3. 執行並產生輸出
    for (const auto &dir : DATA_DIRS) {
        if (!fs::exists(dir)) continue;
        for (const auto &entry : fs::directory_iterator(dir)) {
            if (entry.path().extension() == ".in") {
                string in_path = entry.path().string();
                string out_path = entry.path().parent_path().string() + "/" + entry.path().stem().string() + ".ans";
                
                cout << "Running: " << entry.path().filename() << " -> .ans" << endl;
                
                // ./temp_sol_exec < xx.in > xx.ans
                string run_cmd = "./" + TEMP_EXE + " < \"" + in_path + "\" > \"" + out_path + "\"";
                if (system(run_cmd.c_str()) != 0) {
                    cerr << "Runtime Error on " << in_path << endl;
                }
            }
        }
    }

    // 4. 清理
    fs::remove(TEMP_EXE);
    cout << "All outputs generated." << endl;
    return 0;
}