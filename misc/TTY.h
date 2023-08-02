#if !defined(L0_TTY_H)

#define L0_TTY_H

#include <vector>
#include <string>
#include <functional>

namespace misc
{
    struct Command
    {
        std::string command;
        std::function<void(std::vector<std::string>)> executor;
    };

    class TTY
    {
    private:
        std::vector<Command> _commands;
    public:
        void CreateCommand()
        {
            
        }
    };
}

#endif