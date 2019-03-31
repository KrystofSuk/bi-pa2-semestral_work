#ifndef FILE_H
#define FILE_H

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>

using namespace std;

namespace Extra
{
    template <typename T>
    class File{
        private:
        public:
            static const vector<T> LoadFromFile(const string & fileName){
                vector<T> fields;
                std::ifstream inp ( fileName );
                if( !inp.is_open() || !inp.good() ){
                    inp.close();
                    return fields;
                }
                string field;
                T val;
                while (inp >> field >> val) 
                {
                    fields.push_back(val);
                    if( !inp.is_open() || !inp.good() ){
                        inp.close();
                        return fields;
                    }
                }
                inp.close();
                return fields;
            }

            static const T LoadFromFile(const string & fileName, const string & fieldName){
                T val;
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
    };
}
#endif