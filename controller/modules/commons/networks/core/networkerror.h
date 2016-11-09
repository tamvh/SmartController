#ifndef NETWORKERROR_H
#define NETWORKERROR_H

typedef enum {
    NetworkErrorNoError = 0,
    NetworkErrorConnection,
    NetworkErrorEmptyResponse,
    NetworkErrorInvalidJson,
    NetworkErrorInvalidResponse,
    NetworkErrorInvalidParameter,
    NetworkErrorMissingParameter,
    NetworkErrorServerError
} NetworkError;

#endif // NETWORKERROR_H
