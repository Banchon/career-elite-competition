#include <stdio.h>
#include <vector>
#include <string>

#ifdef TEST
#include <iostream>
#endif

#define BUFFER_SIZE 64

using std::vector;
using std::string;


int recvmsg(FILE* in, vector<string>& msg_vector)
{
	char buffer[BUFFER_SIZE];
	string line;
	//get the first line of message.
	if(::fgets(buffer, BUFFER_SIZE, in) == NULL) {
		return -1;
	}
	line = buffer;
	msg_vector.push_back(line);

	//check whether the message has more lines.
	bool more_line_indication = false;
	string end;
	string::size_type index = line.find("/");
	if(index != string::npos && index != 1) {
		more_line_indication = true;
		end = line.substr(0, index);
		end.insert(0, "/");
	}
	
	while(more_line_indication) {
		if(::fgets(buffer, BUFFER_SIZE, in) == NULL) {
			return -1;
		}
		line = buffer;
		msg_vector.push_back(line);

		if(line.find(end) == 0) {
			more_line_indication = false;
		}
	}

	return 0;
}

#ifdef TEST
int main()
{
	FILE* in = ::fopen("messages.txt", "r");
	if(in == NULL) {
		return -1;
	}

	while(true) {
		vector<string> mesg;
		if(recvmsg(in, mesg) == -1)
			break;

		for(vector<string>::iterator it = mesg.begin(); it != mesg.end(); it++) {
			std::cout << *it;
		}
	}
	return 0;		
}
#endif
