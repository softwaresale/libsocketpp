
/* This file handles basic logging */

#ifndef LOGGING_H
#define LOGGING_H 1

typedef enum
{
	INFO,
	WARNING,
	ERROR
} Status_t;

class Log
{

private:

protected:
	
public:
	Log();
	
	void log(char*  msg, Status_t status);
	void info(char* msg);
	void warn(char* msg);
	void err(char*  msg);

};

#endif // LOGGING_H
