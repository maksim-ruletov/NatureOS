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
        std::string E_ColorizeFont (const std::string S_Content, const ::size_t S_Red, const ::size_t S_Green, const ::size_t S_Blue) {
            return "\033[38;2;" + std::to_string(S_Red) + ";" + std::to_string(S_Green) + ";" + std::to_string(S_Blue) + "m" + S_Content + "\033[0m";
        }

        std::string E_ColorizeBackground (const std::string S_Content, const ::size_t S_Red, const ::size_t S_Green, const ::size_t S_Blue) {
            return "\033[48;2;" + std::to_string(S_Red) + ";" + std::to_string(S_Green) + ";" + std::to_string(S_Blue) + "m" + S_Content + "\033[0m";
        }

        /**
         * Create color template to use it in future.
         * 
         * First - name your template (don't repeat yourself), next -
         * generate first part with method E_GenerateFont() or
         * E_GenerateBackground().
         * 
         * If you want to use your template - use method E_Wrap()
         * But if you forgor template name E_DropTable() will help you!
         */
        class ColorTemplater {
        private:
            Composition I_Templates;
        public:
            Situate E_Push (const std::string S_Name, const std::string S_Start, const std::string S_End) {
                Situate D_Situate;
                D_Situate.E_SetHeader("__StandardLibrary::ColorTemplater::E_Push()");

                for (std::vector<std::string> D_Template : this->I_Templates) {
                    if (D_Template.at(0).compare(S_Name) == 0) {
                        D_Situate.E_SetBody(E_ColorizeFont("@ColorTemplater::E_Push", 197, 57, 235) + " returned error code!");
                        D_Situate.E_SetCode(1);
                        D_Situate.E_PushDetail(E_ColorizeFont("@ColorTemplate", 57, 146, 235) + " with name " + E_ColorizeFont(S_Name, 255, 0, 0) + " already exist!");

                        return D_Situate;
                    }
                }

                this->I_Templates.push_back({ S_Name, S_Start, S_End });

                D_Situate.E_SetCode(0);
                D_Situate.E_SetBody(E_ColorizeFont("@ColorTemplater::E_Push", 197, 57, 235) + " returned success code!");

                return D_Situate;
            }

            Situate E_Wrap (const std::string S_Text, const std::string S_Name) {
                Situate D_Situate;
                D_Situate.E_SetHeader("__StandardLibrary::ColorTemplater::E_Wrap()");

                for (std::vector<std::string> I_Templates : this->I_Templates) {
                    if (I_Templates.at(0).compare(S_Name) == 0) {
                        D_Situate.E_SetBody(E_ColorizeFont("@ColorTemplater::E_Push", 197, 57, 235) + " returned success code!");
                        D_Situate.E_SetCode(0);
                        D_Situate.E_PushDetail(I_Templates.at(1) + S_Text + I_Templates.at(2));

                        return D_Situate;
                    }
                }

                D_Situate.E_SetBody(E_ColorizeFont("@ColorTemplater::E_Wrap", 197, 57, 235) + " returned error code!");
                D_Situate.E_PushDetail(E_ColorizeFont("@ColorTemplate", 57, 146, 235) + " with name " + E_ColorizeFont(S_Name, 255, 0, 0) + " don't exist!");
                D_Situate.E_SetCode(1);

                return D_Situate;
            }

            Situate E_DropTable () {
                Situate D_Situate;
                D_Situate.E_SetHeader("__StandardLibrary::ColorTemplater::E_DropTable()");

                D_Situate.E_SetBody(E_ColorizeFont("@ColorTemplater::E_DropTable", 197, 57, 235) + " returned success code!");
                D_Situate.E_SetCode(0);

                for (::size_t D_Iterator = 0; D_Iterator < this->I_Templates.size(); D_Iterator++) {
                    D_Situate.E_PushDetail("Name: " + this->E_Wrap(this->I_Templates.at(D_Iterator).at(0), this->I_Templates.at(D_Iterator).at(0)).E_GetDetails().at(0));
                }

                return D_Situate;
            }

            std::string E_GenerateFont (const ::size_t S_Red, const ::size_t S_Green, const ::size_t S_Blue) {
                return "\033[38;2;" + std::to_string(S_Red) + ";" + std::to_string(S_Green) + ";" + std::to_string(S_Blue) + "m";
            }

            std::string E_GenerateBackground (const ::size_t S_Red, const ::size_t S_Green, const ::size_t S_Blue) {
                return "\033[48;2;" + std::to_string(S_Red) + ";" + std::to_string(S_Green) + ";" + std::to_string(S_Blue) + "m";
            }
        };
    } /* Include function to colorize text and Template system */

#endif