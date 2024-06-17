#ifndef LOADBALANCER_H
#define LOADBALANCER_H

#include "Webserver.h"
#include <vector>
#include <queue>
using namespace std;

/**
 * @class LoadBalancer
 * @brief Manages distribution of requests among multiple web servers.
 *
 * The LoadBalancer class takes in requests and distributes them
 * across a number of web servers to balance the load and ensure the
 * processing of requests.
 */
class LoadBalancer {

    public:
        /**
         * @brief Constructor that initializes a LoadBalancer with a specified number of web servers.
         * @param numberWebservers Number of web servers to manage.
         */
        LoadBalancer(int numberWebservers);

        /**
         * @brief Adds a web request to the load balancer's queue.
         * @param request The web request to be added.
         * @param currentClockCycle The current clock cycle for the web request.
         */
        void transferRequest(const Request& request, int currentClockCycle);

        /**
         * @brief Processes every web request in the queue across all web servers.
         * @param currentClockCycle The current clock cycle for the web request.
         */
        void processEveryRequest(int currentClockCycle);

    private:
        vector<Webserver> servers; ///< Vector of Webserver objects representing the web servers.
        queue<Request> queueRequest; ///< Queue of web requests awaiting processing.
};

#endif
