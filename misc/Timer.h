#if !defined(L1_TIMER_H)

#define L1_TIMER_H

#include <string>
#include <ctime>

namespace misc {
    std::string E_GetDateAndTime () {
        std::time_t D_TimeStruct = std::time(0);
        std::tm* D_CurrentTime = std::localtime(&D_TimeStruct);

        int D_CurrentDay = D_CurrentTime->tm_mday;
        int D_CurrentMonth = D_CurrentTime->tm_mon + 1;
        int D_CurrentYear = D_CurrentTime->tm_year + 1900;

        std::string D_ReturnableDate;

        if (D_CurrentDay >= 10) {
            D_ReturnableDate += std::to_string(D_CurrentDay);
        }
        else {
            D_ReturnableDate += "0" + std::to_string(D_CurrentDay);
        }

        D_ReturnableDate += ".";

        if (D_CurrentMonth >= 10) {
            D_ReturnableDate += std::to_string(D_CurrentMonth);
        }
        else {
            D_ReturnableDate += "0" + std::to_string(D_CurrentMonth);
        }

        D_ReturnableDate += "." + std::to_string(D_CurrentYear);

        return D_ReturnableDate;
    }
}

#endif