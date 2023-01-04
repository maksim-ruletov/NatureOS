#ifndef NatureOS_Kernel_Drivers_K_D_NakeFS_hpp
    #define NatureOS_Kernel_Drivers_K_D_NakeFS_hpp 1

    #ifndef NatureOS_StandardLibrary_SL_Situate_hpp
        #include "../../__StandardLibrary/SL_Situate.hpp"
    #endif

    #ifndef NatureOS_StandardLibrary_SL_Colorizer_hpp
        #include "../../__StandardLibrary/SL_Colorizer.hpp"
    #endif

    #include <sys/types.h>
    #include <sys/stat.h>
    #include <direct.h>

    #ifndef _FSTREAM_
        #include <fstream>
    #endif

    #ifndef _FILESYSTEM_
        #include <filesystem>
    #endif

    #ifndef _IOSTREAM_
        #include <iostream>
    #endif
    
    namespace __Kernel {
        namespace __Drivers {
            __StandardLibrary::Situate E_FileExist (const std::string S_FileName) {
                __StandardLibrary::Situate D_Situate;

                if (FILE* D_FileController = fopen(S_FileName.c_str(), "r")) {
                    fclose(D_FileController);
                    
                    D_Situate.E_SetHeader("__Kernel::__Drivers::E_FileExit()");
                    D_Situate.E_SetBody(__StandardLibrary::E_ColorizeFont("E_FileExist", 197, 57, 235) + " returned success code!");
                    D_Situate.E_SetCode(0);
                    D_Situate.E_PushDetail(__StandardLibrary::E_ColorizeFont("@File", 57, 146, 235) + " with name " + __StandardLibrary::E_ColorizeFont(S_FileName, 255, 0, 0) + " exist!");

                    return D_Situate;
                }
                else {
                    D_Situate.E_SetHeader("__Kernel::__Drivers::E_FileExit()");
                    D_Situate.E_SetBody(__StandardLibrary::E_ColorizeFont("E_FileExist", 197, 57, 235) + " returned error code!");
                    D_Situate.E_SetCode(1);
                    D_Situate.E_PushDetail(__StandardLibrary::E_ColorizeFont("@File", 57, 146, 235) + " with name " + __StandardLibrary::E_ColorizeFont(S_FileName, 255, 0, 0) + " doesn't exist!");

                    return D_Situate;
                }
            }

            __StandardLibrary::Situate E_DirectoryExist (const std::string S_DirectoryName) {
                __StandardLibrary::Situate D_Situate;

                struct stat D_DirectoryInformation;

                if (stat(S_DirectoryName.c_str(), &D_DirectoryInformation) != 0) {
                    D_Situate.E_SetHeader("__Kernel::__Drivers::E_DirectoryExist()");
                    D_Situate.E_SetBody(__StandardLibrary::E_ColorizeFont("E_DirectoryExist", 197, 57, 235) + " returned error code!");
                    D_Situate.E_SetCode(1);
                    D_Situate.E_PushDetail("Can't access to " + __StandardLibrary::E_ColorizeFont("@Directory", 57, 146, 235) + " with name " + __StandardLibrary::E_ColorizeFont(S_DirectoryName, 255, 0, 0));

                    return D_Situate;
                }
                else if (D_DirectoryInformation.st_mode& S_IFDIR) {
                    D_Situate.E_SetHeader("__Kernel::__Drivers::E_DirectoryExist()");
                    D_Situate.E_SetBody(__StandardLibrary::E_ColorizeFont("E_DirectoryExist", 197, 57, 235) + " returned success code!");
                    D_Situate.E_SetCode(0);
                    D_Situate.E_PushDetail(__StandardLibrary::E_ColorizeFont("@Directory", 57, 146, 235) + " with name " + __StandardLibrary::E_ColorizeFont(S_DirectoryName, 255, 0, 0) + " exist!");

                    return D_Situate;
                }
                else {
                    D_Situate.E_SetHeader("__Kernel::__Drivers::E_DirectoryExist()");
                    D_Situate.E_SetBody(__StandardLibrary::E_ColorizeFont("E_DirectoryExist", 197, 57, 235) + " returned error code!");
                    D_Situate.E_SetCode(2);
                    D_Situate.E_PushDetail(__StandardLibrary::E_ColorizeFont("@Directory", 57, 146, 235) + " with name " + __StandardLibrary::E_ColorizeFont(S_DirectoryName, 255, 0, 0) + " doesn't exist!");

                    return D_Situate;
                }
            }

            __StandardLibrary::Situate E_CreateFile (const std::string S_FileName) {
                __StandardLibrary::Situate D_Situate;

                if (E_FileExist(S_FileName).E_GetCode() == 0) {
                    D_Situate.E_SetHeader("__Kernel::__Drivers::E_CreateFile()");
                    D_Situate.E_SetBody(__StandardLibrary::E_ColorizeFont("E_CreateFile", 197, 57, 235) + " returned error code!");
                    D_Situate.E_SetCode(1);
                    D_Situate.E_PushDetail(__StandardLibrary::E_ColorizeFont("@File", 57, 146, 235) + " with name " + __StandardLibrary::E_ColorizeFont(S_FileName, 255, 0, 0) + " already exist!");
                
                    return D_Situate;
                }

                std::fstream D_FileController;
                D_FileController.open(S_FileName, std::ios::out);
                D_FileController.close();

                D_Situate.E_SetHeader("__Kernel::__Drivers::E_CreateFile()");
                D_Situate.E_SetBody(__StandardLibrary::E_ColorizeFont("E_CreateFile", 197, 57, 235) + " returned succes code!");
                D_Situate.E_SetCode(0);
                D_Situate.E_PushDetail(__StandardLibrary::E_ColorizeFont("@File", 57, 146, 235) + " with name " + __StandardLibrary::E_ColorizeFont(S_FileName, 255, 0, 0) + " successfully created!");
            
                return D_Situate;
            }

            __StandardLibrary::Situate E_CreateDirecotry (const std::string S_DirectoryName) {
                __StandardLibrary::Situate D_Situate;

                if (E_DirectoryExist(S_DirectoryName).E_GetCode() == 0) {
                    D_Situate.E_SetHeader("__Kernel::__Drivers::E_CreateDirecotry()");
                    D_Situate.E_SetBody(__StandardLibrary::E_ColorizeFont("E_CreateDirecotry", 197, 57, 235) + " returned error code!");
                    D_Situate.E_SetCode(1);
                    D_Situate.E_PushDetail(__StandardLibrary::E_ColorizeFont("@Directory", 57, 146, 235) + " with name " + __StandardLibrary::E_ColorizeFont(S_DirectoryName, 255, 0, 0) + " already exist!");
                
                    return D_Situate;
                }

                _mkdir(S_DirectoryName.c_str());

                D_Situate.E_SetHeader("__Kernel::__Drivers::E_CreateDirecotry()");
                D_Situate.E_SetBody(__StandardLibrary::E_ColorizeFont("E_CreateDirecotry", 197, 57, 235) + " returned succes code!");
                D_Situate.E_SetCode(0);
                D_Situate.E_PushDetail(__StandardLibrary::E_ColorizeFont("@Directory", 57, 146, 235) + " with name " + __StandardLibrary::E_ColorizeFont(S_DirectoryName, 255, 0, 0) + " successfully created!");
            
                return D_Situate;
            }

            __StandardLibrary::Situate E_RemoveFile (const std::string S_FileName) {
                __StandardLibrary::Situate D_Situate;

                if (E_FileExist(S_FileName).E_GetCode() == 0) {
                    D_Situate.E_SetHeader("__Kernel::__Drivers::E_RemoveFile()");
                    D_Situate.E_SetBody(__StandardLibrary::E_ColorizeFont("E_RemoveFile", 197, 57, 235) + " returned error code!");
                    D_Situate.E_SetCode(1);
                    D_Situate.E_PushDetail(__StandardLibrary::E_ColorizeFont("@File", 57, 146, 235) + " with name " + __StandardLibrary::E_ColorizeFont(S_FileName, 255, 0, 0) + " doesn't exist!");
                
                    return D_Situate;
                }

                std::filesystem::remove(S_FileName);

                D_Situate.E_SetHeader("__Kernel::__Drivers::E_RemoveFile()");
                D_Situate.E_SetBody(__StandardLibrary::E_ColorizeFont("E_RemoveFile", 197, 57, 235) + " returned succes code!");
                D_Situate.E_SetCode(0);
                D_Situate.E_PushDetail(__StandardLibrary::E_ColorizeFont("@File", 57, 146, 235) + " with name " + __StandardLibrary::E_ColorizeFont(S_FileName, 255, 0, 0) + " successfully removed!");
            
                return D_Situate;
            }

            __StandardLibrary::Situate E_RemoveDirectory (const std::string S_DirectoryName) {
                __StandardLibrary::Situate D_Situate;

                if (E_DirectoryExist(S_DirectoryName).E_GetCode() == 0) {
                    D_Situate.E_SetHeader("__Kernel::__Drivers::E_RemoveDirectory()");
                    D_Situate.E_SetBody(__StandardLibrary::E_ColorizeFont("E_RemoveDirectory", 197, 57, 235) + " returned error code!");
                    D_Situate.E_SetCode(1);
                    D_Situate.E_PushDetail(__StandardLibrary::E_ColorizeFont("@Directory", 57, 146, 235) + " with name " + __StandardLibrary::E_ColorizeFont(S_DirectoryName, 255, 0, 0) + " doesn't exist!");
                
                    return D_Situate;
                }

                std::filesystem::remove_all(S_DirectoryName);

                D_Situate.E_SetHeader("__Kernel::__Drivers::E_RemoveDirectory()");
                D_Situate.E_SetBody(__StandardLibrary::E_ColorizeFont("E_RemoveDirectory", 197, 57, 235) + " returned succes code!");
                D_Situate.E_SetCode(0);
                D_Situate.E_PushDetail(__StandardLibrary::E_ColorizeFont("@Directory", 57, 146, 235) + " with name " + __StandardLibrary::E_ColorizeFont(S_DirectoryName, 255, 0, 0) + " successfully removed!");
            
                return D_Situate;
            }

            __StandardLibrary::Situate E_ReadFile (const std::string S_FileName) {
                __StandardLibrary::Situate D_Situate;

                if (E_FileExist(S_FileName).E_GetCode() != 0) {
                    D_Situate.E_SetHeader("__Kernel::__Drivers::E_ReadFile()");
                    D_Situate.E_SetBody(__StandardLibrary::E_ColorizeFont("E_ReadFile", 197, 57, 235) + " returned error code!");
                    D_Situate.E_SetCode(1);
                    D_Situate.E_PushDetail(__StandardLibrary::E_ColorizeFont("@File", 57, 146, 235) + " with name " + __StandardLibrary::E_ColorizeFont(S_FileName, 255, 0, 0) + " doesn't exist!");
                
                    return D_Situate;
                }

                std::ifstream D_FileInput(S_FileName);
                std::vector<std::string> D_ParsedFile;

                for (std::string D_FileLine; getline(D_FileInput, D_FileLine);) {
                    D_ParsedFile.push_back(D_FileLine);
                }

                D_Situate.E_SetHeader("__Kernel::__Drivers::E_ReadFile()");
                D_Situate.E_SetBody(__StandardLibrary::E_ColorizeFont("E_ReadFile", 197, 57, 235) + " returned success code!");
                D_Situate.E_SetCode(0);
                
                for (std::string D_Line : D_ParsedFile) {
                    D_Situate.E_PushDetail(D_Line);
                }
            
                return D_Situate;
            }

            __StandardLibrary::Situate E_Rewrite (std::string D_FilePath, std::string D_NewContent) {
                __StandardLibrary::Situate D_Situate;
                D_Situate.E_SetHeader("__Kernel::__Drivers::E_Rewrite()");

                if (E_FileExist(D_FilePath).E_GetCode() != 0) {
                    return E_FileExist(D_FilePath);
                }

                std::fstream D_FileController;

                D_FileController.open(D_FilePath.c_str(), std::ios::out);

                D_FileController << D_NewContent;

                D_FileController.close();

                D_Situate.E_SetHeader("__Kernel::__Drivers::E_Rewrite()");
                D_Situate.E_SetBody(__StandardLibrary::E_ColorizeFont("E_ReadFile", 197, 57, 235) + " returned success code!");
                D_Situate.E_SetCode(0);

                return D_Situate;
            }

            __StandardLibrary::Situate E_ReadDirectory (std::string D_DirectoryName) {
                __StandardLibrary::Situate D_Situate;
                D_Situate.E_SetHeader("__Kernel::__Drivers::E_ReadDirectory()");

                for (const auto& entry : std::filesystem::directory_iterator(D_DirectoryName)) {
                    std::string D_Name = __StandardLibrary::E_Split(entry.path().string(), "/").at(__StandardLibrary::E_Split(entry.path().string(), "/").size() - 1);

                    if (entry.is_directory()) {
                        D_Situate.E_PushDetail(__StandardLibrary::E_ColorizeBackground(__StandardLibrary::E_ColorizeFont(D_Name, 0, 0, 0), 235, 235, 52));
                    }
                    else {
                        D_Situate.E_PushDetail(__StandardLibrary::E_ColorizeBackground(__StandardLibrary::E_ColorizeFont(D_Name, 0, 0, 0), 104, 235, 52));
                    }
                }

                D_Situate.E_SetCode(0);

                return D_Situate;
            }
        } 
    }

#endif