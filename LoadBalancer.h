#ifndef LOADBALANCER_H
#define LOADBALANCER_H

#include "Webserver.h"
#include <vector>
#include <queue>
using namespace std;

class LoadBalancer {

    public:
        LoadBalancer(int numberWebservers);
        void transferRequest(const Request& request);
        void processEveryRequest();

    private:
        vector<Webserver> servers;
        queue<Request> queueRequest;
};

#endif
