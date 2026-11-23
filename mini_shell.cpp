#include <iostream>
#include <sstream>
#include <string>
#include <filesystem>
#include <cstdlib>
#include <fstream>
#include <termios.h>
#include <unistd.h>
#include <vector>
#include <csignal>

void DisableExitHotkey()
{
    signal(SIGINT, SIG_IGN);

#ifndef _WIN32
    signal(SIGTSTP, SIG_IGN);
#endif
}

using namespace std;
namespace filesystem = std::filesystem;

void applyChangeCommandIndex(bool is_up, const vector<string> &history, int &hist_idx, string &line, string &draft)
{
    if (history.empty())
    {
        return;
    }

    const int end_idx = static_cast<int>(history.size());

    if (is_up && hist_idx > 0)
    {
        if (end_idx == hist_idx)
        {
            draft = line;
        }

        --hist_idx;
        line = history[static_cast<size_t>(hist_idx)];
    }
    else if (!is_up && hist_idx < end_idx)
    {
        ++hist_idx;
        line = (hist_idx == end_idx) ? draft : history[static_cast<size_t>(hist_idx)];
    }
}

string make_prompt(const filesystem::path &current, const filesystem::path &home)
{

    string home_str = home.string();
    string curr_str = current.string();

    if (home_str == curr_str)

        return string("\033[32m") + "MINI SHELL ~!" + "\033[0m";

    if (curr_str.starts_with(home_str + "/"))

        return string("\033[32m") + "MINI SHELL ~" + curr_str.substr(home_str.size()) + "! \033[0m";

    return "\033[32m MINISHELL" + curr_str + "! \033[0m";
}

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

void create_file(const string &filename)
{
    ofstream(filename, ios::app);
}

void clearTerm()
{
    system("clear");
}

void print_pwd()
{
    cout << filesystem::current_path().string() << "\n";
}

void cmd_ls(const filesystem::path &target = filesystem::current_path())
{
    error_code ec;
    filesystem::directory_iterator it(target, ec);

    if (ec)
    {
        cout << "\033[31mls: " << ec.message() << "\033[0m\n";
        return;
    }

    for (const auto &entry : it)
    {
        string name = entry.path().filename().string();

        if (entry.is_directory(ec))
        {
            cout << "\033[34m" << name << "/\033[0m  ";
        }
        else
        {
            cout << "\033[35m" << name << "  \033[0m";
        }
    }
    cout << "\n";
}

void RemoveItems(const string &nameItem)
{
    filesystem::remove(nameItem);
}

void Create_Directory(const string &nameDirectory)
{
    filesystem::create_directory(nameDirectory);
}

string CatCommand(const string &filename)
{

    ifstream file(filename);

    string line;
    while (getline(file, line))

        cout << line << "\n";

    return line;
}

int main()
{
    DisableExitHotkey();

    string lines_char(30, '=');

    const filesystem::path home = getHome();
    filesystem::current_path(home);

    string commands;
    string start_shell = make_prompt(filesystem::current_path(), home);

    while (true)
    {

        cout << start_shell;

        if (getline(cin, commands))
        {
            istringstream iss(commands);
            string commands, arg;

            if (!(iss >> commands))

                continue;

            // Open Folder Command
            if (commands == "cd")
            {
                if (iss >> arg)
                    start_shell = open_folder(arg, home);
                else
                    cout << string("\033[31m") + "cd requires path!\n" + "\033[0m";
            }
            // Open File Command
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

                    cout << string("\033[31m") + "command open: requires filename!\n" + "\033[0m";
            }
            // CatCommand
            else if (commands == "cat")
            {
                if (iss >> arg)

                    CatCommand(arg);
            }
            else if (commands == "set-home")
            {
                filesystem::current_path(home);
                start_shell = string("\033[32m") + "MINI SHELL ~" + home.string() + "! \033[32m";
            }

            // Listdir Command
            else if (commands == "ls")

                cmd_ls();
            // In what folder are you in Command
            else if (commands == "pwd")

                print_pwd();

            // Clear Terminal Command
            else if (commands == "clear")

                clearTerm();

            // Create File
            else if (commands == "touch")
            {
                if (iss >> arg)
                    create_file(arg);
            }

            // Make Directory
            else if (commands == "mkdir")
            {
                if (iss >> arg)
                    Create_Directory(arg);
            }

            // Remove Item
            else if (commands == "rm")
            {
                if (iss >> arg)
                {
                    if (filesystem::exists(arg))
                        RemoveItems(arg);
                    }
                    else
                        cout << "No such Items with name" << arg << " found!\n";
            }
            // Exit The SHELL command

            else if (commands == "exit")
            {
                cout << lines_char << "\n";
                cerr << "You has been exit Succesfully!";
                cout << "\n"
                     << lines_char << "\n";
                return 1;
            }
            // No Command found
            else

                cout << string("\033[31m") + "No command found!: " << commands << "\n \033[0m";
        }
    }

    // Exit Code
    return 0;
}