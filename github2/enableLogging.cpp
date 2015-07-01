/*
 * Creator: Matthew Rossi
 * Date 6/30/2015
 * Purpose: Random source code that disables logging
 * in your code. This is done through the cmd line
 */

#include <string>
#include <cstdio>
#include <cerrno>
#include <iostream>
#include <fstream>
#include <vector>
#include "logger.h"

using namespace std;

void ReplaceFirst(string & phrase, string sought, string replacement)
{
    size_t  pos = phrase.find(sought, 0);
    if (pos != string::npos)
    {
        // pos is a valid index where it was found
        int num_chars = sought.length();
        // how many characters is the string we are searching for
        phrase.replace(pos, num_chars, replacement);
        pos = phrase.find(sought, pos + num_chars);
        cout << "pos=" << pos << endl;
    }

}
int main(int argc, char* argv[])
{

    string theString = "";
    ifstream ifs;
    if (argc < 2 || argc >4)
    {
        cout << "usage:\n enable logging source_filename [destination_filename]" << endl
            << "\n\nUNcomments out the logging functions in the cpp file passed in by filename," << endl
            << "if only one filename is given it will also be used as the destination" << endl;

        return 2;
    }
    ifs.open(argv[1], ifstream::in);

    vector<string> vecString;
    while (!ifs.eof())
    {
        getline(ifs, theString);
        ReplaceFirst(theString, "//Logger::OpenLogFile", "Logger::OpenLogFile");
        ReplaceFirst(theString, "//Logger::CloseLogFile", "Logger::CloseLogFile");
        ReplaceFirst(theString, "//Logger::Log", "Logger::Log");
        ReplaceFirst(theString, "//LogStart", "LogStart");
        ReplaceFirst(theString, "//LogEnd", "LogEnd");
        ReplaceFirst(theString, "//#include \"logger.h\"", "#include \"logger.h\"");
        //add the cleaned up string into a vector
        vecString.push_back(theString);
    }
    //close the ifstream
    ifs.close();
    ofstream ofs;
    //
    //                                                                                                                                   //open the destination file as a ofstream
    if (argc == 2)
        ofs.open(argv[1], ofstream::out);
    else
        ofs.open(argv[2], ofstream::out);
    for (unsigned int i = 0; i < vecString.size(); i++)
    {
        ofs << vecString[i] << endl;
    }
    ofs.close();

    return 0;
}
