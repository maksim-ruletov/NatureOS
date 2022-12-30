#ifndef NatureOS_VirtualMemory_VM_Core_hpp
    #define NatureOS_VirtualMemory_VM_Core_hpp 1

    #ifndef NatureOS_VirtualMemory_VM_Data_hpp
        #include "./VM_Data.hpp"
    #endif

    #ifndef NatureOS_StandardLibrary_SL_Situate_hpp
        #include "../__StandardLibrary/SL_Situate.hpp"
    #endif

    #ifndef NatureOS_StandardLibrary_SL_Timer_hpp
        #include "../__StandardLibrary/SL_Timer.hpp"
    #endif

    #ifndef NatureOS_StandardLibrary_SL_Colorizer_hpp
        #include "../__StandardLibrary/SL_Colorizer.hpp"
    #endif

    #ifndef NatureOS_Kernel_Drivers_K_D_NakeFS_hpp
        #include "../__Kernel/__Drivers/K_D_NakeFS.hpp"
    #endif

    #ifndef NatureOS_StandardLibrary_SL_Utilities_hpp
        #include "../__StandardLibrary/SL_Utilities.hpp"
    #endif

    #ifndef _VECTOR_
        #include <vector>
    #endif

    #ifndef _STRING_
        #include <string>
    #endif

    #ifndef NatureOS_Kernel_K_Packager_hpp
        #include "../__Kernel/K_Packager.hpp"
    #endif

    #ifndef NatureOS_StandardLibrary_SL_Crypto_hpp
        #include "../__StandardLibrary/SL_Crypto.hpp"
    #endif

    namespace __VirtualMemory {
        class Core {
        private:
            std::vector<Label> D_VMStorage;
            bool D_Debug;
        public:
            __StandardLibrary::Situate E_Initialize (const bool S_Debug, const std::string S_StartPoint) {
                __StandardLibrary::Situate S_Situate;
                __Kernel::Packager D_Packager(S_StartPoint + "/home/.cache/vmdump.package");

                if (__Kernel::__Drivers::E_FileExist(S_StartPoint + "/home/.cache/vmdump.package").E_GetCode() == 0) {
                    D_Packager.E_Parse();

                    for (::size_t D_Iterator = 0; D_Iterator < D_Packager.E_DropBase().size(); D_Iterator++) {
                        Label D_Label;

                        D_Label.D_CodingAlgorythm = D_Packager.E_GetValue(D_Iterator, "D_CodingAlgorythm").E_GetDetails().at(0);
                        D_Label.D_CodingStatus = D_Packager.E_GetValue(D_Iterator, "D_CodingStatus").E_GetDetails().at(0).compare("1") == 0 ? true : false;
                        D_Label.D_CreatingDate = D_Packager.E_GetValue(D_Iterator, "D_CreatingDate").E_GetDetails().at(0);
                        D_Label.D_Creator = D_Packager.E_GetValue(D_Iterator, "D_Creator").E_GetDetails().at(0);
                        D_Label.D_LabelNumber = std::stoi(D_Packager.E_GetValue(D_Iterator, "D_LabelNumber").E_GetDetails().at(0));
                        D_Label.D_Modifiable = D_Packager.E_GetValue(D_Iterator, "D_Modifiable").E_GetDetails().at(0).compare("1") == 0 ? true : false;
                        D_Label.D_Name = D_Packager.E_GetValue(D_Iterator, "D_Name").E_GetDetails().at(0);
                        D_Label.D_Password = __StandardLibrary::E_Encode(D_Packager.E_GetValue(D_Iterator, "D_Password").E_GetDetails().at(0), D_Label.D_CodingAlgorythm).E_GetDetails().at(0);
                        D_Label.D_PasswordStatus = D_Packager.E_GetValue(D_Iterator, "D_PasswordStatus").E_GetDetails().at(0).compare("1") == 0 ? true : false;
                        D_Label.D_RootLaws = D_Packager.E_GetValue(D_Iterator, "D_RootLaws").E_GetDetails().at(0).compare("1") == 0 ? true : false;

                        if (__Kernel::__Drivers::E_FileExist(S_StartPoint + "/home/.cache/" + D_Label.D_Name + ".chains.package").E_GetCode() == 0) {
                            __Kernel::Packager D_LocalPackager(S_StartPoint + "/home/.cache/" + D_Label.D_Name + ".chains.package");
                            D_LocalPackager.E_Parse();

                            for (::size_t D_IteratorC = 0; D_IteratorC < D_LocalPackager.E_DropBase().size(); D_IteratorC++) {
                                __Chain::Core D_Chain;
                                D_Chain.E_Initialize(D_IteratorC);

                                for (::size_t D_IteratorCC = 0; D_IteratorCC < D_LocalPackager.E_DropBase().at(D_IteratorC).D_Scope.size(); D_IteratorCC++) {
                                    Addresser D_Addreser;

                                    D_Addreser.D_ChainIndex = D_IteratorC;
                                    D_Addreser.D_InChainIndex = D_IteratorCC;
                                    D_Addreser.D_Value = D_LocalPackager.E_GetValue(D_IteratorC, std::to_string(D_Addreser.D_ChainIndex) + "x" + std::to_string(D_Addreser.D_InChainIndex)).E_GetDetails().at(0);

                                    D_Chain.E_Push(D_Addreser.D_Value);
                                }

                                D_Label.D_Markup.push_back(D_Chain.E_GetChain());
                            }
                        }

                        this->D_VMStorage.push_back(D_Label);
                    }
                }

                if (D_VMStorage.size() > 0) {
                    if (this->D_Debug || S_Debug) {
                        S_Situate.E_SetHeader("__VirtualMemory::Core::E_Initialize()");
                        S_Situate.E_SetBody(__StandardLibrary::E_ColorizeFront("@Core::E_Initialize", 197, 57, 235) + " returned error code!");
                        S_Situate.E_PushDetail(__StandardLibrary::E_ColorizeFront("@__VirtualMemory", 57, 146, 235) + " " + __StandardLibrary::E_ColorizeFront("@Core", 57, 146, 235) + " already initialized!");
                    }

                    S_Situate.E_SetCode(1);

                    return S_Situate;
                }

                this->D_Debug = S_Debug;

                Label D_SystemLabel;

                D_SystemLabel.D_Name = "System";
                D_SystemLabel.D_Creator = "System";
                D_SystemLabel.D_CreatingDate = __StandardLibrary::E_GetDateAndTime();
                D_SystemLabel.D_LabelNumber = 1;
                D_SystemLabel.D_PasswordStatus = true;
                D_SystemLabel.D_Password = "EuO2-B1m)-p4Z1-Vr7M-Mk1P-q9Nw";
                D_SystemLabel.D_CodingStatus = true;
                D_SystemLabel.D_CodingAlgorythm = "es11";
                D_SystemLabel.D_RootLaws = true;
                
                __Chain::Core D_SystemLabelChain;
                D_SystemLabelChain.E_Initialize(D_SystemLabel.D_Markup.size());

                D_SystemLabelChain.E_Push("first test");

                D_SystemLabel.D_Markup.push_back(D_SystemLabelChain.E_GetChain());
                D_SystemLabel.D_Modifiable = false;

                // std::cout << D_SystemLabel.D_Markup.at(0).D_Chain.at(0).D_Value;

                this->D_VMStorage.push_back(D_SystemLabel);

                if (this->D_Debug) {
                    S_Situate.E_SetHeader("__VirtualMemory::Core::E_Initialize()");
                    S_Situate.E_SetBody(__StandardLibrary::E_ColorizeFront("@Core::E_Initialize", 197, 57, 235) + " returned success code!");
                    S_Situate.E_PushDetail(__StandardLibrary::E_ColorizeFront("@__VirtualMemory", 57, 146, 235) + " " + __StandardLibrary::E_ColorizeFront("@Core", 57, 146, 235) + " successfully initialized!");
                    S_Situate.E_PushDetail(__StandardLibrary::E_ColorizeFront("@Core", 57, 146, 235) + " successfully create System's "  + __StandardLibrary::E_ColorizeFront("@Label", 57, 146, 235) +  "!");
                    S_Situate.E_PushDetail(__StandardLibrary::E_ColorizeFront("@Core", 57, 146, 235) + " successfully System's " + __StandardLibrary::E_ColorizeFront("@Label", 57, 146, 235) + " successfully entered "  + __StandardLibrary::E_ColorizeFront("@Chain", 57, 146, 235) +  "!");
                }

                S_Situate.E_SetCode(1);

                return S_Situate;
            }

            __StandardLibrary::Situate E_DropVM (std::string D_DropPath) {
                __StandardLibrary::Situate D_Situate;
                
                if (this->D_VMStorage.size() == 0) {
                    D_Situate.E_SetCode(0);

                    return D_Situate;
                }

                __Kernel::Packager D_Packager(D_DropPath);

                for (::size_t D_Iterator = 0; D_Iterator < this->D_VMStorage.size(); D_Iterator++) {
                    D_Packager.E_Pack();
                    ::size_t D_PackIndex = D_Packager.E_DropBase().size() - 1;
                    Label D_Label = this->D_VMStorage.at(D_Iterator);

                    D_Packager.E_Push(D_PackIndex, "D_CodingAlgorythm", D_Label.D_CodingAlgorythm);
                    D_Packager.E_Push(D_PackIndex, "D_CodingStatus", std::to_string(D_Label.D_CodingStatus));
                    D_Packager.E_Push(D_PackIndex, "D_CreatingDate", D_Label.D_CreatingDate);
                    D_Packager.E_Push(D_PackIndex, "D_Creator", D_Label.D_Creator);
                    D_Packager.E_Push(D_PackIndex, "D_LabelNumber", std::to_string(D_Label.D_LabelNumber));
                    D_Packager.E_Push(D_PackIndex, "D_Modifiable", std::to_string(D_Label.D_Modifiable));
                    D_Packager.E_Push(D_PackIndex, "D_Name", D_Label.D_Name);
                    D_Packager.E_Push(D_PackIndex, "D_Password", __StandardLibrary::E_Encode(D_Label.D_Password, D_Label.D_CodingAlgorythm).E_GetDetails().at(0));
                    D_Packager.E_Push(D_PackIndex, "D_PasswordStatus", std::to_string(D_Label.D_PasswordStatus));
                    D_Packager.E_Push(D_PackIndex, "D_RootLaws", std::to_string(D_Label.D_RootLaws));

                    if (__Kernel::__Drivers::E_FileExist("mpoint/home/.cache/" + D_Label.D_Name + ".chains.package").E_GetCode() != 0) {
                        __Kernel::__Drivers::E_CreateFile("mpoint/home/.cache/" + D_Label.D_Name + ".chains.package");
                    }

                    __Kernel::Packager D_LocalChainPackager("mpoint/home/.cache/" + D_Label.D_Name + ".chains.package");

                    for (Chain D_Chain : D_Label.D_Markup) {
                        D_LocalChainPackager.E_Pack();
                        ::size_t D_PackIndex = D_LocalChainPackager.E_DropBase().size() - 1;

                        for (Addresser D_Addreser : D_Chain.D_Chain) {
                            D_LocalChainPackager.E_Push(D_PackIndex, std::to_string(D_Addreser.D_ChainIndex) + "x" + std::to_string(D_Addreser.D_InChainIndex), D_Addreser.D_Value);
                        }
                    }

                    __Kernel::__Drivers::E_Rewrite("mpoint/home/.cache/" + D_Label.D_Name + ".chains.package", D_LocalChainPackager.E_Stringify().E_GetDetails().at(0));
                }

                return __Kernel::__Drivers::E_Rewrite(D_DropPath, D_Packager.E_Stringify().E_GetDetails().at(0));
            }

            bool E_Bridge () {
                return true;
            }

            __StandardLibrary::Situate E_BridgeAPI (std::string D_RequestHeader, __StandardLibrary::Composition D_RequestBody) {
                __StandardLibrary::Situate D_Situate;
                D_Situate.E_SetHeader("__VirtualMemory::Core::E_BridgeAPI");
                D_Situate.E_SetBody("Request successfully accepted!");

                if (D_RequestHeader.compare("get") == 0) {
                    for (std::vector<std::string> D_RequestBodyElement : D_RequestBody) {
                        D_Situate.E_PushDetail(D_RequestBodyElement.at(0) + ": " + D_RequestBodyElement.at(1));
                    }

                    return D_Situate;
                }
                else if (D_RequestHeader.compare("drop") == 0) {
                    for (std::vector<std::string> D_RequestBodyElement : D_RequestBody) {
                        if (D_RequestBodyElement.at(1).compare("-size") == 0) {
                            D_Situate.E_PushDetail(std::to_string(this->D_VMStorage.size()));
                        }
                        else if (D_RequestBodyElement.at(1).find("-labels") != std::string::npos) {
                            std::vector<std::string> D_ParsedRequestBody = __StandardLibrary::E_Split(D_RequestBodyElement.at(1), ":");
                            std::string D_Argument = D_ParsedRequestBody.at(1);

                            if (D_Argument.compare("name") == 0) {
                                if (this->D_VMStorage.size() == 0) {
                                    D_Situate.E_SetBody("Request not accepted!");
                                    D_Situate.E_PushDetail(__StandardLibrary::E_ColorizeFront("@Storage", 57, 146, 235) + " is empty!");
                                    D_Situate.E_SetCode(0);
                                }
                                else {
                                    for (Label D_Label : this->D_VMStorage) {
                                        D_Situate.E_PushDetail(D_Label.D_Name);
                                    }

                                    D_Situate.E_SetCode(1);
                                }
                            }
                            else {
                                D_Situate.E_SetBody("Request not accepted!");
                                D_Situate.E_PushDetail("Unknow " + __StandardLibrary::E_ColorizeFront("@Argument", 57, 146, 235) + __StandardLibrary::E_ColorizeFront(D_Argument, 255, 0, 0));
                                D_Situate.E_SetCode(0);
                            }
                        }
                        else if (D_RequestBodyElement.at(1).find("-chains") != std::string::npos) {
                            std::vector<std::string> D_ParsedRequestBody = __StandardLibrary::E_Split(D_RequestBodyElement.at(1), ":");
                            int D_Argument = std::stoi(D_ParsedRequestBody.at(1));

                            if (D_Argument > this->D_VMStorage.size() - 1) {
                                D_Situate.E_SetBody("Request not accepted!");
                                D_Situate.E_PushDetail(__StandardLibrary::E_ColorizeFront("@Lable", 57, 146, 235) + " with index " + __StandardLibrary::E_ColorizeFront(std::to_string(D_Argument), 255, 0, 0) + " not found!");
                                D_Situate.E_SetCode(0);
                            }

                            Label D_Label = this->D_VMStorage.at(D_Argument);

                            if (D_Label.D_Markup.size() == 0) {
                                D_Situate.E_SetBody("Request not accepted!");
                                D_Situate.E_PushDetail(__StandardLibrary::E_ColorizeFront("@Lable", 57, 146, 235) + " is empty");
                                D_Situate.E_SetCode(0);
                            }
                            else {
                                for (Chain D_Chain : D_Label.D_Markup) {
                                    if (D_Chain.D_Chain.size() == 0) {
                                        D_Situate.E_SetBody("Request not accepted!");
                                        D_Situate.E_PushDetail(__StandardLibrary::E_ColorizeFront("@Chain", 57, 146, 235) + " is empty");
                                        D_Situate.E_SetCode(0);
                                    }
                                    else {
                                        for (Addresser D_Adresser : D_Chain.D_Chain) {
                                            D_Situate.E_PushDetail(__StandardLibrary::E_ColorizeFront(std::to_string(D_Adresser.D_ChainIndex) + "x" + std::to_string(D_Adresser.D_InChainIndex), 255, 0, 0) + ": " +__StandardLibrary::E_ColorizeFront(D_Adresser.D_Value, 0, 255, 0));
                                        }

                                        D_Situate.E_SetCode(1);
                                    }
                                }
                            }
                        }
                        else {
                            D_Situate.E_SetBody("Request not accepted!");
                            D_Situate.E_PushDetail("Unknow " + __StandardLibrary::E_ColorizeFront("@Argument", 57, 146, 235) + __StandardLibrary::E_ColorizeFront(D_RequestBodyElement.at(1), 255, 0, 0));
                            D_Situate.E_SetCode(0);
                        }
                    }

                    return D_Situate;
                }

                D_Situate.E_SetHeader("__VirtualMemory::Core::E_BridgeAPI");
                D_Situate.E_SetBody("Request not accepted!");

                return D_Situate;
            }
        };
    }

#endif