#ifndef REQUEST_H
#define REQUEST_H

#include <string>
using namespace std;

/**
 * @struct Request
 * @brief Represents a web request with source, destination, and processing time.
 *
 * This struct is used to contain all relevant information about a web request,
 * including the source IP address, destination IP address, and the time required to process the request.
 */
struct Request {

    string requestIP; ///< Source IP address of the web request.
    string responseIP; ///< Destination IP address of the web request.
    int processingTime; ///< Processing time required for the web request in seconds.

    /**
     * @brief Constructs a Request object with specified source IP, destination IP, and processing time.
     * @param in Source IP address.
     * @param out Destination IP address.
     * @param processingTime Time required to process the request.
     */
    Request (const string& in, const string& out, int processingTime) : requestIP(in), responseIP(out), processingTime(processingTime) {


    }
};

#endif
