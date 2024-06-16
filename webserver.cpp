#include "Webserver.h"
#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>
using namespace std;

mutex mutexServerOutput;

Webserver::Webserver(int serverID) : serverID(serverID), free(true) {


}

void Webserver::processRequest(const Request& request) {

    lock_guard<mutex> lock(mutexServerOutput);
    cout << "Server " << serverID << " queuing request from " << request.requestIP << " to " << request.responseIP << " - " << request.processingTime << " seconds." << endl;
    queueRequest.push(request);
    free = false;
}

void Webserver::processQueue() {

    while (!queueRequest.empty()) {

        Request request = queueRequest.front();
        queueRequest.pop();

        {
            lock_guard<mutex> lock(mutexServerOutput);
            cout << "Server " << serverID << " processing request " << request.requestIP << " in " << request.processingTime << endl;
        }

        this_thread::sleep_for(chrono::seconds(request.processingTime));

        {
            lock_guard<mutex> lock(mutexServerOutput);
            cout << "Server " << serverID << " processed request " << request.requestIP << endl;
        }
    }
    
    free = true;
}

bool Webserver::isFree() const {

    return free && queueRequest.empty();
}
