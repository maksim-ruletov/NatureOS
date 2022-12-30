#ifndef NatureOS_StandardLibrary_SL_Situate_hpp
    #define NatureOS_StandardLibrary_SL_Situate_hpp 1

    #ifndef _STRING_
        #include <string>
    #endif

    #ifndef _VECTOR_
        #include <vector>
    #endif

    namespace __StandardLibrary {
        class Situate {
        private:
            std::string D_Header;
            std::string D_Body;
            ::size_t D_Code;
            std::vector<std::string> D_Details;
        public:
            void E_SetHeader (const std::string S_NewHeader) { this->D_Header = S_NewHeader; }
            void E_SetBody (const std::string S_NewBody) { this->D_Body = S_NewBody; }
            void E_SetCode (const ::size_t S_NewCode) { this->D_Code = S_NewCode; }
            void E_PushDetail (const std::string S_NewDetail) { this->D_Details.push_back(S_NewDetail); }
            void E_ClearDetail () { this->D_Details.clear(); }

            std::string E_GetHeader () { return this->D_Header; }
            std::string E_GetBody () { return this->D_Body; }
            ::size_t E_GetCode () { return this->D_Code; }
            std::vector<std::string> E_GetDetails () { return this->D_Details; }
        };
    }

#endif