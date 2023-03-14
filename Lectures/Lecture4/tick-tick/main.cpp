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
    string period_option = "--period";
    string sett_option = "--sett";
    
    // Settings values
    int period = 1000;
    string sett_file = "";

    // Values read from filw
    double dt = 0.1; // time step
    double xmax  = 1.0; // max
    double xmin  = -1.0;// min
    int    niter = 10; // maximum number of generated values

    // parsing command line args
    for(int i=0; i<argc; ++i)
    {
        if(period_option.compare(argv[i]) == 0) // period
            period = stoi(argv[i+1]); // convert to int
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
                        if(key.compare("DT") == 0) dt = stod(value); // string to double, whitespaces removed
                        else if(key.compare("XMAX") == 0) xmax = stod(value);
                        else if(key.compare("XMIN") == 0) xmin = stod(value);
                        else if(key.compare("N") == 0) niter = stoi(value);
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
    cout << "Period:" << period << '\n';
    cout << "Dt:\t"   << dt << '\n';
    cout << "Xmax:\t" << xmax << '\n';
    cout << "Xmin:\t" << xmin << '\n';
    cout << "N:\t"    << niter << '\n';

    // File to store to
    ofstream myfile; // open output stream
    myfile.open ("data.dat"); // file to store results
    myfile << "# Recording precious random data\n"
           << "# t, value" << '\n'
           << "# Settings: " << period << " " << dt << " " << xmax << " " << xmin << " " << niter << '\n';
    myfile.flush();

    // The "computational" process!
    uniform_real_distribution<double> unif(xmin, xmax);
    default_random_engine re;

    for(int i = 0; i < niter; ++i)
    {
        this_thread::sleep_for(chrono::milliseconds(period)); // a nice do nothing part
        double random_double = unif(re);
        myfile << i*dt << ",\t " << random_double << '\n';
        myfile.flush();
    }

    // Tidy up
    myfile.close();
    return 0;
}