#ifndef NatureOS_VirtualMemory_VM_Data_hpp
    #define NatureOS_VirtualMemory_VM_Data_hpp 1

    #ifndef _VECTOR_
        #include <vector>
    #endif

    #ifndef _STRING_
        #include <string>
    #endif

    namespace __VirtualMemory {
        struct Addresser {
            ::size_t D_ChainIndex;
            int D_InChainIndex;
            std::string D_Value;
        };

        struct Chain {
            ::size_t D_Index;
            std::vector<Addresser> D_Chain;
        };

        struct Label {
            /**
             *  Each Label has a D_Name parameter, which, as the name implies, contains its name.
             * Thanks to the name, the Label is available for interaction with the user level
             */
            std::string D_Name;
            // ==============================================================================================
            /**
             *  D_Creator points to the creator of this Label, for debugging purposes and to provide
             * information in full view.
             */
            std::string D_Creator;
            // ==============================================================================================
            /**
             *  D_CreatingDate indicates the date and time when this Label was created. It is not
             * recommended to change after the first initialization, as there may be consequences,
             * so you act at your own peril and risk and are fully (hopefully) aware of the responsibility!
             * Use this field for debugging and a complete overview.
             */
            std::string D_CreatingDate;
            // ==============================================================================================
            /**
             *  D_LabelNumber parameter that will delay the section number (you must set it yourself).
             * This parameter is not recommended to be edited after the initial initialization, as
             * there may be consequences (you are responsible for them). Use this parameter for
             * debugging and more convenient access to Lable while working with it!
             */
            ::size_t D_LabelNumber;
            // ==============================================================================================
            /**
             *  D_PasswordStatus This option allows you to set a password for the Label (use for security
             * purposes), also if you are writing a program that gives information about the Label, you
             * can use this option for a complete overview.
             */
            bool D_PasswordStatus;
            // ==============================================================================================
            /**
             *  D_Password If you set D_PasswordStatus to true, then you can write the password for the
             * Label in this field, but try to notify the user about changing the password in the Label
             * so that there are no problems.
             */
            std::string D_Password;
            // ==============================================================================================
            /**
             *  D_CodingStatus is a parameter that is responsible for whether the Label has encryption.
             * Use this setting for a complete overview, or turn it on to protect your data.
             */
            bool D_CodingStatus;
            // ==============================================================================================
            /**
             *  D_CodingAlgorythm this parameter stores the name of the algorithm by which this Label
             * will be encrypted. Users cannot implement their own algorithms, use only those supplied
             * by the Authors of the operating system.
             */
            std::string D_CodingAlgorythm;
            // ==============================================================================================
            /**
             *  D_Modifiable this parameter is responsible for the ability to interact with the Label,
             * if you do not want any data to appear / delete / overwrite, then write false in this
             * field, after filling the Lable with the information you need, also at any time your
             * software can open this Label and write the data and then close it again, which will allow
             * quite flexible and safe data storage!
             */
            bool D_Modifiable;
            // ==============================================================================================
            /**
             *   D_RootLaws is a parameter that enables/disables the use of system privileges, you cannot
             * change this value, it will always be false. But you can use this when debugging or full
             * review.
             */
            bool D_RootLaws; // always false!
            // ==============================================================================================
            /**
             *  D_Markup is the contents of your Lable, you can write various information there, more
             * details in the operating system using the "wiki --memory --fordev" command
             */
            std::vector<Chain> D_Markup;
        };

        namespace __Chain {
            class Core {
            private:
                int D_Index = -1;
                Chain D_LocalChain;
            public:
                void E_Initialize (const int S_Index) {
                    if (D_Index == -1 && S_Index >= 0) {
                        this->D_Index = S_Index;
                        this->D_LocalChain.D_Index = this->D_Index;
                    }
                }

                void E_Push (std::string D_Content) {
                    if (this->D_Index != -1) {
                        Addresser D_Adresser;

                        D_Adresser.D_ChainIndex = this->D_Index;
                        D_Adresser.D_InChainIndex = this->D_LocalChain.D_Chain.size();
                        D_Adresser.D_Value = D_Content;

                        this->D_LocalChain.D_Chain.push_back(D_Adresser);
                    }
                }

                Addresser E_GetAdress (const int S_AdresserIndex) {
                    for (Addresser D_CurrentAdresser : this->D_LocalChain.D_Chain) {
                        if (D_CurrentAdresser.D_InChainIndex == S_AdresserIndex) {
                            return D_CurrentAdresser;
                        }
                    }

                    Addresser D_Error;
                    D_Error.D_InChainIndex = -2;
                    return D_Error;
                }

                Chain E_GetChain () {
                    return this->D_LocalChain;
                }
            };
        }
    }

#endif