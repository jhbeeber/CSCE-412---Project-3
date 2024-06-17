#include "Webserver.h"
#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>
using namespace std;

mutex mutexServerOutput;

/**
 * @brief Constructs a Webserver with a given server ID.
 * @param serverID Unique identifier for the webserver.
 */
Webserver::Webserver(int serverID) : serverID(serverID), free(true) {


}

/**
 * @brief Adds a web request to the server's queue and marks the server as busy.
 * @param request The web request to process.
 * @param currentClockCycle The current clock cycle for the web request.
 */
void Webserver::processRequest(const Request& request, int currentClockCycle) {

    {
        lock_guard<mutex> lock(mutexServerOutput);
        cout << "Clock Cycle: " << currentClockCycle << "   " << "Server " << serverID << " queuing request from " << request.requestIP << " to " << request.responseIP << " in " << request.processingTime << " clock cycles" << endl;
        queueRequest.push(request);
        busyUntilClockCycle = request.processingTime + currentClockCycle;
        free = false;
    }
}

/**
 * @brief Processes all web requests in the server's queue sequentially.
 * @param currentClockCycle The current clock cycle for the web request.
 */
void Webserver::processQueue(const Request& request, int currentClockCycle) {

    {
        lock_guard<mutex> lock(mutexServerOutput);
        cout << "Clock Cycle: " << currentClockCycle << "   " << "Server " << serverID << " processing request " << request.requestIP << " in " << request.processingTime << " clock cycles" <<  endl;
    }
}

/**
 * @brief Checks if the server is free to take new web requests.
 * @return True if the server is free and the queue is empty, false otherwise.
 */
bool Webserver::isFree() const {

    return free && queueRequest.empty();
}

/**
 * @brief Gets the size of the web request queue.
 * @return The size of the web request queue.
 */
int Webserver::getSize() const {

    return queueRequest.size();
}
