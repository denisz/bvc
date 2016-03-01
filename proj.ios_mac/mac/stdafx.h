//
//  stdafx.hpp
//  bvunity
//
//  Created by denis zaytcev on 2/6/16.
//
//

#ifndef stdafx_hpp
#define stdafx_hpp

//macros
#include <stdio.h>
#include <chrono>
#include <future>
#include <thread>
#include <map>
#include <forward_list>

#include "Constants.h"
#include "Core.h"

#include "format.h"
#include "NotificationCenter.h"
#include "kiwi.h"

//rapidjson
#include "document.h"
#include "pointer.h"
#include "stringbuffer.h"
#include "writer.h"

//Reference counting
#include "AIRef.h"
#include "ValueMap.h"
#include "Error.hpp"

//task manager
#include "ThreadPool.hh"
#include "Scheduler.hh"
#include "Task.hpp"

#include "Bolts.hpp"

#endif /* stdafx_hpp */


