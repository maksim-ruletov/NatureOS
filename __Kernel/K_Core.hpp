#ifndef NatureOS_Kernel_K_Core_hpp
    #define NatureOS_Kernel_K_Core_hpp 1

    #ifndef NatureOS_VirtualMemory_VM_Core_hpp
        #include "../__VirtualMemory/VM_Core.hpp"
    #endif

    #ifndef NatureOS_StandardLibrary_SL_Debug_hpp
        #include "../__StandardLibrary/SL_Debuger.hpp"
    #endif

    #ifndef NatureOS_Kernel_Drivers_K_D_NakeFS_hpp
        #include "./__Drivers/K_D_NakeFS.hpp"
    #endif

    #ifndef NatureOS_Kernel_K_Bridge_hpp
        #include "./K_Bridge.hpp"
    #endif

    #ifndef NatureOS_Kernel_K_Packager_hpp
        #include "./K_Packager.hpp"
    #endif

    #ifndef NatureOS_StandardLibrary_SL_Crypto_hpp
        #include "../__StandardLibrary/SL_Crypto.hpp"
    #endif

    #ifndef NatureOS_StandardLibrary_SL_Template_hpp
        #include "../__StandardLibrary/SL_Template.hpp"
    #endif

    namespace __Kernel {
        const std::string S_Version = "0.3.0.0";
        const std::string S_Author = "ruletkasuperstar";
        const std::string S_StartPoint = "mpoint";
        const std::vector<std::string> S_FileSystemPaths = { "bin", "sbin", "environment", "environment/application", "environment/documents", "home", "home/.thumbnail", "home/.cache" };
        const std::vector<std::string> S_FileSystemFiles = { "home/.thumbnail/.config" };

        void E_EnterKernel (const bool S_Debug) {
            system("cls");

            __StandardLibrary::Templater D_Templater;

            D_Templater.E_Push("kernel-greet", __StandardLibrary::E_ColorizeFront("@kernel", 255, 0, 0) + "> ");

            if (S_StartPoint.size() < 1) {
                __StandardLibrary::E_Output(D_Templater.E_Drop("kernel-greet").E_GetDetails().at(0) + "Fatal Error:" + __StandardLibrary::E_ColorizeFront("@StartPoint", 255, 0, 0) + " doesn't founded!");
                return;
            }
            else {
                if (S_Debug) {
                    __StandardLibrary::E_Output(D_Templater.E_Drop("kernel-greet").E_GetDetails().at(0) + __StandardLibrary::E_ColorizeFront("@StartPoint", 255, 0, 0) + " successfully registred!\n");
                }
            }

            __StandardLibrary::E_Output(D_Templater.E_Drop("kernel-greet").E_GetDetails().at(0) + "Welcome to NatureOS by " + __StandardLibrary::E_ColorizeFront(S_Author, 255, 0, 0) + "\n\n");
            __StandardLibrary::E_Output(D_Templater.E_Drop("kernel-greet").E_GetDetails().at(0) + "NatureOS version: " + __StandardLibrary::E_ColorizeFront(S_Version, 255, 0, 0) + "\n");
            __StandardLibrary::E_Output(D_Templater.E_Drop("kernel-greet").E_GetDetails().at(0) + "Successfully started" + (S_Debug ? __StandardLibrary::E_ColorizeFront(" in debug mode", 255, 0, 0) : "") + "!\n");

            __VirtualMemory::Core D_VirtualMemoryManager;

            __StandardLibrary::Situate D_Situate;

            if (__Drivers::E_DirectoryExist(S_StartPoint).E_GetCode() != 0) {
                D_Situate = __Drivers::E_CreateDirecotry(S_StartPoint);

                if (S_Debug) {
                    __StandardLibrary::E_EnterDebugMessage(D_Situate);
                }
            }

            for (std::string D_CurrentFileSystemPath : S_FileSystemPaths) {
                if (__Drivers::E_DirectoryExist(S_StartPoint + "/" + D_CurrentFileSystemPath).E_GetCode() != 0) {
                    D_Situate = __Drivers::E_CreateDirecotry(S_StartPoint + "/" + D_CurrentFileSystemPath);

                    if (S_Debug) {
                        __StandardLibrary::E_EnterDebugMessage(D_Situate);
                    }
                }
            }

            for (std::string D_CurrentFileSystemFile : S_FileSystemFiles) {
                if (__Drivers::E_FileExist(S_StartPoint + "/" + D_CurrentFileSystemFile).E_GetCode() != 0) {
                    D_Situate = __Drivers::E_CreateFile(S_StartPoint + "/" + D_CurrentFileSystemFile);

                    if (S_Debug) {
                        __StandardLibrary::E_EnterDebugMessage(D_Situate);
                    }
                }
            }

            while (true) {
                std::string D_UserMessage;

                __StandardLibrary::E_Output(D_Templater.E_Drop("kernel-greet").E_GetDetails().at(0) + "Enter any message: ");

                __StandardLibrary::E_Input(D_UserMessage);

                __StandardLibrary::E_Output(D_UserMessage);
            }
        }
    }

#endif