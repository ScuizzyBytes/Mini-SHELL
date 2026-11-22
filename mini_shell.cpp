#include <iostream>
#include <sstream>
#include <string>
#include <filesystem>
#include <cstdlib>
#include <fstream>

using namespace std;
namespace filesystem = std::filesystem;

string open_folder(const string &arg, const filesystem::path &home)
{
    filesystem::path target = arg;

    if (!filesystem::exists(target))
    {
        cout << "\n";
        cout << string("\033[31m") + "No such a direcotory!" << "\n \033[31m";
        return string("\033[32m") + "MINI SHELL ~" + filesystem::current_path().string() + "!";
    }

    if (!filesystem::is_directory(target))
    {
        cout << string("\033[31m") + "Not a Directory: " << arg << "\n \033[0m";
        return string("\033[32m") + "MINI SHELL ~!" + "\033[0m";
    }

    filesystem::current_path(target);

    string current_folder = filesystem::current_path().string();

    return string("\033[32m") + "MINI SHELL ~" + current_folder + "! \033[0m";
}

filesystem::path getHome()
{
    const char *HomeEnv = getenv("HOME");

    if (HomeEnv != nullptr)
    {
        filesystem::path homepath(HomeEnv);
        if (filesystem::exists(homepath) && filesystem::is_directory(homepath))
        {
            return homepath;
        }
    }

    return filesystem::current_path();
}

void open_file(string &filename, const string &text)
{
    ofstream file(filename, ios::app);
    file << text << "\n";
}

void clearTerm()
{
    system("clear");
}

int main()
{

    const filesystem::path home = getHome();
    filesystem::current_path(home);

    string commands;
    string start_shell = string("\033[32m") + "MINI SHELL ~" + home.string() + "!\033[0m";

    while (true)
    {

        cout << start_shell;

        if (getline(cin, commands))
        {
            istringstream iss(commands);
            string commands, arg;

            if (!(iss >> commands))
            {
                continue;
            }

            if (commands == "cd")
            {
                if (iss >> arg)
                    start_shell = open_folder(arg, home);
                else
                    cout << string("\033[31m") + "cd requires path!\n" + "\033[0m";
            }
            else if (commands == "open")
            {
                if (iss >> arg)
                {
                    string text_file;
                    cout << string("\033[35m") + "write what ever you want: " + "\033[0m";

                    getline(cin, text_file);
                    open_file(arg, text_file);
                }
                else
                {
                    cout << string("\033[31m") + "command open: requires filename!\n" + "\033[0m";
                }
            }
            else if (commands == "set-home")
            {
                filesystem::current_path(home);
                start_shell = string("\033[32m") + "MINI SHELL ~" + home.string() + "!", "\033[32m";
            }
            else if (commands == "clear")
            {
                clearTerm();
            }
            else
            {
                cout << string("\033[31m") + "No command found!: " << commands << "\n \033[0m";
            }
        }
    }

    return 0;
}