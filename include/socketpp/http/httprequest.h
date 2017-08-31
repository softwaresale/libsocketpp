
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

        GET,
        POST,
        HEAD,
        PUT,
        DELETE,
        CONNECT,
        OPTIONS,
        TRACE

} http_cmd_t;

namespace http
{

class http_request : public http_base
{

private:

protected:

public:
        http_request();

        void setCmd(http_cmd_t);
        void setURI(string);
};

}

#endif // HTTPREQUEST_H
