
#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include <socketpp/http/httpbase.h>
#include <vector>
#include <utility>
#include <unordered_map>

using namespace std;

// enumeration of HTTP request commands
typedef enum
{
        GET = 0,
        POST = 1,
        HEAD = 2,
        PUT = 3,
        DELETE = 4,
        CONNECT = 5,
        OPTIONS = 6,
        TRACE = 7
} http_cmd_t;

namespace http
{

class http_request : public http_base
{

private:

protected:

public:
        http_request();
        http_request(string);

        void setCmd(http_cmd_t);
        void setURI(string);
};

}

#endif // HTTPREQUEST_H
