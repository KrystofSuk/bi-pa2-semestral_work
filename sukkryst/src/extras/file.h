#ifndef FILE_H
#define FILE_H

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include <dirent.h>

using namespace std;

namespace Extra
{
template <typename T>
class File
{
public:
    static const vector<T> LoadFromFileClean(const string &fileName)
    {
        vector<T> fields;
        ifstream inp(fileName, ios::binary);
        if (!inp.is_open() || !inp.good())
        {
            inp.close();
            return fields;
        }
        T val;
        while (inp >> val)
        {
            fields.push_back(val);
            if (!inp.is_open() || !inp.good())
            {
                inp.close();
                return fields;
            }
        }
        inp.close();
        return fields;
    }

    static const vector<T> LoadFromFile(const string &fileName)
    {
        vector<T> fields;
        ifstream inp(fileName);
        if (!inp.is_open() || !inp.good())
        {
            inp.close();
            return fields;
        }
        string field;
        T val;
        while (inp >> field >> val)
        {
            fields.push_back(val);
            if (!inp.is_open() || !inp.good())
            {
                inp.close();
                return fields;
            }
        }
        inp.close();
        return fields;
    }

    static const T LoadFromFile(const string &fileName, const string &fieldName)
    {
        T val;
        ifstream inp(fileName);
        if (!inp.is_open() || !inp.good())
        {
            inp.close();
            return val;
        }
        string field;
        while (inp >> field >> val)
        {
            if (field == fieldName)
            {
                inp.close();
                return val;
            }
            if (!inp.is_open() || !inp.good())
            {
                inp.close();
                return val;
            }
        }
        inp.close();
        return val;
    }

    /*
    static const vector<T> GetFileNames(const string &dirName)
    {
        vector<T> res;
        DIR *dir;
        struct dirent *ent;
        if ((dir = opendir(dirName)) != NULL)
        {
            while ((ent = readdir(dir)) != NULL)
            {
                res.push_back(ent->d_name);
            }
            closedir(dir);
        }
        return res;
    }
    */
};
} // namespace Extra
#endif