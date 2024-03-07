#include<bits/stdc++.h>
using namespace std;
void to_lower(char &c)
{
    c=(char)tolower(c);
}
void to_lowerstring(string &str)
{
    for(int i=0;i<str.length();++i)
    {
        str[i]=(char)tolower(str[i]);
    }
}
void Xuly_Name(vector<string> &Name,string &Ten)
{
    Ten="";
    for(int i=0;i<Name.size();++i)
    {
        if(i!=Name.size()-1)
        {
            to_lower(Name[i][0]);
            Ten=Ten+Name[i][0];
        }
        else{
            to_lowerstring(Name[i]);
            Ten=Name[i]+Ten;
        };
    }
    ;
}
void XuLy_Birth(string &Bot)
{
    string word,bit;
    stringstream ss(Bot);
    while(getline(ss,word,'/'))
    {
        bit=bit+word;
    }
    Bot=bit;
}
int main()
{
    string PhanViet,word,TKgmail;
    int So_sv;cin>>So_sv;cin.ignore();
    string DS_Sv[So_sv];
     for(int i=0;i<So_sv;++i)
     {
        getline(cin,PhanViet);
        DS_Sv[i]=PhanViet;
     }
    pair<string,string> TK_and_MK[So_sv];
    vector<string> Ten_Ngaysinh,Name;
    string Birth;
    // Sau   mỗi vòng forr nhớ clear vector "Ten_Ngaysinh,Name" 1294014124124
    for(int i=0;i<So_sv;++i)
    {
        stringstream ss(DS_Sv[i]);
        while(ss>>word)
        {
            Ten_Ngaysinh.push_back(word);
        }
        for(int i=0;i<Ten_Ngaysinh.size()-1;++i)
        {
            Name.push_back(Ten_Ngaysinh[i]);
        }
        Birth=(Ten_Ngaysinh[Ten_Ngaysinh.size()-1]);
        XuLy_Birth(Birth);
        Xuly_Name(Name,TKgmail);
        
        TK_and_MK[i].first=TKgmail;
        TK_and_MK[i].second=Birth;
        Ten_Ngaysinh.clear();
        Name.clear();
    }
    for(int i=0;i<So_sv;++i)
    {
        cout<<TK_and_MK[i].first<<" "<<TK_and_MK[i].second<<endl;
    }
}
