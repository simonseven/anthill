//
//  main.m
//  mds
//
//  Created by Chuck Rose on 3/1/15.
//  Copyright (c) 2015 cfr3. All rights reserved.
//

#import <Cocoa/Cocoa.h>

#include "anthill/core/Exceptions.h"

int main(int argc, const char * argv[]) {
    
    AX_ENFORCE(argc > 0);
    
    return NSApplicationMain(argc, argv);
}
