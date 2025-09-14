#if !defined(L1_MAIN_H)

#define L1_MAIN_H

#include <string>
#include <vector>
#include <cstdint>

#include "../misc/Screen.h"
#include "../misc/Colorizer.h"

#include "../fs/translated.h"

namespace installer
{
    int CreateFileSystem(std::string installPreset)
    {
        if (installPreset.compare("f") != 0 && installPreset.compare("c") != 0)
        {
            return -1;
        }
        else
        {
            const std::vector<std::string> Markers {
                misc::ColorizeBackground("  ", 255, 50, 0), // error
                misc::ColorizeBackground("  ", 0, 255, 50), // success
                misc::ColorizeBackground("  ", 255, 255, 0), // warn
                misc::ColorizeBackground("  ", 0, 0, 255) // info
            };

            // Full Setup
            if (installPreset.compare("f") == 0)
            {
                for (std::string path : RequiredDirectories)
                {
                    if (!fs::translated::DirectoryExist(path))
                    {
                        misc::Output(Markers.at(3) + " >> Path " + path + " not found, creating...\n");
                        fs::translated::CreateDirectory(path);
                    }
                    else
                    {
                        misc::Output(Markers.at(1) + " >> Path " + path + " founded!\n");
                    }
                }

                for (std::string path : RequiredUserDirectories)
                {
                    if (!fs::translated::DirectoryExist(path))
                    {
                        misc::Output(Markers.at(3) + " >> User path " + path + " not found, creating...\n");
                        fs::translated::CreateDirectory(path);
                    }
                    else
                    {
                        misc::Output(Markers.at(1) + " >> User path " + path + " founded!\n");
                    }
                }

                for (std::string path : OptionalDirectories)
                {
                    if (!fs::translated::DirectoryExist(path))
                    {
                        misc::Output(Markers.at(3) + " >> Path " + path + " not found, creating...\n");
                        fs::translated::CreateDirectory(path);
                    }
                    else
                    {
                        misc::Output(Markers.at(1) + " >> User path " + path + " founded!\n");
                    }
                }
            }
            else
            {
                for (std::string path : RequiredDirectories)
                {
                    if (!fs::translated::DirectoryExist(path))
                    {
                        misc::Output(Markers.at(3) + " >> Path " + path + " not found, creating...\n");
                        fs::translated::CreateDirectory(path);
                    }
                    else
                    {
                        misc::Output(Markers.at(1) + " >> Path " + path + " founded!\n");
                    }
                }

                for (std::string path : RequiredUserDirectories)
                {
                    if (!fs::translated::DirectoryExist(path))
                    {
                        misc::Output(Markers.at(3) + " >> User path " + path + " not found, creating...\n");
                        fs::translated::CreateDirectory(path);
                    }
                    else
                    {
                        misc::Output(Markers.at(1) + " >> User path " + path + " founded!\n");
                    }
                }
            }

            return 0;
        }
    }
} // #installer

#endif