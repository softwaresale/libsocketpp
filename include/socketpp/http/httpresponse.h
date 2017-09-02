
#include <iostream>
#include <socketpp/http/httpbase.h>

using namespace std;

namespace http
{

  class http_response : public http_base
  {

  private:

  protected:

   public:
    http_response();
    http_response(string);

    void   setStatus();
    string setStatus();

    void setErrCode(int);
    int  getErrCode();

  };

}
