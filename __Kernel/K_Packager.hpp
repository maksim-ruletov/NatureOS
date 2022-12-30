#ifndef NatureOS_Kernel_K_Packager_hpp
    #define NatureOS_Kernel_K_Packager_hpp 1

    #ifndef NatureOS_StandardLibrary_SL_Utilities_hpp
        #include "../__StandardLibrary/SL_Utilities.hpp"
    #endif

    #ifndef NatureOS_Kernel_Drivers_K_D_NakeFS_hpp
        #include "./__Drivers/K_D_NakeFS.hpp"
    #endif

    #ifndef _STRING_
        #include <string>
    #endif

    #ifndef _ALGORITHM_
        #include <algorithm>
    #endif
    
    namespace __Kernel {
        struct Pack {
            std::vector<std::vector<std::string>> D_Scope;
        };

        class Packager {
        private:
            std::string D_FilePath;
            std::vector<Pack> D_Scope;
        public:
            Packager () {}

            Packager (std::string D_OutFilePath) {
                if (D_OutFilePath.find(".package") == std::string::npos) {
                    D_OutFilePath += ".package";
                }

                this->D_FilePath = D_OutFilePath;
            }

            __StandardLibrary::Situate E_Analysis () {
                __StandardLibrary::Situate D_Situate;
                D_Situate.E_SetHeader("__Kernel::Packager::E_Analysis()");

                D_Situate = __Drivers::E_ReadFile(this->D_FilePath);
                std::vector<std::string> D_Lines = D_Situate.E_GetDetails();
                std::vector<std::vector<::size_t>> D_Positions;
                D_Situate.E_ClearDetail();

                if (D_Lines.size() > 0 && D_Lines.at(0).compare("{") != 0) {
                    D_Situate.E_PushDetail("Line #1: no open figure bracket!");
                }

                for (::size_t D_Iterator = 0; D_Iterator < D_Lines.size(); D_Iterator++) {
                    if (D_Lines.at(D_Iterator).compare("{") != 0 && D_Lines.at(D_Iterator).compare("}") != 0) {
                        if (D_Lines.at(D_Iterator).find(";") == std::string::npos) {
                            D_Situate.E_PushDetail("Line #" + std::to_string(D_Iterator + 1) + ": no close semicolon!");
                        }
                    }
                }

                if (D_Situate.E_GetDetails().size() > 0) {
                    D_Situate.E_SetBody(__StandardLibrary::E_ColorizeFront("@Packager::E_Analysis", 197, 57, 235) + " found errors!");
                    D_Situate.E_SetCode(0);

                    return D_Situate;
                }

                D_Situate.E_SetBody(__StandardLibrary::E_ColorizeFront("@Packager::E_Analysis", 197, 57, 235) + " found 0 errors!");
                D_Situate.E_SetCode(1);

                return D_Situate;
            }

            __StandardLibrary::Situate E_Parse () {
                __StandardLibrary::Situate D_Situate;
                D_Situate.E_SetHeader("__Kernel::Packager::E_Handle()");

                if (__Drivers::E_FileExist(this->D_FilePath).E_GetCode() == 1) {
                    D_Situate.E_SetBody(__StandardLibrary::E_ColorizeFront("@Packager::E_Handle", 197, 57, 235) + " returned error code!");
                    D_Situate.E_PushDetail(__StandardLibrary::E_ColorizeFront("@Packager", 57, 146, 235) + " not found " + __StandardLibrary::E_ColorizeFront("@File", 57, 146, 235) + " with name " + __StandardLibrary::E_ColorizeFront(this->D_FilePath, 255, 0, 0));
                    D_Situate.E_SetCode(1);

                    return D_Situate;
                }

                D_Situate = __Drivers::E_ReadFile(this->D_FilePath);
                std::vector<std::string> D_Lines = D_Situate.E_GetDetails();
                std::vector<std::vector<::size_t>> D_Positions;
                D_Situate.E_ClearDetail();

                if (this->E_Analysis().E_GetCode() != 1) {
                    return this->E_Analysis();
                }

                for (::size_t D_Iterator = 0; D_Iterator < D_Lines.size(); D_Iterator++) {
                    if (D_Lines.at(D_Iterator).compare("{") == 0) {
                        std::vector<::size_t> D_Position;

                        D_Position.push_back(D_Iterator);

                        for (::size_t D_IteratorC = D_Iterator; D_IteratorC < D_Lines.size(); D_IteratorC++) {
                            if (D_Lines.at(D_IteratorC).compare("}") == 0) {
                                D_Position.push_back(D_IteratorC);
                                break;
                            }
                        }

                        D_Positions.push_back(D_Position);
                    }
                }

                // Get all blocks positions
                // for (::size_t D_Iterator = 0; D_Iterator < D_Positions.size(); D_Iterator++) {
                //     D_Situate.E_PushDetail("Block #" + std::to_string(D_Iterator) + " start: " + std::to_string(D_Positions.at(D_Iterator).at(0)));
                //     D_Situate.E_PushDetail("Block #" + std::to_string(D_Iterator) + " end: " + std::to_string(D_Positions.at(D_Iterator).at(1)));
                // }

                std::vector<std::string> D_RegistredNames;

                for (::size_t D_Iterator = 0; D_Iterator < D_Positions.size(); D_Iterator++) {
                    std::vector<::size_t> D_Position = D_Positions.at(D_Iterator);
                    Pack D_Pack;

                    for (::size_t D_IteratorC = D_Position.at(0) + 1; D_IteratorC < D_Position.at(1); D_IteratorC++) {
                        std::vector<std::string> D_NamePlusKey;

                        std::string D_Key = __StandardLibrary::E_Split(D_Lines.at(D_IteratorC), ":").at(0);
                        std::string::iterator D_Key__end_pos = std::remove(D_Key.begin(), D_Key.end(), ' ');
                        D_Key.erase(D_Key__end_pos, D_Key.end());

                        if (__StandardLibrary::E_Has(D_RegistredNames, D_Key)) {
                            D_Situate.E_SetBody(__StandardLibrary::E_ColorizeFront("@Packager::E_Handle", 197, 57, 235) + " returned error code!");
                            D_Situate.E_PushDetail(__StandardLibrary::E_ColorizeFront("@Scope", 57, 146, 235) + " already contains " + __StandardLibrary::E_ColorizeFront("@Key", 57, 146, 235) + " with name " + __StandardLibrary::E_ColorizeFront(D_Key, 255, 0, 0) + "! [Line: " + std::to_string(D_IteratorC + 1) + "]");
                            D_Situate.E_SetCode(0);

                            return D_Situate;
                        }

                        D_NamePlusKey.push_back(D_Key);
                        
                        std::string D_Value = __StandardLibrary::E_Split(D_Lines.at(D_IteratorC), ":").at(1);
                        std::string::iterator D_Value__end_pos = std::remove(D_Value.begin(), D_Value.end(), ' ');
                        D_Value.erase(D_Value__end_pos, D_Value.end());
                        D_Value.pop_back();

                        D_NamePlusKey.push_back(D_Value);

                        D_Pack.D_Scope.push_back(D_NamePlusKey);
                        D_RegistredNames.push_back(D_Key);
                    }

                    this->D_Scope.push_back(D_Pack);
                }

                D_Situate.E_SetBody(__StandardLibrary::E_ColorizeFront("@Packager::E_Handle", 197, 57, 235) + " returned success code!");
                D_Situate.E_PushDetail(__StandardLibrary::E_ColorizeFront("@File", 57, 146, 235) + " successfully parsed!");
                D_Situate.E_SetCode(1);

                return D_Situate;
            }

            __StandardLibrary::Situate E_EditValue (::size_t D_PackIndex, ::size_t D_MergeIndex, std::string D_NewValue) {
                __StandardLibrary::Situate D_Situate;
                D_Situate.E_SetHeader("__Kernel::Packager::E_EditValue()");

                if (this->D_Scope.size() < 1) {
                    D_Situate.E_SetBody(__StandardLibrary::E_ColorizeFront("@Packager::E_EditValue", 197, 57, 235) + " returned error code!");
                    D_Situate.E_PushDetail(__StandardLibrary::E_ColorizeFront("@Scope", 57, 146, 235) + " is empty!");
                    D_Situate.E_SetCode(0);

                    return D_Situate;
                }

                if (D_PackIndex > this->D_Scope.size() - 1) {
                    D_Situate.E_SetBody(__StandardLibrary::E_ColorizeFront("@Packager::E_EditValue", 197, 57, 235) + " returned error code!");
                    D_Situate.E_PushDetail(__StandardLibrary::E_ColorizeFront("@Pack", 57, 146, 235) + " with index " + std::to_string(D_PackIndex) + " not exist!");
                    D_Situate.E_SetCode(0);

                    return D_Situate;
                }

                this->D_Scope.at(D_PackIndex).D_Scope.at(D_MergeIndex).pop_back();
                this->D_Scope.at(D_PackIndex).D_Scope.at(D_MergeIndex).push_back(D_NewValue);

                D_Situate.E_SetBody(__StandardLibrary::E_ColorizeFront("@Packager::E_EditValue", 197, 57, 235) + " returned success code!");
                D_Situate.E_PushDetail(__StandardLibrary::E_ColorizeFront("@Key", 57, 146, 235) + " with name " + __StandardLibrary::E_ColorizeFront(this->D_Scope.at(D_PackIndex).D_Scope.at(D_MergeIndex).at(0), 255, 0, 0) + " now set to " + __StandardLibrary::E_ColorizeFront(this->D_Scope.at(D_PackIndex).D_Scope.at(D_MergeIndex).at(1), 255, 0, 0));
                D_Situate.E_SetCode(1);

                return D_Situate;
            }

            __StandardLibrary::Situate E_Push (::size_t D_PackIndex, std::string D_Key, std::string D_Value) {
                __StandardLibrary::Situate D_Situate;
                D_Situate.E_SetHeader("__Kernel::Packager::E_Push()");

                if (this->D_Scope.size() < 1) {
                    D_Situate.E_SetBody(__StandardLibrary::E_ColorizeFront("@Packager::E_Push", 197, 57, 235) + " returned error code!");
                    D_Situate.E_PushDetail(__StandardLibrary::E_ColorizeFront("@Scope", 57, 146, 235) + " is empty!");
                    D_Situate.E_SetCode(0);

                    return D_Situate;
                }

                if (D_PackIndex > this->D_Scope.size() - 1) {
                    D_Situate.E_SetBody(__StandardLibrary::E_ColorizeFront("@Packager::E_Push", 197, 57, 235) + " returned error code!");
                    D_Situate.E_PushDetail(__StandardLibrary::E_ColorizeFront("@Pack", 57, 146, 235) + " with index " + std::to_string(D_PackIndex) + " not exist!");
                    D_Situate.E_SetCode(0);

                    return D_Situate;
                }

                this->D_Scope.at(D_PackIndex).D_Scope.push_back({ D_Key, D_Value });

                D_Situate.E_SetBody(__StandardLibrary::E_ColorizeFront("@Packager::E_Push", 197, 57, 235) + " returned success code!");
                D_Situate.E_SetCode(1);

                return D_Situate;
            }

            __StandardLibrary::Situate E_GetValue (::size_t D_PackIndex, std::string D_Name) {
                __StandardLibrary::Situate D_Situate;
                D_Situate.E_SetHeader("__Kernel::Packager::E_GetValue()");

                if (this->D_Scope.size() == 0) {
                    D_Situate.E_SetBody(__StandardLibrary::E_ColorizeFront("@Packager::E_GetValue", 197, 57, 235) + " returned error code!");
                    D_Situate.E_PushDetail(__StandardLibrary::E_ColorizeFront("@Scope", 57, 146, 235) + " is empty!");
                    D_Situate.E_SetCode(0);

                    return D_Situate;
                }

                if (D_PackIndex > this->D_Scope.size() - 1) {
                    D_Situate.E_SetBody(__StandardLibrary::E_ColorizeFront("@Packager::E_GetValue", 197, 57, 235) + " returned error code!");
                    D_Situate.E_PushDetail(__StandardLibrary::E_ColorizeFront("@Pack", 57, 146, 235) + " with index " + std::to_string(D_PackIndex) + " not exist!");
                    D_Situate.E_SetCode(0);

                    return D_Situate;
                }

                Pack D_Pack = this->D_Scope.at(D_PackIndex);

                for (::size_t D_Iterator = 0; D_Iterator < D_Pack.D_Scope.size(); D_Iterator++) {
                    if (D_Pack.D_Scope.at(D_Iterator).at(0).compare("\t" + D_Name) == 0) {
                        D_Situate.E_SetBody("Value successfully founded!");
                        D_Situate.E_PushDetail(D_Pack.D_Scope.at(D_Iterator).at(1));
                        D_Situate.E_SetCode(0);

                        return D_Situate;
                    }
                }

                D_Situate.E_PushDetail(__StandardLibrary::E_ColorizeFront("@Value", 57, 146, 235) + " with " + __StandardLibrary::E_ColorizeFront("@Key", 57, 146, 235) + " " + __StandardLibrary::E_ColorizeFront(D_Name, 255, 0, 0) + " not found!");
                D_Situate.E_SetCode(1);

                return D_Situate;
            }

            __StandardLibrary::Situate E_Pack () {
                __StandardLibrary::Situate D_Situate;
                D_Situate.E_SetHeader("__Kernel::Packager::E_Push()");

                Pack D_Pack;
                this->D_Scope.push_back(D_Pack);

                D_Situate.E_SetBody(__StandardLibrary::E_ColorizeFront("@Packager::E_Pack", 197, 57, 235) + " returned success code!");
                D_Situate.E_SetCode(0);

                return D_Situate;
            }

            __StandardLibrary::Situate E_Stringify () {
                __StandardLibrary::Situate D_Situate;
                D_Situate.E_SetHeader("__Kernel::Packager::E_Stringify()");

                if (this->D_Scope.size() == 0) {
                    D_Situate.E_SetBody(__StandardLibrary::E_ColorizeFront("@Packager::E_Stringify", 197, 57, 235) + " returned error code!");
                    D_Situate.E_PushDetail(__StandardLibrary::E_ColorizeFront("@Scope", 57, 146, 235) + " is empty!");
                    D_Situate.E_SetCode(1);

                    return D_Situate;
                }

                std::string D_StringifiedContent = "";

                for (::size_t D_Iterator = 0; D_Iterator < this->D_Scope.size(); D_Iterator++) {
                    D_StringifiedContent += "{\n";

                    Pack D_Pack = this->D_Scope.at(D_Iterator);

                    for (std::vector<std::string> D_PackItem : D_Pack.D_Scope) {
                        D_StringifiedContent += "\t" + D_PackItem.at(0) + ": " + D_PackItem.at(1) + ";\n";
                    }

                    D_StringifiedContent += "}";

                    if (D_Iterator != this->D_Scope.size() - 1) {
                        D_StringifiedContent += "\n";
                    }
                }

                D_Situate.E_SetBody(__StandardLibrary::E_ColorizeFront("@Packager::E_Stringify", 197, 57, 235) + " returned success code!");
                D_Situate.E_PushDetail(D_StringifiedContent);
                D_Situate.E_SetCode(1);

                return D_Situate;
            }

            __StandardLibrary::Situate E_GetFilePath () {
                __StandardLibrary::Situate D_Situate;
                D_Situate.E_SetHeader("__Kernel::Packager::E_GetFilePath()");

                D_Situate.E_SetBody(__StandardLibrary::E_ColorizeFront("@Packager::E_GetFilePath", 197, 57, 235) + " returned success code!");
                D_Situate.E_PushDetail(this->D_FilePath);
                D_Situate.E_SetCode(1);

                return D_Situate;
            }

            std::vector<Pack> E_DropBase () {
                return this->D_Scope;
            }
        };
    }

#endif