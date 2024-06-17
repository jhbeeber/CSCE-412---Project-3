#include "LoadBalancer.h"
#include "Request.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <string>
#include <cstdlib>
#include <ctime>
#include <random>
#include <atomic>
using namespace std;

mutex outputMutex; ///< Mutex to synchronize output.
atomic<int> currentClockCycle(0); ///< Initializes integer to store the current clock cycle.
mutex clockMutex; ///< Mutex to synchronize the clock cycle.

/**
 * @brief Function that gets the current clock cycle and protects it with a mutex.
 * @returns The current clock cycle.
 */
int getCurrentClockCycle() {

    lock_guard<mutex> lock(clockMutex);
    return currentClockCycle.load();
}

/**
 * @brief Generates random web requests and sends them to the load balancer.
 * @param loadbalancer The LoadBalancer object that will process the requests.
 */
void generateRandomRequests(LoadBalancer& loadbalancer) {

    random_device randomNumberGenerator;
    mt19937 gen(randomNumberGenerator());
    uniform_int_distribution<> dis(5, 100);
    uniform_int_distribution<> ip(0, 255);

    while (true) {

        int currentCycle = getCurrentClockCycle();
        this_thread::sleep_for(chrono::nanoseconds(dis(gen)));
        int requestIP = ip(gen);
        int responseIP = ip(gen);
        Request newRequest("192.168.1." + to_string(requestIP), "192.168.2." + to_string(responseIP), dis(gen));
        cout << "New request from 192.168.1." << requestIP << " to 192.168.2." << responseIP << endl;
        loadbalancer.transferRequest(newRequest, currentCycle);
    }
}

/**
 * @brief Main function to initialize and control the Load Balancer.
 * @returns Execution status.
 */
int main() {

    int numberWebservers;
    cout << "Enter the number of webservers: ";
    cin >> numberWebservers;

    LoadBalancer loadBalancer(numberWebservers);
    random_device randomNumberGenerator;
    mt19937 gen(randomNumberGenerator());
    uniform_int_distribution<> dis(5, 100);

    for (int i = 0; i < 10; ++i) {

        int randomProcessingTime = dis(gen);
        Request request("192.168.1." + to_string(i), "192.168.2." + to_string(i), randomProcessingTime);
        loadBalancer.transferRequest(request, currentClockCycle);
    }

    thread requestThread(generateRandomRequests, ref(loadBalancer));
    requestThread.detach();

    int clockCycles = 10000;
    for (int j = 10; j <= clockCycles; ++j) {

        currentClockCycle = j;
        loadBalancer.processEveryRequest(currentClockCycle);
        this_thread::sleep_for(chrono::nanoseconds(100));
        
        if (currentClockCycle % 10 == 0) {

            cout << "Clock Cycle: " << currentClockCycle + 1 << endl; 
        }
    }

    return 0;
}
