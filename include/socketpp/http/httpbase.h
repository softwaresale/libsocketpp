
#ifndef HTTPBASE_H
#define HTTPBASE_H

#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

namespace http
{

class http_base
{

protected:

        // containers of data
        /*
          0 -- command or version
          1 -- URI     or status
          2 -- Version or text
         */
        vector<string>               cmd_line;
        vector<pair<string, string>> header_data;
        string                       body;

        // sets portions of data (key -> value)
        void setCmdData(string, string);
        // returns string portion of objects
        string dumpCmd();

public:
        http_base();


        string toString();
        void setHeaderData(string, string);
        void setBody(string);
        string dumpHead();
        string dumpBody();
};

}

#endif // HTTPBASE
