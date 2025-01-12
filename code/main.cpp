#include <algorithm>
#include <cctype>
#include <chrono>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <thread>

void printhelp()
{
    std::cout << "Help:\nThe '-s <seconds>' argument is REQUIRED! You will reconnect after that time.\nIf your connection is broken, run lagswitch with the -f arg.\n";
    exit(0);
}

int main(int argc, char* argv[])
{
    if (argc == 1)
    {
        printhelp();
    }

    if (argc > 3)
    {
        std::cerr << "Maximum two arguments allowed!\n";
        exit(1);
    }

    if (strcmp(argv[1], "-h") == 0)
    {
        printhelp();
    }

    if (strcmp(argv[1], "-f") == 0)
    {
        std::cout << "Attempting to fix network connection...\n";
        system("nmcli networking on");
        std::cout << "Should be fixed!\n";
        exit(0);
    }

    if (strcmp(argv[1], "-s") == 0)
    {
        int seconds = atoi(argv[2]);

        if (seconds == 0)
        {
            std::cerr << "Error parsing seconds argument...\nIt must be more than 0 seconds!\n";
            exit(1);
        }

        if (seconds > 20)
        {
            std::cout << "You will have to wait over 20 seconds to reconnect...\nAre you sure? (y or n): ";

            std::string verify;
            std::cin >> verify;

            if (verify.empty() == true || verify == "")
            {
                std::cerr << "You didn't enter anything!\n";
                exit(1);
            }

            // make the string lower case
            std::transform(verify.begin(), verify.end(), verify.begin(), ::tolower);

            if (verify == "y")
            {
                std::cout << "OK, continuing...\n";
            }
            else
            {
                std::cout << "OK, stopped.\n";
                exit(0);
            }
        }

        system("nmcli networking off");
        std::cout << "Disconnected\n";
        std::this_thread::sleep_for(std::chrono::seconds(seconds));
        std::cout << "Connecting...\n";
        system("nmcli networking on");
        std::cout << "Connected!\n";
    }

    return 0;
}
