#ifndef REQUEST_H
#define REQUEST_H

#include <string>
using namespace std;

struct Request {
    string requestIP;  
    string responseIP;
    int processingTime; 

    Request (const string& in, const string& out, int processingTime) : requestIP(in), responseIP(out), processingTime(processingTime) {

    }
};

#endif
