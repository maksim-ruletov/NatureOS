#ifndef NatureOS_StandardLibrary_SL_Colorizer_hpp
    #define NatureOS_StandardLibrary_SL_Colorizer_hpp 1

    #ifndef _STRING_
        #include <string>
    #endif

    #ifndef NatureOS_StandardLibrary_SL_Situate_hpp
        #include "./SL_Situate.hpp"
    #endif

    #ifndef NatureOS_StandardLibrary_SL_Utilities_hpp
        #include "./SL_Utilities.hpp"
    #endif

    namespace __StandardLibrary {
        std::string E_ColorizeFront (std::string D_Content, int D_Red, int D_Green, int D_Blue) {
            return "\033[38;2;" + std::to_string(D_Red) + ";" + std::to_string(D_Green) + ";" + std::to_string(D_Blue) + "m" + D_Content + "\033[0m";
        }

        std::string E_ColorizeBack (std::string D_Content, int D_Red, int D_Green, int D_Blue) {
            return "\033[48;2;" + std::to_string(D_Red) + ";" + std::to_string(D_Green) + ";" + std::to_string(D_Blue) + "m" + D_Content + "\033[0m";
        }

        class ColorTemplater {
        private:
            Composition D_Templates;
        public:
            ColorTemplater() {}

            Situate E_Push (const std::string S_Name, const std::string S_Start, const std::string S_End) {
                Situate D_Situate;
                D_Situate.E_SetHeader("__StandardLibrary::ColorTemplater::E_Push()");

                for (std::vector<std::string> D_Template : this->D_Templates) {
                    if (D_Template.at(0).compare(S_Name) == 0) {
                        D_Situate.E_SetBody(E_ColorizeFront("@ColorTemplater::E_Push", 197, 57, 235) + " returned error code!");
                        D_Situate.E_SetCode(1);
                        D_Situate.E_PushDetail(E_ColorizeFront("@ColorTemplate", 57, 146, 235) + " with name " + E_ColorizeFront(S_Name, 255, 0, 0) + " already exist!");

                        return D_Situate;
                    }
                }

                this->D_Templates.push_back({ S_Name, S_Start, S_End });

                D_Situate.E_SetCode(0);
                D_Situate.E_SetBody(E_ColorizeFront("@ColorTemplater::E_Push", 197, 57, 235) + " returned success code!");

                return D_Situate;
            }

            Situate E_Wrap (const std::string S_Text, const std::string S_Name) {
                Situate D_Situate;
                D_Situate.E_SetHeader("__StandardLibrary::ColorTemplater::E_Wrap()");

                for (std::vector<std::string> D_Template : this->D_Templates) {
                    if (D_Template.at(0).compare(S_Name) == 0) {
                        D_Situate.E_SetBody(E_ColorizeFront("@ColorTemplater::E_Push", 197, 57, 235) + " returned success code!");
                        D_Situate.E_SetCode(0);
                        D_Situate.E_PushDetail(D_Template.at(1) + S_Text + D_Template.at(2));

                        return D_Situate;
                    }
                }

                D_Situate.E_SetBody(E_ColorizeFront("@ColorTemplater::E_Wrap", 197, 57, 235) + " returned error code!");
                D_Situate.E_PushDetail(E_ColorizeFront("@ColorTemplate", 57, 146, 235) + " with name " + E_ColorizeFront(S_Name, 255, 0, 0) + " don't exist!");
                D_Situate.E_SetCode(1);

                return D_Situate;
            }

            Situate E_DropTable () {
                Situate D_Situate;
                D_Situate.E_SetHeader("__StandardLibrary::ColorTemplater::E_DropTable()");

                D_Situate.E_SetBody(E_ColorizeFront("@ColorTemplater::E_Wrap", 197, 57, 235) + " returned success code!");
                D_Situate.E_SetCode(0);

                for (::size_t D_Iterator = 0; D_Iterator < this->D_Templates.size(); D_Iterator++) {
                    D_Situate.E_PushDetail(this->E_Wrap("Name " + this->D_Templates.at(D_Iterator).at(0), this->D_Templates.at(D_Iterator).at(0)).E_GetDetails().at(0));
                }

                return D_Situate;
            }

            std::string E_GenerateFront (const ::size_t S_Red, const ::size_t S_Green, const ::size_t S_Blue) {
                return "\033[38;2;" + std::to_string(S_Red) + ";" + std::to_string(S_Green) + ";" + std::to_string(S_Blue) + "m";
            }

            std::string E_GenerateBack (const ::size_t S_Red, const ::size_t S_Green, const ::size_t S_Blue) {
                return "\033[48;2;" + std::to_string(S_Red) + ";" + std::to_string(S_Green) + ";" + std::to_string(S_Blue) + "m";
            }
        };
    }

#endif