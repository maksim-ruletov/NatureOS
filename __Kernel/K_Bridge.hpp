#ifndef NatureOS_Kernel_K_Bridge_hpp
    #define NatureOS_Kernel_K_Bridge_hpp 1

    #ifndef NatureOS_StandardLibrary_SL_Situate_hpp
        #include "../__StandardLibrary/SL_Situate.hpp"
    #endif

    #ifndef NatureOS_StandardLibrary_SL_Utilities_hpp
        #include "../__StandardLibrary/SL_Utilities.hpp"
    #endif

    namespace __Kernel {
        template <class T>
        __StandardLibrary::Situate E_Request(T& D_Getter, std::string D_Request) {
            __StandardLibrary::Situate D_Situate;
            D_Situate.E_SetHeader("__Kernel::E_Request()");
            __StandardLibrary::Composition D_Composition;

            if (!D_Getter.E_Bridge()) {
                D_Situate.E_SetBody(__StandardLibrary::E_ColorizeFront("::E_Request", 197, 57, 235) + " returned error code!");
                D_Situate.E_PushDetail(__StandardLibrary::E_ColorizeFront("@Getter", 57, 146, 235) + " blocked BridgeAPI!");
                D_Situate.E_SetCode(1);

                return D_Situate;
            }
            
            std::vector<std::string> D_ParsedRequest = __StandardLibrary::E_Split(D_Request, " ");
            std::string D_Command = D_ParsedRequest.at(0);

            D_ParsedRequest = __StandardLibrary::E_Delete(D_ParsedRequest, 0);

            for (std::string D_ParsedRequestElement : D_ParsedRequest) {
                D_Composition.push_back({ "argument", D_ParsedRequestElement });
            }

            return D_Getter.E_BridgeAPI(D_Command, D_Composition);
        }
    }

#endif