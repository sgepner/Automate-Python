#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include <filesystem>
#include <algorithm>
#include <random>

using namespace std;

int main(int argc, char *argv[])
{
    // Settings strings
    string sett_option = "--sett";
    
    // Settings values
    string sett_file = "";

    // Values read from file
    double xval  = 1.0;
    double yval  =-1.0;

    // parsing command line args
    for(int i=0; i<argc; ++i)
    {
        if(sett_option.compare(argv[i]) == 0) // setting file
        {
            sett_file = argv[i+1];
            if(filesystem::exists(sett_file)) // file exists, read settings
            {
                ifstream myfile(sett_file); // open file as an input stream
                std::string line;
                while( getline(myfile, line) ) // go through all lines
                {
                    if(line[0] == '#') continue; // skip comments
                    if(line.find_first_of('=') != string::npos) // consider only if there is a '='
                    {
                        istringstream is_line(line); // to use with getline
                        std::string key, value;
                        getline(is_line, key, '='); // first, get the key
                        getline(is_line, value, '='); // get the value
                        key.erase (remove (key.begin(), key.end(), ' '), key.end()); // get rid of whitespaces
                        if(key.compare("X") == 0) xval = stod(value); // string to double, whitespaces removed
                        else if(key.compare("Y") == 0) yval = stod(value);
                        else { cout << key << " " << " with vaue " << value << " is not regcognized" << '\n'; }
                    }
                }
                myfile.close();
            }
            else cout << "Setting file " << sett_file << "does not exist, usin defaults" << '\n';
        }
    }

    // sum up the settings
    cout << "===== Starting process =====" << '\n';
    cout << "X:\t" << xval << '\n';
    cout << "Y:\t" << xval << '\n';

    // File to store to
    ofstream myfile; // open output stream
    myfile.open ("data.dat"); // file to store results
    myfile << "# Recording result\n"
           << "# Settings: " << xval << " " << yval << '\n';
    myfile.flush();

    double zval = (xval-45.68)*(xval+85.45) + (yval-58.84)*(yval-25.55);
    myfile << xval << ",\t " << yval << " " << zval << '\n';
    myfile.flush();
    cout << "Z:\t" << zval << '\n';

    // Tidy up
    myfile.close();
    return 0;
}
