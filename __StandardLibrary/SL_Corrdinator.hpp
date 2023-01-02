#ifndef NatureOS_StandardLibrary_SL_Coordinator_hpp
    #define NatureOS_StandardLibrary_SL_Coordinator_hpp 1

    #ifndef _STRING_
        #include <string>
    #endif

    #ifndef _VECTOR_
        #include <vector>
    #endif

    namespace __StandardLibrary {
        /**
         * This class allows modules to interact with each other
         * and conveniently exchange data.
         */
        class Corrdinator {
        private:
            std::string I_Sender; /* Sender of data (function or module) */
            std::string I_Body; /* Data description */
            std::vector<std::string> I_Data; /* Sending data */
        public:
            void E_SetupSender (const std::string S_Sender) {
                this->I_Sender = S_Sender;
            }

            void E_SetupBody (const std::string S_BodyContent) {
                this->I_Body = S_BodyContent;
            }

            void E_PushData (const std::string S_Data) {
                this->I_Data.push_back(S_Data);
            }

            std::string E_DropSender () {
                return this->I_Sender;
            }

            std::string E_DropBody () {
                return this->I_Body;
            }

            std::string E_DropDataByIndex (const ::size_t S_Index) {
                return this->I_Data.at(S_Index);
            }

            std::vector<std::string> E_DropData () {
                return this->I_Data;
            }

            void E_ClearData () {
                this->I_Data.clear();
            }
        };
    } /* Include modules corrdination system */

#endif