#include <string>
#include <vector>
#include <fstream>

using namespace std;
namespace xutils::file{
    // 写文件
    void writeFile(string content, string file){
        // 1 包含头文件 #include <fstream>    
        // 2 创建流对象
        ofstream ofs;
        // 3 指定路径和打开方式 
        ofs.open(file, ios::out);
        // 4 写内容
        ofs << content;

        // 5 关闭文件
        ofs.close();
    }

    // 文件内容追加
    void appendFile(string content, string file){
        ofstream ofs;
        ofs.open(file, ios::app);
        ofs << content;
        ofs.close();
    }

    // // 读文件
    vector<string> readFile(string file){
        vector<string> result = {};
        string buf;
        ifstream ifs;
        // 打开文件 判断是否打开成功
        ifs.open(file, ios::in);

        // 该怎么处理打开失败呢？？
        // if (!ifs.is_open()) {
        //     cout << "文件打开失败！" << endl;
        //     return;
        // }

        while (getline(ifs, buf)) {
            result.push_back(buf);
        }
        return result;
    }
}