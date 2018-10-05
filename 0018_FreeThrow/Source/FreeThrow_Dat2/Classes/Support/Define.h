//
//  Define.h
//  Galaxy
//
//  Created by antl on 1/28/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//


#define SAFE_RELEASE(p)			{ if (p) { [(p) release]; (p) = nil;  } }

#define IS_IPHONE5 ((CCDirector::sharedDirector()->getWinSize().height-568)?false:true)
#define MAX_LINE 5
#define SCORE "define_Score" 
#define MIN_SCORE "MINSCORE" 
#define ARRAY_SCORE "ARRAY_SCORE" 