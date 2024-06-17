#include "LoadBalancer.h"
#include <iostream>
#include <algorithm>
using namespace std;

/**
 * @brief Constructs a LoadBalancer with a specified number of web servers.
 * @param numberWebservers Number of web servers to manage.
 *
 * Initializes the load balancer and creates the specified number of web servers.
 */
LoadBalancer::LoadBalancer(int numberWebservers) {

    for (int i = 0; i < numberWebservers; ++i) {

        servers.push_back(i + 1);
    }
}

/**
 * @brief Transfers a web request to an available web server or adds it to the queue if none are available.
 * @param request The web request to be transferred.
 * @param currentClockCycle The current clock cycle for the web request.
 *
 * This method attempts to find a free web server to process the web request immediately.
 * If no servers are available, the web request is added to a queue to be processed later.
 */
void LoadBalancer::transferRequest(const Request& request, int currentClockCycle) {
    
    auto possibleServer = find_if(
        servers.begin(), 
        servers.end(), 
        [](const Webserver& server) { 
            
            return server.isFree(); 
        }
    );

    if (possibleServer != servers.end()) {

        possibleServer->processRequest(request, currentClockCycle);
    } 
    else {

        {
            lock_guard<mutex> lock(mutexServerOutput);
            cout << "Clock Cycle: " << currentClockCycle << "   " << "Added request from " << request.requestIP << " to the queue" << endl;
            queueRequest.push(request);
        }
    }
}

/**
 * @brief Processes web requests from the queue across all web servers.
 * @param currentClockCycle The current clock cycle for the web request.
 *
 * This method processes each server's queue and if a server is free and the main queue is not empty,
 * it assigns a new web request from the queue to the server.
 */
void LoadBalancer::processEveryRequest(int currentClockCycle) {

    for (Webserver& server : servers) {
        
        if (currentClockCycle >= server.busyUntilClockCycle && !server.queueRequest.empty()) {

            Request request = server.queueRequest.front(); 
            server.queueRequest.pop();
            cout << "Clock Cycle: " << currentClockCycle << "   " << "Server " << server.serverID << " processed request " << request.requestIP << endl;

            if (server.queueRequest.empty()) {

                server.free = true;
            }
            else {
                
                request = server.queueRequest.front(); 
                server.busyUntilClockCycle = currentClockCycle + request.processingTime; 
                server.processQueue(request, currentClockCycle);
            }
        }
    }
}
