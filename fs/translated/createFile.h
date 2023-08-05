#if !defined(L0_CREATEFILE_H)

#define L0_CREATEFILE_H

#include <string>
#include <fstream>

namespace fs
{
    namespace translated
    {
        void CreateFile(std::string name)
        {
            std::ofstream file(name.c_str());
            file.close();
        }
    } // #translated
} // #fs

#endif