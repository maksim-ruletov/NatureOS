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

    #ifndef NatureOS_Kernel_K_PathManager_hpp
        #include "./K_PathManager.hpp"
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
            __StandardLibrary::ColorTemplater D_ColorTemplater;
            Path D_PathManager(S_StartPoint, S_FileSystemPaths);
            Packager D_PackagerForUser;

            D_ColorTemplater.E_Push("Greet-Color", D_ColorTemplater.E_GenerateFont(255, 0, 0), D_ColorTemplater.E_GenerateFont(255, 255, 255));
            D_ColorTemplater.E_Push("Important-Element", D_ColorTemplater.E_GenerateFont(255, 0, 0), D_ColorTemplater.E_GenerateFont(255, 255, 255));
            D_ColorTemplater.E_Push("System-Element", D_ColorTemplater.E_GenerateFont(197, 57, 235), D_ColorTemplater.E_GenerateFont(255, 255, 255));
            D_ColorTemplater.E_Push("Module-Element", D_ColorTemplater.E_GenerateFont(57, 146, 235), D_ColorTemplater.E_GenerateFont(255, 255, 255));

            D_Templater.E_Push("kernel-greet", D_ColorTemplater.E_Wrap("@kernel", "Greet-Color").E_GetDetails().at(0) + "> ");

            if (S_StartPoint.size() < 1) {
                __StandardLibrary::E_Output(D_Templater.E_Drop("kernel-greet").E_GetDetails().at(0) + "Fatal Error:" + D_ColorTemplater.E_Wrap("@StartPoint", "Important-Element").E_GetDetails().at(0) + " doesn't founded!");
                return;
            }
            else {
                if (S_Debug) {
                    __StandardLibrary::E_Output(D_Templater.E_Drop("kernel-greet").E_GetDetails().at(0) + D_ColorTemplater.E_Wrap("@StartPoint", "Important-Element").E_GetDetails().at(0) + " successfully registred!\n");
                }
            }

            __StandardLibrary::E_Output(D_Templater.E_Drop("kernel-greet").E_GetDetails().at(0) + "Welcome to NatureOS by " + D_ColorTemplater.E_Wrap(S_Author, "Important-Element").E_GetDetails().at(0) + "\n\n");
            __StandardLibrary::E_Output(D_Templater.E_Drop("kernel-greet").E_GetDetails().at(0) + "NatureOS version: " + D_ColorTemplater.E_Wrap(S_Version, "Important-Element").E_GetDetails().at(0) + "\n");
            __StandardLibrary::E_Output(D_Templater.E_Drop("kernel-greet").E_GetDetails().at(0) + "Successfully started" + (S_Debug ? D_ColorTemplater.E_Wrap(" in debug mode", "Important-Element").E_GetDetails().at(0) : "") + "!\n");

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

            // D_VirtualMemoryManager.E_Initialize(S_Debug, S_StartPoint);
            // D_VirtualMemoryManager.E_DropVM(S_StartPoint + "/home/.cache/vmdump.package");

            while (true) {
                std::string D_UserMessage;
                std::string D_Template = __StandardLibrary::E_ColorizeFont("@kernel", 255, 0, 0) + __StandardLibrary::E_ColorizeFont(" ~ " + D_PathManager.E_DropCurrentPath(), 255, 255, 255) + "> ";

                __StandardLibrary::E_Output(D_Template + "Enter any message: ");

                __StandardLibrary::E_Input(D_UserMessage);

                std::vector<std::string> D_ParsedCommand = __StandardLibrary::E_Split(D_UserMessage, " ");

                if (D_ParsedCommand.at(0).compare("crypto") == 0) {
                    if (D_ParsedCommand.size() < 2) {
                        __StandardLibrary::E_Output(D_Template + "[crypto]: Please, enter text to encode!\n");
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
                        __StandardLibrary::E_Output(D_Template + "[decrypto]: Please, enter text to decode!\n");
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
                        __StandardLibrary::E_Output(D_Template + "[vm]: Please, enter any flag!\n");
                        continue;
                    }

                    for (::size_t D_Iterator = 1; D_Iterator < D_ParsedCommand.size(); D_Iterator++) {
                        if (D_ParsedCommand.at(D_Iterator).compare("-s") == 0) {
                            D_Situate = E_Request(D_VirtualMemoryManager, "drop -size");

                            __StandardLibrary::E_Output(__StandardLibrary::E_ColorizeFont("@[vm::-s]", 255, 0, 0) + "> Labels founded " + D_Situate.E_GetDetails().at(0) + "\n");
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

                            __StandardLibrary::E_Output(__StandardLibrary::E_ColorizeFont("@[vm::-e]", 255, 0, 0) + "> Labels names: " + D_Labels + "\n");
                            continue;
                        }
                        else if (D_ParsedCommand.at(D_Iterator).compare("-fm") == 0) {
                            D_Situate = E_Request(D_VirtualMemoryManager, "drop -chains:0");

                            if (D_Situate.E_GetCode() != 1) {
                                __StandardLibrary::E_EnterDebugMessage(D_Situate);
                            }
                            else {
                                for (std::string D_Detail : D_Situate.E_GetDetails()) {
                                    __StandardLibrary::E_Output(__StandardLibrary::E_ColorizeFont("@[vm::-fm]", 255, 0, 0) + "> " + D_Detail + "\n");
                                }
                            }
                        }
                        else if (D_ParsedCommand.at(D_Iterator).compare("-cca") == 0) {

                        }
                    }
                }
                else if (D_ParsedCommand.at(0).compare("colors") == 0) {
                    __StandardLibrary::E_EnterDebugMessage(D_ColorTemplater.E_DropTable());
                }
                else if (D_ParsedCommand.at(0).compare("fs") == 0) {
                    if (D_ParsedCommand.size() < 2) {
                        __StandardLibrary::E_Output(D_Template + "[fs]: Please, enter any flag!\n");
                        continue;
                    }

                    for (::size_t D_Iterator = 1; D_Iterator < D_ParsedCommand.size(); D_Iterator++) {
                        if (D_ParsedCommand.at(D_Iterator).find("-") == std::string::npos) {
                            continue;
                        }
                        else {
                            if (D_ParsedCommand.at(D_Iterator).compare("-md") == 0) {
                                if (D_ParsedCommand.size() == 2) {
                                    __StandardLibrary::E_Output(D_Template + "[fs]: Enter directory name!\n");
                                }
                                else {
                                    std::string D_DirectoryName = D_ParsedCommand.at(2);

                                    if (__Drivers::E_DirectoryExist(S_StartPoint + D_PathManager.E_DropCurrentPath() + D_DirectoryName).E_GetCode() == 0) {
                                        __StandardLibrary::E_Output(D_Template + "[fs]: Directory already exist!\n");
                                    }
                                    else {
                                        __StandardLibrary::Situate D_Situate = __Drivers::E_CreateDirecotry(S_StartPoint + D_PathManager.E_DropCurrentPath() + D_DirectoryName);

                                        if (S_Debug) {
                                            __StandardLibrary::E_EnterDebugMessage(D_Situate);
                                        }

                                        __StandardLibrary::E_Output(D_Template + "[fs]: Directory successfully created!\n");
                                    }
                                }
                            }
                            else if (D_ParsedCommand.at(D_Iterator).compare("-mf") == 0) {
                                if (D_ParsedCommand.size() == 2) {
                                    __StandardLibrary::E_Output(D_Template + "[fs]: Enter file name!\n");
                                }
                                else {
                                    std::string D_FileName = D_ParsedCommand.at(2);

                                    if (__Drivers::E_FileExist(S_StartPoint + D_PathManager.E_DropCurrentPath() + D_FileName).E_GetCode() == 0) {
                                        __StandardLibrary::E_Output(D_Template + "[fs]: File already exist!\n");
                                    }
                                    else {
                                        __StandardLibrary::Situate D_Situate = __Drivers::E_CreateFile(S_StartPoint + D_PathManager.E_DropCurrentPath() + D_FileName);

                                        if (S_Debug) {
                                            __StandardLibrary::E_EnterDebugMessage(D_Situate);
                                        }

                                        __StandardLibrary::E_Output(D_Template + "[fs]: File successfully created!\n");
                                    }
                                }
                            }
                            else if (D_ParsedCommand.at(D_Iterator).compare("-l") == 0) {
                                D_Situate = __Drivers::E_ReadDirectory(S_StartPoint + D_PathManager.E_DropCurrentPath());

                                if (D_Situate.E_GetDetails().size() == 0) {
                                    __StandardLibrary::E_Output(D_Template + "[fs]: Directory is empty!\n");
                                }
                                else {
                                    ::size_t D_Counter = 0;

                                    __StandardLibrary::E_Output("\n");

                                    for (std::string D_DirectoryEntry : D_Situate.E_GetDetails()) {
                                        if ((D_Counter + 5) % 5 == 0) {
                                            __StandardLibrary::E_Output("\t");
                                        }

                                        __StandardLibrary::E_Output(D_DirectoryEntry);
                                        D_Counter++;

                                        if (D_Counter % 5 == 0) {
                                            __StandardLibrary::E_Output("\n\n");
                                        }
                                        else {
                                            __StandardLibrary::E_Output(" ");
                                        }
                                    }

                                    if (D_Counter % 5 != 0) {
                                        __StandardLibrary::E_Output("\n\n");
                                    }
                                }
                            }
                            else {
                                __StandardLibrary::E_Output(D_Template + "[fs]: Unknown flag!!\n");
                            }
                        }
                    }
                }
                else if (D_ParsedCommand.at(0).compare("path") == 0) {
                    if (D_ParsedCommand.size() < 2) {
                        __StandardLibrary::E_Output(D_Template + "[path]: Please, enter any flag!\n");
                        continue;
                    }

                    for (::size_t D_Iterator = 1; D_Iterator < D_ParsedCommand.size(); D_Iterator++) {
                        if (D_ParsedCommand.at(D_Iterator).find("-") == std::string::npos) {
                            continue;
                        }
                        else {
                            if (D_ParsedCommand.at(D_Iterator).compare("-c") == 0) {
                                if (D_ParsedCommand.size() == 2) {
                                    __StandardLibrary::E_Output(D_Template + "[path::-c]: Please, enter directory name!\n");
                                }
                                else {
                                    std::string D_NewPath = D_ParsedCommand.at(2);

                                    if (__Drivers::E_DirectoryExist(S_StartPoint + D_PathManager.E_DropCurrentPath() + D_NewPath).E_GetCode() != 0) {
                                        __StandardLibrary::E_Output(D_Template + "[path::-c]: Directory not found!\n");
                                    }
                                    else {
                                        D_PathManager.E_Append(D_NewPath);
                                    }
                                }
                            }
                            else if (D_ParsedCommand.at(D_Iterator).compare("-b") == 0) {
                                if (D_PathManager.E_DropCurrentPath().compare("/") != 0) {
                                    D_PathManager.E_Remove();
                                }
                            }
                        }
                    }
                }
            }
        }
    }

#endif