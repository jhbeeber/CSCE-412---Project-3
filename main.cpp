#include "LoadBalancer.h"
#include "Request.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <string>
#include <cstdlib>
#include <ctime>
#include <random>
using namespace std;

mutex outputMutex;

/**
 * @brief Generates random web requests and sends them to the load balancer.
 * @param loadbalancer The LoadBalancer object that will process the requests.
 */
void generateRandomRequests(LoadBalancer& loadbalancer) {

    random_device randomNumberGenerator;
    mt19937 gen(randomNumberGenerator());
    uniform_int_distribution<> dis(1, 10);
    uniform_int_distribution<> ip(0, 255);

    while (true) {

        this_thread::sleep_for(chrono::seconds(dis(gen)));
        int requestIP = ip(gen);
        int responseIP = ip(gen);
        Request newRequest("192.168.1." + to_string(requestIP), "192.168.2." + to_string(responseIP), dis(gen));
        loadbalancer.transferRequest(newRequest);
        cout << "New request from 192.168.1." << requestIP << " to 192.168.2." << responseIP << endl;
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
    uniform_int_distribution<> dis(1, 10);

    for (int i = 0; i < 10; ++i) {

        int randomProcessingTime = dis(gen);
        Request request("192.168.1." + to_string(i), "192.168.2." + to_string(i), randomProcessingTime);
        loadBalancer.transferRequest(request);
    }

    thread requestThread(generateRandomRequests, ref(loadBalancer));
    requestThread.detach();

    while (true) {

        loadBalancer.processEveryRequest();
        this_thread::sleep_for(chrono::seconds(1));
    }

    return 0;
}
