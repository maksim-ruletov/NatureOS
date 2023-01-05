#ifndef NatureOS_Kernel_K_Configurator_hpp
    #define NatureOS_Kernel_K_Configurator_hpp 1

    #ifndef _STRING_
        #include <string>
    #endif

    #ifndef NatureOS_StandardLibrary_SL_Types_hpp
        #include "../__StandardLibrary/SL_Types.hpp"
    #endif

    #ifndef NatureOS_StandardLibrary_SL_Coordinator_hpp
        #include "../__StandardLibrary/SL_Corrdinator.hpp"
    #endif

    #ifndef NatureOS_Kernel_Drivers_K_D_NakeFS_hpp
        #include "./__Drivers/K_D_NakeFS.hpp"
    #endif

    namespace __Kernel {
        class CFile {
        private:
            std::string I_Filename;
            __StandardLibrary::_Composition I_Scope;
        public:
            CFile () {}

            CFile (std::string D_Filename) {
                if (D_Filename.find(".config") == std::string::npos) {
                    D_Filename += ".config";
                }

                if (__Drivers::E_FileExist(D_Filename).E_GetCode() != 0) {
                    __Drivers::E_CreateFile(D_Filename);
                }

                this->I_Filename = D_Filename;
            }

            __StandardLibrary::Corrdinator E_Parse () {
                __StandardLibrary::Corrdinator D_Corrdinator;
                D_Corrdinator.E_SetupSender("__Kernel::@CFile.E_Parse()");

                std::vector<std::string> D_Content = __Drivers::E_ReadFile(this->I_Filename).E_GetDetails();

                std::vector<std::string> D_RegistredNames;

                for (std::string D_Line : D_Content) {
                    std::string D_Name = __StandardLibrary::E_Split(D_Line, "=").at(0);
                    std::string D_Value = __StandardLibrary::E_Split(D_Line, "=").at(1);

                    if (__StandardLibrary::E_Has(D_RegistredNames, D_Name)) {
                        continue;
                    }
                    else {
                        this->I_Scope.push_back({ D_Name, D_Value });
                    }
                }

                D_Corrdinator.E_SetupBody("file successfully parsed!");
                D_Corrdinator.E_PushData("0");

                return D_Corrdinator;
            }

            __StandardLibrary::Corrdinator E_Get (std::string D_Name) {
                __StandardLibrary::Corrdinator D_Corrdinator;
                D_Corrdinator.E_SetupSender("__Kernel::@CFile.E_Get()");

                for (std::vector<std::string> E_ScopeItem : this->I_Scope) {
                    if (E_ScopeItem.at(0).compare(D_Name) == 0) {
                        D_Corrdinator.E_SetupBody("item successfully founded!");
                        D_Corrdinator.E_PushData("0");
                        D_Corrdinator.E_PushData(E_ScopeItem.at(1));

                        return D_Corrdinator;
                    }
                }

                D_Corrdinator.E_SetupBody("item not found!");
                D_Corrdinator.E_PushData("1");

                return D_Corrdinator;
            }

            __StandardLibrary::Corrdinator E_Set (std::string D_Name, std::string D_Value) {
                __StandardLibrary::Corrdinator D_Corrdinator;
                D_Corrdinator.E_SetupSender("__Kernel::@CFile.E_Set()");
                ::size_t D_Iterator = 0;

                for (std::vector<std::string> E_ScopeItem : this->I_Scope) {
                    if (E_ScopeItem.at(0).compare(D_Name) == 0) {
                        this->I_Scope.at(D_Iterator)[1] = D_Value;

                        D_Corrdinator.E_SetupBody("item successfully changed!");
                        D_Corrdinator.E_PushData("0");

                        return D_Corrdinator;
                    }

                    D_Iterator++;
                }

                D_Corrdinator.E_SetupBody("item not found!");
                D_Corrdinator.E_PushData("1");

                return D_Corrdinator;
            }

            __StandardLibrary::Corrdinator E_Push (std::string D_Name, std::string D_Value) {
                __StandardLibrary::Corrdinator D_Corrdinator;
                D_Corrdinator.E_SetupSender("__Kernel::@CFile.E_Push()");

                for (std::vector<std::string> D_ScopeItem : this->I_Scope) {
                    if (D_ScopeItem.at(0).compare(D_Name) == 0) {
                        D_Corrdinator.E_SetupBody("name already in use!");
                        D_Corrdinator.E_PushData("1");

                        return D_Corrdinator;
                    }
                }

                this->I_Scope.push_back({ D_Name, D_Value });

                D_Corrdinator.E_SetupBody("item successfully added!");
                D_Corrdinator.E_PushData("0");

                return D_Corrdinator;
            }

            __StandardLibrary::Corrdinator E_DropContent () {
                __StandardLibrary::Corrdinator D_Corrdinator;
                D_Corrdinator.E_SetupSender("__Kernel::@CFile.E_DropContent()");

                std::string D_Content;

                for (std::vector<std::string> D_ScopeItem : this->I_Scope) {
                    D_Content += D_ScopeItem.at(0) + "=" + D_ScopeItem.at(1) + "\n";
                }

                __Drivers::E_Rewrite(this->I_Filename, D_Content);

                D_Corrdinator.E_SetupBody("file writed!");
                D_Corrdinator.E_PushData("0");

                return D_Corrdinator;
            }

            void E_OpenFile (std::string D_Filename) {
                if (D_Filename.find(".config") == std::string::npos) {
                    D_Filename += ".config";
                }

                if (__Drivers::E_FileExist(D_Filename).E_GetCode() != 0) {
                    __Drivers::E_CreateFile(D_Filename);
                }

                this->I_Filename = D_Filename;
            }
        };
    }

#endif