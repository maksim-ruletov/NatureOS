#if !defined(L0_CHECKDIRECTORY_H)

#define L0_CHECKDIRECTORY_H

#include <string>
#include <sys/types.h>
#include <sys/stat.h>

namespace fs
{
    namespace translated
    {
        bool DirectoryExist(std::string path)
        {
            struct stat info;

            if (stat(path.c_str(), &info) != 0)
            {
                return false;
            }
            else if (info.st_mode & S_IFDIR)
            {
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