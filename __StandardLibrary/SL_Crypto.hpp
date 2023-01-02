#ifndef NatureOS_StandardLibrary_SL_Crypto_hpp
    #define NatureOS_StandardLibrary_SL_Crypto_hpp 1

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
        const __StandardLibrary::Composition S_es11_CryptoAlphabet = {
            /* Letters in lower case */
            { "a", "001" }, { "b", "002" }, { "c", "003" }, { "d", "004" }, { "e", "007" },
            { "f", "008" }, { "h", "009" }, { "g", "010" }, { "j", "011" }, { "i", "012" },
            { "k", "013" }, { "l", "014" }, { "m", "015" }, { "r", "016" }, { "t", "017" },
            { "q", "018" }, { "v", "019" }, { "w", "020" }, { "y", "021" }, { "x", "022" },
            { "z", "023" }, { "o", "024" }, { "p", "025" }, { "u", "026" }, { "s", "027" },
            /* Letters in upper case */
            { "A", "062" }, { "E", "042" }, { "X", "052" }, { "M", "062" }, { "K", "072" },
            { "B", "100" }, { "L", "101" }, { "Z", "064" }, { "O", "065" }, { "W", "102" },
            { "V", "103" }, { "D", "066" }, { "S", "067" }, { "I", "104" }, { "C", "105" },
            { "G", "068" }, { "J", "069" }, { "H", "106" }, { "F", "107" }, { "N", "070" },
            { "Y", "071" }, { "U", "108" }, { "Q", "109" }, { "P", "073" }, { "R", "074" },
            /* Numbers */
            { "1", "200" }, { "2", "201" }, { "3", "202" }, { "4", "203" }, { "5", "204" },
            { "6", "205" }, { "7", "206" }, { "8", "207" }, { "9", "208" }, { "0", "199" },
            /* Special symbols */
            { "$", "300" }, { "%", "301" }, { "^", "302" }, { "&", "303" }, { "@", "304" },
            { "*", "305" }, { "!", "306" }, { "?", "307" }, { "+", "308" }, { "-", "309" },
            { "/", "310" }, { "\\", "311" }, { "(", "312" }, { ")", "313" }, { "{", "314" },
            { "}", "315" }, { "[", "316" }, { "]", "317" }, { "'", "318" }, { "\"", "319" },
            { "`", "320" }, { "_", "321" }, { "#", "322" }, { "|", "323" }, { ":", "324" },
            { ";", "325" }, { "<", "326" }, { ">", "327" }, { " ", "328" }, { ",", "329" },
            { ".", "330" }
        };

        Situate E_Encode (std::string D_Text, const std::string S_Algorythm) {
            Situate D_Situate;
            D_Situate.E_SetHeader("__StandardLibrary::E_Encode()");

            std::string D_EncodedText = "";

            if (S_Algorythm.compare("es11") == 0) {
                for (::size_t D_Iterator = 0; D_Iterator < D_Text.size(); D_Iterator++) {
                    for (::size_t D_IteratorC = 0; D_IteratorC < S_es11_CryptoAlphabet.size(); D_IteratorC++) {
                        if (S_es11_CryptoAlphabet.at(D_IteratorC).at(0).at(0) == D_Text.at(D_Iterator)) {
                            D_EncodedText += S_es11_CryptoAlphabet.at(D_IteratorC).at(1);
                            D_EncodedText += " ";
                        }
                    }
                }

                D_EncodedText.pop_back();
                D_Situate.E_SetBody(__StandardLibrary::E_ColorizeFont("::E_Encode", 197, 57, 235) + " returned success code!");
                D_Situate.E_PushDetail(D_EncodedText);
                D_Situate.E_SetCode(0);
            }
            else {
                D_Situate.E_SetBody(__StandardLibrary::E_ColorizeFont("::E_Encode", 197, 57, 235) + " returned error code!");
                D_Situate.E_PushDetail("Unknown encoding algorythm!");
                D_Situate.E_SetCode(1);
            }

            return D_Situate;
        }

        Situate E_Decode (std::string D_Text, const std::string S_Algorythm) {
            Situate D_Situate;
            D_Situate.E_SetHeader("__StandardLibrary::E_Decode()");

            std::string D_DecodedText = "";

            if (S_Algorythm.compare("es11") == 0) {
                std::vector<std::string> D_ParsedText = E_Split(D_Text, " ");

                for (std::string D_TextPart : D_ParsedText) {
                    for (::size_t D_Iterator = 0; D_Iterator < S_es11_CryptoAlphabet.size(); D_Iterator++) {
                        if (S_es11_CryptoAlphabet.at(D_Iterator).at(1).compare(D_TextPart) == 0) {
                            D_DecodedText += S_es11_CryptoAlphabet.at(D_Iterator).at(0);
                        }
                    }
                }

                D_Situate.E_SetBody(__StandardLibrary::E_ColorizeFont("::E_Decode", 197, 57, 235) + " returned success code!");
                D_Situate.E_PushDetail(D_DecodedText);
                D_Situate.E_SetCode(0);
            }
            else {
                D_Situate.E_SetBody(__StandardLibrary::E_ColorizeFont("::E_Decode", 197, 57, 235) + " returned error code!");
                D_Situate.E_PushDetail("Unknown encoding algorythm!");
                D_Situate.E_SetCode(1);
            }

            return D_Situate;
        }
    } /* Include function to encode and decode */

#endif