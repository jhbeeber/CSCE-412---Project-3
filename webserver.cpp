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
 */
void Webserver::processRequest(const Request& request) {

    lock_guard<mutex> lock(mutexServerOutput);
    cout << "Server " << serverID << " queuing request from " << request.requestIP << " to " << request.responseIP << " - " << request.processingTime << " seconds." << endl;
    queueRequest.push(request);
    free = false;
}

/**
 * @brief Processes all web requests in the server's queue sequentially.
 */
void Webserver::processQueue() {

    while (!queueRequest.empty()) {

        Request request = queueRequest.front();
        queueRequest.pop();

        {
            lock_guard<mutex> lock(mutexServerOutput);
            cout << "Server " << serverID << " processing request " << request.requestIP << " in " << request.processingTime << " seconds" <<  endl;
        }

        this_thread::sleep_for(chrono::seconds(request.processingTime));

        {
            lock_guard<mutex> lock(mutexServerOutput);
            cout << "Server " << serverID << " processed request " << request.requestIP << endl;
        }
    }
    
    free = true;
}

/**
 * @brief Checks if the server is free to take new web requests.
 * @return True if the server is free and the queue is empty, false otherwise.
 */
bool Webserver::isFree() const {

    return free && queueRequest.empty();
}
