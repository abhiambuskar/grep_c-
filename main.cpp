#include <iostream>
#include <algorithm>
#include <fstream>
#include <unistd.h>
#include <filesystem>
#include <string>
using namespace std;


std::string string_to_lower(std::string str){
    std::transform(
        str.begin(), str.end(), str.begin(),
        [](unsigned char c){return std::tolower(c);}
    );
    return str;
}


void search_files(std::string searchstring, std::string searchpath, bool ignorecase){
    ifstream input_files;
    string line;
    string search_line;

    for(const auto&file: std::filesystem::directory_iterator(searchpath)){
        input_files.open(file.path());

        if(input_files.is_open()){
            while((getline(input_files, line))){
                if(ignorecase){
                    search_line = string_to_lower(line);
                }else{
                    search_line = line;
                }

                if(search_line.find(searchstring) != std::string::npos){
                    cout<<line<<endl;
                }
            }
            input_files.close();
        }else{
            cout<<"Unable to open file"<<endl;
        }
    }
}

void search_output(std::string search_string, bool ignorecase){
    string inputline;
    string searchline;

    while(std::cin){
        getline(std::cin, inputline);
        if(ignorecase){
            searchline = string_to_lower(inputline);
        }else{
            searchline = inputline;
        }

        if(searchline.find(search_string) != std::string::npos){
            cout<<inputline<<endl;
        }
    }
}

int main(int argc, char** argv){
    bool ignorecase = false;
    string searchstring;
    string searchpath;
    int valid_agr_count = 2;

    if(string("-i").find(argv[1]) != std::string::npos){
        ignorecase = true;
        searchstring = string_to_lower(argv[2]);
        valid_agr_count++;
    }else{
        searchstring = argv[1];
    }

    if(!isatty(fileno(stdin))){
        search_output(searchstring, ignorecase);
    }else if(argc >= valid_agr_count){
        if(ignorecase){
            searchpath= argv[3];
        }else{
            searchpath = argv[2];
        }
        search_files(searchstring, searchpath, ignorecase);
    }else{
        cout<<"Not able to find the cararase"<<endl;
    }

    return 0;
}