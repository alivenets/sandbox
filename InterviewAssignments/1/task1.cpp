// you can use includes, for example:
#include <algorithm>
#include <sstream>
#include <vector>
#include <iostream>
#include <string>
#include <tuple>

using namespace std;

// you can write to stdout for debugging purposes, e.g.
// cout << "this is a debug message" << endl;
vector<string> tokenize(const string &s, char delim)
{
    std::vector<std::string> tokens;
    std::istringstream istr{s};
    std::string tmp;

    do {
        std::getline(istr, tmp, delim);
        tokens.push_back(tmp);
    } while (!istr.eof());
    
    return tokens;
}

int solution(string &S, string &T, string &U) {
    // write your code in C++14 (g++ 6.2.0)
    int installedVersion = 0;

    istringstream lineReader;

    // Find installed version on system
    lineReader.str(T);
    do {
        string installationRecord;
        getline(lineReader, installationRecord, '\n');
        vector<string> tokens = tokenize(installationRecord, ',');
        if (U == tokens[0]) {
            installedVersion = stoi(tokens[1]);
            break;
        }
    } while (!lineReader.eof());

    int downloadSize = -1;
    // Find region in catalog and calculate delta to be downloaded
    lineReader.str(S);
    lineReader.seekg(0);

    do {
        string catalogRecord;
        getline(lineReader, catalogRecord, '\n');
        vector<string> tokens = tokenize(catalogRecord, ',');
        if (U == tokens[0]) {
            int catalogVersion = stoi(tokens[1]);
            if (catalogVersion > installedVersion) {
                if (downloadSize == -1)
                    downloadSize = 0;
                downloadSize += stoi(tokens[2]);
            }
        }
    } while (!lineReader.eof());

    return downloadSize;
}

int main(void)
{
    vector<tuple<string, string, string, int>> testCases = {
        {
            "Netherlands,1,25000\nNetherlands,2,3000\nNetherlands,3,1000",
            "Netherlands,1",
            "Netherlands",
            4000,
        },
        {
            "Netherlands,1,25000\nNetherlands,2,3000\nNetherlands,3,1000",
            "Netherlands,2\nBelgium,4",
            "United Kingdom",
            -1,
        },
    };

    for (auto &test: testCases) {
        int ret = solution(std::get<0>(test), std::get<1>(test), std::get<2>(test));
        if (ret == std::get<3>(test)) {
            std::cout << "PASS" << std::endl;
        }
        else {
            std::cout << "FAIL: " << "expected " << std::get<3>(test) << ", got " << ret << std::endl;
        }
    }
    return 0;
}
