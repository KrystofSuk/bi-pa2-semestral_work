#ifndef FILE_H
#define FILE_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <dirent.h>

namespace Extra
{
/**
 * @brief File not exist exception which will be thrown if specific files like units, config, or towers doesn't exists or are renamed mover an so on!
 * 
 */
class FileNotExistException
{
};
/**
 * @brief File class for managing and loading specific config files
 * 
 * @tparam T which parameter types are expected to be returned
 */
template <typename T>
class File
{
public:
    /**
     * @brief Binary file loading
     * 
     * @param fileName name of file
     * @return const std::vector<T> all fields with specific type
     */
    static const std::vector<T> LoadFromFileClean(const std::string &fileName)
    {
        std::vector<T> fields;
        std::ifstream inp(fileName, std::ios::binary);
        if (!inp.is_open() || !inp.good())
        {
            inp.close();
            throw(FileNotExistException());
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
    /**
     * @brief Same as LoadFromFileClean but for text files
     * 
     * @param fileName name of file
     * @return const std::vector<T> all fields with specific type
     */
    static const std::vector<T> LoadFromFile(const std::string &fileName)
    {
        std::vector<T> fields;
        std::ifstream inp(fileName);
        if (!inp.is_open() || !inp.good())
        {
            inp.close();
            throw(FileNotExistException());
            return fields;
        }
        std::string field;
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
    /**
     * @brief Loads only one field found by name
     * 
     * @param fileName name of file
     * @param fieldName name of field
     * @return const T value of field
     */
    static const T LoadFromFile(const std::string &fileName, const std::string &fieldName)
    {
        T val;
        std::ifstream inp(fileName);
        if (!inp.is_open() || !inp.good())
        {
            inp.close();
            throw(FileNotExistException());
            return val;
        }
        std::string field;
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
};

} // namespace Extra
#endif