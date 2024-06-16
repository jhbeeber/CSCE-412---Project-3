#include "LoadBalancer.h"
#include <iostream>
#include <algorithm>
using namespace std;

LoadBalancer::LoadBalancer(int numberWebservers) {

    for (int i = 0; i < numberWebservers; ++i) {

        servers.push_back(i + 1);
    }
}

void LoadBalancer::transferRequest(const Request& request) {
    
    auto possibleServer = find_if(
        servers.begin(), 
        servers.end(), 
        [](const Webserver& server) { 
            
            return server.isFree(); 
        }
    );

    if (possibleServer != servers.end()) {

        possibleServer->processRequest(request);
    } 
    else {

        lock_guard<mutex> lock(mutexServerOutput);
        cout << "Added request from " << request.requestIP << " to the queue " << endl;
        queueRequest.push(request);
    }
}

void LoadBalancer::processEveryRequest() {

    for (unsigned int i = 0; i < servers.size(); ++i) {

        if (!(servers[i].isFree())) {

            servers[i].processQueue();
        } 
        else if (!(queueRequest.empty())) {

            Request request = queueRequest.front();
            queueRequest.pop();
            servers[i].processRequest(request);
        }
    }
}
