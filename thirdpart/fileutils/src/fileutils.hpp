#pragma once

#include <string>
#include <vector>

using namespace std;
namespace xutils::file{
    // ===== readwrite.cpp =======================
    void writeFile(string content, string file);
    void appendFile(string content, string file);
    vector<string> readFile(string file);


    // ===== filestat.cpp =======================
    bool fileExist(string file);
}