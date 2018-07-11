#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <stdlib.h>

int main()
{
    std::vector<std::string> files;
    std::string fileToConcatTo;
    std::vector<std::string> sysCommandsToExecute;

    //determine number of lines
    std::ifstream lines(".modules");
    std::stringstream buff;
    std::string temp;
    int counter = 0;
    while (std::getline(lines, temp))
        counter++;
    int total_lines = counter;
    std::cout << "total_lines: " << counter << std::endl;

    std::ifstream myfile(".modules");
    buff << myfile.rdbuf();
    std::string line = buff.str();

    //boundaries
    size_t start = 0;
    size_t end;

    //array
    std::string array[total_lines];

    // array = new std::string[SIZE];

    for (int i = 0; i < total_lines; i++)
    {
        end = line.find("\n", start);//search for '\n' position
        array[i] = line.substr(start, end - start);
        start = end + 1; //updating start
    }
    // std::cout << "here: " << array[8] << "hi" ;

    for (int i = 0; i < total_lines; i++)
    {
        int j = 0;
        if (array[j].compare("Files:") == 0)
        {
            if (array[i].compare("ConcatTo:") == 0)
            {
                i++;
                fileToConcatTo = array[i];
                i++;
                if (array[i].compare("RunThisAfter:") == 0)
                {
                    i++;
                    while (array[i].compare("") != 0)
                    {
                        sysCommandsToExecute.push_back(array[i]);
                        i++;
                    }
                    break;
                }
            }
            else
            {
                if (array[i].compare("Files:") != 0)
                    files.push_back(array[i]);
            }
        }
    }

    std::string convert;
    std::stringstream store;
    for (std::vector<std::string>::const_iterator i = files.begin(); i != files.end(); ++i)
    {
        std::ofstream combined(fileToConcatTo);
        std::ifstream file1(*i);
        store << file1.rdbuf();
        store << "\n";
        convert = store.str();
        combined << convert;
        // file1.close();
    }
    for (std::vector<std::string>::const_iterator i = sysCommandsToExecute.begin(); i != sysCommandsToExecute.end(); ++i)
        system((*i).c_str());
    return (0);
}