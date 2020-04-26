
#include "string_util.hpp"

namespace xutils::str {
    
    // 字符串替换  replace_all("12212", "12", "21")  原字串变为 21221 ， 返回 char*
    string replace_all(string& str,const string& old_value,const string& new_value){     
        for(string::size_type pos(0); pos!=string::npos; pos+=new_value.length()){     
            if((pos=str.find(old_value,pos))!=string::npos)     
                str.replace(pos,old_value.length(),new_value);     
            else{
                break;     
            }
        }     
        return str;     
    } 

    // 字符串替换  replace_all2("12212", "12", "21")  原字串变为 22211 ， 返回 char*
    string replace_all2(string& str,const string& old_value,const string& new_value){     
        while(true){     
            string::size_type pos(0);     
            if((pos=str.find(old_value))!=string::npos   )     
                str.replace(pos,old_value.length(),new_value);     
            else{
                break;     
            }
        }     
        return str;     
    }     
}



