#ifndef NatureOS_StandardLibrary_SL_Debug_hpp
    #define NatureOS_StandardLibrary_SL_Debug_hpp 1

    #ifndef NatureOS_StandardLibrary_SL_Situate_hpp
        #include "./SL_Situate.hpp"
    #endif

    #ifndef NatureOS_StandardLibrary_SL_Screen_hpp
        #include "./SL_Screen.hpp"
    #endif

    #ifndef NatureOS_StandardLibrary_SL_Utilities_hpp
        #include "./SL_Utilities.hpp"
    #endif

    #ifndef NatureOS_StandardLibrary_SL_Screen_hpp
        #include "./SL_Screen.hpp"
    #endif

    namespace __StandardLibrary {
        void E_EnterDebugMessage (Situate D_Situate) {
            std::string D_OutputMessage;

            D_OutputMessage += "\n\t" +  D_Situate.E_GetHeader();
            D_OutputMessage += " responded: \n";
            D_OutputMessage += "\t" + D_Situate.E_GetBody() + "\n";
            
            if (D_Situate.E_GetDetails().size() > 0) {
                for (std::string D_CurrentDetail : D_Situate.E_GetDetails()) {
                    D_OutputMessage += "\n\t" + D_CurrentDetail;
                }
            }
                
            D_OutputMessage += "\n\n";

            E_Output(D_OutputMessage);
        }

        class Debugger {
        public:
            /* This module can use BridgeAPI */
            bool E_Bridge () { return true; }

            Situate E_BridgeAPI (std::string D_RequestHeader, Composition D_RequestBody) {
                Situate D_Situate;
                D_Situate.E_SetHeader("__StandardLibrary::Debugger::E_BridgeAPI()");

                if (D_RequestHeader.compare("debug") == 0) {
                    std::string D_DebugText = D_RequestBody.at(0).at(1);

                    E_Output(D_DebugText);

                    D_Situate.E_SetCode(0);
                    return D_Situate;
                }
                
                D_Situate.E_SetCode(1);
                return D_Situate;
            }
        };
    }

#endif