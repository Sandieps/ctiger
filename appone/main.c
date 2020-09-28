//
//  main.c
//  appone
//
//  Created by sandie on 29/09/20.
//

#include <stdio.h>
#include "app.h"

int main(int argc, const char * argv[]) {
    
    const char * host = argv[2];
    const char * httpmethod = argv[1];
    const char * requesturi = argv[3];
    const char * requestbody = argv[4];
    
    httprequest(host, httpmethod, requesturi, requestbody);
    
    
    return 0;
}
