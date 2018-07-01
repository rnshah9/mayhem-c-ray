//
//  includes.h
//  C-Ray
//
//  Created by Valtteri Koskivuori on 28/02/15.
//  Copyright (c) 2015-2018 Valtteri Koskivuori. All rights reserved.
//

#pragma once

//Comment this to disable SDL
//#define UI_ENABLED

//Global constants
#define MAX_CRAY_VERTEX_COUNT 3
#define PIOVER180 0.017453292519943295769236907684886
#define PI        3.141592653589793238462643383279502
#define MATERIAL_NAME_SIZE 256
#define OBJ_FILENAME_LENGTH 500

//Some macros
#define min(a,b) (((a) < (b)) ? (a) : (b))
#define max(a,b) (((a) > (b)) ? (a) : (b))
#define invsqrt(x) (1.0 / sqrt(x))

//Master include file
#define _XOPEN_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h> //for gettimeofday()
#include <stdbool.h>
#include <math.h>
#include <signal.h>
#include <string.h>

#ifdef WINDOWS
#include <Windows.h>
#ifdef UI_ENABLED
#include "SDL.h"
#endif
#else
#include <pthread.h>
#ifdef UI_ENABLED
#include <SDL2/SDL.h>
#endif
#endif
#include "lodepng.h"

//These are for multi-platform physical core detection
#ifdef MACOS
#include <sys/param.h>
#include <sys/sysctl.h>
#elif _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

//Project includes
#include "color.h"
#include "material.h"
#include "vector.h"
#include "list.h"
#include "sphere.h"
#include "transforms.h"
#include "lightRay.h"

enum fileMode {
	loadModeNormal,//Load scene def normally
	loadModeTarga, //Load previous render state
	saveModeNormal,//Save image
	saveModeTarga, //Save current render state
	saveModeNone   //Don't save
};

#ifdef WINDOWS
typedef struct timeval {
	long tv_sec;
	long tv_usec;
} timeval;

int gettimeofday(struct timeval * tp, struct timezone * tzp) {
	// Note: some broken versions only have 8 trailing zero's, the correct epoch has 9 trailing zero's
	// This magic number is the number of 100 nanosecond intervals since January 1, 1601 (UTC)
	// until 00:00:00 January 1, 1970
	static const uint64_t EPOCH = ((uint64_t) 116444736000000000ULL);
	
	SYSTEMTIME  system_time;
	FILETIME    file_time;
	uint64_t    time;
	
	GetSystemTime( &system_time );
	SystemTimeToFileTime( &system_time, &file_time );
	time =  ((uint64_t)file_time.dwLowDateTime )      ;
	time += ((uint64_t)file_time.dwHighDateTime) << 32;
	
	tp->tv_sec  = (long) ((time - EPOCH) / 10000000L);
	tp->tv_usec = (long) (system_time.wMilliseconds * 1000);
	return 0;
}
#endif

//Tile duration timer
static struct timeval timer;

//Timer funcs
static inline void startTimer() {
	gettimeofday(&timer, NULL);
}

static inline unsigned long long endTimer() {
	struct timeval tmr2;
	gettimeofday(&tmr2, NULL);
	return 1000 * (tmr2.tv_sec - timer.tv_sec) + ((tmr2.tv_usec - timer.tv_usec) / 1000);
}
