#include <iostream>
#include<fstream>
#include<string>

using namespace std;

int main(){

    enum{DISABLE,ENABLE};
    short choice;

    string setting_line;
    string temp;
    string proxy_enabled;

    proxy_enabled = "user_pref(\"network.proxy.type\"";
    const char* prefs_js = "C:/Users/hsolanki/AppData/Roaming/Mozilla/Firefox/Profiles/jc53vdeb.default/prefs.js";
    const char* temp_txt = "C:/Users/hsolanki/AppData/Roaming/Mozilla/Firefox/Profiles/jc53vdeb.default/temp.txt";

    ifstream settings_file(prefs_js);
    ofstream temp_file(temp_txt);

    cout << "0.Disable proxy\n1.Enable proxy\nEnter choice:";
    cin >> choice;

    if(settings_file.is_open()){
        while(getline(settings_file,setting_line)){
            //check if proxy is enabled or not and set flag
            if((setting_line.compare(0,30,proxy_enabled))==0){
                temp = setting_line;
                if(choice==ENABLE){
                    if(temp.find('1')==32){
                        cout << "proxy is already enabled";
                    }
                    else{
                        temp.replace(32,1,"1");
                        cout << "proxy enabled";
                    }
                }
                else{
                    if(temp.find('0')==32){
                        cout << "proxy is already disabled";
                    }
                    else{
                        temp.replace(32,1,"0");
                        cout << "proxy disabled";
                    }
                }
                setting_line = temp;
            }
            temp_file << setting_line << endl;
        }
        settings_file.close();
        temp_file.close();
        remove(prefs_js);
        rename(temp_txt,prefs_js);
    }
    else{
        cout << "unable to open file";
    }
    return 0;
}
