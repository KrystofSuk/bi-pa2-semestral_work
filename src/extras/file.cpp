#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include "file.h"

using namespace std;

namespace Extra{            
    const vector<string> & File::LoadFromFile(const string &  fileName){
        vector<string> fields;
        std::ifstream inp ( fileName );
        if( !inp.is_open() || !inp.good() ){
            inp.close();
            return fields;
        }
        string field;
        string val;
        while (inp >> field >> val) 
        {
            fields.push_back(val);
            if( !inp.is_open() || !inp.good() ){
                inp.close();
                return fields;
            }
        }
        return fields;
    }       

    const int File::LoadFromFile(const string &  fileName, const string &  fieldName){
        int val = 0;
        std::ifstream inp ( fileName );
        if( !inp.is_open() || !inp.good() ){
            inp.close();
            return val;
        }
        string field;
        while (inp >> field >> val) 
        {
            if(field == fieldName){
                inp.close();
                return val;
            }
            if( !inp.is_open() || !inp.good() ){
                inp.close();
                return val;
            }
        }
        inp.close();
        return val;
    }
}