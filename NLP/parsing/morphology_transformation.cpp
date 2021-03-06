#include <cstdio>
#include <cstring>
#include <map>
#include <iostream>
#include "morphology_transformation.h"
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
map<string,string> nounmap, verbmap, word2translation;
map<string, bool> missmap;

void loadDic() {
    FILE *fp = fopen("dic_ec.txt", "r");
    char line[500];
    string t[15];
    int len, cnt;
    while (fgets(line, 500, fp) != NULL) {
        len = 0;
        split(string(line), t, len);
        cnt = 2;
        word2translation[t[0]] = t[1];
        while(cnt < len)
            word2translation[t[0]] += '\t' + t[cnt++];
        len = 0;
    }
    fclose(fp);
    return;
}

void loadIrNoun() {
    FILE *fp = fopen("irregular nouns.txt", "r");
    char line[200];
    string t[2];
    int len = 0;
    while(fgets(line, 200 , fp) != NULL) {
        split(string(line), t , len);
        nounmap[t[1]] = t[0];
        len = 0;
    }
    fclose(fp);
    return;
}

void loadIrVerb() {
    FILE *fp = fopen("irregular verbs.txt", "r");
    char line[200];
    string t[15];
    int len = 0,cnt;
    while (fgets(line, 200, fp) != NULL) {
        split(string(line), t, len);
        cnt = 1;
        while (cnt < len)
            verbmap[t[cnt++]] = t[0];
        len = 0;
    }
    fclose(fp);
    return;
}

void loadMiWord() {
    FILE *fp = fopen("missing word.txt", "r");
    char line[50];
    while (fscanf(fp, "%s", line) != EOF)
        missmap[string(line)] = true;
    fclose(fp);
    return;
}

bool regularTrans(string word, string &res, map<string, string> wordmap) {
    bool flag = false;
    if (word.substr(word.length() - 1, 1) == "s"){
        if (word.length() > 3 && word.substr(word.length() - 3, 2) == "ie")
            if (wordmap.find(word.substr(0, word.length() - 3) + "y") != wordmap.end()) {
                flag = true;
                string skey = word.substr(0, word.length() - 3) + "y";
                res = skey + '\t' + wordmap[skey];
            }
        if (!flag && word.length() > 3 && word.substr(word.length() - 3, 2) == "ve")
            if (wordmap.find(word.substr(0, word.length() - 3) + "fe") != wordmap.end()) {
                flag = true;
                string skey = word.substr(0, word.length() - 3) + "fe";
                res = skey + '\t' + wordmap[skey];
            } else if (wordmap.find(word.substr(0, word.length() - 3) + "f") != wordmap.end()) {
                flag = true;
                string skey = word.substr(0, word.length() - 3) + "f";
                res = skey + '\t' + wordmap[skey];
            }
        if (!flag && word.length() > 2 && word.substr(word.length() - 2, 1) == "e")
            if (wordmap.find(word.substr(0, word.length() - 2)) != wordmap.end()) {
                flag = true;
                string skey = word.substr(0, word.length() - 2);
                res = skey + '\t' + wordmap[skey];
            }
        if (!flag && word.length() > 1)
            if (wordmap.find(word.substr(0, word.length() - 1)) != wordmap.end()) {
                flag = true;
                string skey = word.substr(0, word.length() - 1);
                res = skey + '\t' + wordmap[skey];
            }
    }

    if (!flag && word.length() > 2 && word.substr(word.length() - 2, 2) == "ed") {
        if (word.length() > 3 && word.substr(word.length() - 3, 1) == "i")
            if (wordmap.find(word.substr(0, word.length() - 3) + "y") != wordmap.end()) {
                flag = true;
                string skey = word.substr(0, word.length() - 3) + "y";
                res = skey + '\t' + wordmap[skey];
            }
        if (!flag && word.length() > 2)
            if (wordmap.find(word.substr(0, word.length() - 1)) != wordmap.end()) {
                flag = true;
                string skey = word.substr(0, word.length() - 1);
                res = skey + '\t' + wordmap[skey];
            } else if (wordmap.find(word.substr(0, word.length() - 2)) != wordmap.end()) {
                flag = true;
                string skey = word.substr(0, word.length() - 2);
                res = skey + '\t' + wordmap[skey];
            }
        if (!flag && word.length() > 4)
            if (wordmap.find(word.substr(0, word.length() - 3)) != wordmap.end()) {
                flag = true;
                string skey = word.substr(0, word.length() - 3);
                res = skey + wordmap[skey];
            }
    }

    if (!flag && word.length() > 3 && word.substr(word.length() - 3, 3) == "ing") {
        if (word.length() > 4 && word.substr(word.length() - 4, 1) == "y")
            if (wordmap.find(word.substr(0, word.length() - 4) + "ie") != wordmap.end()) {
                flag = true;
                string skey = word.substr(0, word.length() - 4) + "ie";
                res = skey + wordmap[skey];
            }
        if (!flag && word.length() > 3)
            if (wordmap.find(word.substr(0, word.length() - 3) + "e") != wordmap.end()) {
                flag = true;
                string skey = word.substr(0, word.length() - 3) + "e";
                res = skey + '\t' + wordmap[skey];
            } else if (wordmap.find(word.substr(0, word.length() - 3)) != wordmap.end()) {
                flag = true;
                string skey = word.substr(0, word.length() - 3);
                res = skey + '\t' + wordmap[skey];
            }
        if (!flag && word.length() > 5)
            if (wordmap.find(word.substr(0, word.length() - 4)) != wordmap.end()) {
                flag = true;
                string skey = word.substr(0, word.length() - 4);
                res = skey + '\t' + wordmap[skey];
            }
    }
    return flag;
}


// int main(){
//    ios::sync_with_stdio(false);
//    loadMiWord();
//    loadDic();
//    loadIrNoun();
//    loadIrVerb();
//    string word, res;
//    FILE *fp = fopen("missing word.txt", "a");
//    while (1) {
//        cout << "请输入查询单词(输入q!退出查询): ";
//        cin >> word;
//        if (word == "q!"){
//            cout << "退出";
//            break;
//        }
//        bool flag = false;
//        int cnt = 0;
//        if (word2translation.count(word) > 0) {
//            flag = true;
//            cnt++;
//            cout << cnt << ". " + word + '\t' + word2translation[word] << endl;
//        }
//        if (regularTrans(word, res, word2translation)) {
//            flag = true;
//            cnt++;
//            cout << cnt << ". " + res << endl;
//        }
//        if (nounmap.count(word) > 0 && word2translation.count(nounmap[word]) > 0) {
//            flag = true;
//            cnt++;
//            cout << cnt << ". " + nounmap[word] + '\t' + word2translation[nounmap[word]] << endl;
//        }
//        if (verbmap.count(word) > 0 && word2translation.count(verbmap[word]) > 0) {
//            flag = true;
//            cnt++;
//            cout << cnt << ". " + verbmap[word] + '\t' + word2translation[verbmap[word]] << endl;
//        }
//        if(!flag) {
//            cout << "对不起，未查询到相关单词！" << endl;
//            if (missmap.count(word) == 0 && word.length() < 50) {
//               fprintf(fp, "%s\n", word.c_str());
//               missmap[word] == true;
//            }
//        }
//    }
//    fclose(fp);
//    return 0;
// }