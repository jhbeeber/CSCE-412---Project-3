#ifndef WEBSERVER_H
#define WEBSERVER_H

#include "Request.h"
#include <queue>
#include <mutex>
using namespace std;

extern mutex mutexServerOutput;

/**
 * @class Webserver
 * @brief Manages the processing of web requests.
 *
 * This class represents a web server that can process requests sequentially. It maintains a queue of web requests
 * and processes them one by one. The server can be checked for its availability using the isFree method.
 */
class Webserver {
    
    public:
        /**
         * @brief Constructs a Webserver with a given server ID.
         * @param serverID Unique identifier for the webserver.
         */
        Webserver(int serverID);

        /**
         * @brief Takes a web request and adds it to the processing queue.
         * @param request The web request to be processed.
         * @param currentClockCycle The current clock cycle for the web request.
         */
        void processRequest(const Request& request, int currentClockCycle);

        /**
         * @brief Processes all web requests in the queue until it is empty.
         * @param request The web request to be processed.
         * @param currentClockCycle The current clock cycle for the web request.
         */
        void processQueue(const Request& request, int currentClockCycle);

        /**
         * @brief Checks if the webserver is free to take more requests.
         * @return True if the server is free and the queue is empty, false otherwise.
         */
        bool isFree() const;

        /**
         * @brief Gets the size of the web request queue.
         * @return The size of the web request queue.
         */
        int getSize() const;

        int busyUntilClockCycle = 0; ///< Integer to track time until processed.
        queue<Request> queueRequest; ///< Queue of web requests to be processed.
        int serverID; ///< Unique identifier for the webserver.
        bool free; ///< Indicates whether the webserver is free to take more web requests.
}; 

#endif
