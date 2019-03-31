#ifndef FILE_H
#define FILE_H

#include <string>
#include <vector>

using namespace std;

namespace Extra
{
    class File{
        public:
            static const vector<string> & LoadFromFile(const string & fileName);
            static const int LoadFromFile(const string & fileName, const string & fieldName);
        private:
    };
}
#endif