// Siddharth Bisht (C++ 11)
#include<bits/stdc++.h>
#define input_from_file  freopen("input.txt", "r", stdin);
using namespace std;
int char_map[2][26];
bool hassol=false;

bool check(string crypt_str, string dict_str){
    int temp_map[2][26];
    memcpy(temp_map, char_map, sizeof(temp_map));

    for(int i=0;i<crypt_str.size();i++){
        if((char_map[0][dict_str[i]-'a']==50 && char_map[1][crypt_str[i]-'a']==50) || (char_map[0][dict_str[i]-'a']==crypt_str[i]-'a' && char_map[1][crypt_str[i]-'a']==dict_str[i]-'a')){
            char_map[0][dict_str[i]-'a']=crypt_str[i]-'a';
            char_map[1][crypt_str[i]-'a']=dict_str[i]-'a';
        }
        else{
            memcpy(char_map, temp_map, sizeof(char_map));
            return false;
        }
    }
    return true;
}

void dfs(int depth, vector<string>dict, vector<string>crypt, string input){
    if(hassol) return;
    if(depth==crypt.size()){
        hassol=true;
        for(int i=0;i<input.size();i++){
            if(input[i]-'a'>=0 && input[i]-'a'<=26){
                cout<<char(char_map[1][input[i]-'a']+'a');
            }
            else{
                cout<<" ";
            }
        }
        return;
    }
    int temp_map[2][26];
    memcpy(temp_map, char_map, sizeof(temp_map));

    for(int i=0;i<dict.size();i++){
        if(!hassol){
            memcpy(char_map, temp_map, sizeof(char_map));
            if((crypt[depth].size() == dict[i].size())){
                if(check(crypt[depth], dict[i])){
                    dfs(depth+1, dict, crypt, input);
                }
            }
        }
        else break;
    }
}

int main(){
    // input_from_file
    int n;
    cin>>n;
    vector<string>dict;
    for(int i=0;i<n;i++){
        string s;
        cin>>s;
        dict.push_back(s);
    }
    string input;
    cin.ignore();
    while(getline(cin, input)){
        for (int j=0; j<2; j++) for (int i=0; i<26; i++) char_map[j][i] = 50;
        vector<string>crypt;
        stringstream ss(input);
        string word;
        while(ss>>word){
            crypt.push_back(word);
        }
        hassol=false;
        dfs(0, dict, crypt, input);
        if(!hassol){
            for(int i=0;i<input.size();i++){
                if(input[i]-'a'>=0 && input[i]-'a'<=26) cout<<"*";
                else cout<<" ";
            }
        }
        cout<<endl;
    }
}