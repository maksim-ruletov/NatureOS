#ifndef NatureOS_Kernel_K_PathManager_hpp
    #define NatureOS_Kernel_K_PathManager_hpp 1

    #ifndef _STRING_
        #include <string>
    #endif

    #ifndef _VECTOR_
        #include <vector>
    #endif

    #ifndef NatureOS_Kernel_Drivers_K_D_NakeFS_hpp
        #include "./__Drivers/K_D_NakeFS.hpp"
    #endif

    #ifndef NatureOS_StandardLibrary_SL_Situate_hpp
        #include "../__StandardLibrary/SL_Situate.hpp"
    #endif

    #ifndef NatureOS_StandardLibrary_SL_Utilities_hpp
        #include "../__StandardLibrary/SL_Utilities.hpp"
    #endif

    namespace __Kernel {
        class Path {
        private:
            std::string D_CurrentPath = "/";
            std::string D_StartPoint;
            std::vector<std::string> D_SystemRoutes;
        public:
            Path (const std::string S_StartPoint, std::vector<std::string> S_SystemRoutes) {
                this->D_StartPoint = S_StartPoint;
                this->D_SystemRoutes = S_SystemRoutes;
            }

            __StandardLibrary::Situate E_Append (std::string D_NewPath) {
                __StandardLibrary::Situate D_Situate;
                D_Situate.E_SetHeader("__Kernel::Path::E_Append()");

                if (D_NewPath[0] == '/') {
                    D_NewPath.erase(D_NewPath.begin());
                }

                if (D_NewPath[D_NewPath.size() - 1] != '/') {
                    D_NewPath.push_back('/');
                }

                this->D_CurrentPath += D_NewPath;

                D_Situate.E_SetBody(__StandardLibrary::E_ColorizeFront("@Path::E_Append", 197, 57, 235) + " returned success code!");
                D_Situate.E_SetCode(0);

                return D_Situate;
            }

            void E_Remove () {
                std::vector<std::string> S_ParsedCurrentPath = __StandardLibrary::E_Split(this->D_CurrentPath, "/");
                
                S_ParsedCurrentPath.pop_back();
                S_ParsedCurrentPath.pop_back();

                this->D_CurrentPath = "/";

                if (S_ParsedCurrentPath.size() > 1) {
                    for (std::string S_PathPart : S_ParsedCurrentPath) {
                        this->D_CurrentPath += S_PathPart + "/";
                    }
                }
            }

            std::string E_DropCurrentPath () {
                return this->D_CurrentPath;
            }
        };
    }

#endif