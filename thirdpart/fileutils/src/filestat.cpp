#include <string>
#include <fstream>

using namespace std;
namespace xutils::file{
    // 写文件
    bool fileExist(string file){ 
        ifstream f(file.c_str());
        return f.good();
    }

}