#include <iostream>
#include <sstream>
#include <string>
#include <filesystem>

using namespace std;
namespace filesystem = std::filesystem;

string open_folder(const string &arg)
{
    filesystem::path target = arg;

    string open_folder = "MINI SHELL ~" + arg + "!";

    if (!filesystem::exists(target))
    {
        cout << "\n";
        cout << "No such a direcotory!" << "\n";
    }

    if (!filesystem::is_directory(target))
    {
        cout << "Not a Directory: " << arg << "\n\n";
        return "MINI SHELL ~!";
    }

    filesystem::current_path(target);

    string current_folder = filesystem::current_path().string();

    return "MINI SHELL ~" + current_folder + "!";
}

int main()
{
    string commands;
    string start_shell = "MINI SHELL ~! ";

    while (true)
    {

        cout << start_shell;

        if (getline(cin, commands))
        {
            istringstream iss(commands);
            string commands, arg;

            if (!(iss >> commands)) {
                continue;
            }

            if (commands == "cd")
            {
                if (iss >> arg)
                {
                    start_shell = open_folder(arg);
                }
                else
                {
                    cout << "cd requires path!\n";
                }
            }
            else if (commands == "set-home")
                {
                    start_shell = "MINI SHELL ~! ";
                }
            else {
                cout << "No command found!: " << commands << "\n";
            }
        }
    }

    return 0;
}