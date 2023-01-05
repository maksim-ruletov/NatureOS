#ifndef NatureOS_StandardLibrary_SL_Types_hpp
    #define NatureOS_StandardLibrary_SL_Types_hpp 1

    #ifndef _VECTOR_
        #include <vector>
    #endif

    #ifndef _STRING_
        #include <string>
    #endif

    namespace __StandardLibrary {
        typedef std::vector<std::string> _CompositionPart;
        typedef std::vector<std::vector<std::string>> _Composition;
        typedef std::vector<std::vector<::size_t>> _SizeComposition;
        typedef std::vector<::size_t> _SizeCompositionPart;
    } /* Include custom types */

#endif