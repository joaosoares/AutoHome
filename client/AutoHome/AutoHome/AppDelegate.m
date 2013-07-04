//
//  AppDelegate.m
//  AutoHome
//
//  Created by João Soares on 6/28/13.
//  Copyright (c) 2013 João Soares. All rights reserved.
//

#import "AppDelegate.h"
#include "MasterViewController.h"

@interface AppDelegate()
@property (nonatomic, strong) IBOutlet MasterViewController *masterViewController;
@end

@implementation AppDelegate

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
    // Insert code here to initialize your application
    // 1. Create master view controller
    self.masterViewController = [[MasterViewController alloc] initWithNibName:@"MasterViewController" bundle:nil];
    
    // 2. Add the view contorller to the Window view
    [self.window.contentView addSubview:self.masterViewController.view];
    self.masterViewController.view.frame = ((NSView*)self.window.contentView).bounds;
}

@end
