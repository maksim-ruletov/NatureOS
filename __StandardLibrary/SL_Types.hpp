#ifndef NatureOS_StandardLibrary_SL_Types_hpp
    #define NatureOS_StandardLibrary_SL_Types_hpp 1

    #ifndef _VECTOR_
        #include <vector>
    #endif

    #ifndef _STRING_
        #include <string>
    #endif

    namespace __StandardLibary {
        typedef std::vector<std::string> _CompositionPart;
        typedef std::vector<std::vector<std::string>> _Composition;
    } /* Include custom types */

#endif