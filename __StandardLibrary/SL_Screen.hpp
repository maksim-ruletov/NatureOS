#ifndef NatureOS_StandardLibrary_SL_Screen_hpp
    #define NatureOS_StandardLibrary_SL_Screen_hpp 1

    #ifndef _IOSTREAM_
        #include <iostream>
    #endif

    #ifndef _STRING_
        #include <string>
    #endif

    namespace __StandardLibrary {
        void E_Output (std::string D_Content) {
            std::cout << D_Content;
        }

        void E_Input (std::string& D_InputString) {
            std::getline(std::cin, D_InputString);
        }
    } /* Include screen manipulation methods */
    
#endif