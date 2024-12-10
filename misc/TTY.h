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
        std::string description;
        std::function<void(std::vector<std::string>)> executor;
    };

    class TTY
    {
    private:
        std::vector<Command> _commands;
        std::string _screenPrefix = "";
        bool _break = false;
    public:
        void CreateCommand(std::string command, std::string description, std::function<void(std::vector<std::string>)> function)
        {
            int checker = this->CheckIfExists(command);

            if (checker != -1)
            {
                this->_commands.at(checker).executor = function;
                this->_commands.at(checker).description = description;
            }
            else
            {
                Command newCommand = { command, description, function };

                this->_commands.push_back(newCommand);
            }
        }

        void StartInteractive()
        {
            while(true)
            {
                if (this->_break)
                {
                    break;
                }
                
                misc::Output(this->_screenPrefix);

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

        void SetScreenPrefix(std::string newScreenPrefix)
        {
            this->_screenPrefix = newScreenPrefix;
        }

        void Exit()
        {
            this->_break = true;
        }

        std::vector<Command> DropCommands() {
            return this->_commands;
        }
    };
}

#endif