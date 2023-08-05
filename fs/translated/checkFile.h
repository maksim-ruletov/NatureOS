#if !defined(L0_CHECKFILE_H)

#define L0_CHECKFILE_H

#include <string>

namespace fs
{
    namespace translated
    {
        bool FileExists(std::string filename)
        {
            if (FILE* file = fopen(filename.c_str(), "r"))
            {
                fclose(file);

                return true;
            }
            else
            {
                return false;
            }
        }
    } // #translated
} // #fs

#endif