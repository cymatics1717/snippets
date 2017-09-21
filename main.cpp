#include <iostream>
#include <sstream>
#include <vector>

std::string runlengthEncode1(const std::string &in){
    if(in.size()<2) return in;

    std::string buf;

    char c = in.at(0);
    int cnt = 1;
    size_t idx = 1;
    while (idx < in.size()) {

        while (idx < in.size() && in.at(idx)==c ) {
            cnt++;
            idx++;
        }
        /////////////////////////////
        buf.append(1,c);
        if(cnt>1) {
            buf.append(std::to_string(cnt));
        }
        /////////////////////////////
        if(idx < in.size()){
            c = in.at(idx);
        }
        cnt = 1;
        idx++;
    }
    buf.append(1,c);

    return buf;
}

std::string runlengthEncode2(const std::string &in){
    if(in.size()<2) return in;

    std::string buf;

    std::stringstream ss;
    ss<<in;

    char a;
    ss>>a;
    /////////////////////////////
    char b;
    while (ss>>b) {
        static int cnt = 1;
        if(a!=b){
            buf.append(1,a);
            if(cnt>1) {
                buf.append(std::to_string(cnt));
            }
            cnt = 1;
            a=b;
        } else {
            cnt++;
        }
    }
    buf.append(1,b);

    return buf;
}

std::string runlengthDecode(const std::string &in){
    std::string buf;

    std::stringstream ss;
    ss<<in;

    char c;
    while(ss>>c){
        size_t cnt;
        if(ss>>cnt){
            buf.append(cnt,c);
        } else {
            ss.clear();
            buf.append(1,c);
        }
    }

    return buf;
}

void printParenthesesList(std::string context,int v, int h, int n){
    static int cnt = 0;
    if(v==h){
       if(v<n){
           printParenthesesList(context+"(",v, h+1,n);
       } else {
           std::cout<<++cnt<<":" << context <<std::endl;
       }
    } else {
        if(h<n){
            printParenthesesList(context+"(",v, h+1,n);
        }
        printParenthesesList(context+")",v+1, h,n);
    }
}

int main()
{
    {
        std::string test = "aaasjjjjjffgddddsddffgrrrrf";
        std::cout <<test<<":\t"<< runlengthEncode1(test)<< std::endl;
    }
    {
        std::string test = "aaasjjjjjffgddddsddffgrrrrf";
        std::cout <<test<<":\t"<< runlengthEncode2(test)<< std::endl;
    }
    {
        std::string test = "a3sj5f2gd4sd2f2gr4f";
        std::cout <<test<<":\t"<< runlengthDecode(test)<< std::endl;
    }

    printParenthesesList("",0,0,10);

    return 0;
}
