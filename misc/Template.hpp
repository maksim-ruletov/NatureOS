#ifndef NatureOS_StandardLibrary_SL_Template_hpp
    #define NatureOS_StandardLibrary_SL_Template_hpp 1

    #ifndef _VECTOR_
        #include <vector>
    #endif

    #ifndef _STRING_
        #include <string>
    #endif

    #ifndef NatureOS_StandardLibrary_SL_Utilities_hpp
        #include "./SL_Utilities.hpp"
    #endif

    #ifndef NatureOS_StandardLibrary_SL_Situate_hpp
        #include "./SL_Situate.hpp"
    #endif

    #ifndef NatureOS_StandardLibrary_SL_Colorizer_hpp
        #include "./SL_Colorizer.hpp"
    #endif

    namespace __StandardLibrary {
        /**
         * Universal Template Mechanism (UTM)
         * 
         * Create and get string-based templates!
         */
        class Templater {
        private:
            /* All templates */
            Composition D_Templates;
        public:
            /* Empty constructor */
            Templater () {}

            /**
             * Push template.
             * 
             * @param S_TemplateName
             * @param S_Template
             */
            Situate E_Push (const std::string S_TemplateName, const std::string S_Template) {
                Situate D_Situate;
                D_Situate.E_SetHeader("__StandardLibrary::Templater::E_Push()");

                for (std::vector<std::string> D_Template : this->D_Templates) {
                    if (D_Template.at(0).compare(S_TemplateName) == 0) {
                        D_Situate.E_SetBody(__StandardLibrary::E_ColorizeFont("@Templater::E_Push", 197, 57, 235) + " returned error code!");
                        D_Situate.E_PushDetail(__StandardLibrary::E_ColorizeFont("@Template", 57, 146, 235) + " with name " + __StandardLibrary::E_ColorizeFont(S_TemplateName, 255, 0, 0) + " already saved!");
                        D_Situate.E_SetCode(1);

                        return D_Situate;
                    }
                }

                this->D_Templates.push_back({ S_TemplateName, S_Template });

                D_Situate.E_SetBody(__StandardLibrary::E_ColorizeFont("@Templater::E_Push", 197, 57, 235) + " returned success code!");
                D_Situate.E_PushDetail(__StandardLibrary::E_ColorizeFont("@Template", 57, 146, 235) + " successfully saved!");
                D_Situate.E_SetCode(0);

                return D_Situate;
            }

            /**
             * Drop template
             * 
             * @param S_TemplateName
             */
            Situate E_Drop (const std::string S_TemplateName) {
                Situate D_Situate;
                D_Situate.E_SetHeader("__StandardLibrary::Templater::E_Drop()");

                for (std::vector<std::string> D_Template : this->D_Templates) {
                    if (D_Template.at(0).compare(S_TemplateName) == 0) {
                        D_Situate.E_SetBody(__StandardLibrary::E_ColorizeFont("@Templater::E_Drop", 197, 57, 235) + " returned success code!");
                        D_Situate.E_PushDetail(D_Template.at(1));
                        D_Situate.E_SetCode(0);

                        return D_Situate;
                    }
                }

                D_Situate.E_SetBody(__StandardLibrary::E_ColorizeFont("@Templater::E_Drop", 197, 57, 235) + " returned error code!");
                D_Situate.E_PushDetail(__StandardLibrary::E_ColorizeFont("@Template", 57, 146, 235) + " with name " + __StandardLibrary::E_ColorizeFont(S_TemplateName, 255, 0, 0) + " not exist!");
                D_Situate.E_SetCode(1);

                return D_Situate;
            }
        };
    } /* Include UTM module */

#endif