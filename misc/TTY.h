#if !defined(L0_TTY_H)

#define L0_TTY_H

#include <vector>
#include <string>
#include <functional>
#include "./Utilities.h"
#include "./Screen.h"

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
        void CreateCommand(std::string commnad, std::function<void(std::vector<std::string>)> function)
        {
            int checker = this->CheckIfExists(commnad);

            if (checker != -1)
            {
                this->_commands.at(checker).executor = function;
            }
            else
            {
                Command newCommand = { commnad, function };

                this->_commands.push_back(newCommand);
            }
        }

        void StartInteractive()
        {
            while(true)
            {
                std::string UserInput;

                misc::Input(UserInput);

                std::vector<std::string> parsedCommand = misc::Split(UserInput, " ");
                int checker = this->CheckIfExists(parsedCommand.at(0));

                if (checker == -1)
                {
                    misc::Output("Command not found\n");
                }
                else
                {
                    Command command = this->_commands.at(checker);
                    
                    parsedCommand = misc::Delete<std::string>(parsedCommand, 0);

                    command.executor(parsedCommand);
                }
            }
        }

        int CheckIfExists(std::string command)
        {
            for (int i = 0; i < this->_commands.size(); i++)
            {
                Command existsCommand = this->_commands.at(i);

                if (existsCommand.command.compare(command) == 0)
                {
                    return i;
                }
            }

            return -1;
        }
    };
}

#endif