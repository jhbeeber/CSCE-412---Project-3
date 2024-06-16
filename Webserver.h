#ifndef WEBSERVER_H
#define WEBSERVER_H

#include "Request.h"
#include <queue>
#include <mutex>
using namespace std;

extern mutex mutexServerOutput;

class Webserver {
    
    public:
        Webserver(int serverID);
        void processRequest(const Request& request);
        void processQueue();
        bool isFree() const;

    private:
        int serverID;
        bool free;
        queue<Request> queueRequest;
};

#endif
