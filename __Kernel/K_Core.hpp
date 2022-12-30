#ifndef NatureOS_Kernel_K_Core_hpp
    #define NatureOS_Kernel_K_Core_hpp 1

    #ifndef NatureOS_VirtualMemory_VM_Core_hpp
        #include "../__VirtualMemory/VM_Core.hpp"
    #endif

    #ifndef NatureOS_StandardLibrary_SL_Debug_hpp
        #include "../__StandardLibrary/SL_Debug.hpp"
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

    namespace __Kernel {
        const std::string S_Version = "0.2.8.7";
        const std::string S_Author = "ruletkasuperstar";
        const std::string S_StartPoint = "mpoint";
        const std::vector<std::string> S_FileSystemPaths = { "bin", "sbin", "environment", "environment/application", "environment/documents", "home", "home/.thumbnail", "home/.cache" };
        const std::vector<std::string> S_FileSystemFiles = { "home/.thumbnail/.config" };
        const std::string S_VMDumbFileName = "vmdump.package";

        void E_EnterKernel (const bool S_Debug) {
            system("cls");

            if (S_StartPoint.size() < 1) {
                __StandardLibrary::E_Output(__StandardLibrary::E_ColorizeFront("@kernel", 255, 0, 0) + "> Fatal Error: " + __StandardLibrary::E_ColorizeFront("@StartPoint", 255, 0, 0) + " doesn't founded!");
                return;
            }
            else {
                if (S_Debug) {
                    __StandardLibrary::E_Output(__StandardLibrary::E_ColorizeFront("@kernel", 255, 0, 0) + "> " + __StandardLibrary::E_ColorizeFront("@StartPoint", 255, 0, 0) + " successfully registred!\n");
                }
            }

            __StandardLibrary::E_Output(__StandardLibrary::E_ColorizeFront("@kernel", 255, 0, 0) + "> Welcome to NatureOS by " + __StandardLibrary::E_ColorizeFront(S_Author, 255, 0, 0) + "\n\n");
            __StandardLibrary::E_Output(__StandardLibrary::E_ColorizeFront("@kernel", 255, 0, 0) + "> NatureOS version: " + __StandardLibrary::E_ColorizeFront(S_Version, 255, 0, 0) + "\n");
            __StandardLibrary::E_Output(__StandardLibrary::E_ColorizeFront("@kernel", 255, 0, 0) + "> Successfully started" + (S_Debug ? __StandardLibrary::E_ColorizeFront(" in debug mode", 255, 0, 0) : "") + "!\n");

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

            // D_Situate = E_Request(D_VirtualMemoryManager, "drop-size");

            // if (S_Debug) {
            //     __StandardLibrary::E_EnterDebugMessage(D_Situate);
            // }
            
            // Packager D_VMWorker(S_StartPoint + "/home/.cache/" + S_VMDumbFileName);

            D_VirtualMemoryManager.E_Initialize(S_Debug, S_StartPoint);
            D_VirtualMemoryManager.E_DropVM(S_StartPoint + "/home/.cache/" + S_VMDumbFileName);

            while (true) {
                std::string D_UserMessage;

                __StandardLibrary::E_Output(__StandardLibrary::E_ColorizeFront("@kernel", 255, 0, 0) + "> Enter any message: ");

                __StandardLibrary::E_Input(D_UserMessage);

                std::vector<std::string> D_ParsedCommand = __StandardLibrary::E_Split(D_UserMessage, " ");

                if (D_ParsedCommand.at(0).compare("crypto") == 0) {
                    if (D_ParsedCommand.size() < 2) {
                        __StandardLibrary::E_Output(__StandardLibrary::E_ColorizeFront("@kernel", 255, 0, 0) + "> [crypto]: Please, enter text to encode!\n");
                        continue;
                    }

                    std::string D_Text = "";

                    for (::size_t D_Iterator = 1; D_Iterator < D_ParsedCommand.size(); D_Iterator++) {
                        D_Text += D_ParsedCommand.at(D_Iterator) + " ";
                    }

                    D_Text.pop_back();
                    
                    std::string D_EncodedText = __StandardLibrary::E_Encode(D_Text, "es11").E_GetDetails().at(0);
                    __StandardLibrary::E_Output(D_EncodedText + "\n");
                }
                else if (D_ParsedCommand.at(0).compare("decrypto") == 0) {
                    if (D_ParsedCommand.size() < 2) {
                        __StandardLibrary::E_Output(__StandardLibrary::E_ColorizeFront("@kernel", 255, 0, 0) + "> [decrypto]: Please, enter text to decode!\n");
                        continue;
                    }

                    std::string D_Text = "";

                    for (::size_t D_Iterator = 1; D_Iterator < D_ParsedCommand.size(); D_Iterator++) {
                        D_Text += D_ParsedCommand.at(D_Iterator) + " ";
                    }

                    D_Text.pop_back();
                    
                    std::string D_EncodedText = __StandardLibrary::E_Decode(D_Text, "es11").E_GetDetails().at(0);
                    __StandardLibrary::E_Output(D_EncodedText + "\n");
                }
                else if (D_ParsedCommand.at(0).compare("vm") == 0) {
                    if (D_ParsedCommand.size() < 2) {
                        __StandardLibrary::E_Output(__StandardLibrary::E_ColorizeFront("@kernel", 255, 0, 0) + "> [vm]: Please, enter any flag!\n");
                        continue;
                    }

                    for (::size_t D_Iterator = 1; D_Iterator < D_ParsedCommand.size(); D_Iterator++) {
                        if (D_ParsedCommand.at(D_Iterator).compare("-s") == 0) {
                            D_Situate = E_Request(D_VirtualMemoryManager, "drop -size");

                            __StandardLibrary::E_Output(__StandardLibrary::E_ColorizeFront("@[vm::-s]", 255, 0, 0) + "> Labels founded " + D_Situate.E_GetDetails().at(0) + "\n");
                            continue;
                        }
                        else if (D_ParsedCommand.at(D_Iterator).compare("-e") == 0) {
                            D_Situate = E_Request(D_VirtualMemoryManager, "drop -labels:name");

                            std::string D_Labels;

                            for (std::string D_LabelName : D_Situate.E_GetDetails()) {
                                D_Labels += D_LabelName + ", ";
                            }

                            D_Labels.pop_back();
                            D_Labels.pop_back();

                            __StandardLibrary::E_Output(__StandardLibrary::E_ColorizeFront("@[vm::-e]", 255, 0, 0) + "> Labels names: " + D_Labels + "\n");
                            continue;
                        }
                        else if (D_ParsedCommand.at(D_Iterator).compare("-fm") == 0) {
                            D_Situate = E_Request(D_VirtualMemoryManager, "drop -chains:0");

                            if (D_Situate.E_GetCode() != 1) {
                                __StandardLibrary::E_EnterDebugMessage(D_Situate);
                            }
                            else {
                                for (std::string D_Detail : D_Situate.E_GetDetails()) {
                                    __StandardLibrary::E_Output(__StandardLibrary::E_ColorizeFront("@[vm::-fm]", 255, 0, 0) + "> " + D_Detail + "\n");
                                }
                            }
                        }
                        else if (D_ParsedCommand.at(D_Iterator).compare("-cca") == 0) {

                        }
                    }
                }
            }
        }
    }

#endif