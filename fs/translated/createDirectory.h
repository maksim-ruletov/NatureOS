#if !defined(L0_CREATEDIRECTORY_H)

#define L0_CREATEDIRECTORY_H

#include <string>
#include <direct.h>

namespace fs
{
    namespace translated
    {
        void CreateDirectory(std::string name)
        {
            _mkdir(name.c_str());
        }
    } // #translated
} // #fs

#endif