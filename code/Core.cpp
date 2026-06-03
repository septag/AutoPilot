// This source file is auto-generated
// Inlined files:
//	allocators.cpp
//	base.cpp
//	debug.cpp
//	debugclang.cpp
//	debugwin.cpp
//	cj5.h
//	cpu-features.c
//	cpu-features.h
//	ini.h
//	minicoro.h
//	remedybg_driver.h
//	sokol_args.h
//	stb_sprintf.h
//	tlsf.c
//	tlsf.h
//	tracycallstack.h
//	tracyapi.h
//	tracyuwp.hpp
//	tracyc.h
//	hash.cpp
//	includewin.h
//	iniparser.cpp
//	jobs.cpp
//	jsonparser.cpp
//	log.cpp
//	mathall.cpp
//	pools.cpp
//	settings.cpp
//	stringutil.cpp
//	stringutilwin.cpp
//	system.cpp
//	systemandroid.cpp
//	systemlinux.cpp
//	systemmac.cpp
//	systemposix.cpp
//	systemwin.cpp
//	tracyhelper.cpp
//	tracyhelper.h

#include "Core.h"
#define BUILD_UNITY

#include <stdlib.h>

//----------------------------------------------------------------------------------------------------------------------
// TracyHelper.h



#ifndef TRACY_CALLSTACK
    #define TRACY_CALLSTACK 16
#endif

#ifndef TRACY_FIBERS
    #define TRACY_FIBERS
#endif

#if PLATFORM_LINUX || PLATFORM_WINDOWS
    #define TRACY_NO_CALLSTACK
#endif

//----------------------------------------------------------------------------------------------------------------------
// External/tracy/tracy/TracyC.h

#ifndef __TRACYC_HPP__
#define __TRACYC_HPP__

#include <stddef.h>
#include <stdint.h>

//----------------------------------------------------------------------------------------------------------------------
// ../client/TracyCallstack.h

#ifndef __TRACYCALLSTACK_H__
#define __TRACYCALLSTACK_H__

#ifndef TRACY_NO_CALLSTACK

#  if !defined _WIN32
#    include <sys/param.h>
#  endif

#  if defined _WIN32
//----------------------------------------------------------------------------------------------------------------------
// ../common/TracyUwp.hpp

#ifndef __TRACYUWP_HPP__
#define __TRACYUWP_HPP__

#ifdef _WIN32
#  include <winapifamily.h>
#  if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP) && !WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
#    define TRACY_UWP
#  endif
#endif

#endif

#    ifndef TRACY_UWP
#      define TRACY_HAS_CALLSTACK 1
#    endif
#  elif defined __ANDROID__
#    if !defined __arm__ || __ANDROID_API__ >= 21
#      define TRACY_HAS_CALLSTACK 2
#    else
#      define TRACY_HAS_CALLSTACK 5
#    endif
#  elif defined __linux
#    if defined _GNU_SOURCE && defined __GLIBC__
#      define TRACY_HAS_CALLSTACK 3
#    else
#      define TRACY_HAS_CALLSTACK 2
#    endif
#  elif defined __APPLE__
#    define TRACY_HAS_CALLSTACK 4
#  elif defined BSD
#    define TRACY_HAS_CALLSTACK 6
#  endif

#endif

#endif

//----------------------------------------------------------------------------------------------------------------------
// ../common/TracyApi.h

#ifndef __TRACYAPI_H__
#define __TRACYAPI_H__

#if defined _WIN32
#  if defined TRACY_EXPORTS
#    define TRACY_API __declspec(dllexport)
#  elif defined TRACY_IMPORTS
#    define TRACY_API __declspec(dllimport)
#  else
#    define TRACY_API
#  endif
#else
#  define TRACY_API __attribute__((visibility("default")))
#endif

#endif    // __TRACYAPI_H__


#ifdef __cplusplus
extern "C" {
#endif

enum TracyPlotFormatEnum
{
    TracyPlotFormatNumber,
    TracyPlotFormatMemory,
    TracyPlotFormatPercentage,
    TracyPlotFormatWatt
};

TRACY_API void ___tracy_set_thread_name( const char* name );

#define TracyCSetThreadName( name ) ___tracy_set_thread_name( name );

#ifndef TracyFunction
#  define TracyFunction __FUNCTION__
#endif

#ifndef TracyFile
#  define TracyFile __FILE__
#endif

#ifndef TracyLine
#  define TracyLine __LINE__
#endif

#ifndef TRACY_ENABLE

typedef const void* TracyCZoneCtx;

typedef const void* TracyCLockCtx;

#define TracyCZone(c,x)
#define TracyCZoneN(c,x,y)
#define TracyCZoneC(c,x,y)
#define TracyCZoneNC(c,x,y,z)
#define TracyCZoneEnd(c)
#define TracyCZoneText(c,x,y)
#define TracyCZoneName(c,x,y)
#define TracyCZoneColor(c,x)
#define TracyCZoneValue(c,x)

#define TracyCAlloc(x,y)
#define TracyCFree(x)
#define TracyCSecureAlloc(x,y)
#define TracyCSecureFree(x)

#define TracyCAllocN(x,y,z)
#define TracyCFreeN(x,y)
#define TracyCSecureAllocN(x,y,z)
#define TracyCSecureFreeN(x,y)

#define TracyCFrameMark
#define TracyCFrameMarkNamed(x)
#define TracyCFrameMarkStart(x)
#define TracyCFrameMarkEnd(x)
#define TracyCFrameImage(x,y,z,w,a)

#define TracyCPlot(x,y)
#define TracyCPlotF(x,y)
#define TracyCPlotI(x,y)
#define TracyCPlotConfig(x,y,z,w,a)

#define TracyCMessage(x,y)
#define TracyCMessageL(x)
#define TracyCMessageC(x,y,z)
#define TracyCMessageLC(x,y)
#define TracyCAppInfo(x,y)

#define TracyCZoneS(x,y,z)
#define TracyCZoneNS(x,y,z,w)
#define TracyCZoneCS(x,y,z,w)
#define TracyCZoneNCS(x,y,z,w,a)

#define TracyCAllocS(x,y,z)
#define TracyCFreeS(x,y)
#define TracyCSecureAllocS(x,y,z)
#define TracyCSecureFreeS(x,y)

#define TracyCAllocNS(x,y,z,w)
#define TracyCFreeNS(x,y,z)
#define TracyCSecureAllocNS(x,y,z,w)
#define TracyCSecureFreeNS(x,y,z)

#define TracyCMessageS(x,y,z)
#define TracyCMessageLS(x,y)
#define TracyCMessageCS(x,y,z,w)
#define TracyCMessageLCS(x,y,z)

#define TracyCLockCtx(l)
#define TracyCLockAnnounce(l)
#define TracyCLockTerminate(l)
#define TracyCLockBeforeLock(l)
#define TracyCLockAfterLock(l)
#define TracyCLockAfterUnlock(l)
#define TracyCLockAfterTryLock(l,x)
#define TracyCLockMark(l)
#define TracyCLockCustomName(l,x,y)

#define TracyCIsConnected 0
#define TracyCIsStarted 0

#ifdef TRACY_FIBERS
#  define TracyCFiberEnter(fiber)
#  define TracyCFiberLeave
#endif

#else

#ifndef TracyConcat
#  define TracyConcat(x,y) TracyConcatIndirect(x,y)
#endif
#ifndef TracyConcatIndirect
#  define TracyConcatIndirect(x,y) x##y
#endif

struct ___tracy_source_location_data
{
    const char* name;
    const char* function;
    const char* file;
    uint32_t line;
    uint32_t color;
};

struct ___tracy_c_zone_context
{
    uint32_t id;
    int active;
};

struct ___tracy_gpu_time_data
{
    int64_t gpuTime;
    uint16_t queryId;
    uint8_t context;
};

struct ___tracy_gpu_zone_begin_data {
    uint64_t srcloc;
    uint16_t queryId;
    uint8_t context;
};

struct ___tracy_gpu_zone_begin_callstack_data {
    uint64_t srcloc;
    int depth;
    uint16_t queryId;
    uint8_t context;
};

struct ___tracy_gpu_zone_end_data {
    uint16_t queryId;
    uint8_t context;
};

struct ___tracy_gpu_new_context_data {
    int64_t gpuTime;
    float period;
    uint8_t context;
    uint8_t flags;
    uint8_t type;
};

struct ___tracy_gpu_context_name_data {
    uint8_t context;
    const char* name;
    uint16_t len;
};

struct ___tracy_gpu_calibration_data {
    int64_t gpuTime;
    int64_t cpuDelta;
    uint8_t context;
};

struct ___tracy_gpu_time_sync_data {
    int64_t gpuTime;
    uint8_t context;
};

struct __tracy_lockable_context_data;

typedef /*const*/ struct ___tracy_c_zone_context TracyCZoneCtx;

typedef struct __tracy_lockable_context_data* TracyCLockCtx;

#ifdef TRACY_MANUAL_LIFETIME
TRACY_API void ___tracy_startup_profiler(void);
TRACY_API void ___tracy_shutdown_profiler(void);
TRACY_API int ___tracy_profiler_started(void);

#  define TracyCIsStarted ___tracy_profiler_started()
#else
#  define TracyCIsStarted 1
#endif

TRACY_API uint64_t ___tracy_alloc_srcloc( uint32_t line, const char* source, size_t sourceSz, const char* function, size_t functionSz, uint32_t color );
TRACY_API uint64_t ___tracy_alloc_srcloc_name( uint32_t line, const char* source, size_t sourceSz, const char* function, size_t functionSz, const char* name, size_t nameSz, uint32_t color );

TRACY_API TracyCZoneCtx ___tracy_emit_zone_begin( const struct ___tracy_source_location_data* srcloc, int active );
TRACY_API TracyCZoneCtx ___tracy_emit_zone_begin_callstack( const struct ___tracy_source_location_data* srcloc, int depth, int active );
TRACY_API TracyCZoneCtx ___tracy_emit_zone_begin_alloc( uint64_t srcloc, int active );
TRACY_API TracyCZoneCtx ___tracy_emit_zone_begin_alloc_callstack( uint64_t srcloc, int depth, int active );
TRACY_API void ___tracy_emit_zone_end( TracyCZoneCtx ctx );
TRACY_API void ___tracy_emit_zone_text( TracyCZoneCtx ctx, const char* txt, size_t size );
TRACY_API void ___tracy_emit_zone_name( TracyCZoneCtx ctx, const char* txt, size_t size );
TRACY_API void ___tracy_emit_zone_color( TracyCZoneCtx ctx, uint32_t color );
TRACY_API void ___tracy_emit_zone_value( TracyCZoneCtx ctx, uint64_t value );

TRACY_API void ___tracy_emit_gpu_zone_begin( const struct ___tracy_gpu_zone_begin_data );
TRACY_API void ___tracy_emit_gpu_zone_begin_callstack( const struct ___tracy_gpu_zone_begin_callstack_data );
TRACY_API void ___tracy_emit_gpu_zone_begin_alloc( const struct ___tracy_gpu_zone_begin_data );
TRACY_API void ___tracy_emit_gpu_zone_begin_alloc_callstack( const struct ___tracy_gpu_zone_begin_callstack_data );
TRACY_API void ___tracy_emit_gpu_zone_end( const struct ___tracy_gpu_zone_end_data data );
TRACY_API void ___tracy_emit_gpu_time( const struct ___tracy_gpu_time_data );
TRACY_API void ___tracy_emit_gpu_new_context( const struct ___tracy_gpu_new_context_data );
TRACY_API void ___tracy_emit_gpu_context_name( const struct ___tracy_gpu_context_name_data );
TRACY_API void ___tracy_emit_gpu_calibration( const struct ___tracy_gpu_calibration_data );
TRACY_API void ___tracy_emit_gpu_time_sync( const struct ___tracy_gpu_time_sync_data );

TRACY_API void ___tracy_emit_gpu_zone_begin_serial( const struct ___tracy_gpu_zone_begin_data );
TRACY_API void ___tracy_emit_gpu_zone_begin_callstack_serial( const struct ___tracy_gpu_zone_begin_callstack_data );
TRACY_API void ___tracy_emit_gpu_zone_begin_alloc_serial( const struct ___tracy_gpu_zone_begin_data );
TRACY_API void ___tracy_emit_gpu_zone_begin_alloc_callstack_serial( const struct ___tracy_gpu_zone_begin_callstack_data );
TRACY_API void ___tracy_emit_gpu_zone_end_serial( const struct ___tracy_gpu_zone_end_data data );
TRACY_API void ___tracy_emit_gpu_time_serial( const struct ___tracy_gpu_time_data );
TRACY_API void ___tracy_emit_gpu_new_context_serial( const struct ___tracy_gpu_new_context_data );
TRACY_API void ___tracy_emit_gpu_context_name_serial( const struct ___tracy_gpu_context_name_data );
TRACY_API void ___tracy_emit_gpu_calibration_serial( const struct ___tracy_gpu_calibration_data );
TRACY_API void ___tracy_emit_gpu_time_sync_serial( const struct ___tracy_gpu_time_sync_data );

TRACY_API int ___tracy_connected(void);

#if defined TRACY_HAS_CALLSTACK && defined TRACY_CALLSTACK
#  define TracyCZone( ctx, active ) static const struct ___tracy_source_location_data TracyConcat(__tracy_source_location,TracyLine) = { NULL, __func__,  TracyFile, (uint32_t)TracyLine, 0 }; TracyCZoneCtx ctx = ___tracy_emit_zone_begin_callstack( &TracyConcat(__tracy_source_location,TracyLine), TRACY_CALLSTACK, active );
#  define TracyCZoneN( ctx, name, active ) static const struct ___tracy_source_location_data TracyConcat(__tracy_source_location,TracyLine) = { name, __func__,  TracyFile, (uint32_t)TracyLine, 0 }; TracyCZoneCtx ctx = ___tracy_emit_zone_begin_callstack( &TracyConcat(__tracy_source_location,TracyLine), TRACY_CALLSTACK, active );
#  define TracyCZoneC( ctx, color, active ) static const struct ___tracy_source_location_data TracyConcat(__tracy_source_location,TracyLine) = { NULL, __func__,  TracyFile, (uint32_t)TracyLine, color }; TracyCZoneCtx ctx = ___tracy_emit_zone_begin_callstack( &TracyConcat(__tracy_source_location,TracyLine), TRACY_CALLSTACK, active );
#  define TracyCZoneNC( ctx, name, color, active ) static const struct ___tracy_source_location_data TracyConcat(__tracy_source_location,TracyLine) = { name, __func__,  TracyFile, (uint32_t)TracyLine, color }; TracyCZoneCtx ctx = ___tracy_emit_zone_begin_callstack( &TracyConcat(__tracy_source_location,TracyLine), TRACY_CALLSTACK, active );
#else
#  define TracyCZone( ctx, active ) static const struct ___tracy_source_location_data TracyConcat(__tracy_source_location,TracyLine) = { NULL, __func__,  TracyFile, (uint32_t)TracyLine, 0 }; TracyCZoneCtx ctx = ___tracy_emit_zone_begin( &TracyConcat(__tracy_source_location,TracyLine), active );
#  define TracyCZoneN( ctx, name, active ) static const struct ___tracy_source_location_data TracyConcat(__tracy_source_location,TracyLine) = { name, __func__,  TracyFile, (uint32_t)TracyLine, 0 }; TracyCZoneCtx ctx = ___tracy_emit_zone_begin( &TracyConcat(__tracy_source_location,TracyLine), active );
#  define TracyCZoneC( ctx, color, active ) static const struct ___tracy_source_location_data TracyConcat(__tracy_source_location,TracyLine) = { NULL, __func__,  TracyFile, (uint32_t)TracyLine, color }; TracyCZoneCtx ctx = ___tracy_emit_zone_begin( &TracyConcat(__tracy_source_location,TracyLine), active );
#  define TracyCZoneNC( ctx, name, color, active ) static const struct ___tracy_source_location_data TracyConcat(__tracy_source_location,TracyLine) = { name, __func__,  TracyFile, (uint32_t)TracyLine, color }; TracyCZoneCtx ctx = ___tracy_emit_zone_begin( &TracyConcat(__tracy_source_location,TracyLine), active );
#endif

#define TracyCZoneEnd( ctx ) ___tracy_emit_zone_end( ctx );

#define TracyCZoneText( ctx, txt, size ) ___tracy_emit_zone_text( ctx, txt, size );
#define TracyCZoneName( ctx, txt, size ) ___tracy_emit_zone_name( ctx, txt, size );
#define TracyCZoneColor( ctx, color ) ___tracy_emit_zone_color( ctx, color );
#define TracyCZoneValue( ctx, value ) ___tracy_emit_zone_value( ctx, value );


TRACY_API void ___tracy_emit_memory_alloc( const void* ptr, size_t size, int secure );
TRACY_API void ___tracy_emit_memory_alloc_callstack( const void* ptr, size_t size, int depth, int secure );
TRACY_API void ___tracy_emit_memory_free( const void* ptr, int secure );
TRACY_API void ___tracy_emit_memory_free_callstack( const void* ptr, int depth, int secure );
TRACY_API void ___tracy_emit_memory_alloc_named( const void* ptr, size_t size, int secure, const char* name );
TRACY_API void ___tracy_emit_memory_alloc_callstack_named( const void* ptr, size_t size, int depth, int secure, const char* name );
TRACY_API void ___tracy_emit_memory_free_named( const void* ptr, int secure, const char* name );
TRACY_API void ___tracy_emit_memory_free_callstack_named( const void* ptr, int depth, int secure, const char* name );

TRACY_API void ___tracy_emit_message( const char* txt, size_t size, int callstack );
TRACY_API void ___tracy_emit_messageL( const char* txt, int callstack );
TRACY_API void ___tracy_emit_messageC( const char* txt, size_t size, uint32_t color, int callstack );
TRACY_API void ___tracy_emit_messageLC( const char* txt, uint32_t color, int callstack );

#if defined TRACY_HAS_CALLSTACK && defined TRACY_CALLSTACK
#  define TracyCAlloc( ptr, size ) ___tracy_emit_memory_alloc_callstack( ptr, size, TRACY_CALLSTACK, 0 )
#  define TracyCFree( ptr ) ___tracy_emit_memory_free_callstack( ptr, TRACY_CALLSTACK, 0 )
#  define TracyCSecureAlloc( ptr, size ) ___tracy_emit_memory_alloc_callstack( ptr, size, TRACY_CALLSTACK, 1 )
#  define TracyCSecureFree( ptr ) ___tracy_emit_memory_free_callstack( ptr, TRACY_CALLSTACK, 1 )

#  define TracyCAllocN( ptr, size, name ) ___tracy_emit_memory_alloc_callstack_named( ptr, size, TRACY_CALLSTACK, 0, name )
#  define TracyCFreeN( ptr, name ) ___tracy_emit_memory_free_callstack_named( ptr, TRACY_CALLSTACK, 0, name )
#  define TracyCSecureAllocN( ptr, size, name ) ___tracy_emit_memory_alloc_callstack_named( ptr, size, TRACY_CALLSTACK, 1, name )
#  define TracyCSecureFreeN( ptr, name ) ___tracy_emit_memory_free_callstack_named( ptr, TRACY_CALLSTACK, 1, name )

#  define TracyCMessage( txt, size ) ___tracy_emit_message( txt, size, TRACY_CALLSTACK );
#  define TracyCMessageL( txt ) ___tracy_emit_messageL( txt, TRACY_CALLSTACK );
#  define TracyCMessageC( txt, size, color ) ___tracy_emit_messageC( txt, size, color, TRACY_CALLSTACK );
#  define TracyCMessageLC( txt, color ) ___tracy_emit_messageLC( txt, color, TRACY_CALLSTACK );
#else
#  define TracyCAlloc( ptr, size ) ___tracy_emit_memory_alloc( ptr, size, 0 );
#  define TracyCFree( ptr ) ___tracy_emit_memory_free( ptr, 0 );
#  define TracyCSecureAlloc( ptr, size ) ___tracy_emit_memory_alloc( ptr, size, 1 );
#  define TracyCSecureFree( ptr ) ___tracy_emit_memory_free( ptr, 1 );

#  define TracyCAllocN( ptr, size, name ) ___tracy_emit_memory_alloc_named( ptr, size, 0, name );
#  define TracyCFreeN( ptr, name ) ___tracy_emit_memory_free_named( ptr, 0, name );
#  define TracyCSecureAllocN( ptr, size, name ) ___tracy_emit_memory_alloc_named( ptr, size, 1, name );
#  define TracyCSecureFreeN( ptr, name ) ___tracy_emit_memory_free_named( ptr, 1, name );

#  define TracyCMessage( txt, size ) ___tracy_emit_message( txt, size, 0 );
#  define TracyCMessageL( txt ) ___tracy_emit_messageL( txt, 0 );
#  define TracyCMessageC( txt, size, color ) ___tracy_emit_messageC( txt, size, color, 0 );
#  define TracyCMessageLC( txt, color ) ___tracy_emit_messageLC( txt, color, 0 );
#endif


TRACY_API void ___tracy_emit_frame_mark( const char* name );
TRACY_API void ___tracy_emit_frame_mark_start( const char* name );
TRACY_API void ___tracy_emit_frame_mark_end( const char* name );
TRACY_API void ___tracy_emit_frame_image( const void* image, uint16_t w, uint16_t h, uint8_t offset, int flip );

#define TracyCFrameMark ___tracy_emit_frame_mark( 0 );
#define TracyCFrameMarkNamed( name ) ___tracy_emit_frame_mark( name );
#define TracyCFrameMarkStart( name ) ___tracy_emit_frame_mark_start( name );
#define TracyCFrameMarkEnd( name ) ___tracy_emit_frame_mark_end( name );
#define TracyCFrameImage( image, width, height, offset, flip ) ___tracy_emit_frame_image( image, width, height, offset, flip );


TRACY_API void ___tracy_emit_plot( const char* name, double val );
TRACY_API void ___tracy_emit_plot_float( const char* name, float val );
TRACY_API void ___tracy_emit_plot_int( const char* name, int64_t val );
TRACY_API void ___tracy_emit_plot_config( const char* name, int type, int step, int fill, uint32_t color );
TRACY_API void ___tracy_emit_message_appinfo( const char* txt, size_t size );

#define TracyCPlot( name, val ) ___tracy_emit_plot( name, val );
#define TracyCPlotF( name, val ) ___tracy_emit_plot_float( name, val );
#define TracyCPlotI( name, val ) ___tracy_emit_plot_int( name, val );
#define TracyCPlotConfig( name, type, step, fill, color ) ___tracy_emit_plot_config( name, type, step, fill, color );
#define TracyCAppInfo( txt, size ) ___tracy_emit_message_appinfo( txt, size );


#ifdef TRACY_HAS_CALLSTACK
#  define TracyCZoneS( ctx, depth, active ) static const struct ___tracy_source_location_data TracyConcat(__tracy_source_location,TracyLine) = { NULL, __func__,  TracyFile, (uint32_t)TracyLine, 0 }; TracyCZoneCtx ctx = ___tracy_emit_zone_begin_callstack( &TracyConcat(__tracy_source_location,TracyLine), depth, active );
#  define TracyCZoneNS( ctx, name, depth, active ) static const struct ___tracy_source_location_data TracyConcat(__tracy_source_location,TracyLine) = { name, __func__,  TracyFile, (uint32_t)TracyLine, 0 }; TracyCZoneCtx ctx = ___tracy_emit_zone_begin_callstack( &TracyConcat(__tracy_source_location,TracyLine), depth, active );
#  define TracyCZoneCS( ctx, color, depth, active ) static const struct ___tracy_source_location_data TracyConcat(__tracy_source_location,TracyLine) = { NULL, __func__,  TracyFile, (uint32_t)TracyLine, color }; TracyCZoneCtx ctx = ___tracy_emit_zone_begin_callstack( &TracyConcat(__tracy_source_location,TracyLine), depth, active );
#  define TracyCZoneNCS( ctx, name, color, depth, active ) static const struct ___tracy_source_location_data TracyConcat(__tracy_source_location,TracyLine) = { name, __func__,  TracyFile, (uint32_t)TracyLine, color }; TracyCZoneCtx ctx = ___tracy_emit_zone_begin_callstack( &TracyConcat(__tracy_source_location,TracyLine), depth, active );

#  define TracyCAllocS( ptr, size, depth ) ___tracy_emit_memory_alloc_callstack( ptr, size, depth, 0 )
#  define TracyCFreeS( ptr, depth ) ___tracy_emit_memory_free_callstack( ptr, depth, 0 )
#  define TracyCSecureAllocS( ptr, size, depth ) ___tracy_emit_memory_alloc_callstack( ptr, size, depth, 1 )
#  define TracyCSecureFreeS( ptr, depth ) ___tracy_emit_memory_free_callstack( ptr, depth, 1 )

#  define TracyCAllocNS( ptr, size, depth, name ) ___tracy_emit_memory_alloc_callstack_named( ptr, size, depth, 0, name )
#  define TracyCFreeNS( ptr, depth, name ) ___tracy_emit_memory_free_callstack_named( ptr, depth, 0, name )
#  define TracyCSecureAllocNS( ptr, size, depth, name ) ___tracy_emit_memory_alloc_callstack_named( ptr, size, depth, 1, name )
#  define TracyCSecureFreeNS( ptr, depth, name ) ___tracy_emit_memory_free_callstack_named( ptr, depth, 1, name )

#  define TracyCMessageS( txt, size, depth ) ___tracy_emit_message( txt, size, depth );
#  define TracyCMessageLS( txt, depth ) ___tracy_emit_messageL( txt, depth );
#  define TracyCMessageCS( txt, size, color, depth ) ___tracy_emit_messageC( txt, size, color, depth );
#  define TracyCMessageLCS( txt, color, depth ) ___tracy_emit_messageLC( txt, color, depth );
#else
#  define TracyCZoneS( ctx, depth, active ) TracyCZone( ctx, active )
#  define TracyCZoneNS( ctx, name, depth, active ) TracyCZoneN( ctx, name, active )
#  define TracyCZoneCS( ctx, color, depth, active ) TracyCZoneC( ctx, color, active )
#  define TracyCZoneNCS( ctx, name, color, depth, active ) TracyCZoneNC( ctx, name, color, active )

#  define TracyCAllocS( ptr, size, depth ) TracyCAlloc( ptr, size )
#  define TracyCFreeS( ptr, depth ) TracyCFree( ptr )
#  define TracyCSecureAllocS( ptr, size, depth ) TracyCSecureAlloc( ptr, size )
#  define TracyCSecureFreeS( ptr, depth ) TracyCSecureFree( ptr )

#  define TracyCAllocNS( ptr, size, depth, name ) TracyCAllocN( ptr, size, name )
#  define TracyCFreeNS( ptr, depth, name ) TracyCFreeN( ptr, name )
#  define TracyCSecureAllocNS( ptr, size, depth, name ) TracyCSecureAllocN( ptr, size, name )
#  define TracyCSecureFreeNS( ptr, depth, name ) TracyCSecureFreeN( ptr, name )

#  define TracyCMessageS( txt, size, depth ) TracyCMessage( txt, size )
#  define TracyCMessageLS( txt, depth ) TracyCMessageL( txt )
#  define TracyCMessageCS( txt, size, color, depth ) TracyCMessageC( txt, size, color )
#  define TracyCMessageLCS( txt, color, depth ) TracyCMessageLC( txt, color )
#endif


TRACY_API struct __tracy_lockable_context_data* ___tracy_announce_lockable_ctx( const struct ___tracy_source_location_data* srcloc );
TRACY_API void ___tracy_terminate_lockable_ctx( struct __tracy_lockable_context_data* lockdata );
TRACY_API int ___tracy_before_lock_lockable_ctx( struct __tracy_lockable_context_data* lockdata );
TRACY_API void ___tracy_after_lock_lockable_ctx( struct __tracy_lockable_context_data* lockdata );
TRACY_API void ___tracy_after_unlock_lockable_ctx( struct __tracy_lockable_context_data* lockdata );
TRACY_API void ___tracy_after_try_lock_lockable_ctx( struct __tracy_lockable_context_data* lockdata, int acquired );
TRACY_API void ___tracy_mark_lockable_ctx( struct __tracy_lockable_context_data* lockdata, const struct ___tracy_source_location_data* srcloc );
TRACY_API void ___tracy_custom_name_lockable_ctx( struct __tracy_lockable_context_data* lockdata, const char* name, size_t nameSz );

#define TracyCLockAnnounce( lock ) static const struct ___tracy_source_location_data TracyConcat(__tracy_source_location,TracyLine) = { NULL, __func__,  TracyFile, (uint32_t)TracyLine, 0 }; lock = ___tracy_announce_lockable_ctx( &TracyConcat(__tracy_source_location,TracyLine) );
#define TracyCLockTerminate( lock ) ___tracy_terminate_lockable_ctx( lock );
#define TracyCLockBeforeLock( lock ) ___tracy_before_lock_lockable_ctx( lock );
#define TracyCLockAfterLock( lock ) ___tracy_after_lock_lockable_ctx( lock );
#define TracyCLockAfterUnlock( lock ) ___tracy_after_unlock_lockable_ctx( lock );
#define TracyCLockAfterTryLock( lock, acquired ) ___tracy_after_try_lock_lockable_ctx( lock, acquired );
#define TracyCLockMark( lock ) static const struct ___tracy_source_location_data TracyConcat(__tracy_source_location,TracyLine) = { NULL, __func__,  TracyFile, (uint32_t)TracyLine, 0 }; ___tracy_mark_lockable_ctx( lock, &TracyConcat(__tracy_source_location,TracyLine) );
#define TracyCLockCustomName( lock, name, nameSz ) ___tracy_custom_name_lockable_ctx( lock, name, nameSz );

#define TracyCIsConnected ___tracy_connected()

#ifdef TRACY_FIBERS
TRACY_API void ___tracy_fiber_enter( const char* fiber );
TRACY_API void ___tracy_fiber_leave( void );

#  define TracyCFiberEnter( fiber ) ___tracy_fiber_enter( fiber );
#  define TracyCFiberLeave ___tracy_fiber_leave();
#endif

#endif

#ifdef __cplusplus
}
#endif

#endif


#ifdef TRACY_ENABLE
    using TracyZoneEnterCallback = void(*)(TracyCZoneCtx* ctx, const ___tracy_source_location_data* sourceLoc);
    using TracyZoneExitCallback = bool(*)(TracyCZoneCtx* ctx);

    namespace Tracy
    {
        API void SetZoneCallbacks(TracyZoneEnterCallback zoneEnterCallback, TracyZoneExitCallback zoneExitCallback);
        API void RunZoneEnterCallback(TracyCZoneCtx* ctx, const ___tracy_source_location_data* sourceLoc);
        API bool RunZoneExitCallback(TracyCZoneCtx* ctx);

        API int64 GetTime();

        struct CpuProfilerScope
        {
            TracyCZoneCtx mCtx;

            CpuProfilerScope() = delete;

            explicit CpuProfilerScope(const ___tracy_source_location_data* sourceLoc, int callstackDepth, bool isActive, bool isAlloc);
            ~CpuProfilerScope();
        };
    }

    #define TracyCRealloc(oldPtr, ptr, size) if (oldPtr) { TracyCFree(oldPtr); }  TracyCAlloc(ptr, size)

    TRACY_API uint64_t ___tracy_alloc_srcloc_name( uint32_t line, const char* source, size_t sourceSz, const char* function, size_t functionSz, const char* name, size_t nameSz, uint32_t color );

    #if defined TRACY_HAS_CALLSTACK && defined TRACY_CALLSTACK
        #define PROFILE_ZONE_OPT(active, name) \
            static constexpr struct ___tracy_source_location_data CONCAT(__tracy_source_location,__LINE__) = { name, __func__,  __FILE__, (uint32_t)__LINE__, 0 }; \
            Tracy::CpuProfilerScope CONCAT(__cpu_profiler,__LINE__)(&CONCAT(__tracy_source_location,__LINE__), TRACY_CALLSTACK, active, false)
        #define PROFILE_ZONE_ALLOC_OPT(name, active) \
            struct ___tracy_source_location_data CONCAT(__tracy_source_location,__LINE__) = { name, __func__,  __FILE__, (uint32_t)__LINE__, 0 }; \
            Tracy::CpuProfilerScope CONCAT(__cpu_profiler,__LINE__)(&CONCAT(__tracy_source_location,__LINE__), TRACY_CALLSTACK, active, true)
        #define PROFILE_ZONE_COLOR_OPT(name, color, active) \
            static constexpr struct ___tracy_source_location_data CONCAT(__tracy_source_location,__LINE__) = { name, __func__,  __FILE__, (uint32_t)__LINE__, color }; \
            Tracy::CpuProfilerScope CONCAT(__cpu_profiler,__LINE__)(&CONCAT(__tracy_source_location,__LINE__), TRACY_CALLSTACK, active, false)
        #define PROFILE_ZONE_ALLOC_COLOR_OPT(name, color, active) \
            static constexpr struct ___tracy_source_location_data CONCAT(__tracy_source_location,__LINE__) = { name, __func__,  __FILE__, (uint32_t)__LINE__, color }; \
            Tracy::CpuProfilerScope CONCAT(__cpu_profiler,__LINE__)(&CONCAT(__tracy_source_location,__LINE__), TRACY_CALLSTACK, active, true)

        #define PROFILE_ZONE(name) PROFILE_ZONE_OPT(name, true)
        #define PROFILE_ZONE_ALLOC(name) PROFILE_ZONE_ALLOC_OPT(name, true)
        #define PROFILE_ZONE_COLOR(name, color) PROFILE_ZONE_COLOR_OPT(name, color, true)
        #define PROFILE_ZONE_ALLOC_COLOR(name, color) PROFILE_ZONE_ALLOC_COLOR_OPT(name, color, true)
    #else
        #define PROFILE_ZONE_OPT(name, active) \
            static constexpr struct ___tracy_source_location_data CONCAT(__tracy_source_location,__LINE__) = { name, __func__,  __FILE__, (uint32_t)__LINE__, 0 }; \
            Tracy::CpuProfilerScope CONCAT(__cpu_profiler,__LINE__)(&CONCAT(__tracy_source_location,__LINE__), 0, active, false)
        #define PROFILE_ZONE_ALLOC_OPT(name, active) \
            struct ___tracy_source_location_data CONCAT(__tracy_source_location,__LINE__) = { name, __func__,  __FILE__, (uint32_t)__LINE__, 0 }; \
            Tracy::CpuProfilerScope CONCAT(__cpu_profiler,__LINE__)(&CONCAT(__tracy_source_location,__LINE__), 0, active, true)
        #define PROFILE_ZONE_COLOR_OPT(name, color, active) \
            static constexpr struct ___tracy_source_location_data CONCAT(__tracy_source_location,__LINE__) = { name, __func__,  __FILE__, (uint32_t)__LINE__, color }; \
            Tracy::CpuProfilerScope CONCAT(__cpu_profiler,__LINE__)(&CONCAT(__tracy_source_location,__LINE__), 0, active, false)
        #define PROFILE_ZONE_ALLOC_COLOR_OPT(name, color, active) \
            static constexpr struct ___tracy_source_location_data CONCAT(__tracy_source_location,__LINE__) = { name, __func__,  __FILE__, (uint32_t)__LINE__, color }; \
            Tracy::CpuProfilerScope CONCAT(__cpu_profiler,__LINE__)(&CONCAT(__tracy_source_location,__LINE__), 0, active, true)

        #define PROFILE_ZONE(name) PROFILE_ZONE_OPT(name, true)
        #define PROFILE_ZONE_ALLOC(name) PROFILE_ZONE_ALLOC_OPT(name, true)
        #define PROFILE_ZONE_COLOR(name, color) PROFILE_ZONE_COLOR_OPT(name, color, true)
        #define PROFILE_ZONE_ALLOC_COLOR(name, color) PROFILE_ZONE_ALLOC_COLOR_OPT(name, color, true)
    #endif // else: TRACY_HAS_CALLBACK
#else
    #define PROFILE_ZONE_OPT(name, active)
    #define PROFILE_ZONE_ALLOC_OPT(name, active)
    #define PROFILE_ZONE_COLOR_OPT(name, color, active)
    #define PROFILE_ZONE_ALLOC_COLOR_OPT(name, color, active)

    #define PROFILE_ZONE(name)
    #define PROFILE_ZONE_ALLOC(name)
    #define PROFILE_ZONE_COLOR(name, color)
    #define PROFILE_ZONE_ALLOC_COLOR(name, color)

    #define TracyCRealloc(oldPtr, ptr, size)
#endif  // TRACY_ENABLE


//----------------------------------------------------------------------------------------------------------------------
// External/tlsf/tlsf.h

#ifndef INCLUDED_tlsf
#define INCLUDED_tlsf

/*
** Two Level Segregated Fit memory allocator, version 3.1.
** Written by Matthew Conte
**	http://tlsf.baisoku.org
**
** Based on the original documentation by Miguel Masmano:
**	http://www.gii.upv.es/tlsf/main/docs
**
** This implementation was written to the specification
** of the document, therefore no GPL restrictions apply.
** 
** Copyright (c) 2006-2016, Matthew Conte
** All rights reserved.
** 
** Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are met:
**     * Redistributions of source code must retain the above copyright
**       notice, this list of conditions and the following disclaimer.
**     * Redistributions in binary form must reproduce the above copyright
**       notice, this list of conditions and the following disclaimer in the
**       documentation and/or other materials provided with the distribution.
**     * Neither the name of the copyright holder nor the
**       names of its contributors may be used to endorse or promote products
**       derived from this software without specific prior written permission.
** 
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
** ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
** WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
** DISCLAIMED. IN NO EVENT SHALL MATTHEW CONTE BE LIABLE FOR ANY
** DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
** (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
** LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
** ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
** SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <stddef.h>

#if defined(__cplusplus)
extern "C" {
#endif

/* tlsf_t: a TLSF structure. Can contain 1 to N pools. */
/* pool_t: a block of memory that TLSF can manage. */
typedef void* tlsf_t;
typedef void* pool_t;

/* Create/destroy a memory pool. */
tlsf_t tlsf_create(void* mem);
tlsf_t tlsf_create_with_pool(void* mem, size_t bytes);
void tlsf_destroy(tlsf_t tlsf);
pool_t tlsf_get_pool(tlsf_t tlsf);

/* Add/remove memory pools. */
pool_t tlsf_add_pool(tlsf_t tlsf, void* mem, size_t bytes);
void tlsf_remove_pool(tlsf_t tlsf, pool_t pool);

/* malloc/memalign/realloc/free replacements. */
void* tlsf_malloc(tlsf_t tlsf, size_t bytes);
void* tlsf_memalign(tlsf_t tlsf, size_t align, size_t bytes);
void* tlsf_realloc(tlsf_t tlsf, void* ptr, size_t size);
void tlsf_free(tlsf_t tlsf, void* ptr);

/* Returns internal block size, not original request size */
size_t tlsf_block_size(void* ptr);

/* Overheads/limits of internal structures. */
size_t tlsf_size(void);
size_t tlsf_align_size(void);
size_t tlsf_block_size_min(void);
size_t tlsf_block_size_max(void);
size_t tlsf_pool_overhead(void);
size_t tlsf_alloc_overhead(void);

/* Debugging. */
typedef void (*tlsf_walker)(void* ptr, size_t size, int used, void* user);
void tlsf_walk_pool(pool_t pool, tlsf_walker walker, void* user);
/* Returns nonzero if any internal consistency check fails. */
int tlsf_check(tlsf_t tlsf);
int tlsf_check_pool(pool_t pool);

#if defined(__cplusplus)
};
#endif

#endif

PRAGMA_DIAGNOSTIC_PUSH()
PRAGMA_DIAGNOSTIC_IGNORED_MSVC(5054)
PRAGMA_DIAGNOSTIC_IGNORED_MSVC(4245)
PRAGMA_DIAGNOSTIC_IGNORED_MSVC(4127)
#define tlsf_assert ASSERT
//----------------------------------------------------------------------------------------------------------------------
// External/tlsf/tlsf.c

#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#if defined(__cplusplus)
#define tlsf_decl inline
#else
#define tlsf_decl static
#endif

/*
** Architecture-specific bit manipulation routines.
**
** TLSF achieves O(1) cost for malloc and free operations by limiting
** the search for a free block to a free list of guaranteed size
** adequate to fulfill the request, combined with efficient free list
** queries using bitmasks and architecture-specific bit-manipulation
** routines.
**
** Most modern processors provide instructions to count leading zeroes
** in a word, find the lowest and highest set bit, etc. These
** specific implementations will be used when available, falling back
** to a reasonably efficient generic implementation.
**
** NOTE: TLSF spec relies on ffs/fls returning value 0..31.
** ffs/fls return 1-32 by default, returning 0 for error.
*/

/*
** Detect whether or not we are building for a 32- or 64-bit (LP/LLP)
** architecture. There is no reliable portable method at compile-time.
*/
#if defined (__alpha__) || defined (__ia64__) || defined (__x86_64__) \
	|| defined (_WIN64) || defined (__LP64__) || defined (__LLP64__)
#define TLSF_64BIT
#endif

/*
** gcc 3.4 and above have builtin support, specialized for architecture.
** Some compilers masquerade as gcc; patchlevel test filters them out.
*/
#if defined (__GNUC__) && (__GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4)) \
	&& defined (__GNUC_PATCHLEVEL__)

#if defined (__SNC__)
/* SNC for Playstation 3. */

tlsf_decl int tlsf_ffs(unsigned int word)
{
	const unsigned int reverse = word & (~word + 1);
	const int bit = 32 - __builtin_clz(reverse);
	return bit - 1;
}

#else

tlsf_decl int tlsf_ffs(unsigned int word)
{
	return __builtin_ffs(word) - 1;
}

#endif

tlsf_decl int tlsf_fls(unsigned int word)
{
	const int bit = word ? 32 - __builtin_clz(word) : 0;
	return bit - 1;
}

#elif defined (_MSC_VER) && (_MSC_VER >= 1400) && (defined (_M_IX86) || defined (_M_X64))
/* Microsoft Visual C++ support on x86/X64 architectures. */

#include <intrin.h>

#pragma intrinsic(_BitScanReverse)
#pragma intrinsic(_BitScanForward)

tlsf_decl int tlsf_fls(unsigned int word)
{
	unsigned long index;
	return _BitScanReverse(&index, word) ? index : -1;
}

tlsf_decl int tlsf_ffs(unsigned int word)
{
	unsigned long index;
	return _BitScanForward(&index, word) ? index : -1;
}

#elif defined (_MSC_VER) && defined (_M_PPC)
/* Microsoft Visual C++ support on PowerPC architectures. */

#include <ppcintrinsics.h>

tlsf_decl int tlsf_fls(unsigned int word)
{
	const int bit = 32 - _CountLeadingZeros(word);
	return bit - 1;
}

tlsf_decl int tlsf_ffs(unsigned int word)
{
	const unsigned int reverse = word & (~word + 1);
	const int bit = 32 - _CountLeadingZeros(reverse);
	return bit - 1;
}

#elif defined (__ARMCC_VERSION)
/* RealView Compilation Tools for ARM */

tlsf_decl int tlsf_ffs(unsigned int word)
{
	const unsigned int reverse = word & (~word + 1);
	const int bit = 32 - __clz(reverse);
	return bit - 1;
}

tlsf_decl int tlsf_fls(unsigned int word)
{
	const int bit = word ? 32 - __clz(word) : 0;
	return bit - 1;
}

#elif defined (__ghs__)
/* Green Hills support for PowerPC */

#include <ppc_ghs.h>

tlsf_decl int tlsf_ffs(unsigned int word)
{
	const unsigned int reverse = word & (~word + 1);
	const int bit = 32 - __CLZ32(reverse);
	return bit - 1;
}

tlsf_decl int tlsf_fls(unsigned int word)
{
	const int bit = word ? 32 - __CLZ32(word) : 0;
	return bit - 1;
}

#else
/* Fall back to generic implementation. */

tlsf_decl int tlsf_fls_generic(unsigned int word)
{
	int bit = 32;

	if (!word) bit -= 1;
	if (!(word & 0xffff0000)) { word <<= 16; bit -= 16; }
	if (!(word & 0xff000000)) { word <<= 8; bit -= 8; }
	if (!(word & 0xf0000000)) { word <<= 4; bit -= 4; }
	if (!(word & 0xc0000000)) { word <<= 2; bit -= 2; }
	if (!(word & 0x80000000)) { word <<= 1; bit -= 1; }

	return bit;
}

/* Implement ffs in terms of fls. */
tlsf_decl int tlsf_ffs(unsigned int word)
{
	return tlsf_fls_generic(word & (~word + 1)) - 1;
}

tlsf_decl int tlsf_fls(unsigned int word)
{
	return tlsf_fls_generic(word) - 1;
}

#endif

/* Possibly 64-bit version of tlsf_fls. */
#if defined (TLSF_64BIT)
tlsf_decl int tlsf_fls_sizet(size_t size)
{
	int high = (int)(size >> 32);
	int bits = 0;
	if (high)
	{
		bits = 32 + tlsf_fls(high);
	}
	else
	{
		bits = tlsf_fls((int)size & 0xffffffff);

	}
	return bits;
}
#else
#define tlsf_fls_sizet tlsf_fls
#endif

#undef tlsf_decl

/*
** Constants.
*/

/* Public constants: may be modified. */
enum tlsf_public
{
	/* log2 of number of linear subdivisions of block sizes. Larger
	** values require more memory in the control structure. Values of
	** 4 or 5 are typical.
	*/
	SL_INDEX_COUNT_LOG2 = 5,
};

/* Private constants: do not modify. */
enum tlsf_private
{
#if defined (TLSF_64BIT)
	/* All allocation sizes and addresses are aligned to 8 bytes. */
	ALIGN_SIZE_LOG2 = 3,
#else
	/* All allocation sizes and addresses are aligned to 4 bytes. */
	ALIGN_SIZE_LOG2 = 2,
#endif
	ALIGN_SIZE = (1 << ALIGN_SIZE_LOG2),

	/*
	** We support allocations of sizes up to (1 << FL_INDEX_MAX) bits.
	** However, because we linearly subdivide the second-level lists, and
	** our minimum size granularity is 4 bytes, it doesn't make sense to
	** create first-level lists for sizes smaller than SL_INDEX_COUNT * 4,
	** or (1 << (SL_INDEX_COUNT_LOG2 + 2)) bytes, as there we will be
	** trying to split size ranges into more slots than we have available.
	** Instead, we calculate the minimum threshold size, and place all
	** blocks below that size into the 0th first-level list.
	*/

#if defined (TLSF_64BIT)
	/*
	** TODO: We can increase this to support larger sizes, at the expense
	** of more overhead in the TLSF structure.
	*/
	FL_INDEX_MAX = 32,
#else
	FL_INDEX_MAX = 30,
#endif
	SL_INDEX_COUNT = (1 << SL_INDEX_COUNT_LOG2),
	FL_INDEX_SHIFT = (SL_INDEX_COUNT_LOG2 + ALIGN_SIZE_LOG2),
	FL_INDEX_COUNT = (FL_INDEX_MAX - FL_INDEX_SHIFT + 1),

	SMALL_BLOCK_SIZE = (1 << FL_INDEX_SHIFT),
};

/*
** Cast and min/max macros.
*/

#define tlsf_cast(t, exp)	((t) (exp))
#define tlsf_min(a, b)		((a) < (b) ? (a) : (b))
#define tlsf_max(a, b)		((a) > (b) ? (a) : (b))

/*
** Set assert macro, if it has not been provided by the user.
*/
#if !defined (tlsf_assert)
#define tlsf_assert assert
#endif

/*
** Static assertion mechanism.
*/

#define _tlsf_glue2(x, y) x ## y
#define _tlsf_glue(x, y) _tlsf_glue2(x, y)
#define tlsf_static_assert(exp) \
	typedef char _tlsf_glue(static_assert, __LINE__) [(exp) ? 1 : -1]

/* This code has been tested on 32- and 64-bit (LP/LLP) architectures. */
tlsf_static_assert(sizeof(int) * CHAR_BIT == 32);
tlsf_static_assert(sizeof(size_t) * CHAR_BIT >= 32);
tlsf_static_assert(sizeof(size_t) * CHAR_BIT <= 64);

/* SL_INDEX_COUNT must be <= number of bits in sl_bitmap's storage type. */
tlsf_static_assert(sizeof(unsigned int) * CHAR_BIT >= SL_INDEX_COUNT);

/* Ensure we've properly tuned our sizes. */
tlsf_static_assert(ALIGN_SIZE == SMALL_BLOCK_SIZE / SL_INDEX_COUNT);

/*
** Data structures and associated constants.
*/

/*
** Block header structure.
**
** There are several implementation subtleties involved:
** - The prev_phys_block field is only valid if the previous block is free.
** - The prev_phys_block field is actually stored at the end of the
**   previous block. It appears at the beginning of this structure only to
**   simplify the implementation.
** - The next_free / prev_free fields are only valid if the block is free.
*/
typedef struct block_header_t
{
	/* Points to the previous physical block. */
	struct block_header_t* prev_phys_block;

	/* The size of this block, excluding the block header. */
	size_t size;

	/* Next and previous free blocks. */
	struct block_header_t* next_free;
	struct block_header_t* prev_free;
} block_header_t;

/*
** Since block sizes are always at least a multiple of 4, the two least
** significant bits of the size field are used to store the block status:
** - bit 0: whether block is busy or free
** - bit 1: whether previous block is busy or free
*/
static const size_t block_header_free_bit = 1 << 0;
static const size_t block_header_prev_free_bit = 1 << 1;

/*
** The size of the block header exposed to used blocks is the size field.
** The prev_phys_block field is stored *inside* the previous free block.
*/
static const size_t block_header_overhead = sizeof(size_t);

/* User data starts directly after the size field in a used block. */
static const size_t block_start_offset =
	offsetof(block_header_t, size) + sizeof(size_t);

/*
** A free block must be large enough to store its header minus the size of
** the prev_phys_block field, and no larger than the number of addressable
** bits for FL_INDEX.
*/
static const size_t block_size_min = 
	sizeof(block_header_t) - sizeof(block_header_t*);
static const size_t block_size_max = tlsf_cast(size_t, 1) << FL_INDEX_MAX;


/* The TLSF control structure. */
typedef struct control_t
{
	/* Empty lists point at this block to indicate they are free. */
	block_header_t block_null;

	/* Bitmaps for free lists. */
	unsigned int fl_bitmap;
	unsigned int sl_bitmap[FL_INDEX_COUNT];

	/* Head of free lists. */
	block_header_t* blocks[FL_INDEX_COUNT][SL_INDEX_COUNT];
} control_t;

/* A type used for casting when doing pointer arithmetic. */
typedef ptrdiff_t tlsfptr_t;

/*
** block_header_t member functions.
*/

static size_t block_size(const block_header_t* block)
{
	return block->size & ~(block_header_free_bit | block_header_prev_free_bit);
}

static void block_set_size(block_header_t* block, size_t size)
{
	const size_t oldsize = block->size;
	block->size = size | (oldsize & (block_header_free_bit | block_header_prev_free_bit));
}

static int block_is_last(const block_header_t* block)
{
	return block_size(block) == 0;
}

static int block_is_free(const block_header_t* block)
{
	return tlsf_cast(int, block->size & block_header_free_bit);
}

static void block_set_free(block_header_t* block)
{
	block->size |= block_header_free_bit;
}

static void block_set_used(block_header_t* block)
{
	block->size &= ~block_header_free_bit;
}

static int block_is_prev_free(const block_header_t* block)
{
	return tlsf_cast(int, block->size & block_header_prev_free_bit);
}

static void block_set_prev_free(block_header_t* block)
{
	block->size |= block_header_prev_free_bit;
}

static void block_set_prev_used(block_header_t* block)
{
	block->size &= ~block_header_prev_free_bit;
}

static block_header_t* block_from_ptr(const void* ptr)
{
	return tlsf_cast(block_header_t*,
		tlsf_cast(unsigned char*, ptr) - block_start_offset);
}

static void* block_to_ptr(const block_header_t* block)
{
	return tlsf_cast(void*,
		tlsf_cast(unsigned char*, block) + block_start_offset);
}

/* Return location of next block after block of given size. */
static block_header_t* offset_to_block(const void* ptr, size_t size)
{
	return tlsf_cast(block_header_t*, tlsf_cast(tlsfptr_t, ptr) + size);
}

/* Return location of previous block. */
static block_header_t* block_prev(const block_header_t* block)
{
	tlsf_assert(block_is_prev_free(block) && "previous block must be free");
	return block->prev_phys_block;
}

/* Return location of next existing block. */
static block_header_t* block_next(const block_header_t* block)
{
	block_header_t* next = offset_to_block(block_to_ptr(block),
		block_size(block) - block_header_overhead);
	tlsf_assert(!block_is_last(block));
	return next;
}

/* Link a new block with its physical neighbor, return the neighbor. */
static block_header_t* block_link_next(block_header_t* block)
{
	block_header_t* next = block_next(block);
	next->prev_phys_block = block;
	return next;
}

static void block_mark_as_free(block_header_t* block)
{
	/* Link the block to the next block, first. */
	block_header_t* next = block_link_next(block);
	block_set_prev_free(next);
	block_set_free(block);
}

static void block_mark_as_used(block_header_t* block)
{
	block_header_t* next = block_next(block);
	block_set_prev_used(next);
	block_set_used(block);
}

static size_t align_up(size_t x, size_t align)
{
	tlsf_assert(0 == (align & (align - 1)) && "must align to a power of two");
	return (x + (align - 1)) & ~(align - 1);
}

static size_t align_down(size_t x, size_t align)
{
	tlsf_assert(0 == (align & (align - 1)) && "must align to a power of two");
	return x - (x & (align - 1));
}

static void* align_ptr(const void* ptr, size_t align)
{
	const tlsfptr_t aligned =
		(tlsf_cast(tlsfptr_t, ptr) + (align - 1)) & ~(align - 1);
	tlsf_assert(0 == (align & (align - 1)) && "must align to a power of two");
	return tlsf_cast(void*, aligned);
}

/*
** Adjust an allocation size to be aligned to word size, and no smaller
** than internal minimum.
*/
static size_t adjust_request_size(size_t size, size_t align)
{
	size_t adjust = 0;
	if (size)
	{
		const size_t aligned = align_up(size, align);

		/* aligned sized must not exceed block_size_max or we'll go out of bounds on sl_bitmap */
		if (aligned < block_size_max) 
		{
			adjust = tlsf_max(aligned, block_size_min);
		}
	}
	return adjust;
}

/*
** TLSF utility functions. In most cases, these are direct translations of
** the documentation found in the white paper.
*/

static void mapping_insert(size_t size, int* fli, int* sli)
{
	int fl, sl;
	if (size < SMALL_BLOCK_SIZE)
	{
		/* Store small blocks in first list. */
		fl = 0;
		sl = tlsf_cast(int, size) / (SMALL_BLOCK_SIZE / SL_INDEX_COUNT);
	}
	else
	{
		fl = tlsf_fls_sizet(size);
		sl = tlsf_cast(int, size >> (fl - SL_INDEX_COUNT_LOG2)) ^ (1 << SL_INDEX_COUNT_LOG2);
		fl -= (FL_INDEX_SHIFT - 1);
	}
	*fli = fl;
	*sli = sl;
}

/* This version rounds up to the next block size (for allocations) */
static void mapping_search(size_t size, int* fli, int* sli)
{
	if (size >= SMALL_BLOCK_SIZE)
	{
		const size_t round = (1 << (tlsf_fls_sizet(size) - SL_INDEX_COUNT_LOG2)) - 1;
		size += round;
	}
	mapping_insert(size, fli, sli);
}

static block_header_t* search_suitable_block(control_t* control, int* fli, int* sli)
{
	int fl = *fli;
	int sl = *sli;

	/*
	** First, search for a block in the list associated with the given
	** fl/sl index.
	*/
	unsigned int sl_map = control->sl_bitmap[fl] & (~0U << sl);
	if (!sl_map)
	{
		/* No block exists. Search in the next largest first-level list. */
		const unsigned int fl_map = control->fl_bitmap & (~0U << (fl + 1));
		if (!fl_map)
		{
			/* No free blocks available, memory has been exhausted. */
			return 0;
		}

		fl = tlsf_ffs(fl_map);
		*fli = fl;
		sl_map = control->sl_bitmap[fl];
	}
	tlsf_assert(sl_map && "internal error - second level bitmap is null");
	sl = tlsf_ffs(sl_map);
	*sli = sl;

	/* Return the first block in the free list. */
	return control->blocks[fl][sl];
}

/* Remove a free block from the free list.*/
static void remove_free_block(control_t* control, block_header_t* block, int fl, int sl)
{
	block_header_t* prev = block->prev_free;
	block_header_t* next = block->next_free;
	tlsf_assert(prev && "prev_free field can not be null");
	tlsf_assert(next && "next_free field can not be null");
	next->prev_free = prev;
	prev->next_free = next;

	/* If this block is the head of the free list, set new head. */
	if (control->blocks[fl][sl] == block)
	{
		control->blocks[fl][sl] = next;

		/* If the new head is null, clear the bitmap. */
		if (next == &control->block_null)
		{
			control->sl_bitmap[fl] &= ~(1U << sl);

			/* If the second bitmap is now empty, clear the fl bitmap. */
			if (!control->sl_bitmap[fl])
			{
				control->fl_bitmap &= ~(1U << fl);
			}
		}
	}
}

/* Insert a free block into the free block list. */
static void insert_free_block(control_t* control, block_header_t* block, int fl, int sl)
{
	block_header_t* current = control->blocks[fl][sl];
	tlsf_assert(current && "free list cannot have a null entry");
	tlsf_assert(block && "cannot insert a null entry into the free list");
	block->next_free = current;
	block->prev_free = &control->block_null;
	current->prev_free = block;

	tlsf_assert(block_to_ptr(block) == align_ptr(block_to_ptr(block), ALIGN_SIZE)
		&& "block not aligned properly");
	/*
	** Insert the new block at the head of the list, and mark the first-
	** and second-level bitmaps appropriately.
	*/
	control->blocks[fl][sl] = block;
	control->fl_bitmap |= (1U << fl);
	control->sl_bitmap[fl] |= (1U << sl);
}

/* Remove a given block from the free list. */
static void block_remove(control_t* control, block_header_t* block)
{
	int fl, sl;
	mapping_insert(block_size(block), &fl, &sl);
	remove_free_block(control, block, fl, sl);
}

/* Insert a given block into the free list. */
static void block_insert(control_t* control, block_header_t* block)
{
	int fl, sl;
	mapping_insert(block_size(block), &fl, &sl);
	insert_free_block(control, block, fl, sl);
}

static int block_can_split(block_header_t* block, size_t size)
{
	return block_size(block) >= sizeof(block_header_t) + size;
}

/* Split a block into two, the second of which is free. */
static block_header_t* block_split(block_header_t* block, size_t size)
{
	/* Calculate the amount of space left in the remaining block. */
	block_header_t* remaining =
		offset_to_block(block_to_ptr(block), size - block_header_overhead);

	const size_t remain_size = block_size(block) - (size + block_header_overhead);

	tlsf_assert(block_to_ptr(remaining) == align_ptr(block_to_ptr(remaining), ALIGN_SIZE)
		&& "remaining block not aligned properly");

	tlsf_assert(block_size(block) == remain_size + size + block_header_overhead);
	block_set_size(remaining, remain_size);
	tlsf_assert(block_size(remaining) >= block_size_min && "block split with invalid size");

	block_set_size(block, size);
	block_mark_as_free(remaining);

	return remaining;
}

/* Absorb a free block's storage into an adjacent previous free block. */
static block_header_t* block_absorb(block_header_t* prev, block_header_t* block)
{
	tlsf_assert(!block_is_last(prev) && "previous block can't be last");
	/* Note: Leaves flags untouched. */
	prev->size += block_size(block) + block_header_overhead;
	block_link_next(prev);
	return prev;
}

/* Merge a just-freed block with an adjacent previous free block. */
static block_header_t* block_merge_prev(control_t* control, block_header_t* block)
{
	if (block_is_prev_free(block))
	{
		block_header_t* prev = block_prev(block);
		tlsf_assert(prev && "prev physical block can't be null");
		tlsf_assert(block_is_free(prev) && "prev block is not free though marked as such");
		block_remove(control, prev);
		block = block_absorb(prev, block);
	}

	return block;
}

/* Merge a just-freed block with an adjacent free block. */
static block_header_t* block_merge_next(control_t* control, block_header_t* block)
{
	block_header_t* next = block_next(block);
	tlsf_assert(next && "next physical block can't be null");

	if (block_is_free(next))
	{
		tlsf_assert(!block_is_last(block) && "previous block can't be last");
		block_remove(control, next);
		block = block_absorb(block, next);
	}

	return block;
}

/* Trim any trailing block space off the end of a block, return to pool. */
static void block_trim_free(control_t* control, block_header_t* block, size_t size)
{
	tlsf_assert(block_is_free(block) && "block must be free");
	if (block_can_split(block, size))
	{
		block_header_t* remaining_block = block_split(block, size);
		block_link_next(block);
		block_set_prev_free(remaining_block);
		block_insert(control, remaining_block);
	}
}

/* Trim any trailing block space off the end of a used block, return to pool. */
static void block_trim_used(control_t* control, block_header_t* block, size_t size)
{
	tlsf_assert(!block_is_free(block) && "block must be used");
	if (block_can_split(block, size))
	{
		/* If the next block is free, we must coalesce. */
		block_header_t* remaining_block = block_split(block, size);
		block_set_prev_used(remaining_block);

		remaining_block = block_merge_next(control, remaining_block);
		block_insert(control, remaining_block);
	}
}

static block_header_t* block_trim_free_leading(control_t* control, block_header_t* block, size_t size)
{
	block_header_t* remaining_block = block;
	if (block_can_split(block, size))
	{
		/* We want the 2nd block. */
		remaining_block = block_split(block, size - block_header_overhead);
		block_set_prev_free(remaining_block);

		block_link_next(block);
		block_insert(control, block);
	}

	return remaining_block;
}

static block_header_t* block_locate_free(control_t* control, size_t size)
{
	int fl = 0, sl = 0;
	block_header_t* block = 0;

	if (size)
	{
		mapping_search(size, &fl, &sl);
		
		/*
		** mapping_search can futz with the size, so for excessively large sizes it can sometimes wind up 
		** with indices that are off the end of the block array.
		** So, we protect against that here, since this is the only callsite of mapping_search.
		** Note that we don't need to check sl, since it comes from a modulo operation that guarantees it's always in range.
		*/
		if (fl < FL_INDEX_COUNT)
		{
			block = search_suitable_block(control, &fl, &sl);
		}
	}

	if (block)
	{
		tlsf_assert(block_size(block) >= size);
		remove_free_block(control, block, fl, sl);
	}

	return block;
}

static void* block_prepare_used(control_t* control, block_header_t* block, size_t size)
{
	void* p = 0;
	if (block)
	{
		tlsf_assert(size && "size must be non-zero");
		block_trim_free(control, block, size);
		block_mark_as_used(block);
		p = block_to_ptr(block);
	}
	return p;
}

/* Clear structure and point all empty lists at the null block. */
static void control_construct(control_t* control)
{
	int i, j;

	control->block_null.next_free = &control->block_null;
	control->block_null.prev_free = &control->block_null;

	control->fl_bitmap = 0;
	for (i = 0; i < FL_INDEX_COUNT; ++i)
	{
		control->sl_bitmap[i] = 0;
		for (j = 0; j < SL_INDEX_COUNT; ++j)
		{
			control->blocks[i][j] = &control->block_null;
		}
	}
}

/*
** Debugging utilities.
*/

typedef struct integrity_t
{
	int prev_status;
	int status;
} integrity_t;

#define tlsf_insist(x) { tlsf_assert(x); if (!(x)) { status--; } }

static void integrity_walker(void* ptr, size_t size, int used, void* user)
{
	block_header_t* block = block_from_ptr(ptr);
	integrity_t* integ = tlsf_cast(integrity_t*, user);
	const int this_prev_status = block_is_prev_free(block) ? 1 : 0;
	const int this_status = block_is_free(block) ? 1 : 0;
	const size_t this_block_size = block_size(block);

	int status = 0;
	(void)used;
	tlsf_insist(integ->prev_status == this_prev_status && "prev status incorrect");
	tlsf_insist(size == this_block_size && "block size incorrect");

	integ->prev_status = this_status;
	integ->status += status;
}

int tlsf_check(tlsf_t tlsf)
{
	int i, j;

	control_t* control = tlsf_cast(control_t*, tlsf);
	int status = 0;

	/* Check that the free lists and bitmaps are accurate. */
	for (i = 0; i < FL_INDEX_COUNT; ++i)
	{
		for (j = 0; j < SL_INDEX_COUNT; ++j)
		{
			const int fl_map = control->fl_bitmap & (1U << i);
			const int sl_list = control->sl_bitmap[i];
			const int sl_map = sl_list & (1U << j);
			const block_header_t* block = control->blocks[i][j];

			/* Check that first- and second-level lists agree. */
			if (!fl_map)
			{
				tlsf_insist(!sl_map && "second-level map must be null");
			}

			if (!sl_map)
			{
				tlsf_insist(block == &control->block_null && "block list must be null");
				continue;
			}

			/* Check that there is at least one free block. */
			tlsf_insist(sl_list && "no free blocks in second-level map");
			tlsf_insist(block != &control->block_null && "block should not be null");

			while (block != &control->block_null)
			{
				int fli, sli;
				tlsf_insist(block_is_free(block) && "block should be free");
				tlsf_insist(!block_is_prev_free(block) && "blocks should have coalesced");
				tlsf_insist(!block_is_free(block_next(block)) && "blocks should have coalesced");
				tlsf_insist(block_is_prev_free(block_next(block)) && "block should be free");
				tlsf_insist(block_size(block) >= block_size_min && "block not minimum size");

				mapping_insert(block_size(block), &fli, &sli);
				tlsf_insist(fli == i && sli == j && "block size indexed in wrong list");
				block = block->next_free;
			}
		}
	}

	return status;
}

#undef tlsf_insist

static void default_walker(void* ptr, size_t size, int used, void* user)
{
	(void)user;
	printf("\t%p %s size: %x (%p)\n", ptr, used ? "used" : "free", (unsigned int)size, block_from_ptr(ptr));
}

void tlsf_walk_pool(pool_t pool, tlsf_walker walker, void* user)
{
	tlsf_walker pool_walker = walker ? walker : default_walker;
	block_header_t* block =
		offset_to_block(pool, -(int)block_header_overhead);

	while (block && !block_is_last(block))
	{
		pool_walker(
			block_to_ptr(block),
			block_size(block),
			!block_is_free(block),
			user);
		block = block_next(block);
	}
}

size_t tlsf_block_size(void* ptr)
{
	size_t size = 0;
	if (ptr)
	{
		const block_header_t* block = block_from_ptr(ptr);
		size = block_size(block);
	}
	return size;
}

int tlsf_check_pool(pool_t pool)
{
	/* Check that the blocks are physically correct. */
	integrity_t integ = { 0, 0 };
	tlsf_walk_pool(pool, integrity_walker, &integ);

	return integ.status;
}

/*
** Size of the TLSF structures in a given memory block passed to
** tlsf_create, equal to the size of a control_t
*/
size_t tlsf_size(void)
{
	return sizeof(control_t);
}

size_t tlsf_align_size(void)
{
	return ALIGN_SIZE;
}

size_t tlsf_block_size_min(void)
{
	return block_size_min;
}

size_t tlsf_block_size_max(void)
{
	return block_size_max;
}

/*
** Overhead of the TLSF structures in a given memory block passed to
** tlsf_add_pool, equal to the overhead of a free block and the
** sentinel block.
*/
size_t tlsf_pool_overhead(void)
{
	return 2 * block_header_overhead;
}

size_t tlsf_alloc_overhead(void)
{
	return block_header_overhead;
}

pool_t tlsf_add_pool(tlsf_t tlsf, void* mem, size_t bytes)
{
	block_header_t* block;
	block_header_t* next;

	const size_t pool_overhead = tlsf_pool_overhead();
	const size_t pool_bytes = align_down(bytes - pool_overhead, ALIGN_SIZE);

	if (((ptrdiff_t)mem % ALIGN_SIZE) != 0)
	{
		printf("tlsf_add_pool: Memory must be aligned by %u bytes.\n",
			(unsigned int)ALIGN_SIZE);
		return 0;
	}

	if (pool_bytes < block_size_min || pool_bytes > block_size_max)
	{
#if defined (TLSF_64BIT)
		printf("tlsf_add_pool: Memory size must be between 0x%x and 0x%x00 bytes.\n", 
			(unsigned int)(pool_overhead + block_size_min),
			(unsigned int)((pool_overhead + block_size_max) / 256));
#else
		printf("tlsf_add_pool: Memory size must be between %u and %u bytes.\n", 
			(unsigned int)(pool_overhead + block_size_min),
			(unsigned int)(pool_overhead + block_size_max));
#endif
		return 0;
	}

	/*
	** Create the main free block. Offset the start of the block slightly
	** so that the prev_phys_block field falls outside of the pool -
	** it will never be used.
	*/
	block = offset_to_block(mem, -(tlsfptr_t)block_header_overhead);
	block_set_size(block, pool_bytes);
	block_set_free(block);
	block_set_prev_used(block);
	block_insert(tlsf_cast(control_t*, tlsf), block);

	/* Split the block to create a zero-size sentinel block. */
	next = block_link_next(block);
	block_set_size(next, 0);
	block_set_used(next);
	block_set_prev_free(next);

	return mem;
}

void tlsf_remove_pool(tlsf_t tlsf, pool_t pool)
{
	control_t* control = tlsf_cast(control_t*, tlsf);
	block_header_t* block = offset_to_block(pool, -(int)block_header_overhead);

	int fl = 0, sl = 0;

	tlsf_assert(block_is_free(block) && "block should be free");
	tlsf_assert(!block_is_free(block_next(block)) && "next block should not be free");
	tlsf_assert(block_size(block_next(block)) == 0 && "next block size should be zero");

	mapping_insert(block_size(block), &fl, &sl);
	remove_free_block(control, block, fl, sl);
}

/*
** TLSF main interface.
*/

#if _DEBUG
int test_ffs_fls()
{
	/* Verify ffs/fls work properly. */
	int rv = 0;
	rv += (tlsf_ffs(0) == -1) ? 0 : 0x1;
	rv += (tlsf_fls(0) == -1) ? 0 : 0x2;
	rv += (tlsf_ffs(1) == 0) ? 0 : 0x4;
	rv += (tlsf_fls(1) == 0) ? 0 : 0x8;
	rv += (tlsf_ffs(0x80000000) == 31) ? 0 : 0x10;
	rv += (tlsf_ffs(0x80008000) == 15) ? 0 : 0x20;
	rv += (tlsf_fls(0x80000008) == 31) ? 0 : 0x40;
	rv += (tlsf_fls(0x7FFFFFFF) == 30) ? 0 : 0x80;

#if defined (TLSF_64BIT)
	rv += (tlsf_fls_sizet(0x80000000) == 31) ? 0 : 0x100;
	rv += (tlsf_fls_sizet(0x100000000) == 32) ? 0 : 0x200;
	rv += (tlsf_fls_sizet(0xffffffffffffffff) == 63) ? 0 : 0x400;
#endif

	if (rv)
	{
		printf("test_ffs_fls: %x ffs/fls tests failed.\n", rv);
	}
	return rv;
}
#endif

tlsf_t tlsf_create(void* mem)
{
#if _DEBUG
	if (test_ffs_fls())
	{
		return 0;
	}
#endif

	if (((tlsfptr_t)mem % ALIGN_SIZE) != 0)
	{
		printf("tlsf_create: Memory must be aligned to %u bytes.\n",
			(unsigned int)ALIGN_SIZE);
		return 0;
	}

	control_construct(tlsf_cast(control_t*, mem));

	return tlsf_cast(tlsf_t, mem);
}

tlsf_t tlsf_create_with_pool(void* mem, size_t bytes)
{
	tlsf_t tlsf = tlsf_create(mem);
	tlsf_add_pool(tlsf, (char*)mem + tlsf_size(), bytes - tlsf_size());
	return tlsf;
}

void tlsf_destroy(tlsf_t tlsf)
{
	/* Nothing to do. */
	(void)tlsf;
}

pool_t tlsf_get_pool(tlsf_t tlsf)
{
	return tlsf_cast(pool_t, (char*)tlsf + tlsf_size());
}

void* tlsf_malloc(tlsf_t tlsf, size_t size)
{
	control_t* control = tlsf_cast(control_t*, tlsf);
	const size_t adjust = adjust_request_size(size, ALIGN_SIZE);
	block_header_t* block = block_locate_free(control, adjust);
	return block_prepare_used(control, block, adjust);
}

void* tlsf_memalign(tlsf_t tlsf, size_t align, size_t size)
{
	control_t* control = tlsf_cast(control_t*, tlsf);
	const size_t adjust = adjust_request_size(size, ALIGN_SIZE);

	/*
	** We must allocate an additional minimum block size bytes so that if
	** our free block will leave an alignment gap which is smaller, we can
	** trim a leading free block and release it back to the pool. We must
	** do this because the previous physical block is in use, therefore
	** the prev_phys_block field is not valid, and we can't simply adjust
	** the size of that block.
	*/
	const size_t gap_minimum = sizeof(block_header_t);
	const size_t size_with_gap = adjust_request_size(adjust + align + gap_minimum, align);

	/*
	** If alignment is less than or equals base alignment, we're done.
	** If we requested 0 bytes, return null, as tlsf_malloc(0) does.
	*/
	const size_t aligned_size = (adjust && align > ALIGN_SIZE) ? size_with_gap : adjust;

	block_header_t* block = block_locate_free(control, aligned_size);

	/* This can't be a static assert. */
	tlsf_assert(sizeof(block_header_t) == block_size_min + block_header_overhead);

	if (block)
	{
		void* ptr = block_to_ptr(block);
		void* aligned = align_ptr(ptr, align);
		size_t gap = tlsf_cast(size_t,
			tlsf_cast(tlsfptr_t, aligned) - tlsf_cast(tlsfptr_t, ptr));

		/* If gap size is too small, offset to next aligned boundary. */
		if (gap && gap < gap_minimum)
		{
			const size_t gap_remain = gap_minimum - gap;
			const size_t offset = tlsf_max(gap_remain, align);
			const void* next_aligned = tlsf_cast(void*,
				tlsf_cast(tlsfptr_t, aligned) + offset);

			aligned = align_ptr(next_aligned, align);
			gap = tlsf_cast(size_t,
				tlsf_cast(tlsfptr_t, aligned) - tlsf_cast(tlsfptr_t, ptr));
		}

		if (gap)
		{
			tlsf_assert(gap >= gap_minimum && "gap size too small");
			block = block_trim_free_leading(control, block, gap);
		}
	}

	return block_prepare_used(control, block, adjust);
}

void tlsf_free(tlsf_t tlsf, void* ptr)
{
	/* Don't attempt to free a NULL pointer. */
	if (ptr)
	{
		control_t* control = tlsf_cast(control_t*, tlsf);
		block_header_t* block = block_from_ptr(ptr);
		tlsf_assert(!block_is_free(block) && "block already marked as free");
		block_mark_as_free(block);
		block = block_merge_prev(control, block);
		block = block_merge_next(control, block);
		block_insert(control, block);
	}
}

/*
** The TLSF block information provides us with enough information to
** provide a reasonably intelligent implementation of realloc, growing or
** shrinking the currently allocated block as required.
**
** This routine handles the somewhat esoteric edge cases of realloc:
** - a non-zero size with a null pointer will behave like malloc
** - a zero size with a non-null pointer will behave like free
** - a request that cannot be satisfied will leave the original buffer
**   untouched
** - an extended buffer size will leave the newly-allocated area with
**   contents undefined
*/
void* tlsf_realloc(tlsf_t tlsf, void* ptr, size_t size)
{
	control_t* control = tlsf_cast(control_t*, tlsf);
	void* p = 0;

	/* Zero-size requests are treated as free. */
	if (ptr && size == 0)
	{
		tlsf_free(tlsf, ptr);
	}
	/* Requests with NULL pointers are treated as malloc. */
	else if (!ptr)
	{
		p = tlsf_malloc(tlsf, size);
	}
	else
	{
		block_header_t* block = block_from_ptr(ptr);
		block_header_t* next = block_next(block);

		const size_t cursize = block_size(block);
		const size_t combined = cursize + block_size(next) + block_header_overhead;
		const size_t adjust = adjust_request_size(size, ALIGN_SIZE);

		tlsf_assert(!block_is_free(block) && "block already marked as free");

		/*
		** If the next block is used, or when combined with the current
		** block, does not offer enough space, we must reallocate and copy.
		*/
		if (adjust > cursize && (!block_is_free(next) || adjust > combined))
		{
			p = tlsf_malloc(tlsf, size);
			if (p)
			{
				const size_t minsize = tlsf_min(cursize, size);
				memcpy(p, ptr, minsize);
				tlsf_free(tlsf, ptr);
			}
		}
		else
		{
			/* Do we need to expand to the next block? */
			if (adjust > cursize)
			{
				block_merge_next(control, block);
				block_mark_as_used(block);
			}

			/* Trim the resulting block and return the original pointer. */
			block_trim_used(control, block, adjust);
			p = ptr;
		}
	}

	return p;
}

PRAGMA_DIAGNOSTIC_POP()


static constexpr size_t MEM_TEMP_MAX_BUFFER_SIZE = CONFIG_TEMP_ALLOC_MAX;
static constexpr uint32 MEM_TEMP_FRAME_PEAKS_COUNT = 4;
static constexpr uint32 MEM_TEMP_PAGE_SIZE = CONFIG_TEMP_ALLOC_PAGE_SIZE;
static constexpr uint32 MEM_TEMP_MAX_STACK_FRAMES = 8;

struct MemTempStack
{
    size_t baseOffset;
    size_t offset;
    void* lastAllocatedPtr;
    void* stacktrace[MEM_TEMP_MAX_STACK_FRAMES];
    Array<MemDebugPointer> debugPointers;
    MemTempAllocator::ID id;
    uint16 numStackframes;
};

struct alignas(CACHE_LINE_SIZE) MemTempContext
{
    SpinLockMutex inUseMtx;

    Array<MemTempStack> allocStack;
    uint32 generationIdx;   // Just a counter to make temp IDs unique
    uint32 resetCount;
    size_t framePeaks[MEM_TEMP_FRAME_PEAKS_COUNT];
    size_t curFramePeak;
    size_t peakBytes;
    size_t commitedBytes;
    size_t reservedBytes;
    uint8* buffer;
    size_t bufferSize;
    
    uint32 threadId;
    char threadName[32];

    bool init;      // is Buffer initialized ?
    bool used;      // Temp allocator is used since last reset ?
    bool debugMode; // Allocate from heap

    uint8 _paddingBottom[53];

    ~MemTempContext();
};

struct MemTempData
{
    Mutex            tempMtx;
    size_t           pageSize = OS::GetPageSize();
    Array<MemTempContext*> tempCtxs;
    Array<MemTempContext*> tempCtxsCopy;
    bool             captureTempStackTrace;

    MemTempData()  { tempMtx.Initialize(); ASSERT(MEM_TEMP_PAGE_SIZE % pageSize == 0); }
    ~MemTempData() { tempMtx.Release(); tempCtxs.Free(); }
};

static MemTempData gMemTemp;

NO_INLINE static MemTempContext& _GetMemTempContext() 
{ 
    static thread_local MemTempContext tempCtx;
    return tempCtx; 
}

void MemTempAllocator::EnableDebugMode(bool enable)
{
    ASSERT_MSG(_GetMemTempContext().allocStack.Count() == 0, "MemTemp must be at it's initial state");
    _GetMemTempContext().debugMode = enable;
}

void MemTempAllocator::EnableCallstackCapture(bool capture)
{
    gMemTemp.captureTempStackTrace = capture;
}

void MemTempAllocator::GetStats(MemAllocator* alloc, Stats** outStats, uint32* outCount)
{
    ASSERT(alloc);
    ASSERT(outStats);
    ASSERT(outCount);

    MutexScope mtx(gMemTemp.tempMtx);
    if (gMemTemp.tempCtxs.Count())
        *outStats = Mem::AllocTyped<MemTempAllocator::Stats>(gMemTemp.tempCtxs.Count(), alloc);
    *outCount = gMemTemp.tempCtxs.Count();

    for (uint32 i = 0; i < *outCount; i++) {
        Stats& s = (*outStats)[i];
        s.maxPeak = gMemTemp.tempCtxs[i]->peakBytes;
        s.commitedBytes = gMemTemp.tempCtxs[i]->commitedBytes;
        s.reservedBytes = gMemTemp.tempCtxs[i]->reservedBytes;
        s.threadId = gMemTemp.tempCtxs[i]->threadId;

        if (gMemTemp.tempCtxs[i]->threadName[0] == 0) {
            Thread::GetCurrentThreadName(gMemTemp.tempCtxs[i]->threadName, sizeof(gMemTemp.tempCtxs[i]->threadName));
            if (gMemTemp.tempCtxs[i]->threadName[0] == 0)
                Str::PrintFmt(gMemTemp.tempCtxs[i]->threadName, sizeof(gMemTemp.tempCtxs[i]->threadName), "Thread #%u", s.threadId);
        }

        s.threadName = gMemTemp.tempCtxs[i]->threadName;
    }
}

MemTempAllocator::ID MemTempAllocator::PushId()
{
    MemTempContext& ctx = _GetMemTempContext();

    if (ctx.allocStack.IsEmpty())
        ctx.inUseMtx.Enter();

    ++ctx.generationIdx;
    ASSERT_MSG(ctx.generationIdx <= UINT16_MAX, "Too many push temp allocator, generation overflowed");

    if (!ctx.init) {
        if (ctx.buffer == nullptr && !ctx.debugMode) {
            ctx.buffer = (uint8*)Mem::VirtualReserve(MEM_TEMP_MAX_BUFFER_SIZE);
            ctx.reservedBytes = MEM_TEMP_MAX_BUFFER_SIZE;
            ctx.bufferSize = MEM_TEMP_PAGE_SIZE;
            Mem::VirtualCommit(ctx.buffer, ctx.bufferSize); 
            ctx.commitedBytes = ctx.bufferSize;
        }
        ctx.init = true;
    }

    if (!ctx.used) {
        MutexScope mtx(gMemTemp.tempMtx);
        if (gMemTemp.tempCtxs.FindIf([ctx = &ctx](const MemTempContext* tmpCtx)->bool { return ctx == tmpCtx; }) == UINT32_MAX) {
            gMemTemp.tempCtxs.Push(&ctx);
            ctx.threadId = Thread::GetCurrentId();
            Thread::GetCurrentThreadName(ctx.threadName, sizeof(ctx.threadName));
        }

        ctx.used = true;
    }

    uint32 index = ctx.allocStack.Count();
    ASSERT_MSG(index <= UINT16_MAX, "Temp stack depth is too high! Perhaps a mistake in Push/Pop order");

    ID id = (index << 16) | (ctx.generationIdx & 0xffff);
    
    MemTempStack memStack { 
        .baseOffset = index > 0 ? (ctx.allocStack.Last().baseOffset + ctx.allocStack.Last().offset) : 0,
        .id = id
    };

    if constexpr(!CONFIG_FINAL_BUILD) {
        if (gMemTemp.captureTempStackTrace)
            memStack.numStackframes = Debug::CaptureStacktrace(memStack.stacktrace, MEM_TEMP_MAX_STACK_FRAMES, 2);
    }

    ctx.allocStack.Push(memStack);
    return id;
}

void MemTempAllocator::PopId(ID id)
{
    MemTempContext& ctx = _GetMemTempContext();

    ASSERT(id);
    ASSERT(ctx.used);
    ASSERT(ctx.generationIdx);

    [[maybe_unused]] uint32 index = id >> 16;
    ASSERT_MSG(index == ctx.allocStack.Count() - 1, "Invalid temp Push/Pop order");

    MemTempStack memStack = ctx.allocStack.PopLast();
    if (memStack.debugPointers.Count()) {
        for (MemDebugPointer p : memStack.debugPointers)
            Mem::GetDefaultAlloc()->Free(p.ptr, p.align);
        memStack.debugPointers.Free();
    }

    if (ctx.allocStack.IsEmpty())
        ctx.inUseMtx.Exit();
}

MemTempContext::~MemTempContext()
{
    if (buffer) {
        if (bufferSize)
            Mem::VirtualDecommit(buffer, bufferSize);
        Mem::VirtualRelease(buffer, bufferSize);
    }

    if (debugMode) {
        for (MemTempStack& memStack : allocStack) {
            for (MemDebugPointer p : memStack.debugPointers)
                Mem::GetDefaultAlloc()->Free(p.ptr, p.align);
            memStack.debugPointers.Free();
        }
    }
    allocStack.Free();

    used = false;
    init = false;
}

void MemTempAllocator::Reset()
{
    PROFILE_ZONE("TempAllocator.Reset");


    uint32 count;
    {
        MutexScope mtx(gMemTemp.tempMtx);
        gMemTemp.tempCtxs.CopyTo(&gMemTemp.tempCtxsCopy);
        count = gMemTemp.tempCtxs.Count();
    }

    for (uint32 i = 0; i < gMemTemp.tempCtxsCopy.Count();) {
        MemTempContext* ctx = gMemTemp.tempCtxsCopy[i];

        if (!ctx->inUseMtx.TryEnter()) {
            i++;
            continue;
        }

        if (ctx->used && ctx->allocStack.IsEmpty()) {
            ctx->generationIdx = 0;
            ctx->framePeaks[ctx->resetCount] = ctx->curFramePeak;
            ctx->resetCount = (ctx->resetCount + 1) % MEM_TEMP_FRAME_PEAKS_COUNT;
            ctx->curFramePeak = 0;

            if (!ctx->debugMode) {
                size_t maxPeakSize = 0;
                for (uint32 k = 0; k < MEM_TEMP_FRAME_PEAKS_COUNT; k++) {
                    if (ctx->framePeaks[k] > maxPeakSize)
                        maxPeakSize = ctx->framePeaks[k];
                }

                maxPeakSize = Max<size_t>(MEM_TEMP_PAGE_SIZE, maxPeakSize);
                maxPeakSize = AlignValue(maxPeakSize, gMemTemp.pageSize);
                if (maxPeakSize > ctx->bufferSize) {
                    size_t growSize = maxPeakSize - ctx->bufferSize;
                    Mem::VirtualCommit(ctx->buffer + ctx->bufferSize, growSize);
                    ctx->commitedBytes += growSize;
                }
                else if (maxPeakSize < ctx->bufferSize) {
                    size_t shrinkSize = ctx->bufferSize - maxPeakSize;
                    Mem::VirtualDecommit(ctx->buffer + maxPeakSize, shrinkSize);
                    ctx->commitedBytes -= shrinkSize;
                }
                ctx->bufferSize = maxPeakSize;
            }

            ctx->used = false;
            gMemTemp.tempCtxsCopy.RemoveAndSwap(i);
        }
        else {
            i++;
        }

        ctx->inUseMtx.Exit();
    }
    
    {
        MutexScope mtx(gMemTemp.tempMtx);
        for (uint32 i = count; i < gMemTemp.tempCtxs.Count(); i++)
            gMemTemp.tempCtxsCopy.Push(gMemTemp.tempCtxs[i]);
        gMemTemp.tempCtxsCopy.CopyTo(&gMemTemp.tempCtxs);
    }
    
}

MemTempAllocator::MemTempAllocator() : 
    mId(MemTempAllocator::PushId()), 
    mFiberProtectorId(Debug::FiberScopeProtector_Push("TempAllocator")),
    mOwnsId(true) 
{ 
}

MemTempAllocator::MemTempAllocator(ID id)
{
    if (id) {
        mId = id;
        mFiberProtectorId = Debug::FiberScopeProtector_Push("TempAllocator");
        mOwnsId = false;
    }
    else {
        mId = MemTempAllocator::PushId();
        mFiberProtectorId = Debug::FiberScopeProtector_Push("TempAllocator");
        mOwnsId = true;
    }
}

MemTempAllocator::~MemTempAllocator() 
{ 
    Debug::FiberScopeProtector_Pop(mFiberProtectorId); 
    if (mOwnsId) 
        MemTempAllocator::PopId(mId); 
}

void* MemTempAllocator::Malloc(size_t size, uint32 align) 
{
    return Realloc(nullptr, size, align);
}

void* MemTempAllocator::MallocZero(size_t size, uint32 align) 
{
    void* ptr = Realloc(nullptr, size, align);
    if (ptr)
        memset(ptr, 0x0, size);
    return ptr;
}

void* MemTempAllocator::Realloc(void* ptr, size_t size, uint32 align) 
{
    ID id = mId;
    MemTempContext& ctx = _GetMemTempContext();

    ASSERT(id);
    ASSERT(ctx.used);
    ASSERT(size);

    uint32 index = id >> 16;
    ASSERT_MSG(index == ctx.allocStack.Count() - 1, "Invalid temp id, likely doesn't belong to current temp stack scope");

    MemTempStack& memStack = ctx.allocStack[index];

    if (!ctx.debugMode) {
        align = Max(align, CONFIG_MACHINE_ALIGNMENT);
        size = AlignValue<size_t>(size, align);

        void* newPtr = nullptr;
        size_t lastSize = 0;
        size_t addOffset = size;
        if (ptr) {
            lastSize = *((size_t*)ptr - 1);
            ASSERT(size > lastSize);

            if (memStack.lastAllocatedPtr == ptr) {
                newPtr = ptr;
                addOffset -= lastSize;
            }
        }

        size_t startOffset = memStack.baseOffset + memStack.offset;
        size_t offset = startOffset;
        if (newPtr == nullptr) {
            offset += sizeof(size_t);
            if (offset % align != 0) 
                offset = AlignValue<size_t>(offset, align);
        }
        else {
            ASSERT(offset % align == 0);
        }
    
        size_t endOffset = offset + addOffset;

        if (endOffset > MEM_TEMP_MAX_BUFFER_SIZE) {
            MEM_FAIL();
            return nullptr;
        }

        if (endOffset > ctx.bufferSize) {
            size_t newSize = Clamp(ctx.bufferSize << 1, endOffset, MEM_TEMP_MAX_BUFFER_SIZE);

            size_t growSize = AlignValue(newSize - ctx.bufferSize, gMemTemp.pageSize);
            Mem::VirtualCommit(ctx.buffer + ctx.bufferSize, growSize);
            ctx.bufferSize += growSize;
            ctx.commitedBytes += growSize;
        }

        ctx.curFramePeak = Max<size_t>(ctx.curFramePeak, endOffset);
        ctx.peakBytes = Max<size_t>(ctx.peakBytes, endOffset);

        if (newPtr == nullptr) {
            newPtr = ctx.buffer + offset;

            memset(ctx.buffer + startOffset, 0x0, offset - startOffset);

            if (ptr)
                memcpy(newPtr, ptr, lastSize);
        }

        *((size_t*)newPtr - 1) = size;
        memStack.offset = endOffset - memStack.baseOffset;
        memStack.lastAllocatedPtr = newPtr;
        return newPtr;
    }
    else {
        void* initPtr = ptr;
        if (ptr == nullptr)
            ptr = Mem::GetDefaultAlloc()->Malloc(size, align);
        else
            ptr = Mem::GetDefaultAlloc()->Realloc(ptr, size, align);

        if (ptr) {
            memStack.offset += size;
            size_t endOffset = memStack.baseOffset + memStack.offset;

            ctx.peakBytes = Max<size_t>(ctx.peakBytes, endOffset);

            if (initPtr) {
                uint32 oldPtrIdx = memStack.debugPointers.FindIf([initPtr](const MemDebugPointer& p) { return p.ptr == initPtr; });
                if (oldPtrIdx != -1)
                    memStack.debugPointers.RemoveAndSwap(oldPtrIdx);
            }
            
            memStack.debugPointers.Push({ptr, align});
        }
        return ptr;
    }
}

void MemTempAllocator::Free(void* ptr, uint32) 
{
    if (!ptr)
        return;

    MemTempContext& ctx = _GetMemTempContext();

    if (ctx.debugMode) {
        uint32 index = mId >> 16;
        ASSERT_MSG(index == ctx.allocStack.Count() - 1, "Invalid temp id, likely doesn't belong to current temp stack scope");

        MemTempStack& memStack = ctx.allocStack[index];
        uint32 freeIdx = memStack.debugPointers.FindIf([ptr](const MemDebugPointer& p) { return p.ptr == ptr; });
        if (freeIdx != -1)
            memStack.debugPointers.RemoveAndSwap(freeIdx);
    }
}

size_t MemTempAllocator::GetOffset() const
{
    uint32 index = mId >> 16;
    ASSERT_MSG(index == _GetMemTempContext().allocStack.Count() - 1, "Invalid temp id, likely doesn't belong to current temp stack scope");

    const MemTempStack& memStack = _GetMemTempContext().allocStack[index];
    return memStack.baseOffset + memStack.offset;
}

size_t MemTempAllocator::GetPointerOffset(void* ptr) const
{
    return size_t((uint8*)ptr - _GetMemTempContext().buffer);
}


void MemBumpAllocatorBase::Initialize(size_t reserveSize, size_t pageSize, bool debugMode)
{
    mDebugMode = debugMode;

    if (!debugMode) {
        ASSERT(reserveSize);
        ASSERT(pageSize);

        mBuffer = (uint8*)BackendReserve(reserveSize);
        if (!mBuffer) 
            MEM_FAIL();

        mPageSize = pageSize;
        mReserveSize = reserveSize;
    }
    else {
        mDebugPointers = NEW(Mem::GetDefaultAlloc(), Array<MemDebugPointer>);
    }
}

void MemBumpAllocatorBase::Release()
{
    if (mBuffer) {
        if (mCommitSize)
            BackendDecommit(mBuffer, mCommitSize);
        BackendRelease(mBuffer, mReserveSize);
        mBuffer = nullptr;
    }
    
    if (mDebugMode) {
        for (MemDebugPointer p : *mDebugPointers)
            Mem::GetDefaultAlloc()->Free(p.ptr, p.align);
        mDebugPointers->Free();
        Mem::Free(mDebugPointers, Mem::GetDefaultAlloc());
        mDebugPointers = nullptr;
    }

    mCommitSize = 0;
    mReserveSize = 0;
}

bool MemBumpAllocatorBase::IsInitialized() const
{
    return !mDebugMode ? (mBuffer != nullptr) : (mDebugPointers != nullptr);
}

void MemBumpAllocatorBase::CommitAll()
{
    BackendCommit(mBuffer + mCommitSize, mReserveSize - mCommitSize);
    mCommitSize = mReserveSize;
}

void* MemBumpAllocatorBase::Malloc(size_t size, uint32 align)
{
    return MemBumpAllocatorBase::Realloc(nullptr, size, align);
}

void* MemBumpAllocatorBase::Realloc(void* ptr, size_t size, uint32 align)
{
    ASSERT(size);

    if (!mDebugMode) {
        ASSERT_MSG(mBuffer, "BumpAllocator is not initialized yet");
        
        align = Max(align, CONFIG_MACHINE_ALIGNMENT);
        size = AlignValue<size_t>(size, align);

        void* newPtr = nullptr;
        size_t lastSize = 0;
        size_t addOffset = size;
        if (ptr) {
            lastSize = *((size_t*)ptr - 1);
            ASSERT(size >= lastSize);

            if (mLastAllocatedPtr == ptr) {
                newPtr = ptr;
                addOffset -= lastSize;
            }
        }

        size_t startOffset = mOffset;
        size_t offset = startOffset;
        if (newPtr == nullptr) {
            offset += sizeof(size_t);
            if (offset % align != 0) 
                offset = AlignValue<size_t>(offset, align);
        }
        else {
            ASSERT(offset % align == 0);
        }
    
        size_t endOffset = offset + addOffset;

        if (endOffset > mReserveSize) {
            MEM_FAIL();
            return nullptr;
        }

        if (endOffset > mCommitSize) {
            size_t newSize = endOffset;

            size_t growSize = AlignValue(newSize - mCommitSize, mPageSize);
            BackendCommit(mBuffer + mCommitSize, growSize);
            mCommitSize += growSize;
        }

        if (!newPtr) {
            newPtr = mBuffer + offset;

            memset(mBuffer + startOffset, 0x0, offset - startOffset);

            if (ptr)
                memcpy(newPtr, ptr, lastSize);
        }

        *((size_t*)newPtr - 1) = size;
        mOffset = endOffset;
        mLastAllocatedPtr = newPtr;
        return newPtr;
    }
    else {
        if (ptr == nullptr) {
            ptr = Mem::GetDefaultAlloc()->Malloc(size, align);
        }
        else {
            void* newPtr = Mem::GetDefaultAlloc()->Realloc(ptr, size, align);
            if (newPtr != ptr) {
                uint32 index = mDebugPointers->FindIf([ptr](const MemDebugPointer& p) { return p.ptr == ptr; });
                if (index != -1) 
                    mDebugPointers->RemoveAndSwap(index);
            }
            ptr = newPtr;
        }

        mDebugPointers->Push({ptr, align});
        return ptr;
    }
}

void MemBumpAllocatorBase::Free(void* ptr, uint32)
{
    if (mDebugMode && ptr) {
        uint32 index = mDebugPointers->FindIf([ptr](const MemDebugPointer& p) { return p.ptr == ptr; });
        if (index != -1)
            mDebugPointers->RemoveAndSwap(index);
    }
}

void MemBumpAllocatorBase::Reset()
{
    if (!mDebugMode) {
        mLastAllocatedPtr = nullptr;
        mOffset = 0;
    }
    else {
        mOffset = 0;

        for (MemDebugPointer& dbgPtr : *mDebugPointers) 
            Mem::GetDefaultAlloc()->Free(dbgPtr.ptr, dbgPtr.align);
        mDebugPointers->Clear();
    }
}

size_t MemBumpAllocatorBase::GetPointerOffset(void* ptr)
{
    ASSERT(uintptr(ptr) >= uintptr(mBuffer) && uintptr(ptr) < uintptr(mBuffer + mCommitSize));
    return uintptr(ptr) - uintptr(mBuffer);
}

void MemBumpAllocatorBase::SetOffset(size_t offset)
{
    ASSERT(offset <= mOffset);
    mOffset = offset;
    mLastAllocatedPtr = nullptr;
}

void* MemBumpAllocatorVM::BackendReserve(size_t size)
{
    return Mem::VirtualReserve(size);
}

void* MemBumpAllocatorVM::BackendCommit(void* ptr, size_t size)
{
    return Mem::VirtualCommit(ptr, size);
}

void  MemBumpAllocatorVM::BackendDecommit(void* ptr, size_t size)
{
    return Mem::VirtualDecommit(ptr, size);
}

void  MemBumpAllocatorVM::BackendRelease(void* ptr, size_t size)
{
    return Mem::VirtualRelease(ptr, size);
}

void MemBumpAllocatorVM::WarmUp()
{
    size_t hwPageSize = OS::GetPageSize();
    size_t pageOffset = AlignValue(mOffset, mPageSize);
    BackendCommit(mBuffer + pageOffset, mReserveSize - pageOffset);
    for (size_t offset = pageOffset; offset < mReserveSize; offset += hwPageSize)
        memset(mBuffer + offset, 0xfe, CONFIG_MACHINE_ALIGNMENT);
}

void* MemBumpAllocatorCustom::BackendReserve(size_t size)
{
    return mAlloc->Malloc(size);
}

void* MemBumpAllocatorCustom::BackendCommit(void* ptr, size_t)
{
    return ptr;
}

void MemBumpAllocatorCustom::BackendDecommit(void*, size_t)
{
}

void MemBumpAllocatorCustom::BackendRelease(void* ptr, size_t)
{
    mAlloc->Free(ptr);
}

size_t MemTlsfAllocator::GetMemoryRequirement(size_t poolSize)
{
    return tlsf_size() + tlsf_align_size() + tlsf_pool_overhead() + poolSize;
}

void MemTlsfAllocator::Initialize(MemAllocator* alloc, size_t poolSize, bool debugMode)
{
    ASSERT(alloc);
    ASSERT(poolSize);

    mAlloc = alloc;
    size_t bufferSize = GetMemoryRequirement(poolSize);
    Initialize(poolSize, Mem::Alloc(bufferSize, alloc), bufferSize, debugMode);
}

void MemTlsfAllocator::Initialize([[maybe_unused]] size_t poolSize, void* buffer, size_t size, bool debugMode)
{
    mDebugMode = debugMode;
    mPoolSize = poolSize;

    if (!debugMode) {
        ASSERT(GetMemoryRequirement(poolSize) <= size);

        mTlsf = tlsf_create_with_pool(buffer, size);
        if (mTlsf == nullptr) {
            MEM_FAIL();
        }
        mTlsfSize = size;
    }
}

void MemTlsfAllocator::Release()
{
    if (mTlsf)
        tlsf_destroy(mTlsf);
}

void* MemTlsfAllocator::Malloc(size_t size, uint32 align)
{
    ASSERT(size);
    if (!mDebugMode) {
        ASSERT(mTlsf);

        void* ptr = nullptr;
        align = Max(align, CONFIG_MACHINE_ALIGNMENT);
        if (align <= CONFIG_MACHINE_ALIGNMENT) {
            ptr = tlsf_malloc(mTlsf, size);
        }
        else {
            ptr = tlsf_memalign(mTlsf, align, size);
        }

        if (ptr) {
            size_t blockSize = tlsf_block_size(ptr);
            mAllocatedSize += blockSize;

            TracyCAlloc(ptr, size);

            Mem::TrackMalloc(ptr, size);
            
            return ptr;
        }
        else {
            if (mAlloc && size <= mPoolSize) {
                size_t poolBufferSize = tlsf_pool_overhead() + tlsf_align_size() + mPoolSize;
                tlsf_add_pool(mTlsf, Mem::Alloc(poolBufferSize, mAlloc), mPoolSize);
                return Malloc(size, align);
            }

            MEM_FAIL();
            return nullptr;
        }
    }
    else {
        return Mem::GetDefaultAlloc()->Malloc(size, align);
    }
}

void* MemTlsfAllocator::Realloc(void* ptr, size_t size, uint32 align)
{
    if (!mDebugMode) {
        ASSERT(mTlsf);
        [[maybe_unused]] void* freePtr = ptr;

        if (ptr) 
            mAllocatedSize -= tlsf_block_size(ptr);

        ptr = tlsf_realloc(mTlsf, ptr, size);
        if (ptr) {
            mAllocatedSize += tlsf_block_size(ptr);
            TracyCRealloc(freePtr, ptr, size);

            Mem::TrackRealloc(freePtr, ptr, size);
            return ptr;
        }
        else {
            if (mAlloc) {
                size_t poolBufferSize = tlsf_pool_overhead() + tlsf_align_size() + mPoolSize;
                tlsf_add_pool(mTlsf, Mem::Alloc(poolBufferSize, mAlloc), mPoolSize);
                return Realloc(ptr, size, align);
            }

            MEM_FAIL();
            return nullptr;
        }
    }
    else {
        return Mem::GetDefaultAlloc()->Realloc(ptr, size, align);
    }
}

void MemTlsfAllocator::Free(void* ptr, uint32 align)
{
    if (!mDebugMode) {
        ASSERT(mTlsf);
        if (ptr) {
            size_t blockSize = tlsf_block_size(ptr);
            mAllocatedSize -= blockSize;
            tlsf_free(mTlsf, ptr);
            TracyCFree(ptr);
            Mem::TrackFree(ptr);
        }
    }
    else {
        return Mem::GetDefaultAlloc()->Free(ptr, align);
    }
}

bool MemTlsfAllocator::Validate()
{
    if (!mDebugMode) {
        ASSERT(mTlsf);
        return tlsf_check(mTlsf) == 0;
    }
    else {
        return true;
    }
}

float MemTlsfAllocator::CalculateFragmentation()
{
    struct AllocData
    {
        uint64 offset;
        uint64 size;
    };

    struct GetAllocsData
    {
        Array<AllocData> allocs;
        uint64 baseOffset;
    };

    auto GetAllocs = [](void* ptr, size_t size, int used, void* user)
    {
        GetAllocsData* data = reinterpret_cast<GetAllocsData*>(user);
        if (used) {
            data->allocs.Push(AllocData { 
                .offset = PtrToInt<uint64>(ptr) - data->baseOffset,
                .size = size
            });
        }
    };

    if (!mDebugMode) {
        MemTempAllocator tmpAlloc;
        GetAllocsData data;
        data.allocs.SetAllocator(&tmpAlloc);
        data.baseOffset = PtrToInt<uint64>(mTlsf);

        tlsf_walk_pool(tlsf_get_pool(mTlsf), GetAllocs, &data);

        if (data.allocs.Count()) {
            BlitSort<AllocData>(data.allocs.Ptr(), data.allocs.Count(), 
                [](const AllocData& a, const AllocData& b) { return a.offset < b.offset ? -1 : 1; });

            uint32 lastItemIdx = data.allocs.Count() - 1;
            uint64 firstOffset = data.allocs[0].offset;
            uint64 totalSize = (data.allocs[lastItemIdx].offset + data.allocs[lastItemIdx].size) - firstOffset;
            uint64 fragSize = 0;

            for (uint32 i = 1; i < data.allocs.Count(); i++) {
                uint64 prevEndOffset = data.allocs[i - 1].offset + data.allocs[i - 1].size;
                fragSize += data.allocs[i].offset - prevEndOffset;
            }

            return static_cast<float>(double(fragSize) / double(totalSize));
        }
    }

    return 0;
}

MemThreadSafeAllocator::MemThreadSafeAllocator()
{
    SpinLockMutex* lock = (SpinLockMutex*)mLock;
    memset(lock, 0x0, sizeof(SpinLockMutex));
}

MemThreadSafeAllocator::MemThreadSafeAllocator(MemAllocator* alloc) : mAlloc(alloc)
{
    SpinLockMutex* lock = (SpinLockMutex*)mLock;
    memset(lock, 0x0, sizeof(SpinLockMutex));
}

void MemThreadSafeAllocator::SetAllocator(MemAllocator* alloc)
{
    mAlloc = alloc;
}

void* MemThreadSafeAllocator::Malloc(size_t size, uint32 align)
{
    ASSERT(mAlloc);
    SpinLockMutex* lock_ = (SpinLockMutex*)mLock;
    SpinLockMutexScope lock(*lock_);
    return mAlloc->Malloc(size, align);
}

void* MemThreadSafeAllocator::Realloc(void* ptr, size_t size, uint32 align)
{
    ASSERT(mAlloc);
    SpinLockMutex* lock_ = (SpinLockMutex*)mLock;
    SpinLockMutexScope lock(*lock_);
    return mAlloc->Realloc(ptr, size, align);
}

void MemThreadSafeAllocator::Free(void* ptr, uint32 align)
{
    ASSERT(mAlloc);
    SpinLockMutex* lock_ = (SpinLockMutex*)mLock;
    SpinLockMutexScope lock(*lock_);
    mAlloc->Free(ptr, align);
}

MemAllocatorType MemThreadSafeAllocator::GetType() const
{
    ASSERT(mAlloc);
    return mAlloc->GetType();
}

MemProxyAllocator::MemProxyAllocator()
{
    SpinLockMutex* lock = (SpinLockMutex*)mLock;
    memset(lock, 0x0, sizeof(SpinLockMutex));
}

void MemProxyAllocator::Initialize(const char* name, MemAllocator* baseAlloc, MemProxyAllocatorFlags flags)
{
    ASSERT_MSG(!mBaseAlloc, "ProxyAllocator already initialized?");
    ASSERT(name);
    ASSERT(baseAlloc);
    ASSERT(baseAlloc->GetType() != MemAllocatorType::Proxy);

    mName = name;
    mBaseAlloc = baseAlloc;
    mFlags = flags;

    if (IsBitsSet<MemProxyAllocatorFlags>(flags, MemProxyAllocatorFlags::EnableTracking)) {
        mAllocTable = NEW(Mem::GetDefaultAlloc(), HashTable<MemProxyAllocatorItem>);
    }
}

void MemProxyAllocator::Release()
{
    if (IsBitsSet<MemProxyAllocatorFlags>(mFlags, MemProxyAllocatorFlags::EnableTracking)) {
        mAllocTable->Free();
        Mem::Free(mAllocTable);
    }
}

void* MemProxyAllocator::Malloc(size_t size, uint32 align)
{
    ASSERT(size);

    void* ptr = mBaseAlloc->Malloc(size, align);
    if (IsBitsSet<MemProxyAllocatorFlags>(mFlags, MemProxyAllocatorFlags::EnableTracking) && ptr) {
        SpinLockMutex* lock = (SpinLockMutex*)mLock;
        SpinLockMutexScope l(*lock);

        MemProxyAllocatorItem item {
            .ptr = ptr,
            .size = size
        };

        mAllocTable->Add(Hash::Int64To32(uint64(ptr)), item);

        mTotalSizeAllocated += size;
        ++mNumAllocs;
    }

    return ptr;
}

void* MemProxyAllocator::Realloc(void* ptr, size_t size, uint32 align)
{
    ASSERT(size);

    void* newPtr = mBaseAlloc->Realloc(ptr, size, align);
    if (IsBitsSet<MemProxyAllocatorFlags>(mFlags, MemProxyAllocatorFlags::EnableTracking) && newPtr) {
        SpinLockMutex* lock = (SpinLockMutex*)mLock;
        SpinLockMutexScope l(*lock);

        if (ptr) {
            uint32 lookupIdx = mAllocTable->Find(Hash::Int64To32(uint64(ptr)));
            ASSERT_MSG(lookupIdx != -1, "Invalid pointer. Pointer is not tracked in ProxyAllocator");
            MemProxyAllocatorItem& item = mAllocTable->GetMutable(lookupIdx);

            size_t prevSize = item.size;

            mTotalSizeAllocated -= prevSize;
            item.ptr = newPtr;
            item.size = size;
            mTotalSizeAllocated += size;

            if (ptr != newPtr) {
                mAllocTable->Remove(lookupIdx);
                mAllocTable->Add(Hash::Int64To32(uint64(newPtr)), item);

                if (mBaseAlloc->GetType() == MemAllocatorType::Bump && !((MemBumpAllocatorBase*)mBaseAlloc)->IsDebugMode())
                    mTotalSizeAllocated -= prevSize;
            }
        }
        else {
            MemProxyAllocatorItem item {
                .ptr = newPtr,
                .size = size
            };

            mAllocTable->Add(Hash::Int64To32(uint64(newPtr)), item);
            mTotalSizeAllocated += size;
            ++mNumAllocs;
        }
    }

    return newPtr;
}

void MemProxyAllocator::Free(void* ptr, uint32 align)
{
    if (!ptr)
        return;
    
    mBaseAlloc->Free(ptr, align);

    if (IsBitsSet<MemProxyAllocatorFlags>(mFlags, MemProxyAllocatorFlags::EnableTracking) && ptr) {
        SpinLockMutex* lock = (SpinLockMutex*)mLock;
        SpinLockMutexScope l(*lock);

        uint32 lookupIdx = mAllocTable->Find(Hash::Int64To32(uint64(ptr)));
        ASSERT_MSG(lookupIdx != -1, "Pointer is not being tracked in ProxyAllocator");
        const MemProxyAllocatorItem& item = mAllocTable->Get(lookupIdx);

        if (mBaseAlloc->GetType() != MemAllocatorType::Bump || ((MemBumpAllocatorBase*)mBaseAlloc)->IsDebugMode())
            mTotalSizeAllocated -= item.size;

        --mNumAllocs;

        mAllocTable->Remove(lookupIdx);
    }
}


#define __STDC_WANT_LIB_EXT1__ 1

#if MEMPRO_ENABLED
    #define OVERRIDE_NEW_DELETE
    #define WAIT_FOR_CONNECT true
    #define MEMPRO_BACKTRACE(_stackframes, _maxStackframes, _hashPtr) Debug::CaptureStacktrace(_stackframes, _maxStackframes, 3, _hashPtr)
    #include "External/mempro/MemPro.cpp"
    #define MEMPRO_TRACK_REALLOC(oldPtr, ptr, size) do { if (oldPtr)  { MEMPRO_TRACK_FREE(oldPtr); } MEMPRO_TRACK_ALLOC(ptr, size);} while(0)
#else
    #define MEMPRO_TRACK_ALLOC(ptr, size) 
    #define MEMPRO_TRACK_REALLOC(oldPtr, ptr, size)
    #define MEMPRO_TRACK_FREE(ptr)
#endif

#if PLATFORM_APPLE
    #define strcpy_s(dest, size, src)  strlcpy(dest, src, size)
    #define strcat_s(dest, size, src)  strlcat(dest, src, size)
#elif PLATFORM_ANDROID || PLATFORM_LINUX
    static size_t strcpy_s(char *dest, size_t size, const char *src);
    static size_t strcat_s(char *dst, size_t size, const char *src);
#elif PLATFORM_WINDOWS
    #if !MEMPRO_ENABLED
    extern "C" __declspec(dllimport) void __stdcall OutputDebugStringA(const char* lpOutputString);
    #endif
#else
    #define __STDC_WANT_LIB_EXT1__ 1
#endif

#include <time.h>   // time
#include <stdio.h>  // puts
#include <string.h>
#include <stdarg.h>

#if PLATFORM_ANDROID
    #include <android/log.h>
#endif

#if PLATFORM_POSIX
    #include <stdlib.h>
#else
    #include <malloc.h>
#endif


struct RandomContextCtor
{
    RandomContext ctx;

    RandomContextCtor() 
    {
        ctx = Random::CreateContext();
    }
};

namespace Random
{

NO_INLINE static RandomContextCtor& RandomCtx() 
{ 
    static thread_local RandomContextCtor randomCtx;
    return randomCtx; 
}

PRAGMA_DIAGNOSTIC_PUSH()
PRAGMA_DIAGNOSTIC_IGNORED_CLANG_GCC("-Wstrict-aliasing")
static inline float FloatNormalized(uint32 value)
{
    uint32 exponent = 127;
    uint32 mantissa = value >> 9;
    uint32 result = (exponent << 23) | mantissa;
    float fresult = *(float*)(&result);
    return fresult - 1.0f;
}
PRAGMA_DIAGNOSTIC_POP()

INLINE uint64 Avalanche64(uint64 h)
{
    h ^= h >> 33;
    h *= 0xff51afd7ed558ccd;
    h ^= h >> 33;
    h *= 0xc4ceb9fe1a85ec53;
    h ^= h >> 33;
    return h;
}

uint32 Seed()
{
    return static_cast<uint32>(time(nullptr));
}

RandomContext CreateContext(uint32 seed)
{
    RandomContext ctx = {{0, 0}};
    uint64 value = (((uint64)seed) << 1ull) | 1ull;    // make it odd
    value = Avalanche64(value);
    ctx.state[0] = 0ull;
    ctx.state[1] = (value << 1ull) | 1ull;
    Int(&ctx);
    ctx.state[0] += Avalanche64(value);
    Int(&ctx);
    return ctx;
}

uint32 Int(RandomContext* ctx)
{
    uint64 oldstate = ctx->state[0];
    ctx->state[0] = oldstate * 0x5851f42d4c957f2dull + ctx->state[1];
    uint32 xorshifted = uint32(((oldstate >> 18ull) ^ oldstate) >> 27ull);
    uint32 rot = uint32(oldstate >> 59ull);
    return (xorshifted >> rot) | (xorshifted << ((-(int)rot) & 31));
}

float Float(RandomContext* ctx)
{
    return FloatNormalized(Int(ctx));
}

float Float(RandomContext* ctx, float _min, float _max)
{
    ASSERT(_min <= _max);
    
    float r = Float(ctx);
    return _min + r*(_max - _min);
}

int Int(RandomContext* ctx, int _min, int _max)
{
    ASSERT(_min <= _max);
    
    uint32 range = static_cast<uint32>(_max - _min) + 1;
    return _min + static_cast<int>(Int(ctx) % range);
}

uint32 Int()
{
    return Int(&RandomCtx().ctx);
}

float Float()
{
    return Float(&RandomCtx().ctx);
}

float Float(float _min, float _max)
{
    return Float(&RandomCtx().ctx, _min, _max);
}

int Int(int _min, int _max)
{
    return Int(&RandomCtx().ctx, _min, _max);
}
} // Random

static AssertFailCallback gAssertFailCallback;
static void* gAssertFailUserData;

void Assert::DebugMessage(const char* fmt, ...)
{
    char msgFmt[4972];
    char msg[4972];
    
    va_list args;
    va_start(args, fmt);
    vsnprintf(msgFmt, sizeof(msgFmt), fmt, args);
    va_end(args);

    const char* closeBracket = "] ";
    char threadName[32];
    Thread::GetCurrentThreadName(threadName, sizeof(threadName));
    strcpy_s(msg, sizeof(msg), "[ASSERT_FAIL: ");
    strcat_s(msg, sizeof(msg), threadName);
    strcat_s(msg, sizeof(msg), closeBracket);
    strcat_s(msg, sizeof(msg), msgFmt);
    
    puts(msg);

    #if PLATFORM_WINDOWS
    strcat_s(msg, sizeof(msg), "\n");
    OutputDebugStringA(msg);
    #elif PLATFORM_ANDROID
    __android_log_write(ANDROID_LOG_FATAL, CONFIG_APP_NAME, msg);
    #endif

}

void Assert::SetFailCallback(AssertFailCallback callback, void* userdata)
{
    gAssertFailCallback = callback;
    gAssertFailUserData = userdata;
}

void Assert::RunFailCallback()
{
    if (gAssertFailCallback)
        gAssertFailCallback(gAssertFailUserData);
}

struct MemHeapAllocator final : MemAllocator 
{
    void* Malloc(size_t size, uint32 align) override;
    void* Realloc(void* ptr, size_t size, uint32 align) override;
    void  Free(void* ptr, uint32 align) override;
    MemAllocatorType GetType() const override { return MemAllocatorType::Heap; }
};

struct MemBaseContext
{
    MemFailCallback  memFailFn;
    void* 			 memFailUserdata;
    MemAllocator*		 defaultAlloc = &heapAlloc;
    MemHeapAllocator heapAlloc;
    bool             enableMemPro;
};

static MemBaseContext gMemBase;

#if PLATFORM_WINDOWS
    #define aligned_malloc(_align, _size) _aligned_malloc(_size, _align)
    #define aligned_realloc(_ptr, _align, _size) _aligned_realloc(_ptr, _size, _align)
    #define aligned_free(_ptr) _aligned_free(_ptr)
#else
    INLINE void* aligned_malloc(uint32 align, size_t size);
    INLINE void* aligned_realloc(void*, uint32, size_t);
    INLINE void  aligned_free(void* ptr);
#endif

void Mem::SetFailCallback(MemFailCallback callback, void* userdata)
{
    gMemBase.memFailFn = callback;
    gMemBase.memFailUserdata = userdata;
}

void Mem::RunFailCallback()
{
    if (gMemBase.memFailFn) {
        gMemBase.memFailFn(gMemBase.memFailUserdata);
    }
}

void* Mem::AlignPointer(void* ptr, size_t extra, uint32 align)
{
    union {
        void* ptr;
        uintptr_t addr;
    } un;
    un.ptr = ptr;
    uintptr_t unaligned = un.addr + extra;    // space for header
    uintptr_t aligned = AlignValue<uintptr_t>(unaligned, align);
    un.addr = aligned;
    return un.ptr;
}

MemAllocator* Mem::GetDefaultAlloc()
{
    return static_cast<MemAllocator*>(&gMemBase.heapAlloc);
}

void Mem::SetDefaultAlloc(MemAllocator* alloc)
{
    gMemBase.defaultAlloc = alloc != nullptr ? alloc : &gMemBase.heapAlloc;
}

void Mem::EnableMemPro(bool enable)
{
    #if MEMPRO_ENABLED
    gMemBase.enableMemPro = enable;
    #else
    UNUSED(enable);
    #endif
}

bool Mem::IsMemProEnabled()
{
    #if MEMPRO_ENABLED
    return gMemBase.enableMemPro;
    #else
    return false;
    #endif
}

void Mem::TrackMalloc([[maybe_unused]] void* ptr, [[maybe_unused]] size_t size)
{
    if constexpr (MEMPRO_ENABLED) {
        if (gMemBase.enableMemPro)
            MEMPRO_TRACK_ALLOC(ptr, size);
    }    
}

void Mem::TrackFree([[maybe_unused]] void* ptr)
{
    if constexpr (MEMPRO_ENABLED) {
        if (gMemBase.enableMemPro)
            MEMPRO_TRACK_FREE(ptr);
    }
}

void Mem::TrackRealloc([[maybe_unused]] void* oldPtr, [[maybe_unused]] void* ptr, [[maybe_unused]] size_t size)
{
    if constexpr (MEMPRO_ENABLED) {
        if (gMemBase.enableMemPro)
            MEMPRO_TRACK_REALLOC(oldPtr, ptr, size);
    }
}

inline void* MemHeapAllocator::Malloc(size_t size, uint32 align)
{
    void* ptr;
    if (align <= CONFIG_MACHINE_ALIGNMENT) {
        ptr = malloc(size);
        ASSERT((uintptr_t(ptr) % CONFIG_MACHINE_ALIGNMENT) == 0);   // Validate machine alignment with malloc
    }
    else {
        align = Max(align, CONFIG_MACHINE_ALIGNMENT);
        ptr = aligned_malloc(align, size);
    }
    if (!ptr) {
        MEM_FAIL();
        return nullptr;
    }

    TracyCAlloc(ptr, size);        

    Mem::TrackMalloc(ptr, size);
    return ptr;
}
    
inline void* MemHeapAllocator::Realloc(void* ptr, size_t size, uint32 align)
{
    [[maybe_unused]] void* freePtr = ptr;

    if (align <= CONFIG_MACHINE_ALIGNMENT) {
        ptr = realloc(ptr, size);
    }
    else {
        align = Max(align, CONFIG_MACHINE_ALIGNMENT);
        ptr = aligned_realloc(ptr, align, size);
    }
    
    if (!ptr) {
        MEM_FAIL();
        return nullptr;
    }
    
    TracyCRealloc(freePtr, ptr, size);
    Mem::TrackRealloc(freePtr, ptr, size);
    return ptr;
}
    
inline void MemHeapAllocator::Free(void* ptr, uint32 align)
{
    if (ptr != nullptr) {
        if (align <= CONFIG_MACHINE_ALIGNMENT) {
            free(ptr);
        }
        else {
            aligned_free(ptr);
        }
    
        TracyCFree(ptr);
        Mem::TrackFree(ptr);
    }
}

#if !PLATFORM_WINDOWS
INLINE void* aligned_malloc(uint32 align, size_t size)
{
    ASSERT(align >= CONFIG_MACHINE_ALIGNMENT);
    
    size_t total = size + align + sizeof(uint32);
    uint8* ptr = (uint8*)malloc(total);
    if (!ptr)
        return nullptr;
    uint8* aligned = (uint8*)Mem::AlignPointer(ptr, sizeof(uint32), align);
    uint32* header = (uint32*)aligned - 1;
    *header = PtrToInt<uint32>((void*)(aligned - ptr));  // Save the offset needed to move back from aligned pointer
    return aligned;
}

INLINE void* aligned_realloc(void* ptr, uint32 align, size_t size)
{
    ASSERT(align >= CONFIG_MACHINE_ALIGNMENT);

    if (ptr) {
        uint8* aligned = (uint8*)ptr;
        uint32 offset = *((uint32*)aligned - 1);
        ptr = aligned - offset;

        size_t total = size + align + sizeof(uint32);
        ptr = realloc(ptr, total);
        if (!ptr)
            return nullptr;
        uint8* newAligned = (uint8*)Mem::AlignPointer(ptr, sizeof(uint32), align);
        if (newAligned == aligned)
            return aligned;

        aligned = (uint8*)ptr + offset;
        memmove(newAligned, aligned, size);
        uint32* header = (uint32*)newAligned - 1;
        *header = PtrToInt<uint32>((void*)(newAligned - (uint8*)ptr));
        return newAligned;
    }
    else {
        return aligned_malloc(align, size);
    }
}

INLINE void aligned_free(void* ptr)
{
    if (ptr) {
        uint8* aligned = (uint8*)ptr;
        uint32* header = (uint32*)aligned - 1;
        ptr = aligned - *header;
        free(ptr);
    }
}
#endif  // !PLATFORM_WINDOWS

#if PLATFORM_ANDROID || PLATFORM_LINUX
static size_t strcpy_s(char *dest, size_t size, const char *src)
{
    size_t ret = strlen(src);

    if (size) {
        size_t len = (ret >= size) ? size - 1 : ret;
        memcpy(dest, src, len);
        dest[len] = '\0';
    }
    return ret;
}

static size_t strcat_s(char *dst, size_t size, const char *src)
{
    size_t  len;
    size_t  slen;

    len = 0;
    slen = strlen(src);
    while (*dst && size > 0) // added @JS1 edit
    {
        dst++;
        len++;
        size--;
    }
    while (*src && size-- > 1) //added @JS1 edit
        *dst++ = *src++;
    if (size == 1 || *src == 0) // **VERY IMPORTANT:** read update below
        *dst = '\0';
    return (slen + len);
}
#endif  // PLATFORM_ANDROID


#include <stdarg.h> // va_list/va_start
#include <stdio.h>  // puts


#ifdef BUILD_UNITY
    #if PLATFORM_WINDOWS
//----------------------------------------------------------------------------------------------------------------------
// DebugWin.cpp


#if PLATFORM_WINDOWS

//----------------------------------------------------------------------------------------------------------------------
// External/remedybg/remedybg_driver.h

/*

RemedyBG driver for 0.3.9.1 and later.

Note that the following documentation is preliminary and is subject to change.

The RemedyBG driver on Windows uses named pipes for communication between
processes. To enable this feature, RemedyBG can be invoked with the
"--servername" argument, passing the base name used for the creation of the
pipes. Without this argument, no named pipes will be created.

There are two named pipes created when the "--servername basename" argument is
given: one named ""\\.\pipe\basename", the debug control pipe, and another named
"\\.\pipe\basename-events", the debug events pipe.

The debug control pipe is a read-write pipe that should be setup in message mode
and can be used to control the debugger, including things such as creating a
session, adding a breakpoint, or deleting an expression from a watch window.

The debug control pipe command pipe accepts a packed stream of data beginning
with a 2 byte rdbg_Command. Depending on the command, one or more arguments to
the command may be required. See the documentation for individual commands in
the rdbg_Command enumeration below.

All commands will first return a rdbg_CommandResult followed by zero or more
additional values depending on the command.

The debug events pipe is a secondary, read-only pipe that can be used to
receive notifications of various events such as a breakpoint being hit. It, like
the debug control pipe, will use a packed stream of data. The format of the data
is documented in the rdbg_DebugEventKind enumeration below.

Note that to aid in debugging, you can view the RemedyBG error log at
`%APPDATA%\remedybg\app.log`.

*/


#include <stdint.h>

#define RDBG_MAX_SERVERNAME_LEN 64

typedef uint8_t rdbg_Bool;

typedef uint32_t rdbg_Id;

#pragma warning(push)
#pragma warning(disable: 4200)
#pragma pack(push, 1)
struct rdbg_String
{
   uint16_t len;
   uint8_t data[0];
};
#pragma pack(pop)
#pragma warning(pop)

enum rdbg_CommandResult
{
   RDBG_COMMAND_RESULT_UNKNOWN = 0,

   RDBG_COMMAND_RESULT_OK = 1,

   RDBG_COMMAND_RESULT_FAIL = 2,

   RDBG_COMMAND_RESULT_ABORTED = 3,

   RDBG_COMMAND_RESULT_INVALID_COMMAND = 4,

   RDBG_COMMAND_RESULT_BUFFER_TOO_SMALL = 5,

   RDBG_COMMAND_RESULT_FAILED_OPENING_FILE = 6,

   RDBG_COMMAND_RESULT_FAILED_SAVING_SESSION = 7,

   RDBG_COMMAND_RESULT_INVALID_ID = 8,

   RDBG_COMMAND_RESULT_INVALID_TARGET_STATE = 9,

   RDBG_COMMAND_RESULT_FAILED_NO_ACTIVE_CONFIG = 10,

   RDBG_COMMAND_RESULT_INVALID_BREAKPOINT_KIND = 11,
};

enum rdbg_DebuggingTargetBehavior
{
   RDBG_IF_DEBUGGING_TARGET_STOP_DEBUGGING = 1,
   RDBG_IF_DEBUGGING_TARGET_ABORT_COMMAND = 2
};

enum rdbg_ModifiedSessionBehavior
{
   RDBG_IF_SESSION_IS_MODIFIED_SAVE_AND_CONTINUE = 1,
   RDBG_IF_SESSION_IS_MODIFIED_CONTINUE_WITHOUT_SAVING = 2,
   RDBG_IF_SESSION_IS_MODIFIED_ABORT_COMMAND = 3,
};

enum rdbg_TargetState
{
   RDBG_TARGET_STATE_NONE = 1,
   RDBG_TARGET_STATE_SUSPENDED = 2,
   RDBG_TARGET_STATE_EXECUTING = 3,
};

enum rdbg_BreakpointKind
{
   RDBG_BREAKPOINT_KIND_FUNCTION_NAME = 1,
   RDBG_BREAKPOINT_KIND_FILENAME_LINE = 2,
   RDBG_BREAKPOINT_KIND_ADDRESS = 3,
   RDBG_BREAKPOINT_KIND_PROCESSOR = 4,
};

enum rdbg_ProcessorBreakpointAccessKind
{
   RDBG_PROCESSOR_BREAKPOINT_ACCESS_KIND_WRITE = 1,
   RDBG_PROCESSOR_BREAKPOINT_ACCESS_KIND_READ_WRITE = 2,
   RDBG_PROCESSOR_BREAKPOINT_ACCESS_KIND_EXECUTE = 3,
};

enum rdbg_Command
{
   RDBG_COMMAND_BRING_DEBUGGER_TO_FOREGROUND = 50,

   RDBG_COMMAND_SET_WINDOW_POS = 51,

   RDBG_COMMAND_GET_WINDOW_POS = 52,
   
   RDBG_COMMAND_SET_BRING_TO_FOREGROUND_ON_SUSPENDED = 53,

   RDBG_COMMAND_EXIT_DEBUGGER = 75,


   RDBG_COMMAND_GET_IS_SESSION_MODIFIED = 100,

   RDBG_COMMAND_GET_SESSION_FILENAME = 101,

   RDBG_COMMAND_NEW_SESSION = 102,

   RDBG_COMMAND_OPEN_SESSION = 103,

   RDBG_COMMAND_SAVE_SESSION = 104,

   RDBG_COMMAND_SAVE_AS_SESSION = 105,

   RDBG_COMMAND_GET_SESSION_CONFIGS = 106,

   RDBG_COMMAND_ADD_SESSION_CONFIG = 107,

   RDBG_COMMAND_SET_ACTIVE_SESSION_CONFIG = 108,

   RDBG_COMMAND_DELETE_SESSION_CONFIG = 109,

   RDBG_COMMAND_DELETE_ALL_SESSION_CONFIGS = 110,


   RDBG_COMMAND_GOTO_FILE_AT_LINE = 200,

   RDBG_COMMAND_CLOSE_FILE = 201,

   RDBG_COMMAND_CLOSE_ALL_FILES = 202,

   RDBG_COMMAND_GET_CURRENT_FILE = 203,

   RDBG_COMMAND_GET_OPEN_FILES = 204,


   RDBG_COMMAND_GET_TARGET_STATE = 300,

   RDBG_COMMAND_START_DEBUGGING = 301,

   RDBG_COMMAND_STOP_DEBUGGING = 302,

   RDBG_COMMAND_RESTART_DEBUGGING = 303,

   RDBG_COMMAND_ATTACH_TO_PROCESS_BY_PID = 304,

   RDBG_COMMAND_ATTACH_TO_PROCESS_BY_NAME = 305,

   RDBG_COMMAND_DETACH_FROM_PROCESS = 306,

   RDBG_COMMAND_STEP_INTO_BY_LINE = 307,

   RDBG_COMMAND_STEP_INTO_BY_INSTRUCTION = 308,

   RDBG_COMMAND_STEP_OVER_BY_LINE = 309,

   RDBG_COMMAND_STEP_OVER_BY_INSTRUCTION = 310,

   RDBG_COMMAND_STEP_OUT = 311,

   RDBG_COMMAND_CONTINUE_EXECUTION = 312,

   RDBG_COMMAND_RUN_TO_FILE_AT_LINE = 313,

   RDBG_COMMAND_BREAK_EXECUTION = 314,


   RDBG_COMMAND_GET_BREAKPOINTS = 600,

   RDBG_COMMAND_GET_BREAKPOINT_LOCATIONS = 601,

   RDBG_COMMAND_GET_FUNCTION_OVERLOADS = 602,

   RDBG_COMMAND_ADD_BREAKPOINT_AT_FUNCTION = 603,

   RDBG_COMMAND_ADD_BREAKPOINT_AT_FILENAME_LINE = 604,

   RDBG_COMMAND_ADD_BREAKPOINT_AT_ADDRESS = 605,

   RDBG_COMMAND_ADD_PROCESSOR_BREAKPOINT = 606,

   RDBG_COMMAND_SET_BREAKPOINT_CONDITION = 607,

   RDBG_COMMAND_UPDATE_BREAKPOINT_LINE = 608,

   RDBG_COMMAND_ENABLE_BREAKPOINT = 609,

   RDBG_COMMAND_DELETE_BREAKPOINT = 610,

   RDBG_COMMAND_DELETE_ALL_BREAKPOINTS = 611,

   RDBG_COMMAND_GET_BREAKPOINT = 612,


   RDBG_COMMAND_GET_WATCHES = 700,

   RDBG_COMMAND_ADD_WATCH = 701,

   RDBG_COMMAND_UPDATE_WATCH_EXPRESSION = 702,

   RDBG_COMMAND_UPDATE_WATCH_COMMENT = 703,

   RDBG_COMMAND_DELETE_WATCH = 704,

   RDBG_COMMAND_DELETE_ALL_WATCHES = 705,
};

enum rdbg_SourceLocChangedReason
{
   RDBG_SOURCE_LOC_CHANGED_REASON_UNSPECIFIED = 0,

   RDBG_SOURCE_LOC_CHANGED_REASON_BY_COMMAND_LINE = 1,

   RDBG_SOURCE_LOC_CHANGED_REASON_BY_DRIVER = 2,

   RDBG_SOURCE_LOC_CHANGED_REASON_BREAKPOINT_SELECTED = 3,

   RDBG_SOURCE_LOC_CHANGED_REASON_CURRENT_FRAME_CHANGED = 4,

   RDBG_SOURCE_LOC_CHANGED_REASON_ACTIVE_THREAD_CHANGED = 5,

   RDBG_SOURCE_LOC_CHANGED_REASON_BREAKPOINT_HIT = 6,
   RDBG_SOURCE_LOC_CHANGED_REASON_EXCEPTION_HIT = 7,
   RDBG_SOURCE_LOC_CHANGED_REASON_STEP_OVER = 8,
   RDBG_SOURCE_LOC_CHANGED_REASON_STEP_IN = 9,
   RDBG_SOURCE_LOC_CHANGED_REASON_STEP_OUT = 10,
   RDBG_SOURCE_LOC_CHANGED_REASON_NON_USER_BREAKPOINT = 11,
   RDBG_SOURCE_LOC_CHANGED_REASON_DEBUG_BREAK = 12,
};

enum rdbg_DebugEventKind
{
   RDBG_DEBUG_EVENT_KIND_EXIT_PROCESS = 100,

   RDBG_DEBUG_EVENT_KIND_TARGET_STARTED = 101,

   RDBG_DEBUG_EVENT_KIND_TARGET_ATTACHED = 102,

   RDBG_DEBUG_EVENT_KIND_TARGET_DETACHED = 103,

   RDBG_DEBUG_EVENT_KIND_TARGET_CONTINUED = 104,

   RDBG_DEBUG_EVENT_KIND_SOURCE_LOCATION_CHANGED = 200,

   RDBG_DEBUG_EVENT_KIND_BREAKPOINT_HIT = 600,

   RDBG_DEBUG_EVENT_KIND_BREAKPOINT_RESOLVED = 601,

   RDBG_DEBUG_EVENT_KIND_BREAKPOINT_ADDED = 602,

   RDBG_DEBUG_EVENT_KIND_BREAKPOINT_MODIFIED = 603,

   RDBG_DEBUG_EVENT_KIND_BREAKPOINT_REMOVED = 604,

   RDBG_DEBUG_EVENT_KIND_OUTPUT_DEBUG_STRING = 800,
};

//----------------------------------------------------------------------------------------------------------------------
// IncludeWin.h


#if defined(_WIN32) || defined(_WIN64)

#define WIN32_MEAN_AND_LEAN
#define VC_EXTRALEAN
#define NOMINMAX          // Macros min(a,b) and max(a,b)

#include <winsock2.h>
#include <windows.h>

#undef WIN32_MEAN_AND_LEAN
#undef VC_EXTRALEAN
#undef NOMINMAX

#endif // _WIN32 / _WIN64



#pragma pack(push, 8)
#include <DbgHelp.h>

typedef struct _IMAGEHLP_MODULE64_V3
{
    DWORD SizeOfStruct;        // set to sizeof(IMAGEHLP_MODULE64)
    DWORD64 BaseOfImage;       // base load address of module
    DWORD ImageSize;           // virtual size of the loaded module
    DWORD TimeDateStamp;       // date/time stamp from pe header
    DWORD CheckSum;            // checksum from the pe header
    DWORD NumSyms;             // number of symbols in the symbol table
    SYM_TYPE SymType;          // type of symbols loaded
    CHAR ModuleName[32];       // module name
    CHAR ImageName[256];       // image name
    CHAR LoadedImageName[256]; // symbol file name
    CHAR LoadedPdbName[256];   // pdb file name
    DWORD CVSig;               // Signature of the CV record in the debug directories
    CHAR CVData[PATH_CHARS_MAX * 3]; // Contents of the CV record
    DWORD PdbSig;              // Signature of PDB
    GUID PdbSig70;             // Signature of PDB (VC 7 and up)
    DWORD PdbAge;              // DBI age of pdb
    BOOL PdbUnmatched;         // loaded an unmatched pdb
    BOOL DbgUnmatched;         // loaded an unmatched dbg
    BOOL LineNumbers;          // we have line number information
    BOOL GlobalSymbols;        // we have internal symbol information
    BOOL TypeInfo;             // we have type information
    BOOL SourceIndexed; // pdb supports source server
    BOOL Publics;       // contains public symbols
} IMAGEHLP_MODULE64_V3, *PIMAGEHLP_MODULE64_V3;

typedef struct _IMAGEHLP_MODULE64_V2
{
    DWORD SizeOfStruct;        // set to sizeof(IMAGEHLP_MODULE64)
    DWORD64 BaseOfImage;       // base load address of module
    DWORD ImageSize;           // virtual size of the loaded module
    DWORD TimeDateStamp;       // date/time stamp from pe header
    DWORD CheckSum;            // checksum from the pe header
    DWORD NumSyms;             // number of symbols in the symbol table
    SYM_TYPE SymType;          // type of symbols loaded
    CHAR ModuleName[32];       // module name
    CHAR ImageName[256];       // image name
    CHAR LoadedImageName[256]; // symbol file name
} IMAGEHLP_MODULE64_V2, *PIMAGEHLP_MODULE64_V2;
#pragma pack(pop)

using SymInitializeFn = BOOL(*)(IN HANDLE process, IN LPCSTR UserSearchPath, IN BOOL fInvadeProcess);
using SymCleanupFn = BOOL(*)(IN HANDLE process);
using SymGetSymFromAddr64Fn = BOOL(*)(IN HANDLE process, IN DWORD64 dwAddr, OUT PDWORD64 pdwDisplacement, OUT PIMAGEHLP_SYMBOL64 Symbol);
using UnDecorateSymbolNameFn = DWORD(WINAPI*)(PCSTR DecoratedName, PSTR UnDecoratedName, DWORD UndecoratedLength, DWORD Flags);
using SymGetLineFromAddr64Fn = BOOL(*)(IN HANDLE process, IN DWORD64 dwAddr, OUT PDWORD pdwDisplacement, OUT PIMAGEHLP_LINE64 line);  

static SymInitializeFn _SymInitialize;
static SymCleanupFn _SymCleanup;
static SymGetSymFromAddr64Fn _SymGetSymFromAddr64;
static UnDecorateSymbolNameFn _UnDecorateSymbolName;
static SymGetLineFromAddr64Fn _SymGetLineFromAddr64;

struct DebugStacktraceContext
{
    bool mInitialized;
    HINSTANCE mDbgHelp;
    HANDLE mProcess;
    CRITICAL_SECTION mMutex;
    
    DebugStacktraceContext();
    ~DebugStacktraceContext();
};

static DebugStacktraceContext gStacktrace;

namespace Debug
{
    static bool InitializeStacktrace()
    {
        if (gStacktrace.mInitialized)
        return true;
        gStacktrace.mInitialized = true;

        EnterCriticalSection(&gStacktrace.mMutex);
        ASSERT(gStacktrace.mDbgHelp == nullptr);

        gStacktrace.mDbgHelp = LoadLibraryA("dbghelp.dll");
        if (!gStacktrace.mDbgHelp) {
            Debug::PrintLine("Could not load DbgHelp.dll");
            gStacktrace.mInitialized = false;
            return false;
        }

        _SymInitialize = (SymInitializeFn)GetProcAddress(gStacktrace.mDbgHelp, "SymInitialize");
        _SymCleanup = (SymCleanupFn)GetProcAddress(gStacktrace.mDbgHelp, "SymCleanup");
        _SymGetLineFromAddr64 = (SymGetLineFromAddr64Fn)GetProcAddress(gStacktrace.mDbgHelp, "SymGetLineFromAddr64");
        _SymGetSymFromAddr64 = (SymGetSymFromAddr64Fn)GetProcAddress(gStacktrace.mDbgHelp, "SymGetSymFromAddr64");
        _UnDecorateSymbolName = (UnDecorateSymbolNameFn)GetProcAddress(gStacktrace.mDbgHelp, "UnDecorateSymbolName");
        ASSERT(_SymInitialize && _SymCleanup && _SymGetLineFromAddr64 && _SymGetSymFromAddr64 && _UnDecorateSymbolName);

        gStacktrace.mProcess = GetCurrentProcess();

        if (!_SymInitialize(gStacktrace.mProcess, NULL, TRUE)) {
            LeaveCriticalSection(&gStacktrace.mMutex);
            Debug::PrintLine("DbgHelp: _SymInitialize failed");
            gStacktrace.mInitialized = false;
            return false;
        }

        ASSERT(_SymInitialize && _SymCleanup && _SymGetLineFromAddr64 && _SymGetSymFromAddr64 && _UnDecorateSymbolName);
        LeaveCriticalSection(&gStacktrace.mMutex);

        return true;
    }
};

#ifdef TRACY_ENABLE
void DebugDbgHelpInit()
{
    if (!gStacktrace.mInitialized) {
        Debug::InitializeStacktrace();
        ASSERT_MSG(gStacktrace.mInitialized, "Failed to initialize stacktrace capture");
    }  
}

void DebugDbgHelpLock()
{
    EnterCriticalSection(&gStacktrace.mMutex);
}

void DebugDbgHelpUnlock()
{
    LeaveCriticalSection(&gStacktrace.mMutex);
}
#endif // if TRACY_ENABLE

NO_INLINE uint16 Debug::CaptureStacktrace(void** stackframes, uint16 maxStackframes, uint16 framesToSkip, uint32* pHash)
{
    static_assert(sizeof(DWORD) == sizeof(uint32));

    return (uint16)RtlCaptureStackBackTrace(framesToSkip, maxStackframes, stackframes, PDWORD(pHash));
}

void Debug::ResolveStacktrace(uint16 numStacktrace, void* const* stackframes, DebugStacktraceEntry* entries)
{
    if (!gStacktrace.mInitialized) {
        Debug::InitializeStacktrace();
        ASSERT_MSG(gStacktrace.mInitialized, "Failed to initialize stacktrace capture");
    }  

    IMAGEHLP_LINE64 line;
    uint8* symbolBuffer[sizeof(IMAGEHLP_SYMBOL64) + PATH_CHARS_MAX];
    IMAGEHLP_SYMBOL64* symbol = reinterpret_cast<IMAGEHLP_SYMBOL64*>(symbolBuffer);
    memset(symbol, 0, sizeof(IMAGEHLP_SYMBOL64) + PATH_CHARS_MAX);
    symbol->SizeOfStruct = sizeof(IMAGEHLP_SYMBOL64);
    symbol->MaxNameLength = PATH_CHARS_MAX;

    EnterCriticalSection(&gStacktrace.mMutex);
    for (uint16 i = 0; i < numStacktrace; i++) {
        DebugStacktraceEntry entry = {};
        if (_SymGetSymFromAddr64(gStacktrace.mProcess, (DWORD64)stackframes[i], &entry.offsetFromSymbol, symbol)) {
            Str::Copy(entry.name, sizeof(entry.name), symbol->Name);
        } 
        else {
            DWORD gle = GetLastError();
            if (gle != ERROR_INVALID_ADDRESS && gle != ERROR_MOD_NOT_FOUND) {
                Debug::PrintLine("_SymGetSymFromAddr64 failed");
                break;
            }
            Str::Copy(entry.name, sizeof(entry.name), "[NA]");
        }

        if (_SymGetLineFromAddr64(gStacktrace.mProcess, (DWORD64)stackframes[i], (PDWORD)&(entry.offsetFromLine), &line)) {
            entry.line = line.LineNumber;
            Str::Copy(entry.filename, PATH_CHARS_MAX, line.FileName);
        } 
        else {
            DWORD gle = GetLastError();
            if (gle != ERROR_INVALID_ADDRESS && gle != ERROR_MOD_NOT_FOUND) {
                Debug::PrintLine("_SymGetLineFromAddr64 failed");
                break;
            }
            Str::Copy(entry.filename, PATH_CHARS_MAX, "[NA]");
        }

        memcpy(&entries[i], &entry, sizeof(DebugStacktraceEntry));
    }
    LeaveCriticalSection(&gStacktrace.mMutex);
}

void Debug::StacktraceSaveStopPoint(void*)
{
}

DebugStacktraceContext::DebugStacktraceContext() : mDbgHelp(nullptr), mProcess(nullptr)
{
    if constexpr (!CONFIG_FINAL_BUILD) {
        InitializeCriticalSectionAndSpinCount(&mMutex, 32);
        Debug::InitializeStacktrace();
    }
}

DebugStacktraceContext::~DebugStacktraceContext()
{
    if (mInitialized) {
        ASSERT(mDbgHelp);
        ASSERT(_SymCleanup);

        EnterCriticalSection(&mMutex);
        _SymCleanup(mProcess);
        FreeLibrary(mDbgHelp);
        mDbgHelp = nullptr;
        LeaveCriticalSection(&mMutex);

        #if defined(TRACY_ENABLE)
        DeleteCriticalSection(&mMutex);
        #endif
    }
}


static const char* RDBG_PIPE_NAME_PREFIX = "\\\\.\\pipe\\";
static constexpr uint32 RDBG_BUFFER_SIZE = 8*SIZE_KB;
static constexpr uint32 RDBG_LAUNCH_MAX_WAIT_TIME = 2000;
static constexpr uint32 RDBG_CONNECTION_RETRY_INTERVAL = 100;
static constexpr uint32 RDBG_CONNECTION_MAX_RETRIES = 5;

struct RDBG_Context
{
    OSProcess remedybgProc;
    HANDLE cmdPipe = INVALID_HANDLE_VALUE;
};
static RDBG_Context gRemedyBG;

namespace RDBG
{
    static Blob SendCommand(const Blob& cmdBuffer, MemAllocator* outBufferAlloc)
    {
        ASSERT(gRemedyBG.cmdPipe != INVALID_HANDLE_VALUE);

        uint8 tempBuffer[RDBG_BUFFER_SIZE];
        DWORD bytesRead;
        Blob outBuffer(outBufferAlloc);
        outBuffer.SetGrowPolicy(Blob::GrowPolicy::Linear);

        BOOL r = TransactNamedPipe(gRemedyBG.cmdPipe, const_cast<void*>(cmdBuffer.Data()), DWORD(cmdBuffer.Size()), tempBuffer, sizeof(tempBuffer), &bytesRead, nullptr);
        if (r)
            outBuffer.Write(tempBuffer, bytesRead);

        while (!r && GetLastError() == ERROR_MORE_DATA) {
            r = ReadFile(gRemedyBG.cmdPipe, tempBuffer, sizeof(tempBuffer), &bytesRead, nullptr);
            if (r)
                outBuffer.Write(tempBuffer, bytesRead);
        }

        if (!r) {
            LOG_ERROR("Reading RemedyBG pipe failed");
            RDBG::Release();
            return outBuffer;
        }

        return outBuffer;
    }

    static inline rdbg_CommandResult GetResult(Blob& resultBuff)
    {
        uint16 res;
        resultBuff.Read<uint16>(&res);
        return rdbg_CommandResult(res);
    }
}

bool RDBG::Initialize(const char* serverName, const char* remedybgPath)
{
    ASSERT(remedybgPath);
    ASSERT_MSG(gRemedyBG.cmdPipe == INVALID_HANDLE_VALUE, "RemedyBG is initialized before");

    ASSERT_MSG(!OS::IsDebuggerPresent(), "Another debugger is already attached to this executable");
    ASSERT_ALWAYS(Str::Len(serverName) <= RDBG_MAX_SERVERNAME_LEN, "ServerName is too long for RemedyBG sessions: %s", serverName);

    Path remedybgCmdline(remedybgPath);
    remedybgCmdline.Append(" --servername ");
    remedybgCmdline.Append(serverName);
    if (!gRemedyBG.remedybgProc.Run(remedybgCmdline.CStr(), OSProcessFlags::None)) {
        LOG_ERROR("RemedyBG: Could not run RemedyBG instance '%s'", remedybgPath);
        return false;
    }
    constexpr uint32 WAIT_TIME = 20;
    uint32 waitTm = 0;
    while (!gRemedyBG.remedybgProc.IsRunning() && waitTm < RDBG_LAUNCH_MAX_WAIT_TIME) {
        Thread::Sleep(WAIT_TIME);
        waitTm += WAIT_TIME;
    }
    if (!gRemedyBG.remedybgProc.IsRunning())
        return false;

    String<256> pipeName(RDBG_PIPE_NAME_PREFIX);
    pipeName.Append(serverName);

    uint32 retryCount = 0;
    while (gRemedyBG.cmdPipe == INVALID_HANDLE_VALUE && retryCount < RDBG_CONNECTION_MAX_RETRIES) {
        gRemedyBG.cmdPipe = CreateFileA(pipeName.CStr(), GENERIC_READ|GENERIC_WRITE, 0, nullptr, OPEN_EXISTING, 0, nullptr);
        if (gRemedyBG.cmdPipe == INVALID_HANDLE_VALUE) {
            LOG_ERROR("RemedyBG: Creating command pipe failed");
            return false;
        }
        Thread::Sleep(RDBG_CONNECTION_RETRY_INTERVAL);   // wait a little more so remedybg gets it's shit together
        ++retryCount;
    }
    
    DWORD newMode = PIPE_READMODE_MESSAGE;
    if (!SetNamedPipeHandleState(gRemedyBG.cmdPipe, &newMode, nullptr, nullptr)) {
        LOG_ERROR("RemedyBG: SetNamedPipeHandleState failed");
        return false;
    }

    if (RDBG::AttachToProcess(0)) {
        LOG_DEBUG("RemedyBG launched and attached to the process");
        return true;
    }
    else {
        LOG_ERROR("Attaching RemedyBG debugger to the current process failed");
        return false;
    }
}

void RDBG::Release()
{
    if (gRemedyBG.cmdPipe != INVALID_HANDLE_VALUE) 
        CloseHandle(gRemedyBG.cmdPipe);
    gRemedyBG.cmdPipe = INVALID_HANDLE_VALUE;
    if (gRemedyBG.remedybgProc.IsValid())
        gRemedyBG.remedybgProc.Abort();
}

#define DEBUG_REMEDYBG_BEGINCOMMAND(_cmd)   \
    MemTempAllocator tempAlloc; \
    Blob cmdBuffer(&tempAlloc); \
    cmdBuffer.SetGrowPolicy(Blob::GrowPolicy::Linear); \
    cmdBuffer.Write<uint16>(_cmd)

bool RDBG::AttachToProcess(uint32 id)
{
    if (gRemedyBG.cmdPipe == INVALID_HANDLE_VALUE)
        return 0;

    DEBUG_REMEDYBG_BEGINCOMMAND(RDBG_COMMAND_ATTACH_TO_PROCESS_BY_PID);

    if (id == 0)
        id = GetCurrentProcessId();

    cmdBuffer.Write<uint32>(id);
    cmdBuffer.Write<rdbg_Bool>(true);
    cmdBuffer.Write<uint8>(RDBG_IF_DEBUGGING_TARGET_STOP_DEBUGGING);
    Blob res = RDBG::SendCommand(cmdBuffer, &tempAlloc);
    return RDBG::GetResult(res) == RDBG_COMMAND_RESULT_OK;
}

bool RDBG::DetachFromProcess()
{
    if (gRemedyBG.cmdPipe == INVALID_HANDLE_VALUE)
        return 0;

    DEBUG_REMEDYBG_BEGINCOMMAND(RDBG_COMMAND_DETACH_FROM_PROCESS);
    Blob res = RDBG::SendCommand(cmdBuffer, &tempAlloc);
    return RDBG::GetResult(res) == RDBG_COMMAND_RESULT_OK;
}

bool RDBG::Break()
{
    if (gRemedyBG.cmdPipe == INVALID_HANDLE_VALUE)
        return 0;
    
    DEBUG_REMEDYBG_BEGINCOMMAND(RDBG_COMMAND_BREAK_EXECUTION);
    Blob res = RDBG::SendCommand(cmdBuffer, &tempAlloc);
    return RDBG::GetResult(res) == RDBG_COMMAND_RESULT_OK;
}

bool RDBG::Continue()
{
    DEBUG_REMEDYBG_BEGINCOMMAND(RDBG_COMMAND_CONTINUE_EXECUTION);
    Blob res = RDBG::SendCommand(cmdBuffer, &tempAlloc);
    return RDBG::GetResult(res) == RDBG_COMMAND_RESULT_OK;
}

bool RDBG::RunToFileAtLine(const char* filename, uint32 line)
{
    if (gRemedyBG.cmdPipe == INVALID_HANDLE_VALUE)
        return 0;

    ASSERT(filename);
    DEBUG_REMEDYBG_BEGINCOMMAND(RDBG_COMMAND_RUN_TO_FILE_AT_LINE);
    cmdBuffer.WriteStringBinary16(filename);
    cmdBuffer.Write<uint32>(line);
    Blob res = RDBG::SendCommand(cmdBuffer, &tempAlloc);
    return RDBG::GetResult(res) == RDBG_COMMAND_RESULT_OK;
}

RDBG_Id RDBG::AddFunctionBreakpoint(const char* funcName, const char* conditionExpr, uint32 overloadId)
{
    if (gRemedyBG.cmdPipe == INVALID_HANDLE_VALUE)
        return 0;

    ASSERT(funcName);
    DEBUG_REMEDYBG_BEGINCOMMAND(RDBG_COMMAND_ADD_BREAKPOINT_AT_FUNCTION);
    cmdBuffer.WriteStringBinary16(funcName);
    cmdBuffer.Write<uint32>(overloadId);
    cmdBuffer.WriteStringBinary16(conditionExpr ? conditionExpr : "");
    Blob res = RDBG::SendCommand(cmdBuffer, &tempAlloc);

    RDBG_Id bid = 0;
    if (RDBG::GetResult(res) == RDBG_COMMAND_RESULT_OK)
        res.Read<RDBG_Id>(&bid);
    return bid;
}

RDBG_Id RDBG::AddFileLineBreakpoint(const char* filename, uint32 line, const char* conditionExpr)
{
    if (gRemedyBG.cmdPipe == INVALID_HANDLE_VALUE)
        return 0;

    ASSERT(filename);
    DEBUG_REMEDYBG_BEGINCOMMAND(RDBG_COMMAND_ADD_BREAKPOINT_AT_FILENAME_LINE);
    cmdBuffer.WriteStringBinary16(filename);
    cmdBuffer.Write<uint32>(line);
    cmdBuffer.WriteStringBinary16(conditionExpr ? conditionExpr : "");
    Blob res = RDBG::SendCommand(cmdBuffer, &tempAlloc);

    RDBG_Id bid = 0;
    if (RDBG::GetResult(res) == RDBG_COMMAND_RESULT_OK)
        res.Read<RDBG_Id>(&bid);
    return bid;
}

RDBG_Id RDBG::AddAddressBreakpoint(uintptr_t addr, const char* conditionExpr)
{
    if (gRemedyBG.cmdPipe == INVALID_HANDLE_VALUE)
        return 0;

    ASSERT(addr);
    DEBUG_REMEDYBG_BEGINCOMMAND(RDBG_COMMAND_ADD_BREAKPOINT_AT_ADDRESS);
    cmdBuffer.Write<uint64>(addr);
    cmdBuffer.WriteStringBinary16(conditionExpr ? conditionExpr : "");
    Blob res = RDBG::SendCommand(cmdBuffer, &tempAlloc);

    RDBG_Id bid = 0;
    if (RDBG::GetResult(res) == RDBG_COMMAND_RESULT_OK)
        res.Read<RDBG_Id>(&bid);
    return bid;
}

RDBG_Id RDBG::AddProcessorBreakpoint(const void* addr, uint8 numBytes, RDBG_ProcessorBreakpointType type, const char* conditionExpr)
{
    if (gRemedyBG.cmdPipe == INVALID_HANDLE_VALUE)
        return 0;

    ASSERT_MSG(numBytes <= 8, "Processor breakpoints cannot be more than 8 bytes");

    ASSERT(addr);
    DEBUG_REMEDYBG_BEGINCOMMAND(RDBG_COMMAND_ADD_PROCESSOR_BREAKPOINT);

    char addrExpr[64];
    Str::PrintFmt(addrExpr, sizeof(addrExpr), "0x%llx", addr);
    cmdBuffer.WriteStringBinary16(addrExpr);
    cmdBuffer.Write<uint8>(numBytes);
    cmdBuffer.Write<uint8>(uint8(type));
    cmdBuffer.WriteStringBinary16(conditionExpr ? conditionExpr : "");
    Blob res = RDBG::SendCommand(cmdBuffer, &tempAlloc);

    RDBG_Id bid = 0;
    if (RDBG::GetResult(res) == RDBG_COMMAND_RESULT_OK)
        res.Read<RDBG_Id>(&bid);

    return bid;
}

bool RDBG::EnableBreakpoint(RDBG_Id bId, bool enable)
{
    if (gRemedyBG.cmdPipe == INVALID_HANDLE_VALUE)
        return 0;

    DEBUG_REMEDYBG_BEGINCOMMAND(RDBG_COMMAND_ENABLE_BREAKPOINT);
    cmdBuffer.Write<rdbg_Id>(bId);
    cmdBuffer.Write<rdbg_Bool>(enable);
    Blob res = RDBG::SendCommand(cmdBuffer, &tempAlloc);
    return RDBG::GetResult(res) == RDBG_COMMAND_RESULT_OK;
}

bool RDBG::SetBreakpointCondition(RDBG_Id bId, const char* conditionExpr)
{
    if (gRemedyBG.cmdPipe == INVALID_HANDLE_VALUE)
        return 0;

    DEBUG_REMEDYBG_BEGINCOMMAND(RDBG_COMMAND_ENABLE_BREAKPOINT);
    cmdBuffer.Write<rdbg_Id>(bId);
    cmdBuffer.WriteStringBinary16(conditionExpr ? conditionExpr : "");
    Blob res = RDBG::SendCommand(cmdBuffer, &tempAlloc);
    return RDBG::GetResult(res) == RDBG_COMMAND_RESULT_OK;
}

bool RDBG::DeleteBreakpoint(RDBG_Id bId)
{
    if (gRemedyBG.cmdPipe == INVALID_HANDLE_VALUE)
        return 0;

    DEBUG_REMEDYBG_BEGINCOMMAND(RDBG_COMMAND_DELETE_BREAKPOINT);
    cmdBuffer.Write<rdbg_Id>(bId);
    Blob res = RDBG::SendCommand(cmdBuffer, &tempAlloc);
    return RDBG::GetResult(res) == RDBG_COMMAND_RESULT_OK;
}

bool RDBG::DeleteAllBreakpoints()
{
    if (gRemedyBG.cmdPipe == INVALID_HANDLE_VALUE)
        return 0;

    DEBUG_REMEDYBG_BEGINCOMMAND(RDBG_COMMAND_DELETE_ALL_BREAKPOINTS);
    Blob res = RDBG::SendCommand(cmdBuffer, &tempAlloc);
    return RDBG::GetResult(res) == RDBG_COMMAND_RESULT_OK;
}

RDBG_Id RDBG::AddWatch(const char* expr, const char* comment, uint8 windowNum)
{
    if (gRemedyBG.cmdPipe == INVALID_HANDLE_VALUE)
        return 0;

    ASSERT(expr);
    DEBUG_REMEDYBG_BEGINCOMMAND(RDBG_COMMAND_ADD_WATCH);
    cmdBuffer.Write<uint8>(windowNum);
    cmdBuffer.WriteStringBinary16(expr);
    cmdBuffer.WriteStringBinary16(comment ? comment : "");
    Blob res = RDBG::SendCommand(cmdBuffer, &tempAlloc);

    RDBG_Id wid = 0;
    if (RDBG::GetResult(res) == RDBG_COMMAND_RESULT_OK)
        res.Read<RDBG_Id>(&wid);
    return wid;
}

RDBG_Id RDBG::DeleteWatch(RDBG_Id wId)
{
    if (gRemedyBG.cmdPipe == INVALID_HANDLE_VALUE)
        return 0;

    ASSERT(wId);
    DEBUG_REMEDYBG_BEGINCOMMAND(RDBG_COMMAND_DELETE_WATCH);
    cmdBuffer.Write<rdbg_Id>(wId);
    Blob res = RDBG::SendCommand(cmdBuffer, &tempAlloc);

    RDBG_Id wid = 0;
    if (RDBG::GetResult(res) == RDBG_COMMAND_RESULT_OK)
        res.Read<RDBG_Id>(&wid);
    return wid;
}

bool RDBG::DeleteAllWatches()
{
    if (gRemedyBG.cmdPipe == INVALID_HANDLE_VALUE)
        return 0;

    DEBUG_REMEDYBG_BEGINCOMMAND(RDBG_COMMAND_DELETE_ALL_WATCHES);
    Blob res = RDBG::SendCommand(cmdBuffer, &tempAlloc);
    return RDBG::GetResult(res) == RDBG_COMMAND_RESULT_OK;
}

#endif // PLATFORM_WINDOWS

    #elif PLATFORM_POSIX
//----------------------------------------------------------------------------------------------------------------------
// DebugClang.cpp


#if COMPILER_CLANG && !COMPILER_MSVC

#include <unwind.h> // _Unwind_Backtrace
#include <dlfcn.h>  // dladdr
#include <cxxabi.h> // __cxa_demangle

#if PLATFORM_ANDROID || PLATFORM_LINUX
#include <malloc.h>
#elif PLATFORM_APPLE
#include <stdlib.h>    
#endif




#define DEBUG_STACKTRACE_SKIP_FRAMES 1
#define DEBUG_STACKTRACE_HASH_SEED 0x0CCE41BB

struct DebugStacktraceState
{
    void** current;
    void** end;
    uint16 framesToSkip;
    uint16 numFrames;
};

static StaticArray<void*, 16> gDebugStopFuncs;

namespace Debug
{
    static _Unwind_Reason_Code UnwindCallback(_Unwind_Context* context, void* arg)
    {
        DebugStacktraceState* state = reinterpret_cast<DebugStacktraceState*>(arg);

        state->numFrames++;
        if (state->numFrames <= state->framesToSkip)
            return _URC_NO_REASON;

        void* ip = reinterpret_cast<void*>(_Unwind_GetIP(context));
        if (ip) {
            bool endOfStack = false;
            if (gDebugStopFuncs.Count()) {
                void* fn = _Unwind_FindEnclosingFunction(ip);
                endOfStack = gDebugStopFuncs.FindIf([fn](const void* _fn)->bool { return fn == _fn; }) != UINT32_MAX;
            }

            if (state->current == state->end || endOfStack)
            return _URC_END_OF_STACK;
            else
            *state->current++ = ip;
        }
        return _URC_NO_REASON;
    }
}

NO_INLINE uint16 Debug::CaptureStacktrace(void** stackframes, uint16 maxStackframes, uint16 framesToSkip, uint32* pHash)
{
    ASSERT(maxStackframes);
    DebugStacktraceState state {stackframes, stackframes + maxStackframes, framesToSkip};
    _Unwind_Backtrace(Debug::UnwindCallback, &state);
    uint32 numStacktrace = PtrToInt<uint16>((void*)(state.current - stackframes));

    if (pHash)
        *pHash = Hash::Murmur32(stackframes, sizeof(void*)*numStacktrace, DEBUG_STACKTRACE_HASH_SEED);

    return numStacktrace;
}

void Debug::ResolveStacktrace(uint16 numStacktrace, void* const* stackframes, DebugStacktraceEntry* entries)
{
    for (uint16 i = 0; i < numStacktrace; i++) {
        memset(&entries[i], 0x0, sizeof(entries[i]));

        const void* addr = stackframes[i];
        Dl_info info;
        if (dladdr(addr, &info)) {
            Str::Copy(entries[i].filename, sizeof(entries[i].filename), info.dli_fname);
            Str::Copy(entries[i].name, sizeof(entries[i].name), info.dli_sname);

            int status = 0;
            char* demangled = abi::__cxa_demangle(entries[i].name, 0, 0, &status);
            if (status == 0)
                Str::Copy(entries[i].name, sizeof(entries[i].name), demangled);
            ::free(demangled);
        }
    }
}

void Debug::StacktraceSaveStopPoint(void* funcPtr)
{
    ASSERT(funcPtr);
    ASSERT_MSG(gDebugStopFuncs.FindIf([funcPtr](const void* fn)->bool { return funcPtr == fn; }) == UINT32_MAX, 
               "Function pointer is already saved");
    gDebugStopFuncs.Push(funcPtr);
}

#endif // COMPILER_CLANG


    #endif
#endif 

static bool gDebugCaptureStacktraceForFiberProtector;

void Debug::PrintLine(const char* text)
{
    #if PLATFORM_WINDOWS
    OS::Win32PrintToDebugger(text);
    OS::Win32PrintToDebugger("\n");
    #elif PLATFORM_ANDROID
    OS::AndroidPrintToLog(OSAndroidLogType::Debug, CONFIG_APP_NAME, text);
    #else
    puts(text);
    #endif
}

void Debug::PrintLineFmt(const char* fmt, ...)
{
    char text[1024];
    va_list args;
    va_start(args, fmt);
    [[maybe_unused]] uint32 len = Str::PrintFmtArgs(text, sizeof(text)-1, fmt, args);
    va_end(args);

    #if PLATFORM_WINDOWS
    text[len] = '\n';
    text[len+1] = '\0';
    OS::Win32PrintToDebugger(text);
    #elif PLATFORM_ANDROID
    OS::AndroidPrintToLog(OSAndroidLogType::Debug, CONFIG_APP_NAME, text);
    #else
    puts(text);
    #endif
}

void Debug::SetCaptureStacktraceForFiberProtector(bool capture)
{
    gDebugCaptureStacktraceForFiberProtector = capture;
}

#if CONFIG_ENABLE_ASSERT
static constexpr uint16 kDebugMaxFiberProtectorStackframes = 8;

using DebugFiberScopeProtectorCallbackPair = Pair<DebugFiberScopeProtectorCallback, void*>;
struct DebugFiberProtector
{
    StaticArray<DebugFiberScopeProtectorCallbackPair, 4> callbacks;
};

struct DebugFiberProtectorThreadContext
{
    struct Item 
    {
        const char* name;
        void* stackframes[kDebugMaxFiberProtectorStackframes];
        uint16 numStackframes;
        uint16 id;
    };

    ~DebugFiberProtectorThreadContext()
    {
        items.Free();
    }

    uint16 idGen;
    Array<Item> items;
};
 
static DebugFiberProtector gFiberProtector;
NO_INLINE static DebugFiberProtectorThreadContext& FiberProtectorCtx() 
{ 
    static thread_local DebugFiberProtectorThreadContext fiberProtectorCtx;
    return fiberProtectorCtx; 
}

void Debug::FiberScopeProtector_RegisterCallback(DebugFiberScopeProtectorCallback callback, void* userData)
{
    ASSERT_MSG(gFiberProtector.callbacks.FindIf([callback](const DebugFiberScopeProtectorCallbackPair& p) { return p.first == callback; }) == UINT32_MAX,
               "Callback already added");
    gFiberProtector.callbacks.Push(DebugFiberScopeProtectorCallbackPair(callback, userData));
}

INLINE bool debugFiberScopeProtector_IsInFiber()
{
    bool inFiber = false;
    for (const DebugFiberScopeProtectorCallbackPair p : gFiberProtector.callbacks)
        inFiber |= p.first(p.second);
    return inFiber;
}

uint16 Debug::FiberScopeProtector_Push(const char* name)
{
    if (debugFiberScopeProtector_IsInFiber()) {
        ASSERT(name);
        DebugFiberProtectorThreadContext::Item* item = FiberProtectorCtx().items.Push();
        memset(item, 0x0, sizeof(*item));
        item->name = name;
        if (gDebugCaptureStacktraceForFiberProtector) 
            item->numStackframes = Debug::CaptureStacktrace(item->stackframes, kDebugMaxFiberProtectorStackframes, 2);
        uint16 id = ++FiberProtectorCtx().idGen;
        if (id == 0)
            id = 1;
        item->id = id;
        return id;
    }
    return 0;
}

void Debug::FiberScopeProtector_Pop(uint16 id)
{
    if (id == 0)
        return;
    
    ASSERT_MSG(debugFiberScopeProtector_IsInFiber(), "Item was pushed in the fiber, but not popping in any fibers");
    ASSERT(FiberProtectorCtx().items.Count());

    uint32 index = FiberProtectorCtx().items.FindIf([id](const DebugFiberProtectorThreadContext::Item& item) { return item.id == id; });
    ASSERT_MSG(index != UINT32_MAX, "Something went wrong. Very likely, you are not popping the protected item in the correct thread");
    FiberProtectorCtx().items.Pop(index);
}

void Debug::FiberScopeProtector_Check()
{
    if (FiberProtectorCtx().items.Count()) {
        Debug::PrintLineFmt("Found %u protected items in the fiber that are not destructed in the scope:", FiberProtectorCtx().items.Count());
        
        DebugStacktraceEntry stacktraces[kDebugMaxFiberProtectorStackframes];
        for (const DebugFiberProtectorThreadContext::Item& item : FiberProtectorCtx().items) {
            Debug::PrintLineFmt("\t%s:", item.name);
            if (item.numStackframes) {
                Debug::ResolveStacktrace(item.numStackframes, item.stackframes, stacktraces);
                for (uint16 i = 0; i < item.numStackframes; i++) {
                    Debug::PrintLineFmt("\t\t%s(%u): %s", stacktraces[i].filename, stacktraces[i].line, stacktraces[i].name);
                }
            }
        }

        DEBUG_BREAK();
    }
}
#else
void Debug::FiberScopeProtector_RegisterCallback(DebugFiberScopeProtectorCallback, void*) {}
uint16 Debug::FiberScopeProtector_Push(const char*) { return 0; }
void Debug::FiberScopeProtector_Pop(uint16) {}
void Debug::FiberScopeProtector_Check() {}
#endif  // CONFIG_ENABLE_ASSERT




#if CPU_X86 && defined(__SSE4_2__)
#if COMPILER_MSVC
#include <intrin.h>     // _mm_crc32_u64
#else
#include <immintrin.h>
#endif
#endif


/* This file is derived from crc32.c from the zlib-1.1.3 distribution
 * by Jean-loup Gailly and Mark Adler.
 */

/* crc32.c -- compute the CRC-32 of a data stream
 * Copyright (C) 1995-1998 Mark Adler
 * For conditions of distribution and use, see copyright notice in zlib.h
 */


/* ========================================================================
*  Table of CRC-32's of all single-byte values (made by make_crc_table)
*/
static const uint32 HASH_CRC_TABLE[256] = {
    0x00000000L, 0x77073096L, 0xee0e612cL, 0x990951baL, 0x076dc419L, 0x706af48fL, 0xe963a535L,
    0x9e6495a3L, 0x0edb8832L, 0x79dcb8a4L, 0xe0d5e91eL, 0x97d2d988L, 0x09b64c2bL, 0x7eb17cbdL,
    0xe7b82d07L, 0x90bf1d91L, 0x1db71064L, 0x6ab020f2L, 0xf3b97148L, 0x84be41deL, 0x1adad47dL,
    0x6ddde4ebL, 0xf4d4b551L, 0x83d385c7L, 0x136c9856L, 0x646ba8c0L, 0xfd62f97aL, 0x8a65c9ecL,
    0x14015c4fL, 0x63066cd9L, 0xfa0f3d63L, 0x8d080df5L, 0x3b6e20c8L, 0x4c69105eL, 0xd56041e4L,
    0xa2677172L, 0x3c03e4d1L, 0x4b04d447L, 0xd20d85fdL, 0xa50ab56bL, 0x35b5a8faL, 0x42b2986cL,
    0xdbbbc9d6L, 0xacbcf940L, 0x32d86ce3L, 0x45df5c75L, 0xdcd60dcfL, 0xabd13d59L, 0x26d930acL,
    0x51de003aL, 0xc8d75180L, 0xbfd06116L, 0x21b4f4b5L, 0x56b3c423L, 0xcfba9599L, 0xb8bda50fL,
    0x2802b89eL, 0x5f058808L, 0xc60cd9b2L, 0xb10be924L, 0x2f6f7c87L, 0x58684c11L, 0xc1611dabL,
    0xb6662d3dL, 0x76dc4190L, 0x01db7106L, 0x98d220bcL, 0xefd5102aL, 0x71b18589L, 0x06b6b51fL,
    0x9fbfe4a5L, 0xe8b8d433L, 0x7807c9a2L, 0x0f00f934L, 0x9609a88eL, 0xe10e9818L, 0x7f6a0dbbL,
    0x086d3d2dL, 0x91646c97L, 0xe6635c01L, 0x6b6b51f4L, 0x1c6c6162L, 0x856530d8L, 0xf262004eL,
    0x6c0695edL, 0x1b01a57bL, 0x8208f4c1L, 0xf50fc457L, 0x65b0d9c6L, 0x12b7e950L, 0x8bbeb8eaL,
    0xfcb9887cL, 0x62dd1ddfL, 0x15da2d49L, 0x8cd37cf3L, 0xfbd44c65L, 0x4db26158L, 0x3ab551ceL,
    0xa3bc0074L, 0xd4bb30e2L, 0x4adfa541L, 0x3dd895d7L, 0xa4d1c46dL, 0xd3d6f4fbL, 0x4369e96aL,
    0x346ed9fcL, 0xad678846L, 0xda60b8d0L, 0x44042d73L, 0x33031de5L, 0xaa0a4c5fL, 0xdd0d7cc9L,
    0x5005713cL, 0x270241aaL, 0xbe0b1010L, 0xc90c2086L, 0x5768b525L, 0x206f85b3L, 0xb966d409L,
    0xce61e49fL, 0x5edef90eL, 0x29d9c998L, 0xb0d09822L, 0xc7d7a8b4L, 0x59b33d17L, 0x2eb40d81L,
    0xb7bd5c3bL, 0xc0ba6cadL, 0xedb88320L, 0x9abfb3b6L, 0x03b6e20cL, 0x74b1d29aL, 0xead54739L,
    0x9dd277afL, 0x04db2615L, 0x73dc1683L, 0xe3630b12L, 0x94643b84L, 0x0d6d6a3eL, 0x7a6a5aa8L,
    0xe40ecf0bL, 0x9309ff9dL, 0x0a00ae27L, 0x7d079eb1L, 0xf00f9344L, 0x8708a3d2L, 0x1e01f268L,
    0x6906c2feL, 0xf762575dL, 0x806567cbL, 0x196c3671L, 0x6e6b06e7L, 0xfed41b76L, 0x89d32be0L,
    0x10da7a5aL, 0x67dd4accL, 0xf9b9df6fL, 0x8ebeeff9L, 0x17b7be43L, 0x60b08ed5L, 0xd6d6a3e8L,
    0xa1d1937eL, 0x38d8c2c4L, 0x4fdff252L, 0xd1bb67f1L, 0xa6bc5767L, 0x3fb506ddL, 0x48b2364bL,
    0xd80d2bdaL, 0xaf0a1b4cL, 0x36034af6L, 0x41047a60L, 0xdf60efc3L, 0xa867df55L, 0x316e8eefL,
    0x4669be79L, 0xcb61b38cL, 0xbc66831aL, 0x256fd2a0L, 0x5268e236L, 0xcc0c7795L, 0xbb0b4703L,
    0x220216b9L, 0x5505262fL, 0xc5ba3bbeL, 0xb2bd0b28L, 0x2bb45a92L, 0x5cb36a04L, 0xc2d7ffa7L,
    0xb5d0cf31L, 0x2cd99e8bL, 0x5bdeae1dL, 0x9b64c2b0L, 0xec63f226L, 0x756aa39cL, 0x026d930aL,
    0x9c0906a9L, 0xeb0e363fL, 0x72076785L, 0x05005713L, 0x95bf4a82L, 0xe2b87a14L, 0x7bb12baeL,
    0x0cb61b38L, 0x92d28e9bL, 0xe5d5be0dL, 0x7cdcefb7L, 0x0bdbdf21L, 0x86d3d2d4L, 0xf1d4e242L,
    0x68ddb3f8L, 0x1fda836eL, 0x81be16cdL, 0xf6b9265bL, 0x6fb077e1L, 0x18b74777L, 0x88085ae6L,
    0xff0f6a70L, 0x66063bcaL, 0x11010b5cL, 0x8f659effL, 0xf862ae69L, 0x616bffd3L, 0x166ccf45L,
    0xa00ae278L, 0xd70dd2eeL, 0x4e048354L, 0x3903b3c2L, 0xa7672661L, 0xd06016f7L, 0x4969474dL,
    0x3e6e77dbL, 0xaed16a4aL, 0xd9d65adcL, 0x40df0b66L, 0x37d83bf0L, 0xa9bcae53L, 0xdebb9ec5L,
    0x47b2cf7fL, 0x30b5ffe9L, 0xbdbdf21cL, 0xcabac28aL, 0x53b39330L, 0x24b4a3a6L, 0xbad03605L,
    0xcdd70693L, 0x54de5729L, 0x23d967bfL, 0xb3667a2eL, 0xc4614ab8L, 0x5d681b02L, 0x2a6f2b94L,
    0xb40bbe37L, 0xc30c8ea1L, 0x5a05df1bL, 0x2d02ef8dL
};

#define DO1(buf) crc = HASH_CRC_TABLE[((int)crc ^ (*buf++)) & 0xff] ^ (crc >> 8);
#define DO2(buf) \
    DO1(buf);    \
    DO1(buf);
#define DO4(buf) \
    DO2(buf);    \
    DO2(buf);
#define DO8(buf) \
    DO4(buf);    \
    DO4(buf);

uint32 Hash::CRC32(const void* data, size_t len, uint32 seed)
{
    const uint8* buf = (const uint8*)data;
    uint32 crc = seed ^ 0xffffffffL;

    while (len >= 8) {
        DO8(buf);
        len -= 8;
    }

    while (len--) {
        DO1(buf);
    }

    crc ^= 0xffffffffL;

    return crc;
}

#if CPU_X86 && defined(__SSE4_2__)
uint32 Hash::CRC32_x86_Aligned(const void* data, size_t len)
{
    ASSERT_MSG(len % 8 == 0, "Data must be aligned to 8 bytes");
    
    const uint64* M64 = (const uint64*)data;
    uint64 hash = 0;
    len >>= 3;
    for (uint32 i = 0; i < len; ++i)
        hash = _mm_crc32_u64(hash, M64[i]);
    
    return (uint32)hash;
}
#endif

namespace Hash
{
    FORCE_INLINE uint32 rotl32(uint32 x, int8 r)
    {
        return (x << r) | (x >> (32 - r));
    }

    FORCE_INLINE uint64 rotl64(uint64 x, int8 r)
    {
        return (x << r) | (x >> (64 - r));
    }

    #define	ROTL32(x,y)	rotl32(x,y)
    #define ROTL64(x,y)	rotl64(x,y)
    #define BIG_CONSTANT(x) (x##LLU)
    #define HASH_M 0x5bd1e995
    #define HASH_R 24
    #define MMIX(h, k) { k *= HASH_M; k ^= k >> HASH_R; k *= HASH_M; h *= HASH_M; h ^= k; }

    #define getblock(p, i) (p[i])


    FORCE_INLINE uint32 MurmurFmix32(uint32 h)
    {
        h ^= h >> 16;
        h *= 0x85ebca6b;
        h ^= h >> 13;
        h *= 0xc2b2ae35;
        h ^= h >> 16;
    
        return h;
    }

    FORCE_INLINE uint64 MurmurFmix64(uint64 k)
    {
        k ^= k >> 33;
        k *= BIG_CONSTANT(0xff51afd7ed558ccd);
        k ^= k >> 33;
        k *= BIG_CONSTANT(0xc4ceb9fe1a85ec53);
        k ^= k >> 33;
    
        return k;
    }
} // Hash

uint32 Hash::Murmur32(const void * key, uint32 len, uint32 seed)
{
    const uint8 * data = (const uint8*)key;
    const int nblocks = static_cast<int>(len / 4);
    int i;

    uint32 h1 = seed;
    constexpr uint32 c1 = 0xcc9e2d51;
    constexpr uint32 c2 = 0x1b873593;

    auto blocks = reinterpret_cast<const uint32*>(data + nblocks*4);

    for(i = -nblocks; i; i++) {
        uint32 k1 = getblock(blocks,i);
    
        k1 *= c1;
        k1 = ROTL32(k1,15);
        k1 *= c2;
    
        h1 ^= k1;
        h1 = ROTL32(h1,13);
        h1 = h1*5+0xe6546b64;
    }

    auto tail = reinterpret_cast<const uint8*>(data + nblocks*4);
    uint32 k1 = 0;

    switch(len & 3) {
    case 3: k1 ^= tail[2] << 16;
    case 2: k1 ^= tail[1] << 8;
    case 1: k1 ^= tail[0];
        k1 *= c1; k1 = ROTL32(k1,15); k1 *= c2; h1 ^= k1;
    }

    h1 ^= len;
    return MurmurFmix32(h1);
}

HashResult128 Hash::Murmur128(const void * key, size_t len, const uint32 seed)
{
    const uint8 * data = (const uint8*)key;
    const size_t nblocks = len / 16;
    size_t i;

    uint64 h1 = seed;
    uint64 h2 = seed;

    uint64 c1 = BIG_CONSTANT(0x87c37b91114253d5);
    uint64 c2 = BIG_CONSTANT(0x4cf5ad432745937f);

    const uint64 * blocks = (const uint64 *)(data);

    for(i = 0; i < nblocks; i++)
    {
        uint64 k1 = getblock(blocks,i*2+0);
        uint64 k2 = getblock(blocks,i*2+1);
    
        k1 *= c1; k1  = ROTL64(k1,31); k1 *= c2; h1 ^= k1;
        h1 = ROTL64(h1,27); h1 += h2; h1 = h1*5+0x52dce729;
        k2 *= c2; k2  = ROTL64(k2,33); k2 *= c1; h2 ^= k2;
        h2 = ROTL64(h2,31); h2 += h1; h2 = h2*5+0x38495ab5;
    }

    const uint8* tail = reinterpret_cast<const uint8*>(data + nblocks*16);

    uint64 k1 = 0;
    uint64 k2 = 0;

    switch(len & 15)
    {
    case 15: k2 ^= (uint64)(tail[14]) << 48;
    case 14: k2 ^= (uint64)(tail[13]) << 40;
    case 13: k2 ^= (uint64)(tail[12]) << 32;
    case 12: k2 ^= (uint64)(tail[11]) << 24;
    case 11: k2 ^= (uint64)(tail[10]) << 16;
    case 10: k2 ^= (uint64)(tail[ 9]) << 8;
    case  9: k2 ^= (uint64)(tail[ 8]) << 0;
        k2 *= c2; k2  = ROTL64(k2,33); k2 *= c1; h2 ^= k2;
    
    case  8: k1 ^= (uint64)(tail[ 7]) << 56;
    case  7: k1 ^= (uint64)(tail[ 6]) << 48;
    case  6: k1 ^= (uint64)(tail[ 5]) << 40;
    case  5: k1 ^= (uint64)(tail[ 4]) << 32;
    case  4: k1 ^= (uint64)(tail[ 3]) << 24;
    case  3: k1 ^= (uint64)(tail[ 2]) << 16;
    case  2: k1 ^= (uint64)(tail[ 1]) << 8;
    case  1: k1 ^= (uint64)(tail[ 0]) << 0;
        k1 *= c1; k1  = ROTL64(k1,31); k1 *= c2; h1 ^= k1;
    }

    h1 ^= len; h2 ^= len;

    h1 += h2;
    h2 += h1;

    h1 = MurmurFmix64(h1);
    h2 = MurmurFmix64(h2);

    h1 += h2;
    h2 += h1;

    return {
        .h1 = h1,
        .h2 = h2
    };
}

HashMurmur32Incremental::HashMurmur32Incremental(uint32 seed) : 
    mHash(seed),
    mTail(0),
    mCount(0),
    mSize(0)
{
}

HashMurmur32Incremental& HashMurmur32Incremental::AddAny(const void* _data, uint32 _size)
{
    if (!_data || !_size)
        return *this;

    const uint8* key = (const uint8*)_data;
    mSize += _size;
    
    Murmur32MixTail(&key, &_size);
    
    while (_size >= 4)	{
        uint32 k = *((const uint32*)key);
        
        MMIX(mHash, k);
        
        key += 4;
        _size -= 4;
    }
    
    Murmur32MixTail(&key, &_size);
    return *this;
}

HashMurmur32Incremental& HashMurmur32Incremental::AddCStringArray(const char** _strs, uint32 _numStrings)
{
    if (!_strs || !_numStrings) 
        return *this;

    for (uint32 i = 0; i < _numStrings; i++) 
        AddAny(_strs[i], Str::Len(_strs[i]));

    return *this;
}

uint32 HashMurmur32Incremental::Hash()
{
    MMIX(mHash, mTail);
    MMIX(mHash, mSize);
    
    mHash ^= mHash >> 13;
    mHash *= HASH_M;
    mHash ^= mHash >> 15;
    
    return mHash;
}

void HashMurmur32Incremental::Murmur32MixTail(const uint8** pData, uint32* pSize)
{
    uint32 size = *pSize;
    const uint8* data = *pData;
    
    while (size && ((size<4) || mCount)) {
        mTail |= (*data++) << (mCount * 8);
        
        mCount++;
        size--;
        
        if (mCount == 4)	{
            MMIX(mHash, mTail);
            mTail = 0;
            mCount = 0;
        }
    }
    
    *pData = data;
    *pSize = size;
}


FORCE_INLINE uint32 hashTableFibHash(uint32 h, int bits)
{
    uint64 h64 = static_cast<uint64>(h);
    h64 ^= (h64 >> bits);
    return static_cast<uint32>((h64 * 11400714819323198485llu) >> bits);
}

FORCE_INLINE uint32 hashTableCalcBitShift(uint32 n)
{
    uint32 c = 0;
    uint32 un = n;
    while (un > 1) {
        c++;
        un >>= 1;
    }
    return 64 - c;
}

FORCE_INLINE constexpr int hashTableNearestPow2(int n)
{
    n--;
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;
    n++;
    return n;
}

_private::HashTableData* _private::hashtableCreate(uint32 capacity, uint32 valueStride, MemAllocator* alloc)
{
    ASSERT(capacity > 0);
    
    capacity = hashTableNearestPow2(capacity);   
    
    MemSingleShotMalloc<HashTableData> mallocator;
    mallocator.AddMemberArray<uint32>(offsetof(HashTableData, keys), capacity)
              .AddMemberArray<uint8>(offsetof(HashTableData, values), valueStride*capacity);
    HashTableData* tbl = mallocator.Calloc(alloc);
    
    tbl->bitshift = hashTableCalcBitShift(capacity);
    tbl->valueStride = valueStride;
    tbl->count = 0;
    tbl->capacity = capacity;
    
    return tbl;
}

size_t _private::hashtableGetMemoryRequirement(uint32 capacity, uint32 valueStride)
{
    ASSERT(capacity > 0);
    
    capacity = hashTableNearestPow2(capacity);
    MemSingleShotMalloc<HashTableData> mallocator;
    return mallocator.AddMemberArray<uint32>(offsetof(HashTableData, keys), capacity)
                     .AddMemberArray<uint8>(offsetof(HashTableData, values), valueStride*capacity)
                     .GetMemoryRequirement();        
}

void _private::hashtableDestroy(HashTableData* tbl, MemAllocator* alloc)
{
    ASSERT(tbl);
    tbl->count = tbl->capacity = 0;

    MemSingleShotMalloc<HashTableData>::Free(tbl, alloc);
}

bool _private::hashtableGrow(HashTableData** pTbl, MemAllocator* alloc)
{
    HashTableData* tbl = *pTbl;
    HashTableData* newTable = hashtableCreate(tbl->capacity << 1, tbl->valueStride, alloc);
    if (!newTable)
        return false;
    
    for (uint32 i = 0, c = tbl->capacity; i < c; i++) {
        if (tbl->keys[i] > 0) {
            hashtableAdd(newTable, tbl->keys[i], tbl->values + i * tbl->valueStride);
        }
    }
    
    hashtableDestroy(tbl, alloc);
    *pTbl = newTable;
    return true;
}

uint32 _private::hashtableAdd(HashTableData* tbl, uint32 key, const void* value)
{
    uint32 h = _private::hashtableAddKey(tbl, key);
    memcpy(tbl->values + tbl->valueStride * h, value, tbl->valueStride);
    return h;
}

uint32 _private::hashtableAddKey(HashTableData* tbl, uint32 key)
{
    ASSERT(tbl->count < tbl->capacity);
    
    uint32 h = hashTableFibHash(key, tbl->bitshift);
    uint32 cnt = (uint32)tbl->capacity;

    if (tbl->keys[h]) {
        for (uint32 i = 1; i < cnt; i++) {
            uint32 index = (h + i) % cnt;
            if (tbl->keys[index] == 0) {
                h = index;
                break;
            }
        }
    }
    
    ASSERT_MSG(tbl->keys[h] == 0, "No free slot found in the hash-table");
    tbl->keys[h] = key;
    ++tbl->count;
    return h;
}

uint32 _private::hashtableFind(const HashTableData* tbl, uint32 key)
{
    uint32 h = hashTableFibHash(key, tbl->bitshift);
    uint32 cnt = (uint32)tbl->capacity;
    if (tbl->keys[h] == key) {
        return h;
    } else {
        for (uint32 i = 1; i < cnt; i++) {
            uint32 index = (h + i) % cnt;
            if (tbl->keys[index] == key)
                return index;
        }
        
        return INVALID_INDEX;    // Worst case: Not found!
    }
}

void _private::hashtableClear(HashTableData* tbl)
{
    memset(tbl->keys, 0x0, sizeof(uint32) * tbl->capacity);
    tbl->count = 0;
}

_private::HashTableData* _private::hashtableCreateWithBuffer(uint32 capacity, uint32 valueStride, void* buff, size_t size)
{
    ASSERT(capacity > 0);
    
    capacity = hashTableNearestPow2(capacity);   
    
    MemSingleShotMalloc<HashTableData> hashTableBuff;
    hashTableBuff.AddMemberArray<uint32>(offsetof(HashTableData, keys), capacity)
                 .AddMemberArray<uint8>(offsetof(HashTableData, values), valueStride*capacity);
    HashTableData* tbl = hashTableBuff.Calloc(buff, size);
    
    tbl->bitshift = hashTableCalcBitShift(capacity);
    tbl->valueStride = valueStride;
    tbl->count = 0;
    tbl->capacity = capacity;
    
    return tbl;
}

bool _private::hashtableGrowWithBuffer(HashTableData** pTbl, void* buff, size_t size)
{
    HashTableData* tbl = *pTbl;
    HashTableData* newTable = hashtableCreateWithBuffer(tbl->capacity << 1, tbl->valueStride, buff, size);
    if (!newTable)
        return false;
    
    for (uint32 i = 0, c = tbl->capacity; i < c; i++) {
        if (tbl->keys[i] > 0) {
            hashtableAdd(newTable, tbl->keys[i], tbl->values + i * tbl->valueStride);
        }
    }
    
    *pTbl = newTable;
    return true;
}



#define INI_IMPLEMENTATION
#define INI_MALLOC(ctx, size)       Mem::Alloc(size, (MemAllocator*)ctx)
#define INI_FREE(ctx, ptr)          Mem::Free(ptr, (MemAllocator*)ctx)
#define INI_MEMCPY(dst, src, cnt)   memcpy(dst, src, cnt)
#define INI_STRLEN(s)               Str::Len(s)
#define INI_STRNICMP(s1, s2, cnt)   (Str::IsEqualNoCaseCount(s1, s2, cnt) ? 0 : 1)

PRAGMA_DIAGNOSTIC_PUSH()
PRAGMA_DIAGNOSTIC_IGNORED_CLANG_GCC("-Wsign-compare")
//----------------------------------------------------------------------------------------------------------------------
// External/mgustavsson/ini.h

/*
------------------------------------------------------------------------------
          Licensing information can be found at the end of the file.
------------------------------------------------------------------------------

ini.h - v1.2 - Simple ini-file reader for C/C++.

Do this:
    #define INI_IMPLEMENTATION
before you include this file in *one* C/C++ file to create the implementation.
*/

#ifndef ini_h
#define ini_h

#define INI_GLOBAL_SECTION ( 0 )
#define INI_NOT_FOUND ( -1 )

typedef struct ini_t ini_t;

ini_t* ini_create( void* memctx );
ini_t* ini_load( char const* data, void* memctx );

int ini_save( ini_t const* ini, char* data, int size );
void ini_destroy( ini_t* ini );

int ini_section_count( ini_t const* ini );
char const* ini_section_name( ini_t const* ini, int section );

int ini_property_count( ini_t const* ini, int section );
char const* ini_property_name( ini_t const* ini, int section, int property );
char const* ini_property_value( ini_t const* ini, int section, int property );

int ini_find_section( ini_t const* ini, char const* name, int name_length );
int ini_find_property( ini_t const* ini, int section, char const* name, int name_length );

int ini_section_add( ini_t* ini, char const* name, int length );
void ini_property_add( ini_t* ini, int section, char const* name, int name_length, char const* value, int value_length );
void ini_section_remove( ini_t* ini, int section );
void ini_property_remove( ini_t* ini, int section, int property );

void ini_section_name_set( ini_t* ini, int section, char const* name, int length );
void ini_property_name_set( ini_t* ini, int section, int property, char const* name, int length );
void ini_property_value_set( ini_t* ini, int section, int property, char const* value, int length  );

#endif /* ini_h */


/**

ini.h 
=====

Simple ini-file reader for C/C++.


Examples
--------

#### Loading an ini file and retrieving values

    #define INI_IMPLEMENTATION

    #include <stdio.h>
    #include <stdlib.h>

    int main()
        {
        FILE* fp = fopen( "test.ini", "r" );
        fseek( fp, 0, SEEK_END );
        int size = ftell( fp );
        fseek( fp, 0, SEEK_SET );
        char* data = (char*) malloc( size + 1 );
        fread( data, 1, size, fp );
        data[ size ] = '\0';
        fclose( fp );

        ini_t* ini = ini_load( data );
        free( data );
        int second_index = ini_find_property( ini, INI_GLOBAL_SECTION, "SecondSetting" );
        char const* second = ini_property_value( ini, INI_GLOBAL_SECTION, second_index );
        printf( "%s=%s\n", "SecondSetting", second );
        int section = ini_find_section( ini, "MySection" );
        int third_index = ini_find_property( ini, section, "ThirdSetting" );
        char const* third = ini_property_value( ini, section, third_index );
        printf( "%s=%s\n", "ThirdSetting", third );
        ini_destroy( ini );

        return 0;
        }

-----------------------------------------------------------------------------------------------

#### Creating a new ini file

    #define INI_IMPLEMENTATION

    #include <stdio.h>
    #include <stdlib.h>

    int main()
        {       
        ini_t* ini = ini_create();
        ini_property_add( ini, INI_GLOBAL_SECTION, "FirstSetting", "Test" );
        ini_property_add( ini, INI_GLOBAL_SECTION, "SecondSetting", "2" );
        int section = ini_section_add( ini, "MySection" );
        ini_property_add( ini, section, "ThirdSetting", "Three" );

        int size = ini_save( ini, NULL, 0 ); // Find the size needed
        char* data = (char*) malloc( size );
        size = ini_save( ini, data, size ); // Actually save the file
        ini_destroy( ini );

        FILE* fp = fopen( "test.ini", "w" );
        fwrite( data, 1, size, fp );
        fclose( fp );
        free( data );

        return 0;
        }



API Documentation
-----------------

ini.h is a small library for reading classic .ini files. It is a single-header library, and does not need any .lib files 
or other binaries, or any build scripts. To use it, you just include ini.h to get the API declarations. To get the 
definitions, you must include ini.h from *one* single C or C++ file, and #define the symbol `INI_IMPLEMENTATION` before 
you do. 


### Customization

There are a few different things in ini.h which are configurable by #defines. The customizations only affect the 
implementation, so will only need to be defined in the file where you have the #define INI_IMPLEMENTATION.

Note that if all customizations are utilized, ini.h will include no external files whatsoever, which might be useful
if you need full control over what code is being built.


#### Custom memory allocators

To store the internal data structures, ini.h needs to do dynamic allocation by calling `malloc`. Programs might want to 
keep track of allocations done, or use custom defined pools to allocate memory from. ini.h allows for specifying custom 
memory allocation functions for `malloc` and `free`.
This is done with the following code:

    #define INI_IMPLEMENTATION
    #define INI_MALLOC( ctx, size ) ( my_custom_malloc( ctx, size ) )
    #define INI_FREE( ctx, ptr ) ( my_custom_free( ctx, ptr ) )

where `my_custom_malloc` and `my_custom_free` are your own memory allocation/deallocation functions. The `ctx` parameter
is an optional parameter of type `void*`. When `ini_create` or `ini_load` is called, you can pass in a `memctx` 
parameter, which can be a pointer to anything you like, and which will be passed through as the `ctx` parameter to every 
`INI_MALLOC`/`INI_FREE` call. For example, if you are doing memory tracking, you can pass a pointer to your tracking 
data as `memctx`, and in your custom allocation/deallocation function, you can cast the `ctx` param back to the 
right type, and access the tracking data.

If no custom allocator is defined, ini.h will default to `malloc` and `free` from the C runtime library.


#### Custom C runtime function

The library makes use of three additional functions from the C runtime library, and for full flexibility, it allows you 
to substitute them for your own. Here's an example:

    #define INI_IMPLEMENTATION
    #define INI_MEMCPY( dst, src, cnt ) ( my_memcpy_func( dst, src, cnt ) )
    #define INI_STRLEN( s ) ( my_strlen_func( s ) )
    #define INI_STRNICMP( s1, s2, cnt ) ( my_strnicmp_func( s1, s2, cnt ) )

If no custom function is defined, ini.h will default to the C runtime library equivalent.


ini_create
----------
    
    ini_t* ini_create( void* memctx )

Instantiates a new, empty ini structure, which can be manipulated with other API calls, to fill it with data. To save it
out to an ini-file string, use `ini_save`. When no longer needed, it can be destroyed by calling `ini_destroy`.
`memctx` is a pointer to user defined data which will be passed through to the custom INI_MALLOC/INI_FREE calls. It can 
be NULL if no user defined data is needed.


ini_load
--------

    ini_t* ini_load( char const* data, void* memctx )

Parse the zero-terminated string `data` containing an ini-file, and create a new ini_t instance containing the data. 
The instance can be manipulated with other API calls to enumerate sections/properties and retrieve values. When no 
longer needed, it can be destroyed by calling `ini_destroy`. `memctx` is a pointer to user defined data which will be 
passed through to the custom INI_MALLOC/INI_FREE calls. It can be NULL if no user defined data is needed.


ini_save
--------
    
    int ini_save( ini_t const* ini, char* data, int size )

Saves an ini structure as a zero-terminated ini-file string, into the specified buffer. Returns the number of bytes 
written, including the zero terminator. If `data` is NULL, nothing is written, but `ini_save` still returns the number
of bytes it would have written. If the size of `data`, as specified in the `size` parameter, is smaller than that 
required, only part of the ini-file string will be written. `ini_save` still returns the number of bytes it would have
written had the buffer been large enough.


ini_destroy
-----------

    void ini_destroy( ini_t* ini )

Destroy an `ini_t` instance created by calling `ini_load` or `ini_create`, releasing the memory allocated by it. No
further API calls are valid on an `ini_t` instance after calling `ini_destroy` on it.


ini_section_count
-----------------

    int ini_section_count( ini_t const* ini )

Returns the number of sections in an ini file. There's at least one section in an ini file (the global section), but 
there can be many more, each specified in the file by the section name wrapped in square brackets [ ].


ini_section_name
----------------

    char const* ini_section_name( ini_t const* ini, int section )

Returns the name of the section with the specified index. `section` must be non-negative and less than the value 
returned by `ini_section_count`, or `ini_section_name` will return NULL. The defined constant `INI_GLOBAL_SECTION` can
be used to indicate the global section.


ini_property_count
------------------

    int ini_property_count( ini_t const* ini, int section )

Returns the number of properties belonging to the section with the specified index. `section` must be non-negative and 
less than the value returned by `ini_section_count`, or `ini_section_name` will return 0. The defined constant 
`INI_GLOBAL_SECTION` can be used to indicate the global section. Properties are declared in the ini-file on he format
`name=value`.


ini_property_name
-----------------

    char const* ini_property_name( ini_t const* ini, int section, int property )

Returns the name of the property with the specified index `property` in the section with the specified index `section`.
`section` must be non-negative and less than the value returned by `ini_section_count`, and `property` must be 
non-negative and less than the value returned by `ini_property_count`, or `ini_property_name` will return NULL. The 
defined constant `INI_GLOBAL_SECTION` can be used to indicate the global section.


ini_property_value
------------------

    char const* ini_property_value( ini_t const* ini, int section, int property )

Returns the value of the property with the specified index `property` in the section with the specified index `section`.
`section` must be non-negative and less than the value returned by `ini_section_count`, and `property` must be 
non-negative and less than the value returned by `ini_property_count`, or `ini_property_value` will return NULL. The 
defined constant `INI_GLOBAL_SECTION` can be used to indicate the global section.


ini_find_section
----------------

    int ini_find_section( ini_t const* ini, char const* name, int name_length )

Finds the section with the specified name, and returns its index. `name_length` specifies the number of characters in
`name`, which does not have to be zero-terminated. If `name_length` is zero, the length is determined automatically, but
in this case `name` has to be zero-terminated. If no section with the specified name could be found, the value
`INI_NOT_FOUND` is returned.


ini_find_property
-----------------

    int ini_find_property( ini_t const* ini, int section, char const* name, int name_length )

Finds the property with the specified name, within the section with the specified index, and returns the index of the 
property. `name_length` specifies the number of characters in `name`, which does not have to be zero-terminated. If 
`name_length` is zero, the length is determined automatically, but in this case `name` has to be zero-terminated. If no 
property with the specified name could be found within the specified section, the value `INI_NOT_FOUND` is  returned.
`section` must be non-negative and less than the value returned by `ini_section_count`, or `ini_find_property` will 
return `INI_NOT_FOUND`. The defined constant `INI_GLOBAL_SECTION` can be used to indicate the global section.


ini_section_add
---------------

    int ini_section_add( ini_t* ini, char const* name, int length )

Adds a section with the specified name, and returns the index it was added at. There is no check done to see if a 
section with the specified name already exists - multiple sections of the same name are allowed. `length` specifies the 
number of characters in `name`, which does not have to be zero-terminated. If `length` is zero, the length is determined 
automatically, but in this case `name` has to be zero-terminated.


ini_property_add
----------------
    
    void ini_property_add( ini_t* ini, int section, char const* name, int name_length, char const* value, int value_length )

Adds a property with the specified name and value to the specified section, and returns the index it was added at. There 
is no check done to see if a property with the specified name already exists - multiple properties of the same name are 
allowed. `name_length` and `value_length` specifies the number of characters in `name` and `value`, which does not have 
to be zero-terminated. If `name_length` or `value_length` is zero, the length is determined automatically, but in this 
case `name`/`value` has to be zero-terminated. `section` must be non-negative and less than the value returned by
`ini_section_count`, or the property will not be added. The defined constant `INI_GLOBAL_SECTION` can be used to 
indicate the global section.


ini_section_remove
------------------

    void ini_section_remove( ini_t* ini, int section )

Removes the section with the specified index, and all properties within it. `section` must be non-negative and less than 
the value returned by `ini_section_count`. The defined constant `INI_GLOBAL_SECTION` can be used to indicate the global 
section. Note that removing a section will shuffle section indices, so that section indices you may have stored will no 
longer indicate the same section as it did before the remove. Use the find functions to update your indices.


ini_property_remove
-------------------

    void ini_property_remove( ini_t* ini, int section, int property )

Removes the property with the specified index from the specified section. `section` must be non-negative and less than 
the value returned by `ini_section_count`, and `property` must be non-negative and less than the value returned by 
`ini_property_count`. The defined constant `INI_GLOBAL_SECTION` can be used to indicate the global section. Note that 
removing a property will shuffle property indices within the specified section, so that property indices you may have 
stored will no longer indicate the same property as it did before the remove. Use the find functions to update your 
indices.


ini_section_name_set
--------------------

    void ini_section_name_set( ini_t* ini, int section, char const* name, int length )

Change the name of the section with the specified index. `section` must be non-negative and less than the value returned 
by `ini_section_count`. The defined constant `INI_GLOBAL_SECTION` can be used to indicate the global section. `length` 
specifies the number of characters in `name`, which does not have to be zero-terminated. If `length` is zero, the length 
is determined automatically, but in this case `name` has to be zero-terminated.


ini_property_name_set
---------------------

    void ini_property_name_set( ini_t* ini, int section, int property, char const* name, int length )

Change the name of the property with the specified index in the specified section. `section` must be non-negative and 
less than the value returned by `ini_section_count`, and `property` must be non-negative and less than the value 
returned by `ini_property_count`. The defined constant `INI_GLOBAL_SECTION` can be used to indicate the global section.
`length` specifies the number of characters in `name`, which does not have to be zero-terminated. If `length` is zero, 
the length is determined automatically, but in this case `name` has to be zero-terminated.


ini_property_value_set
----------------------

    void ini_property_value_set( ini_t* ini, int section, int property, char const* value, int length  )

Change the value of the property with the specified index in the specified section. `section` must be non-negative and 
less than the value returned by `ini_section_count`, and `property` must be non-negative and less than the value 
returned by `ini_property_count`. The defined constant `INI_GLOBAL_SECTION` can be used to indicate the global section.
`length` specifies the number of characters in `value`, which does not have to be zero-terminated. If `length` is zero, 
the length is determined automatically, but in this case `value` has to be zero-terminated.

*/


/*
----------------------
    IMPLEMENTATION
----------------------
*/

#ifdef INI_IMPLEMENTATION
#undef INI_IMPLEMENTATION

#define INITIAL_CAPACITY ( 256 )

#undef _CRT_NONSTDC_NO_DEPRECATE 
#define _CRT_NONSTDC_NO_DEPRECATE 
#undef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include <stddef.h>

#ifndef INI_MALLOC
    #include <stdlib.h>
    #define INI_MALLOC( ctx, size ) ( malloc( size ) )
    #define INI_FREE( ctx, ptr ) ( free( ptr ) )
#endif

#ifndef INI_MEMCPY
    #include <string.h>
    #define INI_MEMCPY( dst, src, cnt ) ( memcpy( dst, src, cnt ) )
#endif 

#ifndef INI_STRLEN
    #include <string.h>
    #define INI_STRLEN( s ) ( strlen( s ) )
#endif 

#ifndef INI_STRNICMP
    #ifdef _WIN32
        #include <string.h>
        #define INI_STRNICMP( s1, s2, cnt ) ( strnicmp( s1, s2, cnt ) )
    #else                           
        #include <string.h>         
        #define INI_STRNICMP( s1, s2, cnt ) ( strncasecmp( s1, s2, cnt ) )        
    #endif
#endif 


struct ini_internal_section_t
    {
    char name[ 32 ];
    char* name_large;
    };


struct ini_internal_property_t
    {
    int section;
    char name[ 32 ];
    char* name_large;
    char value[ 64 ];
    char* value_large;
    };


struct ini_t
    {
    struct ini_internal_section_t* sections;
    int section_capacity;
    int section_count;

    struct ini_internal_property_t* properties;
    int property_capacity;
    int property_count;

    void* memctx;
    };


static int ini_internal_property_index( ini_t const* ini, int section, int property )
    {
    int i;
    int p;

    if( ini && section >= 0 && section < ini->section_count )
        {
        p = 0;
        for( i = 0; i < ini->property_count; ++i )
            {
            if( ini->properties[ i ].section == section )
                {
                if( p == property ) return i;
                ++p;
                }
            }
        }

    return INI_NOT_FOUND;
    }


ini_t* ini_create( void* memctx )
    {
    ini_t* ini;

    ini = (ini_t*) INI_MALLOC( memctx, sizeof( ini_t ) );
    ini->memctx = memctx;
    ini->sections = (struct ini_internal_section_t*) INI_MALLOC( ini->memctx, INITIAL_CAPACITY * sizeof( ini->sections[ 0 ] ) );
    ini->section_capacity = INITIAL_CAPACITY;
    ini->section_count = 1; /* global section */
    ini->sections[ 0 ].name[ 0 ] = '\0'; 
    ini->sections[ 0 ].name_large = 0;
    ini->properties = (struct ini_internal_property_t*) INI_MALLOC( ini->memctx, INITIAL_CAPACITY * sizeof( ini->properties[ 0 ] ) );
    ini->property_capacity = INITIAL_CAPACITY;
    ini->property_count = 0;
    return ini;
    }


ini_t* ini_load( char const* data, void* memctx )
    {
    ini_t* ini;
    char const* ptr;
    int s;
    char const* start;
    char const* start2;
    int l;

    ini = ini_create( memctx );

    ptr = data;
    if( ptr )
        {
        s = 0;
        while( *ptr )
            {
            /* trim leading whitespace */
            while( *ptr && *ptr <=' ' )
                ++ptr;
            
            /* done? */
            if( !*ptr ) break;

            /* comment */
            else if( *ptr == ';' || *ptr == '#')
                {
                while( *ptr && *ptr !='\n' )
                    ++ptr;
                }
            /* section */
            else if( *ptr == '[' )
                {
                ++ptr;
                start = ptr;
                while( *ptr && *ptr !=']' && *ptr != '\n' )
                    ++ptr;

                if( *ptr == ']' )
                    {
                    s = ini_section_add( ini, start, (int)( ptr - start) );
                    ++ptr;
                    }
                }
            /* property */
            else
                {
                start = ptr;
                while( *ptr && *ptr !='=' && *ptr != '\n' )
                    ++ptr;

                if( *ptr == '=' )
                    {
                    l = (int)( ptr - start);
                    ++ptr;
                    while( *ptr && *ptr <= ' ' && *ptr != '\n' ) 
                        ptr++;
                    start2 = ptr;
                    while( *ptr && *ptr != '\n' )
                        ++ptr;
                    while( *(--ptr) <= ' ' ) 
                        (void)ptr;
                    ptr++;
                    ini_property_add( ini, s, start, l, start2, (int)( ptr - start2) );
                    }
                }
            }
        }   

    return ini;
    }


int ini_save( ini_t const* ini, char* data, int size )
    {
    int s;
    int p;
    int i;
    int l;
    char* n;
    int pos;

    if( ini )
        {
        pos = 0;
        for( s = 0; s < ini->section_count; ++s )
            {
            n = ini->sections[ s ].name_large ? ini->sections[ s ].name_large : ini->sections[ s ].name;
            l = (int) INI_STRLEN( n );
            if( l > 0 )
                {
                if( data && pos < size ) data[ pos ] = '[';
                ++pos;
                for( i = 0; i < l; ++i )
                    {
                    if( data && pos < size ) data[ pos ] = n[ i ];
                    ++pos;
                    }
                if( data && pos < size ) data[ pos ] = ']';
                ++pos;
                if( data && pos < size ) data[ pos ] = '\n';
                ++pos;
                }

            for( p = 0; p < ini->property_count; ++p )
                {
                if( ini->properties[ p ].section == s )
                    {
                    n = ini->properties[ p ].name_large ? ini->properties[ p ].name_large : ini->properties[ p ].name;
                    l = (int) INI_STRLEN( n );
                    for( i = 0; i < l; ++i )
                        {
                        if( data && pos < size ) data[ pos ] = n[ i ];
                        ++pos;
                        }
                    if( data && pos < size ) data[ pos ] = '=';
                    ++pos;
                    n = ini->properties[ p ].value_large ? ini->properties[ p ].value_large : ini->properties[ p ].value;
                    l = (int) INI_STRLEN( n );
                    for( i = 0; i < l; ++i )
                        {
                        if( data && pos < size ) data[ pos ] = n[ i ];
                        ++pos;
                        }
                    if( data && pos < size ) data[ pos ] = '\n';
                    ++pos;
                    }
                }

            if( pos > 0 )
                {
                if( data && pos < size ) data[ pos ] = '\n';
                ++pos;
                }
            }

        if( data && pos < size ) data[ pos ] = '\0';
        ++pos;

        return pos;
        }

    return 0;
    }


void ini_destroy( ini_t* ini )
    {
    int i;

    if( ini )
        {
        for( i = 0; i < ini->property_count; ++i )
            {
            if( ini->properties[ i ].value_large ) INI_FREE( ini->memctx, ini->properties[ i ].value_large );
            if( ini->properties[ i ].name_large ) INI_FREE( ini->memctx, ini->properties[ i ].name_large );
            }
        for( i = 0; i < ini->section_count; ++i )
            if( ini->sections[ i ].name_large ) INI_FREE( ini->memctx, ini->sections[ i ].name_large );
        INI_FREE( ini->memctx, ini->properties );
        INI_FREE( ini->memctx, ini->sections );
        INI_FREE( ini->memctx, ini );
        }
    }


int ini_section_count( ini_t const* ini )
    {
    if( ini ) return ini->section_count;
    return 0;
    }


char const* ini_section_name( ini_t const* ini, int section )
    {
    if( ini && section >= 0 && section < ini->section_count )
        return ini->sections[ section ].name_large ? ini->sections[ section ].name_large : ini->sections[ section ].name;

    return NULL;
    }


int ini_property_count( ini_t const* ini, int section )
    {
    int i;
    int count;

    if( ini )
        {
        count = 0;
        for( i = 0; i < ini->property_count; ++i )
            {
            if( ini->properties[ i ].section == section ) ++count;
            }
        return count;
        }

    return 0;
    }


char const* ini_property_name( ini_t const* ini, int section, int property )
    {
    int p;

    if( ini && section >= 0 && section < ini->section_count )
        {
        p = ini_internal_property_index( ini, section, property );
        if( p != INI_NOT_FOUND )
            return ini->properties[ p ].name_large ? ini->properties[ p ].name_large : ini->properties[ p ].name;
        }

    return NULL;
    }


char const* ini_property_value( ini_t const* ini, int section, int property )
    {
    int p;

    if( ini && section >= 0 && section < ini->section_count )
        {
        p = ini_internal_property_index( ini, section, property );
        if( p != INI_NOT_FOUND )
            return ini->properties[ p ].value_large ? ini->properties[ p ].value_large : ini->properties[ p ].value;
        }

    return NULL;
    }


int ini_find_section( ini_t const* ini, char const* name, int name_length )
    {
    int i;

    if( ini && name )
        {
        if( name_length <= 0 ) name_length = (int) INI_STRLEN( name );
        for( i = 0; i < ini->section_count; ++i )
            {
            char const* const other = 
                ini->sections[ i ].name_large ? ini->sections[ i ].name_large : ini->sections[ i ].name;
            if( INI_STRNICMP( name, other, name_length ) == 0 )
                return i;
            }
        }

    return INI_NOT_FOUND;
    }


int ini_find_property( ini_t const* ini, int section, char const* name, int name_length )
    {
    int i;
    int c;

    if( ini && name && section >= 0 && section < ini->section_count)
        {
        if( name_length <= 0 ) name_length = (int) INI_STRLEN( name );
        c = 0;
        for( i = 0; i < ini->property_capacity; ++i )
            {
            if( ini->properties[ i ].section == section )
                {
                char const* const other = 
                    ini->properties[ i ].name_large ? ini->properties[ i ].name_large : ini->properties[ i ].name;
                if( INI_STRNICMP( name, other, name_length ) == 0 )
                    return c;
                ++c;
                }
            }
        }

    return INI_NOT_FOUND;
    }


int ini_section_add( ini_t* ini, char const* name, int length )
    {
    struct ini_internal_section_t* new_sections;
    
    if( ini && name )
        {
        if( length <= 0 ) length = (int) INI_STRLEN( name );
        if( ini->section_count >= ini->section_capacity )
            {
            ini->section_capacity *= 2;
            new_sections = (struct ini_internal_section_t*) INI_MALLOC( ini->memctx, 
                ini->section_capacity * sizeof( ini->sections[ 0 ] ) );
            INI_MEMCPY( new_sections, ini->sections, ini->section_count * sizeof( ini->sections[ 0 ] ) );
            INI_FREE( ini->memctx, ini->sections );
            ini->sections = new_sections;
            }

        ini->sections[ ini->section_count ].name_large = 0;
        if( length + 1 >= sizeof( ini->sections[ 0 ].name ) )
            {
            ini->sections[ ini->section_count ].name_large = (char*) INI_MALLOC( ini->memctx, (size_t) length + 1 );
            INI_MEMCPY( ini->sections[ ini->section_count ].name_large, name, (size_t) length );
            ini->sections[ ini->section_count ].name_large[ length ] = '\0';
            }
        else
            {
            INI_MEMCPY( ini->sections[ ini->section_count ].name, name, (size_t) length );
            ini->sections[ ini->section_count ].name[ length ] = '\0';
            }

        return ini->section_count++;
        }
    return INI_NOT_FOUND;
    }


void ini_property_add( ini_t* ini, int section, char const* name, int name_length, char const* value, int value_length )
    {
    struct ini_internal_property_t* new_properties;

    if( ini && name && section >= 0 && section < ini->section_count )
        {
        if( name_length <= 0 ) name_length = (int) INI_STRLEN( name );
        if( value_length <= 0 ) value_length = (int) INI_STRLEN( value );

        if( ini->property_count >= ini->property_capacity )
            {

            ini->property_capacity *= 2;
            new_properties = (struct ini_internal_property_t*) INI_MALLOC( ini->memctx, 
                ini->property_capacity * sizeof( ini->properties[ 0 ] ) );
            INI_MEMCPY( new_properties, ini->properties, ini->property_count * sizeof( ini->properties[ 0 ] ) );
            INI_FREE( ini->memctx, ini->properties );
            ini->properties = new_properties;
            }
        
        ini->properties[ ini->property_count ].section = section;
        ini->properties[ ini->property_count ].name_large = 0;
        ini->properties[ ini->property_count ].value_large = 0;

        if( name_length + 1 >= sizeof( ini->properties[ 0 ].name ) )
            {
            ini->properties[ ini->property_count ].name_large = (char*) INI_MALLOC( ini->memctx, (size_t) name_length + 1 );
            INI_MEMCPY( ini->properties[ ini->property_count ].name_large, name, (size_t) name_length );
            ini->properties[ ini->property_count ].name_large[ name_length ] = '\0';
            }
        else
            {
            INI_MEMCPY( ini->properties[ ini->property_count ].name, name, (size_t) name_length );
            ini->properties[ ini->property_count ].name[ name_length ] = '\0';
            }

        if( value_length + 1 >= sizeof( ini->properties[ 0 ].value ) )
            {
            ini->properties[ ini->property_count ].value_large = (char*) INI_MALLOC( ini->memctx, (size_t) value_length + 1 );
            INI_MEMCPY( ini->properties[ ini->property_count ].value_large, value, (size_t) value_length );
            ini->properties[ ini->property_count ].value_large[ value_length ] = '\0';
            }
        else
            {
            INI_MEMCPY( ini->properties[ ini->property_count ].value, value, (size_t) value_length );
            ini->properties[ ini->property_count ].value[ value_length ] = '\0';
            }

        ++ini->property_count;
        }
    }


void ini_section_remove( ini_t* ini, int section )
    {
    int p;

    if( ini && section >= 0 && section < ini->section_count )
        {
        if( ini->sections[ section ].name_large ) INI_FREE( ini->memctx, ini->sections[ section ].name_large );
        for( p = ini->property_count - 1; p >= 0; --p ) 
            {
            if( ini->properties[ p ].section == section )
                {
                if( ini->properties[ p ].value_large ) INI_FREE( ini->memctx, ini->properties[ p ].value_large );
                if( ini->properties[ p ].name_large ) INI_FREE( ini->memctx, ini->properties[ p ].name_large );
                ini->properties[ p ] = ini->properties[ --ini->property_count ];
                }
            }

        ini->sections[ section ] = ini->sections[ --ini->section_count  ];
        
        for( p = 0; p < ini->property_count; ++p ) 
            {
            if( ini->properties[ p ].section == ini->section_count )
                ini->properties[ p ].section = section;
            }
        }
    }


void ini_property_remove( ini_t* ini, int section, int property )
    {
    int p;

    if( ini && section >= 0 && section < ini->section_count )
        {
        p = ini_internal_property_index( ini, section, property );
        if( p != INI_NOT_FOUND )
            {
            if( ini->properties[ p ].value_large ) INI_FREE( ini->memctx, ini->properties[ p ].value_large );
            if( ini->properties[ p ].name_large ) INI_FREE( ini->memctx, ini->properties[ p ].name_large );
            ini->properties[ p ] = ini->properties[ --ini->property_count  ];
            return;
            }
        }
    }


void ini_section_name_set( ini_t* ini, int section, char const* name, int length )
    {
    if( ini && name && section >= 0 && section < ini->section_count )
        {
        if( length <= 0 ) length = (int) INI_STRLEN( name );
        if( ini->sections[ section ].name_large ) INI_FREE( ini->memctx, ini->sections[ section ].name_large );
        ini->sections[ section ].name_large = 0;
        
        if( length + 1 >= sizeof( ini->sections[ 0 ].name ) )
            {
            ini->sections[ section ].name_large = (char*) INI_MALLOC( ini->memctx, (size_t) length + 1 );
            INI_MEMCPY( ini->sections[ section ].name_large, name, (size_t) length );
            ini->sections[ section ].name_large[ length ] = '\0';
            }
        else
            {
            INI_MEMCPY( ini->sections[ section ].name, name, (size_t) length );
            ini->sections[ section ].name[ length ] = '\0';
            }
        }
    }


void ini_property_name_set( ini_t* ini, int section, int property, char const* name, int length )
    {
    int p;

    if( ini && name && section >= 0 && section < ini->section_count )
        {
        if( length <= 0 ) length = (int) INI_STRLEN( name );
        p = ini_internal_property_index( ini, section, property );
        if( p != INI_NOT_FOUND )
            {
            if( ini->properties[ p ].name_large ) INI_FREE( ini->memctx, ini->properties[ p ].name_large );
            ini->properties[ ini->property_count ].name_large = 0;

            if( length + 1 >= sizeof( ini->properties[ 0 ].name ) )
                {
                ini->properties[ p ].name_large = (char*) INI_MALLOC( ini->memctx, (size_t) length + 1 );
                INI_MEMCPY( ini->properties[ p ].name_large, name, (size_t) length );
                ini->properties[ p ].name_large[ length ] = '\0';
                }
            else
                {
                INI_MEMCPY( ini->properties[ p ].name, name, (size_t) length );
                ini->properties[ p ].name[ length ] = '\0';
                }
            }
        }
    }


void ini_property_value_set( ini_t* ini, int section, int property, char const* value, int length )
    {
    int p;

    if( ini && value && section >= 0 && section < ini->section_count )
        {
        if( length <= 0 ) length = (int) INI_STRLEN( value );
        p = ini_internal_property_index( ini, section, property );
        if( p != INI_NOT_FOUND )
            {
            if( ini->properties[ p ].value_large ) INI_FREE( ini->memctx, ini->properties[ p ].value_large );
            ini->properties[ ini->property_count ].value_large = 0;

            if( length + 1 >= sizeof( ini->properties[ 0 ].value ) )
                {
                ini->properties[ p ].value_large = (char*) INI_MALLOC( ini->memctx, (size_t) length + 1 );
                INI_MEMCPY( ini->properties[ p ].value_large, value, (size_t) length );
                ini->properties[ p ].value_large[ length ] = '\0';
                }
            else
                {
                INI_MEMCPY( ini->properties[ p ].value, value, (size_t) length );
                ini->properties[ p ].value[ length ] = '\0';
                }
            }
        }
    }


#endif /* INI_IMPLEMENTATION */

/*

contributors:
    Randy Gaul (copy-paste bug in ini_property_value_set)
    Branimir Karadzic (INI_STRNICMP bugfix)

revision history:
    1.2     using strnicmp for correct length compares, fixed copy-paste bug in ini_property_value_set
    1.1     customization, added documentation, cleanup
    1.0     first publicly released version

*/

/*
------------------------------------------------------------------------------

This software is available under 2 licenses - you may choose the one you like.

------------------------------------------------------------------------------

ALTERNATIVE A - MIT License

Copyright (c) 2015 Mattias Gustavsson

Permission is hereby granted, free of charge, to any person obtaining a copy of 
this software and associated documentation files (the "Software"), to deal in 
the Software without restriction, including without limitation the rights to 
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies 
of the Software, and to permit persons to whom the Software is furnished to do 
so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all 
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE 
SOFTWARE.

------------------------------------------------------------------------------

ALTERNATIVE B - Public Domain (www.unlicense.org)

This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or distribute this 
software, either in source code form or as a compiled binary, for any purpose, 
commercial or non-commercial, and by any means.

In jurisdictions that recognize copyright laws, the author or authors of this 
software dedicate any and all copyright interest in the software to the public 
domain. We make this dedication for the benefit of the public at large and to 
the detriment of our heirs and successors. We intend this dedication to be an 
overt act of relinquishment in perpetuity of all present and future rights to 
this software under copyright law.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN 
ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION 
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

------------------------------------------------------------------------------
*/

PRAGMA_DIAGNOSTIC_POP()

typedef struct ini_t ini_t;

INIFileContext INIFile::Create(MemAllocator* alloc)
{
    return INIFileContext { .ini = ini_create(alloc) };
}

INIFileContext INIFile::Load(const char* filepath, MemAllocator* alloc)
{
    ASSERT_MSG(alloc->GetType() != MemAllocatorType::Temp, "alloc cannot be temp. Because the code below also has temp alloc and breaks the stack");

    File f;

    MemTempAllocator tmpAlloc;
    Blob blob(&tmpAlloc);
    if (f.Open(filepath, FileOpenFlags::Read | FileOpenFlags::SeqScan)) {
        size_t size = f.GetSize();
        blob.Reserve(size + 1);
        f.Read(const_cast<void*>(blob.Data()), size);
        blob.SetSize(size);
        blob.Write<char>('\0');
        f.Close();
    }
    else {
        return INIFileContext {};
    }

    void* data;
    size_t size;
    blob.Detach(&data, &size);
    return INIFileContext { .ini = ini_load((const char*)data, alloc) };
}

INIFileContext INIFile::LoadFromString(const char* data, MemAllocator* alloc)
{
    return INIFileContext { .ini = ini_load(data, alloc) };
}

bool INIFile::Save(const INIFileContext& ini, const char* filepath)
{
    bool saveDone = false;
    int size = ini_save(ini.ini, nullptr, 0);
    if (size > 0) {
        MemTempAllocator tmpAlloc;
        char* data = tmpAlloc.MallocTyped<char>(size);
        ini_save(ini.ini, data, size);

        File f;
        if (f.Open(filepath, FileOpenFlags::Write)) {
            f.Write(data, size);
            f.Close();
            saveDone = true;
        }
    }
    return saveDone;
}

Blob INIFile::SaveToMem(const INIFileContext& ini, MemAllocator* alloc)
{
    int size = ini_save(ini.ini, nullptr, 0);
    Blob blob(alloc);
    if (size > 0) {
        blob.Reserve(size);
        ini_save(ini.ini, (char*)blob.Data(), (int)blob.Size());
        return blob;
    }
    return blob;
}

uint32 INIFileContext::GetSectionCount() const
{
    ASSERT(this->ini);
    return static_cast<uint32>(ini_section_count(this->ini));
}

INIFileSection INIFileContext::GetSection(uint32 index) const
{
    ASSERT(this->ini);
    return INIFileSection { .ini = this->ini, .id = static_cast<int>(index) };
}

const char* INIFileContext::GetSectionName(uint32 index) const
{
    ASSERT(this->ini);
    return ini_section_name(this->ini, static_cast<int>(index));
}

INIFileSection INIFileContext::GetRootSection() const
{
    ASSERT(this->ini);
    return INIFileSection { .ini = this->ini, .id = INI_GLOBAL_SECTION };
}

INIFileSection INIFileContext::NewSection(const char* name) const
{
    ASSERT(this->ini);
    return INIFileSection { .ini = this->ini, .id = ini_section_add(this->ini, name, Str::Len(name)) };
}

INIFileSection INIFileContext::FindSection(const char* name) const
{
    ASSERT(this->ini);
    return INIFileSection { .ini = this->ini, .id = ini_find_section(this->ini, name, Str::Len(name)) };
}

void INIFileContext::Destroy()
{
    if (this->ini) 
        ini_destroy(this->ini);
    this->ini = nullptr;
}

uint32 INIFileSection::GetPropertyCount()
{
    ASSERT(this->id != INI_NOT_FOUND);
    return static_cast<uint32>(ini_property_count(this->ini, this->id));
}

INIFileProperty INIFileSection::GetProperty(uint32 index)
{
    return { .ini = this->ini, .sectionId = this->id, .id = static_cast<int>(index) };
}

const char* INIFileSection::GetPropertyName(uint32 index)
{
    ASSERT(this->id != INI_NOT_FOUND);
    return ini_property_name(this->ini, this->id, static_cast<int>(index));
}

INIFileProperty INIFileSection::NewProperty(const char* name, const char* value)
{
    ASSERT(this->id != INI_NOT_FOUND);
    ini_property_add(this->ini, this->id, name, Str::Len(name), value, Str::Len(value));
    return INIFileProperty { 
        .ini = this->ini, 
        .sectionId = this->id,
        .id = ini_property_count(this->ini, this->id) - 1 
    };
}

INIFileProperty INIFileSection::FindProperty(const char* name)
{
    ASSERT(this->id != INI_NOT_FOUND);
    return INIFileProperty { 
        .ini = this->ini, 
        .sectionId = this->id,
        .id = ini_find_property(this->ini, this->id, name, Str::Len(name)) 
    };
}

void INIFileSection::SetName(const char* name)
{
    ASSERT(this->id != INI_NOT_FOUND);
    ini_section_name_set(this->ini, this->id, name, Str::Len(name));
}

const char* INIFileSection::GetName()
{
    ASSERT(this->id != INI_NOT_FOUND);
    return ini_section_name(this->ini, this->id);
}

void INIFileSection::Delete()
{
    ASSERT(this->id != INI_NOT_FOUND);
    ini_section_remove(this->ini, this->id);
}

void INIFileProperty::SetName(const char* name)
{
    ASSERT(this->id != INI_NOT_FOUND);
    ini_property_name_set(this->ini, this->sectionId, this->id, name, (int)Str::Len(name));
}

void INIFileProperty::SetValue(const char* value)
{
    ASSERT(this->id != INI_NOT_FOUND);
    ini_property_value_set(this->ini, this->sectionId, this->id, value, (int)Str::Len(value));
}

const char* INIFileProperty::GetName()
{
    ASSERT(this->id != INI_NOT_FOUND);
    return ini_property_name(this->ini, this->sectionId, this->id);
}

const char* INIFileProperty::GetValue()
{
    ASSERT(this->id != INI_NOT_FOUND);
    return ini_property_value(this->ini, this->sectionId, this->id);
}

void INIFileProperty::Delete()
{
    ASSERT(this->id != INI_NOT_FOUND);
    ini_property_remove(this->ini, this->sectionId, this->id);
}


#define MINICORO_IMPL
#define MCO_ASSERT(c) ASSERT(c)
#define MCO_LOG(e) LOG_ERROR(e)
//----------------------------------------------------------------------------------------------------------------------
// External/minicoro/minicoro.h

/*
Minimal asymmetric stackful cross-platform coroutine library in pure C.
minicoro - v0.2.0 - 15/Nov/2023
Eduardo Bart - edub4rt@gmail.com
https://github.com/edubart/minicoro

Minicoro is single file library for using asymmetric coroutines in C.
The API is inspired by Lua coroutines but with C use in mind.

# Features

- Stackful asymmetric coroutines.
- Supports nesting coroutines (resuming a coroutine from another coroutine).
- Supports custom allocators.
- Storage system to allow passing values between yield and resume.
- Customizable stack size.
- Supports growable stacks and low memory footprint when enabling the virtual memory allocator.
- Coroutine API design inspired by Lua with C use in mind.
- Yield across any C function.
- Made to work in multithread applications.
- Cross platform.
- Minimal, self contained and no external dependencies.
- Readable sources and documented.
- Implemented via assembly, ucontext or fibers.
- Lightweight and very efficient.
- Works in most C89 compilers.
- Error prone API, returning proper error codes on misuse.
- Support running with Valgrind, ASan (AddressSanitizer) and TSan (ThreadSanitizer).

# Supported Platforms

Most platforms are supported through different methods:

| Platform     | Assembly Method  | Fallback Method   |
|--------------|------------------|-------------------|
| Android      | ARM/ARM64        | N/A               |
| iOS          | ARM/ARM64        | N/A               |
| Windows      | x86_64           | Windows fibers    |
| Linux        | x86_64/i686      | ucontext          |
| Mac OS X     | x86_64/ARM/ARM64 | ucontext          |
| WebAssembly  | N/A              | Emscripten fibers / Binaryen asyncify |
| Raspberry Pi | ARM              | ucontext          |
| RISC-V       | rv64/rv32        | ucontext          |

The assembly method is used by default if supported by the compiler and CPU,
otherwise ucontext or fiber method is used as a fallback.

The assembly method is very efficient, it just take a few cycles
to create, resume, yield or destroy a coroutine.

# Caveats

- Avoid using coroutines with C++ exceptions, this is not recommended, it may not behave as you expect.
- When using C++ RAII (i.e. destructors) you must resume the coroutine until it dies to properly execute all destructors.
- Some unsupported sanitizers for C may trigger false warnings when using coroutines.
- The `mco_coro` object is not thread safe, you should use a mutex for manipulating it in multithread applications.
- To use in multithread applications, you must compile with C compiler that supports `thread_local` qualifier.
- Avoid using `thread_local` inside coroutine code, the compiler may cache thread local variables pointers which can be invalid when a coroutine switch threads.
- Stack space is limited. By default it has 56KB of space, this can be changed on coroutine creation, or by enabling the virtual memory backed allocator to make it 2040KB.
- Take care to not cause stack overflows (run out of stack space), otherwise your program may crash or not, the behavior is undefined.
- On WebAssembly you must compile with Emscripten flag `-s ASYNCIFY=1`.
- The WebAssembly Binaryen asyncify method can be used when explicitly enabled,
you may want to do this only to use minicoro with WebAssembly native interpreters
(no Web browser). This method is confirmed to work well with Emscripten toolchain,
however it fails on other WebAssembly toolchains like WASI SDK.

# Introduction

A coroutine represents an independent "green" thread of execution.
Unlike threads in multithread systems, however,
a coroutine only suspends its execution by explicitly calling a yield function.

You create a coroutine by calling `mco_create`.
Its sole argument is a `mco_desc` structure with a description for the coroutine.
The `mco_create` function only creates a new coroutine and returns a handle to it, it does not start the coroutine.

You execute a coroutine by calling `mco_resume`.
When calling a resume function the coroutine starts its execution by calling its body function.
After the coroutine starts running, it runs until it terminates or yields.

A coroutine yields by calling `mco_yield`.
When a coroutine yields, the corresponding resume returns immediately,
even if the yield happens inside nested function calls (that is, not in the main function).
The next time you resume the same coroutine, it continues its execution from the point where it yielded.

To associate a persistent value with the coroutine,
you can  optionally set `user_data` on its creation and later retrieve with `mco_get_user_data`.

To pass values between resume and yield,
you can optionally use `mco_push` and `mco_pop` APIs,
they are intended to pass temporary values using a LIFO style buffer.
The storage system can also be used to send and receive initial values on coroutine creation or before it finishes.

# Usage

To use minicoro, do the following in one .c file:

```c
#define MINICORO_IMPL
```

You can do `#include "minicoro.h"` in other parts of the program just like any other header.

## Minimal Example

The following simple example demonstrates on how to use the library:

```c
#define MINICORO_IMPL
#include <stdio.h>
#include <assert.h>

void coro_entry(mco_coro* co) {
  printf("coroutine 1\n");
  mco_yield(co);
  printf("coroutine 2\n");
}

int main() {
  mco_desc desc = mco_desc_init(coro_entry, 0);
  desc.user_data = NULL;
  mco_coro* co;
  mco_result res = mco_create(&co, &desc);
  assert(res == MCO_SUCCESS);
  assert(mco_status(co) == MCO_SUSPENDED);
  res = mco_resume(co); // Should print "coroutine 1".
  assert(res == MCO_SUCCESS);
  assert(mco_status(co) == MCO_SUSPENDED);
  res = mco_resume(co); // Should print "coroutine 2".
  assert(res == MCO_SUCCESS);
  assert(mco_status(co) == MCO_DEAD);
  res = mco_destroy(co);
  assert(res == MCO_SUCCESS);
  return 0;
}
```

_NOTE_: In case you don't want to use the minicoro allocator system you should
allocate a coroutine object yourself using `mco_desc.coro_size` and call `mco_init`,
then later to destroy call `mco_uninit` and deallocate it.

## Yielding from anywhere

You can yield the current running coroutine from anywhere
without having to pass `mco_coro` pointers around,
to this just use `mco_yield(mco_running())`.

## Passing data between yield and resume

The library has the storage interface to assist passing data between yield and resume.
It's usage is straightforward,
use `mco_push` to send data before a `mco_resume` or `mco_yield`,
then later use `mco_pop` after a `mco_resume` or `mco_yield` to receive data.
Take care to not mismatch a push and pop, otherwise these functions will return
an error.

## Error handling

The library return error codes in most of its API in case of misuse or system error,
the user is encouraged to handle them properly.

## Virtual memory backed allocator

The new compile time option `MCO_USE_VMEM_ALLOCATOR` enables a virtual memory backed allocator.

Every stackful coroutine usually have to reserve memory for its full stack,
this typically makes the total memory usage very high when allocating thousands of coroutines,
for example, an application with 100 thousands coroutine with stacks of 56KB would consume as high
as 5GB of memory, however your application may not really full stack usage for every coroutine.

Some developers often prefer stackless coroutines over stackful coroutines
because of this problem, stackless memory footprint is low, therefore often considered more lightweight.
However stackless have many other limitations, like you cannot run unconstrained code inside them.

One remedy to the solution is to make stackful coroutines growable,
to only use physical memory on demand when its really needed,
and there is a nice way to do this relying on virtual memory allocation
when supported by the operating system.

The virtual memory backed allocator will reserve virtual memory in the OS for each coroutine stack,
but not trigger real physical memory usage yet.
While the application virtual memory usage will be high,
the physical memory usage will be low and actually grow on demand (usually every 4KB chunk in Linux).

The virtual memory backed allocator also raises the default stack size to about 2MB,
typically the size of extra threads in Linux,
so you have more space in your coroutines and the risk of stack overflow is low.

As an example, allocating 100 thousands coroutines with nearly 2MB stack reserved space
with the virtual memory allocator uses 783MB of physical memory usage, that is about 8KB per coroutine,
however the virtual memory usage will be at 98GB.

It is recommended to enable this option only if you plan to spawn thousands of coroutines
while wanting to have a low memory footprint.
Not all environments have an OS with virtual memory support, therefore this option is disabled by default.

This option may add an order of magnitude overhead to `mco_create()`/`mco_destroy()`,
because they will request the OS to manage virtual memory page tables,
if this is a problem for you, please customize a custom allocator for your own needs.

## Library customization

The following can be defined to change the library behavior:

- `MCO_API`                   - Public API qualifier. Default is `extern`.
- `MCO_MIN_STACK_SIZE`        - Minimum stack size when creating a coroutine. Default is 32768 (32KB).
- `MCO_DEFAULT_STORAGE_SIZE`  - Size of coroutine storage buffer. Default is 1024.
- `MCO_DEFAULT_STACK_SIZE`    - Default stack size when creating a coroutine. Default is 57344 (56KB). When `MCO_USE_VMEM_ALLOCATOR` is true the default is 2040KB (nearly 2MB).
- `MCO_ALLOC`                 - Default allocation function. Default is `calloc`.
- `MCO_DEALLOC`               - Default deallocation function. Default is `free`.
- `MCO_USE_VMEM_ALLOCATOR`    - Use virtual memory backed allocator, improving memory footprint per coroutine.
- `MCO_NO_DEFAULT_ALLOCATOR`  - Disable the default allocator using `MCO_ALLOC` and `MCO_DEALLOC`.
- `MCO_ZERO_MEMORY`           - Zero memory of stack when poping storage, intended for garbage collected environments.
- `MCO_DEBUG`                 - Enable debug mode, logging any runtime error to stdout. Defined automatically unless `NDEBUG` or `MCO_NO_DEBUG` is defined.
- `MCO_NO_DEBUG`              - Disable debug mode.
- `MCO_NO_MULTITHREAD`        - Disable multithread usage. Multithread is supported when `thread_local` is supported.
- `MCO_USE_ASM`               - Force use of assembly context switch implementation.
- `MCO_USE_UCONTEXT`          - Force use of ucontext context switch implementation.
- `MCO_USE_FIBERS`            - Force use of fibers context switch implementation.
- `MCO_USE_ASYNCIFY`          - Force use of Binaryen asyncify context switch implementation.
- `MCO_USE_VALGRIND`          - Define if you want run with valgrind to fix accessing memory errors.

# License

Your choice of either Public Domain or MIT No Attribution, see end of file.
*/


#ifndef MINICORO_H
#define MINICORO_H

#ifdef __cplusplus
extern "C" {
#endif

/* Public API qualifier. */
#ifndef MCO_API
#define MCO_API extern
#endif

/* Size of coroutine storage buffer. */
#ifndef MCO_DEFAULT_STORAGE_SIZE
#define MCO_DEFAULT_STORAGE_SIZE 1024
#endif

#include <stddef.h> /* for size_t */

/* ---------------------------------------------------------------------------------------------- */

/* Coroutine states. */
typedef enum mco_state {
  MCO_DEAD = 0,  /* The coroutine has finished normally or was uninitialized before finishing. */
  MCO_NORMAL,    /* The coroutine is active but not running (that is, it has resumed another coroutine). */
  MCO_RUNNING,   /* The coroutine is active and running. */
  MCO_SUSPENDED  /* The coroutine is suspended (in a call to yield, or it has not started running yet). */
} mco_state;

/* Coroutine result codes. */
typedef enum mco_result {
  MCO_SUCCESS = 0,
  MCO_GENERIC_ERROR,
  MCO_INVALID_POINTER,
  MCO_INVALID_COROUTINE,
  MCO_NOT_SUSPENDED,
  MCO_NOT_RUNNING,
  MCO_MAKE_CONTEXT_ERROR,
  MCO_SWITCH_CONTEXT_ERROR,
  MCO_NOT_ENOUGH_SPACE,
  MCO_OUT_OF_MEMORY,
  MCO_INVALID_ARGUMENTS,
  MCO_INVALID_OPERATION,
  MCO_STACK_OVERFLOW
} mco_result;

/* Coroutine structure. */
typedef struct mco_coro mco_coro;
struct mco_coro {
  void* context;
  mco_state state;
  void (*func)(mco_coro* co);
  mco_coro* prev_co;
  void* user_data;
  size_t coro_size;
  void* allocator_data;
  void (*dealloc_cb)(void* ptr, size_t size, void* allocator_data);
  void* stack_base; /* Stack base address, can be used to scan memory in a garbage collector. */
  size_t stack_size;
  unsigned char* storage;
  size_t bytes_stored;
  size_t storage_size;
  void* asan_prev_stack; /* Used by address sanitizer. */
  void* tsan_prev_fiber; /* Used by thread sanitizer. */
  void* tsan_fiber; /* Used by thread sanitizer. */
  size_t magic_number; /* Used to check stack overflow. */
};

/* Structure used to initialize a coroutine. */
typedef struct mco_desc {
  void (*func)(mco_coro* co); /* Entry point function for the coroutine. */
  void* user_data;            /* Coroutine user data, can be get with `mco_get_user_data`. */
  /* Custom allocation interface. */
  void* (*alloc_cb)(size_t size, void* allocator_data); /* Custom allocation function. */
  void  (*dealloc_cb)(void* ptr, size_t size, void* allocator_data);     /* Custom deallocation function. */
  void* allocator_data;       /* User data pointer passed to `alloc`/`dealloc` allocation functions. */
  size_t storage_size;        /* Coroutine storage size, to be used with the storage APIs. */
  /* These must be initialized only through `mco_init_desc`. */
  size_t coro_size;           /* Coroutine structure size. */
  size_t stack_size;          /* Coroutine stack size. */
} mco_desc;

/* Coroutine functions. */
MCO_API mco_desc mco_desc_init(void (*func)(mco_coro* co), size_t stack_size);  /* Initialize description of a coroutine. When stack size is 0 then MCO_DEFAULT_STACK_SIZE is used. */
MCO_API mco_result mco_init(mco_coro* co, mco_desc* desc);                      /* Initialize the coroutine. */
MCO_API mco_result mco_uninit(mco_coro* co);                                    /* Uninitialize the coroutine, may fail if it's not dead or suspended. */
MCO_API mco_result mco_create(mco_coro** out_co, mco_desc* desc);               /* Allocates and initializes a new coroutine. */
MCO_API mco_result mco_destroy(mco_coro* co);                                   /* Uninitialize and deallocate the coroutine, may fail if it's not dead or suspended. */
MCO_API mco_result mco_resume(mco_coro* co);                                    /* Starts or continues the execution of the coroutine. */
MCO_API mco_result mco_yield(mco_coro* co);                                     /* Suspends the execution of a coroutine. */
MCO_API mco_state mco_status(mco_coro* co);                                     /* Returns the status of the coroutine. */
MCO_API void* mco_get_user_data(mco_coro* co);                                  /* Get coroutine user data supplied on coroutine creation. */

/* Storage interface functions, used to pass values between yield and resume. */
MCO_API mco_result mco_push(mco_coro* co, const void* src, size_t len); /* Push bytes to the coroutine storage. Use to send values between yield and resume. */
MCO_API mco_result mco_pop(mco_coro* co, void* dest, size_t len);       /* Pop bytes from the coroutine storage. Use to get values between yield and resume. */
MCO_API mco_result mco_peek(mco_coro* co, void* dest, size_t len);      /* Like `mco_pop` but it does not consumes the storage. */
MCO_API size_t mco_get_bytes_stored(mco_coro* co);                      /* Get the available bytes that can be retrieved with a `mco_pop`. */
MCO_API size_t mco_get_storage_size(mco_coro* co);                      /* Get the total storage size. */

/* Misc functions. */
MCO_API mco_coro* mco_running(void);                        /* Returns the running coroutine for the current thread. */
MCO_API const char* mco_result_description(mco_result res); /* Get the description of a result. */

#ifdef __cplusplus
}
#endif

#endif /* MINICORO_H */

#ifdef MINICORO_IMPL

#ifdef __cplusplus
extern "C" {
#endif

/* ---------------------------------------------------------------------------------------------- */

/* Minimum stack size when creating a coroutine. */
#ifndef MCO_MIN_STACK_SIZE
#define MCO_MIN_STACK_SIZE 32768
#endif

/* Default stack size when creating a coroutine. */
#ifndef MCO_DEFAULT_STACK_SIZE
/* Use multiples of 64KB minus 8KB, because 8KB is reserved for coroutine internal structures. */
#ifdef MCO_USE_VMEM_ALLOCATOR
#define MCO_DEFAULT_STACK_SIZE 2040*1024 /* 2040KB, nearly the same stack size of a thread in x86_64 Linux. */
#else
#define MCO_DEFAULT_STACK_SIZE 56*1024 /* 56KB */
#endif
#endif

/* Number used only to assist checking for stack overflows. */
#define MCO_MAGIC_NUMBER 0x7E3CB1A9

/* Detect implementation based on OS, arch and compiler. */
#if !defined(MCO_USE_UCONTEXT) && !defined(MCO_USE_FIBERS) && !defined(MCO_USE_ASM) && !defined(MCO_USE_ASYNCIFY)
  #if defined(_WIN32)
    #if (defined(__GNUC__) && defined(__x86_64__)) || (defined(_MSC_VER) && defined(_M_X64))
      #define MCO_USE_ASM
    #else
      #define MCO_USE_FIBERS
    #endif
  #elif defined(__CYGWIN__) /* MSYS */
    #define MCO_USE_UCONTEXT
  #elif defined(__EMSCRIPTEN__)
    #define MCO_USE_FIBERS
  #elif defined(__wasm__)
    #define MCO_USE_ASYNCIFY
  #else
    #if __GNUC__ >= 3 /* Assembly extension supported. */
      #if defined(__x86_64__) || \
          defined(__i386) || defined(__i386__) || \
          defined(__ARM_EABI__) || defined(__aarch64__) || \
          defined(__riscv)
        #define MCO_USE_ASM
      #else
        #define MCO_USE_UCONTEXT
      #endif
    #else
      #define MCO_USE_UCONTEXT
    #endif
  #endif
#endif

#define _MCO_UNUSED(x) (void)(x)

#if !defined(MCO_NO_DEBUG) && !defined(NDEBUG) && !defined(MCO_DEBUG)
#define MCO_DEBUG
#endif

#ifndef MCO_LOG
  #ifdef MCO_DEBUG
    #include <stdio.h>
    #define MCO_LOG(s) puts(s)
  #else
    #define MCO_LOG(s)
  #endif
#endif

#ifndef MCO_ASSERT
  #ifdef MCO_DEBUG
    #include <assert.h>
    #define MCO_ASSERT(c) assert(c)
  #else
    #define MCO_ASSERT(c)
  #endif
#endif

#ifndef MCO_THREAD_LOCAL
  #ifdef MCO_NO_MULTITHREAD
    #define MCO_THREAD_LOCAL
  #else
    #ifdef thread_local
      #define MCO_THREAD_LOCAL thread_local
    #elif __STDC_VERSION__ >= 201112 && !defined(__STDC_NO_THREADS__)
      #define MCO_THREAD_LOCAL _Thread_local
    #elif defined(_WIN32) && (defined(_MSC_VER) || defined(__ICL) ||  defined(__DMC__) ||  defined(__BORLANDC__))
      #define MCO_THREAD_LOCAL __declspec(thread)
    #elif defined(__GNUC__) || defined(__SUNPRO_C) || defined(__xlC__)
      #define MCO_THREAD_LOCAL __thread
    #else /* No thread local support, `mco_running` will be thread unsafe. */
      #define MCO_THREAD_LOCAL
      #define MCO_NO_MULTITHREAD
    #endif
  #endif
#endif

#ifndef MCO_FORCE_INLINE
  #ifdef _MSC_VER
    #define MCO_FORCE_INLINE __forceinline
  #elif defined(__GNUC__)
    #if defined(__STRICT_ANSI__)
      #define MCO_FORCE_INLINE __inline__ __attribute__((always_inline))
    #else
      #define MCO_FORCE_INLINE inline __attribute__((always_inline))
    #endif
  #elif defined(__BORLANDC__) || defined(__DMC__) || defined(__SC__) || defined(__WATCOMC__) || defined(__LCC__) ||  defined(__DECC)
    #define MCO_FORCE_INLINE __inline
  #else /* No inline support. */
    #define MCO_FORCE_INLINE
  #endif
#endif

#ifndef MCO_NO_INLINE
  #ifdef __GNUC__
    #define MCO_NO_INLINE __attribute__((noinline))
  #elif defined(_MSC_VER)
    #define MCO_NO_INLINE __declspec(noinline)
  #else
    #define MCO_NO_INLINE
  #endif
#endif

#if defined(_WIN32) && (defined(MCO_USE_FIBERS) || defined(MCO_USE_VMEM_ALLOCATOR))
  #ifndef _WIN32_WINNT
    #define _WIN32_WINNT 0x0400
  #endif
  #ifndef WIN32_LEAN_AND_MEAN
    #define WIN32_LEAN_AND_MEAN
  #endif
  #include <windows.h>
#endif

#ifndef MCO_NO_DEFAULT_ALLOCATOR
  #if defined(MCO_USE_VMEM_ALLOCATOR) && defined(_WIN32)
    static void* mco_alloc(size_t size, void* allocator_data) {
      _MCO_UNUSED(allocator_data);
      return VirtualAlloc(NULL, size, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
    }
    static void mco_dealloc(void* ptr, size_t size, void* allocator_data) {
      _MCO_UNUSED(allocator_data);
      _MCO_UNUSED(size);
      int res = VirtualFree(ptr, 0, MEM_RELEASE);
      _MCO_UNUSED(res);
      MCO_ASSERT(res != 0);
    }
  #elif defined(MCO_USE_VMEM_ALLOCATOR) /* POSIX virtual memory allocator */
    #include <sys/mman.h>
    static void* mco_alloc(size_t size, void* allocator_data) {
      _MCO_UNUSED(allocator_data);
      void *ptr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
      return ptr != MAP_FAILED ? ptr : NULL;
    }
    static void mco_dealloc(void* ptr, size_t size, void* allocator_data) {
      _MCO_UNUSED(allocator_data);
      int res = munmap(ptr, size);
      _MCO_UNUSED(res);
      MCO_ASSERT(res == 0);
    }
  #else /* C allocator */
    #ifndef MCO_ALLOC
      #include <stdlib.h>
      /* We use calloc() so we give a chance for the OS to reserve virtual memory without really using physical memory,
         calloc() also has the nice property of initializing the stack to zeros. */
      #define MCO_ALLOC(size) calloc(1, size)
      #define MCO_DEALLOC(ptr, size) free(ptr)
    #endif
    static void* mco_alloc(size_t size, void* allocator_data) {
      _MCO_UNUSED(allocator_data);
      return MCO_ALLOC(size);
    }
    static void mco_dealloc(void* ptr, size_t size, void* allocator_data) {
      _MCO_UNUSED(size);
      _MCO_UNUSED(allocator_data);
      MCO_DEALLOC(ptr, size);
    }
  #endif /* MCO_USE_VMEM_ALLOCATOR */
#endif /* MCO_NO_DEFAULT_ALLOCATOR */

#if defined(__has_feature)
  #if __has_feature(address_sanitizer)
    #define _MCO_USE_ASAN
  #endif
  #if __has_feature(thread_sanitizer)
    #define _MCO_USE_TSAN
  #endif
#endif
#if defined(__SANITIZE_ADDRESS__)
  #define _MCO_USE_ASAN
#endif
#if defined(__SANITIZE_THREAD__)
  #define _MCO_USE_TSAN
#endif
#ifdef _MCO_USE_ASAN
void __sanitizer_start_switch_fiber(void** fake_stack_save, const void *bottom, size_t size);
void __sanitizer_finish_switch_fiber(void* fake_stack_save, const void **bottom_old, size_t *size_old);
#endif
#ifdef _MCO_USE_TSAN
void* __tsan_get_current_fiber(void);
void* __tsan_create_fiber(unsigned flags);
void __tsan_destroy_fiber(void* fiber);
void __tsan_switch_to_fiber(void* fiber, unsigned flags);
#endif

#include <string.h> /* For memcpy and memset. */

/* Utility for aligning addresses. */
static MCO_FORCE_INLINE size_t _mco_align_forward(size_t addr, size_t align) {
  return (addr + (align-1)) & ~(align-1);
}

/* Variable holding the current running coroutine per thread. */
static MCO_THREAD_LOCAL mco_coro* mco_current_co = NULL;

static MCO_FORCE_INLINE void _mco_prepare_jumpin(mco_coro* co) {
  /* Set the old coroutine to normal state and update it. */
  mco_coro* prev_co = mco_running(); /* Must access through `mco_running`. */
  MCO_ASSERT(co->prev_co == NULL);
  co->prev_co = prev_co;
  if(prev_co) {
    MCO_ASSERT(prev_co->state == MCO_RUNNING);
    prev_co->state = MCO_NORMAL;
  }
  mco_current_co = co;
#ifdef _MCO_USE_ASAN
  if(prev_co) {
    void* bottom_old = NULL;
    size_t size_old = 0;
    __sanitizer_finish_switch_fiber(prev_co->asan_prev_stack, (const void**)&bottom_old, &size_old);
    prev_co->asan_prev_stack = NULL;
  }
  __sanitizer_start_switch_fiber(&co->asan_prev_stack, co->stack_base, co->stack_size);
#endif
#ifdef _MCO_USE_TSAN
  co->tsan_prev_fiber = __tsan_get_current_fiber();
  __tsan_switch_to_fiber(co->tsan_fiber, 0);
#endif
}

static MCO_FORCE_INLINE void _mco_prepare_jumpout(mco_coro* co) {
  /* Switch back to the previous running coroutine. */
  /* MCO_ASSERT(mco_running() == co); */
  mco_coro* prev_co = co->prev_co;
  co->prev_co = NULL;
  if(prev_co) {
    /* MCO_ASSERT(prev_co->state == MCO_NORMAL); */
    prev_co->state = MCO_RUNNING;
  }
  mco_current_co = prev_co;
#ifdef _MCO_USE_ASAN
  void* bottom_old = NULL;
  size_t size_old = 0;
  __sanitizer_finish_switch_fiber(co->asan_prev_stack, (const void**)&bottom_old, &size_old);
  co->asan_prev_stack = NULL;
  if(prev_co) {
    __sanitizer_start_switch_fiber(&prev_co->asan_prev_stack, bottom_old, size_old);
  }
#endif
#ifdef _MCO_USE_TSAN
  void* tsan_prev_fiber = co->tsan_prev_fiber;
  co->tsan_prev_fiber = NULL;
  __tsan_switch_to_fiber(tsan_prev_fiber, 0);
#endif
}

static void _mco_jumpin(mco_coro* co);
static void _mco_jumpout(mco_coro* co);

static MCO_NO_INLINE void _mco_main(mco_coro* co) {
  co->func(co); /* Run the coroutine function. */
  co->state = MCO_DEAD; /* Coroutine finished successfully, set state to dead. */
  _mco_jumpout(co); /* Jump back to the old context .*/
}

/* ---------------------------------------------------------------------------------------------- */

#if defined(MCO_USE_UCONTEXT) || defined(MCO_USE_ASM)

/*
Some of the following assembly code is taken from LuaCoco by Mike Pall.
See https://coco.luajit.org/index.html

MIT license

Copyright (C) 2004-2016 Mike Pall. All rights reserved.

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifdef MCO_USE_ASM

#if defined(__x86_64__) || defined(_M_X64)

#ifdef _WIN32

typedef struct _mco_ctxbuf {
  void *rip, *rsp, *rbp, *rbx, *r12, *r13, *r14, *r15, *rdi, *rsi;
  void* xmm[20]; /* xmm6, xmm7, xmm8, xmm9, xmm10, xmm11, xmm12, xmm13, xmm14, xmm15 */
  void* fiber_storage;
  void* dealloc_stack;
  void* stack_limit;
  void* stack_base;
} _mco_ctxbuf;

#if defined(__GNUC__)
#define _MCO_ASM_BLOB __attribute__((section(".text")))
#elif defined(_MSC_VER)
#define _MCO_ASM_BLOB __declspec(allocate(".text"))
#pragma section(".text")
#endif

_MCO_ASM_BLOB static unsigned char _mco_wrap_main_code[] = {
  0x4c, 0x89, 0xe9,                                       /* mov    %r13,%rcx */
  0x41, 0xff, 0xe4,                                       /* jmpq   *%r12 */
  0xc3,                                                   /* retq */
  0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90    /* nop */
};

_MCO_ASM_BLOB static unsigned char _mco_switch_code[] = {
  0x48, 0x8d, 0x05, 0x3e, 0x01, 0x00, 0x00,              /* lea    0x13e(%rip),%rax    */
  0x48, 0x89, 0x01,                                      /* mov    %rax,(%rcx)         */
  0x48, 0x89, 0x61, 0x08,                                /* mov    %rsp,0x8(%rcx)      */
  0x48, 0x89, 0x69, 0x10,                                /* mov    %rbp,0x10(%rcx)     */
  0x48, 0x89, 0x59, 0x18,                                /* mov    %rbx,0x18(%rcx)     */
  0x4c, 0x89, 0x61, 0x20,                                /* mov    %r12,0x20(%rcx)     */
  0x4c, 0x89, 0x69, 0x28,                                /* mov    %r13,0x28(%rcx)     */
  0x4c, 0x89, 0x71, 0x30,                                /* mov    %r14,0x30(%rcx)     */
  0x4c, 0x89, 0x79, 0x38,                                /* mov    %r15,0x38(%rcx)     */
  0x48, 0x89, 0x79, 0x40,                                /* mov    %rdi,0x40(%rcx)     */
  0x48, 0x89, 0x71, 0x48,                                /* mov    %rsi,0x48(%rcx)     */
  0x0f, 0x11, 0x71, 0x50,                                /* movups %xmm6,0x50(%rcx)    */
  0x0f, 0x11, 0x79, 0x60,                                /* movups %xmm7,0x60(%rcx)    */
  0x44, 0x0f, 0x11, 0x41, 0x70,                          /* movups %xmm8,0x70(%rcx)    */
  0x44, 0x0f, 0x11, 0x89, 0x80, 0x00, 0x00, 0x00,        /* movups %xmm9,0x80(%rcx)    */
  0x44, 0x0f, 0x11, 0x91, 0x90, 0x00, 0x00, 0x00,        /* movups %xmm10,0x90(%rcx)   */
  0x44, 0x0f, 0x11, 0x99, 0xa0, 0x00, 0x00, 0x00,        /* movups %xmm11,0xa0(%rcx)   */
  0x44, 0x0f, 0x11, 0xa1, 0xb0, 0x00, 0x00, 0x00,        /* movups %xmm12,0xb0(%rcx)   */
  0x44, 0x0f, 0x11, 0xa9, 0xc0, 0x00, 0x00, 0x00,        /* movups %xmm13,0xc0(%rcx)   */
  0x44, 0x0f, 0x11, 0xb1, 0xd0, 0x00, 0x00, 0x00,        /* movups %xmm14,0xd0(%rcx)   */
  0x44, 0x0f, 0x11, 0xb9, 0xe0, 0x00, 0x00, 0x00,        /* movups %xmm15,0xe0(%rcx)   */
  0x65, 0x4c, 0x8b, 0x14, 0x25, 0x30, 0x00, 0x00, 0x00,  /* mov    %gs:0x30,%r10       */
  0x49, 0x8b, 0x42, 0x20,                                /* mov    0x20(%r10),%rax     */
  0x48, 0x89, 0x81, 0xf0, 0x00, 0x00, 0x00,              /* mov    %rax,0xf0(%rcx)     */
  0x49, 0x8b, 0x82, 0x78, 0x14, 0x00, 0x00,              /* mov    0x1478(%r10),%rax   */
  0x48, 0x89, 0x81, 0xf8, 0x00, 0x00, 0x00,              /* mov    %rax,0xf8(%rcx)     */
  0x49, 0x8b, 0x42, 0x10,                                /* mov    0x10(%r10),%rax     */
  0x48, 0x89, 0x81, 0x00, 0x01, 0x00, 0x00,              /* mov    %rax,0x100(%rcx)    */
  0x49, 0x8b, 0x42, 0x08,                                /* mov    0x8(%r10),%rax      */
  0x48, 0x89, 0x81, 0x08, 0x01, 0x00, 0x00,              /* mov    %rax,0x108(%rcx)    */
  0x48, 0x8b, 0x82, 0x08, 0x01, 0x00, 0x00,              /* mov    0x108(%rdx),%rax    */
  0x49, 0x89, 0x42, 0x08,                                /* mov    %rax,0x8(%r10)      */
  0x48, 0x8b, 0x82, 0x00, 0x01, 0x00, 0x00,              /* mov    0x100(%rdx),%rax    */
  0x49, 0x89, 0x42, 0x10,                                /* mov    %rax,0x10(%r10)     */
  0x48, 0x8b, 0x82, 0xf8, 0x00, 0x00, 0x00,              /* mov    0xf8(%rdx),%rax     */
  0x49, 0x89, 0x82, 0x78, 0x14, 0x00, 0x00,              /* mov    %rax,0x1478(%r10)   */
  0x48, 0x8b, 0x82, 0xf0, 0x00, 0x00, 0x00,              /* mov    0xf0(%rdx),%rax     */
  0x49, 0x89, 0x42, 0x20,                                /* mov    %rax,0x20(%r10)     */
  0x44, 0x0f, 0x10, 0xba, 0xe0, 0x00, 0x00, 0x00,        /* movups 0xe0(%rdx),%xmm15   */
  0x44, 0x0f, 0x10, 0xb2, 0xd0, 0x00, 0x00, 0x00,        /* movups 0xd0(%rdx),%xmm14   */
  0x44, 0x0f, 0x10, 0xaa, 0xc0, 0x00, 0x00, 0x00,        /* movups 0xc0(%rdx),%xmm13   */
  0x44, 0x0f, 0x10, 0xa2, 0xb0, 0x00, 0x00, 0x00,        /* movups 0xb0(%rdx),%xmm12   */
  0x44, 0x0f, 0x10, 0x9a, 0xa0, 0x00, 0x00, 0x00,        /* movups 0xa0(%rdx),%xmm11   */
  0x44, 0x0f, 0x10, 0x92, 0x90, 0x00, 0x00, 0x00,        /* movups 0x90(%rdx),%xmm10   */
  0x44, 0x0f, 0x10, 0x8a, 0x80, 0x00, 0x00, 0x00,        /* movups 0x80(%rdx),%xmm9    */
  0x44, 0x0f, 0x10, 0x42, 0x70,                          /* movups 0x70(%rdx),%xmm8    */
  0x0f, 0x10, 0x7a, 0x60,                                /* movups 0x60(%rdx),%xmm7    */
  0x0f, 0x10, 0x72, 0x50,                                /* movups 0x50(%rdx),%xmm6    */
  0x48, 0x8b, 0x72, 0x48,                                /* mov    0x48(%rdx),%rsi     */
  0x48, 0x8b, 0x7a, 0x40,                                /* mov    0x40(%rdx),%rdi     */
  0x4c, 0x8b, 0x7a, 0x38,                                /* mov    0x38(%rdx),%r15     */
  0x4c, 0x8b, 0x72, 0x30,                                /* mov    0x30(%rdx),%r14     */
  0x4c, 0x8b, 0x6a, 0x28,                                /* mov    0x28(%rdx),%r13     */
  0x4c, 0x8b, 0x62, 0x20,                                /* mov    0x20(%rdx),%r12     */
  0x48, 0x8b, 0x5a, 0x18,                                /* mov    0x18(%rdx),%rbx     */
  0x48, 0x8b, 0x6a, 0x10,                                /* mov    0x10(%rdx),%rbp     */
  0x48, 0x8b, 0x62, 0x08,                                /* mov    0x8(%rdx),%rsp      */
  0xff, 0x22,                                            /* jmpq   *(%rdx)             */
  0xc3,                                                  /* retq                       */
  0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90,        /* nop                        */
  0x90, 0x90,                                            /* nop                        */
};

void (*_mco_wrap_main)(void) = (void(*)(void))(void*)_mco_wrap_main_code;
void (*_mco_switch)(_mco_ctxbuf* from, _mco_ctxbuf* to) = (void(*)(_mco_ctxbuf* from, _mco_ctxbuf* to))(void*)_mco_switch_code;

static mco_result _mco_makectx(mco_coro* co, _mco_ctxbuf* ctx, void* stack_base, size_t stack_size) {
  stack_size = stack_size - 32; /* Reserve 32 bytes for the shadow space. */
  void** stack_high_ptr = (void**)((size_t)stack_base + stack_size - sizeof(size_t));
  stack_high_ptr[0] = (void*)(0xdeaddeaddeaddead);  /* Dummy return address. */
  ctx->rip = (void*)(_mco_wrap_main);
  ctx->rsp = (void*)(stack_high_ptr);
  ctx->r12 = (void*)(_mco_main);
  ctx->r13 = (void*)(co);
  void* stack_top = (void*)((size_t)stack_base + stack_size);
  ctx->stack_base = stack_top;
  ctx->stack_limit = stack_base;
  ctx->dealloc_stack = stack_base;
  return MCO_SUCCESS;
}

#else /* not _WIN32 */

typedef struct _mco_ctxbuf {
  void *rip, *rsp, *rbp, *rbx, *r12, *r13, *r14, *r15;
} _mco_ctxbuf;

void _mco_wrap_main(void);
int _mco_switch(_mco_ctxbuf* from, _mco_ctxbuf* to);

__asm__(
  ".text\n"
#ifdef __MACH__ /* Mac OS X assembler */
  ".globl __mco_wrap_main\n"
  "__mco_wrap_main:\n"
#else /* Linux assembler */
  ".globl _mco_wrap_main\n"
  ".type _mco_wrap_main @function\n"
  ".hidden _mco_wrap_main\n"
  "_mco_wrap_main:\n"
#endif
  "  movq %r13, %rdi\n"
  "  jmpq *%r12\n"
#ifndef __MACH__
  ".size _mco_wrap_main, .-_mco_wrap_main\n"
#endif
);

__asm__(
  ".text\n"
#ifdef __MACH__ /* Mac OS assembler */
  ".globl __mco_switch\n"
  "__mco_switch:\n"
#else /* Linux assembler */
  ".globl _mco_switch\n"
  ".type _mco_switch @function\n"
  ".hidden _mco_switch\n"
  "_mco_switch:\n"
#endif
  "  leaq 0x3d(%rip), %rax\n"
  "  movq %rax, (%rdi)\n"
  "  movq %rsp, 8(%rdi)\n"
  "  movq %rbp, 16(%rdi)\n"
  "  movq %rbx, 24(%rdi)\n"
  "  movq %r12, 32(%rdi)\n"
  "  movq %r13, 40(%rdi)\n"
  "  movq %r14, 48(%rdi)\n"
  "  movq %r15, 56(%rdi)\n"
  "  movq 56(%rsi), %r15\n"
  "  movq 48(%rsi), %r14\n"
  "  movq 40(%rsi), %r13\n"
  "  movq 32(%rsi), %r12\n"
  "  movq 24(%rsi), %rbx\n"
  "  movq 16(%rsi), %rbp\n"
  "  movq 8(%rsi), %rsp\n"
  "  jmpq *(%rsi)\n"
  "  ret\n"
#ifndef __MACH__
  ".size _mco_switch, .-_mco_switch\n"
#endif
);

static mco_result _mco_makectx(mco_coro* co, _mco_ctxbuf* ctx, void* stack_base, size_t stack_size) {
  stack_size = stack_size - 128; /* Reserve 128 bytes for the Red Zone space (System V AMD64 ABI). */
  void** stack_high_ptr = (void**)((size_t)stack_base + stack_size - sizeof(size_t));
  stack_high_ptr[0] = (void*)(0xdeaddeaddeaddead);  /* Dummy return address. */
  ctx->rip = (void*)(_mco_wrap_main);
  ctx->rsp = (void*)(stack_high_ptr);
  ctx->r12 = (void*)(_mco_main);
  ctx->r13 = (void*)(co);
  return MCO_SUCCESS;
}

#endif /* not _WIN32 */

#elif defined(__riscv)

typedef struct _mco_ctxbuf {
  void* s[12]; /* s0-s11 */
  void* ra;
  void* pc;
  void* sp;
#ifdef __riscv_flen
#if __riscv_flen == 64
  double fs[12]; /* fs0-fs11 */
#elif __riscv_flen == 32
  float fs[12]; /* fs0-fs11 */
#endif
#endif /* __riscv_flen */
} _mco_ctxbuf;

void _mco_wrap_main(void);
int _mco_switch(_mco_ctxbuf* from, _mco_ctxbuf* to);

__asm__(
  ".text\n"
  ".globl _mco_wrap_main\n"
  ".type _mco_wrap_main @function\n"
  ".hidden _mco_wrap_main\n"
  "_mco_wrap_main:\n"
  "  mv a0, s0\n"
  "  jr s1\n"
  ".size _mco_wrap_main, .-_mco_wrap_main\n"
);

__asm__(
  ".text\n"
  ".globl _mco_switch\n"
  ".type _mco_switch @function\n"
  ".hidden _mco_switch\n"
  "_mco_switch:\n"
  #if __riscv_xlen == 64
    "  sd s0, 0x00(a0)\n"
    "  sd s1, 0x08(a0)\n"
    "  sd s2, 0x10(a0)\n"
    "  sd s3, 0x18(a0)\n"
    "  sd s4, 0x20(a0)\n"
    "  sd s5, 0x28(a0)\n"
    "  sd s6, 0x30(a0)\n"
    "  sd s7, 0x38(a0)\n"
    "  sd s8, 0x40(a0)\n"
    "  sd s9, 0x48(a0)\n"
    "  sd s10, 0x50(a0)\n"
    "  sd s11, 0x58(a0)\n"
    "  sd ra, 0x60(a0)\n"
    "  sd ra, 0x68(a0)\n" /* pc */
    "  sd sp, 0x70(a0)\n"
    #ifdef __riscv_flen
    #if __riscv_flen == 64
    "  fsd fs0, 0x78(a0)\n"
    "  fsd fs1, 0x80(a0)\n"
    "  fsd fs2, 0x88(a0)\n"
    "  fsd fs3, 0x90(a0)\n"
    "  fsd fs4, 0x98(a0)\n"
    "  fsd fs5, 0xa0(a0)\n"
    "  fsd fs6, 0xa8(a0)\n"
    "  fsd fs7, 0xb0(a0)\n"
    "  fsd fs8, 0xb8(a0)\n"
    "  fsd fs9, 0xc0(a0)\n"
    "  fsd fs10, 0xc8(a0)\n"
    "  fsd fs11, 0xd0(a0)\n"
    "  fld fs0, 0x78(a1)\n"
    "  fld fs1, 0x80(a1)\n"
    "  fld fs2, 0x88(a1)\n"
    "  fld fs3, 0x90(a1)\n"
    "  fld fs4, 0x98(a1)\n"
    "  fld fs5, 0xa0(a1)\n"
    "  fld fs6, 0xa8(a1)\n"
    "  fld fs7, 0xb0(a1)\n"
    "  fld fs8, 0xb8(a1)\n"
    "  fld fs9, 0xc0(a1)\n"
    "  fld fs10, 0xc8(a1)\n"
    "  fld fs11, 0xd0(a1)\n"
    #else
    #error "Unsupported RISC-V FLEN"
    #endif
    #endif /* __riscv_flen */
    "  ld s0, 0x00(a1)\n"
    "  ld s1, 0x08(a1)\n"
    "  ld s2, 0x10(a1)\n"
    "  ld s3, 0x18(a1)\n"
    "  ld s4, 0x20(a1)\n"
    "  ld s5, 0x28(a1)\n"
    "  ld s6, 0x30(a1)\n"
    "  ld s7, 0x38(a1)\n"
    "  ld s8, 0x40(a1)\n"
    "  ld s9, 0x48(a1)\n"
    "  ld s10, 0x50(a1)\n"
    "  ld s11, 0x58(a1)\n"
    "  ld ra, 0x60(a1)\n"
    "  ld a2, 0x68(a1)\n" /* pc */
    "  ld sp, 0x70(a1)\n"
    "  jr a2\n"
  #elif __riscv_xlen == 32
    "  sw s0, 0x00(a0)\n"
    "  sw s1, 0x04(a0)\n"
    "  sw s2, 0x08(a0)\n"
    "  sw s3, 0x0c(a0)\n"
    "  sw s4, 0x10(a0)\n"
    "  sw s5, 0x14(a0)\n"
    "  sw s6, 0x18(a0)\n"
    "  sw s7, 0x1c(a0)\n"
    "  sw s8, 0x20(a0)\n"
    "  sw s9, 0x24(a0)\n"
    "  sw s10, 0x28(a0)\n"
    "  sw s11, 0x2c(a0)\n"
    "  sw ra, 0x30(a0)\n"
    "  sw ra, 0x34(a0)\n" /* pc */
    "  sw sp, 0x38(a0)\n"
    #ifdef __riscv_flen
    #if __riscv_flen == 64
    "  fsd fs0, 0x3c(a0)\n"
    "  fsd fs1, 0x44(a0)\n"
    "  fsd fs2, 0x4c(a0)\n"
    "  fsd fs3, 0x54(a0)\n"
    "  fsd fs4, 0x5c(a0)\n"
    "  fsd fs5, 0x64(a0)\n"
    "  fsd fs6, 0x6c(a0)\n"
    "  fsd fs7, 0x74(a0)\n"
    "  fsd fs8, 0x7c(a0)\n"
    "  fsd fs9, 0x84(a0)\n"
    "  fsd fs10, 0x8c(a0)\n"
    "  fsd fs11, 0x94(a0)\n"
    "  fld fs0, 0x3c(a1)\n"
    "  fld fs1, 0x44(a1)\n"
    "  fld fs2, 0x4c(a1)\n"
    "  fld fs3, 0x54(a1)\n"
    "  fld fs4, 0x5c(a1)\n"
    "  fld fs5, 0x64(a1)\n"
    "  fld fs6, 0x6c(a1)\n"
    "  fld fs7, 0x74(a1)\n"
    "  fld fs8, 0x7c(a1)\n"
    "  fld fs9, 0x84(a1)\n"
    "  fld fs10, 0x8c(a1)\n"
    "  fld fs11, 0x94(a1)\n"
    #elif __riscv_flen == 32
    "  fsw fs0, 0x3c(a0)\n"
    "  fsw fs1, 0x40(a0)\n"
    "  fsw fs2, 0x44(a0)\n"
    "  fsw fs3, 0x48(a0)\n"
    "  fsw fs4, 0x4c(a0)\n"
    "  fsw fs5, 0x50(a0)\n"
    "  fsw fs6, 0x54(a0)\n"
    "  fsw fs7, 0x58(a0)\n"
    "  fsw fs8, 0x5c(a0)\n"
    "  fsw fs9, 0x60(a0)\n"
    "  fsw fs10, 0x64(a0)\n"
    "  fsw fs11, 0x68(a0)\n"
    "  flw fs0, 0x3c(a1)\n"
    "  flw fs1, 0x40(a1)\n"
    "  flw fs2, 0x44(a1)\n"
    "  flw fs3, 0x48(a1)\n"
    "  flw fs4, 0x4c(a1)\n"
    "  flw fs5, 0x50(a1)\n"
    "  flw fs6, 0x54(a1)\n"
    "  flw fs7, 0x58(a1)\n"
    "  flw fs8, 0x5c(a1)\n"
    "  flw fs9, 0x60(a1)\n"
    "  flw fs10, 0x64(a1)\n"
    "  flw fs11, 0x68(a1)\n"
    #else
    #error "Unsupported RISC-V FLEN"
    #endif
    #endif /* __riscv_flen */
    "  lw s0, 0x00(a1)\n"
    "  lw s1, 0x04(a1)\n"
    "  lw s2, 0x08(a1)\n"
    "  lw s3, 0x0c(a1)\n"
    "  lw s4, 0x10(a1)\n"
    "  lw s5, 0x14(a1)\n"
    "  lw s6, 0x18(a1)\n"
    "  lw s7, 0x1c(a1)\n"
    "  lw s8, 0x20(a1)\n"
    "  lw s9, 0x24(a1)\n"
    "  lw s10, 0x28(a1)\n"
    "  lw s11, 0x2c(a1)\n"
    "  lw ra, 0x30(a1)\n"
    "  lw a2, 0x34(a1)\n" /* pc */
    "  lw sp, 0x38(a1)\n"
    "  jr a2\n"
  #else
    #error "Unsupported RISC-V XLEN"
  #endif /* __riscv_xlen */
  ".size _mco_switch, .-_mco_switch\n"
);

static mco_result _mco_makectx(mco_coro* co, _mco_ctxbuf* ctx, void* stack_base, size_t stack_size) {
  ctx->s[0] = (void*)(co);
  ctx->s[1] = (void*)(_mco_main);
  ctx->pc = (void*)(_mco_wrap_main);
#if __riscv_xlen == 64
  ctx->ra = (void*)(0xdeaddeaddeaddead);
#elif __riscv_xlen == 32
  ctx->ra = (void*)(0xdeaddead);
#endif
  ctx->sp = (void*)((size_t)stack_base + stack_size);
  return MCO_SUCCESS;
}

#elif defined(__i386) || defined(__i386__)

typedef struct _mco_ctxbuf {
  void *eip, *esp, *ebp, *ebx, *esi, *edi;
} _mco_ctxbuf;

void _mco_switch(_mco_ctxbuf* from, _mco_ctxbuf* to);

__asm__(
#ifdef __DJGPP__ /* DOS compiler */
  "__mco_switch:\n"
#else
  ".text\n"
  ".globl _mco_switch\n"
  ".type _mco_switch @function\n"
  ".hidden _mco_switch\n"
  "_mco_switch:\n"
#endif
  "  call 1f\n"
  "  1:\n"
  "  popl %ecx\n"
  "  addl $(2f-1b), %ecx\n"
  "  movl 4(%esp), %eax\n"
  "  movl 8(%esp), %edx\n"
  "  movl %ecx, (%eax)\n"
  "  movl %esp, 4(%eax)\n"
  "  movl %ebp, 8(%eax)\n"
  "  movl %ebx, 12(%eax)\n"
  "  movl %esi, 16(%eax)\n"
  "  movl %edi, 20(%eax)\n"
  "  movl 20(%edx), %edi\n"
  "  movl 16(%edx), %esi\n"
  "  movl 12(%edx), %ebx\n"
  "  movl 8(%edx), %ebp\n"
  "  movl 4(%edx), %esp\n"
  "  jmp *(%edx)\n"
  "  2:\n"
  "  ret\n"
#ifndef __DJGPP__
  ".size _mco_switch, .-_mco_switch\n"
#endif
);

static mco_result _mco_makectx(mco_coro* co, _mco_ctxbuf* ctx, void* stack_base, size_t stack_size) {
  void** stack_high_ptr = (void**)((size_t)stack_base + stack_size - 16 - 1*sizeof(size_t));
  stack_high_ptr[0] = (void*)(0xdeaddead);  /* Dummy return address. */
  stack_high_ptr[1] = (void*)(co);
  ctx->eip = (void*)(_mco_main);
  ctx->esp = (void*)(stack_high_ptr);
  return MCO_SUCCESS;
}

#elif defined(__ARM_EABI__)

typedef struct _mco_ctxbuf {
#ifndef __SOFTFP__
  void* f[16];
#endif
  void *d[4]; /* d8-d15 */
  void *r[4]; /* r4-r11 */
  void *lr;
  void *sp;
} _mco_ctxbuf;

void _mco_wrap_main(void);
int _mco_switch(_mco_ctxbuf* from, _mco_ctxbuf* to);

__asm__(
  ".text\n"
#ifdef __APPLE__
  ".globl __mco_switch\n"
  "__mco_switch:\n"
#else
  ".globl _mco_switch\n"
  ".type _mco_switch #function\n"
  ".hidden _mco_switch\n"
  "_mco_switch:\n"
#endif
#ifndef __SOFTFP__
  "  vstmia r0!, {d8-d15}\n"
#endif
  "  stmia r0, {r4-r11, lr}\n"
  "  str sp, [r0, #9*4]\n"
#ifndef __SOFTFP__
  "  vldmia r1!, {d8-d15}\n"
#endif
  "  ldr sp, [r1, #9*4]\n"
  "  ldmia r1, {r4-r11, pc}\n"
#ifndef __APPLE__
  ".size _mco_switch, .-_mco_switch\n"
#endif
);

__asm__(
  ".text\n"
#ifdef __APPLE__
  ".globl __mco_wrap_main\n"
  "__mco_wrap_main:\n"
#else
  ".globl _mco_wrap_main\n"
  ".type _mco_wrap_main #function\n"
  ".hidden _mco_wrap_main\n"
  "_mco_wrap_main:\n"
#endif
  "  mov r0, r4\n"
  "  mov ip, r5\n"
  "  mov lr, r6\n"
  "  bx ip\n"
#ifndef __APPLE__
  ".size _mco_wrap_main, .-_mco_wrap_main\n"
#endif
);

static mco_result _mco_makectx(mco_coro* co, _mco_ctxbuf* ctx, void* stack_base, size_t stack_size) {
  ctx->d[0] = (void*)(co);
  ctx->d[1] = (void*)(_mco_main);
  ctx->d[2] = (void*)(0xdeaddead); /* Dummy return address. */
  ctx->lr = (void*)(_mco_wrap_main);
  ctx->sp = (void*)((size_t)stack_base + stack_size);
  return MCO_SUCCESS;
}

#elif defined(__aarch64__)

typedef struct _mco_ctxbuf {
  void *x[12]; /* x19-x30 */
  void *sp;
  void *lr;
  void *d[8]; /* d8-d15 */
} _mco_ctxbuf;

void _mco_wrap_main(void);
int _mco_switch(_mco_ctxbuf* from, _mco_ctxbuf* to);

__asm__(
  ".text\n"
#ifdef __APPLE__
  ".globl __mco_switch\n"
  "__mco_switch:\n"
#else
  ".globl _mco_switch\n"
  ".type _mco_switch #function\n"
  ".hidden _mco_switch\n"
  "_mco_switch:\n"
#endif

  "  mov x10, sp\n"
  "  mov x11, x30\n"
  "  stp x19, x20, [x0, #(0*16)]\n"
  "  stp x21, x22, [x0, #(1*16)]\n"
  "  stp d8, d9, [x0, #(7*16)]\n"
  "  stp x23, x24, [x0, #(2*16)]\n"
  "  stp d10, d11, [x0, #(8*16)]\n"
  "  stp x25, x26, [x0, #(3*16)]\n"
  "  stp d12, d13, [x0, #(9*16)]\n"
  "  stp x27, x28, [x0, #(4*16)]\n"
  "  stp d14, d15, [x0, #(10*16)]\n"
  "  stp x29, x30, [x0, #(5*16)]\n"
  "  stp x10, x11, [x0, #(6*16)]\n"
  "  ldp x19, x20, [x1, #(0*16)]\n"
  "  ldp x21, x22, [x1, #(1*16)]\n"
  "  ldp d8, d9, [x1, #(7*16)]\n"
  "  ldp x23, x24, [x1, #(2*16)]\n"
  "  ldp d10, d11, [x1, #(8*16)]\n"
  "  ldp x25, x26, [x1, #(3*16)]\n"
  "  ldp d12, d13, [x1, #(9*16)]\n"
  "  ldp x27, x28, [x1, #(4*16)]\n"
  "  ldp d14, d15, [x1, #(10*16)]\n"
  "  ldp x29, x30, [x1, #(5*16)]\n"
  "  ldp x10, x11, [x1, #(6*16)]\n"
  "  mov sp, x10\n"
  "  br x11\n"
#ifndef __APPLE__
  ".size _mco_switch, .-_mco_switch\n"
#endif
);

__asm__(
  ".text\n"
#ifdef __APPLE__
  ".globl __mco_wrap_main\n"
  "__mco_wrap_main:\n"
#else
  ".globl _mco_wrap_main\n"
  ".type _mco_wrap_main #function\n"
  ".hidden _mco_wrap_main\n"
  "_mco_wrap_main:\n"
#endif
  "  mov x0, x19\n"
  "  mov x30, x21\n"
  "  br x20\n"
#ifndef __APPLE__
  ".size _mco_wrap_main, .-_mco_wrap_main\n"
#endif
);

static mco_result _mco_makectx(mco_coro* co, _mco_ctxbuf* ctx, void* stack_base, size_t stack_size) {
  ctx->x[0] = (void*)(co);
  ctx->x[1] = (void*)(_mco_main);
  ctx->x[2] = (void*)(0xdeaddeaddeaddead); /* Dummy return address. */
  ctx->sp = (void*)((size_t)stack_base + stack_size);
  ctx->lr = (void*)(_mco_wrap_main);
  return MCO_SUCCESS;
}

#else

#error "Unsupported architecture for assembly method."

#endif /* ARCH */

#elif defined(MCO_USE_UCONTEXT)

#include <ucontext.h>

typedef ucontext_t _mco_ctxbuf;

#if defined(_LP64) || defined(__LP64__)
static void _mco_wrap_main(unsigned int lo, unsigned int hi) {
  mco_coro* co = (mco_coro*)(((size_t)lo) | (((size_t)hi) << 32)); /* Extract coroutine pointer. */
  _mco_main(co);
}
#else
static void _mco_wrap_main(unsigned int lo) {
  mco_coro* co = (mco_coro*)((size_t)lo); /* Extract coroutine pointer. */
  _mco_main(co);
}
#endif

static MCO_FORCE_INLINE void _mco_switch(_mco_ctxbuf* from, _mco_ctxbuf* to) {
  int res = swapcontext(from, to);
  _MCO_UNUSED(res);
  MCO_ASSERT(res == 0);
}

static mco_result _mco_makectx(mco_coro* co, _mco_ctxbuf* ctx, void* stack_base, size_t stack_size) {
  /* Initialize ucontext. */
  if(getcontext(ctx) != 0) {
    MCO_LOG("failed to get ucontext");
    return MCO_MAKE_CONTEXT_ERROR;
  }
  ctx->uc_link = NULL;  /* We never exit from _mco_wrap_main. */
  ctx->uc_stack.ss_sp = stack_base;
  ctx->uc_stack.ss_size = stack_size;
  unsigned int lo = (unsigned int)((size_t)co);
#if defined(_LP64) || defined(__LP64__)
  unsigned int hi = (unsigned int)(((size_t)co)>>32);
  makecontext(ctx, (void (*)(void))_mco_wrap_main, 2, lo, hi);
#else
  makecontext(ctx, (void (*)(void))_mco_wrap_main, 1, lo);
#endif
  return MCO_SUCCESS;
}

#endif /* defined(MCO_USE_UCONTEXT) */

#ifdef MCO_USE_VALGRIND
#include <valgrind/valgrind.h>
#endif

typedef struct _mco_context {
#ifdef MCO_USE_VALGRIND
  unsigned int valgrind_stack_id;
#endif
  _mco_ctxbuf ctx;
  _mco_ctxbuf back_ctx;
} _mco_context;

static void _mco_jumpin(mco_coro* co) {
  _mco_context* context = (_mco_context*)co->context;
  _mco_prepare_jumpin(co);
  _mco_switch(&context->back_ctx, &context->ctx); /* Do the context switch. */
}

static void _mco_jumpout(mco_coro* co) {
  _mco_context* context = (_mco_context*)co->context;
  _mco_prepare_jumpout(co);
  _mco_switch(&context->ctx, &context->back_ctx); /* Do the context switch. */
}

static mco_result _mco_create_context(mco_coro* co, mco_desc* desc) {
  /* Determine the context and stack address. */
  size_t co_addr = (size_t)co;
  size_t context_addr = _mco_align_forward(co_addr + sizeof(mco_coro), 16);
  size_t storage_addr = _mco_align_forward(context_addr + sizeof(_mco_context), 16);
  size_t stack_addr = _mco_align_forward(storage_addr + desc->storage_size, 16);
  /* Initialize context. */
  _mco_context* context = (_mco_context*)context_addr;
  memset(context, 0, sizeof(_mco_context));
  /* Initialize storage. */
  unsigned char* storage = (unsigned char*)storage_addr;
  /* Initialize stack. */
  void *stack_base = (void*)stack_addr;
  size_t stack_size = desc->stack_size;
  /* Make the context. */
  mco_result res = _mco_makectx(co, &context->ctx, stack_base, stack_size);
  if(res != MCO_SUCCESS) {
    return res;
  }
#ifdef MCO_USE_VALGRIND
  context->valgrind_stack_id = VALGRIND_STACK_REGISTER(stack_addr, stack_addr + stack_size);
#endif
  co->context = context;
  co->stack_base = stack_base;
  co->stack_size = stack_size;
  co->storage = storage;
  co->storage_size = desc->storage_size;
  return MCO_SUCCESS;
}

static void _mco_destroy_context(mco_coro* co) {
#ifdef MCO_USE_VALGRIND
  _mco_context* context = (_mco_context*)co->context;
  if(context && context->valgrind_stack_id != 0) {
    VALGRIND_STACK_DEREGISTER(context->valgrind_stack_id);
    context->valgrind_stack_id = 0;
  }
#else
  _MCO_UNUSED(co);
#endif
}

static MCO_FORCE_INLINE void _mco_init_desc_sizes(mco_desc* desc, size_t stack_size) {
  desc->coro_size = _mco_align_forward(sizeof(mco_coro), 16) +
                    _mco_align_forward(sizeof(_mco_context), 16) +
                    _mco_align_forward(desc->storage_size, 16) +
                    stack_size + 16;
  desc->stack_size = stack_size; /* This is just a hint, it won't be the real one. */
}

#endif /* defined(MCO_USE_UCONTEXT) || defined(MCO_USE_ASM) */

/* ---------------------------------------------------------------------------------------------- */

#ifdef MCO_USE_FIBERS

#ifdef _WIN32

typedef struct _mco_context {
  void* fib;
  void* back_fib;
} _mco_context;

static void _mco_jumpin(mco_coro* co) {
  void *cur_fib = GetCurrentFiber();
  if(!cur_fib || cur_fib == (void*)0x1e00) { /* See http://blogs.msdn.com/oldnewthing/archive/2004/12/31/344799.aspx */
    cur_fib = ConvertThreadToFiber(NULL);
  }
  MCO_ASSERT(cur_fib != NULL);
  _mco_context* context = (_mco_context*)co->context;
  context->back_fib = cur_fib;
  _mco_prepare_jumpin(co);
  SwitchToFiber(context->fib);
}

static void CALLBACK _mco_wrap_main(void* co) {
  _mco_main((mco_coro*)co);
}

static void _mco_jumpout(mco_coro* co) {
  _mco_context* context = (_mco_context*)co->context;
  void* back_fib = context->back_fib;
  MCO_ASSERT(back_fib != NULL);
  context->back_fib = NULL;
  _mco_prepare_jumpout(co);
  SwitchToFiber(back_fib);
}

/* Reverse engineered Fiber struct, used to get stack base. */
typedef struct _mco_fiber {
  LPVOID param;                /* fiber param */
  void* except;                /* saved exception handlers list */
  void* stack_base;            /* top of fiber stack */
  void* stack_limit;           /* fiber stack low-water mark */
  void* stack_allocation;      /* base of the fiber stack allocation */
  CONTEXT context;             /* fiber context */
  DWORD flags;                 /* fiber flags */
  LPFIBER_START_ROUTINE start; /* start routine */
  void **fls_slots;            /* fiber storage slots */
} _mco_fiber;

static mco_result _mco_create_context(mco_coro* co, mco_desc* desc) {
  /* Determine the context address. */
  size_t co_addr = (size_t)co;
  size_t context_addr = _mco_align_forward(co_addr + sizeof(mco_coro), 16);
  size_t storage_addr = _mco_align_forward(context_addr + sizeof(_mco_context), 16);
  /* Initialize context. */
  _mco_context* context = (_mco_context*)context_addr;
  memset(context, 0, sizeof(_mco_context));
  /* Initialize storage. */
  unsigned char* storage = (unsigned char*)storage_addr;
  /* Create the fiber. */
  _mco_fiber* fib = (_mco_fiber*)CreateFiberEx(desc->stack_size, desc->stack_size, FIBER_FLAG_FLOAT_SWITCH, _mco_wrap_main, co);
  if(!fib) {
    MCO_LOG("failed to create fiber");
    return MCO_MAKE_CONTEXT_ERROR;
  }
  context->fib = fib;
  co->context = context;
  co->stack_base = (void*)((size_t)fib->stack_base - desc->stack_size);
  co->stack_size = desc->stack_size;
  co->storage = storage;
  co->storage_size = desc->storage_size;
  return MCO_SUCCESS;
}

static void _mco_destroy_context(mco_coro* co) {
  _mco_context* context = (_mco_context*)co->context;
  if(context && context->fib) {
    DeleteFiber(context->fib);
    context->fib = NULL;
  }
}

static MCO_FORCE_INLINE void _mco_init_desc_sizes(mco_desc* desc, size_t stack_size) {
  desc->coro_size = _mco_align_forward(sizeof(mco_coro), 16) +
                    _mco_align_forward(sizeof(_mco_context), 16) +
                    _mco_align_forward(desc->storage_size, 16) +
                    16;
  desc->stack_size = stack_size;
}

#elif defined(__EMSCRIPTEN__)

#include <emscripten/fiber.h>

#ifndef MCO_ASYNCFY_STACK_SIZE
#define MCO_ASYNCFY_STACK_SIZE 16384
#endif

typedef struct _mco_context {
  emscripten_fiber_t fib;
  emscripten_fiber_t* back_fib;
} _mco_context;

static emscripten_fiber_t* running_fib = NULL;
static unsigned char main_asyncify_stack[MCO_ASYNCFY_STACK_SIZE];
static emscripten_fiber_t main_fib;

static void _mco_wrap_main(void* co) {
  _mco_main((mco_coro*)co);
}

static void _mco_jumpin(mco_coro* co) {
  _mco_context* context = (_mco_context*)co->context;
  emscripten_fiber_t* back_fib = running_fib;
  if(!back_fib) {
    back_fib = &main_fib;
    emscripten_fiber_init_from_current_context(back_fib, main_asyncify_stack, MCO_ASYNCFY_STACK_SIZE);
  }
  running_fib = &context->fib;
  context->back_fib = back_fib;
  _mco_prepare_jumpin(co);
  emscripten_fiber_swap(back_fib, &context->fib); /* Do the context switch. */
}

static void _mco_jumpout(mco_coro* co) {
  _mco_context* context = (_mco_context*)co->context;
  running_fib = context->back_fib;
  _mco_prepare_jumpout(co);
  emscripten_fiber_swap(&context->fib, context->back_fib); /* Do the context switch. */
}

static mco_result _mco_create_context(mco_coro* co, mco_desc* desc) {
  if(emscripten_has_asyncify() != 1) {
    MCO_LOG("failed to create fiber because ASYNCIFY is not enabled");
    return MCO_MAKE_CONTEXT_ERROR;
  }
  /* Determine the context address. */
  size_t co_addr = (size_t)co;
  size_t context_addr = _mco_align_forward(co_addr + sizeof(mco_coro), 16);
  size_t storage_addr = _mco_align_forward(context_addr + sizeof(_mco_context), 16);
  size_t stack_addr = _mco_align_forward(storage_addr + desc->storage_size, 16);
  size_t asyncify_stack_addr = _mco_align_forward(stack_addr + desc->stack_size, 16);
  /* Initialize context. */
  _mco_context* context = (_mco_context*)context_addr;
  memset(context, 0, sizeof(_mco_context));
  /* Initialize storage. */
  unsigned char* storage = (unsigned char*)storage_addr;
  /* Initialize stack. */
  void *stack_base = (void*)stack_addr;
  size_t stack_size = asyncify_stack_addr - stack_addr;
  void *asyncify_stack_base = (void*)asyncify_stack_addr;
  size_t asyncify_stack_size = co_addr + desc->coro_size - asyncify_stack_addr;
  /* Create the fiber. */
  emscripten_fiber_init(&context->fib, _mco_wrap_main, co, stack_base, stack_size, asyncify_stack_base, asyncify_stack_size);
  co->context = context;
  co->stack_base = stack_base;
  co->stack_size = stack_size;
  co->storage = storage;
  co->storage_size = desc->storage_size;
  return MCO_SUCCESS;
}

static void _mco_destroy_context(mco_coro* co) {
  /* Nothing to do. */
  _MCO_UNUSED(co);
}

static MCO_FORCE_INLINE void _mco_init_desc_sizes(mco_desc* desc, size_t stack_size) {
  desc->coro_size = _mco_align_forward(sizeof(mco_coro), 16) +
                    _mco_align_forward(sizeof(_mco_context), 16) +
                    _mco_align_forward(desc->storage_size, 16) +
                    _mco_align_forward(stack_size, 16) +
                    _mco_align_forward(MCO_ASYNCFY_STACK_SIZE, 16) +
                    16;
  desc->stack_size = stack_size; /* This is just a hint, it won't be the real one. */
}

#else

#error "Unsupported architecture for fibers method."

#endif

#endif /* MCO_USE_FIBERS */

/* ---------------------------------------------------------------------------------------------- */

#ifdef MCO_USE_ASYNCIFY

typedef struct _asyncify_stack_region {
  void* start;
  void* limit;
} _asyncify_stack_region;

typedef struct _mco_context {
  int rewind_id;
  _asyncify_stack_region stack_region;
} _mco_context;

__attribute__((import_module("asyncify"), import_name("start_unwind"))) void _asyncify_start_unwind(void*);
__attribute__((import_module("asyncify"), import_name("stop_unwind")))  void _asyncify_stop_unwind();
__attribute__((import_module("asyncify"), import_name("start_rewind"))) void _asyncify_start_rewind(void*);
__attribute__((import_module("asyncify"), import_name("stop_rewind")))  void _asyncify_stop_rewind();

MCO_NO_INLINE void _mco_jumpin(mco_coro* co) {
  _mco_context* context = (_mco_context*)co->context;
  _mco_prepare_jumpin(co);
  if(context->rewind_id > 0) { /* Begin rewinding until last yield point. */
    _asyncify_start_rewind(&context->stack_region);
  }
  _mco_main(co); /* Run the coroutine function. */
  _asyncify_stop_unwind(); /* Stop saving coroutine stack. */
}

static MCO_NO_INLINE void _mco_finish_jumpout(mco_coro* co, volatile int rewind_id) {
  _mco_context* context = (_mco_context*)co->context;
  int next_rewind_id = context->rewind_id + 1;
  if(rewind_id == next_rewind_id) { /* Begins unwinding the stack (save locals and call stack to rewind later) */
    _mco_prepare_jumpout(co);
    context->rewind_id = next_rewind_id;
    _asyncify_start_unwind(&context->stack_region);
  } else if(rewind_id == context->rewind_id) { /* Continue from yield point. */
    _asyncify_stop_rewind();
  }
  /* Otherwise, we should be rewinding, let it continue... */
}

MCO_NO_INLINE void _mco_jumpout(mco_coro* co) {
  _mco_context* context = (_mco_context*)co->context;
  /*
  Save rewind point into a local, that should be restored when rewinding.
  That is "rewind_id != co->rewind_id + 1" may be true when rewinding.
  Use volatile here just to be safe from compiler optimizing this out.
  */
  volatile int rewind_id = context->rewind_id + 1;
  _mco_finish_jumpout(co, rewind_id);
}

static mco_result _mco_create_context(mco_coro* co, mco_desc* desc) {
  /* Determine the context address. */
  size_t co_addr = (size_t)co;
  size_t context_addr = _mco_align_forward(co_addr + sizeof(mco_coro), 16);
  size_t storage_addr = _mco_align_forward(context_addr + sizeof(_mco_context), 16);
  size_t stack_addr = _mco_align_forward(storage_addr + desc->storage_size, 16);
  /* Initialize context. */
  _mco_context* context = (_mco_context*)context_addr;
  memset(context, 0, sizeof(_mco_context));
  /* Initialize storage. */
  unsigned char* storage = (unsigned char*)storage_addr;
  /* Initialize stack. */
  void *stack_base = (void*)stack_addr;
  size_t stack_size = desc->stack_size;
  context->stack_region.start = stack_base;
  context->stack_region.limit = (void*)((size_t)stack_base + stack_size);
  co->context = context;
  co->stack_base = stack_base;
  co->stack_size = stack_size;
  co->storage = storage;
  co->storage_size = desc->storage_size;
  return MCO_SUCCESS;
}

static void _mco_destroy_context(mco_coro* co) {
  /* Nothing to do. */
  _MCO_UNUSED(co);
}

static MCO_FORCE_INLINE void _mco_init_desc_sizes(mco_desc* desc, size_t stack_size) {
  desc->coro_size = _mco_align_forward(sizeof(mco_coro), 16) +
                    _mco_align_forward(sizeof(_mco_context), 16) +
                    _mco_align_forward(desc->storage_size, 16) +
                    _mco_align_forward(stack_size, 16) +
                    16;
  desc->stack_size = stack_size; /* This is just a hint, it won't be the real one. */
}

#endif /* MCO_USE_ASYNCIFY */

/* ---------------------------------------------------------------------------------------------- */

mco_desc mco_desc_init(void (*func)(mco_coro* co), size_t stack_size) {
  if(stack_size != 0) {
    /* Stack size should be at least `MCO_MIN_STACK_SIZE`. */
    if(stack_size < MCO_MIN_STACK_SIZE) {
      stack_size = MCO_MIN_STACK_SIZE;
    }
  } else {
    stack_size = MCO_DEFAULT_STACK_SIZE;
  }
  stack_size = _mco_align_forward(stack_size, 16); /* Stack size should be aligned to 16 bytes. */
  mco_desc desc;
  memset(&desc, 0, sizeof(mco_desc));
#ifndef MCO_NO_DEFAULT_ALLOCATOR
  /* Set default allocators. */
  desc.alloc_cb = mco_alloc;
  desc.dealloc_cb = mco_dealloc;
#endif
  desc.func = func;
  desc.storage_size = MCO_DEFAULT_STORAGE_SIZE;
  _mco_init_desc_sizes(&desc, stack_size);
  return desc;
}

static mco_result _mco_validate_desc(mco_desc* desc) {
  if(!desc) {
    MCO_LOG("coroutine description is NULL");
    return MCO_INVALID_ARGUMENTS;
  }
  if(!desc->func) {
    MCO_LOG("coroutine function in invalid");
    return MCO_INVALID_ARGUMENTS;
  }
  if(desc->stack_size < MCO_MIN_STACK_SIZE) {
    MCO_LOG("coroutine stack size is too small");
    return MCO_INVALID_ARGUMENTS;
  }
  if(desc->coro_size < sizeof(mco_coro)) {
    MCO_LOG("coroutine size is invalid");
    return MCO_INVALID_ARGUMENTS;
  }
  return MCO_SUCCESS;
}

mco_result mco_init(mco_coro* co, mco_desc* desc) {
  if(!co) {
    MCO_LOG("attempt to initialize an invalid coroutine");
    return MCO_INVALID_COROUTINE;
  }
  memset(co, 0, sizeof(mco_coro));
  /* Validate coroutine description. */
  mco_result res = _mco_validate_desc(desc);
  if(res != MCO_SUCCESS)
    return res;
  /* Create the coroutine. */
  res = _mco_create_context(co, desc);
  if(res != MCO_SUCCESS)
    return res;
  co->state = MCO_SUSPENDED; /* We initialize in suspended state. */
  co->dealloc_cb = desc->dealloc_cb;
  co->coro_size = desc->coro_size;
  co->allocator_data = desc->allocator_data;
  co->func = desc->func;
  co->user_data = desc->user_data;
#ifdef _MCO_USE_TSAN
  co->tsan_fiber = __tsan_create_fiber(0);
#endif
  co->magic_number = MCO_MAGIC_NUMBER;
  return MCO_SUCCESS;
}

mco_result mco_uninit(mco_coro* co) {
  if(!co) {
    MCO_LOG("attempt to uninitialize an invalid coroutine");
    return MCO_INVALID_COROUTINE;
  }
  /* Cannot uninitialize while running. */
  if(!(co->state == MCO_SUSPENDED || co->state == MCO_DEAD)) {
    MCO_LOG("attempt to uninitialize a coroutine that is not dead or suspended");
    return MCO_INVALID_OPERATION;
  }
  /* The coroutine is now dead and cannot be used anymore. */
  co->state = MCO_DEAD;
#ifdef _MCO_USE_TSAN
  if(co->tsan_fiber != NULL) {
    __tsan_destroy_fiber(co->tsan_fiber);
    co->tsan_fiber = NULL;
  }
#endif
  _mco_destroy_context(co);
  return MCO_SUCCESS;
}

mco_result mco_create(mco_coro** out_co, mco_desc* desc) {
  /* Validate input. */
  if(!out_co) {
    MCO_LOG("coroutine output pointer is NULL");
    return MCO_INVALID_POINTER;
  }
  if(!desc || !desc->alloc_cb || !desc->dealloc_cb) {
    *out_co = NULL;
    MCO_LOG("coroutine allocator description is not set");
    return MCO_INVALID_ARGUMENTS;
  }
  /* Allocate the coroutine. */
  mco_coro* co = (mco_coro*)desc->alloc_cb(desc->coro_size, desc->allocator_data);
  if(!co) {
    MCO_LOG("coroutine allocation failed");
    *out_co = NULL;
    return MCO_OUT_OF_MEMORY;
  }
  /* Initialize the coroutine. */
  mco_result res = mco_init(co, desc);
  if(res != MCO_SUCCESS) {
    desc->dealloc_cb(co, desc->coro_size, desc->allocator_data);
    *out_co = NULL;
    return res;
  }
  *out_co = co;
  return MCO_SUCCESS;
}

mco_result mco_destroy(mco_coro* co) {
  if(!co) {
    MCO_LOG("attempt to destroy an invalid coroutine");
    return MCO_INVALID_COROUTINE;
  }
  /* Uninitialize the coroutine first. */
  mco_result res = mco_uninit(co);
  if(res != MCO_SUCCESS)
    return res;
  /* Free the coroutine. */
  if(!co->dealloc_cb) {
    MCO_LOG("attempt destroy a coroutine that has no free callback");
    return MCO_INVALID_POINTER;
  }
  co->dealloc_cb(co, co->coro_size, co->allocator_data);
  return MCO_SUCCESS;
}

mco_result mco_resume(mco_coro* co) {
  if(!co) {
    MCO_LOG("attempt to resume an invalid coroutine");
    return MCO_INVALID_COROUTINE;
  }
  if(co->state != MCO_SUSPENDED) { /* Can only resume coroutines that are suspended. */
    MCO_LOG("attempt to resume a coroutine that is not suspended");
    return MCO_NOT_SUSPENDED;
  }
  co->state = MCO_RUNNING; /* The coroutine is now running. */
  _mco_jumpin(co);
  return MCO_SUCCESS;
}

mco_result mco_yield(mco_coro* co) {
  if(!co) {
    MCO_LOG("attempt to yield an invalid coroutine");
    return MCO_INVALID_COROUTINE;
  }
#ifdef MCO_USE_ASYNCIFY
  /* Asyncify already checks for stack overflow. */
#else
  /* This check happens when the stack overflow already happened, but better later than never. */
  volatile size_t dummy;
  size_t stack_addr = (size_t)&dummy;
  size_t stack_min = (size_t)co->stack_base;
  size_t stack_max = stack_min + co->stack_size;
  if(co->magic_number != MCO_MAGIC_NUMBER || stack_addr < stack_min || stack_addr > stack_max) { /* Stack overflow. */
    MCO_LOG("coroutine stack overflow, try increasing the stack size");
    return MCO_STACK_OVERFLOW;
  }
#endif
  if(co->state != MCO_RUNNING) {  /* Can only yield coroutines that are running. */
    MCO_LOG("attempt to yield a coroutine that is not running");
    return MCO_NOT_RUNNING;
  }
  co->state = MCO_SUSPENDED; /* The coroutine is now suspended. */
  _mco_jumpout(co);
  return MCO_SUCCESS;
}

mco_state mco_status(mco_coro* co) {
  if(co != NULL) {
    return co->state;
  }
  return MCO_DEAD;
}

void* mco_get_user_data(mco_coro* co) {
  if(co != NULL) {
    return co->user_data;
  }
  return NULL;
}

mco_result mco_push(mco_coro* co, const void* src, size_t len) {
  if(!co) {
    MCO_LOG("attempt to use an invalid coroutine");
    return MCO_INVALID_COROUTINE;
  } else if(len > 0) {
    size_t bytes_stored = co->bytes_stored + len;
    if(bytes_stored > co->storage_size) {
      MCO_LOG("attempt to push too many bytes into coroutine storage");
      return MCO_NOT_ENOUGH_SPACE;
    }
    if(!src) {
      MCO_LOG("attempt push a null pointer into coroutine storage");
      return MCO_INVALID_POINTER;
    }
    memcpy(&co->storage[co->bytes_stored], src, len);
    co->bytes_stored = bytes_stored;
  }
  return MCO_SUCCESS;
}

mco_result mco_pop(mco_coro* co, void* dest, size_t len) {
  if(!co) {
    MCO_LOG("attempt to use an invalid coroutine");
    return MCO_INVALID_COROUTINE;
  } else if(len > 0) {
    if(len > co->bytes_stored) {
      MCO_LOG("attempt to pop too many bytes from coroutine storage");
      return MCO_NOT_ENOUGH_SPACE;
    }
    size_t bytes_stored = co->bytes_stored - len;
    if(dest) {
      memcpy(dest, &co->storage[bytes_stored], len);
    }
    co->bytes_stored = bytes_stored;
#ifdef MCO_ZERO_MEMORY
    /* Clear garbage in the discarded storage. */
    memset(&co->storage[bytes_stored], 0, len);
#endif
  }
  return MCO_SUCCESS;
}

mco_result mco_peek(mco_coro* co, void* dest, size_t len) {
  if(!co) {
    MCO_LOG("attempt to use an invalid coroutine");
    return MCO_INVALID_COROUTINE;
  } else if(len > 0) {
    if(len > co->bytes_stored) {
      MCO_LOG("attempt to peek too many bytes from coroutine storage");
      return MCO_NOT_ENOUGH_SPACE;
    }
    if(!dest) {
      MCO_LOG("attempt peek into a null pointer");
      return MCO_INVALID_POINTER;
    }
    memcpy(dest, &co->storage[co->bytes_stored - len], len);
  }
  return MCO_SUCCESS;
}

size_t mco_get_bytes_stored(mco_coro* co) {
  if(co == NULL) {
    return 0;
  }
  return co->bytes_stored;
}

size_t mco_get_storage_size(mco_coro* co) {
  if(co == NULL) {
    return 0;
  }
  return co->storage_size;
}

#ifdef MCO_NO_MULTITHREAD
mco_coro* mco_running(void) {
  return mco_current_co;
}
#else
static MCO_NO_INLINE mco_coro* _mco_running(void) {
  return mco_current_co;
}
mco_coro* mco_running(void) {
  /*
  Compilers aggressively optimize the use of TLS by caching loads.
  Since fiber code can migrate between threads it’s possible for the load to be stale.
  To prevent this from happening we avoid inline functions.
  */
  mco_coro* (*volatile func)(void) = _mco_running;
  return func();
}
#endif

const char* mco_result_description(mco_result res) {
  switch(res) {
    case MCO_SUCCESS:
      return "No error";
    case MCO_GENERIC_ERROR:
      return "Generic error";
    case MCO_INVALID_POINTER:
      return "Invalid pointer";
    case MCO_INVALID_COROUTINE:
      return "Invalid coroutine";
    case MCO_NOT_SUSPENDED:
      return "Coroutine not suspended";
    case MCO_NOT_RUNNING:
      return "Coroutine not running";
    case MCO_MAKE_CONTEXT_ERROR:
      return "Make context error";
    case MCO_SWITCH_CONTEXT_ERROR:
      return "Switch context error";
    case MCO_NOT_ENOUGH_SPACE:
      return "Not enough space";
    case MCO_OUT_OF_MEMORY:
      return "Out of memory";
    case MCO_INVALID_ARGUMENTS:
      return "Invalid arguments";
    case MCO_INVALID_OPERATION:
      return "Invalid operation";
    case MCO_STACK_OVERFLOW:
      return "Stack overflow";
  }
  return "Unknown error";
}

#ifdef __cplusplus
}
#endif

#endif /* MINICORO_IMPL */

/*
This software is available as a choice of the following licenses. Choose
whichever you prefer.

===============================================================================
ALTERNATIVE 1 - Public Domain (www.unlicense.org)
===============================================================================
This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or distribute this
software, either in source code form or as a compiled binary, for any purpose,
commercial or non-commercial, and by any means.

In jurisdictions that recognize copyright laws, the author or authors of this
software dedicate any and all copyright interest in the software to the public
domain. We make this dedication for the benefit of the public at large and to
the detriment of our heirs and successors. We intend this dedication to be an
overt act of relinquishment in perpetuity of all present and future rights to
this software under copyright law.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

For more information, please refer to <http://unlicense.org/>

===============================================================================
ALTERNATIVE 2 - MIT No Attribution
===============================================================================
Copyright (c) 2021-2023 Eduardo Bart (https://github.com/edubart/minicoro)

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is furnished to do
so.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/



#define JOBS_DEBUG_TRACY_ZONES 0
#define JOBS_USE_ANDERSON_LOCK 1 // Experimental


namespace _limits
{
    inline constexpr uint32 JOBS_MAX_INSTANCES = 1024;
    inline constexpr uint32 JOBS_MAX_PENDING = JOBS_MAX_INSTANCES*4;

#ifdef TRACY_ENABLE
    inline constexpr uint32 JOBS_TRACY_MAX_STACKDEPTH = 8;
#endif
}

inline constexpr size_t JOBS_STACK_SIZES[uint32(JobsStackSize::_Count)] = {
    64*SIZE_KB,
    512*SIZE_KB,
    2*SIZE_MB
};

#if JOBS_USE_ANDERSON_LOCK
struct alignas(CACHE_LINE_SIZE) JobsAndersonLockThread
{
    uint32 locked;
    uint8 _padding1[CACHE_LINE_SIZE - sizeof(uint32)];
    uint32 position;
    uint8 _padding2[CACHE_LINE_SIZE - sizeof(uint32)];
};

struct alignas(CACHE_LINE_SIZE) JobsAndersonLock
{
    inline void Initialize(uint32 numThreads, JobsAndersonLockThread* threads);
    inline uint32 Enter();
    inline void Exit(uint32 slot);

    JobsAndersonLockThread* mSlots;
    uint32 mCount;
    uint32 mWrap;
    uint32 mMask;
    char _padding1[CACHE_LINE_SIZE - sizeof(uint32)*3 - sizeof(void*)];
    uint32 mNext;
    char _padding2[CACHE_LINE_SIZE - sizeof(uint32)];
};

struct JobsAndersonLockScope
{
    JobsAndersonLockScope() = delete;
    JobsAndersonLockScope(const JobsAndersonLockScope& _lock) = delete;
    inline explicit JobsAndersonLockScope(JobsAndersonLock& _lock) : mLock(_lock) { mSlot = mLock.Enter(); }
    inline ~JobsAndersonLockScope() { mLock.Exit(mSlot); }
        
private:
    JobsAndersonLock& mLock;
    uint32 mSlot;
};

using JobsLock = JobsAndersonLock;
using JobsLockScope = JobsAndersonLockScope;
#else   // JOBS_CONFIG_USE_ANDERSON_LOCK
using JobsLock = SpinLockMutex;
using JobsLockScope = SpinLockMutex;
#endif  // else:JOBS_CONFIG_USE_ANDERSON_LOCK

struct JobsFiber;

struct JobsFiberProperties
{
    JobsCallback callback;
    void* userData;
    JobsInstance* instance;
    JobsPriority prio;
    JobsFiber* fiber;
    JobsFiberProperties* next;
    JobsFiberProperties* prev;
    JobsStackSize stackSize;
    uint32 index;
};

struct JobsSignalInternal
{
    AtomicUint32 signaled;
    uint8 reserved[CACHE_LINE_SIZE-4];
    AtomicUint32 value;
};
static_assert(sizeof(JobsSignalInternal) <= sizeof(JobsSignal), "Mismatch sizes between JobsSignal and JobsSignalInternal");

#ifdef TRACY_ENABLE
struct JobsTracyZone
{
    TracyCZoneCtx ctx;
    const ___tracy_source_location_data* sourceLoc;
};
#endif

struct JobsFiber
{
    uint32 ownerTid;
    mco_coro* co;
    mco_desc coDesc;
    AtomicUint32* childCounter;
    JobsFiberProperties* props;
    JobsSignalInternal* signal;
    #ifdef TRACY_ENABLE
    StaticArray<JobsTracyZone, _limits::JOBS_TRACY_MAX_STACKDEPTH> tracyZonesStack;
    #endif
};

struct JobsThreadData
{
    JobsFiber* curFiber;
    JobsInstance* waitInstance;
    JobsType type;
    uint32 threadIndex;
    uint32 threadId;
    bool init;
};

struct alignas(CACHE_LINE_SIZE) JobsInstance
{
    AtomicUint32 counter;                       // Atomic counter of sub items within a job 
    uint8 _padding1[CACHE_LINE_SIZE - 4];        // padding for the atomic var to fit inside a cache line
    JobsType type;
    bool isAutoDelete;
    uint8 _padding2[CACHE_LINE_SIZE - sizeof(JobsType) - sizeof(bool)];
};

struct JobsWaitingList
{
    JobsFiberProperties* mWaitingList[static_cast<uint32>(JobsPriority::_Count)];
    JobsFiberProperties* mWaitingListLast[static_cast<uint32>(JobsPriority::_Count)];

    inline void AddToList(JobsFiberProperties* props);
    inline void RemoveFromList(JobsFiberProperties* props);
};

template <typename _T, uint32 _MaxCount> 
struct alignas(CACHE_LINE_SIZE) JobsAtomicPool
{
    static JobsAtomicPool<_T, _MaxCount>* Create(MemAllocator* alloc);
    static void Destroy(JobsAtomicPool<_T, _MaxCount>* p, MemAllocator* alloc);

    _T* New();
    void Delete(_T* props);

    AtomicUint32 mIndex;
    uint8 _reserved1[CACHE_LINE_SIZE - sizeof(AtomicUint32)];
    _T** mPtrs;
    _T* mProps;
    uint8 _reserved2[CACHE_LINE_SIZE - sizeof(void*) * 2];
};

struct JobsFiberMemAllocator
{
    struct Pool
    {
        uint8** ptrs;
        uint8* buffer;
        Pool* next;
        uint32 index;
    };

    SpinLockMutex mLock;

    size_t mAllocationSize;
    uint32 mBufferAlignment;
    Pool* mPools;
    uint32 mNumItemsInPool;

    void Initialize(size_t allocationSize);
    void Release();
    void* Allocate();
    void Free(void* ptr);
    Pool* CreatePool();
};

struct JobsContext
{
    JobsInitParams initParams;
    Thread* threads[uint32(JobsType::_Count)];
    uint32 numThreads[uint32(JobsType::_Count)];
    uint8 _padding1[8];

    JobsFiberMemAllocator fiberAllocators[uint32(JobsStackSize::_Count)];
    JobsWaitingList waitingLists[uint32(JobsType::_Count)];
    uint8 _padding3[sizeof(JobsWaitingList) * 2 - alignof(JobsLock)];
    JobsLock waitingListLock;
    Semaphore semaphores[uint32(JobsType::_Count)];
    JobsAtomicPool<JobsInstance, _limits::JOBS_MAX_INSTANCES>* instancePool;
    JobsAtomicPool<JobsFiberProperties, _limits::JOBS_MAX_PENDING>* fiberPropsPool;

    AtomicUint32 quit;
};

static JobsContext gJobs;
static thread_local bool gIsInFiber = false;

namespace Jobs
{
    NO_INLINE static JobsThreadData* _GetThreadData(bool allocateNew = false) 
    { 
        static thread_local JobsThreadData* data = nullptr;

        if (allocateNew) {
            ASSERT(data == nullptr);
            data = Mem::AllocZeroTyped<JobsThreadData>();
        }
        else if (data) {
            ASSERT(data->init);
        }

        return data; 
    }

    static void _EntryFn(mco_coro* co)
    {
        ASSERT(co);
        JobsFiber* fiber = reinterpret_cast<JobsFiber*>(co->storage);
        if (fiber) {
            JobsFiberProperties* props = fiber->props;
            ASSERT(props->callback);
            props->callback(props->index, props->userData);
        }
    }

    static JobsFiber* _CreateFiber(JobsFiberProperties* props)
    {
        auto McoMallocFn = [](size_t size, void*)->void*
        {
            JobsFiberMemAllocator* alloc = nullptr;
            for (uint32 i = 0; i < uint32(JobsStackSize::_Count); i++) {
                if (size <= JOBS_STACK_SIZES[i] + 4096) {
                    alloc = &gJobs.fiberAllocators[i];
                    break;
                }
            }
            ASSERT(alloc);

            return alloc->Allocate();
        };

        auto McoFreeFn = [](void* ptr, size_t size, void*)
        {
            JobsFiberMemAllocator* alloc = nullptr;
            for (uint32 i = 0; i < uint32(JobsStackSize::_Count); i++) {
                if (size <= JOBS_STACK_SIZES[i] + 4096) {
                    alloc = &gJobs.fiberAllocators[i];
                    break;
                }
            }
            ASSERT(alloc);

            return alloc->Free(ptr);
        };    

        ASSERT(props->stackSize != JobsStackSize::_Count);
        mco_desc desc = mco_desc_init(_EntryFn, JOBS_STACK_SIZES[uint32(props->stackSize)]);
        desc.alloc_cb = McoMallocFn;
        desc.dealloc_cb = McoFreeFn;

        mco_coro* co;
        mco_result r = mco_create(&co, &desc);
        if (r != MCO_SUCCESS) {
            MEM_FAIL();
            return nullptr;
        }

        JobsFiber fiber {
            .ownerTid = 0,
            .co = co,
            .coDesc = desc,
            .props = props
        };

        mco_push(co, &fiber, sizeof(fiber));

        return reinterpret_cast<JobsFiber*>(co->storage);
    }

    NO_INLINE static void _DestroyFiber(JobsFiber* fiber)
    {
        ASSERT(fiber->props);
        ASSERT(fiber->props->next == nullptr && fiber->props->prev == nullptr);

        gJobs.fiberPropsPool->Delete(fiber->props);

        ASSERT(fiber->co);
        mco_destroy(fiber->co);
    }

    static void _SetFiberToCurrentThread(JobsFiber* fiber)
    {
        ASSERT(fiber);
        ASSERT(_GetThreadData());
        ASSERT(_GetThreadData()->curFiber == nullptr);

        JobsThreadData* tdata = _GetThreadData();
        fiber->ownerTid = 0;
        tdata->curFiber = fiber;
        gIsInFiber = true;
    
        ASSERT(fiber->props->next == nullptr);

        #ifdef TRACY_ENABLE
        if (!fiber->tracyZonesStack.IsEmpty()) {
            for (JobsTracyZone& zone : fiber->tracyZonesStack) {
                #if !defined(TRACY_NO_CALLSTACK)
                    zone.ctx = ___tracy_emit_zone_begin_callstack(zone.sourceLoc, TRACY_CALLSTACK, zone.ctx.active);
                #else
                    zone.ctx = ___tracy_emit_zone_begin(zone.sourceLoc, zone.ctx.active);
                #endif
            }
        }
        #endif

        {
            mco_coro* co = fiber->co;

            ASSERT(co->state != MCO_RUNNING);
            ASSERT(co->state != MCO_DEAD);
            co->state = MCO_RUNNING;

            #ifdef _MCO_USE_ASAN
            __sanitizer_start_switch_fiber(&co->asan_prev_stack, co->stack_base, co->stack_size);
            #endif

            #ifdef _MCO_USE_TSAN
            co->tsan_prev_fiber = __tsan_get_current_fiber();
            __tsan_switch_to_fiber(co->tsan_fiber, 0);
            #endif
    
            _mco_context* context = (_mco_context*)co->context;
            _mco_switch(&context->back_ctx, &context->ctx);
        }
    
        #ifdef TRACY_ENABLE
        if (!fiber->tracyZonesStack.IsEmpty() && fiber->co->state != MCO_DEAD) {
            for (uint32 i = fiber->tracyZonesStack.Count(); i-- > 0;) 
                TracyCZoneEnd(fiber->tracyZonesStack[i].ctx);
        }
        #endif

        tdata->curFiber = nullptr;
        gIsInFiber = false;
    
        JobsInstance* inst = fiber->props->instance;
        if (fiber->co->state == MCO_DEAD) {
            #ifdef TRACY_ENABLE
            ASSERT_MSG(fiber->tracyZonesStack.IsEmpty(), "Tracy zones stack currently have %u remaining items", fiber->tracyZonesStack.Count());
            #endif

            if (Atomic::FetchSub(&inst->counter, 1) == 1) {     // Job is finished with all the fibers
                if (inst->isAutoDelete) {
                    gJobs.instancePool->Delete(inst);
                }
            }

            _DestroyFiber(fiber);
        }
        else {
            ASSERT(fiber->co->state == MCO_SUSPENDED);
            fiber->childCounter = &tdata->waitInstance->counter;
            tdata->waitInstance = nullptr;
            uint32 typeIndex = uint32(inst->type);

            {
                JobsLockScope lk(gJobs.waitingListLock);
                gJobs.waitingLists[typeIndex].AddToList(fiber->props);
            }

            gJobs.semaphores[typeIndex].Post();
        }
    }

    static int _WorkerThread(void* userData)
    {
        JobsThreadData* tdata = _GetThreadData(true);
        uint64 param = PtrToInt<uint64>(userData);
        tdata->threadIndex = (param >> 32) & 0xffffffff;
        tdata->type = static_cast<JobsType>(uint32(param & 0xffffffff));
        tdata->threadId = Thread::GetCurrentId();
        tdata->init = true;

        uint32 spinCount = !PLATFORM_MOBILE;
        uint32 typeIndex = uint32(tdata->type);
    
        while (Atomic::LoadExplicit(&gJobs.quit, AtomicMemoryOrder::Acquire) != 1) {
            gJobs.semaphores[typeIndex].Wait();

            bool waitingListIsLive = false;
            JobsFiber* fiber = nullptr;

            {
                JobsLockScope lock(gJobs.waitingListLock);
                for (uint32 prioIdx = 0; prioIdx < static_cast<uint32>(JobsPriority::_Count); prioIdx++) {
                    JobsWaitingList* list = &gJobs.waitingLists[typeIndex];
                    JobsFiberProperties* props = list->mWaitingList[prioIdx];
    
                    while (props) {
                        waitingListIsLive = true;

                        JobsFiber* tmpFiber = props->fiber;
                        AtomicUint32 one = 1;
                        if (tmpFiber == nullptr || 
                            ((tmpFiber->childCounter == nullptr || Atomic::LoadExplicit(tmpFiber->childCounter, AtomicMemoryOrder::Acquire) == 0) &&
                            (tmpFiber->signal == nullptr || Atomic::CompareExchange_Strong(&tmpFiber->signal->signaled, &one, 0))))
                        {
                            if (tmpFiber == nullptr)
                                props->fiber = _CreateFiber(props);

                            fiber = props->fiber;
                            fiber->childCounter = nullptr;
                            list->RemoveFromList(props);
                            prioIdx = static_cast<uint32>(JobsPriority::_Count);    // break out of outer loop
                            break;
                        }
    
    
                        props = props->next;
                    }
                }
            }

            if (fiber) {
                _SetFiberToCurrentThread(fiber);
            }
            else if (waitingListIsLive) {
                gJobs.semaphores[typeIndex].Post();

                if (spinCount & 1023) 
                    OS::PauseCPU();
                else
                    Thread::SwitchContext();
            }
        }

        Mem::Free(_GetThreadData());
        return 0;
    }

    static JobsInstance* _DispatchInternal(bool isAutoDelete, JobsType type, JobsCallback callback, void* userData, 
                                        uint32 groupSize, JobsPriority prio, JobsStackSize stackSize)
    {
        ASSERT(groupSize);

        uint32 numFibers = groupSize;
        ASSERT(numFibers);

        JobsInstance* instance = gJobs.instancePool->New();

        memset(instance, 0x0, sizeof(*instance));

        Atomic::ExchangeExplicit(&instance->counter, numFibers, AtomicMemoryOrder::Release);
        instance->type = type;
        instance->isAutoDelete = isAutoDelete;

        #if 0
        JobsFiber* parent = nullptr;
        if (gIsInFiber && !isAutoDelete) {
            JobsThreadData* tdata = _GetThreadData();
            ASSERT(tdata->curFiber);
            parent = tdata->curFiber;
        }
        #endif

        {
            JobsLockScope lock(gJobs.waitingListLock);
            for (uint32 i = 0; i < numFibers; i++) {
                JobsFiberProperties* props = gJobs.fiberPropsPool->New();
                *props = JobsFiberProperties {
                    .callback = callback,
                    .userData = userData,
                    .instance = instance,
                    .prio = prio,
                    .stackSize = stackSize,
                    .index = i
                };
    
                gJobs.waitingLists[uint32(type)].AddToList(props);
            }
        }

        gJobs.semaphores[uint32(type)].Post(numFibers);
        return instance;
    }
} // Jobs

void Jobs::WaitForCompletionAndDelete(JobsHandle instance)
{
    ASSERT(!instance->isAutoDelete);

    uint32 spinCount = !PLATFORM_MOBILE;    // On mobile hardware, we start from yielding then proceed with Pause
    while (Atomic::LoadExplicit(&instance->counter, AtomicMemoryOrder::Acquire)) {
        JobsThreadData* tdata = _GetThreadData();
        if (tdata) {
            ASSERT_MSG(tdata->curFiber, "Task threads should always have a fiber assigned when 'Wait' is called");

            JobsFiber* curFiber = tdata->curFiber;
            curFiber->ownerTid = tdata->threadId;    // save ownerTid as a hint so we can pick this up again on the same thread context
            tdata->waitInstance = instance;

            {
                mco_coro* co = curFiber->co;
                ASSERT(co);
                ASSERT(co->state != MCO_SUSPENDED);
                ASSERT(co->state != MCO_DEAD);
                co->state = MCO_SUSPENDED;

                #ifdef _MCO_USE_ASAN
                void* bottom_old = nullptr;
                size_t size_old = 0;
                __sanitizer_finish_switch_fiber(co->asan_prev_stack, (const void**)&bottom_old, &size_old);
                #endif

                #ifdef _MCO_USE_TSAN
                void* tsan_prev_fiber = co->tsan_prev_fiber;
                co->tsan_prev_fiber = nullptr;
                __tsan_switch_to_fiber(tsan_prev_fiber, 0);
                #endif

                Debug::FiberScopeProtector_Check();

                _mco_context* context = (_mco_context*)co->context;
                _mco_switch(&context->ctx, &context->back_ctx);
            }
        }
        else {
            if (spinCount++ & 1023)
                OS::PauseCPU();   // Main thread just loops 
            else
                Thread::SwitchContext();
        }
    }

    gJobs.instancePool->Delete(instance);
}

void Jobs::YieldCurrent()
{
    JobsThreadData* tdata = _GetThreadData();
    ASSERT_MSG(tdata, "YieldCurrent() can only be called within the task threads");
    ASSERT_MSG(tdata->curFiber, "Task threads should always have a fiber assigned when 'Yield' is called");

    JobsFiber* curFiber = tdata->curFiber;

    {
        mco_coro* co = curFiber->co;
        ASSERT(co);
        ASSERT(co->state != MCO_SUSPENDED);
        ASSERT(co->state != MCO_DEAD);
        co->state = MCO_SUSPENDED;

        #ifdef _MCO_USE_ASAN
        void* bottom_old = nullptr;
        size_t size_old = 0;
        __sanitizer_finish_switch_fiber(co->asan_prev_stack, (const void**)&bottom_old, &size_old);
        #endif

        #ifdef _MCO_USE_TSAN
        void* tsan_prev_fiber = co->tsan_prev_fiber;
        co->tsan_prev_fiber = nullptr;
        __tsan_switch_to_fiber(tsan_prev_fiber, 0);
        #endif

        Debug::FiberScopeProtector_Check();

        _mco_context* context = (_mco_context*)co->context;
        _mco_switch(&context->ctx, &context->back_ctx);
    }
}

bool Jobs::IsRunning(JobsHandle handle)
{
    ASSERT(handle);
    ASSERT(!handle->isAutoDelete);    // Can't query for AutoDelete jobs
    return Atomic::LoadExplicit(&handle->counter, AtomicMemoryOrder::Acquire);
}

void Jobs::Delete(JobsHandle handle)
{
    ASSERT_MSG(Atomic::LoadExplicit(&handle->counter, AtomicMemoryOrder::Acquire) == 0, "Job must be completed before deletion");
    
    gJobs.instancePool->Delete(handle);
}

JobsHandle Jobs::Dispatch(JobsType type, JobsCallback callback, void* userData, uint32 groupSize, JobsPriority prio, JobsStackSize stackSize)
{
    return _DispatchInternal(false, type, callback, userData, groupSize, prio, stackSize);
}

void Jobs::DispatchAndForget(JobsType type, JobsCallback callback, void* userData, uint32 groupSize, JobsPriority prio, JobsStackSize stackSize)
{
    _DispatchInternal(true, type, callback, userData, groupSize, prio, stackSize);
}

uint32 Jobs::GetWorkerThreadsCount(JobsType type)
{
    ASSERT(type != JobsType::_Count);
    return gJobs.numThreads[uint32(type)];
}


void Jobs::Initialize(const JobsInitParams& initParams)
{
    ASSERT(initParams.alloc);

    gJobs.initParams = initParams;
    
    SysInfo info {};
    OS::GetSysInfo(&info);
    uint32 numCores = info.coreCount;
    ASSERT(numCores);

    gJobs.numThreads[uint32(JobsType::ShortTask)] = initParams.numShortTaskThreads == 0 ? Max<uint32>(1, numCores - 1) : initParams.numShortTaskThreads;
    gJobs.numThreads[uint32(JobsType::LongTask)] =  initParams.numLongTaskThreads == 0 ? Max<uint32>(1, numCores - 1) : initParams.numLongTaskThreads;

    if constexpr (PLATFORM_ANDROID)
        Debug::StacktraceSaveStopPoint((void*)_EntryFn);   // workaround for stacktrace crash bug. see `debugStacktraceSaveStopPoint`

    #ifdef JOBS_USE_ANDERSON_LOCK
    uint32 numTotalThreads = gJobs.numThreads[0] + gJobs.numThreads[1] + 1;
    gJobs.waitingListLock.Initialize(numTotalThreads, Mem::AllocAlignedTyped<JobsAndersonLockThread>(numTotalThreads, alignof(JobsAndersonLockThread), initParams.alloc));
    #endif

    gJobs.semaphores[uint32(JobsType::ShortTask)].Initialize();
    gJobs.semaphores[uint32(JobsType::LongTask)].Initialize();
    
    for (uint32 i = 0; i < uint32(JobsStackSize::_Count); i++)
        gJobs.fiberAllocators[i].Initialize(JOBS_STACK_SIZES[i]);

    gJobs.instancePool = JobsAtomicPool<JobsInstance, _limits::JOBS_MAX_INSTANCES>::Create(initParams.alloc);
    gJobs.fiberPropsPool = JobsAtomicPool<JobsFiberProperties, _limits::JOBS_MAX_PENDING>::Create(initParams.alloc);

    gJobs.threads[uint32(JobsType::LongTask)] = NEW_ARRAY(initParams.alloc, Thread, gJobs.numThreads[uint32(JobsType::LongTask)]);

    for (uint32 i = 0; i < gJobs.numThreads[uint32(JobsType::LongTask)]; i++) {
        char name[32];
        Str::PrintFmt(name, sizeof(name), "LongTask_%u", i+1);
        gJobs.threads[uint32(JobsType::LongTask)][i].Start(ThreadDesc {
            .entryFn = _WorkerThread, 
            .userData = IntToPtr<uint64>((static_cast<uint64>(i+1) << 32) | uint32(JobsType::LongTask)), 
            .name = name, 
            .stackSize = 64*SIZE_KB,
            .flags = ThreadCreateFlags::None
        });
        ASSERT(gJobs.threads[uint32(JobsType::LongTask)][i].IsRunning());
        gJobs.threads[uint32(JobsType::LongTask)][i].SetPriority(ThreadPriority::Normal);
    }
    
    gJobs.threads[uint32(JobsType::ShortTask)] = NEW_ARRAY(initParams.alloc, Thread, gJobs.numThreads[uint32(JobsType::ShortTask)]);

    for (uint32 i = 0; i < gJobs.numThreads[uint32(JobsType::ShortTask)]; i++) {
        char name[32];
        Str::PrintFmt(name, sizeof(name), "ShortTask_%u", i+1);
        gJobs.threads[uint32(JobsType::ShortTask)][i].Start(ThreadDesc {
            .entryFn = _WorkerThread, 
            .userData = IntToPtr<uint64>((static_cast<uint64>(i+1) << 32) | uint32(JobsType::ShortTask)), 
            .name = name, 
            .stackSize = 64*SIZE_KB,
            .flags = ThreadCreateFlags::None
        });
        ASSERT(gJobs.threads[uint32(JobsType::ShortTask)][i].IsRunning());
        gJobs.threads[uint32(JobsType::ShortTask)][i].SetPriority(ThreadPriority::High);
    }

    Debug::FiberScopeProtector_RegisterCallback([](void*)->bool { return gIsInFiber; });

    #if TRACY_ENABLE
    auto TracyEnterZone = [](TracyCZoneCtx* ctx, const ___tracy_source_location_data* sourceLoc)
    {
        ASSERT(ctx);
        if (gIsInFiber) {
            JobsThreadData* tdata = _GetThreadData();
            ASSERT(tdata->curFiber);

            ASSERT_MSG(!tdata->curFiber->tracyZonesStack.IsFull(), "Profile sampling stack is too deep. Either remove samples or increase the kJobsMaxTracyStackDepth");
            tdata->curFiber->tracyZonesStack.Push(JobsTracyZone {*ctx, sourceLoc});
        }
    };

    auto TracyExitZone = [](TracyCZoneCtx* ctx)->bool
    {
        if (gIsInFiber) {
            JobsThreadData* tdata = _GetThreadData();
            ASSERT(tdata->curFiber);
            JobsFiber* fiber = tdata->curFiber;
            if (fiber->tracyZonesStack.Count()) {
                if (fiber->tracyZonesStack.Last().ctx.id != ctx->id) {
                    TracyCZoneEnd(fiber->tracyZonesStack.Last().ctx);
                    fiber->tracyZonesStack.PopLast();
                    return true;
                }
                else {
                    fiber->tracyZonesStack.PopLast();
                }            
            }        
        }
        return false;
    };

    Tracy::SetZoneCallbacks(TracyEnterZone, TracyExitZone);
    #endif  // TRACY_ENABLE

    LOG_INFO("(init) Job dispatcher: %u short task threads, %u long task threads", 
            gJobs.numThreads[uint32(JobsType::ShortTask)],
            gJobs.numThreads[uint32(JobsType::LongTask)]);
}

void Jobs::Release()
{
    Atomic::StoreExplicit(&gJobs.quit, 1, AtomicMemoryOrder::Release);

    gJobs.semaphores[uint32(JobsType::ShortTask)].Post(gJobs.numThreads[uint32(JobsType::ShortTask)]);
    gJobs.semaphores[uint32(JobsType::LongTask)].Post(gJobs.numThreads[uint32(JobsType::LongTask)]);

    if (gJobs.threads[uint32(JobsType::ShortTask)]) {
        for (uint32 i = 0; i < gJobs.numThreads[uint32(JobsType::ShortTask)]; i++)
            gJobs.threads[uint32(JobsType::ShortTask)][i].Stop();
    }

    if (gJobs.threads[uint32(JobsType::LongTask)]) {
        for (uint32 i = 0; i < gJobs.numThreads[uint32(JobsType::LongTask)]; i++)
            gJobs.threads[uint32(JobsType::LongTask)][i].Stop();
    }

    if (gJobs.instancePool)
        JobsAtomicPool<JobsInstance, _limits::JOBS_MAX_INSTANCES>::Destroy(gJobs.instancePool, gJobs.initParams.alloc);
    if (gJobs.fiberPropsPool)
        JobsAtomicPool<JobsFiberProperties, _limits::JOBS_MAX_PENDING>::Destroy(gJobs.fiberPropsPool, gJobs.initParams.alloc);

    gJobs.semaphores[uint32(JobsType::ShortTask)].Release();
    gJobs.semaphores[uint32(JobsType::LongTask)].Release();

    for (uint32 i = 0; i < uint32(JobsStackSize::_Count); i++)
        gJobs.fiberAllocators[i].Release();
}

JobsSignal::JobsSignal()
{
    JobsSignalInternal* self = reinterpret_cast<JobsSignalInternal*>(data);
    self->signaled = 0;
    self->value = 0;
}

void JobsSignal::Raise()
{
    JobsSignalInternal* self = reinterpret_cast<JobsSignalInternal*>(data);
    Atomic::ExchangeExplicit(&self->signaled, 1, AtomicMemoryOrder::Release);
}

void JobsSignal::Wait()
{
    WaitOnCondition([](int value, int reference)->bool { return value == reference; }, 0);
}

void JobsSignal::WaitOnCondition(bool(*condFn)(int value, int reference), int reference)
{
    JobsSignalInternal* self = reinterpret_cast<JobsSignalInternal*>(data);

    uint32 spinCount = !PLATFORM_MOBILE;
    while (condFn(Atomic::LoadExplicit(&self->value, AtomicMemoryOrder::Acquire), reference)) {
        JobsThreadData* tdata = Jobs::_GetThreadData();
        if (tdata) {
            JobsFiber* curFiber = tdata->curFiber;
            ASSERT_MSG(curFiber, "'Wait' should only be called during running job tasks");

            curFiber->ownerTid = tdata->threadId;    // save ownerTid as a hint so we can pick this up again on the same thread context
            curFiber->signal = self;

            {
                mco_coro* co = curFiber->co;
                ASSERT(co);
                ASSERT(co->state != MCO_SUSPENDED);
                ASSERT(co->state != MCO_DEAD);
                co->state = MCO_SUSPENDED;

                #ifdef _MCO_USE_ASAN
                void* bottom_old = nullptr;
                size_t size_old = 0;
                __sanitizer_finish_switch_fiber(co->asan_prev_stack, (const void**)&bottom_old, &size_old);
                #endif

                #ifdef _MCO_USE_TSAN
                void* tsan_prev_fiber = co->tsan_prev_fiber;
                co->tsan_prev_fiber = nullptr;
                __tsan_switch_to_fiber(tsan_prev_fiber, 0);
                #endif

                Debug::FiberScopeProtector_Check();

                _mco_context* context = (_mco_context*)co->context;
                _mco_switch(&context->ctx, &context->back_ctx);
            }

            curFiber->signal = nullptr;
        }
        else {
            if (spinCount++ & 1023)
                OS::PauseCPU();   // Main thread just loops 
            else
                Thread::SwitchContext();
        }
    }
}

void JobsSignal::Set(int value)
{
    JobsSignalInternal* self = reinterpret_cast<JobsSignalInternal*>(data);
    Atomic::ExchangeExplicit(&self->value, uint32(value), AtomicMemoryOrder::Release);
}

void JobsSignal::Reset()
{
    JobsSignalInternal* self = reinterpret_cast<JobsSignalInternal*>(data);
    Atomic::ExchangeExplicit(&self->value, uint32(0), AtomicMemoryOrder::Release);
}

void JobsSignal::Decrement()
{
    JobsSignalInternal* self = reinterpret_cast<JobsSignalInternal*>(data);
    Atomic::FetchAddExplicit(&self->value, 1, AtomicMemoryOrder::Release);
}

void JobsSignal::Increment()
{
    JobsSignalInternal* self = reinterpret_cast<JobsSignalInternal*>(data);
    Atomic::FetchSubExplicit(&self->value, 1, AtomicMemoryOrder::Release);
}


template <typename _T, uint32 _MaxCount> 
JobsAtomicPool<_T, _MaxCount>* JobsAtomicPool<_T, _MaxCount>::Create(MemAllocator* alloc)
{
    MemSingleShotMalloc<JobsAtomicPool<_T, _MaxCount>> mallocator;
    using PoolT = JobsAtomicPool<_T, _MaxCount>;
    mallocator.template AddMemberArray<_T*>(offsetof(PoolT, mPtrs), _MaxCount);
    mallocator.template AddMemberArray<_T>(offsetof(PoolT, mProps), _MaxCount, false, alignof(_T));
    JobsAtomicPool<_T, _MaxCount>* p = mallocator.Calloc(alloc);

    p->mIndex = _MaxCount;
    for (uint32 i = 0; i < _MaxCount; i++)
        p->mPtrs[_MaxCount - i - 1] = &p->mProps[i];

    return p;
}

template <typename _T, uint32 _MaxCount> 
void JobsAtomicPool<_T, _MaxCount>::Destroy(JobsAtomicPool<_T, _MaxCount>* p, MemAllocator* alloc)
{
    MemSingleShotMalloc<JobsAtomicPool<_T, _MaxCount>>::Free(p, alloc);
}

template <typename _T, uint32 _MaxCount> 
inline _T* JobsAtomicPool<_T, _MaxCount>::New()
{
    uint32 idx = Atomic::FetchSub(&mIndex, 1);
    ASSERT_MSG(idx != 0, "Pool is full. Increase _MaxCount (%u). See _limits namespace", _MaxCount);
    return mPtrs[idx - 1];
}

template <typename _T, uint32 _MaxCount>
inline void JobsAtomicPool<_T, _MaxCount>::Delete(_T* p)
{
    uint32 idx = Atomic::FetchAdd(&mIndex, 1);
    ASSERT_MSG(idx != _MaxCount, "Pool delete fault");
    mPtrs[idx] = p;
}


inline void JobsWaitingList::AddToList(JobsFiberProperties* props)
{
    uint32 index = static_cast<uint32>(props->prio);
    JobsFiberProperties** pfirst = &mWaitingList[index];
    JobsFiberProperties** plast = &mWaitingListLast[index];

    if (*plast) {
        (*plast)->next = props;
        props->prev = *plast;
    }
    *plast = props;
    if (*pfirst == NULL)
        *pfirst = props;
}

inline void JobsWaitingList::RemoveFromList(JobsFiberProperties* props)
{
    uint32 index = static_cast<uint32>(props->prio);
    JobsFiberProperties** pfirst = &mWaitingList[index];
    JobsFiberProperties** plast = &mWaitingListLast[index];

    if (props->prev)
        props->prev->next = props->next;
    if (props->next)
        props->next->prev = props->prev;
    if (*pfirst == props)
        *pfirst = props->next;
    if (*plast == props)
        *plast = props->prev;
    props->prev = props->next = nullptr;
}



#if JOBS_USE_ANDERSON_LOCK
inline void JobsAndersonLock::Initialize(uint32 numThreads, JobsAndersonLockThread* threads)
{
    ASSERT(threads);
    ASSERT(numThreads);

    memset(threads, 0x0, sizeof(JobsAndersonLockThread)*numThreads);
    mSlots = threads;

    for (uint32 i = 1; i < numThreads; i++) {
        mSlots[i].locked = 1;
        mSlots[i].position = i;
    }

    mCount = numThreads;
    mMask = numThreads - 1;

    if (numThreads & (numThreads - 1)) 
        mWrap = (UINT32_MAX % numThreads) + 1;
    else
        mWrap = 0;

    c89atomic_compiler_fence();
}

inline uint32 JobsAndersonLock::Enter()
{
    uint32 position, next;

    if (mWrap) {
        position = c89atomic_load_explicit_32(&next, c89atomic_memory_order_acquire);

        do {
            if (position == UINT32_MAX)
                next = mWrap;
            else 
                next = position + 1;
        } while (c89atomic_compare_exchange_strong_32(&mNext, &position, next) == false);

        position %= mCount;
    } else {
        position = c89atomic_fetch_add_32(&next, 1);
        position &= mMask;
    }

    c89atomic_thread_fence(c89atomic_memory_order_acq_rel);

    while (c89atomic_load_explicit_32(&mSlots[position].locked, c89atomic_memory_order_acquire))
        OS::PauseCPU();

    c89atomic_store_explicit_32(&mSlots[position].locked, 1, c89atomic_memory_order_release);

    return position;
}

inline void JobsAndersonLock::Exit(uint32 slot)
{
    uint32 position;

    c89atomic_thread_fence(c89atomic_memory_order_acq_rel);

    if (mWrap == 0)
        position = (mSlots[slot].position + 1) & mMask;
    else
        position = (mSlots[slot].position + 1) % mCount;

    c89atomic_store_explicit_32(&mSlots[position].locked, 0, c89atomic_memory_order_release);
}
#endif // JOBS_USE_ANDERSON_LOCK


                                                                                    
void JobsFiberMemAllocator::Initialize(size_t allocationSize)
{
    size_t pageSize = OS::GetPageSize();
    ASSERT(allocationSize % pageSize == 0);
    allocationSize = AlignValue(allocationSize + pageSize, pageSize);   // Leave some room for mco_coro

    mBufferAlignment = uint32(pageSize);
    mAllocationSize = allocationSize;
    mNumItemsInPool = (gJobs.numThreads[uint32(JobsType::ShortTask)] + gJobs.numThreads[uint32(JobsType::LongTask)]) * 2;
    mPools = nullptr;
}

void JobsFiberMemAllocator::Release()
{
    MemAllocator* alloc = gJobs.initParams.alloc;
    Pool* pool = mPools;
    while (pool) {
        Pool* curPool = pool;
        pool = pool->next;

        Mem::FreeAligned(curPool->buffer, mBufferAlignment, alloc);
        Mem::Free(curPool->ptrs, alloc);
        Mem::Free(curPool, alloc);
    }
}

void* JobsFiberMemAllocator::Allocate()
{
    SpinLockMutexScope mtx(mLock);
    
    Pool* pool = mPools;
    while (pool && pool->index == 0 && pool->next)
        pool = pool->next;

    if (!pool || pool->index == 0) {
        pool = CreatePool();
        if (mPools) {
            Pool* lastPool = mPools;
            while (lastPool->next)
                lastPool = lastPool->next;
            lastPool->next = pool;
        }
        else {
            mPools = pool;
        }
    }

    ASSERT(pool && pool->index);
    return pool->ptrs[--pool->index];
}

void JobsFiberMemAllocator::Free(void* ptr)
{
    SpinLockMutexScope mtx(mLock);

    uint64 uptr = PtrToInt<uint64>(ptr);
    Pool* pool = mPools;
    
    while (pool) {
        if (uptr >= PtrToInt<uint64>(pool->buffer) && uptr < PtrToInt<uint64>(pool->buffer + mAllocationSize*mNumItemsInPool)) {
            ASSERT_MSG(pool->index < mNumItemsInPool, "Invalid free on this pool");
            pool->ptrs[pool->index++] = (uint8*)ptr;
            return;
        }

        pool = pool->next;
    }

    ASSERT_MSG(0, "Pointer doesn't belong to the allocator");
}

JobsFiberMemAllocator::Pool* JobsFiberMemAllocator::CreatePool()
{
    MemAllocator* alloc = gJobs.initParams.alloc;
    Pool* pool = Mem::AllocTyped<Pool>(1, alloc);
    pool->ptrs = Mem::AllocTyped<uint8*>(mNumItemsInPool, alloc);
    pool->buffer = (uint8*)Mem::AllocAligned(mAllocationSize*size_t(mNumItemsInPool), mBufferAlignment, alloc);
    pool->index = mNumItemsInPool;
    pool->next = nullptr;
    for (uint32 i = 0; i < mNumItemsInPool; i++)
        pool->ptrs[mNumItemsInPool - i - 1] = pool->buffer + size_t(i)*mAllocationSize;
    return pool;
}

bool Jobs::IsRunningOnCurrentThread()
{
    JobsThreadData* data = _GetThreadData();
    return data && data->curFiber;
}

#define CJ5_IMPLEMENT
#define CJ5_ASSERT(e) ASSERT(e)
#define CJ5_SKIP_ASAN NO_ASAN
//----------------------------------------------------------------------------------------------------------------------
// External/cj5/cj5.h


#include <stdbool.h>    // bool
#include <stdint.h>     // uint32_t, int64_t, etc.

#ifndef CJ5_TOKEN_HELPERS
#    define CJ5_TOKEN_HELPERS 1
#endif

#ifndef CJ5_API
#    ifdef __cplusplus
#        define CJ5_API extern "C"
#    else
#        define CJ5_API
#    endif
#endif

#ifndef CJ5_SKIP_ASAN
#    define CJ5_SKIP_ASAN
#endif

typedef enum cj5_token_type {
    CJ5_TOKEN_OBJECT = 0,
    CJ5_TOKEN_ARRAY,
    CJ5_TOKEN_NUMBER,
    CJ5_TOKEN_STRING,
    CJ5_TOKEN_BOOL,
    CJ5_TOKEN_NULL
} cj5_token_type;

typedef enum cj5_token_number_type {
    CJ5_TOKEN_NUMBER_UNKNOWN = 0,
    CJ5_TOKEN_NUMBER_FLOAT,
    CJ5_TOKEN_NUMBER_INT,
    CJ5_TOKEN_NUMBER_HEX
} cj5_token_number_type;

typedef enum cj5_error_code {
    CJ5_ERROR_NONE = 0,
    CJ5_ERROR_INVALID,       // invalid character/syntax
    CJ5_ERROR_INCOMPLETE,    // incomplete json string
    CJ5_ERROR_OVERFLOW       // token buffer overflow, need more tokens (see cj5_result.num_tokens)
} cj5_error_code;

typedef struct cj5_token {
    cj5_token_type type;
    union {
        cj5_token_number_type num_type;
        uint32_t key_hash;
    };
    int key_start;
    int key_end;
    int start;
    int end;
    int size;
    int parent_id;      // = -1 if there is no parent
} cj5_token;

typedef struct cj5_factory {
    cj5_token* (*create_token)(void* user);
    cj5_token* (*get_all)(void* user);
    void* user_data;
} cj5_factory;

typedef struct cj5_result {
    cj5_error_code error;
    int error_line;
    int error_col;
    int num_tokens;
    const cj5_token* tokens;
    const char* json5;
} cj5_result;

CJ5_API cj5_result cj5_parse(const char* json5, int len, cj5_token* tokens, int max_tokens);
CJ5_API cj5_result cj5_parse_with_factory(const char* json5, int len, cj5_factory factory);

#if CJ5_TOKEN_HELPERS
CJ5_API int cj5_seek(cj5_result* r, int parent_id, const char* key);
CJ5_API int cj5_seek_hash(cj5_result* r, int parent_id, const uint32_t key_hash);
CJ5_API int cj5_seek_recursive(cj5_result* r, int parent_id, const char* key);
CJ5_API const char* cj5_get_string(cj5_result* r, int id, char* str, int max_str);
CJ5_API double cj5_get_double(cj5_result* r, int id);
CJ5_API float cj5_get_float(cj5_result* r, int id);
CJ5_API int cj5_get_int(cj5_result* r, int id);
CJ5_API uint32_t cj5_get_uint(cj5_result* r, int id);
CJ5_API uint64_t cj5_get_uint64(cj5_result* r, int id);
CJ5_API int64_t cj5_get_int64(cj5_result* r, int id);
CJ5_API bool cj5_get_bool(cj5_result* r, int id);
CJ5_API double cj5_seekget_double(cj5_result* r, int parent_id, const char* key, double def_val);
CJ5_API float cj5_seekget_float(cj5_result* r, int parent_id, const char* key, float def_val);
CJ5_API int cj5_seekget_array_int16(cj5_result* r, int parent_id, const char* key, int16_t* values, int max_values);
CJ5_API int cj5_seekget_array_uint16(cj5_result* r, int parent_id, const char* key, uint16_t* values, int max_values);
CJ5_API int cj5_seekget_int(cj5_result* r, int parent_id, const char* key, int def_val);
CJ5_API uint32_t cj5_seekget_uint(cj5_result* r, int parent_id, const char* key, uint32_t def_val);
CJ5_API uint64_t cj5_seekget_uint64(cj5_result* r, int parent_id, const char* key, uint64_t def_val);
CJ5_API int64_t cj5_seekget_int64(cj5_result* r, int parent_id, const char* key, int64_t def_val);
CJ5_API bool cj5_seekget_bool(cj5_result* r, int parent_id, const char* key, bool def_val);
CJ5_API const char* cj5_seekget_string(cj5_result* r, int parent_id, const char* key, char* str, int max_str, const char* def_val);

CJ5_API int cj5_seekget_array_double(cj5_result* r, int parent_id, const char* key, double* values, int max_values);
CJ5_API int cj5_seekget_array_float(cj5_result* r, int parent_id, const char* key, float* values, int max_values);
CJ5_API int cj5_seekget_array_int(cj5_result* r, int parent_id, const char* key, int* values, int max_values);
CJ5_API int cj5_seekget_array_uint(cj5_result* r, int parent_id, const char* key, uint32_t* values, int max_values);
CJ5_API int cj5_seekget_array_uint64(cj5_result* r, int parent_id, const char* key, uint64_t* values, int max_values);
CJ5_API int cj5_seekget_array_int64(cj5_result* r, int parent_id, const char* key, int64_t* values, int max_values);
CJ5_API int cj5_seekget_array_bool(cj5_result* r, int parent_id, const char* key, bool* values, int max_values);
CJ5_API int cj5_seekget_array_string(cj5_result* r, int parent_id, const char* key, char** strs, int max_str, int max_values);
CJ5_API int cj5_get_array_elem(cj5_result* r, int id, int index);
CJ5_API int cj5_get_array_elem_incremental(cj5_result* r, int id, int index, int prev_elem);
#endif

#if defined(CJ5_IMPLEMENT)

#    ifndef CJ5_ASSERT
#        include <assert.h>
#        define CJ5_ASSERT(_e) assert(_e)
#    endif

#    ifndef CJ5_MEMCPY
#        include <string.h>    // memcpy
#        define CJ5_MEMCPY(_dst, _src, _n) memcpy((_dst), (_src), (_n))
#    endif

#    ifndef CJ5_MEMSET
#        include <string.h>
#        define CJ5_MEMSET(_dst, _val, _size) memset((_dst), (_val), (_size))
#    endif

#    define CJ5__ARCH_64BIT 0
#    define CJ5__ARCH_32BIT 0
#    if defined(__x86_64__) || defined(_M_X64) || defined(__aarch64__) || defined(__64BIT__) || \
        defined(__mips64) || defined(__powerpc64__) || defined(__ppc64__) || defined(__LP64__)
#        undef CJ5__ARCH_64BIT
#        define CJ5__ARCH_64BIT 64
#    else
#        undef CJ5__ARCH_32BIT
#        define CJ5__ARCH_32BIT 32
#    endif    //

#    if defined(_MSC_VER)
#        define CJ5__RESTRICT __restrict
#    else
#        define CJ5__RESTRICT __restrict__
#    endif

#    define CJ5__UNUSED(_a) (void)(_a)

#    define CJ5__FOURCC(_a, _b, _c, _d) \
        (((uint32_t)(_a) | ((uint32_t)(_b) << 8) | ((uint32_t)(_c) << 16) | ((uint32_t)(_d) << 24)))

static const uint32_t CJ5__NULL_FOURCC = CJ5__FOURCC('n', 'u', 'l', 'l');
static const uint32_t CJ5__TRUE_FOURCC = CJ5__FOURCC('t', 'r', 'u', 'e');
static const uint32_t CJ5__FALSE_FOURCC = CJ5__FOURCC('f', 'a', 'l', 's');

static const uint32_t CJ5__FNV1_32_INIT = 0x811c9dc5;
static const uint32_t CJ5__FNV1_32_PRIME = 0x01000193;

typedef struct cj5__parser {
    int pos;
    int next_id;
    int super_id;
    int line;
    cj5_token* tokens;
    cj5_factory token_factory;
} cj5__parser;

static inline uint32_t cj5__hash_fnv32(const char* start, const char* end)
{
    const char* bp = start;
    const char* be = end;    // start + len

    uint32_t hval = CJ5__FNV1_32_INIT;
    while (bp < be) {
        hval ^= (uint32_t)*bp++;
        hval *= CJ5__FNV1_32_PRIME;
    }

    return hval;
}

static inline bool cj5__isspace(char ch)
{
    return (uint32_t)(ch - 1) < 32 && ((0x80001F00 >> (uint32_t)(ch - 1)) & 1) == 1;
}

static inline bool cj5__isrange(char ch, char from, char to)
{
    return (uint8_t)(ch - from) <= (uint8_t)(to - from);
}

static inline bool cj5__isupperchar(char ch)
{
    return cj5__isrange(ch, 'A', 'Z');
}

static inline bool cj5__islowerchar(char ch)
{
    return cj5__isrange(ch, 'a', 'z');
}

static inline bool cj5__isnum(char ch)
{
    return cj5__isrange(ch, '0', '9');
}

static inline char* cj5__strcpy(char* CJ5__RESTRICT dst, int dst_sz, const char* CJ5__RESTRICT src, int num)
{
    const int _max = dst_sz - 1;
    const int _num = (num < _max ? num : _max);
    if (_num > 0) {
        CJ5_MEMCPY(dst, src, _num);
    }
    dst[_num] = '\0';
    return dst;
}

CJ5_SKIP_ASAN static int cj5__strlen(const char* str)
{
    const char* char_ptr;
    const uintptr_t* longword_ptr;
    uintptr_t longword, himagic, lomagic;

    for (char_ptr = str; ((uintptr_t)char_ptr & (sizeof(longword) - 1)) != 0; ++char_ptr) {
        if (*char_ptr == '\0')
            return (int)(intptr_t)(char_ptr - str);
    }
    longword_ptr = (uintptr_t*)char_ptr;
    himagic = 0x80808080L;
    lomagic = 0x01010101L;
#    if CJ5__ARCH_64BIT
    /* 64-bit version of the magic.  */
    /* Do the shift in two steps to avoid a warning if long has 32 bits.  */
    himagic = ((himagic << 16) << 16) | himagic;
    lomagic = ((lomagic << 16) << 16) | lomagic;
#    endif

    for (;;) {
        longword = *longword_ptr++;

        if (((longword - lomagic) & ~longword & himagic) != 0) {
            const char* cp = (const char*)(longword_ptr - 1);

            if (cp[0] == 0)
                return (int)(intptr_t)(cp - str);
            if (cp[1] == 0)
                return (int)(intptr_t)(cp - str + 1);
            if (cp[2] == 0)
                return (int)(intptr_t)(cp - str + 2);
            if (cp[3] == 0)
                return (int)(intptr_t)(cp - str + 3);
#    if CJ5__ARCH_64BIT
            if (cp[4] == 0)
                return (int)(intptr_t)(cp - str + 4);
            if (cp[5] == 0)
                return (int)(intptr_t)(cp - str + 5);
            if (cp[6] == 0)
                return (int)(intptr_t)(cp - str + 6);
            if (cp[7] == 0)
                return (int)(intptr_t)(cp - str + 7);
#    endif
        }
    }

    #ifndef _MSC_VER
    CJ5_ASSERT(0);
    return -1;
    #endif
}

static inline cj5_token* cj5__alloc_token(cj5__parser* parser)
{
    cj5_token* token = parser->token_factory.create_token(parser->token_factory.user_data);
    if (!token)
        return NULL;
    CJ5_MEMSET(token, 0x0, sizeof(cj5_token));

    ++parser->next_id;
    parser->tokens = parser->token_factory.get_all(parser->token_factory.user_data);

    token->start = -1;
    token->end = -1;
    token->parent_id = -1;
    return token;
}

static inline void cj5__set_error(cj5_result* r, cj5_error_code code, int line, int col)
{
    r->error = code;
    r->error_line = line + 1;
    r->error_col = col + 1;
}

static bool cj5__parse_primitive(cj5__parser* parser, cj5_result* r, const char* json5, int len)
{
    cj5_token* token;
    int start = parser->pos;
    int line_start = start;
    bool keyname = false;
    bool new_line = false;

    for (; parser->pos < len; parser->pos++) {
        switch (json5[parser->pos]) {
        case '\n':
            line_start = parser->pos;
            new_line = true;
            goto found;
        case ':':
            keyname = true;
            goto found;
        case '\t':
        case '\r':
        case ' ':
        case ',':
        case ']':
        case '}':
            goto found;
        default:
            break;
        }

        if (json5[parser->pos] < 32 || json5[parser->pos] >= 127) {
            cj5__set_error(r, CJ5_ERROR_INVALID, parser->line, parser->pos - line_start);
            parser->pos = start;
            return false;
        }
    }

    cj5__set_error(r, CJ5_ERROR_INCOMPLETE, parser->line, parser->pos - line_start);
    parser->pos = start;
    return false;

found:
    token = cj5__alloc_token(parser);
    if (token == NULL) {
        r->error = CJ5_ERROR_OVERFLOW;
        --parser->pos;
        return true;
    }

    cj5_token_type type;
    cj5_token_number_type num_type = CJ5_TOKEN_NUMBER_UNKNOWN;
    if (keyname) {
        for (int i = start; i < parser->pos; i++) {
            if (cj5__islowerchar(json5[i]) || cj5__isupperchar(json5[i]) || json5[i] == '_') {
                continue;
            }

            if (cj5__isnum(json5[i])) {
                if (i == start) {
                    cj5__set_error(r, CJ5_ERROR_INVALID, parser->line, parser->pos - line_start);
                    parser->pos = start;
                    return false;
                }
                continue;
            }

            cj5__set_error(r, CJ5_ERROR_INVALID, parser->line, parser->pos - line_start);
            parser->pos = start;
            return false;
        }

        type = CJ5_TOKEN_STRING;
    } else {
        uint32_t fourcc_ = 0;
        if (parser->pos - start >= 4)
            CJ5_MEMCPY(&fourcc_, &json5[start], 4);
        else
            CJ5_MEMCPY(&fourcc_, &json5[start], parser->pos - start);

        uint32_t* fourcc = &fourcc_;
 
        if (*fourcc == CJ5__NULL_FOURCC) {
            type = CJ5_TOKEN_NULL;
        } else if (*fourcc == CJ5__TRUE_FOURCC) {
            type = CJ5_TOKEN_BOOL;
        } else if (*fourcc == CJ5__FALSE_FOURCC) {
            type = CJ5_TOKEN_BOOL;
        } else {
            num_type = CJ5_TOKEN_NUMBER_INT;
            if (json5[start] == '0' && start < parser->pos + 1 && json5[start + 1] == 'x') {
                start = start + 2;
                for (int i = start; i < parser->pos; i++) {
                    if (!(cj5__isrange(json5[i], '0', '9') || cj5__isrange(json5[i], 'A', 'F') ||
                          cj5__isrange(json5[i], 'a', 'f'))) {
                        cj5__set_error(r, CJ5_ERROR_INVALID, parser->line,
                                       parser->pos - line_start);
                        parser->pos = start;
                        return false;
                    }
                }
                num_type = CJ5_TOKEN_NUMBER_HEX;
            } else {
                int start_index = start;
                if (json5[start] == '+') {
                    ++start_index;
                    ++start;
                } else if (json5[start] == '-') {
                    ++start_index;
                }

                for (int i = start_index; i < parser->pos; i++) {
                    if (json5[i] == '.') {
                        if (num_type == CJ5_TOKEN_NUMBER_FLOAT) {
                            cj5__set_error(r, CJ5_ERROR_INVALID, parser->line,
                                           parser->pos - line_start);
                            parser->pos = start;
                            return false;
                        }
                        num_type = CJ5_TOKEN_NUMBER_FLOAT;
                        continue;
                    }

                    if (!cj5__isnum(json5[i])) {
                        cj5__set_error(r, CJ5_ERROR_INVALID, parser->line,
                                       parser->pos - line_start);
                        parser->pos = start;
                        return false;
                    }
                }
            }

            type = CJ5_TOKEN_NUMBER;
        }
    }

    if (new_line) {
        ++parser->line;
    }

    token->type = type;
    if (type == CJ5_TOKEN_STRING) {
        token->key_hash = cj5__hash_fnv32(&json5[start], &json5[parser->pos]);
        token->key_start = start;
        token->key_end = parser->pos;
    } else {
        token->num_type = num_type;
    }
    token->start = start;
    token->end = parser->pos;
    token->parent_id = parser->super_id;
    --parser->pos;
    return true;
}

static bool cj5__parse_string(cj5__parser* parser, cj5_result* r, const char* json5, int len)
{
    cj5_token* token;
    int start = parser->pos;
    int line_start = start;
    char str_open = json5[start];
    ++parser->pos;

    for (; parser->pos < len; parser->pos++) {
        char c = json5[parser->pos];

        if (str_open == c) {
            token = cj5__alloc_token(parser);
            if (token == NULL) {
                r->error = CJ5_ERROR_OVERFLOW;
                return true;
            }

            token->type = CJ5_TOKEN_STRING;
            token->start = start + 1;
            token->end = parser->pos;
            token->parent_id = parser->super_id;

            return true;
        }

        if (c == '\\' && parser->pos + 1 < len) {
            ++parser->pos;
            switch (json5[parser->pos]) {
            case '\"':
            case '/':
            case '\\':
            case 'b':
            case 'f':
            case 'r':
            case 'n':
            case 't':
                break;
            case 'u':
                ++parser->pos;
                for (int i = 0; i < 4 && parser->pos < len; i++) {
                    /* If it isn't a hex character we have an error */
                    if (!((json5[parser->pos] >= 48 && json5[parser->pos] <= 57) ||   /* 0-9 */
                          (json5[parser->pos] >= 65 && json5[parser->pos] <= 70) ||   /* A-F */
                          (json5[parser->pos] >= 97 && json5[parser->pos] <= 102))) { /* a-f */
                        cj5__set_error(r, CJ5_ERROR_INVALID, parser->line,
                                       parser->pos - line_start);
                        parser->pos = start;
                        return false;
                    }
                    parser->pos++;
                }

                --parser->pos;
                break;
            case '\n':
                line_start = parser->pos;
                ++parser->line;
                break;
            default:
                cj5__set_error(r, CJ5_ERROR_INVALID, parser->line, parser->pos - line_start);
                parser->pos = start;
                return false;
            }
        }
    }

    parser->pos = start;
    return true;
}

static void cj5__skip_comment(cj5__parser* parser, const char* json5, int len)
{
    for (; parser->pos < len; parser->pos++) {
        if (json5[parser->pos] == '\n' || json5[parser->pos] == '\r') {
            return;
        }
    }
}

static void cj5__skip_multiline_comment(cj5__parser* parser, const char* json5, int len)
{
    for (; parser->pos < len; parser->pos++) {
        if (json5[parser->pos] == '*' && parser->pos < (len - 1) && json5[parser->pos+1] == '/') {
            return;
        }
    }
}

cj5_result cj5_parse_with_factory(const char* json5, int len, cj5_factory factory)
{
    CJ5_ASSERT(json5);

    cj5__parser parser;
    CJ5_MEMSET(&parser, 0x0, sizeof(parser));
    parser.super_id = -1;
    parser.token_factory = factory;

    cj5_result r;
    CJ5_MEMSET(&r, 0x0, sizeof(r));

    cj5_token* token;
    int count = parser.next_id;
    bool can_comment = false;

    for (; parser.pos < len; parser.pos++) {
        char c;
        cj5_token_type type;

        c = json5[parser.pos];
        switch (c) {
        case '{':
        case '[':
            can_comment = false;
            count++;
            token = cj5__alloc_token(&parser);
            if (token == NULL) {
                r.error = CJ5_ERROR_OVERFLOW;
                break;
            }

            if (parser.super_id != -1) {
                cj5_token* super_token = &parser.tokens[parser.super_id];
                token->parent_id = parser.super_id;
                if (++super_token->size == 1 && super_token->type == CJ5_TOKEN_STRING) {
                    super_token->key_hash =
                        cj5__hash_fnv32(&json5[super_token->start], &json5[super_token->end]);
                    super_token->key_start = super_token->start;
                    super_token->key_end = super_token->end;
                }
            }

            token->type = (c == '{' ? CJ5_TOKEN_OBJECT : CJ5_TOKEN_ARRAY);
            token->start = parser.pos;
            parser.super_id = parser.next_id - 1;
            break;

        case '}':
        case ']':
            can_comment = false;
            if (r.error == CJ5_ERROR_OVERFLOW) {
                break;
            }
            type = (c == '}' ? CJ5_TOKEN_OBJECT : CJ5_TOKEN_ARRAY);

            if (parser.next_id < 1) {
                cj5__set_error(&r, CJ5_ERROR_INVALID, parser.line, parser.pos - parser.line);
                return r;
            }

            token = &parser.tokens[parser.next_id - 1];
            for (;;) {
                if (token->start != -1 && token->end == -1) {
                    if (token->type != type) {
                        cj5__set_error(&r, CJ5_ERROR_INVALID, parser.line,
                                       parser.pos - parser.line);
                        return r;
                    }
                    token->end = parser.pos + 1;
                    parser.super_id = token->parent_id;
                    break;
                }

                if (token->parent_id == -1) {
                    if (token->type != type || parser.super_id == -1) {
                        cj5__set_error(&r, CJ5_ERROR_INVALID, parser.line,
                                       parser.pos - parser.line);
                        return r;
                    }
                    break;
                }

                token = &parser.tokens[token->parent_id];
            }
            break;

        case '\"':
        case '\'':
            can_comment = false;
            cj5__parse_string(&parser, &r, json5, len);
            if (r.error && r.error != CJ5_ERROR_OVERFLOW) {
                return r;
            }
            count++;
            if (parser.super_id != -1 && r.error != CJ5_ERROR_OVERFLOW) {
                if (++parser.tokens[parser.super_id].size == 1 &&
                    parser.tokens[parser.super_id].type == CJ5_TOKEN_STRING) {
                    parser.tokens[parser.super_id].key_hash = cj5__hash_fnv32(
                        &json5[parser.tokens[parser.super_id].start], &json5[parser.tokens[parser.super_id].end]);
                    parser.tokens[parser.super_id].key_start = parser.tokens[parser.super_id].start;
                    parser.tokens[parser.super_id].key_end = parser.tokens[parser.super_id].end;
                }
            }
            break;

        case '\r':
            can_comment = true;
            break;
        case '\n':
            ++parser.line;
            can_comment = true;
            break;
        case '\t':
        case ' ':
            break;

        case ':':
            can_comment = false;
            parser.super_id = parser.next_id - 1;
            break;

        case ',':
            can_comment = false;
            if (parser.super_id != -1 && r.error != CJ5_ERROR_OVERFLOW &&
                parser.tokens[parser.super_id].type != CJ5_TOKEN_ARRAY &&
                parser.tokens[parser.super_id].type != CJ5_TOKEN_OBJECT) {
                parser.super_id = parser.tokens[parser.super_id].parent_id;
            }
            break;
        case '/':
            if (can_comment && parser.pos < len - 1) {
                if (json5[parser.pos + 1] == '/') {
                    cj5__skip_comment(&parser, json5, len);
                } else if (json5[parser.pos + 1] == '*') {
                    cj5__skip_multiline_comment(&parser, json5, len);
                }
            } 
            break;

        default:
            cj5__parse_primitive(&parser, &r, json5, len);
            if (r.error && r.error != CJ5_ERROR_OVERFLOW) {
                return r;
            }
            can_comment = false;
            count++;
            if (parser.super_id != -1 && r.error != CJ5_ERROR_OVERFLOW) {
                if (++parser.tokens[parser.super_id].size == 1 &&
                    parser.tokens[parser.super_id].type == CJ5_TOKEN_STRING) {
                    parser.tokens[parser.super_id].key_hash = cj5__hash_fnv32(
                        &json5[parser.tokens[parser.super_id].start], &json5[parser.tokens[parser.super_id].end]);
                    parser.tokens[parser.super_id].key_start = parser.tokens[parser.super_id].start;
                    parser.tokens[parser.super_id].key_end = parser.tokens[parser.super_id].end;
                }
            }
            break;
        }
    }

    if (r.error != CJ5_ERROR_OVERFLOW) {
        for (int i = parser.next_id - 1; i >= 0; i--) {
            if (parser.tokens[i].start != -1 && parser.tokens[i].end == -1) {
                cj5__set_error(&r, CJ5_ERROR_INCOMPLETE, parser.line, parser.pos - parser.line);
                return r;
            }
        }
    }

    r.num_tokens = count;
    r.tokens = parser.tokens;
    r.json5 = json5;
    return r;
}

typedef struct cj5_factory_default {
    cj5_token* tokens;
    int max_tokens;
    int index;
} cj5_factory_default;

static cj5_token* cj5_factory_default_create_fn(void* user)
{
    cj5_factory_default* factory = (cj5_factory_default*)user;

    if (factory->index < factory->max_tokens)
        return &factory->tokens[factory->index++];
    else
        return NULL;
}

static cj5_token* cj5_factory_default_getall_fn(void* user)
{
    cj5_factory_default* factory = (cj5_factory_default*)user;
    return factory->tokens;
}

cj5_result cj5_parse(const char* json5, int len, cj5_token* tokens, int max_tokens)
{
    CJ5_ASSERT(json5);
    CJ5_ASSERT(tokens);
    CJ5_ASSERT(max_tokens > 0);

    cj5_factory factory;
    cj5_factory_default factory_data;
    factory_data.tokens = tokens;
    factory_data.max_tokens = max_tokens;
    factory_data.index = 0;

    factory.create_token = cj5_factory_default_create_fn;
    factory.get_all = cj5_factory_default_getall_fn;
    factory.user_data = &factory_data;

    return cj5_parse_with_factory(json5, len, factory);
}

#    if CJ5_TOKEN_HELPERS
#        include <stdlib.h>

static int cj5__seek_recursive(cj5_result* r, int parent_id, uint32_t key_hash)
{
    const cj5_token* parent_tok = &r->tokens[parent_id];

    for (int i = parent_id + 1, count = 0; i < r->num_tokens && count < parent_tok->size; i++) {
        const cj5_token* tok = &r->tokens[i];

        if (tok->size != 1 || tok->type != CJ5_TOKEN_STRING) {
            continue;
        }

        if (parent_id == tok->parent_id) {
            CJ5_ASSERT((i + 1) < r->num_tokens);
            if (key_hash == tok->key_hash) {
                return i + 1;    // return next "value" token (array/objects and primitive values)
            } else if (r->tokens[i + 1].size) {
                int found_id = cj5__seek_recursive(r, i + 1, key_hash);
                if (found_id != -1) {
                    return found_id;
                }
            }
            count++;
        }
    }

    return -1;
}

static bool cj5__tofloat(const char* str, double* ofloat)
{
    while (*str && cj5__isspace(*str)) {
        str++;
    }
    int sign = 1;

    const char* pC = str;
    if (*pC == '-') {
        sign = -1;
        pC++;
    }

    int64_t tmp = 0;
    while (*pC >= '0' && *pC <= '9') {
        tmp *= 10;
        tmp += *pC - '0';
        pC++;
    }

    if (*pC == 0) {
        *ofloat = (double)(sign >= 0 ? tmp : -tmp);
        return true;
    }

    if (*pC == '.') {
        pC++;

        int64_t divisor = sign;
        while (*pC >= '0' && *pC <= '9') {
            divisor *= 10;
            tmp *= 10;
            tmp += *pC - '0';
            pC++;
        }

        while (*pC && cj5__isspace(*pC)) {
            pC++;
        }

        if (*pC == 0) {
            *ofloat = (double)tmp / (double)divisor;
            return true;
        }
    }

    *ofloat = strtod(str, NULL);
    return true;
}

int cj5_seek_recursive(cj5_result* r, int parent_id, const char* key)
{
    CJ5_ASSERT(parent_id >= 0 && parent_id < r->num_tokens);

    uint32_t key_hash = cj5__hash_fnv32(key, key + cj5__strlen(key));
    return cj5__seek_recursive(r, parent_id, key_hash);
}

int cj5_seek_hash(cj5_result* r, int parent_id, const uint32_t key_hash)
{
    CJ5_ASSERT(parent_id >= 0 && parent_id < r->num_tokens);
    const cj5_token* parent_tok = &r->tokens[parent_id];

    for (int i = parent_id + 1, count = 0; i < r->num_tokens && count < parent_tok->size; i++) {
        const cj5_token* tok = &r->tokens[i];

        if (tok->size != 1 || tok->type != CJ5_TOKEN_STRING) {
            continue;
        }

        if (parent_id == tok->parent_id) {
            if (key_hash == tok->key_hash) {
                CJ5_ASSERT((i + 1) < r->num_tokens);
                return i + 1;    // return next "value" token (array/objects and primitive values)
            }
            count++;
        }
    }

    return -1;
}

int cj5_seek(cj5_result* r, int parent_id, const char* key)
{
    CJ5_ASSERT(parent_id >= 0 && parent_id < r->num_tokens);

    uint32_t key_hash = cj5__hash_fnv32(key, key + cj5__strlen(key));

    return cj5_seek_hash(r, parent_id, key_hash);
}

const char* cj5_get_string(cj5_result* r, int id, char* str, int max_str)
{
    CJ5_ASSERT(id >= 0 && id < r->num_tokens);
    const cj5_token* tok = &r->tokens[id];
    CJ5_ASSERT(tok->type == CJ5_TOKEN_STRING);
    return cj5__strcpy(str, max_str, &r->json5[tok->start], tok->end - tok->start);
}

double cj5_get_double(cj5_result* r, int id)
{
    CJ5_ASSERT(id >= 0 && id < r->num_tokens);
    const cj5_token* tok = &r->tokens[id];
    CJ5_ASSERT(tok->type == CJ5_TOKEN_NUMBER);
    char snum[32];
    double num;
    cj5__strcpy(snum, sizeof(snum), &r->json5[tok->start], tok->end - tok->start);
    bool valid = cj5__tofloat(snum, &num);
    CJ5__UNUSED(valid);
    CJ5_ASSERT(valid);
    return num;
}

float cj5_get_float(cj5_result* r, int id)
{
    return (float)cj5_get_double(r, id);
}

int cj5_get_int(cj5_result* r, int id)
{
    CJ5_ASSERT(id >= 0 && id < r->num_tokens);
    const cj5_token* tok = &r->tokens[id];
    CJ5_ASSERT(tok->type == CJ5_TOKEN_NUMBER);
    char snum[32];
    cj5__strcpy(snum, sizeof(snum), &r->json5[tok->start], tok->end - tok->start);
    return (int)strtol(snum, NULL, tok->num_type != CJ5_TOKEN_NUMBER_HEX ? 10 : 16);
}

uint32_t cj5_get_uint(cj5_result* r, int id)
{
    CJ5_ASSERT(id >= 0 && id < r->num_tokens);
    const cj5_token* tok = &r->tokens[id];
    CJ5_ASSERT(tok->type == CJ5_TOKEN_NUMBER);
    char snum[32];
    cj5__strcpy(snum, sizeof(snum), &r->json5[tok->start], tok->end - tok->start);
    return (uint32_t)strtoul(snum, NULL, tok->num_type != CJ5_TOKEN_NUMBER_HEX ? 10 : 16);
}

uint64_t cj5_get_uint64(cj5_result* r, int id)
{
    CJ5_ASSERT(id >= 0 && id < r->num_tokens);
    const cj5_token* tok = &r->tokens[id];
    CJ5_ASSERT(tok->type == CJ5_TOKEN_NUMBER);
    char snum[64];
    cj5__strcpy(snum, sizeof(snum), &r->json5[tok->start], tok->end - tok->start);
    return strtoull(snum, NULL, tok->num_type != CJ5_TOKEN_NUMBER_HEX ? 10 : 16);
}

int64_t cj5_get_int64(cj5_result* r, int id)
{
    CJ5_ASSERT(id >= 0 && id < r->num_tokens);
    const cj5_token* tok = &r->tokens[id];
    CJ5_ASSERT(tok->type == CJ5_TOKEN_NUMBER);
    char snum[64];
    cj5__strcpy(snum, sizeof(snum), &r->json5[tok->start], tok->end - tok->start);
    return strtoll(snum, NULL, tok->num_type != CJ5_TOKEN_NUMBER_HEX ? 10 : 16);
}

bool cj5_get_bool(cj5_result* r, int id)
{
    CJ5_ASSERT(id >= 0 && id < r->num_tokens);
    const cj5_token* tok = &r->tokens[id];
    CJ5_ASSERT(tok->type == CJ5_TOKEN_BOOL);
    CJ5_ASSERT((tok->end - tok->start) >= 4);

    uint32_t fourcc = *((const uint32_t*)&r->json5[tok->start]);
    if (fourcc == CJ5__TRUE_FOURCC) {
        return true;
    } else if (fourcc == CJ5__FALSE_FOURCC) {
        return false;
    } else {
        CJ5_ASSERT(0);
        return false;
    }
}

double cj5_seekget_double(cj5_result* r, int parent_id, const char* key, double def_val)
{
    int id = cj5_seek(r, parent_id, key);
    return id > -1 ? cj5_get_double(r, id) : def_val;
}

float cj5_seekget_float(cj5_result* r, int parent_id, const char* key, float def_val)
{
    int id = cj5_seek(r, parent_id, key);
    return id > -1 ? cj5_get_float(r, id) : def_val;
}

int cj5_seekget_int(cj5_result* r, int parent_id, const char* key, int def_val)
{
    int id = cj5_seek(r, parent_id, key);
    return id > -1 ? cj5_get_int(r, id) : def_val;
}

uint32_t cj5_seekget_uint(cj5_result* r, int parent_id, const char* key, uint32_t def_val)
{
    int id = cj5_seek(r, parent_id, key);
    return id > -1 ? cj5_get_uint(r, id) : def_val;
}

uint64_t cj5_seekget_uint64(cj5_result* r, int parent_id, const char* key, uint64_t def_val)
{
    int id = cj5_seek(r, parent_id, key);
    return id > -1 ? cj5_get_uint64(r, id) : def_val;
}

int64_t cj5_seekget_int64(cj5_result* r, int parent_id, const char* key, int64_t def_val)
{
    int id = cj5_seek(r, parent_id, key);
    return id > -1 ? cj5_get_int64(r, id) : def_val;
}

bool cj5_seekget_bool(cj5_result* r, int parent_id, const char* key, bool def_val)
{
    int id = cj5_seek(r, parent_id, key);
    return id > -1 ? cj5_get_bool(r, id) : def_val;
}

const char* cj5_seekget_string(cj5_result* r, int parent_id, const char* key, char* str,
                               int max_str, const char* def_val)
{
    int id = cj5_seek(r, parent_id, key);
    return id > -1 ? cj5_get_string(r, id, str, max_str) : def_val;
}

int cj5_seekget_array_double(cj5_result* r, int parent_id, const char* key, double* values,
                             int max_values)
{
    int id = key != NULL ? cj5_seek(r, parent_id, key) : parent_id;
    if (id != -1) {
        const cj5_token* tok = &r->tokens[id];
        CJ5__UNUSED(tok);
        CJ5_ASSERT(tok->type == CJ5_TOKEN_ARRAY);
        int count = 0;
        for (int i = id + 1, ic = r->num_tokens; i < ic && r->tokens[i].parent_id == id && count < max_values; i++) {
            values[count++] = cj5_get_double(r, i);
        }
        return count;
    } else {
        return 0;
    }
}

int cj5_seekget_array_float(cj5_result* r, int parent_id, const char* key, float* values,
                            int max_values)
{
    int id = key != NULL ? cj5_seek(r, parent_id, key) : parent_id;
    if (id != -1) {
        const cj5_token* tok = &r->tokens[id];
        CJ5__UNUSED(tok);
        CJ5_ASSERT(tok->type == CJ5_TOKEN_ARRAY);
        int count = 0;
        for (int i = id + 1, ic = r->num_tokens; i < ic && r->tokens[i].parent_id == id && count < max_values; i++) {
            values[count++] = cj5_get_float(r, i);
        }
        return count;
    } else {
        return 0;
    }
}

int cj5_seekget_array_int16(cj5_result* r, int parent_id, const char* key, int16_t* values,
                            int max_values)
{
    int id = key != NULL ? cj5_seek(r, parent_id, key) : parent_id;
    if (id != -1) {
        const cj5_token* tok = &r->tokens[id];
        CJ5__UNUSED(tok);
        CJ5_ASSERT(tok->type == CJ5_TOKEN_ARRAY);
        int count = 0;
        for (int i = id + 1, ic = r->num_tokens; i < ic && r->tokens[i].parent_id == id && count < max_values; i++) {
            values[count++] = (int16_t)cj5_get_int(r, i);
        }
        return count;
    } else {
        return 0;
    }
}

int cj5_seekget_array_uint16(cj5_result* r, int parent_id, const char* key, uint16_t* values,
                             int max_values)
{
    int id = key != NULL ? cj5_seek(r, parent_id, key) : parent_id;
    if (id != -1) {
        const cj5_token* tok = &r->tokens[id];
        CJ5__UNUSED(tok);
        CJ5_ASSERT(tok->type == CJ5_TOKEN_ARRAY);
        int count = 0;
        for (int i = id + 1, ic = r->num_tokens; i < ic && r->tokens[i].parent_id == id && count < max_values; i++) {
            values[count++] = (uint16_t)cj5_get_int(r, i);
        }
        return count;
    } else {
        return 0;
    }
}


int cj5_seekget_array_int(cj5_result* r, int parent_id, const char* key, int* values,
                          int max_values)
{
    int id = key != NULL ? cj5_seek(r, parent_id, key) : parent_id;
    if (id != -1) {
        const cj5_token* tok = &r->tokens[id];
        CJ5__UNUSED(tok);
        CJ5_ASSERT(tok->type == CJ5_TOKEN_ARRAY);
        int count = 0;
        for (int i = id + 1, ic = r->num_tokens; i < ic && r->tokens[i].parent_id == id && count < max_values; i++) {
            values[count++] = cj5_get_int(r, i);
        }
        return count;
    } else {
        return 0;
    }
}

int cj5_seekget_array_uint(cj5_result* r, int parent_id, const char* key, uint32_t* values,
                           int max_values)
{
    int id = key != NULL ? cj5_seek(r, parent_id, key) : parent_id;
    if (id != -1) {
        const cj5_token* tok = &r->tokens[id];
        CJ5__UNUSED(tok);
        CJ5_ASSERT(tok->type == CJ5_TOKEN_ARRAY);
        int count = 0;
        for (int i = id + 1, ic = r->num_tokens; i < ic && r->tokens[i].parent_id == id && count < max_values; i++) {
            values[count++] = cj5_get_uint(r, i);
        }
        return count;
    } else {
        return 0;
    }
}

int cj5_seekget_array_uint64(cj5_result* r, int parent_id, const char* key, uint64_t* values,
                             int max_values)
{
    int id = key != NULL ? cj5_seek(r, parent_id, key) : parent_id;
    if (id != -1) {
        const cj5_token* tok = &r->tokens[id];
        CJ5__UNUSED(tok);
        CJ5_ASSERT(tok->type == CJ5_TOKEN_ARRAY);
        int count = 0;
        for (int i = id + 1, ic = r->num_tokens; i < ic && r->tokens[i].parent_id == id && count < max_values; i++) {
            values[count++] = cj5_get_uint64(r, i);
        }
        return count;
    } else {
        return 0;
    }
}

int cj5_seekget_array_int64(cj5_result* r, int parent_id, const char* key, int64_t* values,
                            int max_values)
{
    int id = key != NULL ? cj5_seek(r, parent_id, key) : parent_id;
    if (id != -1) {
        const cj5_token* tok = &r->tokens[id];
        CJ5__UNUSED(tok);
        CJ5_ASSERT(tok->type == CJ5_TOKEN_ARRAY);
        int count = 0;
        for (int i = id + 1, ic = r->num_tokens; i < ic && r->tokens[i].parent_id == id && count < max_values; i++) {
            values[count++] = cj5_get_int64(r, i);
        }
        return count;
    } else {
        return 0;
    }
}

int cj5_seekget_array_bool(cj5_result* r, int parent_id, const char* key, bool* values,
                           int max_values)
{
    int id = key != NULL ? cj5_seek(r, parent_id, key) : parent_id;
    if (id != -1) {
        const cj5_token* tok = &r->tokens[id];
        CJ5__UNUSED(tok);
        CJ5_ASSERT(tok->type == CJ5_TOKEN_ARRAY);
        int count = 0;
        for (int i = id + 1, ic = r->num_tokens; i < ic && r->tokens[i].parent_id == id && count < max_values; i++) {
            values[count++] = cj5_get_bool(r, i);
        }
        return count;
    } else {
        return 0;
    }
}

int cj5_seekget_array_string(cj5_result* r, int parent_id, const char* key, char** strs,
                             int max_str, int max_values)
{
    int id = key != NULL ? cj5_seek(r, parent_id, key) : parent_id;
    if (id != -1) {
        const cj5_token* tok = &r->tokens[id];
        CJ5__UNUSED(tok);
        CJ5_ASSERT(tok->type == CJ5_TOKEN_ARRAY);
        int count = 0;
        for (int i = id + 1, ic = r->num_tokens; i < ic && r->tokens[i].parent_id == id && count < max_values; i++) {
            cj5_get_string(r, i, strs[count++], max_str);
        }
        return count;
    } else {
        return 0;
    }
}

int cj5_get_array_elem(cj5_result* r, int id, int index)
{
    const cj5_token* tok = &r->tokens[id];
    CJ5_ASSERT(tok->type == CJ5_TOKEN_ARRAY);
    CJ5_ASSERT(index < tok->size);
    for (int i = id + 1, count = 0, ic = r->num_tokens; i < ic && count < tok->size; i++) {
        if (r->tokens[i].parent_id == id) {
            if (count == index) {
                return i;
            }
            count++;
        }
    }
    return -1;
}

int cj5_get_array_elem_incremental(cj5_result* r, int id, int index, int prev_elem)
{
    const cj5_token* tok = &r->tokens[id];
    CJ5_ASSERT(tok->type == CJ5_TOKEN_ARRAY);
    CJ5_ASSERT(index < tok->size);
    int start = prev_elem <= 0 ? (id + 1) : (prev_elem + 1);
    for (int i = start, count = index, ic = r->num_tokens; i < ic && count < tok->size; i++) {
        if (r->tokens[i].parent_id == id) {
            if (count == index) {
                return i;
            }
            count++;
        }
    }
    return -1;
}

#    endif    // CJ5_TOKEN_HELPERS
#endif        // CJ5_IMPLEMENT

#undef CJ5_IMPLEMENT


struct JsonContext
{
    cj5_result r;       // This should always come first, because the wrapper API casts JsonContext to cj5_result*
    uint32 numTokens;
    MemAllocator* alloc;
    cj5_token* tokens;
};

JsonContext* Json::Parse(const char* json5, uint32 json5Len, JsonErrorLocation* outErrLoc, MemAllocator* alloc)
{
    ASSERT(json5);
    ASSERT(json5Len < INT32_MAX);
    ASSERT(alloc);

    bool mainAllocIsTemp = alloc->GetType() == MemAllocatorType::Temp;
    MemTempAllocator::ID tempMemId = mainAllocIsTemp ? ((MemTempAllocator*)alloc)->GetId() : MemTempAllocator::PushId();
    MemTempAllocator tmpAlloc(tempMemId);
    Array<cj5_token> tokens(&tmpAlloc);
    tokens.Reserve(64);

    auto CreateToken = [](void* user)->cj5_token* { return ((Array<cj5_token>*)user)->Push(); };
    auto GetAll = [](void* user)->cj5_token* { return ((Array<cj5_token>*)user)->Ptr(); };
    cj5_factory factory {
        .create_token = CreateToken,
        .get_all = GetAll,
        .user_data = &tokens
    };

    json5Len = json5Len == 0 ? json5Len : Str::Len(json5);
    cj5_result r = cj5_parse_with_factory(json5, (int)json5Len, factory);

    if (r.error == CJ5_ERROR_NONE) {
        ASSERT(tokens.Count());

        MemSingleShotMalloc<JsonContext> mallocator;
        mallocator.AddMemberArray<cj5_token>(offsetof(JsonContext, tokens), tokens.Count());
        JsonContext* ctx = mallocator.Malloc(alloc);

        ctx->numTokens = tokens.Count();
        memcpy(ctx->tokens, r.tokens, tokens.Count());
        ctx->r.tokens = ctx->tokens;

        ctx->r = r;
        ctx->alloc = alloc;

        if (!mainAllocIsTemp)
            MemTempAllocator::PopId(tempMemId);
        return ctx;
    }
    else {
        if (outErrLoc) {
            *outErrLoc = JsonErrorLocation {
                .line = (uint32)r.error_line,
                .col = (uint32)r.error_col
            };
        }
        if (!mainAllocIsTemp)
            MemTempAllocator::PopId(tempMemId);
        return nullptr;
    }
}

void Json::Destroy(JsonContext* ctx)
{
    if (ctx && ctx->alloc) 
        MemSingleShotMalloc<JsonContext>::Free(ctx, ctx->alloc);
}

uint32 JsonNode::GetChildCount() const
{
    cj5_result* r = reinterpret_cast<cj5_result*>(mCtx);

    const cj5_token* tok = &r->tokens[mTokenId];
    if (tok->parent_id != -1) {
        const cj5_token* parent = &r->tokens[tok->parent_id];
        if (parent->type == CJ5_TOKEN_STRING) {     // this would be the key
            return r->tokens[parent->parent_id].type == CJ5_TOKEN_OBJECT ? r->tokens[parent->parent_id].size : 0;
        }
        else {
            return 0;
        }
    }
    else {
        return tok->type == CJ5_TOKEN_OBJECT ? tok->size : 0;
    }
}

uint32 JsonNode::GetArrayCount() const
{
    cj5_result* r = reinterpret_cast<cj5_result*>(mCtx);
    const cj5_token* tok = &r->tokens[mTokenId];
    ASSERT(tok->type == CJ5_TOKEN_ARRAY);
    return tok->size;
}

bool JsonNode::IsArray() const
{
    return mCtx->r.tokens[mTokenId].type == CJ5_TOKEN_ARRAY;
}

bool JsonNode::IsObject() const
{
    cj5_result* r = reinterpret_cast<cj5_result*>(mCtx);
    
    const cj5_token* tok = &r->tokens[mTokenId];
    if (tok->type == CJ5_TOKEN_OBJECT)
        return true;

    if (tok->parent_id != -1)
        return r->tokens[tok->parent_id].type == CJ5_TOKEN_OBJECT;

    return false;
}

const char* JsonNode::GetKey(char* outKey, uint32 keySize) const
{
    cj5_result* r = reinterpret_cast<cj5_result*>(mCtx);
    ASSERT(mTokenId > 0 && mTokenId < r->num_tokens);
    ASSERT(r->tokens[mTokenId].parent_id != -1);
    const cj5_token* tok = &r->tokens[r->tokens[mTokenId].parent_id];   // get the 'key' token (parent)
    ASSERT(tok->type == CJ5_TOKEN_STRING);
    return cj5__strcpy(outKey, keySize, &r->json5[tok->start], tok->end - tok->start);
}

const char* JsonNode::GetValue(char* outValue, uint32 valueSize) const
{
    cj5_result* r = reinterpret_cast<cj5_result*>(mCtx);
    CJ5_ASSERT(mTokenId >= 0 && mTokenId < r->num_tokens);
    const cj5_token* tok = &r->tokens[mTokenId];
    return cj5__strcpy(outValue, valueSize, &r->json5[tok->start], tok->end - tok->start);

}

JsonNode JsonNode::GetChildItem(uint32 _index) const
{
    cj5_result* r = reinterpret_cast<cj5_result*>(mCtx);
    const cj5_token* tok = &r->tokens[mTokenId];
    int index = (int)_index;

    ASSERT(tok->type == CJ5_TOKEN_OBJECT);
    ASSERT(index < tok->size);
    
    for (int i = mTokenId + 1, count = 0, ic = r->num_tokens; i < ic && count < tok->size; i+=2) {
        ASSERT(r->tokens[i].type == CJ5_TOKEN_STRING);
        if (r->tokens[i].parent_id == mTokenId) {
            if (count == index)
                return JsonNode(mCtx, i + 1, index);       // get next 'value' token
            count++;
        }
    }
    return JsonNode(mCtx, -1);
}

JsonNode JsonNode::GetNextChildItem(const JsonNode& curChildItem) const
{
    cj5_result* r = reinterpret_cast<cj5_result*>(mCtx);
    const cj5_token* tok = &r->tokens[mTokenId];

    ASSERT(curChildItem.mItemIndex < tok->size);

    int nextIndex = curChildItem.mItemIndex + 1;
    if (nextIndex == tok->size) 
        return JsonNode(mCtx, -1);

    for (int i = curChildItem.mTokenId + 1, ic = r->num_tokens; i < ic; i+=2) {
        if (r->tokens[i].parent_id == mTokenId)
            return JsonNode(mCtx, i + 1, nextIndex);
    }

    return JsonNode(mCtx, -1);
}

JsonNode JsonNode::GetArrayItem(uint32 _index) const
{
    cj5_result* r = reinterpret_cast<cj5_result*>(mCtx);
    const cj5_token* tok = &r->tokens[mTokenId];
    int index = (int)_index;
    ASSERT(tok->type == CJ5_TOKEN_ARRAY);
    ASSERT(index < tok->size);
    for (int i = mTokenId + 1, count = 0, ic = r->num_tokens; i < ic && count < tok->size; i++) {
        if (r->tokens[i].parent_id == mTokenId) {
            if (count == index)
                return JsonNode(mCtx, i, _index);
            count++;
        }
    }
    return JsonNode(mCtx, -1);
}

JsonNode JsonNode::GetNextArrayItem(const JsonNode& curItem) const
{
    cj5_result* r = reinterpret_cast<cj5_result*>(mCtx);
    const cj5_token* tok = &r->tokens[mTokenId];
    int index = curItem.mItemIndex + 1;
    ASSERT(tok->type == CJ5_TOKEN_ARRAY);

    if (index == tok->size) 
        return JsonNode(mCtx, -1);

    int startId = curItem.mTokenId <= 0 ? (mTokenId + 1) : (curItem.mTokenId + 1);
    for (int i = startId, ic = r->num_tokens; i < ic; i++) {
        if (r->tokens[i].parent_id == mTokenId)
            return JsonNode(mCtx, i, index);
    }
    return JsonNode(mCtx, -1);
}


#include <stdarg.h> // va_list
#include <stdio.h>  // puts


#if PLATFORM_MOBILE || PLATFORM_OSX
    #define TERM_COLOR_RESET     ""
    #define TERM_COLOR_RED       ""
    #define TERM_COLOR_YELLOW    ""
    #define TERM_COLOR_GREEN     ""
    #define TERM_COLOR_CYAN      ""
    #define TERM_COLOR_WHITE     ""
#else
    #define TERM_COLOR_RESET     "\033[0m"
    #define TERM_COLOR_RED       "\033[31m"
    #define TERM_COLOR_YELLOW    "\033[33m"
    #define TERM_COLOR_GREEN     "\033[32m"
    #define TERM_COLOR_CYAN      "\033[36m"
    #define TERM_COLOR_WHITE     "\033[97m"
#endif

#ifndef DEFAULT_LOG_LEVEL
    #if CONFIG_DEV_MODE
        #define DEFAULT_LOG_LEVEL LogLevel::Debug
    #else
        #define DEFAULT_LOG_LEVEL LogLevel::Info
    #endif
#endif

static constexpr uint32 LOG_MAX_MESSAGE_CHARS = 2048;

struct LogContext
{
    StaticArray<Pair<LogCallback, void*>, 8> callbacks;
    LogLevel logLevel = DEFAULT_LOG_LEVEL;
    bool breakOnErrors;
    bool treatWarningsAsErrors;
};

static LogContext gLog;

static const char* LOG_ENTRY_TYPES[static_cast<uint32>(LogLevel::_Count)] = { 
    "", 
    "[ERR] ",
    "[WRN] ",
    "", 
    "", 
    "[DBG] "
};

namespace Log
{
    void SetSettings(LogLevel logLevel, bool breakOnErrors, bool treatWarningsAsErrors)
    {
        ASSERT(logLevel != LogLevel::Default);

        gLog.logLevel = logLevel;
        gLog.breakOnErrors = breakOnErrors;
        gLog.treatWarningsAsErrors = treatWarningsAsErrors;
    }

    static void _PrintToTerminal(const LogEntry& entry)
    {
        uint32 newSize = entry.textLen + 128;

        MemTempAllocator tmp;
        char* text = tmp.MallocTyped<char>(newSize);

        if (text) {
            const char* openFmt = "";
            const char* closeFmt = "";

            switch (entry.type) {
            case LogLevel::Info:    openFmt = TERM_COLOR_WHITE; closeFmt = TERM_COLOR_WHITE; break;
            case LogLevel::Debug:	openFmt = TERM_COLOR_CYAN; closeFmt = TERM_COLOR_RESET; break;
            case LogLevel::Verbose:	openFmt = TERM_COLOR_RESET; closeFmt = TERM_COLOR_RESET; break;
            case LogLevel::Warning:	openFmt = TERM_COLOR_YELLOW; closeFmt = TERM_COLOR_RESET; break;
            case LogLevel::Error:	openFmt = TERM_COLOR_RED; closeFmt = TERM_COLOR_RESET; break;
            default:			    break;
            }

            Str::PrintFmt(text, newSize, "%s%s%s%s", 
                openFmt, 
                LOG_ENTRY_TYPES[static_cast<uint32>(entry.type)], 
                entry.text, closeFmt);
        
            puts(text);
        }
        else {
            ASSERT_ALWAYS(0, "Not enough stack memory: %u bytes", newSize);
        }
    }

    #if PLATFORM_ANDROID
    static void _PrintToAndroidLog(const LogEntry& entry)
    {
        OSAndroidLogType androidLogType;
        switch (entry.type) {
        case LogLevel::Info:	androidLogType = OSAndroidLogType::Info;        break;
        case LogLevel::Debug:	androidLogType = OSAndroidLogType::Debug;       break;
        case LogLevel::Verbose:	androidLogType = OSAndroidLogType::Verbose;     break;
        case LogLevel::Warning:	androidLogType = OSAndroidLogType::Warn;        break;
        case LogLevel::Error:	androidLogType = OSAndroidLogType::Error;       break;
        default:			    androidLogType = OSAndroidLogType::Unknown;
        }
        
        OS::AndroidPrintToLog(androidLogType, CONFIG_APP_NAME, entry.text);
    }
    #endif // PLATFORM_ANDROID

    static void _PrintToDebugger(const LogEntry& entry)
    {
        if constexpr(!PLATFORM_WINDOWS)
            return;

        uint32 newSize = entry.textLen + 128;
        MemTempAllocator tmp;
        char* text = tmp.MallocTyped<char>(newSize);

        if (text) {
            char source[PATH_CHARS_MAX];
            if (entry.sourceFile)
                Str::PrintFmt(source, sizeof(source), "%s(%d): ", entry.sourceFile, entry.line);
            else 
                source[0] = '\0';
            Str::PrintFmt(text, newSize, "%s%s%s", source, LOG_ENTRY_TYPES[static_cast<uint32>(entry.type)], entry.text);
            Debug::PrintLine(text);
        }
        else {
            ASSERT_ALWAYS(0, "Not enough stack memory: %u bytes", newSize);
        }
    }

    #ifdef TRACY_ENABLE
    static void _PrintToTracy(const LogEntry& entry)
    {
        uint32 color;
        switch (entry.type) {
        case LogLevel::Info:	color = 0xFFFFFF; break;
        case LogLevel::Debug:	color = 0xC8C8C8; break;
        case LogLevel::Verbose:	color = 0x808080; break;
        case LogLevel::Warning:	color = 0xFFFF00; break;
        case LogLevel::Error:	color = 0xFF0000; break;
        default:			    color = 0xFFFFFF; break;
        }

        TracyCMessageC(entry.text, entry.textLen, color);
    }
    #endif

    static void _DispatchLogEntry(const LogEntry& entry)
    {
        _PrintToTerminal(entry); 
        _PrintToDebugger(entry);
        #ifdef TRACY_ENABLE
            _PrintToTracy(entry);
        #endif
        #if PLATFORM_ANDROID
            _PrintToAndroidLog(entry);
        #endif

        for (Pair<LogCallback, void*> c : gLog.callbacks)
            c.first(entry, c.second);

        if (entry.type == LogLevel::Error && gLog.breakOnErrors) {
            ASSERT_MSG(0, "Breaking on error");
        }
    }

    void _private::PrintInfo(uint32 channels, const char* sourceFile, uint32 line, const char* fmt, ...)
    {
        if (gLog.logLevel < LogLevel::Info)
            return;

        MemTempAllocator tmp;
        uint32 fmtLen = Str::Len(fmt) + LOG_MAX_MESSAGE_CHARS;
        char* text = tmp.MallocTyped<char>(fmtLen);

        va_list args;
        va_start(args, fmt);
        Str::PrintFmtArgs(text, fmtLen, fmt, args);
        va_end(args);

        _DispatchLogEntry({
            .type = LogLevel::Info,
            .channels = channels,
            .textLen = Str::Len(text),
            .sourceFileLen = sourceFile ? Str::Len(sourceFile) : 0,
            .line = line,
            .text = text,
            .sourceFile = sourceFile
        });
    }

    void _private::PrintDebug(uint32 channels, const char* sourceFile, uint32 line, const char* fmt, ...)
    {
        #if !CONFIG_FINAL_BUILD
            if (gLog.logLevel < LogLevel::Debug)
                return;
        
            MemTempAllocator tmp;
            uint32 fmtLen = Str::Len(fmt) + LOG_MAX_MESSAGE_CHARS;
            char* text = tmp.MallocTyped<char>(fmtLen);

            va_list args;
            va_start(args, fmt);
            Str::PrintFmtArgs(text, fmtLen, fmt, args);
            va_end(args);

            _DispatchLogEntry({
                .type = LogLevel::Debug,
                .channels = channels,
                .textLen = Str::Len(text),
                .sourceFileLen = sourceFile ? Str::Len(sourceFile) : 0,
                .line = line,
                .text = text,
                .sourceFile = sourceFile
            });
        #else
            UNUSED(channels);
            UNUSED(sourceFile);
            UNUSED(line);
            UNUSED(fmt);
        #endif
    }

    void _private::PrintVerbose(uint32 channels, const char* sourceFile, uint32 line, const char* fmt, ...)
    {
        if (gLog.logLevel < LogLevel::Verbose)
            return;

        MemTempAllocator tmp;
        uint32 fmtLen = Str::Len(fmt) + LOG_MAX_MESSAGE_CHARS;
        char* text = tmp.MallocTyped<char>(fmtLen);

        va_list args;
        va_start(args, fmt);
        Str::PrintFmtArgs(text, fmtLen, fmt, args);
        va_end(args);

        _DispatchLogEntry({
            .type = LogLevel::Verbose,
            .channels = channels,
            .textLen = Str::Len(text),
            .sourceFileLen = sourceFile ? Str::Len(sourceFile) : 0,
            .line = line,
            .text = text,
            .sourceFile = sourceFile
        });
    }

    void _private::PrintWarning(uint32 channels, const char* sourceFile, uint32 line, const char* fmt, ...)
    {
        if (gLog.logLevel < LogLevel::Warning)
            return;

        MemTempAllocator tmp;
        uint32 fmtLen = Str::Len(fmt) + LOG_MAX_MESSAGE_CHARS;
        char* text = tmp.MallocTyped<char>(fmtLen);

        va_list args;
        va_start(args, fmt);
        Str::PrintFmtArgs(text, fmtLen, fmt, args);
        va_end(args);

        _DispatchLogEntry({
            .type = !gLog.treatWarningsAsErrors ? LogLevel::Warning : LogLevel::Error,
            .channels = channels,
            .textLen = Str::Len(text),
            .sourceFileLen = sourceFile ? Str::Len(sourceFile) : 0,
            .line = line,
            .text = text,
            .sourceFile = sourceFile
        });
    }

    void _private::PrintError(uint32 channels, const char* sourceFile, uint32 line, const char* fmt, ...)
    {
        if (gLog.logLevel < LogLevel::Error)
            return;

        MemTempAllocator tmp;
        uint32 fmtLen = Str::Len(fmt) + LOG_MAX_MESSAGE_CHARS;
        char* text = tmp.MallocTyped<char>(fmtLen);

        va_list args;
        va_start(args, fmt);
        Str::PrintFmtArgs(text, fmtLen, fmt, args);
        va_end(args);

        _DispatchLogEntry({
            .type = LogLevel::Error,
            .channels = channels,
            .textLen = Str::Len(text),
            .sourceFileLen = sourceFile ? Str::Len(sourceFile) : 0,
            .line = line,
            .text = text,
            .sourceFile = sourceFile        
        });
    }

    void RegisterCallback(LogCallback callback, void* userData)
    {
        ASSERT(callback);
        ASSERT_MSG(gLog.callbacks.FindIf([callback](const Pair<LogCallback, void*>& p) { return p.first == callback; }) == UINT32_MAX, "Callback already added");
        gLog.callbacks.Push(Pair<LogCallback, void*>(callback, userData));
    }

    void UnregisterCallback(LogCallback callback)
    {
        uint32 index = gLog.callbacks.FindIf([callback](const Pair<LogCallback, void*>& p) { return p.first == callback; });
        if (index != UINT32_MAX)
            gLog.callbacks.RemoveAndSwap(index);
    }
} // Log


#include <math.h>

float M::CopySign(float _x, float _y)
{
    return ::copysignf(_x, _y);
}

float M::Floor(float _f)
{
    return ::floorf(_f);
}

float M::Cos(float _a)
{
    return ::cosf(_a);
}

float M::ACos(float _a)
{
    return ::acosf(_a);
}

float M::Sin(float _a)
{
    return ::sinf(_a);
}

float M::ASin(float _a)
{
    return ::asinf(_a);
}

float M::ATan2(float _y, float _x)
{
    return ::atan2f(_y, _x);
}

float M::Exp(float _a)
{
    return ::expf(_a);
}

float M::Log(float _a)
{
    return ::logf(_a);
}

#if !(defined(__SSE2__) || (COMPILER_MSVC && (ARCH_64BIT || _M_IX86_FP >= 2)))
    float M::Sqrt(float _a)
    {
        return ::sqrtf(_a);
    }

    float M::Rsqrt(float _a)
    {
        return 1.0f / ::sqrtf(_a);
    }
#endif // if not __SSE2__

    
                                        
Mat4 Mat4::ViewLookAt(Float3 eye, Float3 target, Float3 up)
{
    Float3 zaxis = Float3::Norm(Float3::Sub(target, eye));
    Float3 xaxis = Float3::Norm(Float3::Cross(zaxis, up));
    Float3 yaxis = Float3::Cross(xaxis, zaxis);
    
    return Mat4(xaxis.x,    xaxis.y,    xaxis.z,    -Float3::Dot(xaxis, eye), 
                yaxis.x,    yaxis.y,    yaxis.z,    -Float3::Dot(yaxis, eye), 
                -zaxis.x,   -zaxis.y,   -zaxis.z,    Float3::Dot(zaxis, eye),
                0,          0,          0,           1.0f);
}

Mat4 Mat4::ViewLookAtLH(Float3 eye, Float3 target, Float3 up)
{
    Float3 zaxis = Float3::Norm(Float3::Sub(target, eye));
    Float3 xaxis = Float3::Norm(Float3::Cross(up, zaxis));
    Float3 yaxis = Float3::Cross(zaxis, xaxis);
    
    return Mat4(xaxis.x, xaxis.y, xaxis.z, -Float3::Dot(xaxis, eye), 
                yaxis.x, yaxis.y, yaxis.z, -Float3::Dot(yaxis, eye), 
                zaxis.x, zaxis.y, zaxis.z, -Float3::Dot(zaxis, eye),
                0,       0,       0,        1.0f);
}

Mat4 Mat4::ViewFPS(Float3 eye, float pitch, float yaw)
{
    float cos_pitch = M::Cos(pitch);
    float sin_pitch = M::Sin(pitch);
    float cos_yaw = M::Cos(yaw);
    float sin_yaw = M::Sin(yaw);
    
    Float3 xaxis = Float3(cos_yaw, 0, -sin_yaw);
    Float3 yaxis = Float3(sin_yaw * sin_pitch, cos_pitch, cos_yaw * sin_pitch);
    Float3 zaxis = Float3(sin_yaw * cos_pitch, -sin_pitch, cos_pitch * cos_yaw);
    
    return Mat4(xaxis.x, xaxis.y, xaxis.z, -Float3::Dot(xaxis, eye), yaxis.x, yaxis.y, yaxis.z,
                -Float3::Dot(yaxis, eye), zaxis.x, zaxis.y, zaxis.z, -Float3::Dot(zaxis, eye),
                0, 0, 0, 1.0f);
}

Mat4 Mat4::ViewArcBall(Float3 move, Quat rot, Float3 target_pos)
{
    Mat4 translateInv = Mat4::Translate(-move.x, -move.y, -move.z);
    Mat4 rotateInv = Mat4::FromQuat(Quat::Conjugate(rot));
    Mat4 translateObjInv = Mat4::Translate(-target_pos.x, -target_pos.y, -target_pos.z);
    Mat4 TR = Mat4::Mul(translateObjInv, rotateInv);
    return Mat4::Mul(TR, translateInv);
}


Mat4 Mat4::Perspective(float width, float height, float zn, float zf, bool d3dNdc)
{
    const float d = zf - zn;
    const float aa = zf / d;
    const float bb = zn * aa;
    const float invY = !d3dNdc ? -1.0f : 1.0f;
    return Mat4(width,  0,              0,      0, 
                0,      height*invY,    0,      0, 
                0,      0,              -aa,    -bb, 
                0,      0,              -1.0f,  0);
}

Mat4 Mat4::PerspectiveLH(float width, float height, float zn, float zf, bool d3dNdc)
{
    const float d = zf - zn;
    const float aa = zf / d;
    const float bb = zn * aa;
    const float invY = !d3dNdc ? -1.0f : 1.0f;
    return Mat4(width,  0,              0,      0, 
                0,      height*invY,    0,      0, 
                0,      0,              aa,     -bb, 
                0,      0,              1.0f,   0);
}

Mat4 Mat4::PerspectiveOffCenter(float xmin, float ymin, float xmax, float ymax, float zn, float zf, bool d3dNdc)
{
    const float d = zf - zn;
    const float aa = zf / d;
    const float bb = zn * aa;
    const float width = xmax - xmin;
    const float height = ymax - ymin;
    const float invY = !d3dNdc ? -1.0f : 1.0f;
    return Mat4(width,  0,              xmin,   0, 
                0,      height*invY,    ymin,   0, 
                0,      0,              -aa,    -bb, 
                0,      0,              -1.0f,  0);
}

Mat4 Mat4::PerspectiveOffCenterLH(float xmin, float ymin, float xmax, float ymax, float zn, float zf, bool d3dNdc)
{
    const float d = zf - zn;
    const float aa = zf / d;
    const float bb = zn * aa;
    const float width = xmax - xmin;
    const float height = ymax - ymin;
    const float invY = !d3dNdc ? -1.0f : 1.0f;
    return Mat4(width,  0,              -xmin,  0, 
                0,      height*invY,    -ymin,  0, 
                0,      0,              aa,     -bb, 
                0,      0,              1.0f,   0);
}

Mat4 Mat4::PerspectiveFOV(float fov_y, float aspect, float zn, float zf, bool d3dNdc)
{
    const float height = 1.0f / M::Tan(fov_y * 0.5f);
    const float width = height / aspect;
    return Mat4::Perspective(width, height, zn, zf, d3dNdc);
}

Mat4 Mat4::PerspectiveFOVLH(float fovY, float aspect, float zn, float zf, bool d3dNdc)
{
    const float height = 1.0f / M::Tan(fovY * 0.5f);
    const float width = height / aspect;
    return Mat4::PerspectiveLH(width, height, zn, zf, d3dNdc);
}

Mat4 Mat4::Ortho(float width, float height, float zn, float zf, float offset, bool d3dNdc)
{
    const float d = zf - zn;
    const float cc = 1.0f / d;
    const float ff = -zn / d;
    const float ym = !d3dNdc ? -1.0f : 1.0f;
    
    return Mat4(2.0f / width,   0,                      0,      offset, 
                0,              (2.0f / height)*ym,     0,      0, 
                0,              0,                      -cc,    ff, 
                0,              0,                      0,      1.0f);
}

Mat4 Mat4::OrthoLH(float width, float height, float zn, float zf, float offset, bool d3dNdc)
{
    const float d = zf - zn;
    const float cc = 1.0f / d;
    const float ff = -zn / d;
    const float ym = !d3dNdc ? -1.0f : 1.0f;
    
    return Mat4(2.0f / width,   0,                      0,      offset, 
                0,              (2.0f / height)*ym,     0,      0, 
                0,              0,                      cc,     ff, 
                0,              0,                      0,      1.0f);
}

Mat4 Mat4::OrthoOffCenter(float xmin, float ymin, float xmax, float ymax, float zn, float zf, float offset, bool d3dNdc)
{
    const float width = xmax - xmin;
    const float height = ymax - ymin;
    const float d = zf - zn;
    const float cc = 1.0f / d;
    const float dd = (xmin + xmax) / (xmin - xmax);
    const float ee = (ymin + ymax) / (ymin - ymax);
    const float ff = -zn / d;
    const float ym = !d3dNdc ? -1.0f : 1.0f;
    
    return Mat4(2.0f / width,   0,                  0,      dd + offset, 
                0,              (2.0f / height)*ym, 0,      ee*ym, 
                0,              0,                  -cc,    ff,
                0,              0,                  0,      1.0f);
}

Mat4 Mat4::OrthoOffCenterLH(float xmin, float ymin, float xmax, float ymax, float zn, float zf, float offset, bool d3dNdc)
{
    const float width = xmax - xmin;
    const float height = ymax - ymin;
    const float d = zf - zn;
    const float cc = 1.0f / d;
    const float dd = (xmin + xmax) / (xmin - xmax);
    const float ee = (ymin + ymax) / (ymin - ymax);
    const float ff = -zn / d;
    const float ym = !d3dNdc ? -1.0f : 1.0f;
    
    return Mat4(2.0f / width,   0,                      0,      dd + offset, 
                0,              (2.0f / height)*ym,     0,      ee*ym, 
                0,              0,                      cc,     ff, 
                0,              0,                      0,      1.0f);
}

Mat4 Mat4::TransformMat(float _tx, float _ty, float _tz, 
                        float _ax, float _ay, float _az, 
                        float _sx, float _sy, float _sz)
{
    float sx, cx, sy, cy, sz, cz;
    
    sx = M::Sin(_ax);
    cx = M::Cos(_ax);
    
    sy = M::Sin(_ay);
    cy = M::Cos(_ay);
    
    sz = M::Sin(_az);
    cz = M::Cos(_az);
    
    const float sxsz = sx * sz;
    const float cycz = cy * cz;
    
    return Mat4(_sx * (cycz - sxsz * sy),       _sy * -cx * sz,       _sz * (cz * sy + cy * sxsz),    _tx,
                _sx * (cz * sx * sy + cy * sz), _sy * cx * cz,        _sz * (sy * sz - cycz * sx),    _ty,
                _sx * -cx * sy,                 _sy * sx,             _sz * cx * cy,                  _tz, 
                0.0f,                           0.0f,                 0.0f,                           1.0f);
}

Mat4 Mat4::TransformMat(Float3 translation, Quat rotation, Float3 scale)
{
    ASSERT(Quat::IsNorm(rotation));

    float x = rotation.x;
    float y = rotation.y;
    float z = rotation.z;
    float w = rotation.w;

    float xx = x*x, yy = y*y, zz = z*z;
    float xy = x*y, xz = x*z, yz = y*z;
    float wx = w*x, wy = w*y, wz = w*z;

    float r00 = 1.0f - 2.0f*(yy + zz);
    float r01 = 2.0f*(xy - wz);
    float r02 = 2.0f*(xz - wy);

    float r10 = 2.0f*(xy + wz);
    float r11 = 1.0f - 2.0f*(xx + zz);
    float r12 = 2.0f*(yz + wx);

    float r20 = 2.0f*(xz + wy);
    float r21 = 2.0f*(yz - wx);
    float r22 = 1.0f - 2.0f*(xx + yy);

    float sx = scale.x, sy = scale.y, sz = scale.z;

    return Mat4(
        Float4(r00 * sx, r10 * sx, r20 * sx, 0.0f),
        Float4(r01 * sy, r11 * sy, r21 * sy, 0.0f),
        Float4(r02 * sz, r12 * sz, r22 * sz, 0.0f),
        Float4(translation.x, translation.y, translation.z, 1.0f));
}

Mat4 Mat4::FromNormal(Float3 _normal, float _scale, Float3 _pos)
{
    Float3 tangent;
    Float3 bitangent;
    Float3::Tangent(&tangent, &bitangent, _normal);
    
    Float4 row1 = Float4(Float3::Mul(bitangent, _scale), 0.0f);
    Float4 row2 = Float4(Float3::Mul(_normal, _scale), 0.0f);
    Float4 row3 = Float4(Float3::Mul(tangent, _scale), 0.0f);
    
    return Mat4(row1.f, row2.f, row3.f, Float4(_pos, 1.0f).f);
}

Mat4 Mat4::Inverse(const Mat4& _a)
{
    float xx = _a.f[0];
    float xy = _a.f[1];
    float xz = _a.f[2];
    float xw = _a.f[3];
    float yx = _a.f[4];
    float yy = _a.f[5];
    float yz = _a.f[6];
    float yw = _a.f[7];
    float zx = _a.f[8];
    float zy = _a.f[9];
    float zz = _a.f[10];
    float zw = _a.f[11];
    float wx = _a.f[12];
    float wy = _a.f[13];
    float wz = _a.f[14];
    float ww = _a.f[15];
    
    float det = 0.0f;
    det += xx * (yy * (zz * ww - zw * wz) - yz * (zy * ww - zw * wy) + yw * (zy * wz - zz * wy));
    det -= xy * (yx * (zz * ww - zw * wz) - yz * (zx * ww - zw * wx) + yw * (zx * wz - zz * wx));
    det += xz * (yx * (zy * ww - zw * wy) - yy * (zx * ww - zw * wx) + yw * (zx * wy - zy * wx));
    det -= xw * (yx * (zy * wz - zz * wy) - yy * (zx * wz - zz * wx) + yz * (zx * wy - zy * wx));
    
    float det_rcp = 1.0f / det;
    
    return Mat4(
        Float4(
            +(yy * (zz*ww - wz*zw) - yz * (zy * ww - wy * zw) + yw * (zy * wz - wy * zz))*det_rcp,
            -(xy * (zz * ww - wz * zw) - xz * (zy * ww - wy * zw) + xw * (zy * wz - wy * zz))*det_rcp,
            +(xy * (yz * ww - wz * yw) - xz * (yy * ww - wy * yw) + xw * (yy * wz - wy * yz))*det_rcp,
            -(xy * (yz * zw - zz * yw) - xz * (yy * zw - zy * yw) + xw * (yy * zz - zy * yz))*det_rcp),
        Float4(
            -(yx * (zz * ww - wz * zw) - yz * (zx * ww - wx * zw) + yw * (zx * wz - wx * zz))*det_rcp,
            +(xx * (zz * ww - wz * zw) - xz * (zx * ww - wx * zw) + xw * (zx * wz - wx * zz))*det_rcp,
            -(xx * (yz * ww - wz * yw) - xz * (yx * ww - wx * yw) + xw * (yx * wz - wx * yz))*det_rcp,
            +(xx * (yz * zw - zz * yw) - xz * (yx * zw - zx * yw) + xw * (yx * zz - zx * yz))*det_rcp),
        Float4(
            +(yx * (zy * ww - wy * zw) - yy * (zx * ww - wx * zw) + yw * (zx * wy - wx * zy))*det_rcp,
            -(xx * (zy * ww - wy * zw) - xy * (zx * ww - wx * zw) + xw * (zx * wy - wx * zy))*det_rcp,
            +(xx * (yy * ww - wy * yw) - xy * (yx * ww - wx * yw) + xw * (yx * wy - wx * yy))*det_rcp,
            -(xx * (yy * zw - zy * yw) - xy * (yx * zw - zx * yw) + xw * (yx * zy - zx * yy))*det_rcp),
        Float4(
            -(yx * (zy * wz - wy * zz) - yy * (zx * wz - wx * zz) + yz * (zx * wy - wx * zy))*det_rcp,
            +(xx * (zy * wz - wy * zz) - xy * (zx * wz - wx * zz) + xz * (zx * wy - wx * zy))*det_rcp,
            -(xx * (yy * wz - wy * yz) - xy * (yx * wz - wx * yz) + xz * (yx * wy - wx * yy))*det_rcp,
            +(xx * (yy * zz - zy * yz) - xy * (yx * zz - zx * yz) + xz * (yx * zy - zx * yy))*det_rcp));
}

Mat4 Mat4::InverseTransformMat(const Mat4& _mat)
{
    ASSERT((_mat.m41 + _mat.m42 + _mat.m43) == 0 && _mat.m44 == 1.0f);

    float det = (_mat.m11 * (_mat.m22 * _mat.m33 - _mat.m23 * _mat.m32) +
        _mat.m12 * (_mat.m23 * _mat.m31 - _mat.m21 * _mat.m33) +
        _mat.m13 * (_mat.m21 * _mat.m32 - _mat.m22 * _mat.m31));
    float det_rcp = 1.0f / det;
    float tx = _mat.m14;
    float ty = _mat.m24;
    float tz = _mat.m34;
    
    Mat4 r = Mat4((_mat.m22 * _mat.m33 - _mat.m23 * _mat.m32) * det_rcp,
                  (_mat.m13 * _mat.m32 - _mat.m12 * _mat.m33) * det_rcp,
                  (_mat.m12 * _mat.m23 - _mat.m13 * _mat.m22) * det_rcp, 0.0f,
                  (_mat.m23 * _mat.m31 - _mat.m21 * _mat.m33) * det_rcp,
                  (_mat.m11 * _mat.m33 - _mat.m13 * _mat.m31) * det_rcp,
                  (_mat.m13 * _mat.m21 - _mat.m11 * _mat.m23) * det_rcp, 0,
                  (_mat.m21 * _mat.m32 - _mat.m22 * _mat.m31) * det_rcp,
                  (_mat.m12 * _mat.m31 - _mat.m11 * _mat.m32) * det_rcp,
                  (_mat.m11 * _mat.m22 - _mat.m12 * _mat.m21) * det_rcp, 0, 0.0f,
                  0.0f, 0.0f, 1.0f);
    
    r.f[12] = -(tx * r.m11 + ty * r.m12 + tz * r.m13);
    r.f[13] = -(tx * r.m21 + ty * r.m22 + tz * r.m23);
    r.f[14] = -(tx * r.m31 + ty * r.m32 + tz * r.m33);
    return r;
}

Quat Mat4::ToQuat(const Mat4& m)
{
    float trace, r, rinv;
    Quat q;
    
    trace = m.m11 + m.m22 + m.m33;
    if (trace >= 0.0f) {
        r = M::Sqrt(1.0f + trace);
        rinv = 0.5f / r;
        
        q.x = rinv * (m.m32 - m.m23);
        q.y = rinv * (m.m13 - m.m31);
        q.z = rinv * (m.m21 - m.m12);
        q.w = r * 0.5f;
    } 
    else if (m.m11 >= m.m22 && m.m11 >= m.m33) {
        r = M::Sqrt(1.0f - m.m22 - m.m33 + m.m11);
        rinv = 0.5f / r;
        
        q.x = r * 0.5f;
        q.y = rinv * (m.m21 + m.m12);
        q.z = rinv * (m.m31 + m.m13);
        q.w = rinv * (m.m32 - m.m23);
    } 
    else if (m.m22 >= m.m33) {
        r = M::Sqrt(1.0f - m.m11 - m.m33 + m.m22);
        rinv = 0.5f / r;
        
        q.x = rinv * (m.m21 + m.m12);
        q.y = r * 0.5f;
        q.z = rinv * (m.m32 + m.m23);
        q.w = rinv * (m.m13 - m.m31);
    } 
    else {
        r = M::Sqrt(1.0f - m.m11 - m.m22 + m.m33);
        rinv = 0.5f / r;
        
        q.x = rinv * (m.m31 + m.m13);
        q.y = rinv * (m.m32 + m.m23);
        q.z = r * 0.5f;
        q.w = rinv * (m.m21 - m.m12);
    }
    
    return q;
}

Mat4 Mat4::FromQuat(Quat q)
{
    float norm = M::Sqrt(Quat::Dot(q, q));
    float s = norm > 0.0f ? (2.0f / norm) : 0.0f;
    
    float x = q.x;
    float y = q.y;
    float z = q.z;
    float w = q.w;
    
    float xx = s * x * x;
    float xy = s * x * y;
    float wx = s * w * x;
    float yy = s * y * y;
    float yz = s * y * z;
    float wy = s * w * y;
    float zz = s * z * z;
    float xz = s * x * z;
    float wz = s * w * z;
    
    return Mat4(1.0f - yy - zz,     xy - wz,            xz + wy,        0.0f,
                xy + wz,            1.0f - xx - zz,     yz - wx,        0.0f,
                xz - wy,            yz + wx,            1.0f - xx - yy, 0.0f,
                0.0f,               0.0f,               0.0f,           1.0f);
}

Mat4 Mat4::FromMat3(const Mat3& _mat)
{
    return Mat4(_mat.m11, _mat.m12, _mat.m13, 0,
                _mat.m21, _mat.m22, _mat.m23, 0,
                _mat.m31, _mat.m32, _mat.m33, 0, 
                0       , 0       , 0       , 1);
}

Mat4 Mat4::FromNormalAngle(Float3 _normal, float _scale, Float3 _pos, float _angle)
{
    Float3 tangent;
    Float3 bitangent;
    Float3::TangentAngle(&tangent, &bitangent, _normal, _angle);
    
    Float4 row1 = Float4(Float3::Mul(bitangent, _scale), 0.0f);
    Float4 row2 = Float4(Float3::Mul(_normal, _scale), 0.0f);
    Float4 row3 = Float4(Float3::Mul(tangent, _scale), 0.0f);
    
    return Mat4(row1.f, row2.f, row3.f, Float4(_pos, 1.0f).f);
}

Mat4 Mat4::ProjectPlane(Float3 planeNormal)
{
    float xx = planeNormal.x * planeNormal.x;
    float yy = planeNormal.y * planeNormal.y;
    float zz = planeNormal.z * planeNormal.z;
    float xy = planeNormal.x * planeNormal.y;
    float xz = planeNormal.x * planeNormal.z;
    float yz = planeNormal.y * planeNormal.z;
    
    return Mat4(1.0f - xx,      -xy,        -xz,        0.0f,
                -xy,            1.0f - yy,  -yz,        0.0f,
                -xz,            -yz,        1.0f - zz,  0.0f,
                0.0f,           0.0f,       0.0f,       1.0f);
}

Mat4 Mat4::Mul(const Mat4& _a, const Mat4& _b)
{
    return Mat4(
        Mat4::MulFloat4(_a, Float4(_b.fc1)).f, 
        Mat4::MulFloat4(_a, Float4(_b.fc2)).f,
        Mat4::MulFloat4(_a, Float4(_b.fc3)).f, 
        Mat4::MulFloat4(_a, Float4(_b.fc4)).f);
}

Mat3 Mat3::Inverse(const Mat3& _a)
{
    float xx = _a.f[0];
    float xy = _a.f[3];
    float xz = _a.f[6];
    float yx = _a.f[1];
    float yy = _a.f[4];
    float yz = _a.f[7];
    float zx = _a.f[2];
    float zy = _a.f[5];
    float zz = _a.f[8];
    
    float det = 0.0f;
    det += xx * (yy * zz - yz * zy);
    det -= xy * (yx * zz - yz * zx);
    det += xz * (yx * zy - yy * zx);
    
    float det_rcp = 1.0f / det;
    
    return Mat3(+(yy * zz - yz * zy) * det_rcp, -(xy * zz - xz * zy) * det_rcp,
        +(xy * yz - xz * yy) * det_rcp, -(yx * zz - yz * zx) * det_rcp,
        +(xx * zz - xz * zx) * det_rcp, -(xx * yz - xz * yx) * det_rcp,
        +(yx * zy - yy * zx) * det_rcp, -(xx * zy - xy * zx) * det_rcp,
        +(xx * yy - xy * yx) * det_rcp);
}

Mat3 Mat3::Mul(const Mat3& _a, const Mat3& _b)
{
    return Mat3(
        Mat3::MulFloat3(_a, Float3(_b.fc1)), 
        Mat3::MulFloat3(_a, Float3(_b.fc2)),
        Mat3::MulFloat3(_a, Float3(_b.fc3)));
}

Mat3 Mat3::Abs(const Mat3& m)
{
    return Mat3(
        M::Abs(m.m11), M::Abs(m.m12), M::Abs(m.m13), 
        M::Abs(m.m21), M::Abs(m.m22), M::Abs(m.m23), 
        M::Abs(m.m31), M::Abs(m.m32), M::Abs(m.m33));
}

Mat3 Mat3::FromQuat(Quat q)
{
    float norm = M::Sqrt(Quat::Dot(q, q));
    float s = norm > 0.0f ? (2.0f / norm) : 0.0f;
    
    float x = q.x;
    float y = q.y;
    float z = q.z;
    float w = q.w;
    
    float xx = s * x * x;
    float xy = s * x * y;
    float wx = s * w * x;
    float yy = s * y * y;
    float yz = s * y * z;
    float wy = s * w * y;
    float zz = s * z * z;
    float xz = s * x * z;
    float wz = s * w * z;
    
    return Mat3(1.0f - yy - zz,     xy - wz,            xz + wy,
                xy + wz,            1.0f - xx - zz,     yz - wx,
                xz - wy,            yz + wx,            1.0f - xx - yy);
}

Float2 float2CalcLinearFit2D(const Float2* _points, int _num)
{
    float sumX = 0.0f;
    float sumY = 0.0f;
    float sumXX = 0.0f;
    float sumXY = 0.0f;
    
    for (int ii = 0; ii < _num; ++ii) {
        float xx = _points[ii].f[0];
        float yy = _points[ii].f[1];
        sumX += xx;
        sumY += yy;
        sumXX += xx * xx;
        sumXY += xx * yy;
    }
    
    
    float det = (sumXX * _num - sumX * sumX);
    float invDet = 1.0f / det;
    
    return Float2((-sumX * sumY + _num * sumXY) * invDet, (sumXX * sumY - sumX * sumXY) * invDet);
}


Float3 Float3::CalcLinearFit3D(const Float3* _points, int _num)
{
    float sumX = 0.0f;
    float sumY = 0.0f;
    float sumZ = 0.0f;
    float sumXX = 0.0f;
    float sumXY = 0.0f;
    float sumXZ = 0.0f;
    float sumYY = 0.0f;
    float sumYZ = 0.0f;
    
    for (int ii = 0; ii < _num; ++ii) {
        float xx = _points[ii].f[0];
        float yy = _points[ii].f[1];
        float zz = _points[ii].f[2];
        
        sumX += xx;
        sumY += yy;
        sumZ += zz;
        sumXX += xx * xx;
        sumXY += xx * yy;
        sumXZ += xx * zz;
        sumYY += yy * yy;
        sumYZ += yy * zz;
    }
    
    
    Mat3 mat(sumXX, sumXY, sumX, sumXY, sumYY, sumY, sumX, sumY, (float)(_num));
    Mat3 matInv = Mat3::Inverse(mat);
    
    return Float3(matInv.f[0] * sumXZ + matInv.f[1] * sumYZ + matInv.f[2] * sumZ,
                  matInv.f[3] * sumXZ + matInv.f[4] * sumYZ + matInv.f[5] * sumZ,
                  matInv.f[6] * sumXZ + matInv.f[7] * sumYZ + matInv.f[8] * sumZ);
}


Float3 Color4u::RGBtoHSV(Float3 rgb)
{
    float K = 0.f;
    float r = rgb.f[0];
    float g = rgb.f[1];
    float b = rgb.f[2];
    
    if (g < b)
    {
        Swap(g, b);
        K = -1.f;
    }
    
    if (r < g)
    {
        Swap(r, g);
        K = -2.f / 6.f - K;
    }
    
    float chroma = r - Min(g, b);
    return Float3(M::Abs(K + (g - b) / (6.f * chroma + 1e-20f)),
                  chroma / (r + 1e-20f),
                  r);
}

Float3 Color4u::HSVtoRGB(Float3 hsv)
{
    const float hh = hsv.f[0];
    const float ss = hsv.f[1];
    const float vv = hsv.f[2];
    
    const float px = M::Abs(M::Fract(hh + 1.0f) * 6.0f - 3.0f);
    const float py = M::Abs(M::Fract(hh + 2.0f / 3.0f) * 6.0f - 3.0f);
    const float pz = M::Abs(M::Fract(hh + 1.0f / 3.0f) * 6.0f - 3.0f);
    
    return Float3(vv * M::Lerp(1.0f, M::Saturate(px - 1.0f), ss), 
                  vv * M::Lerp(1.0f, M::Saturate(py - 1.0f), ss),
                  vv * M::Lerp(1.0f, M::Saturate(pz - 1.0f), ss));
}

Color4u Color4u::Blend(Color4u _a, Color4u _b, float _t)
{
    Float4 c1 = Color4u::ToFloat4(_a);
    Float4 c2 = Color4u::ToFloat4(_b);
    
    return Color4u::FromFloat4(
        M::Lerp(c1.x, c2.x, _t),
        M::Lerp(c1.y, c2.y, _t),
        M::Lerp(c1.z, c2.z, _t),
        M::Lerp(c1.w, c2.w, _t)
    );
}

Float4 Color4u::ToFloat4Linear(Float4 c)
{
    for (int i = 0; i < 3; i++) {
        c.f[i] = c.f[i] < 0.04045f ? c.f[i]/12.92f : M::Pow((c.f[i] + 0.055f)/1.055f, 2.4f);
    }
    return c;
}

Float4 Color4u::ToFloat4SRGB(Float4 cf) 
{
    for (int i = 0; i < 3; i++) {
        cf.f[i] = cf.f[i] <= 0.0031308 ? 
            (12.92f*cf.f[i]) : 
            1.055f*M::Pow(cf.f[i], 0.416666f) - 0.055f;
    }
    return cf;
}

Quat Quat::Lerp(Quat _a, Quat _b, float t)
{
    float tinv = 1.0f - t;
    float dot = Quat::Dot(_a, _b);
    Quat r;
    if (dot >= 0.0f) {
        r = Quat(tinv * _a.x + t * _b.x, 
                 tinv * _a.y + t * _b.y, 
                 tinv * _a.z + t * _b.z, 
                 tinv * _a.w + t * _b.w);
    } else {
        r = Quat(tinv * _a.x - t * _b.x, 
                 tinv * _a.y - t * _b.y, 
                 tinv * _a.z - t * _b.z, 
                 tinv * _a.w - t * _b.w);
    }
    return Quat::Norm(r);
}

Quat Quat::Slerp(Quat _a, Quat _b, float t)
{
    const float epsilon = 1e-6f;
    
    float dot = Quat::Dot(_a, _b);
    bool flip = false;
    if (dot < 0.0f) {
        flip = true;
        dot *= -1.0f;
    }
    
    float s1, s2;
    if (dot > (1.0f - epsilon)) {
        s1 = 1.0f - t;
        s2 = t;
        if (flip)
            s2 *= -1.0f;
    } else {
        float omega = M::ACos(dot);
        float inv_omega_sin = 1.0f / M::Sin(omega);
        s1 = M::Sin((1.0f - t) * omega) * inv_omega_sin;
        s2 = M::Sin(t * omega) * inv_omega_sin;
        if (flip)
            s2 *= -1.0f;
    }

    return Quat(s1 * _a.x + s2 * _b.x, 
                s1 * _a.y + s2 * _b.y, 
                s1 * _a.z + s2 * _b.z,
                s1 * _a.w + s2 * _b.w);
}

Float3 Quat::ToEuler(Quat q)
{
    float sinr_cosp = 2 * (q.w * q.x + q.y * q.z);
    float cosr_cosp = 1 - 2 * (q.x * q.x + q.y * q.y);
    float x = M::ATan2(sinr_cosp, cosr_cosp);
    
    float sinp = 2 * (q.w * q.y - q.z * q.x);
    float y;
    if (M::Abs(sinp) >= 1)
        y = M::CopySign(M_HALFPI, sinp);
    else
        y = M::ASin(sinp);
    
    float siny_cosp = 2 * (q.w * q.z + q.x * q.y);
    float cosy_cosp = 1 - 2 * (q.y * q.y + q.z * q.z);
    float z = M::ATan2(siny_cosp, cosy_cosp);
    
    return Float3(x, y, z);
}

Quat Quat::FromEuler(Float3 _vec3)
{
    float z = _vec3.z;
    float x = _vec3.x;
    float y = _vec3.y;
    
    float cy = M::Cos(z * 0.5f);
    float sy = M::Sin(z * 0.5f);
    float cp = M::Cos(y * 0.5f);
    float sp = M::Sin(y * 0.5f);
    float cr = M::Cos(x * 0.5f);
    float sr = M::Sin(x * 0.5f);
    
    Quat q;
    q.w = cr * cp * cy + sr * sp * sy;
    q.x = sr * cp * cy - cr * sp * sy;
    q.y = cr * sp * cy + sr * cp * sy;
    q.z = cr * cp * sy - sr * sp * cy;
    
    return q;
}

Float3 Plane::CalcNormal(Float3 _va, Float3 _vb, Float3 _vc)
{
    Float3 ba = Float3::Sub(_vb, _va);
    Float3 ca = Float3::Sub(_vc, _va);
    Float3 baca = Float3::Cross(ca, ba);
    
    return Float3::Norm(baca);
}

Plane Plane::From3Points(Float3 _va, Float3 _vb, Float3 _vc)
{
    Float3 normal = Plane::CalcNormal(_va, _vb, _vc);
    return Plane(normal, -Float3::Dot(normal, _va));
}

Plane Plane::FromNormalPoint(Float3 _normal, Float3 _p)
{
    ASSERT(M::IsEqual(Float3::Dot(_normal, _normal), 1));

    float d = Float3::Dot(_normal, _p);
    return Plane(_normal, -d);
}

float Plane::Distance(Plane _plane, Float3 _p)
{
    return Float3::Dot(_plane.normal, _p) + _plane.d;
}

Float3 Plane::ProjectPoint(Plane _plane, Float3 _p)
{
    return Float3::Sub(_p, Float3::Mul(_plane.normal, Distance(_plane, _p)));
}

Float3 Plane::ClosestPointToOrigin(Plane _plane)
{
    return Float3::Mul(_plane.normal, -_plane.d);
}

float Plane::HitRay(Plane _plane, Float3 _origin, Float3 _direction)
{
    float VdotN = Float3::Dot(_direction, _plane.normal);
    if (M::Abs(VdotN) < 0.000001f)
        return -1.0f;
    float PdotN = Float3::Dot(_origin, _plane.normal);
    float t = -(PdotN + _plane.d)/VdotN;
    return t;    
}


AABB AABB::Transform(const AABB& aabb, const Mat4& mat)
{
    Float3 center = aabb.Center();
    Float3 extents = aabb.Extents();
    
    Mat3 rotMat = Mat3(mat.fc1, mat.fc2, mat.fc3);
    Mat3 absMat  = Mat3::Abs(rotMat);
    Float3 newCenter = Mat4::MulFloat3(mat, center);
    Float3 newExtents = Mat3::MulFloat3(absMat, extents);
    
    return AABB(Float3::Sub(newCenter, newExtents), Float3::Add(newCenter, newExtents));
}

Float2 MathUtil::ProjectPointToScreenPixels(Float3 pt, const Mat4& cameraWorldToClipMat, const RectFloat& viewport)
{
    Float4 pos = Float4(pt, 1);
    pos = Mat4::MulFloat4(cameraWorldToClipMat, pos);
    if (pos.w <= 0)
        return Float2(-1, -1);  // Behind the camera

    pos = pos * (1/pos.w);

    pos.x = 0.5f*pos.x + 0.5f;
    pos.y = 0.5f*pos.y + 0.5f;

    pos.x *= viewport.Width();
    pos.y *= viewport.Height();
    pos.x += viewport.xmin;
    pos.y += viewport.ymin;

    return Float2(pos.x, pos.y);
}


DEFINE_HANDLE(HandleDummy);

_private::HandlePoolTable* _private::handleCreatePoolTable(uint32 capacity, MemAllocator* alloc)
{
    uint32 maxSize = AlignValue(capacity, 16u);

    MemSingleShotMalloc<HandlePoolTable> buff;
    HandlePoolTable* tbl = buff.AddMemberArray<uint32>(offsetof(HandlePoolTable, dense), maxSize)
    .AddMemberArray<uint32>(offsetof(HandlePoolTable, sparse), maxSize)
    .Calloc(alloc);
    tbl->capacity = capacity;
    handleResetPoolTable(tbl);

    return tbl;
}

void _private::handleDestroyPoolTable(HandlePoolTable* tbl, MemAllocator* alloc)
{
    MemSingleShotMalloc<HandlePoolTable>::Free(tbl, alloc);
}

bool _private::handleGrowPoolTable(HandlePoolTable** pTbl, MemAllocator* alloc)
{
    HandlePoolTable* tbl = *pTbl;
    uint32 newCapacity = tbl->capacity << 1;

    HandlePoolTable* newTable = handleCreatePoolTable(newCapacity, alloc);
    if (!newTable)
        return false;
    newTable->count = tbl->count;
    memcpy(newTable->dense, tbl->dense, sizeof(uint32) * tbl->capacity);
    memcpy(newTable->sparse, tbl->sparse, sizeof(uint32) * tbl->capacity);

    handleDestroyPoolTable(tbl, alloc);
    *pTbl = newTable;
    return true;
}

_private::HandlePoolTable* _private::handleClone(HandlePoolTable* tbl, MemAllocator* alloc)
{
    ASSERT(tbl->capacity);
    HandlePoolTable* newTable = handleCreatePoolTable(tbl->capacity, alloc);
    if (!newTable)
        return nullptr;

    newTable->count = tbl->count;
    memcpy(newTable->dense, tbl->dense, sizeof(uint32) * tbl->capacity);
    memcpy(newTable->sparse, tbl->sparse, sizeof(uint32) * tbl->capacity);

    return newTable;
}

uint32 _private::handleNew(HandlePoolTable* tbl)
{
    if (tbl->count < tbl->capacity) {
        uint32 index = tbl->count++;
        HandleDummy handle(tbl->dense[index]);

        uint32 gen = handle.GetGen();
        uint32 sparseIndex = handle.GetSparseIndex();
        HandleDummy newHandle;
        newHandle.Set(++gen, sparseIndex);

        tbl->dense[index] = static_cast<uint32>(newHandle);
        tbl->sparse[sparseIndex] = index;
        return static_cast<uint32>(newHandle);
    } else {
        ASSERT_MSG(0, "handle pool table is full");
    }

    return UINT32_MAX;
}

void _private::handleDel(HandlePoolTable* tbl, uint32 handle)
{
    ASSERT(tbl->count > 0);
    ASSERT(handleIsValid(tbl, handle));

    HandleDummy h(handle);

    uint32 index = tbl->sparse[h.GetSparseIndex()];
    HandleDummy lastHandle = HandleDummy(tbl->dense[--tbl->count]);

    tbl->dense[tbl->count] = handle;
    tbl->sparse[lastHandle.GetSparseIndex()] = index;
    tbl->dense[index] = static_cast<uint32>(lastHandle);
}

void _private::handleResetPoolTable(HandlePoolTable* tbl)
{
    tbl->count = 0;
    uint32* dense = tbl->dense;
    for (uint32 i = 0, c = tbl->capacity; i < c; i++) {
        HandleDummy h;
        h.Set(0, i);
        dense[i] = static_cast<uint32>(h);
    }
}

bool _private::handleIsValid(const HandlePoolTable* tbl, uint32 handle)
{
    ASSERT(handle);
    HandleDummy h(handle);

    uint32 index = tbl->sparse[h.GetSparseIndex()];
    return index < tbl->count && tbl->dense[index] == handle;
}

uint32 _private::handleAt(const HandlePoolTable* tbl, uint32 index)
{
    ASSERT(index < tbl->count);
    return tbl->dense[index];
}

bool _private::handleFull(const HandlePoolTable* tbl)
{
    return tbl->count == tbl->capacity;
}

size_t _private::handleGetMemoryRequirement(uint32 capacity)
{
    uint32 maxSize = AlignValue(capacity, 16u);
    
    MemSingleShotMalloc<HandlePoolTable> mallocator;
    return mallocator.AddMemberArray<uint32>(offsetof(HandlePoolTable, dense), maxSize)
        .AddMemberArray<uint32>(offsetof(HandlePoolTable, sparse), maxSize)
        .GetMemoryRequirement();
}

_private::HandlePoolTable* _private::handleCreatePoolTableWithBuffer(uint32 capacity, void* data, size_t size)
{
    uint32 maxSize = AlignValue(capacity, 16u);
    
    MemSingleShotMalloc<HandlePoolTable> mallocator;
    HandlePoolTable* tbl = mallocator.AddMemberArray<uint32>(offsetof(HandlePoolTable, dense), maxSize)
        .AddMemberArray<uint32>(offsetof(HandlePoolTable, sparse), maxSize)
        .Calloc(data, size);
    tbl->capacity = capacity;
    handleResetPoolTable(tbl);
    
    return tbl;
}

bool _private::handleGrowPoolTableWithBuffer(HandlePoolTable** pTbl, void* buff, size_t size)
{
    HandlePoolTable* tbl = *pTbl;
    uint32 newCapacity = tbl->capacity << 1;
    
    HandlePoolTable* newTable = handleCreatePoolTableWithBuffer(newCapacity, buff, size);
    if (!newTable)
        return false;
    newTable->count = tbl->count;
    memcpy(newTable->dense, tbl->dense, sizeof(uint32) * tbl->capacity);
    memcpy(newTable->sparse, tbl->sparse, sizeof(uint32) * tbl->capacity);
    
    *pTbl = newTable;
    return true;
}




#define SOKOL_ARGS_IMPL
#define SOKOL_ASSERT(c)     ASSERT(c)
#define SOKOL_LOG(msg)      LOG_DEBUG(msg)
#define SOKOL_CALLOC(n,s)   Mem::AllocZero((n)*(s))
#define SOKOL_FREE(p)       Mem::Free(p)
#define SOKOL_ARGS_API_DECL 
#define SOKOL_API_IMPL      
PRAGMA_DIAGNOSTIC_PUSH()
PRAGMA_DIAGNOSTIC_IGNORED_MSVC(4505)
PRAGMA_DIAGNOSTIC_IGNORED_CLANG_GCC("-Wunused-function")
//----------------------------------------------------------------------------------------------------------------------
// External/sokol/sokol_args.h

#if defined(SOKOL_IMPL) && !defined(SOKOL_ARGS_IMPL)
#define SOKOL_ARGS_IMPL
#endif
#ifndef SOKOL_ARGS_INCLUDED
/*
    sokol_args.h    -- cross-platform key/value arg-parsing for web and native

    Project URL: https://github.com/floooh/sokol

    Do this:
        #define SOKOL_IMPL or
        #define SOKOL_ARGS_IMPL
    before you include this file in *one* C or C++ file to create the
    implementation.

    Optionally provide the following defines with your own implementations:

    SOKOL_ASSERT(c)     - your own assert macro (default: assert(c))
    SOKOL_LOG(msg)      - your own logging functions (default: puts(msg))
    SOKOL_CALLOC(n,s)   - your own calloc() implementation (default: calloc(n,s))
    SOKOL_FREE(p)       - your own free() implementation (default: free(p))
    SOKOL_ARGS_API_DECL - public function declaration prefix (default: extern)
    SOKOL_API_DECL      - same as SOKOL_ARGS_API_DECL
    SOKOL_API_IMPL      - public function implementation prefix (default: -)

    If sokol_args.h is compiled as a DLL, define the following before
    including the declaration or implementation:

    SOKOL_DLL

    On Windows, SOKOL_DLL will define SOKOL_ARGS_API_DECL as __declspec(dllexport)
    or __declspec(dllimport) as needed.

    OVERVIEW
    ========
    sokol_args.h provides a simple unified argument parsing API for WebAssembly and
    native apps.

    When running as WebAssembly app, arguments are taken from the page URL:

    https://floooh.github.io/tiny8bit/kc85.html?type=kc85_3&mod=m022&snapshot=kc85/jungle.kcc

    The same arguments provided to a command line app:

    kc85 type=kc85_3 mod=m022 snapshot=kc85/jungle.kcc

    ARGUMENT FORMATTING
    ===================
    On the web platform, arguments must be formatted as a valid URL query string
    with 'percent encoding' used for special characters.

    Strings are expected to be UTF-8 encoded (although sokol_args.h doesn't
    contain any special UTF-8 handling). See below on how to obtain
    UTF-8 encoded argc/argv values on Windows when using WinMain() as
    entry point.

    On native platforms the following rules must be followed:

    Arguments have the general form

        key=value

    Key/value pairs are separated by 'whitespace', valid whitespace
    characters are space and tab.

    Whitespace characters in front and after the separating '=' character
    are ignored:

        key = value

    ...is the same as

        key=value

    The 'key' string must be a simple string without escape sequences or whitespace.

    Currently 'single keys' without values are not allowed, but may be
    in the future.

    The 'value' string can be quoted, and quoted value strings can contain
    whitespace:

        key = 'single-quoted value'
        key = "double-quoted value"

    Single-quoted value strings can contain double quotes, and vice-versa:

        key = 'single-quoted value "can contain double-quotes"'
        key = "double-quoted value 'can contain single-quotes'"

    Note that correct quoting can be tricky on some shells, since command
    shells may remove quotes, unless they're escaped.

    Value strings can contain a small selection of escape sequences:

        \n  - newline
        \r  - carriage return
        \t  - tab
        \\  - escaped backslash

    (more escape codes may be added in the future).

    CODE EXAMPLE
    ============

        int main(int argc, char* argv[]) {
            sargs_setup(&(sargs_desc){
                .argc = argc,
                .argv = argv
            });

            if (sargs_exists("bla")) {
                ...
            }

            const char* val0 = sargs_value("bla");

            const char* val1 = sargs_value_def("bla", "default_value");

            if (sargs_equals("type", "kc85_4")) {
                ...
            }

            if (sargs_boolean("joystick_enabled")) {
                ...
            }

            for (int i = 0; i < sargs_num_args(); i++) {
                printf("key: %s, value: %s\n", sargs_key_at(i), sargs_value_at(i));
            }

            int index = sargs_find("bla");
            printf("key: %s, value: %s\n", sargs_key_at(index), sargs_value_at(index));

            sargs_shutdown();
        }

    WINMAIN AND ARGC / ARGV
    =======================
    On Windows with WinMain() based apps, getting UTF8-encoded command line
    arguments is a bit more complicated:

    First call GetCommandLineW(), this returns the entire command line
    as UTF-16 string. Then call CommandLineToArgvW(), this parses the
    command line string into the usual argc/argv format (but in UTF-16).
    Finally convert the UTF-16 strings in argv[] into UTF-8 via
    WideCharToMultiByte().

    See the function _sapp_win32_command_line_to_utf8_argv() in sokol_app.h
    for example code how to do this (if you're using sokol_app.h, it will
    already convert the command line arguments to UTF-8 for you of course,
    so you can plug them directly into sokol_app.h).

    API DOCUMENTATION
    =================
    void sargs_setup(const sargs_desc* desc)
        Initialize sokol_args, desc contains the following configuration
        parameters:
            int argc        - the main function's argc parameter
            char** argv     - the main function's argv parameter
            int max_args    - max number of key/value pairs, default is 16
            int buf_size    - size of the internal string buffer, default is 16384

        Note that on the web, argc and argv will be ignored and the arguments
        will be taken from the page URL instead.

        sargs_setup() will allocate 2 memory chunks: one for keeping track
        of the key/value args of size 'max_args*8', and a string buffer
        of size 'buf_size'.

    void sargs_shutdown(void)
        Shutdown sokol-args and free any allocated memory.

    bool sargs_isvalid(void)
        Return true between sargs_setup() and sargs_shutdown()

    bool sargs_exists(const char* key)
        Test if a key arg exists.

    const char* sargs_value(const char* key)
        Return value associated with key. Returns an empty
        string ("") if the key doesn't exist.

    const char* sargs_value_def(const char* key, const char* default)
        Return value associated with key, or the provided default
        value if the value doesn't exist.

    bool sargs_equals(const char* key, const char* val);
        Return true if the value associated with key matches
        the 'val' argument.

    bool sargs_boolean(const char* key)
        Return true if the value string of 'key' is one
        of 'true', 'yes', 'on'.

    int sargs_find(const char* key)
        Find argument by key name and return its index, or -1 if not found.

    int sargs_num_args(void)
        Return number of key/value pairs.

    const char* sargs_key_at(int index)
        Return the key name of argument at index. Returns empty string if
        is index is outside range.

    const char* sargs_value_at(int index)
        Return the value of argument at index. Returns empty string
        if index is outside range.

    TODO
    ====
    - parsing errors?

    LICENSE
    =======

    zlib/libpng license

    Copyright (c) 2018 Andre Weissflog

    This software is provided 'as-is', without any express or implied warranty.
    In no event will the authors be held liable for any damages arising from the
    use of this software.

    Permission is granted to anyone to use this software for any purpose,
    including commercial applications, and to alter it and redistribute it
    freely, subject to the following restrictions:

        1. The origin of this software must not be misrepresented; you must not
        claim that you wrote the original software. If you use this software in a
        product, an acknowledgment in the product documentation would be
        appreciated but is not required.

        2. Altered source versions must be plainly marked as such, and must not
        be misrepresented as being the original software.

        3. This notice may not be removed or altered from any source
        distribution.
*/
#define SOKOL_ARGS_INCLUDED (1)
#include <stdint.h>
#include <stdbool.h>

#if defined(SOKOL_API_DECL) && !defined(SOKOL_ARGS_API_DECL)
#define SOKOL_ARGS_API_DECL SOKOL_API_DECL
#endif
#ifndef SOKOL_ARGS_API_DECL
#if defined(_WIN32) && defined(SOKOL_DLL) && defined(SOKOL_ARGS_IMPL)
#define SOKOL_ARGS_API_DECL __declspec(dllexport)
#elif defined(_WIN32) && defined(SOKOL_DLL)
#define SOKOL_ARGS_API_DECL __declspec(dllimport)
#else
#define SOKOL_ARGS_API_DECL extern
#endif
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct sargs_desc {
    int argc;
    char** argv;
    int max_args;
    int buf_size;
} sargs_desc;

typedef struct sargs_state sargs_state;

/* setup sokol-args */
SOKOL_ARGS_API_DECL sargs_state* sargs_create(const sargs_desc* desc);
/* shutdown sokol-args */
SOKOL_ARGS_API_DECL void sargs_destroy(sargs_state* state);
/* true between sargs_create() and sargs_destroy() */
SOKOL_ARGS_API_DECL bool sargs_isvalid(const sargs_state* state);
/* test if an argument exists by key name */
SOKOL_ARGS_API_DECL bool sargs_exists(const sargs_state* state, const char* key);
/* get value by key name, return empty string if key doesn't exist */
SOKOL_ARGS_API_DECL const char* sargs_value(const sargs_state* state, const char* key);
/* get value by key name, return provided default if key doesn't exist */
SOKOL_ARGS_API_DECL const char* sargs_value_def(const sargs_state* state, const char* key, const char* def);
/* return true if val arg matches the value associated with key */
SOKOL_ARGS_API_DECL bool sargs_equals(const sargs_state* state, const char* key, const char* val);
/* return true if key's value is "true", "yes" or "on" */
SOKOL_ARGS_API_DECL bool sargs_boolean(const sargs_state* state, const char* key);
/* get index of arg by key name, return -1 if not exists */
SOKOL_ARGS_API_DECL int sargs_find(const sargs_state* state, const char* key);
/* get number of parsed arguments */
SOKOL_ARGS_API_DECL int sargs_num_args(const sargs_state* state);
/* get key name of argument at index, or empty string */
SOKOL_ARGS_API_DECL const char* sargs_key_at(const sargs_state* state, int index);
/* get value string of argument at index, or empty string */
SOKOL_ARGS_API_DECL const char* sargs_value_at(const sargs_state* state, int index);

#ifdef __cplusplus
} /* extern "C" */

/* reference-based equivalents for c++ */
inline sargs_state* sargs_create(const sargs_desc& desc) { return sargs_create(&desc); }

#endif
#endif // SOKOL_ARGS_INCLUDED

/*--- IMPLEMENTATION ---------------------------------------------------------*/
#ifdef SOKOL_ARGS_IMPL
#define SOKOL_ARGS_IMPL_INCLUDED (1)
#include <string.h> /* memset, strcmp */

#if defined(__EMSCRIPTEN__)
#include <emscripten/emscripten.h>
#endif

#ifndef SOKOL_API_IMPL
    #define SOKOL_API_IMPL
#endif
#ifndef SOKOL_DEBUG
    #ifndef NDEBUG
        #define SOKOL_DEBUG (1)
    #endif
#endif
#ifndef SOKOL_ASSERT
    #include <assert.h>
    #define SOKOL_ASSERT(c) assert(c)
#endif
#if !defined(SOKOL_CALLOC) && !defined(SOKOL_FREE)
    #include <stdlib.h>
#endif
#if !defined(SOKOL_CALLOC)
    #define SOKOL_CALLOC(n,s) calloc(n,s)
#endif
#if !defined(SOKOL_FREE)
    #define SOKOL_FREE(p) free(p)
#endif
#ifndef SOKOL_LOG
    #ifdef SOKOL_DEBUG
        #include <stdio.h>
        #define SOKOL_LOG(s) { SOKOL_ASSERT(s); puts(s); }
    #else
        #define SOKOL_LOG(s)
    #endif
#endif

#ifndef _SOKOL_PRIVATE
    #if defined(__GNUC__) || defined(__clang__)
        #define _SOKOL_PRIVATE __attribute__((unused)) static
    #else
        #define _SOKOL_PRIVATE static
    #endif
#endif

#define _sargs_def(val, def) (((val) == 0) ? (def) : (val))

#define _SARGS_MAX_ARGS_DEF (16)
#define _SARGS_BUF_SIZE_DEF (16*1024)

/* parser state */
#define _SARGS_EXPECT_KEY (1<<0)
#define _SARGS_EXPECT_SEP (1<<1)
#define _SARGS_EXPECT_VAL (1<<2)
#define _SARGS_PARSING_KEY (1<<3)
#define _SARGS_PARSING_VAL (1<<4)
#define _SARGS_ERROR (1<<5)

/* a key/value pair struct */
typedef struct {
    int key;        /* index to start of key string in buf */
    int val;        /* index to start of value string in buf */
} _sargs_kvp_t;

/* sokol-args state */
typedef struct sargs_state {
    int max_args;       /* number of key/value pairs in args array */
    int num_args;       /* number of valid items in args array */
    _sargs_kvp_t* args;   /* key/value pair array */
    int buf_size;       /* size of buffer in bytes */
    int buf_pos;        /* current buffer position */
    char* buf;          /* character buffer, first char is reserved and zero for 'empty string' */
    bool valid;
    uint32_t parse_state;
    char quote;         /* current quote char, 0 if not in a quote */
    bool in_escape;     /* currently in an escape sequence */
} sargs_state;

/*== PRIVATE IMPLEMENTATION FUNCTIONS ========================================*/

_SOKOL_PRIVATE void _sargs_putc(sargs_state* state, char c) {
    if ((state->buf_pos+2) < state->buf_size) {
        state->buf[state->buf_pos++] = c;
    }
}

_SOKOL_PRIVATE const char* _sargs_str(const sargs_state* state, int index) {
    SOKOL_ASSERT((index >= 0) && (index < state->buf_size));
    return &state->buf[index];
}

/*-- argument parser functions ------------------*/
_SOKOL_PRIVATE void _sargs_expect_key(sargs_state* state) {
    state->parse_state = _SARGS_EXPECT_KEY;
}

_SOKOL_PRIVATE bool _sargs_key_expected(sargs_state* state) {
    return 0 != (state->parse_state & _SARGS_EXPECT_KEY);
}

_SOKOL_PRIVATE void _sargs_expect_val(sargs_state* state) {
    state->parse_state = _SARGS_EXPECT_VAL;
}

_SOKOL_PRIVATE bool _sargs_val_expected(const sargs_state* state) {
    return 0 != (state->parse_state & _SARGS_EXPECT_VAL);
}

_SOKOL_PRIVATE void _sargs_expect_sep(sargs_state* state) {
    state->parse_state = _SARGS_EXPECT_SEP;
}

_SOKOL_PRIVATE bool _sargs_any_expected(const sargs_state* state) {
    return 0 != (state->parse_state & (_SARGS_EXPECT_KEY | _SARGS_EXPECT_VAL | _SARGS_EXPECT_SEP));
}

_SOKOL_PRIVATE bool _sargs_is_separator(char c) {
    return c == '=';
}

_SOKOL_PRIVATE bool _sargs_is_quote(const sargs_state* state, char c) {
    if (0 == state->quote) {
        return (c == '\'') || (c == '"');
    }
    else {
        return c == state->quote;
    }
}

_SOKOL_PRIVATE void _sargs_begin_quote(sargs_state* state, char c) {
    state->quote = c;
}

_SOKOL_PRIVATE void _sargs_end_quote(sargs_state* state) {
    state->quote = 0;
}

_SOKOL_PRIVATE bool _sargs_in_quotes(const sargs_state* state) {
    return 0 != state->quote;
}

_SOKOL_PRIVATE bool _sargs_is_whitespace(const sargs_state* state, char c) {
    return !_sargs_in_quotes(state) && ((c == ' ') || (c == '\t'));
}

_SOKOL_PRIVATE void _sargs_start_key(sargs_state* state) {
    SOKOL_ASSERT(state->num_args < state->max_args);
    state->parse_state = _SARGS_PARSING_KEY;
    state->args[state->num_args].key = state->buf_pos;
}

_SOKOL_PRIVATE void _sargs_end_key(sargs_state* state) {
    SOKOL_ASSERT(state->num_args < state->max_args);
    _sargs_putc(state, 0);
    state->parse_state = 0;
}

_SOKOL_PRIVATE bool _sargs_parsing_key(const sargs_state* state) {
    return 0 != (state->parse_state & _SARGS_PARSING_KEY);
}

_SOKOL_PRIVATE void _sargs_start_val(sargs_state* state) {
    SOKOL_ASSERT(state->num_args < state->max_args);
    state->parse_state = _SARGS_PARSING_VAL;
    state->args[state->num_args].val = state->buf_pos;
}

_SOKOL_PRIVATE void _sargs_end_val(sargs_state* state) {
    SOKOL_ASSERT(state->num_args < state->max_args);
    _sargs_putc(state, 0);
    state->num_args++;
    state->parse_state = 0;
}

_SOKOL_PRIVATE bool _sargs_is_escape(char c) {
    return '\\' == c;
}

_SOKOL_PRIVATE void _sargs_start_escape(sargs_state* state) {
    state->in_escape = true;
}

_SOKOL_PRIVATE bool _sargs_in_escape(const sargs_state* state) {
    return state->in_escape;
}

_SOKOL_PRIVATE char _sargs_escape(char c) {
    switch (c) {
        case 'n':   return '\n';
        case 't':   return '\t';
        case 'r':   return '\r';
        case '\\':  return '\\';
        default:    return c;
    }
}

_SOKOL_PRIVATE void _sargs_end_escape(sargs_state* state) {
    state->in_escape = false;
}

_SOKOL_PRIVATE bool _sargs_parsing_val(const sargs_state* state) {
    return 0 != (state->parse_state & _SARGS_PARSING_VAL);
}

_SOKOL_PRIVATE bool _sargs_parse_carg(sargs_state* state, const char* src) {
    char c;
    while (0 != (c = *src++)) {
        if (_sargs_in_escape(state)) {
            c = _sargs_escape(c);
            _sargs_end_escape(state);
        }
        else if (_sargs_is_escape(c)) {
            _sargs_start_escape(state);
            continue;
        }
        if (_sargs_any_expected(state)) {
            if (!_sargs_is_whitespace(state, c)) {
                /* start of key, value or separator */
                if (_sargs_key_expected(state)) {
                    /* start of new key */
                    _sargs_start_key(state);
                }
                else if (_sargs_val_expected(state)) {
                    /* start of value */
                    if (_sargs_is_quote(state, c)) {
                        _sargs_begin_quote(state, c);
                        continue;
                    }
                    _sargs_start_val(state);
                }
                else {
                    /* separator */
                    if (_sargs_is_separator(c)) {
                        _sargs_expect_val(state);
                        continue;
                    }
                }
            }
            else {
                /* skip white space */
                continue;
            }
        }
        else if (_sargs_parsing_key(state)) {
            if (_sargs_is_whitespace(state, c) || _sargs_is_separator(c)) {
                /* end of key string */
                _sargs_end_key(state);
                if (_sargs_is_separator(c)) {
                    _sargs_expect_val(state);
                }
                else {
                    _sargs_expect_sep(state);
                }
                continue;
            }
        }
        else if (_sargs_parsing_val(state)) {
            if (_sargs_in_quotes(state)) {
                /* when in quotes, whitespace is a normal character
                   and a matching quote ends the value string
                */
                if (_sargs_is_quote(state, c)) {
                    _sargs_end_quote(state);
                    _sargs_end_val(state);
                    _sargs_expect_key(state);
                    continue;
                }
            }
            else if (_sargs_is_whitespace(state, c)) {
                /* end of value string (no quotes) */
                _sargs_end_val(state);
                _sargs_expect_key(state);
                continue;
            }
        }
        _sargs_putc(state, c);
    }
    if (_sargs_parsing_key(state)) {
        _sargs_end_key(state);
        _sargs_expect_sep(state);
    }
    else if (_sargs_parsing_val(state) && !_sargs_in_quotes(state)) {
        _sargs_end_val(state);
        _sargs_expect_key(state);
    }
    return true;
}

_SOKOL_PRIVATE bool _sargs_parse_cargs(sargs_state* state, int argc, const char** argv) {
    _sargs_expect_key(state);
    bool retval = true;
    for (int i = 1; i < argc; i++) {
        retval &= _sargs_parse_carg(state, argv[i]);
    }
    state->parse_state = 0;
    return retval;
}

/*-- EMSCRIPTEN IMPLEMENTATION -----------------------------------------------*/
#if defined(__EMSCRIPTEN__)

#ifdef __cplusplus
extern "C" {
#endif
EMSCRIPTEN_KEEPALIVE void _sargs_add_kvp(sargs_state* state, const char* key, const char* val) {
    SOKOL_ASSERT(state->valid && key && val);
    if (state->num_args >= state->max_args) {
        return;
    }

    /* copy key string */
    char c;
    state->args[state->num_args].key = state->buf_pos;
    const char* ptr = key;
    while (0 != (c = *ptr++)) {
        _sargs_putc(state, c);
    }
    _sargs_putc(state, 0);

    /* copy value string */
    state->args[state->num_args].val = state->buf_pos;
    ptr = val;
    while (0 != (c = *ptr++)) {
        _sargs_putc(state, c);
    }
    _sargs_putc(state, 0);

    state->num_args++;
}
#ifdef __cplusplus
} /* extern "C" */
#endif

/* JS function to extract arguments from the page URL */
EM_JS(void, sargs_js_parse_url, (void), {
    var params = new URLSearchParams(window.location.search).entries();
    for (var p = params.next(); !p.done; p = params.next()) {
        var key = p.value[0];
        var val = p.value[1];
        var res = ccall('_sargs_add_kvp', 'void', ['string','string'], [key,val]);
    }
});

#endif /* EMSCRIPTEN */

/*== PUBLIC IMPLEMENTATION FUNCTIONS =========================================*/
SOKOL_API_IMPL sargs_state* sargs_create(const sargs_desc* desc) {
    SOKOL_ASSERT(desc);
    sargs_state* state = (sargs_state*)SOKOL_CALLOC(1, sizeof(sargs_state));
    memset(state, 0, sizeof(*state));
    state->max_args = _sargs_def(desc->max_args, _SARGS_MAX_ARGS_DEF);
    state->buf_size = _sargs_def(desc->buf_size, _SARGS_BUF_SIZE_DEF);
    SOKOL_ASSERT(state->buf_size > 8);
    state->args = (_sargs_kvp_t*) SOKOL_CALLOC((size_t)state->max_args, sizeof(_sargs_kvp_t));
    state->buf = (char*) SOKOL_CALLOC((size_t)state->buf_size, sizeof(char));
    /* the first character in buf is reserved and always zero, this is the 'empty string' */
    state->buf_pos = 1;
    state->valid = true;

    /* parse argc/argv */
    _sargs_parse_cargs(state, desc->argc, (const char**) desc->argv);

    #if defined(__EMSCRIPTEN__)
        /* on emscripten, also parse the page URL*/
        sargs_js_parse_url(state);
    #endif
    return state;
}

SOKOL_API_IMPL void sargs_destroy(sargs_state* state) {
    if (state) {
        SOKOL_ASSERT(state->valid);
        if (state->args) {
            SOKOL_FREE(state->args);
            state->args = 0;
        }
        if (state->buf) {
            SOKOL_FREE(state->buf);
            state->buf = 0;
        }
        state->valid = false;
        SOKOL_FREE(state);
    }
}

SOKOL_API_IMPL bool sargs_isvalid(const sargs_state* state) {
    return state->valid;
}

SOKOL_API_IMPL int sargs_find(const sargs_state* state, const char* key) {
    SOKOL_ASSERT(state->valid && key);
    for (int i = 0; i < state->num_args; i++) {
        if (0 == strcmp(_sargs_str(state, state->args[i].key), key)) {
            return i;
        }
    }
    return -1;
}

SOKOL_API_IMPL int sargs_num_args(const sargs_state* state) {
    SOKOL_ASSERT(state->valid);
    return state->num_args;
}

SOKOL_API_IMPL const char* sargs_key_at(const sargs_state* state, int index) {
    SOKOL_ASSERT(state->valid);
    if ((index >= 0) && (index < state->num_args)) {
        return _sargs_str(state, state->args[index].key);
    }
    else {
        /* index 0 is always the empty string */
        return _sargs_str(state, 0);
    }
}

SOKOL_API_IMPL const char* sargs_value_at(const sargs_state* state, int index) {
    SOKOL_ASSERT(state->valid);
    if ((index >= 0) && (index < state->num_args)) {
        return _sargs_str(state, state->args[index].val);
    }
    else {
        /* index 0 is always the empty string */
        return _sargs_str(state, 0);
    }
}

SOKOL_API_IMPL bool sargs_exists(const sargs_state* state, const char* key) {
    SOKOL_ASSERT(state->valid && key);
    return -1 != sargs_find(state, key);
}

SOKOL_API_IMPL const char* sargs_value(const sargs_state* state, const char* key) {
    SOKOL_ASSERT(state->valid && key);
    return sargs_value_at(state, sargs_find(state, key));
}

SOKOL_API_IMPL const char* sargs_value_def(const sargs_state* state, const char* key, const char* def) {
    SOKOL_ASSERT(state->valid && key && def);
    int arg_index = sargs_find(state, key);
    if (-1 != arg_index) {
        return sargs_value_at(state, arg_index);
    }
    else {
        return def;
    }
}

SOKOL_API_IMPL bool sargs_equals(const sargs_state* state, const char* key, const char* val) {
    SOKOL_ASSERT(state->valid && key && val);
    return 0 == strcmp(sargs_value(state, key), val);
}

SOKOL_API_IMPL bool sargs_boolean(const sargs_state* state, const char* key) {
    const char* val = sargs_value(state, key);
    return (0 == strcmp("true", val)) ||
           (0 == strcmp("yes", val)) ||
           (0 == strcmp("on", val));
}

#endif /* SOKOL_ARGS_IMPL */

PRAGMA_DIAGNOSTIC_POP()

#if PLATFORM_ANDROID
#include <android/asset_manager.h>
#endif

#define SETTINGS_NONE_PREDEFINED "_UNKNOWN_"

struct SettingsContext
{
    Array<SettingsKeyValue> keyValuePairs;  // Container to save none-predefined settings
    StaticArray<SettingsCustomCallbacks*, 8> customCallbacks;
};

static SettingsContext gSettings;

namespace Settings
{
    static bool _LoadFromINIInternal(const Blob& blob)
    {
        ASSERT(blob.IsValid());

        ini_t* ini = ini_load(reinterpret_cast<const char*>(blob.Data()), Mem::GetDefaultAlloc());
        if (!ini)
            return false;

        char keyTrimmed[64];
        char valueTrimmed[256];
        uint32 count = 0;

        for (int i = 0; i < ini_section_count(ini); i++) {
            const char* sectionName = ini_section_name(ini, i);

            for (uint32 c = 0; c < gSettings.customCallbacks.Count(); c++) {
                SettingsCustomCallbacks* callbacks = gSettings.customCallbacks[c];

                uint32 foundCatId = UINT32_MAX;
                for (uint32 catId = 0, catIdCount = callbacks->GetCategoryCount(); catId < catIdCount; catId++) {
                    if (Str::IsEqualNoCase(sectionName, callbacks->GetCategory(catId))) {
                        foundCatId = catId;
                        break;
                    }
                }

                for (int j = 0; j < ini_property_count(ini, i); j++) {
                    const char* key = ini_property_name(ini, i, j);
                    const char* value = ini_property_value(ini, i, j);
                    Str::Trim(keyTrimmed, sizeof(keyTrimmed), key);
                    Str::Trim(valueTrimmed, sizeof(valueTrimmed), value);

                    bool predefined = foundCatId != UINT32_MAX ? callbacks->ParseSetting(foundCatId, keyTrimmed, valueTrimmed) : false;

                    if (!predefined)
                        SetValue(keyTrimmed, valueTrimmed);

                    Debug::PrintLineFmt("\t%u) %s%s = %s", ++count, keyTrimmed, !predefined ? "(*)" : "", valueTrimmed);
                }
            } // for each custom settings parser
        }

        int sectionId = ini_find_section(ini, SETTINGS_NONE_PREDEFINED, Str::Len(SETTINGS_NONE_PREDEFINED));
        if (sectionId != -1) {
            for (int i = 0; i < ini_property_count(ini, sectionId); i++) {
                SetValue(ini_property_name(ini, sectionId, i), ini_property_value(ini, sectionId, i));
            }
        }

        ini_destroy(ini);
        return true;
    }
} // Settings

void Settings::AddCustomCallbacks(SettingsCustomCallbacks* callbacks)
{
    ASSERT(callbacks);

    uint32 index = gSettings.customCallbacks.Find(callbacks);
    if (index == UINT32_MAX) 
        gSettings.customCallbacks.Push(callbacks);
}

void Settings::RemoveCustomCallbacks(SettingsCustomCallbacks* callbacks)
{
    ASSERT(callbacks);

    uint32 index = gSettings.customCallbacks.Find(callbacks);
    if (index != UINT32_MAX) 
        gSettings.customCallbacks.RemoveAndSwap(index);
}

#if PLATFORM_ANDROID
bool Settings::InitializeFromAndroidAsset(AAssetManager* assetMgr, const char* iniFilepath)
{
    Debug::PrintLineFmt("Loading settings from assets: %s", iniFilepath);

    Blob blob;
    AAsset* asset = AAssetManager_open(assetMgr, iniFilepath, AASSET_MODE_BUFFER);
    if (asset && AAsset_getLength(asset) > 0) {
        off_t size = AAsset_getLength(asset);
        blob.Reserve(size + 1);
        int bytesRead = AAsset_read(asset, const_cast<void*>(blob.Data()), size);
        
        if (bytesRead > 0) {
            blob.SetSize(bytesRead);
            blob.Write<char>('\0');
        }

        AAsset_close(asset);
    }

    if (!blob.IsValid()) {
        Debug::PrintLineFmt("Opening ini file '%s' failed", iniFilepath);
        return false;
    }

    bool r = _LoadFromINIInternal(blob);
    blob.Free();

    if (!r)
        Debug::PrintLineFmt("Parsing ini file '%s' failed", iniFilepath);
    return r;
}
#endif  // PLATFORM_ANDROID

bool Settings::InitializeFromINI(const char* iniFilepath)
{
    Debug::PrintLineFmt("Loading settings from file: %s", iniFilepath);

    Blob blob;
    File f;
    if (f.Open(iniFilepath, FileOpenFlags::Read | FileOpenFlags::SeqScan)) {
        uint64 size = f.GetSize();
        if (size) {
            blob.Reserve(size + 1);
            size_t bytesRead = f.Read(const_cast<void*>(blob.Data()), size);
            blob.SetSize(bytesRead);
            blob.Write<char>('\0');
        }
        f.Close();
    }

    if (!blob.IsValid()) {
        Debug::PrintLineFmt("Opening ini file '%s' failed", iniFilepath);
        return false;
    }

    bool r = _LoadFromINIInternal(blob);
    blob.Free();

    if (!r) 
        Debug::PrintLineFmt("Parsing ini file '%s' failed", iniFilepath);
    return r;
}

void Settings::SaveToINI(const char* iniFilepath)
{
    Debug::PrintLineFmt("Saving settings to file: %s", iniFilepath);
    
    MemTempAllocator tmpAlloc;
    ini_t* ini = ini_create(&tmpAlloc);
    
    for (SettingsCustomCallbacks* callbacks : gSettings.customCallbacks) {
        for (uint32 cId = 0; cId < callbacks->GetCategoryCount(); cId++) {
            Array<SettingsKeyValue> items(&tmpAlloc);
            const char* catName = callbacks->GetCategory(cId);
            int sectionId = ini_section_add(ini, catName, Str::Len(catName));
            
            callbacks->SaveCategory(cId, items);
            
            for (SettingsKeyValue& item : items) {
                if (item.value.Length())
                    ini_property_add(ini, sectionId, item.key.CStr(), item.key.Length(), item.value.CStr(), item.value.Length());
            }

            items.Free();
        }
    }

    if (gSettings.keyValuePairs.Count()) {
        int sectionId = ini_section_add(ini, SETTINGS_NONE_PREDEFINED, Str::Len(SETTINGS_NONE_PREDEFINED));
        
        for (SettingsKeyValue& item : gSettings.keyValuePairs) {
            if (item.value.Length())
                ini_property_add(ini, sectionId, item.key.CStr(), item.key.Length(), item.value.CStr(), item.value.Length());
        }
    }

    int size = ini_save(ini, nullptr, 0);
    if (size > 0) {
        char* data = tmpAlloc.MallocTyped<char>(size);
        ini_save(ini, data, size);

        while (size && data[size-1] == 0)
            --size;
    
        File f;
        if (f.Open(iniFilepath, FileOpenFlags::Write)) {
            f.Write(data, size);
            f.Close();
        }
    }

    ini_destroy(ini);
}

bool Settings::InitializeFromCommandLine(int argc, char* argv[])
{
    sargs_state* args = sargs_create(sargs_desc {
        .argc = argc,
        .argv = argv
    });

    if (sargs_num_args(args) > 0)
        Debug::PrintLine("Loading settings from CommandLine:");

    for (int i = 0; i < sargs_num_args(args); i++) {
        const char* key = sargs_key_at(args, i);
        const char* value = sargs_value_at(args, i);

        if (key[0] != '-')
            continue;
        ++key;

        for (uint32 c = 0; c < gSettings.customCallbacks.Count(); c++) {
            SettingsCustomCallbacks* callbacks = gSettings.customCallbacks[c];

            uint32 foundCatId = UINT32_MAX;
            uint32 catLen = 0;
            for (uint32 catId = 0, catIdCount = callbacks->GetCategoryCount(); catId < catIdCount; catId++) {
                const char* cat = callbacks->GetCategory(catId);
                catLen = Str::Len(cat);
                if (Str::IsEqualNoCaseCount(key, cat, catLen)) {
                    foundCatId = catId;
                    break;
                }
            }
    
            bool predefined = foundCatId != UINT32_MAX ? callbacks->ParseSetting(foundCatId, key + catLen, value) : false;

            if (!predefined)
                SetValue(key, value);

            Debug::PrintLineFmt("\t%d) %s%s = %s", i+1, key, !predefined ? "(*)" : "", value);
        }

    }

    sargs_destroy(args);
    return true;
}

void Settings::SetValue(const char* key, const char* value)
{
    if (value[0] == 0)
        return;

    uint32 index = gSettings.keyValuePairs.FindIf([key](const SettingsKeyValue& keyval) {
        return keyval.key.IsEqual(key);
    });

    if (index != UINT32_MAX)
        gSettings.keyValuePairs[index].value = value;
    else
        gSettings.keyValuePairs.Push(SettingsKeyValue {.key = key, .value = value});
}

const char* Settings::GetValue(const char* key, const char* defaultValue)
{
    uint32 index = gSettings.keyValuePairs.FindIf([key](const SettingsKeyValue& keyval) {
        return keyval.key.IsEqual(key);
    });
    
    return index != UINT32_MAX ? gSettings.keyValuePairs[index].value.CStr() : defaultValue;
}

void Settings::Release()
{
    gSettings.keyValuePairs.Free();
}


#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#if PLATFORM_POSIX
#include <strings.h>
#endif

#define STB_SPRINTF_IMPLEMENTATION
PRAGMA_DIAGNOSTIC_PUSH()
PRAGMA_DIAGNOSTIC_IGNORED_CLANG_GCC("-Wunused-function")
PRAGMA_DIAGNOSTIC_IGNORED_CLANG_GCC("-Wunused-parameter")
PRAGMA_DIAGNOSTIC_IGNORED_CLANG_GCC("-Wsign-compare")
PRAGMA_DIAGNOSTIC_IGNORED_CLANG_GCC("-Wstrict-aliasing")
PRAGMA_DIAGNOSTIC_IGNORED_CLANG_GCC("-Wconditional-uninitialized")
//----------------------------------------------------------------------------------------------------------------------
// External/stb/stb_sprintf.h


#ifndef STB_SPRINTF_H_INCLUDE
#define STB_SPRINTF_H_INCLUDE

/*
Single file sprintf replacement.

Originally written by Jeff Roberts at RAD Game Tools - 2015/10/20.
Hereby placed in public domain.

This is a full sprintf replacement that supports everything that
the C runtime sprintfs support, including float/double, 64-bit integers,
hex floats, field parameters (%*.*d stuff), length reads backs, etc.

Why would you need this if sprintf already exists?  Well, first off,
it's *much* faster (see below). It's also much smaller than the CRT
versions code-space-wise. We've also added some simple improvements
that are super handy (commas in thousands, callbacks at buffer full,
for example). Finally, the format strings for MSVC and GCC differ
for 64-bit integers (among other small things), so this lets you use
the same format strings in cross platform code.

It uses the standard single file trick of being both the header file
and the source itself. If you just include it normally, you just get
the header file function definitions. To get the code, you include
it from a C or C++ file and define STB_SPRINTF_IMPLEMENTATION first.

It only uses va_args macros from the C runtime to do it's work. It
does cast doubles to S64s and shifts and divides U64s, which does
drag in CRT code on most platforms.

It compiles to roughly 8K with float support, and 4K without.
As a comparison, when using MSVC static libs, calling sprintf drags
in 16K.

API:
====
int stbsp_sprintf( char * buf, char const * fmt, ... )
int stbsp_snprintf( char * buf, int count, char const * fmt, ... )
  Convert an arg list into a buffer.  stbsp_snprintf always returns
  a zero-terminated string (unlike regular snprintf).

int stbsp_vsprintf( char * buf, char const * fmt, va_list va )
int stbsp_vsnprintf( char * buf, int count, char const * fmt, va_list va )
  Convert a va_list arg list into a buffer.  stbsp_vsnprintf always returns
  a zero-terminated string (unlike regular snprintf).

int stbsp_vsprintfcb( STBSP_SPRINTFCB * callback, void * user, char * buf, char const * fmt, va_list va )
    typedef char * STBSP_SPRINTFCB( char const * buf, void * user, int len );
  Convert into a buffer, calling back every STB_SPRINTF_MIN chars.
  Your callback can then copy the chars out, print them or whatever.
  This function is actually the workhorse for everything else.
  The buffer you pass in must hold at least STB_SPRINTF_MIN characters.

void stbsp_set_separators( char comma, char period )
  Set the comma and period characters to use.

FLOATS/DOUBLES:
===============
This code uses a internal float->ascii conversion method that uses
doubles with error correction (double-doubles, for ~105 bits of
precision).  This conversion is round-trip perfect - that is, an atof
of the values output here will give you the bit-exact double back.

One difference is that our insignificant digits will be different than
with MSVC or GCC (but they don't match each other either).  We also
don't attempt to find the minimum length matching float (pre-MSVC15
doesn't either).

If you don't need float or doubles at all, define STB_SPRINTF_NOFLOAT
and you'll save 4K of code space.

64-BIT INTS:
============
This library also supports 64-bit integers and you can use MSVC style or
GCC style indicators (%I64d or %lld).  It supports the C99 specifiers
for size_t and ptr_diff_t (%jd %zd) as well.

EXTRAS:
=======
Like some GCCs, for integers and floats, you can use a ' (single quote)
specifier and commas will be inserted on the thousands: "%'d" on 12345
would print 12,345.

For integers and floats, you can use a "$" specifier and the number
will be converted to float and then divided to get kilo, mega, giga or
tera and then printed, so "%$d" 1000 is "1.0 k", "%$.2d" 2536000 is
"2.53 M", etc. For byte values, use two $:s, like "%$$d" to turn
2536000 to "2.42 Mi". If you prefer JEDEC suffixes to SI ones, use three
$:s: "%$$$d" -> "2.42 M". To remove the space between the number and the
suffix, add "_" specifier: "%_$d" -> "2.53M".

In addition to octal and hexadecimal conversions, you can print
integers in binary: "%b" for 256 would print 100.

PERFORMANCE vs MSVC 2008 32-/64-bit (GCC is even slower than MSVC):
===================================================================
"%d" across all 32-bit ints (4.8x/4.0x faster than 32-/64-bit MSVC)
"%24d" across all 32-bit ints (4.5x/4.2x faster)
"%x" across all 32-bit ints (4.5x/3.8x faster)
"%08x" across all 32-bit ints (4.3x/3.8x faster)
"%f" across e-10 to e+10 floats (7.3x/6.0x faster)
"%e" across e-10 to e+10 floats (8.1x/6.0x faster)
"%g" across e-10 to e+10 floats (10.0x/7.1x faster)
"%f" for values near e-300 (7.9x/6.5x faster)
"%f" for values near e+300 (10.0x/9.1x faster)
"%e" for values near e-300 (10.1x/7.0x faster)
"%e" for values near e+300 (9.2x/6.0x faster)
"%.320f" for values near e-300 (12.6x/11.2x faster)
"%a" for random values (8.6x/4.3x faster)
"%I64d" for 64-bits with 32-bit values (4.8x/3.4x faster)
"%I64d" for 64-bits > 32-bit values (4.9x/5.5x faster)
"%s%s%s" for 64 char strings (7.1x/7.3x faster)
"...512 char string..." ( 35.0x/32.5x faster!)
*/

#if defined(__clang__)
 #if defined(__has_feature) && defined(__has_attribute)
  #if __has_feature(address_sanitizer)
   #if __has_attribute(__no_sanitize__)
    #define STBSP__ASAN __attribute__((__no_sanitize__("address")))
   #elif __has_attribute(__no_sanitize_address__)
    #define STBSP__ASAN __attribute__((__no_sanitize_address__))
   #elif __has_attribute(__no_address_safety_analysis__)
    #define STBSP__ASAN __attribute__((__no_address_safety_analysis__))
   #endif
  #endif
 #endif
#elif defined(__GNUC__) && (__GNUC__ >= 5 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 8))
 #if defined(__SANITIZE_ADDRESS__) && __SANITIZE_ADDRESS__
  #define STBSP__ASAN __attribute__((__no_sanitize_address__))
 #endif
#elif defined(_MSC_VER) && _MSC_VER >= 1928
 #if defined(__SANITIZE_ADDRESS__)
  #define STBSP__ASAN __declspec(no_sanitize_address)
 #endif
#endif

#ifndef STBSP__ASAN
#define STBSP__ASAN
#endif

#ifdef STB_SPRINTF_STATIC
#define STBSP__PUBLICDEC static
#define STBSP__PUBLICDEF static STBSP__ASAN
#else
#ifdef __cplusplus
#define STBSP__PUBLICDEC extern "C" STBSP__ASAN
#define STBSP__PUBLICDEF extern "C" STBSP__ASAN
#else
#define STBSP__PUBLICDEC extern
#define STBSP__PUBLICDEF STBSP__ASAN
#endif
#endif

#if defined(__has_attribute)
 #if __has_attribute(format)
   #define STBSP__ATTRIBUTE_FORMAT(fmt,va) __attribute__((format(printf,fmt,va)))
 #endif
#endif

#ifndef STBSP__ATTRIBUTE_FORMAT
#define STBSP__ATTRIBUTE_FORMAT(fmt,va)
#endif

#ifdef _MSC_VER
#define STBSP__NOTUSED(v)  (void)(v)
#else
#define STBSP__NOTUSED(v)  (void)sizeof(v)
#endif

#include <stdarg.h> // for va_arg(), va_list()
#include <stddef.h> // size_t, ptrdiff_t

#ifndef STB_SPRINTF_MIN
#define STB_SPRINTF_MIN 512 // how many characters per callback
#endif
typedef char *STBSP_SPRINTFCB(const char *buf, void *user, int len);

#ifndef STB_SPRINTF_DECORATE
#define STB_SPRINTF_DECORATE(name) stbsp_##name // define this before including if you want to change the names
#endif

STBSP__PUBLICDEC int STB_SPRINTF_DECORATE(vsprintf)(char *buf, char const *fmt, va_list va);
STBSP__PUBLICDEC int STB_SPRINTF_DECORATE(vsnprintf)(char *buf, int count, char const *fmt, va_list va);
STBSP__PUBLICDEC int STB_SPRINTF_DECORATE(sprintf)(char *buf, char const *fmt, ...) STBSP__ATTRIBUTE_FORMAT(2,3);
STBSP__PUBLICDEC int STB_SPRINTF_DECORATE(snprintf)(char *buf, int count, char const *fmt, ...) STBSP__ATTRIBUTE_FORMAT(3,4);

STBSP__PUBLICDEC int STB_SPRINTF_DECORATE(vsprintfcb)(STBSP_SPRINTFCB *callback, void *user, char *buf, char const *fmt, va_list va);
STBSP__PUBLICDEC void STB_SPRINTF_DECORATE(set_separators)(char comma, char period);

#endif // STB_SPRINTF_H_INCLUDE

#ifdef STB_SPRINTF_IMPLEMENTATION

#define stbsp__uint32 unsigned int
#define stbsp__int32 signed int

#ifdef _MSC_VER
#define stbsp__uint64 unsigned __int64
#define stbsp__int64 signed __int64
#else
#define stbsp__uint64 unsigned long long
#define stbsp__int64 signed long long
#endif
#define stbsp__uint16 unsigned short

#ifndef stbsp__uintptr
#if defined(__ppc64__) || defined(__powerpc64__) || defined(__aarch64__) || defined(_M_X64) || defined(__x86_64__) || defined(__x86_64) || defined(__s390x__)
#define stbsp__uintptr stbsp__uint64
#else
#define stbsp__uintptr stbsp__uint32
#endif
#endif

#ifndef STB_SPRINTF_MSVC_MODE // used for MSVC2013 and earlier (MSVC2015 matches GCC)
#if defined(_MSC_VER) && (_MSC_VER < 1900)
#define STB_SPRINTF_MSVC_MODE
#endif
#endif

#ifdef STB_SPRINTF_NOUNALIGNED // define this before inclusion to force stbsp_sprintf to always use aligned accesses
#define STBSP__UNALIGNED(code)
#else
#define STBSP__UNALIGNED(code) code
#endif

#ifndef STB_SPRINTF_NOFLOAT
static stbsp__int32 stbsp__real_to_str(char const **start, stbsp__uint32 *len, char *out, stbsp__int32 *decimal_pos, double value, stbsp__uint32 frac_digits);
static stbsp__int32 stbsp__real_to_parts(stbsp__int64 *bits, stbsp__int32 *expo, double value);
#define STBSP__SPECIAL 0x7000
#endif

static char stbsp__period = '.';
static char stbsp__comma = ',';
static struct
{
   short temp; // force next field to be 2-byte aligned
   char pair[201];
} stbsp__digitpair =
{
  0,
   "00010203040506070809101112131415161718192021222324"
   "25262728293031323334353637383940414243444546474849"
   "50515253545556575859606162636465666768697071727374"
   "75767778798081828384858687888990919293949596979899"
};

STBSP__PUBLICDEF void STB_SPRINTF_DECORATE(set_separators)(char pcomma, char pperiod)
{
   stbsp__period = pperiod;
   stbsp__comma = pcomma;
}

#define STBSP__LEFTJUST 1
#define STBSP__LEADINGPLUS 2
#define STBSP__LEADINGSPACE 4
#define STBSP__LEADING_0X 8
#define STBSP__LEADINGZERO 16
#define STBSP__INTMAX 32
#define STBSP__TRIPLET_COMMA 64
#define STBSP__NEGATIVE 128
#define STBSP__METRIC_SUFFIX 256
#define STBSP__HALFWIDTH 512
#define STBSP__METRIC_NOSPACE 1024
#define STBSP__METRIC_1024 2048
#define STBSP__METRIC_JEDEC 4096

static void stbsp__lead_sign(stbsp__uint32 fl, char *sign)
{
   sign[0] = 0;
   if (fl & STBSP__NEGATIVE) {
      sign[0] = 1;
      sign[1] = '-';
   } else if (fl & STBSP__LEADINGSPACE) {
      sign[0] = 1;
      sign[1] = ' ';
   } else if (fl & STBSP__LEADINGPLUS) {
      sign[0] = 1;
      sign[1] = '+';
   }
}

static STBSP__ASAN stbsp__uint32 stbsp__strlen_limited(char const *s, stbsp__uint32 limit)
{
   char const * sn = s;

   for (;;) {
      if (((stbsp__uintptr)sn & 3) == 0)
         break;

      if (!limit || *sn == 0)
         return (stbsp__uint32)(sn - s);

      ++sn;
      --limit;
   }

   while (limit >= 4) {
      stbsp__uint32 v = *(stbsp__uint32 *)sn;
      if ((v - 0x01010101) & (~v) & 0x80808080UL)
         break;

      sn += 4;
      limit -= 4;
   }

   while (limit && *sn) {
      ++sn;
      --limit;
   }

   return (stbsp__uint32)(sn - s);
}

STBSP__PUBLICDEF int STB_SPRINTF_DECORATE(vsprintfcb)(STBSP_SPRINTFCB *callback, void *user, char *buf, char const *fmt, va_list va)
{
   static char hex[] = "0123456789abcdefxp";
   static char hexu[] = "0123456789ABCDEFXP";
   char *bf;
   char const *f;
   int tlen = 0;

   bf = buf;
   f = fmt;
   for (;;) {
      stbsp__int32 fw, pr, tz;
      stbsp__uint32 fl;

      #define stbsp__chk_cb_bufL(bytes)                        \
         {                                                     \
            int len = (int)(bf - buf);                         \
            if ((len + (bytes)) >= STB_SPRINTF_MIN) {          \
               tlen += len;                                    \
               if (0 == (bf = buf = callback(buf, user, len))) \
                  goto done;                                   \
            }                                                  \
         }
      #define stbsp__chk_cb_buf(bytes)    \
         {                                \
            if (callback) {               \
               stbsp__chk_cb_bufL(bytes); \
            }                             \
         }
      #define stbsp__flush_cb()                      \
         {                                           \
            stbsp__chk_cb_bufL(STB_SPRINTF_MIN - 1); \
         } // flush if there is even one byte in the buffer
      #define stbsp__cb_buf_clamp(cl, v)                \
         cl = v;                                        \
         if (callback) {                                \
            int lg = STB_SPRINTF_MIN - (int)(bf - buf); \
            if (cl > lg)                                \
               cl = lg;                                 \
         }

      for (;;) {
         while (((stbsp__uintptr)f) & 3) {
         schk1:
            if (f[0] == '%')
               goto scandd;
         schk2:
            if (f[0] == 0)
               goto endfmt;
            stbsp__chk_cb_buf(1);
            *bf++ = f[0];
            ++f;
         }
         for (;;) {
            stbsp__uint32 v, c;
            v = *(stbsp__uint32 *)f;
            c = (~v) & 0x80808080;
            if (((v ^ 0x25252525) - 0x01010101) & c)
               goto schk1;
            if ((v - 0x01010101) & c)
               goto schk2;
            if (callback)
               if ((STB_SPRINTF_MIN - (int)(bf - buf)) < 4)
                  goto schk1;
            #ifdef STB_SPRINTF_NOUNALIGNED
                if(((stbsp__uintptr)bf) & 3) {
                    bf[0] = f[0];
                    bf[1] = f[1];
                    bf[2] = f[2];
                    bf[3] = f[3];
                } else
            #endif
            {
                *(stbsp__uint32 *)bf = v;
            }
            bf += 4;
            f += 4;
         }
      }
   scandd:

      ++f;

      fw = 0;
      pr = -1;
      fl = 0;
      tz = 0;

      for (;;) {
         switch (f[0]) {
         case '-':
            fl |= STBSP__LEFTJUST;
            ++f;
            continue;
         case '+':
            fl |= STBSP__LEADINGPLUS;
            ++f;
            continue;
         case ' ':
            fl |= STBSP__LEADINGSPACE;
            ++f;
            continue;
         case '#':
            fl |= STBSP__LEADING_0X;
            ++f;
            continue;
         case '\'':
            fl |= STBSP__TRIPLET_COMMA;
            ++f;
            continue;
         case '$':
            if (fl & STBSP__METRIC_SUFFIX) {
               if (fl & STBSP__METRIC_1024) {
                  fl |= STBSP__METRIC_JEDEC;
               } else {
                  fl |= STBSP__METRIC_1024;
               }
            } else {
               fl |= STBSP__METRIC_SUFFIX;
            }
            ++f;
            continue;
         case '_':
            fl |= STBSP__METRIC_NOSPACE;
            ++f;
            continue;
         case '0':
            fl |= STBSP__LEADINGZERO;
            ++f;
            goto flags_done;
         default: goto flags_done;
         }
      }
   flags_done:

      if (f[0] == '*') {
         fw = va_arg(va, stbsp__uint32);
         ++f;
      } else {
         while ((f[0] >= '0') && (f[0] <= '9')) {
            fw = fw * 10 + f[0] - '0';
            f++;
         }
      }
      if (f[0] == '.') {
         ++f;
         if (f[0] == '*') {
            pr = va_arg(va, stbsp__uint32);
            ++f;
         } else {
            pr = 0;
            while ((f[0] >= '0') && (f[0] <= '9')) {
               pr = pr * 10 + f[0] - '0';
               f++;
            }
         }
      }

      switch (f[0]) {
      case 'h':
         fl |= STBSP__HALFWIDTH;
         ++f;
         if (f[0] == 'h')
            ++f;  // QUARTERWIDTH
         break;
      case 'l':
         fl |= ((sizeof(long) == 8) ? STBSP__INTMAX : 0);
         ++f;
         if (f[0] == 'l') {
            fl |= STBSP__INTMAX;
            ++f;
         }
         break;
      case 'j':
         fl |= (sizeof(size_t) == 8) ? STBSP__INTMAX : 0;
         ++f;
         break;
      case 'z':
         fl |= (sizeof(ptrdiff_t) == 8) ? STBSP__INTMAX : 0;
         ++f;
         break;
      case 't':
         fl |= (sizeof(ptrdiff_t) == 8) ? STBSP__INTMAX : 0;
         ++f;
         break;
      case 'I':
         if ((f[1] == '6') && (f[2] == '4')) {
            fl |= STBSP__INTMAX;
            f += 3;
         } else if ((f[1] == '3') && (f[2] == '2')) {
            f += 3;
         } else {
            fl |= ((sizeof(void *) == 8) ? STBSP__INTMAX : 0);
            ++f;
         }
         break;
      default: break;
      }

      switch (f[0]) {
         #define STBSP__NUMSZ 512 // big enough for e308 (with commas) or e-307
         char num[STBSP__NUMSZ];
         char lead[8];
         char tail[8];
         char *s;
         char const *h;
         stbsp__uint32 l, n, cs;
         stbsp__uint64 n64;
#ifndef STB_SPRINTF_NOFLOAT
         double fv;
#endif
         stbsp__int32 dp;
         char const *sn;

      case 's':
         s = va_arg(va, char *);
         if (s == 0)
            s = (char *)"null";
         l = stbsp__strlen_limited(s, (pr >= 0) ? pr : ~0u);
         lead[0] = 0;
         tail[0] = 0;
         pr = 0;
         dp = 0;
         cs = 0;
         goto scopy;

      case 'c': // char
         s = num + STBSP__NUMSZ - 1;
         *s = (char)va_arg(va, int);
         l = 1;
         lead[0] = 0;
         tail[0] = 0;
         pr = 0;
         dp = 0;
         cs = 0;
         goto scopy;

      case 'n': // weird write-bytes specifier
      {
         int *d = va_arg(va, int *);
         *d = tlen + (int)(bf - buf);
      } break;

#ifdef STB_SPRINTF_NOFLOAT
      case 'A':              // float
      case 'a':              // hex float
      case 'G':              // float
      case 'g':              // float
      case 'E':              // float
      case 'e':              // float
      case 'f':              // float
         va_arg(va, double); // eat it
         s = (char *)"No float";
         l = 8;
         lead[0] = 0;
         tail[0] = 0;
         pr = 0;
         cs = 0;
         STBSP__NOTUSED(dp);
         goto scopy;
#else
      case 'A': // hex float
      case 'a': // hex float
         h = (f[0] == 'A') ? hexu : hex;
         fv = va_arg(va, double);
         if (pr == -1)
            pr = 6; // default is 6
         if (stbsp__real_to_parts((stbsp__int64 *)&n64, &dp, fv))
            fl |= STBSP__NEGATIVE;

         s = num + 64;

         stbsp__lead_sign(fl, lead);

         if (dp == -1023)
            dp = (n64) ? -1022 : 0;
         else
            n64 |= (((stbsp__uint64)1) << 52);
         n64 <<= (64 - 56);
         if (pr < 15)
            n64 += ((((stbsp__uint64)8) << 56) >> (pr * 4));

#ifdef STB_SPRINTF_MSVC_MODE
         *s++ = '0';
         *s++ = 'x';
#else
         lead[1 + lead[0]] = '0';
         lead[2 + lead[0]] = 'x';
         lead[0] += 2;
#endif
         *s++ = h[(n64 >> 60) & 15];
         n64 <<= 4;
         if (pr)
            *s++ = stbsp__period;
         sn = s;

         n = pr;
         if (n > 13)
            n = 13;
         if (pr > (stbsp__int32)n)
            tz = pr - n;
         pr = 0;
         while (n--) {
            *s++ = h[(n64 >> 60) & 15];
            n64 <<= 4;
         }

         tail[1] = h[17];
         if (dp < 0) {
            tail[2] = '-';
            dp = -dp;
         } else
            tail[2] = '+';
         n = (dp >= 1000) ? 6 : ((dp >= 100) ? 5 : ((dp >= 10) ? 4 : 3));
         tail[0] = (char)n;
         for (;;) {
            tail[n] = '0' + dp % 10;
            if (n <= 3)
               break;
            --n;
            dp /= 10;
         }

         dp = (int)(s - sn);
         l = (int)(s - (num + 64));
         s = num + 64;
         cs = 1 + (3 << 24);
         goto scopy;

      case 'G': // float
      case 'g': // float
         h = (f[0] == 'G') ? hexu : hex;
         fv = va_arg(va, double);
         if (pr == -1)
            pr = 6;
         else if (pr == 0)
            pr = 1; // default is 6
         if (stbsp__real_to_str(&sn, &l, num, &dp, fv, (pr - 1) | 0x80000000))
            fl |= STBSP__NEGATIVE;

         n = pr;
         if (l > (stbsp__uint32)pr)
            l = pr;
         while ((l > 1) && (pr) && (sn[l - 1] == '0')) {
            --pr;
            --l;
         }

         if ((dp <= -4) || (dp > (stbsp__int32)n)) {
            if (pr > (stbsp__int32)l)
               pr = l - 1;
            else if (pr)
               --pr; // when using %e, there is one digit before the decimal
            goto doexpfromg;
         }
         if (dp > 0) {
            pr = (dp < (stbsp__int32)l) ? l - dp : 0;
         } else {
            pr = -dp + ((pr > (stbsp__int32)l) ? (stbsp__int32) l : pr);
         }
         goto dofloatfromg;

      case 'E': // float
      case 'e': // float
         h = (f[0] == 'E') ? hexu : hex;
         fv = va_arg(va, double);
         if (pr == -1)
            pr = 6; // default is 6
         if (stbsp__real_to_str(&sn, &l, num, &dp, fv, pr | 0x80000000))
            fl |= STBSP__NEGATIVE;
      doexpfromg:
         tail[0] = 0;
         stbsp__lead_sign(fl, lead);
         if (dp == STBSP__SPECIAL) {
            s = (char *)sn;
            cs = 0;
            pr = 0;
            goto scopy;
         }
         s = num + 64;
         *s++ = sn[0];

         if (pr)
            *s++ = stbsp__period;

         if ((l - 1) > (stbsp__uint32)pr)
            l = pr + 1;
         for (n = 1; n < l; n++)
            *s++ = sn[n];
         tz = pr - (l - 1);
         pr = 0;
         tail[1] = h[0xe];
         dp -= 1;
         if (dp < 0) {
            tail[2] = '-';
            dp = -dp;
         } else
            tail[2] = '+';
#ifdef STB_SPRINTF_MSVC_MODE
         n = 5;
#else
         n = (dp >= 100) ? 5 : 4;
#endif
         tail[0] = (char)n;
         for (;;) {
            tail[n] = '0' + dp % 10;
            if (n <= 3)
               break;
            --n;
            dp /= 10;
         }
         cs = 1 + (3 << 24); // how many tens
         goto flt_lead;

      case 'f': // float
         fv = va_arg(va, double);
      doafloat:
         if (fl & STBSP__METRIC_SUFFIX) {
            double divisor;
            divisor = 1000.0f;
            if (fl & STBSP__METRIC_1024)
               divisor = 1024.0;
            while (fl < 0x4000000) {
               if ((fv < divisor) && (fv > -divisor))
                  break;
               fv /= divisor;
               fl += 0x1000000;
            }
         }
         if (pr == -1)
            pr = 6; // default is 6
         if (stbsp__real_to_str(&sn, &l, num, &dp, fv, pr))
            fl |= STBSP__NEGATIVE;
      dofloatfromg:
         tail[0] = 0;
         stbsp__lead_sign(fl, lead);
         if (dp == STBSP__SPECIAL) {
            s = (char *)sn;
            cs = 0;
            pr = 0;
            goto scopy;
         }
         s = num + 64;

         if (dp <= 0) {
            stbsp__int32 i;
            *s++ = '0';
            if (pr)
               *s++ = stbsp__period;
            n = -dp;
            if ((stbsp__int32)n > pr)
               n = pr;
            i = n;
            while (i) {
               if ((((stbsp__uintptr)s) & 3) == 0)
                  break;
               *s++ = '0';
               --i;
            }
            while (i >= 4) {
               *(stbsp__uint32 *)s = 0x30303030;
               s += 4;
               i -= 4;
            }
            while (i) {
               *s++ = '0';
               --i;
            }
            if ((stbsp__int32)(l + n) > pr)
               l = pr - n;
            i = l;
            while (i) {
               *s++ = *sn++;
               --i;
            }
            tz = pr - (n + l);
            cs = 1 + (3 << 24); // how many tens did we write (for commas below)
         } else {
            cs = (fl & STBSP__TRIPLET_COMMA) ? ((600 - (stbsp__uint32)dp) % 3) : 0;
            if ((stbsp__uint32)dp >= l) {
               n = 0;
               for (;;) {
                  if ((fl & STBSP__TRIPLET_COMMA) && (++cs == 4)) {
                     cs = 0;
                     *s++ = stbsp__comma;
                  } else {
                     *s++ = sn[n];
                     ++n;
                     if (n >= l)
                        break;
                  }
               }
               if (n < (stbsp__uint32)dp) {
                  n = dp - n;
                  if ((fl & STBSP__TRIPLET_COMMA) == 0) {
                     while (n) {
                        if ((((stbsp__uintptr)s) & 3) == 0)
                           break;
                        *s++ = '0';
                        --n;
                     }
                     while (n >= 4) {
                        *(stbsp__uint32 *)s = 0x30303030;
                        s += 4;
                        n -= 4;
                     }
                  }
                  while (n) {
                     if ((fl & STBSP__TRIPLET_COMMA) && (++cs == 4)) {
                        cs = 0;
                        *s++ = stbsp__comma;
                     } else {
                        *s++ = '0';
                        --n;
                     }
                  }
               }
               cs = (int)(s - (num + 64)) + (3 << 24); // cs is how many tens
               if (pr) {
                  *s++ = stbsp__period;
                  tz = pr;
               }
            } else {
               n = 0;
               for (;;) {
                  if ((fl & STBSP__TRIPLET_COMMA) && (++cs == 4)) {
                     cs = 0;
                     *s++ = stbsp__comma;
                  } else {
                     *s++ = sn[n];
                     ++n;
                     if (n >= (stbsp__uint32)dp)
                        break;
                  }
               }
               cs = (int)(s - (num + 64)) + (3 << 24); // cs is how many tens
               if (pr)
                  *s++ = stbsp__period;
               if ((l - dp) > (stbsp__uint32)pr)
                  l = pr + dp;
               while (n < l) {
                  *s++ = sn[n];
                  ++n;
               }
               tz = pr - (l - dp);
            }
         }
         pr = 0;

         if (fl & STBSP__METRIC_SUFFIX) {
            char idx;
            idx = 1;
            if (fl & STBSP__METRIC_NOSPACE)
               idx = 0;
            tail[0] = idx;
            tail[1] = ' ';
            {
               if (fl >> 24) { // SI kilo is 'k', JEDEC and SI kibits are 'K'.
                  if (fl & STBSP__METRIC_1024)
                     tail[idx + 1] = "_KMGT"[fl >> 24];
                  else
                     tail[idx + 1] = "_kMGT"[fl >> 24];
                  idx++;
                  if (fl & STBSP__METRIC_1024 && !(fl & STBSP__METRIC_JEDEC)) {
                     tail[idx + 1] = 'i';
                     idx++;
                  }
                  tail[0] = idx;
               }
            }
         };

      flt_lead:
         l = (stbsp__uint32)(s - (num + 64));
         s = num + 64;
         goto scopy;
#endif

      case 'B': // upper binary
      case 'b': // lower binary
         h = (f[0] == 'B') ? hexu : hex;
         lead[0] = 0;
         if (fl & STBSP__LEADING_0X) {
            lead[0] = 2;
            lead[1] = '0';
            lead[2] = h[0xb];
         }
         l = (8 << 4) | (1 << 8);
         goto radixnum;

      case 'o': // octal
         h = hexu;
         lead[0] = 0;
         if (fl & STBSP__LEADING_0X) {
            lead[0] = 1;
            lead[1] = '0';
         }
         l = (3 << 4) | (3 << 8);
         goto radixnum;

      case 'p': // pointer
         fl |= (sizeof(void *) == 8) ? STBSP__INTMAX : 0;
         pr = sizeof(void *) * 2;
         fl &= ~STBSP__LEADINGZERO; // 'p' only prints the pointer with zeros

      case 'X': // upper hex
      case 'x': // lower hex
         h = (f[0] == 'X') ? hexu : hex;
         l = (4 << 4) | (4 << 8);
         lead[0] = 0;
         if (fl & STBSP__LEADING_0X) {
            lead[0] = 2;
            lead[1] = '0';
            lead[2] = h[16];
         }
      radixnum:
         if (fl & STBSP__INTMAX)
            n64 = va_arg(va, stbsp__uint64);
         else
            n64 = va_arg(va, stbsp__uint32);

         s = num + STBSP__NUMSZ;
         dp = 0;
         tail[0] = 0;
         if (n64 == 0) {
            lead[0] = 0;
            if (pr == 0) {
               l = 0;
               cs = 0;
               goto scopy;
            }
         }
         for (;;) {
            *--s = h[n64 & ((1 << (l >> 8)) - 1)];
            n64 >>= (l >> 8);
            if (!((n64) || ((stbsp__int32)((num + STBSP__NUMSZ) - s) < pr)))
               break;
            if (fl & STBSP__TRIPLET_COMMA) {
               ++l;
               if ((l & 15) == ((l >> 4) & 15)) {
                  l &= ~15;
                  *--s = stbsp__comma;
               }
            }
         };
         cs = (stbsp__uint32)((num + STBSP__NUMSZ) - s) + ((((l >> 4) & 15)) << 24);
         l = (stbsp__uint32)((num + STBSP__NUMSZ) - s);
         goto scopy;

      case 'u': // unsigned
      case 'i':
      case 'd': // integer
         if (fl & STBSP__INTMAX) {
            stbsp__int64 i64 = va_arg(va, stbsp__int64);
            n64 = (stbsp__uint64)i64;
            if ((f[0] != 'u') && (i64 < 0)) {
               n64 = (stbsp__uint64)-i64;
               fl |= STBSP__NEGATIVE;
            }
         } else {
            stbsp__int32 i = va_arg(va, stbsp__int32);
            n64 = (stbsp__uint32)i;
            if ((f[0] != 'u') && (i < 0)) {
               n64 = (stbsp__uint32)-i;
               fl |= STBSP__NEGATIVE;
            }
         }

#ifndef STB_SPRINTF_NOFLOAT
         if (fl & STBSP__METRIC_SUFFIX) {
            if (n64 < 1024)
               pr = 0;
            else if (pr == -1)
               pr = 1;
            fv = (double)(stbsp__int64)n64;
            goto doafloat;
         }
#endif

         s = num + STBSP__NUMSZ;
         l = 0;

         for (;;) {
            char *o = s - 8;
            if (n64 >= 100000000) {
               n = (stbsp__uint32)(n64 % 100000000);
               n64 /= 100000000;
            } else {
               n = (stbsp__uint32)n64;
               n64 = 0;
            }
            if ((fl & STBSP__TRIPLET_COMMA) == 0) {
               do {
                  s -= 2;
                  *(stbsp__uint16 *)s = *(stbsp__uint16 *)&stbsp__digitpair.pair[(n % 100) * 2];
                  n /= 100;
               } while (n);
            }
            while (n) {
               if ((fl & STBSP__TRIPLET_COMMA) && (l++ == 3)) {
                  l = 0;
                  *--s = stbsp__comma;
                  --o;
               } else {
                  *--s = (char)(n % 10) + '0';
                  n /= 10;
               }
            }
            if (n64 == 0) {
               if ((s[0] == '0') && (s != (num + STBSP__NUMSZ)))
                  ++s;
               break;
            }
            while (s != o)
               if ((fl & STBSP__TRIPLET_COMMA) && (l++ == 3)) {
                  l = 0;
                  *--s = stbsp__comma;
                  --o;
               } else {
                  *--s = '0';
               }
         }

         tail[0] = 0;
         stbsp__lead_sign(fl, lead);

         l = (stbsp__uint32)((num + STBSP__NUMSZ) - s);
         if (l == 0) {
            *--s = '0';
            l = 1;
         }
         cs = l + (3 << 24);
         if (pr < 0)
            pr = 0;

      scopy:
         if (pr < (stbsp__int32)l)
            pr = l;
         n = pr + lead[0] + tail[0] + tz;
         if (fw < (stbsp__int32)n)
            fw = n;
         fw -= n;
         pr -= l;

         if ((fl & STBSP__LEFTJUST) == 0) {
            if (fl & STBSP__LEADINGZERO) // if leading zeros, everything is in pr
            {
               pr = (fw > pr) ? fw : pr;
               fw = 0;
            } else {
               fl &= ~STBSP__TRIPLET_COMMA; // if no leading zeros, then no commas
            }
         }

         if (fw + pr) {
            stbsp__int32 i;
            stbsp__uint32 c;

            if ((fl & STBSP__LEFTJUST) == 0)
               while (fw > 0) {
                  stbsp__cb_buf_clamp(i, fw);
                  fw -= i;
                  while (i) {
                     if ((((stbsp__uintptr)bf) & 3) == 0)
                        break;
                     *bf++ = ' ';
                     --i;
                  }
                  while (i >= 4) {
                     *(stbsp__uint32 *)bf = 0x20202020;
                     bf += 4;
                     i -= 4;
                  }
                  while (i) {
                     *bf++ = ' ';
                     --i;
                  }
                  stbsp__chk_cb_buf(1);
               }

            sn = lead + 1;
            while (lead[0]) {
               stbsp__cb_buf_clamp(i, lead[0]);
               lead[0] -= (char)i;
               while (i) {
                  *bf++ = *sn++;
                  --i;
               }
               stbsp__chk_cb_buf(1);
            }

            c = cs >> 24;
            cs &= 0xffffff;
            cs = (fl & STBSP__TRIPLET_COMMA) ? ((stbsp__uint32)(c - ((pr + cs) % (c + 1)))) : 0;
            while (pr > 0) {
               stbsp__cb_buf_clamp(i, pr);
               pr -= i;
               if ((fl & STBSP__TRIPLET_COMMA) == 0) {
                  while (i) {
                     if ((((stbsp__uintptr)bf) & 3) == 0)
                        break;
                     *bf++ = '0';
                     --i;
                  }
                  while (i >= 4) {
                     *(stbsp__uint32 *)bf = 0x30303030;
                     bf += 4;
                     i -= 4;
                  }
               }
               while (i) {
                  if ((fl & STBSP__TRIPLET_COMMA) && (cs++ == c)) {
                     cs = 0;
                     *bf++ = stbsp__comma;
                  } else
                     *bf++ = '0';
                  --i;
               }
               stbsp__chk_cb_buf(1);
            }
         }

         sn = lead + 1;
         while (lead[0]) {
            stbsp__int32 i;
            stbsp__cb_buf_clamp(i, lead[0]);
            lead[0] -= (char)i;
            while (i) {
               *bf++ = *sn++;
               --i;
            }
            stbsp__chk_cb_buf(1);
         }

         n = l;
         while (n) {
            stbsp__int32 i;
            stbsp__cb_buf_clamp(i, n);
            n -= i;
            STBSP__UNALIGNED(while (i >= 4) {
               *(stbsp__uint32 volatile *)bf = *(stbsp__uint32 volatile *)s;
               bf += 4;
               s += 4;
               i -= 4;
            })
            while (i) {
               *bf++ = *s++;
               --i;
            }
            stbsp__chk_cb_buf(1);
         }

         while (tz) {
            stbsp__int32 i;
            stbsp__cb_buf_clamp(i, tz);
            tz -= i;
            while (i) {
               if ((((stbsp__uintptr)bf) & 3) == 0)
                  break;
               *bf++ = '0';
               --i;
            }
            while (i >= 4) {
               *(stbsp__uint32 *)bf = 0x30303030;
               bf += 4;
               i -= 4;
            }
            while (i) {
               *bf++ = '0';
               --i;
            }
            stbsp__chk_cb_buf(1);
         }

         sn = tail + 1;
         while (tail[0]) {
            stbsp__int32 i;
            stbsp__cb_buf_clamp(i, tail[0]);
            tail[0] -= (char)i;
            while (i) {
               *bf++ = *sn++;
               --i;
            }
            stbsp__chk_cb_buf(1);
         }

         if (fl & STBSP__LEFTJUST)
            if (fw > 0) {
               while (fw) {
                  stbsp__int32 i;
                  stbsp__cb_buf_clamp(i, fw);
                  fw -= i;
                  while (i) {
                     if ((((stbsp__uintptr)bf) & 3) == 0)
                        break;
                     *bf++ = ' ';
                     --i;
                  }
                  while (i >= 4) {
                     *(stbsp__uint32 *)bf = 0x20202020;
                     bf += 4;
                     i -= 4;
                  }
                  while (i--)
                     *bf++ = ' ';
                  stbsp__chk_cb_buf(1);
               }
            }
         break;

      default: // unknown, just copy code
         s = num + STBSP__NUMSZ - 1;
         *s = f[0];
         l = 1;
         fw = fl = 0;
         lead[0] = 0;
         tail[0] = 0;
         pr = 0;
         dp = 0;
         cs = 0;
         goto scopy;
      }
      ++f;
   }
endfmt:

   if (!callback)
      *bf = 0;
   else
      stbsp__flush_cb();

done:
   return tlen + (int)(bf - buf);
}

#undef STBSP__LEFTJUST
#undef STBSP__LEADINGPLUS
#undef STBSP__LEADINGSPACE
#undef STBSP__LEADING_0X
#undef STBSP__LEADINGZERO
#undef STBSP__INTMAX
#undef STBSP__TRIPLET_COMMA
#undef STBSP__NEGATIVE
#undef STBSP__METRIC_SUFFIX
#undef STBSP__NUMSZ
#undef stbsp__chk_cb_bufL
#undef stbsp__chk_cb_buf
#undef stbsp__flush_cb
#undef stbsp__cb_buf_clamp


STBSP__PUBLICDEF int STB_SPRINTF_DECORATE(sprintf)(char *buf, char const *fmt, ...)
{
   int result;
   va_list va;
   va_start(va, fmt);
   result = STB_SPRINTF_DECORATE(vsprintfcb)(0, 0, buf, fmt, va);
   va_end(va);
   return result;
}

typedef struct stbsp__context {
   char *buf;
   int count;
   int length;
   char tmp[STB_SPRINTF_MIN];
} stbsp__context;

static char *stbsp__clamp_callback(const char *buf, void *user, int len)
{
   stbsp__context *c = (stbsp__context *)user;
   c->length += len;

   if (len > c->count)
      len = c->count;

   if (len) {
      if (buf != c->buf) {
         const char *s, *se;
         char *d;
         d = c->buf;
         s = buf;
         se = buf + len;
         do {
            *d++ = *s++;
         } while (s < se);
      }
      c->buf += len;
      c->count -= len;
   }

   if (c->count <= 0)
      return c->tmp;
   return (c->count >= STB_SPRINTF_MIN) ? c->buf : c->tmp; // go direct into buffer if you can
}

static char * stbsp__count_clamp_callback( const char * buf, void * user, int len )
{
   stbsp__context * c = (stbsp__context*)user;
   (void) sizeof(buf);

   c->length += len;
   return c->tmp; // go direct into buffer if you can
}

STBSP__PUBLICDEF int STB_SPRINTF_DECORATE( vsnprintf )( char * buf, int count, char const * fmt, va_list va )
{
   stbsp__context c;

   if ( (count == 0) && !buf )
   {
      c.length = 0;

      STB_SPRINTF_DECORATE( vsprintfcb )( stbsp__count_clamp_callback, &c, c.tmp, fmt, va );
   }
   else
   {
      int l;

      c.buf = buf;
      c.count = count;
      c.length = 0;

      STB_SPRINTF_DECORATE( vsprintfcb )( stbsp__clamp_callback, &c, stbsp__clamp_callback(0,&c,0), fmt, va );

      l = (int)( c.buf - buf );
      if ( l >= count ) // should never be greater, only equal (or less) than count
         l = count - 1;
      buf[l] = 0;
   }

   return c.length;
}

STBSP__PUBLICDEF int STB_SPRINTF_DECORATE(snprintf)(char *buf, int count, char const *fmt, ...)
{
   int result;
   va_list va;
   va_start(va, fmt);

   result = STB_SPRINTF_DECORATE(vsnprintf)(buf, count, fmt, va);
   va_end(va);

   return result;
}

STBSP__PUBLICDEF int STB_SPRINTF_DECORATE(vsprintf)(char *buf, char const *fmt, va_list va)
{
   return STB_SPRINTF_DECORATE(vsprintfcb)(0, 0, buf, fmt, va);
}


#ifndef STB_SPRINTF_NOFLOAT

#define STBSP__COPYFP(dest, src)                   \
   {                                               \
      int cn;                                      \
      for (cn = 0; cn < 8; cn++)                   \
         ((char *)&dest)[cn] = ((char *)&src)[cn]; \
   }

static stbsp__int32 stbsp__real_to_parts(stbsp__int64 *bits, stbsp__int32 *expo, double value)
{
   double d;
   stbsp__int64 b = 0;

   d = value;

   STBSP__COPYFP(b, d);

   *bits = b & ((((stbsp__uint64)1) << 52) - 1);
   *expo = (stbsp__int32)(((b >> 52) & 2047) - 1023);

   return (stbsp__int32)((stbsp__uint64) b >> 63);
}

static double const stbsp__bot[23] = {
   1e+000, 1e+001, 1e+002, 1e+003, 1e+004, 1e+005, 1e+006, 1e+007, 1e+008, 1e+009, 1e+010, 1e+011,
   1e+012, 1e+013, 1e+014, 1e+015, 1e+016, 1e+017, 1e+018, 1e+019, 1e+020, 1e+021, 1e+022
};
static double const stbsp__negbot[22] = {
   1e-001, 1e-002, 1e-003, 1e-004, 1e-005, 1e-006, 1e-007, 1e-008, 1e-009, 1e-010, 1e-011,
   1e-012, 1e-013, 1e-014, 1e-015, 1e-016, 1e-017, 1e-018, 1e-019, 1e-020, 1e-021, 1e-022
};
static double const stbsp__negboterr[22] = {
   -5.551115123125783e-018,  -2.0816681711721684e-019, -2.0816681711721686e-020, -4.7921736023859299e-021, -8.1803053914031305e-022, 4.5251888174113741e-023,
   4.5251888174113739e-024,  -2.0922560830128471e-025, -6.2281591457779853e-026, -3.6432197315497743e-027, 6.0503030718060191e-028,  2.0113352370744385e-029,
   -3.0373745563400371e-030, 1.1806906454401013e-032,  -7.7705399876661076e-032, 2.0902213275965398e-033,  -7.1542424054621921e-034, -7.1542424054621926e-035,
   2.4754073164739869e-036,  5.4846728545790429e-037,  9.2462547772103625e-038,  -4.8596774326570872e-039
};
static double const stbsp__top[13] = {
   1e+023, 1e+046, 1e+069, 1e+092, 1e+115, 1e+138, 1e+161, 1e+184, 1e+207, 1e+230, 1e+253, 1e+276, 1e+299
};
static double const stbsp__negtop[13] = {
   1e-023, 1e-046, 1e-069, 1e-092, 1e-115, 1e-138, 1e-161, 1e-184, 1e-207, 1e-230, 1e-253, 1e-276, 1e-299
};
static double const stbsp__toperr[13] = {
   8388608,
   6.8601809640529717e+028,
   -7.253143638152921e+052,
   -4.3377296974619174e+075,
   -1.5559416129466825e+098,
   -3.2841562489204913e+121,
   -3.7745893248228135e+144,
   -1.7356668416969134e+167,
   -3.8893577551088374e+190,
   -9.9566444326005119e+213,
   6.3641293062232429e+236,
   -5.2069140800249813e+259,
   -5.2504760255204387e+282
};
static double const stbsp__negtoperr[13] = {
   3.9565301985100693e-040,  -2.299904345391321e-063,  3.6506201437945798e-086,  1.1875228833981544e-109,
   -5.0644902316928607e-132, -6.7156837247865426e-155, -2.812077463003139e-178,  -5.7778912386589953e-201,
   7.4997100559334532e-224,  -4.6439668915134491e-247, -6.3691100762962136e-270, -9.436808465446358e-293,
   8.0970921678014997e-317
};

#if defined(_MSC_VER) && (_MSC_VER <= 1200)
static stbsp__uint64 const stbsp__powten[20] = {
   1,
   10,
   100,
   1000,
   10000,
   100000,
   1000000,
   10000000,
   100000000,
   1000000000,
   10000000000,
   100000000000,
   1000000000000,
   10000000000000,
   100000000000000,
   1000000000000000,
   10000000000000000,
   100000000000000000,
   1000000000000000000,
   10000000000000000000U
};
#define stbsp__tento19th ((stbsp__uint64)1000000000000000000)
#else
static stbsp__uint64 const stbsp__powten[20] = {
   1,
   10,
   100,
   1000,
   10000,
   100000,
   1000000,
   10000000,
   100000000,
   1000000000,
   10000000000ULL,
   100000000000ULL,
   1000000000000ULL,
   10000000000000ULL,
   100000000000000ULL,
   1000000000000000ULL,
   10000000000000000ULL,
   100000000000000000ULL,
   1000000000000000000ULL,
   10000000000000000000ULL
};
#define stbsp__tento19th (1000000000000000000ULL)
#endif

#define stbsp__ddmulthi(oh, ol, xh, yh)                            \
   {                                                               \
      double ahi = 0, alo, bhi = 0, blo;                           \
      stbsp__int64 bt;                                             \
      oh = xh * yh;                                                \
      STBSP__COPYFP(bt, xh);                                       \
      bt &= ((~(stbsp__uint64)0) << 27);                           \
      STBSP__COPYFP(ahi, bt);                                      \
      alo = xh - ahi;                                              \
      STBSP__COPYFP(bt, yh);                                       \
      bt &= ((~(stbsp__uint64)0) << 27);                           \
      STBSP__COPYFP(bhi, bt);                                      \
      blo = yh - bhi;                                              \
      ol = ((ahi * bhi - oh) + ahi * blo + alo * bhi) + alo * blo; \
   }

#define stbsp__ddtoS64(ob, xh, xl)          \
   {                                        \
      double ahi = 0, alo, vh, t;           \
      ob = (stbsp__int64)xh;                \
      vh = (double)ob;                      \
      ahi = (xh - vh);                      \
      t = (ahi - xh);                       \
      alo = (xh - (ahi - t)) - (vh + t);    \
      ob += (stbsp__int64)(ahi + alo + xl); \
   }

#define stbsp__ddrenorm(oh, ol) \
   {                            \
      double s;                 \
      s = oh + ol;              \
      ol = ol - (s - oh);       \
      oh = s;                   \
   }

#define stbsp__ddmultlo(oh, ol, xh, xl, yh, yl) ol = ol + (xh * yl + xl * yh);

#define stbsp__ddmultlos(oh, ol, xh, yl) ol = ol + (xh * yl);

static void stbsp__raise_to_power10(double *ohi, double *olo, double d, stbsp__int32 power) // power can be -323 to +350
{
   double ph, pl;
   if ((power >= 0) && (power <= 22)) {
      stbsp__ddmulthi(ph, pl, d, stbsp__bot[power]);
   } else {
      stbsp__int32 e, et, eb;
      double p2h, p2l;

      e = power;
      if (power < 0)
         e = -e;
      et = (e * 0x2c9) >> 14; /* %23 */
      if (et > 13)
         et = 13;
      eb = e - (et * 23);

      ph = d;
      pl = 0.0;
      if (power < 0) {
         if (eb) {
            --eb;
            stbsp__ddmulthi(ph, pl, d, stbsp__negbot[eb]);
            stbsp__ddmultlos(ph, pl, d, stbsp__negboterr[eb]);
         }
         if (et) {
            stbsp__ddrenorm(ph, pl);
            --et;
            stbsp__ddmulthi(p2h, p2l, ph, stbsp__negtop[et]);
            stbsp__ddmultlo(p2h, p2l, ph, pl, stbsp__negtop[et], stbsp__negtoperr[et]);
            ph = p2h;
            pl = p2l;
         }
      } else {
         if (eb) {
            e = eb;
            if (eb > 22)
               eb = 22;
            e -= eb;
            stbsp__ddmulthi(ph, pl, d, stbsp__bot[eb]);
            if (e) {
               stbsp__ddrenorm(ph, pl);
               stbsp__ddmulthi(p2h, p2l, ph, stbsp__bot[e]);
               stbsp__ddmultlos(p2h, p2l, stbsp__bot[e], pl);
               ph = p2h;
               pl = p2l;
            }
         }
         if (et) {
            stbsp__ddrenorm(ph, pl);
            --et;
            stbsp__ddmulthi(p2h, p2l, ph, stbsp__top[et]);
            stbsp__ddmultlo(p2h, p2l, ph, pl, stbsp__top[et], stbsp__toperr[et]);
            ph = p2h;
            pl = p2l;
         }
      }
   }
   stbsp__ddrenorm(ph, pl);
   *ohi = ph;
   *olo = pl;
}

static stbsp__int32 stbsp__real_to_str(char const **start, stbsp__uint32 *len, char *out, stbsp__int32 *decimal_pos, double value, stbsp__uint32 frac_digits)
{
   double d;
   stbsp__int64 bits = 0;
   stbsp__int32 expo, e, ng, tens;

   d = value;
   STBSP__COPYFP(bits, d);
   expo = (stbsp__int32)((bits >> 52) & 2047);
   ng = (stbsp__int32)((stbsp__uint64) bits >> 63);
   if (ng)
      d = -d;

   if (expo == 2047) // is nan or inf?
   {
      *start = (bits & ((((stbsp__uint64)1) << 52) - 1)) ? "NaN" : "Inf";
      *decimal_pos = STBSP__SPECIAL;
      *len = 3;
      return ng;
   }

   if (expo == 0) // is zero or denormal
   {
      if (((stbsp__uint64) bits << 1) == 0) // do zero
      {
         *decimal_pos = 1;
         *start = out;
         out[0] = '0';
         *len = 1;
         return ng;
      }
      {
         stbsp__int64 v = ((stbsp__uint64)1) << 51;
         while ((bits & v) == 0) {
            --expo;
            v >>= 1;
         }
      }
   }

   {
      double ph, pl;

      tens = expo - 1023;
      tens = (tens < 0) ? ((tens * 617) / 2048) : (((tens * 1233) / 4096) + 1);

      stbsp__raise_to_power10(&ph, &pl, d, 18 - tens);

      stbsp__ddtoS64(bits, ph, pl);

      if (((stbsp__uint64)bits) >= stbsp__tento19th)
         ++tens;
   }

   frac_digits = (frac_digits & 0x80000000) ? ((frac_digits & 0x7ffffff) + 1) : (tens + frac_digits);
   if ((frac_digits < 24)) {
      stbsp__uint32 dg = 1;
      if ((stbsp__uint64)bits >= stbsp__powten[9])
         dg = 10;
      while ((stbsp__uint64)bits >= stbsp__powten[dg]) {
         ++dg;
         if (dg == 20)
            goto noround;
      }
      if (frac_digits < dg) {
         stbsp__uint64 r;
         e = dg - frac_digits;
         if ((stbsp__uint32)e >= 24)
            goto noround;
         r = stbsp__powten[e];
         bits = bits + (r / 2);
         if ((stbsp__uint64)bits >= stbsp__powten[dg])
            ++tens;
         bits /= r;
      }
   noround:;
   }

   if (bits) {
      stbsp__uint32 n;
      for (;;) {
         if (bits <= 0xffffffff)
            break;
         if (bits % 1000)
            goto donez;
         bits /= 1000;
      }
      n = (stbsp__uint32)bits;
      while ((n % 1000) == 0)
         n /= 1000;
      bits = n;
   donez:;
   }

   out += 64;
   e = 0;
   for (;;) {
      stbsp__uint32 n;
      char *o = out - 8;
      if (bits >= 100000000) {
         n = (stbsp__uint32)(bits % 100000000);
         bits /= 100000000;
      } else {
         n = (stbsp__uint32)bits;
         bits = 0;
      }
      while (n) {
         out -= 2;
         *(stbsp__uint16 *)out = *(stbsp__uint16 *)&stbsp__digitpair.pair[(n % 100) * 2];
         n /= 100;
         e += 2;
      }
      if (bits == 0) {
         if ((e) && (out[0] == '0')) {
            ++out;
            --e;
         }
         break;
      }
      while (out != o) {
         *--out = '0';
         ++e;
      }
   }

   *decimal_pos = tens;
   *start = out;
   *len = e;
   return ng;
}

#undef stbsp__ddmulthi
#undef stbsp__ddrenorm
#undef stbsp__ddmultlo
#undef stbsp__ddmultlos
#undef STBSP__SPECIAL
#undef STBSP__COPYFP

#endif // STB_SPRINTF_NOFLOAT

#undef stbsp__uint16
#undef stbsp__uint32
#undef stbsp__int32
#undef stbsp__uint64
#undef stbsp__int64
#undef STBSP__UNALIGNED

#endif // STB_SPRINTF_IMPLEMENTATION

/*
------------------------------------------------------------------------------
This software is available under 2 licenses -- choose whichever you prefer.
------------------------------------------------------------------------------
ALTERNATIVE A - MIT License
Copyright (c) 2017 Sean Barrett
Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is furnished to do
so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
------------------------------------------------------------------------------
ALTERNATIVE B - Public Domain (www.unlicense.org)
This is free and unencumbered software released into the public domain.
Anyone is free to copy, modify, publish, use, compile, sell, or distribute this
software, either in source code form or as a compiled binary, for any purpose,
commercial or non-commercial, and by any means.
In jurisdictions that recognize copyright laws, the author or authors of this
software dedicate any and all copyright interest in the software to the public
domain. We make this dedication for the benefit of the public at large and to
the detriment of our heirs and successors. We intend this dedication to be an
overt act of relinquishment in perpetuity of all present and future rights to
this software under copyright law.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
------------------------------------------------------------------------------
*/

PRAGMA_DIAGNOSTIC_POP();
#undef STB_SPRINTF_IMPLEMENTATION

#ifdef BUILD_UNITY
    #if PLATFORM_WINDOWS
//----------------------------------------------------------------------------------------------------------------------
// StringUtilWin.cpp


#if PLATFORM_WINDOWS


bool Str::Utf8ToWide(const char* src, wchar_t* dst, size_t dstNumBytes)
{
	ASSERT(src && dst && (dstNumBytes > 1));

	memset(dst, 0, dstNumBytes);
	const int dstChars = (int)(dstNumBytes / sizeof(wchar_t));
	const int dstNeeded = (int)MultiByteToWideChar(CP_UTF8, 0, src, -1, 0, 0);
	if ((dstNeeded > 0) && (dstNeeded <= dstChars)) {
		MultiByteToWideChar(CP_UTF8, 0, src, -1, dst, dstChars);
		return true;
	}
    else {
        return false;
    }
}

bool Str::WideToUtf8(const wchar_t* src, char* dst, size_t dstNumBytes)
{
	ASSERT(src && dst && (dstNumBytes > 1));

	memset(dst, 0, dstNumBytes);
	const int dstChars = (int)dstNumBytes;
    const int dstNeeded = WideCharToMultiByte(CP_UTF8, 0, src, -1, 0, 0, NULL, NULL);
	if ((dstNeeded > 0) && (dstNeeded <= dstChars)) {
		WideCharToMultiByte(CP_UTF8, 0, src, -1, dst, dstChars, NULL, NULL);
		return true;
	}
	else {
		return false;
	}
}

#endif // PLATFORM_WINDOWS

    #endif
#endif


namespace Str
{
    NO_ASAN INLINE uint32 LenCount(const char* str, uint32 _max)
    {
        const char* char_ptr;
        const uintptr* longWordPtr;
        uintptr longword, himagic, lomagic;

        for (char_ptr = str; ((uintptr)char_ptr & (sizeof(longword) - 1)) != 0; ++char_ptr) {
            if (*char_ptr == '\0') {
                uint32 _len = (uint32)(uintptr)(char_ptr - str);
                return (_len > _max) ? _max : _len;
            }
        }

        longWordPtr = (uintptr*)char_ptr;
        himagic = 0x80808080L;
        lomagic = 0x01010101L;
        #if ARCH_64BIT
        /* 64-bit version of the magic.  */
        /* Do the shift in two steps to avoid a warning if long has 32 bits.  */
        himagic = ((himagic << 16) << 16) | himagic;
        lomagic = ((lomagic << 16) << 16) | lomagic;
        #endif

        for (;;) {
            longword = *longWordPtr++;

            if (((longword - lomagic) & ~longword & himagic) != 0) {
                const char* cp = (const char*)(longWordPtr - 1);
                uint32 baseOffset = (uint32)(intptr_t)(cp - str);
                if (baseOffset > _max)
                    return _max;

                if (cp[0] == 0)
                    return Min(_max, baseOffset);
                if (cp[1] == 0)
                    return Min(_max, baseOffset + 1);
                if (cp[2] == 0)
                    return Min(_max, baseOffset + 2);
                if (cp[3] == 0)
                    return Min(_max, baseOffset + 3);
                #if ARCH_64BIT
                if (cp[4] == 0)
                    return Min(_max, baseOffset + 4);
                if (cp[5] == 0)
                    return Min(_max, baseOffset + 5);
                if (cp[6] == 0)
                    return Min(_max, baseOffset + 6);
                if (cp[7] == 0)
                    return Min(_max, baseOffset + 7);
                #endif // ARCH_64BIT
            }
        }

        #if !COMPILER_MSVC
        ASSERT_MSG(0, "Not a null-terminated string");
        return 0;
        #endif
    }
} // Str


uint32 Str::PrintFmt(char* str, uint32 size, const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    uint32 r = Str::PrintFmtArgs(str, size, fmt, args);
    va_end(args);
    return r;
}

uint32 Str::PrintFmtArgs(char* str, uint32 size, const char* fmt, va_list args)
{
    return (uint32)stbsp_vsnprintf(str, (int)size, fmt, args);
}

char* Str::PrintFmtAlloc(MemAllocator* alloc, const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    char* str = Str::PrintFmtAllocArgs(alloc, fmt, args);
    va_end(args);
    return str;
}

uint32 Str::ScanFmt(const char* str, const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
#if PLATFORM_WINDOWS
    uint32 r = vsscanf_s(str, fmt, args);
#else
    uint32 r = vsscanf(str, fmt, args);
#endif 
    va_end(args);
    return r;
}

uint32 Str::ScanFmtArgs(const char* str, const char* fmt, va_list args)
{
#if PLATFORM_WINDOWS
    return vsscanf_s(str, fmt, args);
#else
    return vsscanf  (str, fmt, args);
#endif
}

char* Str::PrintFmtAllocArgs(MemAllocator* alloc, const char* fmt, va_list args)
{
    struct strPrintfContext
    {
        MemAllocator* alloc;
        char* buff;
        int len;
        char tmp[STB_SPRINTF_MIN];
    };

    auto strStbPrintfCallback = [](const char*, void* user, int len)->char*
    {
        strPrintfContext* ctx = reinterpret_cast<strPrintfContext*>(user);
        int len_ = len + 1;    // Reserve one character for null-termination
        ctx->buff = Mem::ReallocTyped<char>(ctx->buff, len_, ctx->alloc);
        memcpy(ctx->buff + ctx->len, ctx->tmp, len);
        ctx->len += len;
        return ctx->tmp;
    };
    
    strPrintfContext ctx;
    ctx.alloc = alloc;
    ctx.buff = nullptr;
    ctx.len = 0;
    stbsp_vsprintfcb(strStbPrintfCallback, &ctx, ctx.tmp, fmt, args);
    ctx.buff[ctx.len] = '\0';
    return ctx.buff;
}

char* Str::Copy(char* RESTRICT dst, uint32 dstSize, const char* RESTRICT src)
{
    ASSERT(dst);
    ASSERT(src);		

    const uint32 len = Str::Len(src);
    const uint32 max = dstSize ? dstSize - 1 : 0;
    const uint32 num = (len < max ? len : max);
    if (num > 0) {
        memcpy(dst, src, num);
    }
    dst[num] = '\0';

    return &dst[num];
}

uint32 Str::Len(const char* str)
{
    const char* char_ptr;
    const uintptr* longWordPtr;
    uintptr longword, himagic, lomagic;

    for (char_ptr = str; ((uintptr)char_ptr & (sizeof(longword) - 1)) != 0; ++char_ptr) {
        if (*char_ptr == '\0')
            return (uint32)(intptr_t)(char_ptr - str);
    }
    longWordPtr = (uintptr*)char_ptr;
    himagic = 0x80808080L;
    lomagic = 0x01010101L;
    #if ARCH_64BIT
    /* 64-bit version of the magic.  */
    /* Do the shift in two steps to avoid a warning if long has 32 bits.  */
    himagic = ((himagic << 16) << 16) | himagic;
    lomagic = ((lomagic << 16) << 16) | lomagic;
    #endif

    for (;;) {
        longword = *longWordPtr++;

        if (((longword - lomagic) & ~longword & himagic) != 0) {
            const char* cp = (const char*)(longWordPtr - 1);

            if (cp[0] == 0)
                return (uint32)(intptr_t)(cp - str);
            if (cp[1] == 0)
                return (uint32)(intptr_t)(cp - str + 1);
            if (cp[2] == 0)
                return (uint32)(intptr_t)(cp - str + 2);
            if (cp[3] == 0)
                return (uint32)(intptr_t)(cp - str + 3);
            #if ARCH_64BIT
            if (cp[4] == 0)
                return (uint32)(intptr_t)(cp - str + 4);
            if (cp[5] == 0)
                return (uint32)(intptr_t)(cp - str + 5);
            if (cp[6] == 0)
                return (uint32)(intptr_t)(cp - str + 6);
            if (cp[7] == 0)
                return (uint32)(intptr_t)(cp - str + 7);
            #endif // ARCH_64BIT
        }
    }

    #if !COMPILER_MSVC
        ASSERT_MSG(0, "Not a null-terminated string");
        return 0;
    #endif
}

char* Str::CopyCount(char* RESTRICT dst, uint32 dstSize, const char* RESTRICT src, uint32 count)
{
    ASSERT(dst);
    ASSERT(src);

    const uint32 len = LenCount(src, count);
    const uint32 max = dstSize ? dstSize - 1 : 0;
    const uint32 num = (len < max ? len : max);
    if (num > 0) 
        memcpy(dst, src, num);
    dst[num] = '\0';

    return &dst[num];
}

char* Str::Concat(char* RESTRICT dst, uint32 dstSize, const char* RESTRICT src)
{
    ASSERT(dst);
    ASSERT(src);

    uint32 len = Str::Len(dst);
    return Str::Copy(dst + len, dstSize - len, src);
}

char* Str::ConcatCount(char* RESTRICT dst, uint32 dstSize, const char* RESTRICT src, uint32 count)
{
    ASSERT(dst);
    ASSERT(src);

    uint32 len = Str::Len(dst);
    return Str::CopyCount(dst + len, dstSize - len, src, count);
}

bool Str::IsEqual(const char* s1, const char* s2)
{
    uint32 alen = Str::Len(s1);
    uint32 blen = Str::Len(s2);
    if (alen != blen)
        return false;

    for (uint32 i = 0; i < alen; i++) {
        if (s1[i] != s2[i])
            return false;
    }
    return true;
}

bool Str::IsEqualNoCase(const char* s1, const char* s2)
{
    uint32 alen = Str::Len(s1);
    uint32 blen = Str::Len(s2);
    if (alen != blen)
        return false;

    for (uint32 i = 0; i < alen; i++) {
        if (Str::ToLower(s1[i]) != Str::ToLower(s2[i]))
            return false;
    }
    return true;    
}

bool Str::IsEqualCount(const char* a, const char* b, uint32 count)
{
    uint32 _alen = Str::Len(a);
    uint32 _blen = Str::Len(b);
    uint32 alen = Min(count, _alen);
    uint32 blen = Min(count, _blen);
    if (alen != blen)
        return false;

    for (uint32 i = 0; i < alen; i++) {
        if (a[i] != b[i])
            return false;
    }
    return true;
}

bool Str::IsEqualNoCaseCount(const char* a, const char* b, uint32 count)
{
    uint32 _alen = Str::Len(a);
    uint32 _blen = Str::Len(b);
    uint32 alen = Min(count, _alen);
    uint32 blen = Min(count, _blen);
    if (alen != blen)
        return false;

    for (uint32 i = 0; i < alen; i++) {
        if (Str::ToLower(a[i]) != Str::ToLower(b[i]))
            return false;
    }
    return true;
}

int Str::Compare(const char* a, const char* b)
{
    return strcmp(a, b);
}

int Str::CompareNoCase(const char* a, const char* b)
{
#if PLATFORM_WINDOWS
    return _stricmp(a, b);
#else
    return strcasecmp(a, b);
#endif
}

uint32 Str::CountMatchingFirstChars(const char* s1, const char* s2)
{
    uint32 count = 0;
    while (true) {
        if (s1[count] == 0 || s2[count] == 0 || s1[count] != s2[count])
            return count;
        count++;
    }
    
    return count;
}

bool Str::StartsWith(const char* str, const char* startsWith)
{
    uint32 len = Str::Len(str);
    uint32 startsWithLen = Str::Len(startsWith);
    if (startsWithLen > len)
        return false;

    return Str::IsEqualCount(str, startsWith, startsWithLen);
}

bool Str::EndsWith(const char* str, const char* endsWith)
{
    uint32 len = Str::Len(str);
    uint32 endsWithLen = Str::Len(endsWith);
    if (endsWithLen > len)
        return false;
    return Str::IsEqual(str + len - endsWithLen, endsWith);   
}

bool Str::IsWhitespace(char ch)
{
    return static_cast<uint32>(ch - 1) < 32 && ((0x80001F00 >> static_cast<uint32>(ch - 1)) & 1) == 1;
}

char Str::ToLower(char ch)
{
    return ch + (Str::IsInRange(ch, 'A', 'Z') ? 0x20 : 0);
}

char* Str::ToLower(char* dst, uint32 dstSize, const char* src)
{
    uint32 offset = 0;
    uint32 dstMax = dstSize - 1;
    while (*src && offset < dstMax) {
        dst[offset++] = Str::ToLower(*src);
        ++src;
    }
    dst[offset] = '\0';
    return dst;
}

char Str::ToUpper(char ch)
{
    return ch - (Str::IsInRange(ch, 'a', 'z') ? 0x20 : 0);
}

char* Str::ToUpper(char* dst, uint32 dstSize, const char* src)
{
    uint32 offset = 0;
    uint32 dstMax = dstSize - 1;
    while (*src && offset < dstMax) {
        dst[offset++] = Str::ToUpper(*src);
        ++src;
    }
    dst[offset] = '\0';
    return dst;
}

char Str::IsInRange(char ch, char from, char to)
{
    return static_cast<uint8>(ch - from) <= static_cast<uint8>(to - from);
}

char Str::IsNumber(char ch)
{
    return Str::IsInRange(ch, '0', '9');
}

char* Str::Trim(char* dst, uint32 dstSize, const char* src)
{
    uint32 len = Min(Str::Len(src), dstSize - 1);
    uint32 startOffset = 0;
    uint32 endOffset = len;
    
    {
        for (uint32 i = 0; i < len; i++) {
            if (Str::IsWhitespace(src[i]))
                startOffset++;
            else
                break;
        }
    }

    if (len) {
        for (uint32 i = len; --i > 0; ) {
            if (!Str::IsWhitespace(src[i]))   {
                endOffset = i + 1;  
                break;
            }
        }
    }

    for (uint32 i = startOffset; i < endOffset; i++) 
        dst[i - startOffset] = src[i];

    dst[endOffset - startOffset] = '\0';
    return dst;
}

char* Str::Trim(char* dst, uint32 dstSize, const char* src, char ch)
{
    uint32 len = Min(Str::Len(src), dstSize - 1);
    uint32 startOffset = 0;
    uint32 endOffset = len;
    
    {
        for (uint32 i = 0; i < len; i++) {
            if (src[i] == ch)
                startOffset++;
            else
                break;
        }
    }

    {
        for (uint32 i = len; --i > 0; ) {
            if (src[i] != ch)   {
                endOffset = i + 1;  
                break;
            }
        }
    }

    for (uint32 i = startOffset; i < endOffset; i++) 
        dst[i - startOffset] = src[i];

    dst[endOffset - startOffset] = '\0';
    return dst;
}

char* Str::RemoveWhitespace(char* dst, uint32 dstSize, const char* src)
{
    uint32 c = 0;
    while (*src) {
        if (!Str::IsWhitespace(*src)) {
            if (c < (dstSize - 1))
                dst[c++] = *src;
            else
                break;
        }
        src++;
    }
    dst[c] = '\0';
    return dst;
}

char* Str::RemoveChar(char* dst, uint32 dstSize, const char* src, char ch)
{
    uint32 c = 0;
    while (*src) {
        if (*src != ch) {
            if (c < (dstSize - 1))
                dst[c++] = *src;
            else
                break;
        }
        src++;
    }
    dst[c] = '\0';
    return dst;
}

const char* Str::FindChar(const char* str, char ch)
{
    const uint8* charPtr;
    uintptr* longwordPtr;
    uintptr longword, magicBits, charmask;
    uint8 c = (uint8)ch;

    for (charPtr = (const uint8*)str;
         ((uintptr)charPtr & (sizeof(longword) - 1)) != 0; ++charPtr) {
        if (*charPtr == c)
            return (const char*)charPtr;
        else if (*charPtr == '\0')
            return nullptr;
    }

    longwordPtr = (uintptr*)charPtr;
    magicBits = (uintptr)-1;
    magicBits = magicBits / 0xff * 0xfe << 1 >> 1 | 1;
    charmask = c | (c << 8);
    charmask |= charmask << 16;
    #if ARCH_64BIT
        charmask |= (charmask << 16) << 16;
    #endif

    for (;;) {
        longword = *longwordPtr++;

        if ((((longword + magicBits) ^ ~longword) & ~magicBits) != 0 ||
            ((((longword ^ charmask) + magicBits) ^ ~(longword ^ charmask)) &
             ~magicBits) != 0) {
            const uint8* cp = (const uint8*)(longwordPtr - 1);

            if (*cp == c)
                return (const char*)cp;
            else if (*cp == '\0')
                break;
            if (*++cp == c)
                return (const char*)cp;
            else if (*cp == '\0')
                break;
            if (*++cp == c)
                return (const char*)cp;
            else if (*cp == '\0')
                break;
            if (*++cp == c)
                return (const char*)cp;
            else if (*cp == '\0')
                break;
            #if ARCH_64BIT
                if (*++cp == c)
                    return (const char*)cp;
                else if (*cp == '\0')
                    break;
                if (*++cp == c)
                    return (const char*)cp;
                else if (*cp == '\0')
                    break;
                if (*++cp == c)
                    return (const char*)cp;
                else if (*cp == '\0')
                    break;
                if (*++cp == c)
                    return (const char*)cp;
                else if (*cp == '\0')
                    break;
            #endif
        }
    }

    return nullptr;
}

const char* Str::FindCharRev(const char* str, char ch)
{
    const char *found = nullptr, *p;
    ch = (uint8)ch;
    
    if (ch == '\0')
        return Str::FindChar(str, '\0');
    while ((p = Str::FindChar(str, ch)) != NULL) {
        found = p;
        str = p + 1;
    }
    return (const char*)found;
}

const char* Str::FindStr(const char* RESTRICT str, const char* RESTRICT find)
{
    ASSERT(str);
    ASSERT(find);
    
    char ch = find[0];
    const char* _start = Str::FindChar(str, ch);
    uint32 find_len = Str::Len(find);
    uint32 len = Str::Len(str);
    
    while (_start) {
        len -= (uint32)(intptr_t)(_start - str);
        if (len < find_len)
            return NULL;
        str = _start;
        
        if (memcmp(_start, find, find_len) == 0)
            return str;
        
        _start = Str::FindChar(_start + 1, ch);
    }
    
    return nullptr;
}

bool Str::ToBool(const char* str)
{
    if (!str || str[0] == '\0')
        return false;

    if (Str::IsEqualNoCase(str, "true") || Str::IsEqualNoCase(str, "on") || str[0] == '1')
        return true;

    return false;    
}

int Str::ToInt(const char* str)
{
    return atoi(str);
}

uint32 Str::ToUint(const char* str, uint32 radix)
{
    return static_cast<uint32>(strtoul(str, nullptr, radix));
}

uint64 Str::ToUint64(const char* str, uint32 radix)
{
    return static_cast<uint64>(strtoull(str, nullptr, radix));
}

double Str::ToDouble(const char* str)
{
    return strtod(str, nullptr);
}

char* Str::ReplaceChar(char* dst, uint32 dstSize, char ch, char replaceWith)
{
    char* s = dst;
    uint32 count = 0; 
    while (*s != 0 && count++ < dstSize) {
        if (*s == ch)
            *s = replaceWith;
        ++s;
    }
    return dst;
}

char* Str::SubStr(char* dst, uint32 dstSize, const char* str, uint32 startIdx, uint32 endIdx)
{
    if (endIdx == 0)
        endIdx = Str::Len(str);

    ASSERT(startIdx < endIdx);

    uint32 srcCopyLen = Min(endIdx - startIdx, dstSize - 1);
    memcpy(dst, str + startIdx, srcCopyLen);
    dst[srcCopyLen] = '\0';

    return dst;
}

const char* Str::SkipWhitespace(const char* str)
{
    while (*str) {
        if (Str::IsWhitespace(*str))
            ++str;
        else
            break;
    }
    return str;
}

const char* Str::SkipChar(const char* str, char ch)
{
    while (*str) {
        if (*str == ch)
            ++str;
        else
            break;
    }
    return str;
}

Str::SplitResult Str::Split(const char* str, char ch, MemAllocator* alloc, bool acceptEmptySplits)
{
    Array<char*> splits(alloc);
    char* strCopy = Mem::AllocCopy<char>(str, Str::Len(str) + 1, alloc);

    char* s = strCopy;
    char* start = s;
    while (*s) {
        if (*s == ch) {
            if (start != s || acceptEmptySplits) {
                *(s++) = 0;
                splits.Push(start);
            }
            
            if (!acceptEmptySplits)
                s = const_cast<char*>(Str::SkipChar(s, ch));

            start = s;
        }
        else {
            ++s;
        }
    }

    if (start < s) 
        splits.Push(start);

    Str::SplitResult r {
        .buffer = strCopy,
        .splits = splits.Detach()
    };

    return r;
}

Str::SplitResult Str::SplitWhitespace(const char* str, MemAllocator* alloc)
{
    Array<char*> splits(alloc);
    char* strCopy = Mem::AllocCopy<char>(str, Str::Len(str) + 1, alloc);

    char* s = strCopy;
    char* start = s;
    while (*s) {
        if (Str::IsWhitespace(*s)) {
            if (start != s) {
                *(s++) = 0;
                splits.Push(start);
            }

            s = const_cast<char*>(Str::SkipWhitespace(s));
            start = s;
        }
        else {
            ++s;
        }
    }

    if (start != s) 
        splits.Push(start);

    Str::SplitResult r {
        .buffer = strCopy,
        .splits = splits.Detach()
    };

    return r;
}

void Str::FreeSplitResult(SplitResult& sres, MemAllocator* alloc)
{
    Mem::Free(sres.buffer, alloc);
    Mem::Free(sres.splits.Ptr(), alloc);
}


#ifdef BUILD_UNITY
    #if PLATFORM_POSIX
//----------------------------------------------------------------------------------------------------------------------
// SystemPosix.cpp


#if PLATFORM_POSIX

#include <unistd.h>             // sysconf, gettid
#include <dlfcn.h>              // dlopen, dlclose, dlsym
#include <pthread.h>            // pthread_t and family
#include <sys/types.h>
#include <sys/socket.h>         // socket funcs
#if PLATFORM_ANDROID || PLATFORM_LINUX
    #include <sys/prctl.h>          // prctl
    #include <semaphore.h>
    #include <sys/syscall.h>
    #include <sys/sendfile.h>
#else
    #include <sched.h>
#endif
#include <sys/stat.h>           // stat
#include <sys/mman.h>           // mmap/munmap/mprotect/..
#include <limits.h> 
#include <stdlib.h>             // realpath
#include <stdio.h>              // rename
#include <errno.h>
#include <fcntl.h>
#include <netdb.h>              // getaddrinfo, freeaddrinfo
#include <netinet/in.h>         // sockaddr_in
#include <arpa/inet.h>          // inet_ntop
#include <poll.h>               // async file poll
#include <spawn.h>
#include <signal.h>             // kill

#if PLATFORM_LINUX
#include <sys/wait.h>
#endif

#if PLATFORM_APPLE || PLATFORM_LINUX
    #include <uuid/uuid.h>
#endif


static inline void timespecAdd(struct timespec* _ts, int32_t _msecs)
{
    auto timespecToNs = [](const struct timespec* _ts)->uint64
    {
        return _ts->tv_sec * UINT64_C(1000000000) + _ts->tv_nsec;
    };

    auto timespecFromNs = [](struct timespec* _ts, uint64 _nsecs)
    {
        _ts->tv_sec = _nsecs / UINT64_C(1000000000);
        _ts->tv_nsec = _nsecs % UINT64_C(1000000000);
    };

    uint64 ns = timespecToNs(_ts);
    timespecFromNs(_ts, ns + (uint64)(_msecs)*1000000);
}

struct ThreadImpl
{
    Semaphore sem;
    MemAllocator* alloc;
    ThreadEntryFunc entryFn;
    pthread_t handle;
    char name[32];
    void* userData;
    size_t stackSize;
    pid_t tId;
    AtomicUint32 running;
    bool init;
};
static_assert(sizeof(ThreadImpl) <= sizeof(Thread), "Thread size mismatch");

static void* _ThreadStubFn(void* arg)
{
    ThreadImpl* thrd = reinterpret_cast<ThreadImpl*>(arg);

    union cast {
        void* ptr;
        int32 i;
    };

    thrd->tId = Thread::GetCurrentId();
    Thread::SetCurrentThreadName(thrd->name);

    ASSERT(thrd->entryFn);
    Atomic::StoreExplicit(&thrd->running, 1, AtomicMemoryOrder::Release);
    thrd->sem.Post();

    cast c;
    c.i = thrd->entryFn(thrd->userData);

    Atomic::StoreExplicit(&thrd->running, 0, AtomicMemoryOrder::Release);
    return c.ptr;
}

Thread::Thread()
{
    memset(mData, 0x0, sizeof(Thread));
}

static void _SetThreadPriority(pthread_t threadHandle, ThreadPriority prio)
{
    sched_param param {};
    int policy;
    
    pthread_getschedparam(threadHandle, &policy, &param);
    if (policy != SCHED_OTHER)
        policy = SCHED_OTHER;
    
    int prioMax = sched_get_priority_max(policy);
    int prioMin = sched_get_priority_min(policy);
    int prioNormal = prioMin + (prioMax - prioMin) / 2;

    #if PLATFORM_APPLE
        int policyIdle = policy;
        int prioIdle = prioMin;
        prioMin = prioMin + (prioNormal - prioMin)/2;
    #else
        int policyIdle = SCHED_IDLE;
        int prioIdle = 0;
    #endif
    
    switch (prio) {
    case ThreadPriority::Normal:    param.sched_priority = prioNormal; break;
    case ThreadPriority::Idle:      policy = policyIdle; param.sched_priority = prioIdle; break;
    case ThreadPriority::Realtime:  policy = SCHED_RR; param.sched_priority = prioMax; break;
    case ThreadPriority::High:      param.sched_priority = prioNormal + (prioMax - prioNormal)/2; break;
    case ThreadPriority::Low:       param.sched_priority = prioMin; break;
    }

    [[maybe_unused]] int r = pthread_setschedparam(threadHandle, policy, &param);
    ASSERT_ALWAYS(r != -1, "pthread_setschedparam failed: %d", errno);
}

bool Thread::Start(const ThreadDesc& desc)
{
    ThreadImpl* thrd = reinterpret_cast<ThreadImpl*>(mData);
    ASSERT(thrd->handle == 0 && !thrd->init);

    thrd->sem.Initialize();
    thrd->entryFn = desc.entryFn;
    thrd->userData = desc.userData;
    thrd->stackSize = Max<uint64>(static_cast<uint64>(desc.stackSize), 64*SIZE_KB);
    Str::Copy(thrd->name, sizeof(thrd->name), desc.name ? desc.name : "");

    pthread_attr_t attr;
    [[maybe_unused]] int r = pthread_attr_init(&attr);
    ASSERT_MSG(r == 0, "pthread_attr_init failed");
    r = pthread_attr_setstacksize(&attr, thrd->stackSize);
    ASSERT_MSG(r == 0, "pthread_attr_setstacksize failed");

    if ((desc.flags & ThreadCreateFlags::Detached) == ThreadCreateFlags::Detached) {
        r = pthread_attr_setdetachstate(&attr, static_cast<int>(ThreadCreateFlags::Detached));
        ASSERT_MSG(r == 0, "pthread_attr_setdetachstate failed");
    }

    r = pthread_create(&thrd->handle, &attr, _ThreadStubFn, thrd);
    if (r != 0) {
        ASSERT_ALWAYS(r == 0, "pthread_create failed");
        thrd->sem.Release();
        return false;
    }
    
    if (desc.priority != ThreadPriority::Normal)
        _SetThreadPriority(thrd->handle, desc.priority);

    thrd->sem.Wait();
    thrd->init = true;

    _private::CountersAddThread(thrd->stackSize);
    return true;
}

int Thread::Stop()
{
    union {
        void* ptr;
        int32_t i;
    } cast = {};

    ThreadImpl* thrd = reinterpret_cast<ThreadImpl*>(mData);

    if (thrd->handle) {
        ASSERT_MSG(thrd->init, "Thread is not init!");
       
        pthread_join(thrd->handle, &cast.ptr);
    }

    thrd->sem.Release();

    _private::CountersRemoveThread(thrd->stackSize);

    memset(mData, 0x0, sizeof(Thread));        
    return cast.i;
}

bool Thread::IsRunning()
{
    ThreadImpl* thrd = reinterpret_cast<ThreadImpl*>(mData);
    return Atomic::LoadExplicit(&thrd->running, AtomicMemoryOrder::Acquire) == 1;
}

void Thread::SetPriority(ThreadPriority prio)
{
    _SetThreadPriority(reinterpret_cast<ThreadImpl*>(mData)->handle, prio);
}

void Thread::SetCurrentThreadName(const char* name)
{
    #if PLATFORM_APPLE
        pthread_setname_np(name);
    #else
        prctl(PR_SET_NAME, name, 0, 0, 0);
    #endif

    #ifdef TRACY_ENABLE
        TracyCSetThreadName(name);
    #endif
}

void Thread::GetCurrentThreadName(char* nameOut, [[maybe_unused]] uint32 nameSize)
{
    ASSERT(nameSize > 16);
    
    #if PLATFORM_APPLE
        pthread_getname_np(pthread_self(), nameOut, nameSize);
    #else
        prctl(PR_GET_NAME, nameOut, 0, 0, 0);
    #endif
    
}

void Thread::SwitchContext()
{
    sched_yield();
}

uint32 Thread::GetCurrentId()
{
    #if PLATFORM_LINUX
        return static_cast<uint32>((pid_t)syscall(SYS_gettid));
    #elif PLATFORM_ANDROID
        return static_cast<uint32>(gettid());
    #elif PLATFORM_APPLE
        return pthread_mach_thread_np(pthread_self());
    #else
        #error "Not implemented"
    #endif
}

void Thread::Sleep(uint32 msecs)
{
    struct timespec req = { (time_t)msecs / 1000, (long)((msecs % 1000) * 1000000) };
    struct timespec rem = { 0, 0 };
    nanosleep(&req, &rem);
}

void Thread::SetCurrentThreadPriority(ThreadPriority prio)
{
    _SetThreadPriority(pthread_self(), prio);
}

struct MutexImpl
{
    pthread_mutex_t handle;
};
static_assert(sizeof(MutexImpl) <= sizeof(Mutex), "Mutex size mismatch");

void Mutex::Initialize(uint32 spinCount)
{
    MutexImpl* _m = reinterpret_cast<MutexImpl*>(mData);
    
    pthread_mutexattr_t attr;
    [[maybe_unused]] int r = pthread_mutexattr_init(&attr);
    ASSERT(r == 0);
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
    
    r = pthread_mutex_init(&_m->handle, &attr);
    ASSERT_ALWAYS(r == 0, "pthread_mutex_init failed");

    _private::CountersAddMutex();
}

void Mutex::Release()
{
    MutexImpl* _m = reinterpret_cast<MutexImpl*>(mData);

    pthread_mutex_destroy(&_m->handle);

    _private::CountersRemoveMutex();
}

void Mutex::Enter()
{
    MutexImpl* _m = reinterpret_cast<MutexImpl*>(mData);

    pthread_mutex_lock(&_m->handle);
}

void Mutex::Exit()
{
    MutexImpl* _m = reinterpret_cast<MutexImpl*>(mData);

    pthread_mutex_unlock(&_m->handle);
}

bool Mutex::TryEnter()
{
    MutexImpl* _m = reinterpret_cast<MutexImpl*>(mData);

    return pthread_mutex_trylock(&_m->handle) == 0;
}

struct ReadWriteMutexImpl
{
    pthread_rwlock_t handle;
};
static_assert(sizeof(ReadWriteMutexImpl) <= sizeof(ReadWriteMutex), "ReadWriteMutex mismatch");

void ReadWriteMutex::Initialize()
{
    ReadWriteMutexImpl* m = reinterpret_cast<ReadWriteMutexImpl*>(mData);
    pthread_rwlock_init(&m->handle, nullptr);
}

void ReadWriteMutex::Release()
{
    ReadWriteMutexImpl* m = reinterpret_cast<ReadWriteMutexImpl*>(mData);
    pthread_rwlock_destroy(&m->handle);
}

bool ReadWriteMutex::TryRead()
{
    ReadWriteMutexImpl* m = reinterpret_cast<ReadWriteMutexImpl*>(mData);
    return pthread_rwlock_tryrdlock(&m->handle) == 0;
}

bool ReadWriteMutex::TryWrite()
{
    ReadWriteMutexImpl* m = reinterpret_cast<ReadWriteMutexImpl*>(mData);
    return pthread_rwlock_trywrlock(&m->handle) == 0;
}

void ReadWriteMutex::EnterRead()
{
    ReadWriteMutexImpl* m = reinterpret_cast<ReadWriteMutexImpl*>(mData);
    pthread_rwlock_rdlock(&m->handle);
}

void ReadWriteMutex::ExitRead()
{
    ReadWriteMutexImpl* m = reinterpret_cast<ReadWriteMutexImpl*>(mData);
    pthread_rwlock_unlock(&m->handle);
}

void ReadWriteMutex::EnterWrite()
{
    ReadWriteMutexImpl* m = reinterpret_cast<ReadWriteMutexImpl*>(mData);
    pthread_rwlock_wrlock(&m->handle);
}

void ReadWriteMutex::ExitWrite()
{
    ReadWriteMutexImpl* m = reinterpret_cast<ReadWriteMutexImpl*>(mData);
    pthread_rwlock_unlock(&m->handle);
}

#if !PLATFORM_APPLE
struct SemaphoreImpl
{
    sem_t sem;
};
static_assert(sizeof(SemaphoreImpl) <= sizeof(Semaphore), "Sempahore size mismatch");

void Semaphore::Initialize()
{
    SemaphoreImpl* sem = reinterpret_cast<SemaphoreImpl*>(mData);

    [[maybe_unused]] int r = sem_init(&sem->sem, 0, 0);
    ASSERT_MSG(r == 0, "Initialize semaphore failed");

    _private::CountersAddSemaphore();
}

void Semaphore::Release()
{
    SemaphoreImpl* sem = reinterpret_cast<SemaphoreImpl*>(mData);
    sem_destroy(&sem->sem);

    _private::CountersRemoveSemaphore();
}

void Semaphore::Post(uint32 count)
{
    SemaphoreImpl* sem = reinterpret_cast<SemaphoreImpl*>(mData);
    for (uint32 i = 0; i < count; i++) {
        [[maybe_unused]] int r = sem_post(&sem->sem);
        ASSERT(r == 0);
    }
}

bool Semaphore::Wait(uint32 msecs)
{
    SemaphoreImpl* sem = reinterpret_cast<SemaphoreImpl*>(mData);
    [[maybe_unused]] int r;
    if (msecs == UINT32_MAX) {
        r = sem_wait(&sem->sem);
    }
    else {
        struct timespec ts;
        #if defined(__ANDROID_API__) && __ANDROID_API__ >= 28
        clock_gettime(CLOCK_MONOTONIC, &ts);
        timespecAdd(&ts, msecs);
        r = sem_timedwait_monotonic_np(&sem->sem, &ts);
        #else
        clock_gettime(CLOCK_REALTIME, &ts);
        timespecAdd(&ts, msecs);
        r = sem_timedwait(&sem->sem, &ts);
        #endif
    }

    ASSERT(r == 0 || r == ETIMEDOUT);
    return r == 0;
}
#endif // PLATFORM_APPLE


struct SignalImpl 
{
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    int value;
};
static_assert(sizeof(SignalImpl) <= sizeof(Signal), "Signal size mismatch");

void Signal::Initialize()
{
    SignalImpl* sig = reinterpret_cast<SignalImpl*>(mData);

    sig->value = 0;
    [[maybe_unused]] int r = pthread_mutex_init(&sig->mutex, NULL);
    ASSERT_MSG(r == 0, "pthread_mutex_init failed");

    [[maybe_unused]] int r2 = pthread_cond_init(&sig->cond, NULL);
    ASSERT_MSG(r2 == 0, "pthread_cond_init failed");

    _private::CountersAddSignal();
}

void Signal::Release()
{
    SignalImpl* sig = reinterpret_cast<SignalImpl*>(mData);

    pthread_cond_destroy(&sig->cond);
    pthread_mutex_destroy(&sig->mutex);

    _private::CountersRemoveSignal();
}

void Signal::Raise()
{
    SignalImpl* sig = reinterpret_cast<SignalImpl*>(mData);

    pthread_cond_signal(&sig->cond);
}

void Signal::RaiseAll()
{
    SignalImpl* sig = reinterpret_cast<SignalImpl*>(mData);

    pthread_cond_broadcast(&sig->cond);
}

bool Signal::Wait(uint32 msecs)
{
    SignalImpl* sig = reinterpret_cast<SignalImpl*>(mData);

    [[maybe_unused]] int r = pthread_mutex_lock(&sig->mutex);
    ASSERT(r == 0);
    
    bool timedOut = false;
    while (sig->value == 0) {
        if (msecs == -1) {
            r = pthread_cond_wait(&sig->cond, &sig->mutex);
        } else {
            struct timespec ts;

            #if defined(__ANDROID_API__) && __ANDROID_API__ >= 28
            clock_gettime(CLOCK_MONOTONIC, &ts);
            timespecAdd(&ts, msecs);
            r = pthread_cond_timedwait_monotonic_np(&sig->cond, &sig->mutex, &ts);
            #else
            clock_gettime(CLOCK_REALTIME, &ts);
            timespecAdd(&ts, msecs);
            r = pthread_cond_timedwait(&sig->cond, &sig->mutex, &ts);
            #endif
        }

        ASSERT(r == 0 || r == ETIMEDOUT);
        if (r == ETIMEDOUT) { 
            timedOut = true;
            break;
        }
    }

    if (!timedOut)
        sig->value = 0;

    pthread_mutex_unlock(&sig->mutex);
    return !timedOut;
}

bool Signal::WaitOnCondition(bool(*condFn)(int value, int reference), int reference, uint32 msecs)
{
    SignalImpl* sig = reinterpret_cast<SignalImpl*>(mData);

    [[maybe_unused]] int r = pthread_mutex_lock(&sig->mutex);
    ASSERT(r == 0);
    
    bool timedOut = false;
    while (condFn(sig->value, reference)) {
        if (msecs == -1) {
            r = pthread_cond_wait(&sig->cond, &sig->mutex);
        } else {
            struct timespec ts;
            #if defined(__ANDROID_API__) && __ANDROID_API__ >= 28
            clock_gettime(CLOCK_MONOTONIC, &ts);
            timespecAdd(&ts, msecs);
            r = pthread_cond_timedwait_monotonic_np(&sig->cond, &sig->mutex, &ts);
            #else
            clock_gettime(CLOCK_REALTIME, &ts);
            timespecAdd(&ts, msecs);
            r = pthread_cond_timedwait(&sig->cond, &sig->mutex, &ts);
            #endif
        }

        ASSERT(r == 0 || r == ETIMEDOUT);
        if (r == ETIMEDOUT) { 
            timedOut = true;
            break;
        }
    }
    if (!timedOut)
        sig->value = reference;
    pthread_mutex_unlock(&sig->mutex);
    return !timedOut;
}

void Signal::Decrement(uint32 count)
{
    SignalImpl* sig = reinterpret_cast<SignalImpl*>(mData);

    [[maybe_unused]] int r = pthread_mutex_lock(&sig->mutex);
    ASSERT(r == 0);
    sig->value -= int(count);
    pthread_mutex_unlock(&sig->mutex);
}

void Signal::Increment(uint32 count)
{
    SignalImpl* sig = reinterpret_cast<SignalImpl*>(mData);

    [[maybe_unused]] int r = pthread_mutex_lock(&sig->mutex);
    ASSERT(r == 0);
    sig->value += int(count);
    pthread_mutex_unlock(&sig->mutex);
}


void Signal::Set(int value)
{
    SignalImpl* sig = reinterpret_cast<SignalImpl*>(mData);

    [[maybe_unused]] int r = pthread_mutex_lock(&sig->mutex);
    ASSERT(r == 0);
    sig->value = value;
    pthread_mutex_unlock(&sig->mutex);
}

#if !PLATFORM_APPLE
struct TimerState
{
    bool init;
    uint64 start;
};
static TimerState gTimer;

void Timer::Initialize() 
{
    gTimer.init = true;
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    gTimer.start = (uint64)ts.tv_sec*1000000000 + (uint64)ts.tv_nsec;
}

uint64 Timer::GetTicks() 
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ((uint64)ts.tv_sec*1000000000 + (uint64)ts.tv_nsec) - gTimer.start;
}
#endif // !PLATFORM_APPLE

OSDLL OS::LoadDLL(const char* filepath, char** pErrorMsg)
{
    OSDLL dll = dlopen(filepath, RTLD_LOCAL | RTLD_LAZY);
    if (dll == nullptr && pErrorMsg) {
        static char errMsg[64];
        Str::PrintFmt(errMsg, sizeof(errMsg), dlerror());
        *pErrorMsg = errMsg;
    }
    else {
        if (pErrorMsg) 
            *pErrorMsg = nullptr;
    }
    return dll;
}

void OS::UnloadDLL(OSDLL dll)
{
    if (dll)
        dlclose(dll);
}

void* OS::GetSymbolAddress(OSDLL dll, const char* symbolName)
{
    return dlsym(dll, symbolName);
}

size_t OS::GetPageSize()
{
    return static_cast<size_t>(sysconf(_SC_PAGESIZE));
}

bool OS::SetEnvVar(const char* name, const char* value)
{
    return value != nullptr ? setenv(name, value, 1) == 0 : unsetenv(name) == 0;
}

bool OS::GetEnvVar(const char* name, char* outValue, uint32 valueSize)
{
    char* value = getenv(name);
    if (!value)
        return false;
    Str::Copy(outValue, valueSize, value);
    return true;
}

char* OS::GetAbsolutePath(const char* path, char* dst, size_t dstSize)
{
    char absPath[PATH_CHARS_MAX];
    if (realpath(path, absPath) != NULL) {
        Str::Copy(dst, (uint32)dstSize, absPath);
    } 
    else {
        dst[0] = '\0';
    }
    return dst;
}

PathInfo OS::GetPathInfo(const char* path)
{
    struct stat st;
    int result = stat(path, &st);
    if (result)
        return PathInfo {};

    PathType type = PathType::Invalid;
    if (st.st_mode & S_IFREG)
        type = PathType::File;
    else if (st.st_mode & S_IFDIR)
        type = PathType::Directory;
    #if PLATFORM_APPLE
        uint64 lastModified = st.st_mtimespec.tv_sec;
    #else
        uint64 lastModified = st.st_mtim.tv_sec;
    #endif

    return PathInfo {
        .type = type,
        .size = static_cast<uint64>(st.st_size),
        .lastModified = lastModified
    };
}

bool OS::CreateDir(const char* path)
{
    return mkdir(path, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == 0;
}

bool OS::CopyPath(const char *srcPath, const char *destPath)
{
    int in = open(srcPath, O_RDONLY);
    if (in < 0) 
        return -1;

    struct stat st;
    fstat(in, &st);

    int out = open(destPath, O_WRONLY | O_CREAT | O_TRUNC, st.st_mode);
    if (out < 0) { 
        close(in); 
        return -1; 
    }

    off_t offset = 0;
    ssize_t ret = sendfile(out, in, &offset, st.st_size);

    close(in);
    close(out);
    return ret >= 0;
}

bool OS::MovePath(const char* src, const char* dest)
{
    bool r = rename(src, dest) == 0;
    if (!r && errno == EXDEV) {
        if (CopyPath(src, dest)) {
            unlink(src);
            r = true;
        }
    }
    ASSERT_MSG(r, "rename failed: %d", errno);
    return r;
}

bool OS::DeletePath(const char* path)
{
    return remove(path) == 0;
}

bool OS::MakeTempPath(char* dst, size_t dstSize, const char* namePrefix, const char* dir)
{
    if (dir == nullptr)
        dir = "/tmp";
    PathUtils::Join(dst, dstSize, dir, namePrefix);
    Str::Concat(dst, uint32(dstSize), "XXXXXX");
    mkstemp(dst);
    return dst[0] ? true : false;
}

struct MemVirtualStatsAtomic 
{
    AtomicUint64 commitedBytes;
    AtomicUint64 reservedBytes;
};

static MemVirtualStatsAtomic gVMStats;

void* Mem::VirtualReserve(size_t size, MemVirtualFlags flags)
{
    void* ptr = mmap(NULL, size, PROT_NONE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (!ptr) {
        MEM_FAIL();
    }

    Atomic::FetchAdd(&gVMStats.reservedBytes, size);
    return ptr;
}

void* Mem::VirtualCommit(void* ptr, size_t size)
{
    int r = mprotect(ptr, size, PROT_READ | PROT_WRITE);
    ASSERT(r == 0);
    
    r = madvise(ptr, size, MADV_WILLNEED);
    if (r != 0) {
        if (errno == ENOMEM) {
            MEM_FAIL();
        }
        ASSERT(0);
        return nullptr;
    }

    Atomic::FetchAdd(&gVMStats.commitedBytes, size);
    return ptr;
}

void Mem::VirtualDecommit(void* ptr, size_t size)
{
    [[maybe_unused]] int r = madvise(ptr, size, MADV_DONTNEED);
    ASSERT(r == 0);
    Atomic::FetchSub(&gVMStats.commitedBytes, size);
}

void Mem::VirtualRelease(void* ptr, size_t size)
{
    [[maybe_unused]] int r = munmap(ptr, size);
    ASSERT(r == 0);
    Atomic::FetchSub(&gVMStats.reservedBytes, size);
}

MemVirtualStats Mem::VirtualGetStats()
{
    return MemVirtualStats {
        .commitedBytes = gVMStats.commitedBytes,
        .reservedBytes = gVMStats.reservedBytes
    };
}

#if PLATFORM_APPLE || PLATFORM_LINUX
struct UUIDImpl
{
    uuid_t uuid;
};
static_assert(sizeof(UUIDImpl) <= sizeof(UniqueID), "UUID size mismatch");
#endif

bool UniqueID::Generate(UniqueID* uuid)
{
#if PLATFORM_APPLE || PLATFORM_LINUX
    UUIDImpl* u = reinterpret_cast<UUIDImpl*>(uuid);
    uuid_generate_random(u->uuid);
    return true;
#else
    UNUSED(uuid);
    ASSERT_MSG(0, "Not implemented");
    return false;
#endif
}

bool UniqueID::ToString(const UniqueID& uuid, char* str, uint32 size)
{
#if PLATFORM_APPLE || PLATFORM_LINUX
    ASSERT(size >= 36);
    UNUSED(size);
    
    const UUIDImpl& u = reinterpret_cast<const UUIDImpl&>(uuid);
    uuid_unparse(u.uuid, str);
    return true;
#else
    UNUSED(uuid);
    UNUSED(str);
    UNUSED(size);
    ASSERT_MSG(0, "Not implemented");
    return false;
#endif
}

bool UniqueID::FromString(UniqueID* uuid, const char* str)
{
#if PLATFORM_APPLE || PLATFORM_LINUX
    UUIDImpl* u = reinterpret_cast<UUIDImpl*>(uuid);

    if (uuid_parse(str, u->uuid) < 0)
        return false;
    return true;
#else
    UNUSED(uuid);
    UNUSED(str);
    ASSERT_MSG(0, "Not implemented");
    return false;
#endif
}

bool UniqueID::operator==(const UniqueID& uuid) const
{
    return memcmp(&uuid, this, sizeof(UUIDImpl)) == 0;
}

#undef _LARGEFILE64_SOURCE
#ifndef __O_LARGEFILE4
    #define __O_LARGEFILE 0
#endif

struct FilePosix
{
    int         id;
    FileOpenFlags flags;
    uint64      size;  
    uint64      lastModifiedTime;
};
static_assert(sizeof(FilePosix) <= sizeof(File));

File::File()
{
    FilePosix* f = (FilePosix*)mData;
    f->id = -1;
    f->flags = FileOpenFlags::None;
    f->size = 0;
    f->lastModifiedTime = 0;
}

bool File::Open(const char* filepath, FileOpenFlags flags)
{
    ASSERT((flags & (FileOpenFlags::Read|FileOpenFlags::Write)) != (FileOpenFlags::Read|FileOpenFlags::Write));
    ASSERT((flags & (FileOpenFlags::Read|FileOpenFlags::Write)) != FileOpenFlags::None);

    FilePosix* f = (FilePosix*)mData;

    int openFlags = __O_LARGEFILE;
    mode_t mode = 0;

    if ((flags & FileOpenFlags::Read) == FileOpenFlags::Read) {
        openFlags |= O_RDONLY;
    } else if ((flags & FileOpenFlags::Write) == FileOpenFlags::Write) {
        openFlags |= O_WRONLY;
        if ((flags & FileOpenFlags::Append) == FileOpenFlags::Append) {
            openFlags |= O_APPEND;
        } 
        else {
            openFlags |= (O_CREAT | O_TRUNC);
            mode |= (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH); 
        }
    }

    #if (PLATFORM_LINUX || PLATFORM_ANDROID)
        if ((flags & FileOpenFlags::Temp) == FileOpenFlags::Temp) {
            openFlags |= __O_TMPFILE;
        }
    #endif

    int fileId = open(filepath, openFlags, mode);
    if (fileId == -1) 
        return false;

    #if PLATFORM_APPLE
        if ((flags & FileOpenFlags::NoCache) == FileOpenFlags::NoCache) {
            if (fcntl(fileId, F_NOCACHE) != 0) {
                return false;
            }
        }
    #endif

    struct stat _stat;
    int sr = fstat(fileId, &_stat);
    if (sr != 0) {
        ASSERT_MSG(0, "stat failed!");
        return false;
    }

    f->id = fileId;
    f->flags = flags;
    f->size = static_cast<uint64>(_stat.st_size);
    f->lastModifiedTime = static_cast<uint64>(_stat.st_mtime);
    return true;
}

void File::Close()
{
    FilePosix* f = (FilePosix*)mData;

    if (f->id != -1) {
        close(f->id);
        f->id = -1;
    }
}

size_t File::Read(void* dst, size_t size)
{
    FilePosix* f = (FilePosix*)mData;
    ASSERT(f->id != -1);
    
    if ((f->flags & FileOpenFlags::NoCache) == FileOpenFlags::NoCache) {
        static size_t pagesz = 0;
        if (pagesz == 0)
            pagesz = OS::GetPageSize();
        ASSERT_ALWAYS((uintptr_t)dst % pagesz == 0, "buffers must be aligned with NoCache flag");
    }
    ssize_t r = read(f->id, dst, size);
    return r != -1 ? r : 0;
}

size_t File::Write(const void* src, size_t size)
{
    ASSERT(size);
    FilePosix* f = (FilePosix*)mData;
    ASSERT(f->id != -1);

    int64_t bytesWritten = write(f->id, src, size);
    if (bytesWritten > -1) {
        f->size += bytesWritten; 
        return bytesWritten;
    }
    else {
        return 0;
    }
}

size_t File::Seek(size_t offset, FileSeekMode mode)
{
    FilePosix* f = (FilePosix*)mData;
    ASSERT(f->id != -1);

    int _whence = 0;
    switch (mode) {
    case FileSeekMode::Current:    _whence = SEEK_CUR; break;
    case FileSeekMode::Start:      _whence = SEEK_SET; break;
    case FileSeekMode::End:        _whence = SEEK_END; break;
    }

    return size_t(lseek(f->id, static_cast<off_t>(offset), _whence));
}

size_t File::GetSize() const
{
    const FilePosix* f = (const FilePosix*)mData;
    return f->size;
}

uint64 File::GetLastModified() const
{
    const FilePosix* f = (const FilePosix*)mData;
    return f->lastModifiedTime;
}

bool File::IsOpen() const
{
    FilePosix* f = (FilePosix*)mData;
    return f->id != -1;
}

#define SOCKET_INVALID -1
#define SOCKET_ERROR -1

namespace _private
{
    static SocketErrorCode::Enum socketTranslatePlatformErrorCode()
    {
        switch (errno) {
        case EADDRINUSE:        return SocketErrorCode::AddressInUse;
        case ECONNREFUSED:      return SocketErrorCode::ConnectionRefused;
        case EISCONN:           return SocketErrorCode::AlreadyConnected;
        case EHOSTUNREACH: 
        case ENETUNREACH:       return SocketErrorCode::HostUnreachable;
        case EWOULDBLOCK:
        case ETIMEDOUT:         return SocketErrorCode::Timeout;
        case ECONNRESET:        return SocketErrorCode::ConnectionReset;
        case EADDRNOTAVAIL:     return SocketErrorCode::AddressNotAvailable;
        case EAFNOSUPPORT:      return SocketErrorCode::AddressUnsupported;
        case ESHUTDOWN:         return SocketErrorCode::SocketShutdown;
        case EMSGSIZE:          return SocketErrorCode::MessageTooLarge;
        case ENOTCONN:          return SocketErrorCode::NotConnected;
        default:                return SocketErrorCode::Unknown;
        }
    }
} // namespace _private

#define SOCKET_INVALID -1
#define SOCKET_ERROR -1

SocketTCP::SocketTCP() :
    mSock(SOCKET_INVALID),
    mErrCode(SocketErrorCode::None),
    mLive(0)
{
}

void SocketTCP::Close()
{
    if (mSock != SOCKET_INVALID) {
        if (mLive)
            shutdown(mSock, SHUT_RDWR);
        close(mSock);

        mSock = SOCKET_INVALID;
        mErrCode = SocketErrorCode::None;
        mLive = false;
    }
}

SocketTCP SocketTCP::CreateListener()
{
    SocketTCP sock;

    sock.mSock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock.mSock == SOCKET_INVALID) {
        sock.mErrCode = _private::socketTranslatePlatformErrorCode();
        LOG_ERROR("SocketTCP: Opening the socket failed");
        return sock;
    }
    return sock;    
}

bool SocketTCP::Listen(uint16 port, uint32 maxConnections)
{
    ASSERT(IsValid());

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);

    if (bind(mSock, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        mErrCode = _private::socketTranslatePlatformErrorCode();
        LOG_ERROR("SocketTCP: failed binding the socket to port: %d", port);
        return false;
    }

    LOG_VERBOSE("SocketTCP: Listening on port '%d' for incoming connections ...", port);
    int _maxConnections = maxConnections > INT32_MAX ? INT32_MAX : static_cast<int>(maxConnections);
    bool success = listen(mSock, _maxConnections) >= 0;
    
    if (!success) 
        mErrCode = _private::socketTranslatePlatformErrorCode();
    else
        mLive = true;

    return success;
}

SocketTCP SocketTCP::Accept(char* clientUrl, uint32 clientUrlSize)
{
    ASSERT(IsValid());

    SocketTCP newSock;

    struct sockaddr_in addr;
    socklen_t addrlen = sizeof(addr);
    newSock.mSock = accept(mSock, (struct sockaddr*)&addr, &addrlen);
    if (mLive && newSock.mSock == SOCKET_INVALID) {
        newSock.mErrCode = _private::socketTranslatePlatformErrorCode();
        LOG_ERROR("SocketTCP: failed to accept the new socket");
        return newSock;
    }

    if (clientUrl && clientUrlSize) {
        char ip[256];
        inet_ntop(AF_INET, &addr.sin_addr, ip, sizeof(ip));
        uint16 port = htons(addr.sin_port);
        
        Str::PrintFmt(clientUrl, clientUrlSize, "%s:%d", ip, port);
    }

    newSock.mLive = true;
    return newSock;
}

SocketTCP SocketTCP::Connect(const char* url)
{
    SocketTCP sock;

    char address[256];
    char port[16];
    if (!ParseUrl(url, address, sizeof(address), port, sizeof(port))) {
        LOG_ERROR("SocketTCP: failed parsing the url: %s", url);
        return sock;
    }

    struct addrinfo hints;
    memset(&hints, 0x0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_flags = AI_PASSIVE;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    struct addrinfo* addri = nullptr;
    if (getaddrinfo(address, port, &hints, &addri) != 0) {
        LOG_ERROR("SocketTCP: failed to resolve url: %s", url);
        return sock;
    }

    sock.mSock = socket(addri->ai_family, addri->ai_socktype, addri->ai_protocol);
    if (sock.mSock == SOCKET_INVALID) {
        freeaddrinfo(addri);
        LOG_ERROR("SocketTCP: failed to create socket");
        return sock;
    }

    if (connect(sock.mSock, addri->ai_addr, (int)addri->ai_addrlen) == -1) {
        freeaddrinfo(addri);
        sock.mErrCode = _private::socketTranslatePlatformErrorCode();
        LOG_ERROR("SocketTCP: failed to connect to url: %s", url);
        sock.Close();
        return sock;
    }

    freeaddrinfo(addri);

    sock.mLive = true;
    return sock;
}

uint32 SocketTCP::Write(const void* src, uint32 size)
{
    ASSERT(IsValid());
    ASSERT(mLive);
    uint32 totalBytesSent = 0;

    while (size > 0) {
        int bytesSent = (int)send(mSock, reinterpret_cast<const char*>(src) + totalBytesSent, size, 0);
        if (bytesSent == 0) {
            break;
        }
        else if (bytesSent == -1) {
            mErrCode = _private::socketTranslatePlatformErrorCode();
            if (mErrCode == SocketErrorCode::SocketShutdown ||
                mErrCode == SocketErrorCode::NotConnected)
            {
                LOG_DEBUG("SocketTCP: socket connection closed forcefully by the peer");
                mLive = false;
            }
            return UINT32_MAX;
        }

        totalBytesSent += static_cast<uint32>(bytesSent);
        size -= static_cast<uint32>(bytesSent);
    }

    return totalBytesSent;
}

uint32 SocketTCP::Read(void* dst, uint32 dstSize)
{
    ASSERT(IsValid());
    ASSERT(mLive);

    int bytesRecv = (int)recv(mSock, reinterpret_cast<char*>(dst), dstSize, 0);
    if (bytesRecv == -1) {
        mErrCode = _private::socketTranslatePlatformErrorCode();
        if (mErrCode == SocketErrorCode::SocketShutdown ||
            mErrCode == SocketErrorCode::NotConnected)
        {
            LOG_DEBUG("SocketTCP: socket connection closed forcefully by the peer");
            mLive = false;
        }
        return UINT32_MAX;
    }

    return static_cast<uint32>(bytesRecv);
}

bool SocketTCP::IsValid() const
{
    return mSock != SOCKET_INVALID;
}


struct AsyncFilePosix
{
    AsyncFile f;
    MemAllocator* alloc;
    AsyncFileCallback readFn;
    int fd;
    AtomicUint32 done;
};

struct AsyncContext
{
    Mutex mutex;
    Thread* threads;
    Array<AsyncFilePosix*> queue;
    uint32 queueIndex;
    uint32 numThreads;
    Semaphore sem;
    AtomicUint32 quit;
};

static AsyncContext gAsyncCtx;

namespace Async
{
    static int _IOThreadCallback(void* userData)
    {
        while (!Atomic::Load(&gAsyncCtx.quit)) {
            gAsyncCtx.sem.Wait();
            
            AsyncFilePosix* file = nullptr;
            {
                MutexScope lock(gAsyncCtx.mutex);
                if (gAsyncCtx.queue.IsEmpty())
                    continue;
                uint32 index = gAsyncCtx.queueIndex++;
                file = gAsyncCtx.queue[index];
                gAsyncCtx.queue.RemoveAndSwap(index);
                if (gAsyncCtx.queueIndex >= gAsyncCtx.queue.Count())
                    gAsyncCtx.queueIndex = 0;
            }
            
            ASSERT(file->fd != -1);
            pollfd p {};
            p.fd = file->fd;
            p.events = POLLIN;
            [[maybe_unused]] int r = poll(&p, 1, -1);
            ASSERT(r != -1);
            ssize_t bytesRead = read(file->fd, file->f.data, file->f.size);
            ASSERT(bytesRead <= UINT32_MAX);
            
            bool hadError = bytesRead != file->f.size;
            Atomic::StoreExplicit(&file->done, hadError ? 1 : -1, AtomicMemoryOrder::Release);
            file->readFn(&file->f, hadError);
        }
        
        return 0;
    }
} // Async

bool Async::Initialize()
{
    SysInfo info {};
    OS::GetSysInfo(&info);
    ASSERT(info.coreCount);
    
    gAsyncCtx.mutex.Initialize();
    gAsyncCtx.sem.Initialize();
    
    gAsyncCtx.threads = NEW_ARRAY(Mem::GetDefaultAlloc(), Thread, info.coreCount);
    gAsyncCtx.numThreads = info.coreCount;

    for (uint32 i = 0; i < gAsyncCtx.numThreads; i++) {
        String<32> name = String<32>::Format("IO_%u", i+1);
        ThreadDesc tdesc {
            .entryFn = Async::_IOThreadCallback,
            .name = name.CStr(),
            .stackSize = 512*SIZE_KB
        };
        
        gAsyncCtx.threads[i].Start(tdesc);
    }

    LOG_INFO("(init) Initialized %u Async IO Threads", gAsyncCtx.numThreads);

    return true;
}

void Async::Release()
{
    Atomic::Store(&gAsyncCtx.quit, 1);
    gAsyncCtx.sem.Post(gAsyncCtx.numThreads);
    for (uint32 i = 0; i < gAsyncCtx.numThreads; i++)
        gAsyncCtx.threads[i].Stop();
    Mem::Free(gAsyncCtx.threads);
    gAsyncCtx.sem.Release();
    gAsyncCtx.mutex.Release();
}

AsyncFile* Async::ReadFile(const char* filepath, const AsyncFileRequest& request)
{
    int fd = open(filepath, O_RDONLY|O_NONBLOCK, 0);
    if (fd == -1)
        return nullptr;
    
    uint64 fileSize = request.sizeHint;
    uint64 fileModificationTime = 0;
    
    if (!fileSize) {
        PathInfo info = OS::GetPathInfo(filepath);
        if (info.type != PathType::File) {
            close(fd);
            return nullptr;
        }
        
        fileSize = info.size;
        fileModificationTime = info.lastModified;
    }
    
    MemSingleShotMalloc<AsyncFilePosix> mallocator;
    uint8* data;
    uint8* userData = nullptr;
    if (request.userDataAllocateSize)
        mallocator.AddExternalPointerField<uint8>(&userData, request.userDataAllocateSize);
    mallocator.AddExternalPointerField<uint8>(&data, fileSize);
    
    AsyncFilePosix* file = mallocator.Malloc(request.alloc);
    memset((void*)file, 0x0, sizeof(*file));
    
    file->f.filepath = filepath;
    file->f.data = data;
    file->f.size = uint32(fileSize);
    file->f.lastModifiedTime = fileModificationTime;
    if (request.userData) {
        if (request.userDataAllocateSize) {
            memcpy(userData, request.userData, request.userDataAllocateSize);
            file->f.userData = userData;
        }
        else {
            file->f.userData = request.userData;
        }
    }

    file->fd = fd;
    file->alloc = request.alloc;
    file->readFn = request.readFn;
    
    {
        MutexScope lock(gAsyncCtx.mutex);
        gAsyncCtx.queue.Push(file);
        gAsyncCtx.sem.Post();
    }

    return &file->f;
}

void Async::Close(AsyncFile* file)
{
    AsyncFilePosix* fm = (AsyncFilePosix*)file;
    if (fm->fd)
        close(fm->fd);
    MemSingleShotMalloc<AsyncFilePosix>::Free(fm, fm->alloc);
}

bool Async::Wait(AsyncFile* file)
{
    ASSERT_MSG(0, "Wait not implemented for generic impl");
    return false;
}

bool Async::IsFinished(AsyncFile* file, bool* outError)
{
    ASSERT(file);
    AsyncFilePosix* f = (AsyncFilePosix*)file;
    uint32 r = Atomic::LoadExplicit(&f->done, AtomicMemoryOrder::Acquire);
    if (outError)
        *outError = (r == -1);
    return r != 0;
}

OSProcess::OSProcess() :
    mExitCode(-1),
    mTermSignalCode(0)
{
    mProcess = IntToPtr<int>(-1);
    mStdOutPipeRead = IntToPtr<int>(-1);
    mStdErrPipeRead = IntToPtr<int>(-1);
}

OSProcess::~OSProcess()
{
    int stdoutPipeRead = PtrToInt<int32>(mStdOutPipeRead);
    int stderrPipeRead = PtrToInt<int32>(mStdErrPipeRead);
    pid_t pid = PtrToInt<int32>(mProcess);
    
    if (stdoutPipeRead != -1)
        close(stdoutPipeRead);
    if (stderrPipeRead != -1)
        close(stderrPipeRead);
    
    if (pid != -1) {
        int status;
        waitpid(pid, &status, 0);
    }
}

bool OSProcess::Run(const char* cmdline, OSProcessFlags flags, const char* cwd)
{
    int stdoutPipes[2] = {-1, -1};
    int stderrPipes[2] = {-1, -1};
    pid_t pid;
    posix_spawn_file_actions_t fileActions;

    [[maybe_unused]] int r = posix_spawn_file_actions_init(&fileActions);
    ASSERT_MSG(r == 0, "posix_spawn_file_actions_init failed");

    if ((flags & OSProcessFlags::CaptureOutput) == OSProcessFlags::CaptureOutput) {
        r = pipe(stdoutPipes);
        ASSERT_MSG(r == 0, "Creating pipes failed");

        r = posix_spawn_file_actions_addclose(&fileActions, stdoutPipes[0]);
        ASSERT_MSG(r == 0, "posix_spawn_file_actions_addclose");
        
        r = posix_spawn_file_actions_adddup2(&fileActions, stdoutPipes[1], STDOUT_FILENO);
        ASSERT_MSG(r == 0, "posix_spawn_file_actions_addup2 failed");
        
        r = pipe(stderrPipes);
        ASSERT_MSG(r == 0, "Creating pipes failed");

        r = posix_spawn_file_actions_addclose(&fileActions, stderrPipes[0]);
        ASSERT_MSG(r == 0, "posix_spawn_file_actions_addclose");
        
        r = posix_spawn_file_actions_adddup2(&fileActions, stderrPipes[1], STDERR_FILENO);
        ASSERT_MSG(r == 0, "posix_spawn_file_actions_addup2 failed");
    }
    
    if (cwd) {
        if (__builtin_available(macOS 10.15, *))
            posix_spawn_file_actions_addchdir_np(&fileActions, cwd);
        else
            ASSERT_MSG(0, "Not implemented for versions less than macOS 10.15");
    }
    
    MemTempAllocator tmpAlloc;
    Array<char*> argsArr(&tmpAlloc);

    char* cmdlineCopy = Mem::AllocCopy<char>(cmdline, Str::Len(cmdline)+1, &tmpAlloc);
    char* str = const_cast<char*>(Str::SkipWhitespace(cmdlineCopy));
    while (*str) {
        char* start = str;
        while (*(++str)) {
            if (Str::IsWhitespace(*str)) {
                *str = 0;
                str = const_cast<char*>(Str::SkipWhitespace(str+1));
                break;
            }
        }
        argsArr.Push(start);
    }
    
    ASSERT(argsArr.Count());
    char** args = nullptr;
    if (argsArr.Count() > 1) {
        args = (char**)tmpAlloc.MallocTyped<char*>(argsArr.Count() + 1);
        for (uint32 i = 0; i < argsArr.Count(); i++)
            args[i] = argsArr[i];
        args[argsArr.Count()] = nullptr;
    }
    
    if (posix_spawn(&pid, argsArr[0], &fileActions, nullptr, args, nullptr) != 0) {
        LOG_ERROR("Running process failed: %s", cmdline);
        posix_spawn_file_actions_destroy(&fileActions);
        if (stdoutPipes[0] != -1)
            close(stdoutPipes[0]);
        if (stdoutPipes[1] != -1)
            close(stdoutPipes[1]);
        return false;
    }
    
    if ((flags & OSProcessFlags::CaptureOutput) == OSProcessFlags::CaptureOutput) {
        close(stdoutPipes[1]);
        close(stderrPipes[1]);
        mStdOutPipeRead = IntToPtr<int>(stdoutPipes[0]);
        mStdErrPipeRead = IntToPtr<int>(stderrPipes[0]);
    }
    
    posix_spawn_file_actions_destroy(&fileActions);
    mProcess = IntToPtr<int32>(pid);
    return true;
}

void OSProcess::Wait() const
{
    pid_t pid = PtrToInt<int32>(mProcess);
    ASSERT(pid != -1);
    int status;
    [[maybe_unused]] int r = waitpid(pid, &status, 0);
    ASSERT(r == pid);
    if (WIFEXITED(status))
        const_cast<OSProcess*>(this)->mExitCode = WEXITSTATUS(status);
    else if (WIFSIGNALED(status))
        const_cast<OSProcess*>(this)->mTermSignalCode = WTERMSIG(status);
    const_cast<OSProcess*>(this)->mProcess = IntToPtr<int32>(-1);
}

bool OSProcess::IsRunning() const
{
    pid_t pid = PtrToInt<int32>(mProcess);
    ASSERT(pid != -1);
    int status;
    return waitpid(pid, &status, WNOHANG) == 0;
}

int OSProcess::GetExitCode() const
{
    return mExitCode;
}

uint32 OSProcess::ReadStdOut(void* data, uint32 size) const
{
    int pipeId = PtrToInt<int>(mStdOutPipeRead);
    ASSERT(pipeId != -1);
    ssize_t r = read(pipeId, data, size);
    return r > 0 ? (uint32)r : 0;
}

uint32 OSProcess::ReadStdErr(void* data, uint32 size) const
{
    int pipeId = PtrToInt<int>(mStdErrPipeRead);
    ASSERT(pipeId != -1);
    ssize_t r = read(pipeId, data, size);
    return r > 0 ? (uint32)r : 0;
}

void OSProcess::Abort()
{
    pid_t pid = PtrToInt<int32>(mProcess);
    if (pid)
        kill(pid, 1);
}



#endif // PLATFORM_POSIX

    #endif
    
    #if PLATFORM_WINDOWS
//----------------------------------------------------------------------------------------------------------------------
// SystemWin.cpp


#if PLATFORM_WINDOWS

#include <synchapi.h>   // InitializeCriticalSectionAndSpinCount, InitializeCriticalSection, ...
#include <sysinfoapi.h> // GetPhysicallyInstalledSystemMemory
#include <intrin.h>     // __cpuid
#include <tlhelp32.h>   // CreateToolhelp32Snapshot
#include <winsock2.h>
#include <ws2tcpip.h>
#include <ShlObj.h>     // SH family of functions (Shell32)

#pragma comment(lib, "ws2_32.lib")

namespace _limits 
{
    const uint32 SYS_MAX_CORES = 128;
}


struct AdvApi32
{
    typedef LSTATUS (*RegGetValueAFn)(
        _In_ HKEY hkey,
        _In_opt_ LPCSTR lpSubKey,
        _In_opt_ LPCSTR lpValue,
        _In_ DWORD dwFlags,
        _Out_opt_ LPDWORD pdwType,
        _When_((dwFlags & 0x7F) == RRF_RT_REG_SZ ||
               (dwFlags & 0x7F) == RRF_RT_REG_EXPAND_SZ ||
               (dwFlags & 0x7F) == (RRF_RT_REG_SZ | RRF_RT_REG_EXPAND_SZ) ||
               *pdwType == REG_SZ ||
               *pdwType == REG_EXPAND_SZ, _Post_z_)
        _When_((dwFlags & 0x7F) == RRF_RT_REG_MULTI_SZ ||
               *pdwType == REG_MULTI_SZ, _Post_ _NullNull_terminated_)
        _Out_writes_bytes_to_opt_(*pcbData,*pcbData) PVOID pvData,
        _Inout_opt_ LPDWORD pcbData);

    typedef BOOL (*OpenProcessTokenFn)(
        _In_ HANDLE ProcessHandle,
        _In_ DWORD DesiredAccess,
        _Outptr_ PHANDLE TokenHandle
    );

    typedef BOOL (*AdjustTokenPrivilegesFn)(
        _In_ HANDLE TokenHandle,
        _In_ BOOL DisableAllPrivileges,
        _In_opt_ PTOKEN_PRIVILEGES NewState,
        _In_ DWORD BufferLength,
        _Out_writes_bytes_to_opt_(BufferLength,*ReturnLength) PTOKEN_PRIVILEGES PreviousState,
        _Out_opt_ PDWORD ReturnLength
    );

    typedef BOOL (*LookupPrivilegeValueAFn)(
        _In_opt_ LPCSTR lpSystemName,
        _In_     LPCSTR lpName,
        _Out_    PLUID   lpLuid
    );

    HANDLE dll;
    RegGetValueAFn RegGetValueA;
    OpenProcessTokenFn OpenProcessToken;
    AdjustTokenPrivilegesFn AdjustTokenPrivileges;
    LookupPrivilegeValueAFn LookupPrivilegeValueA;
};

struct Ole32
{
    typedef int (*StringFromGUID2Fn)(
        _In_ REFGUID rguid,
        _Out_writes_to_(cchMax, return) LPOLESTR lpsz,
        _In_ int cchMax
    );

    typedef HRESULT (*CoCreateGuidFn)(
        _Out_ GUID  FAR * pguid
    );

    typedef void (*CoTaskMemFreeFn)(
        _Frees_ptr_opt_ LPVOID pv
    );

    typedef HRESULT (*CLSIDFromStringFn)(
        _In_ LPCOLESTR lpsz,
        _Out_ LPCLSID pclsid
    );

    HANDLE dll;
    StringFromGUID2Fn StringFromGUID2;
    CoCreateGuidFn CoCreateGuid;
    CoTaskMemFreeFn CoTaskMemFree;
    CLSIDFromStringFn CLSIDFromString;
};

struct Shell32
{
    typedef HINSTANCE (*ShellExecuteAFn)(_In_opt_ HWND hwnd, _In_opt_ LPCSTR lpOperation, _In_ LPCSTR lpFile, _In_opt_ LPCSTR lpParameters,
                                       _In_opt_ LPCSTR lpDirectory, _In_ INT nShowCmd);
    typedef HRESULT (*SHGetKnownFolderPathFn)(_In_ REFKNOWNFOLDERID rfid,
                            _In_ DWORD /* KNOWN_FOLDER_FLAG */ dwFlags,
                            _In_opt_ HANDLE hToken,
                            _Outptr_ PWSTR *ppszPath); // free *ppszPath with CoTaskMemFree

    HANDLE dll;
    ShellExecuteAFn ShellExecuteA;
    SHGetKnownFolderPathFn SHGetKnownFolderPath;
};

static AdvApi32 gAdvApi32;

static void _LoadAdvApi32()
{
    if (gAdvApi32.dll == nullptr) {
        gAdvApi32.dll = (HANDLE)OS::LoadDLL("Advapi32.dll");
        ASSERT_ALWAYS(gAdvApi32.dll, "Could not load system DLL: Advapi32.dll");

        gAdvApi32.RegGetValueA = (AdvApi32::RegGetValueAFn)OS::GetSymbolAddress(gAdvApi32.dll, "RegGetValueA");
        gAdvApi32.OpenProcessToken = (AdvApi32::OpenProcessTokenFn)OS::GetSymbolAddress(gAdvApi32.dll, "OpenProcessToken");
        gAdvApi32.AdjustTokenPrivileges = (AdvApi32::AdjustTokenPrivilegesFn)OS::GetSymbolAddress(gAdvApi32.dll, "AdjustTokenPrivileges");
        gAdvApi32.LookupPrivilegeValueA = (AdvApi32::LookupPrivilegeValueAFn)OS::GetSymbolAddress(gAdvApi32.dll, "LookupPrivilegeValueA");

        ASSERT_ALWAYS(gAdvApi32.RegGetValueA && gAdvApi32.OpenProcessToken && gAdvApi32.AdjustTokenPrivileges && gAdvApi32.LookupPrivilegeValueA,
                      "Loading AdvApi32 API failed");
    }
}

static Ole32 gOle32;

static void _LoadOle32()
{
    if (gOle32.dll == nullptr) {
        gOle32.dll = (HANDLE)OS::LoadDLL("Ole32.dll");
        ASSERT_ALWAYS(gOle32.dll, "Could not load system DLL: Ole32.dll");

        gOle32.StringFromGUID2 = (Ole32::StringFromGUID2Fn)OS::GetSymbolAddress(gOle32.dll, "StringFromGUID2");
        gOle32.CoCreateGuid = (Ole32::CoCreateGuidFn)OS::GetSymbolAddress(gOle32.dll, "CoCreateGuid");
        gOle32.CoTaskMemFree = (Ole32::CoTaskMemFreeFn)OS::GetSymbolAddress(gOle32.dll, "CoTaskMemFree");
        gOle32.CLSIDFromString = (Ole32::CLSIDFromStringFn)OS::GetSymbolAddress(gOle32.dll, "CLSIDFromString");

        ASSERT_ALWAYS(gOle32.StringFromGUID2 && gOle32.CoCreateGuid && gOle32.CoTaskMemFree && gOle32.CLSIDFromString,
                      "Loading Ole32 API failed");
    }
}

static Shell32 gShell32;

static void _LoadShell32()
{
    if (gShell32.dll == nullptr) {
        gShell32.dll = (HANDLE)OS::LoadDLL("Shell32.dll");
        ASSERT_ALWAYS(gShell32.dll, "Could not load system DLL: Shell32.dll");

        gShell32.ShellExecuteA = (Shell32::ShellExecuteAFn)OS::GetSymbolAddress(gShell32.dll, "ShellExecuteA");
        gShell32.SHGetKnownFolderPath = (Shell32::SHGetKnownFolderPathFn)OS::GetSymbolAddress(gShell32.dll, "SHGetKnownFolderPath");

        ASSERT_ALWAYS(gShell32.ShellExecuteA && gShell32.SHGetKnownFolderPath, "Loading Shell32 API failed");
    }
}


struct ThreadImpl
{
    Semaphore sem;
    ThreadEntryFunc threadFn;
    HANDLE handle;
    void* userData;
    size_t stackSize;
    char name[32];
    DWORD tId;
    AtomicUint32 running;
    bool init;
};
static_assert(sizeof(ThreadImpl) <= sizeof(Thread), "Thread size mismatch");

static DWORD WINAPI _ThreadStubFn(LPVOID arg)
{
    ThreadImpl* thrd = reinterpret_cast<ThreadImpl*>(arg);
    thrd->tId = GetCurrentThreadId();
    Thread::SetCurrentThreadName(thrd->name);

    ASSERT(thrd->threadFn);
    Atomic::StoreExplicit(&thrd->running, 1, AtomicMemoryOrder::Release);
    thrd->sem.Post();
    DWORD r = static_cast<DWORD>(thrd->threadFn(thrd->userData));
    Atomic::StoreExplicit(&thrd->running, 0, AtomicMemoryOrder::Release);

    return r;
}

Thread::Thread()
{
    ThreadImpl* thrd = reinterpret_cast<ThreadImpl*>(mData);
    thrd->threadFn = nullptr;
    thrd->handle = nullptr;
    thrd->userData = nullptr;
    thrd->stackSize = 0;
    thrd->name[0] = 0;
    thrd->tId = 0;
    thrd->running = 0;
    thrd->init = false;
}

bool Thread::Start(const ThreadDesc& desc)
{
    ThreadImpl* thrd = reinterpret_cast<ThreadImpl*>(mData);
    ASSERT(thrd->handle == nullptr && !thrd->init);

    thrd->sem.Initialize();
    thrd->threadFn = desc.entryFn;
    thrd->userData = desc.userData;
    thrd->stackSize = Max<size_t>(desc.stackSize, 64*SIZE_KB);
    Str::Copy(thrd->name, sizeof(thrd->name), desc.name ? desc.name : "");

    thrd->handle = CreateThread(nullptr, thrd->stackSize, (LPTHREAD_START_ROUTINE)_ThreadStubFn, thrd, 0, nullptr);
    if (thrd->handle == nullptr) {
        thrd->sem.Release();
        return false;
    }
    ASSERT_ALWAYS(thrd->handle != nullptr, "CreateThread failed");

    thrd->sem.Wait();   // Ensure that thread callback is init
    thrd->init = true;

    _private::CountersAddThread(thrd->stackSize);

    return true;
}

int Thread::Stop()
{
    ThreadImpl* thrd = reinterpret_cast<ThreadImpl*>(mData);
    DWORD exitCode = 0;
    if (thrd->handle != nullptr) {
        ASSERT_MSG(thrd->init, "Thread is not init!");

        WaitForSingleObject(thrd->handle, INFINITE);
        GetExitCodeThread(thrd->handle, &exitCode);
        CloseHandle(thrd->handle);
        thrd->sem.Release();

        thrd->handle = nullptr;
    }

    thrd->init = false;

    _private::CountersRemoveThread(thrd->stackSize);

    return static_cast<int>(exitCode);
}

bool Thread::IsRunning()
{
    ThreadImpl* thrd = reinterpret_cast<ThreadImpl*>(mData);
    return Atomic::LoadExplicit(&thrd->running, AtomicMemoryOrder::Acquire) == 1;
}

void Thread::SetPriority(ThreadPriority prio)
{
    ThreadImpl* thrd = reinterpret_cast<ThreadImpl*>(mData);

    int prioWin = 0;
    switch (prio) {
    case ThreadPriority::Normal:    prioWin = THREAD_PRIORITY_NORMAL; break;
    case ThreadPriority::Idle:      prioWin = THREAD_PRIORITY_IDLE; break;
    case ThreadPriority::Realtime:  prioWin = THREAD_PRIORITY_TIME_CRITICAL; break;
    case ThreadPriority::High:      prioWin = THREAD_PRIORITY_HIGHEST; break;
    case ThreadPriority::Low:       prioWin = THREAD_PRIORITY_LOWEST; break;
    }

    [[maybe_unused]] BOOL r = SetThreadPriority(thrd->handle, prioWin);
    ASSERT(r);
}

void Thread::SwitchContext()
{
    SwitchToThread();
}

uint32 Thread::GetCurrentId()
{
    return GetCurrentThreadId();
}

void Thread::Sleep(uint32 msecs)
{
    ::Sleep((DWORD)msecs);
}

void Thread::SetCurrentThreadPriority(ThreadPriority prio)
{
    int prioWin = 0;
    switch (prio) {
    case ThreadPriority::Normal:    prioWin = THREAD_PRIORITY_NORMAL; break;
    case ThreadPriority::Idle:      prioWin = THREAD_PRIORITY_IDLE; break;
    case ThreadPriority::Realtime:  prioWin = THREAD_PRIORITY_TIME_CRITICAL; break;
    case ThreadPriority::High:      prioWin = THREAD_PRIORITY_HIGHEST; break;
    case ThreadPriority::Low:       prioWin = THREAD_PRIORITY_LOWEST; break;
    }

    [[maybe_unused]] BOOL r = SetThreadPriority(GetCurrentThread(), prioWin);
    ASSERT(r);
}

void Thread::SetCurrentThreadName(const char* name)
{
    wchar_t namew[32];
    Str::Utf8ToWide(name, namew, sizeof(namew));
    SetThreadDescription(GetCurrentThread(), namew);

    #if TRACY_ENABLE
    TracyCSetThreadName(name);
    #endif
}

void Thread::GetCurrentThreadName(char* nameOut, uint32 nameSize)
{
    PWSTR namew;
    if (SUCCEEDED(GetThreadDescription(GetCurrentThread(), &namew)))
        Str::WideToUtf8(namew, nameOut, nameSize);
    else 
        nameOut[0] = 0;
}


struct MutexImpl 
{
    CRITICAL_SECTION handle;
};
static_assert(sizeof(MutexImpl) <= sizeof(Mutex), "Mutex size mismatch");

void Mutex::Initialize(uint32 spinCount)
{
    MutexImpl* _m = reinterpret_cast<MutexImpl*>(mData);
    [[maybe_unused]] BOOL r = InitializeCriticalSectionAndSpinCount(&_m->handle, spinCount);
    ASSERT_ALWAYS(r, "InitializeCriticalSection failed");

    _private::CountersAddMutex();
}

void Mutex::Release()
{
    MutexImpl* _m = reinterpret_cast<MutexImpl*>(mData);
    DeleteCriticalSection(&_m->handle);

    _private::CountersRemoveMutex();
}

void Mutex::Enter()
{
    MutexImpl* _m = reinterpret_cast<MutexImpl*>(mData);
    EnterCriticalSection(&_m->handle);
}

void Mutex::Exit()
{
    MutexImpl* _m = reinterpret_cast<MutexImpl*>(mData);
    LeaveCriticalSection(&_m->handle);
}

bool Mutex::TryEnter()
{
    MutexImpl* _m = reinterpret_cast<MutexImpl*>(mData);
    return TryEnterCriticalSection(&_m->handle) == TRUE;
}


struct ReadWriteMutexImpl
{
    SRWLOCK handle;
};
static_assert(sizeof(ReadWriteMutexImpl) < sizeof(ReadWriteMutex), "ReadWriteMutex mismatch");

void ReadWriteMutex::Initialize()
{
    ReadWriteMutexImpl* m = reinterpret_cast<ReadWriteMutexImpl*>(mData);
    InitializeSRWLock(&m->handle);
}

void ReadWriteMutex::Release()
{
}

bool ReadWriteMutex::TryRead()
{
    ReadWriteMutexImpl* m = reinterpret_cast<ReadWriteMutexImpl*>(mData);
    return TryAcquireSRWLockShared(&m->handle) != 0;
}

bool ReadWriteMutex::TryWrite()
{
    ReadWriteMutexImpl* m = reinterpret_cast<ReadWriteMutexImpl*>(mData);
    return TryAcquireSRWLockExclusive(&m->handle) != 0;
}

void ReadWriteMutex::EnterRead()
{
    ReadWriteMutexImpl* m = reinterpret_cast<ReadWriteMutexImpl*>(mData);
    AcquireSRWLockShared(&m->handle);
}

void ReadWriteMutex::ExitRead()
{
    ReadWriteMutexImpl* m = reinterpret_cast<ReadWriteMutexImpl*>(mData);
    ReleaseSRWLockShared(&m->handle);
}

void ReadWriteMutex::EnterWrite()
{
    ReadWriteMutexImpl* m = reinterpret_cast<ReadWriteMutexImpl*>(mData);
    AcquireSRWLockExclusive(&m->handle);
}

void ReadWriteMutex::ExitWrite()
{
    ReadWriteMutexImpl* m = reinterpret_cast<ReadWriteMutexImpl*>(mData);
    ReleaseSRWLockExclusive(&m->handle);
}


struct SemaphoreImpl 
{
    HANDLE handle;
};
static_assert(sizeof(SemaphoreImpl) <= sizeof(Semaphore), "Sempahore size mismatch");

void Semaphore::Initialize()
{
    SemaphoreImpl* _sem = reinterpret_cast<SemaphoreImpl*>(mData);
    _sem->handle = CreateSemaphoreA(nullptr, 0, LONG_MAX, nullptr);
    ASSERT_ALWAYS(_sem->handle != INVALID_HANDLE_VALUE, "Failed to create semaphore");

    _private::CountersAddSemaphore();
}

void Semaphore::Release()
{
    SemaphoreImpl* _sem = reinterpret_cast<SemaphoreImpl*>(mData);
    if (_sem->handle != INVALID_HANDLE_VALUE) {
        CloseHandle(_sem->handle);
        _sem->handle = INVALID_HANDLE_VALUE;

        _private::CountersRemoveSemaphore();
    }
}

void Semaphore::Post(uint32 count)
{
    SemaphoreImpl* _sem = reinterpret_cast<SemaphoreImpl*>(mData);
    ASSERT(_sem->handle != INVALID_HANDLE_VALUE);
    ReleaseSemaphore(_sem->handle, count, nullptr);
}

bool Semaphore::Wait(uint32 msecs)
{
    SemaphoreImpl* _sem = reinterpret_cast<SemaphoreImpl*>(mData);
    ASSERT(_sem->handle != INVALID_HANDLE_VALUE);
    return WaitForSingleObject(_sem->handle, (DWORD)msecs) == WAIT_OBJECT_0;
}


struct SignalImpl 
{
    CRITICAL_SECTION mutex;
    CONDITION_VARIABLE cond;
    int value;
};
static_assert(sizeof(SignalImpl) <= sizeof(Signal), "Signal size mismatch");

void Signal::Initialize()
{
    SignalImpl* _sig = reinterpret_cast<SignalImpl*>(mData);
    [[maybe_unused]] BOOL r = InitializeCriticalSectionAndSpinCount(&_sig->mutex, 32);
    ASSERT_ALWAYS(r, "InitializeCriticalSectionAndSpinCount failed");
    InitializeConditionVariable(&_sig->cond);
    _sig->value = 0;

    _private::CountersAddSignal();
}

void Signal::Release()
{
    SignalImpl* _sig = reinterpret_cast<SignalImpl*>(mData);
    DeleteCriticalSection(&_sig->mutex);

    _private::CountersRemoveSignal();
}

void Signal::Raise()
{
    SignalImpl* _sig = reinterpret_cast<SignalImpl*>(mData);
    WakeConditionVariable(&_sig->cond);
}

void Signal::RaiseAll()
{
    SignalImpl* _sig = reinterpret_cast<SignalImpl*>(mData);
    WakeAllConditionVariable(&_sig->cond);
}

bool Signal::Wait(uint32 msecs)
{
    SignalImpl* _sig = reinterpret_cast<SignalImpl*>(mData);

    bool timedOut = false;
    EnterCriticalSection(&_sig->mutex);
    while (_sig->value == 0) {
        int r = SleepConditionVariableCS(&_sig->cond, &_sig->mutex, (DWORD)msecs);
        if (!r && GetLastError() == ERROR_TIMEOUT) {
            timedOut = true;
            break;
        }
    }
    if (!timedOut)
        _sig->value = 0;
    LeaveCriticalSection(&_sig->mutex);
    return !timedOut;
}

void Signal::Decrement(uint32 count)
{
    SignalImpl* _sig = reinterpret_cast<SignalImpl*>(mData);
    EnterCriticalSection(&_sig->mutex);
    _sig->value -= int(count);
    LeaveCriticalSection(&_sig->mutex);
}

void Signal::Increment(uint32 count)
{
    SignalImpl* _sig = reinterpret_cast<SignalImpl*>(mData);
    EnterCriticalSection(&_sig->mutex);
    _sig->value += int(count);
    LeaveCriticalSection(&_sig->mutex);
}

bool Signal::WaitOnCondition(bool(*condFn)(int value, int reference), int reference, uint32 msecs)
{
    SignalImpl* _sig = reinterpret_cast<SignalImpl*>(mData);

    bool timedOut = false;
    EnterCriticalSection(&_sig->mutex);
    while (condFn(_sig->value, reference)) {
        int r = SleepConditionVariableCS(&_sig->cond, &_sig->mutex, (DWORD)msecs);
        if (!r && GetLastError() == ERROR_TIMEOUT) {
            timedOut = true;
            break;
        }
    }
    if (!timedOut)
        _sig->value = reference;
    LeaveCriticalSection(&_sig->mutex);
    return !timedOut;
}

void Signal::Set(int value)
{
    SignalImpl* _sig = reinterpret_cast<SignalImpl*>(mData);

    EnterCriticalSection(&_sig->mutex);
    _sig->value = value;
    LeaveCriticalSection(&_sig->mutex);
}

struct TimerState
{
    bool init;
    LARGE_INTEGER freq;
    LARGE_INTEGER start;
};
static TimerState gTimer;

FORCE_INLINE int64 timerInt64MulDiv(int64 value, int64 numer, int64 denom) 
{
    int64 q = value / denom;
    int64 r = value % denom;
    return q * numer + r * numer / denom;
}

void Timer::Initialize() 
{
    gTimer.init = true;
    
    QueryPerformanceFrequency(&gTimer.freq);
    QueryPerformanceCounter(&gTimer.start);
}

uint64 Timer::GetTicks() 
{
    ASSERT_MSG(gTimer.init, "Timer not initialized. call timerInitialize()");
    
    LARGE_INTEGER li;
    QueryPerformanceCounter(&li);
    return timerInt64MulDiv(li.QuadPart - gTimer.start.QuadPart, 1000000000, gTimer.freq.QuadPart);
}

struct UUIDImpl
{
    GUID guid;
};
static_assert(sizeof(UUIDImpl) <= sizeof(UniqueID), "UUID size mismatch");

bool UniqueID::operator==(const UniqueID& uuid) const
{
    return memcmp(data, uuid.data, sizeof(UUIDImpl)) == 0;
}

bool UniqueID::Generate(UniqueID* _uuid)
{
    _LoadOle32();

    UUIDImpl* uuid = reinterpret_cast<UUIDImpl*>(_uuid);
    if (gOle32.CoCreateGuid(&uuid->guid) != S_OK)
    return false;

    return true;
}

bool UniqueID::ToString(const UniqueID& _uuid, char* str, uint32 size)
{
    _LoadOle32();

    const UUIDImpl& uuid = reinterpret_cast<const UUIDImpl&>(_uuid);
    wchar_t guidStr[39];

    gOle32.StringFromGUID2(uuid.guid, guidStr, CountOf(guidStr));
    if (WideCharToMultiByte(CP_UTF8, 0, guidStr, -1, str, size, nullptr, nullptr) == 0)
    return false;

    uint32 len = Str::Len(str);
    if (str[0] == '{') {
        memmove(str, str + 1, len + 1);
        --len;
    }
    if (str[len - 1] == '}')
    str[len - 1] = 0;
    return true;
}

bool UniqueID::FromString(UniqueID* _uuid, const char* str)
{
    _LoadOle32();

    ASSERT(str);

    if (str[0] == 0)
    return false;

    char strTmp[64] {};

    uint32 len = Str::Len(str);
    if (str[0] != '{') {
        strTmp[0] = '{';
        Str::Concat(strTmp, sizeof(strTmp), str);
        if (str[len - 1] != '}') 
        Str::Concat(strTmp, sizeof(strTmp), "}");
    }
    else {
        ASSERT(str[len - 1] == '}');
        Str::Copy(strTmp, sizeof(strTmp), str);
    }        

    UUIDImpl* uuid = reinterpret_cast<UUIDImpl*>(_uuid);
    wchar_t guidStr[64];
    if (MultiByteToWideChar(CP_UTF8, 0, strTmp, -1, guidStr, sizeof(guidStr)) == 0) 
    return false;
    if (gOle32.CLSIDFromString(guidStr, &uuid->guid) != S_OK) 
    return false;
    return true;
}



OSDLL OS::LoadDLL(const char* filepath, char** pErrorMsg)
{
    OSDLL dll = (OSDLL)LoadLibraryA(filepath);
    if (dll == nullptr && pErrorMsg) {
        static char errMsg[64];
        Str::PrintFmt(errMsg, sizeof(errMsg), "GetLastError: %u", GetLastError());
        *pErrorMsg = errMsg;
    }
    else {
        if (pErrorMsg) 
            *pErrorMsg = nullptr;
    }
    return dll;
}

void OS::UnloadDLL(OSDLL dll)
{
    if (dll)
        FreeLibrary((HMODULE)dll);
}

void* OS::GetSymbolAddress(OSDLL dll, const char* symbolName)
{
    return (void*)GetProcAddress((HMODULE)dll, symbolName);
}

size_t OS::GetPageSize()
{
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    return (size_t)si.dwPageSize;
}

bool OS::Win32GetRegisterLocalMachineString(const char* subkey, const char* value, char* dst, size_t dstSize)
{
    _LoadAdvApi32();

    DWORD dataSize = (DWORD)dstSize;
    return gAdvApi32.RegGetValueA(HKEY_LOCAL_MACHINE, subkey, value, RRF_RT_REG_SZ|RRF_RT_REG_EXPAND_SZ, nullptr, dst, &dataSize) == ERROR_SUCCESS;
}

void OS::GetSysInfo(SysInfo* info)
{
    memset(info, 0x0, sizeof(*info));

    struct i4 
    {
        int i[4];
    };

    i4 cpui;
    Array<i4> data;
    Array<i4> extData;
    int ids;
    int extIds;
    uint32 f_1_ECX_ = 0;
    uint32 f_1_EDX_ = 0;
    uint32 f_7_EBX_ = 0;
    uint32 f_7_ECX_ = 0;
    uint32 f_81_ECX_ = 0;
    uint32 f_81_EDX_ = 0;

    __cpuid(cpui.i, 0);
    ids = cpui.i[0];
    for (int i = 0; i <= ids; i++) {
        __cpuidex(cpui.i, i, 0);
        memcpy(data.Push(), cpui.i, sizeof(cpui));
    }

    char vendor[0x20];
    memset(vendor, 0x0, sizeof(vendor));
    *(int*)(vendor) = data[0].i[1];
    *(int*)(vendor + 4) = data[0].i[3];
    *(int*)(vendor + 8) = data[0].i[2];
    
    Str::Copy(info->cpuName, sizeof(info->cpuName), vendor);
    
    if (ids >= 1) {
        f_1_ECX_ = static_cast<uint32>(data[1].i[2]);
        f_1_EDX_ = static_cast<uint32>(data[1].i[3]);
    }

    if (ids >= 7) {
        f_7_EBX_ = data[7].i[1];
        f_7_ECX_ = data[7].i[2];
    }

    __cpuid(cpui.i, 0x80000000);
    extIds = cpui.i[0];
    
    char brand[0x40];
    memset(brand, 0, sizeof(brand));
    
    for (int i = 0x80000000; i <= extIds; ++i)
    {
        __cpuidex(cpui.i, i, 0);
        memcpy(extData.Push(), cpui.i, sizeof(cpui));
    }
    
    if (extIds >= 0x80000001)
    {
        f_81_ECX_ = extData[1].i[2];
        f_81_EDX_ = extData[1].i[3];
    }
    
    if (extIds >= 0x80000004)
    {
        memcpy(brand, extData[2].i, sizeof(cpui));
        memcpy(brand + 16, extData[3].i, sizeof(cpui));
        memcpy(brand + 32, extData[4].i, sizeof(cpui));
    }

    Str::Copy(info->cpuModel, sizeof(info->cpuModel), brand);
    Str::Trim(info->cpuModel, sizeof(info->cpuModel), info->cpuModel);

    #if CPU_X86
        info->cpuFamily = SysInfo::CpuFamily::x86_64;
    #else
        info->cpuFamily = SysInfo::CpuFamily::ARM64;
    #endif
    info->cpuCapsSSE = ((f_1_EDX_ >> 25) & 0x1) ? true : false;
    info->cpuCapsSSE2 = ((f_1_EDX_ >> 26) & 0x1) ? true : false;
    info->cpuCapsSSE3 = (f_1_ECX_ & 0x1) ? true : false;
    info->cpuCapsSSE41 = ((f_1_ECX_ >> 19) & 0x1) ? true : false;
    info->cpuCapsSSE42 = ((f_1_ECX_ >> 20) & 0x1) ? true : false;
    info->cpuCapsAVX = ((f_1_ECX_ >> 28) & 0x1) ? true : false;
    info->cpuCapsAVX2 = ((f_7_EBX_ >> 5) & 0x1) ? true : false;
    info->cpuCapsAVX512 = ((f_7_EBX_ >> 16) & 0x1) ? true : false;

    SYSTEM_INFO sysinfo;
    GetSystemInfo(&sysinfo);
    
    info->pageSize = sysinfo.dwPageSize;

    {
        SYSTEM_LOGICAL_PROCESSOR_INFORMATION* buffer = nullptr;
        DWORD returnLen = 0;
        DWORD coreCount = 0;
        if (!GetLogicalProcessorInformation(buffer, &returnLen)) {
            if (GetLastError() == ERROR_INSUFFICIENT_BUFFER)
                buffer = (SYSTEM_LOGICAL_PROCESSOR_INFORMATION*)Mem::Alloc(returnLen);
        }

        if (buffer != nullptr && GetLogicalProcessorInformation(buffer, &returnLen)) {
            SYSTEM_LOGICAL_PROCESSOR_INFORMATION* ptr = buffer;
            DWORD byteOffset = 0;
            while (byteOffset + sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION) <= returnLen) {
                if (ptr->Relationship == RelationProcessorCore) {
                    ++coreCount;
                }

                if (ptr->Relationship == RelationCache) {
                    const CACHE_DESCRIPTOR& cache = ptr->Cache;
                    if (cache.Type == CacheUnified || cache.Type == CacheData) {
                        SysInfo::CacheInfo* cacheInfo = nullptr;
                        switch (cache.Level) {
                            case 1:  cacheInfo = &info->L1Cache;   break;
                            case 2:  cacheInfo = &info->L2Cache;   break;
                            case 3:  cacheInfo = &info->L3Cache;   break;
                        }
                        ++cacheInfo->count;
                        cacheInfo->kway = cache.Associativity;
                        cacheInfo->lineSize = cache.LineSize;
                        cacheInfo->size = cache.Size;
                    }
                }

                byteOffset += sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION);
                ++ptr;
            }
        }

        Mem::Free(buffer);

        ASSERT(coreCount);
        ASSERT_MSG(coreCount <= _limits::SYS_MAX_CORES, "CPU core count appears to be too high (%u). Consider increasing SYS_MAX_CORES", coreCount);
        coreCount = Clamp<uint32>(coreCount, 1, _limits::SYS_MAX_CORES);
        
        info->coreCount = coreCount;       
    }

    ULONGLONG memSizeKb;
    if (GetPhysicallyInstalledSystemMemory(&memSizeKb)) 
        info->physicalMemorySize = memSizeKb * 1024;

    data.Free();
    extData.Free();
}

#if PLATFORM_PC
OSProcess::OSProcess() :
    mProcess(INVALID_HANDLE_VALUE),
    mStdOutPipeRead(INVALID_HANDLE_VALUE),
    mStdErrPipeRead(INVALID_HANDLE_VALUE)
{
}

OSProcess::~OSProcess()
{
    if (mStdOutPipeRead != INVALID_HANDLE_VALUE) 
        CloseHandle(mStdOutPipeRead);
    if (mStdErrPipeRead != INVALID_HANDLE_VALUE)
        CloseHandle(mStdErrPipeRead);
    if (mProcess != INVALID_HANDLE_VALUE)
        CloseHandle(mProcess);
}

bool OSProcess::Run(const char* cmdline, OSProcessFlags flags, const char* cwd)
{
    ASSERT(mProcess == INVALID_HANDLE_VALUE);

    HANDLE stdOutPipeWrite = INVALID_HANDLE_VALUE;
    HANDLE stdErrPipeWrite = INVALID_HANDLE_VALUE;
    BOOL r;
    BOOL inheritHandles = (flags & OSProcessFlags::InheritHandles) == OSProcessFlags::InheritHandles ? TRUE : FALSE;

    if ((flags & OSProcessFlags::CaptureOutput) == OSProcessFlags::CaptureOutput) {
        SECURITY_ATTRIBUTES saAttr {}; 
        saAttr.nLength = sizeof(SECURITY_ATTRIBUTES); 
        saAttr.bInheritHandle = inheritHandles; 

        r = CreatePipe(&mStdOutPipeRead, &stdOutPipeWrite, &saAttr, 0);
        ASSERT_MSG(r, "CreatePipe failed");

        r = CreatePipe(&mStdErrPipeRead, &stdErrPipeWrite, &saAttr, 0);
        ASSERT_MSG(r, "CreatePipe failed");

        if (inheritHandles) {
            r = SetHandleInformation(mStdOutPipeRead, HANDLE_FLAG_INHERIT, 0);
            ASSERT_MSG(r, "SetHandleInformation for pipe failed");
            r = SetHandleInformation(mStdErrPipeRead, HANDLE_FLAG_INHERIT, 0);
            ASSERT_MSG(r, "SetHandleInformation for pipe failed");
        }
    }

    PROCESS_INFORMATION procInfo {};
    STARTUPINFOA startInfo {};
    startInfo.cb = sizeof(startInfo);
    if ((flags & OSProcessFlags::CaptureOutput) == OSProcessFlags::CaptureOutput) {
        startInfo.dwFlags = STARTF_USESTDHANDLES;
        startInfo.hStdOutput = stdOutPipeWrite;
        startInfo.hStdError = stdErrPipeWrite;
        startInfo.hStdInput = INVALID_HANDLE_VALUE; // TODO
    }

    MemTempAllocator tmpAlloc;
    char* cmdLineCopy = Mem::AllocCopy<char>(cmdline, Str::Len(cmdline)+1, &tmpAlloc);
    DWORD createProcessFlags = 0; // TODO

    if ((flags & OSProcessFlags::DontCreateConsole) == OSProcessFlags::DontCreateConsole) 
        createProcessFlags |= CREATE_NO_WINDOW;
    if ((flags & OSProcessFlags::ForceCreateConsole) == OSProcessFlags::ForceCreateConsole)
        createProcessFlags |= CREATE_NEW_CONSOLE;

    r = CreateProcessA(nullptr, cmdLineCopy, nullptr, nullptr, inheritHandles, createProcessFlags, NULL, cwd, &startInfo, &procInfo);
    if (!r) {
        LOG_ERROR("Run process failed: %s", cmdline);
        return false;
    }

    CloseHandle(procInfo.hThread);
    mProcess = procInfo.hProcess;

    if ((flags & OSProcessFlags::CaptureOutput) == OSProcessFlags::CaptureOutput) {
        CloseHandle(stdOutPipeWrite);
        CloseHandle(stdErrPipeWrite);
    }

    return true;
}

void OSProcess::Wait() const
{
    ASSERT(mProcess != INVALID_HANDLE_VALUE);
    WaitForSingleObject(mProcess, INFINITE);
}

bool OSProcess::IsRunning() const
{
    ASSERT(mProcess != INVALID_HANDLE_VALUE);
    return WaitForSingleObject(mProcess, 0) != WAIT_OBJECT_0;
}

bool OSProcess::IsValid() const
{
    return mProcess != INVALID_HANDLE_VALUE;
}

static void _TerminateChildProcesses(DWORD parentProcessId) 
{
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapshot != INVALID_HANDLE_VALUE) {
        PROCESSENTRY32 pe { sizeof(PROCESSENTRY32) };

        if (Process32First(hSnapshot, &pe)) {
            do {
                if (pe.th32ParentProcessID == parentProcessId) {
                    HANDLE childProcess = OpenProcess(PROCESS_TERMINATE, TRUE, pe.th32ProcessID);
                    if (childProcess) {
                        LOG_DEBUG("Terminating child process: %u (%s)", pe.th32ProcessID, pe.szExeFile);
                        _TerminateChildProcesses(pe.th32ProcessID);

                        TerminateProcess(childProcess, 1);
                        CloseHandle(childProcess);
                    }
                }
            } while (Process32Next(hSnapshot, &pe));
        }

        CloseHandle(hSnapshot);
    }
};

void OSProcess::Abort()
{
    ASSERT(mProcess != INVALID_HANDLE_VALUE);

    DWORD processId = GetProcessId(mProcess);
    _TerminateChildProcesses(processId);

    BOOL r = TerminateProcess(mProcess, 1);
    if (!r) {
        LOG_ERROR("Process failed to terminate: 0x%x (ErrorCode: %u)", mProcess, GetLastError());
    }
    else {
        mProcess = INVALID_HANDLE_VALUE;
    }
}

int OSProcess::GetExitCode() const
{
    ASSERT(mProcess != INVALID_HANDLE_VALUE);
    DWORD exitCode = UINT32_MAX;
    GetExitCodeProcess(mProcess, &exitCode);
    return static_cast<int>(exitCode);
}

uint32 OSProcess::ReadStdOut(void* data, uint32 size) const
{
    ASSERT(mStdOutPipeRead != INVALID_HANDLE_VALUE);

    DWORD bytesRead;
    BOOL r = ReadFile((HANDLE)mStdOutPipeRead, data, size, &bytesRead, nullptr);
    return (r && bytesRead) ? bytesRead : 0; 
}

uint32 OSProcess::ReadStdErr(void* data, uint32 size) const
{
    ASSERT(mStdErrPipeRead != INVALID_HANDLE_VALUE);

    DWORD bytesRead;
    BOOL r = ReadFile((HANDLE)mStdErrPipeRead, data, size, &bytesRead, nullptr);
    return (r && bytesRead) ? bytesRead : 0;
}
#endif  // PLATFORM_PC

bool OS::Win32IsProcessRunning(const char* execName)
{
    PROCESSENTRY32 entry { sizeof(PROCESSENTRY32) };

    char execNameTrimmed[PATH_CHARS_MAX];
    Str::Trim(execNameTrimmed, sizeof(execNameTrimmed), execName, '\'');
    Str::Trim(execNameTrimmed, sizeof(execNameTrimmed), execNameTrimmed, '"');

    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, TH32CS_SNAPPROCESS);
    if (!Process32First(snapshot, &entry)) {
        CloseHandle(snapshot);
        return false;
    }

    bool isRunning = false;
    do {
        if constexpr (sizeof(CHAR) == 2) {
            char exeFile[MAX_PATH];
            if (Str::WideToUtf8((const wchar_t*)entry.szExeFile, exeFile, sizeof(exeFile)))
                isRunning = Str::IsEqualNoCase(exeFile, execNameTrimmed);
        }
        else {
            isRunning = Str::IsEqualNoCase((const char*)entry.szExeFile, execNameTrimmed);
        }
    } while (!isRunning && Process32Next(snapshot, &entry));

    CloseHandle(snapshot);
    return false;
}

OSWin32ShellExecuteResult OS::Win32ShellExecute(const char* filepath, const char* args, 
                                                const char* cwd, OSWin32ShowWindow showFlag, 
                                                const char* operation,
                                                void** pInstance)
{
    _LoadShell32();

    HINSTANCE hInst = gShell32.ShellExecuteA(nullptr, operation, filepath, args, cwd, (INT)showFlag);

    INT_PTR errCode = INT_PTR(hInst);
    if (errCode <= 32) {
        switch (errCode) {
        case 0:
        case SE_ERR_OOM:
            return OSWin32ShellExecuteResult::OutOfMemory;
        case SE_ERR_DLLNOTFOUND:
        case SE_ERR_FNF:
            return OSWin32ShellExecuteResult::FileNotFound;
        case SE_ERR_PNF:
            return OSWin32ShellExecuteResult::PathNotFound;
        case ERROR_BAD_FORMAT:
            return OSWin32ShellExecuteResult::BadFormat;
        case SE_ERR_ASSOCINCOMPLETE:
        case SE_ERR_NOASSOC:
            return OSWin32ShellExecuteResult::NoAssociation;
        case SE_ERR_ACCESSDENIED:
            return OSWin32ShellExecuteResult::AccessDenied;
        default:
            return OSWin32ShellExecuteResult::UnknownError;
        }
    }
    else {
        if (pInstance)
            *pInstance = hInst;
        return OSWin32ShellExecuteResult::Ok;
    }
}


bool OS::SetEnvVar(const char* name, const char* value)
{
    return SetEnvironmentVariableA(name, value) == TRUE;
}

bool OS::GetEnvVar(const char* name, char* outValue, uint32 valueSize)
{
    DWORD dwValueSize = GetEnvironmentVariableA(name, outValue, valueSize);
    return dwValueSize != 0 && dwValueSize < valueSize;
}

bool OS::IsDebuggerPresent()
{
    return ::IsDebuggerPresent();
}

void OS::Win32PrintToDebugger(const char* text)
{
    OutputDebugStringA(text);
}

bool OS::Win32SetPrivilege(const char* name, bool enable)
{
    _LoadAdvApi32();

    HANDLE tokenHandle;
    TOKEN_PRIVILEGES tp;

    if (!gAdvApi32.OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &tokenHandle)) 
        return false;

    if (!gAdvApi32.LookupPrivilegeValueA(nullptr, name, &tp.Privileges[0].Luid)) 
        return false;
    tp.PrivilegeCount = 1;

    if (enable) 
        tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
    else
        tp.Privileges[0].Attributes = 0;

    BOOL status = gAdvApi32.AdjustTokenPrivileges(tokenHandle, FALSE, &tp, 0, nullptr, 0);
    DWORD error = GetLastError();
    if (!status || error != ERROR_SUCCESS) {
        LOG_ERROR("AdjustTokenPrivileges failed. Code: %u", error);
    }
    
    CloseHandle(tokenHandle);
    return true;
}

char* OS::GetMyPath(char* dst, size_t dstSize)
{
    GetModuleFileNameA(NULL, dst, (DWORD)dstSize);
    return dst;
}

char* OS::GetAbsolutePath(const char* path, char* dst, size_t dstSize)
{
    if (GetFullPathNameA(path, (DWORD)dstSize, dst, NULL) == 0)
        dst[0] = '\0';
    return dst;
}

char* OS::GetCurrentDir(char* dst, size_t dstSize)
{
    GetCurrentDirectoryA((DWORD)dstSize, dst);
    return dst;
}

void OS::SetCurrentDir(const char* path)
{
    SetCurrentDirectoryA(path);
}

bool OS::CreateDir(const char* path)
{
    return bool(CreateDirectoryA(path, nullptr)); 
}

bool OS::CopyPath(const char *srcPath, const char *destPath)
{
    return bool(CopyFileA(srcPath, destPath, FALSE));
}

bool OS::MovePath(const char* src, const char* dest)
{
    return bool(MoveFileExA(src, dest, MOVEFILE_REPLACE_EXISTING|MOVEFILE_COPY_ALLOWED));
}

char* OS::GetHomeDir(char* dst, size_t dstSize)
{
    _LoadOle32();
    _LoadShell32();

    PWSTR homeDir = nullptr;
    if (SUCCEEDED(gShell32.SHGetKnownFolderPath(FOLDERID_Profile, 0, nullptr, &homeDir))) {
        Str::WideToUtf8(homeDir, dst, (uint32)dstSize);
        gOle32.CoTaskMemFree(homeDir);
        return dst;
    }
    else {
        ASSERT_MSG(0, "Getting home directory failed");
        return nullptr;
    }
}

char* OS::GetCacheDir(char* dst, size_t dstSize, const char* appName)
{
    _LoadOle32();
    _LoadShell32();

    PWSTR homeDir = nullptr;
    if (SUCCEEDED(gShell32.SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, nullptr, &homeDir))) {
        char homeDirUtf8[CONFIG_MAX_PATH];
        Str::WideToUtf8(homeDir, homeDirUtf8, sizeof(homeDirUtf8));
        gOle32.CoTaskMemFree(homeDir);
        PathUtils::Join(dst, dstSize, homeDirUtf8, appName);
        return dst;
    }
    else {
        ASSERT_MSG(0, "Getting LOCALAPPDATA directory failed");
        return nullptr;
    }
}

bool OS::MakeTempPath(char* dst, [[maybe_unused]] size_t dstSize, const char* namePrefix, const char* dir)
{
    static char osTempPath[PATH_CHARS_MAX] = {};
    if (dir == nullptr) {
        if (osTempPath[0] == '\0')
            GetTempPathA(sizeof(osTempPath), osTempPath);
        dir = osTempPath;
    }

    ASSERT(dstSize >= PATH_CHARS_MAX);
    return GetTempFileNameA(dir, namePrefix, 0, dst) != 0;
}

bool OS::DeletePath(const char* path)
{
    ASSERT(path);
    return DeleteFileA(path);
}

char* OS::Win32GetFolder(OSWin32Folder folder, char* dst, size_t dstSize)
{
    _LoadOle32();
    _LoadShell32();

    static const KNOWNFOLDERID folderIds[] = {
        FOLDERID_Documents,
        FOLDERID_Fonts,
        FOLDERID_Downloads,
        FOLDERID_RoamingAppData,
        FOLDERID_LocalAppData,
        FOLDERID_ProgramFiles,
        FOLDERID_System,
        FOLDERID_CommonStartup,
        FOLDERID_Desktop
    };
    static_assert(CountOf(folderIds) == uint32(OSWin32Folder::_Count));

    PWSTR folderPath = nullptr;
    if (SUCCEEDED(gShell32.SHGetKnownFolderPath(folderIds[uint32(folder)], 0, nullptr, &folderPath))) {
        Str::WideToUtf8(folderPath, dst, (uint32)dstSize);
        gOle32.CoTaskMemFree(folderPath);
        return dst;
    }
    else {
        ASSERT_MSG(0, "SHGetKnownFolderPath failed");
        return nullptr;
    }
}

void OS::Win32EnableProgramConsoleCoding()
{
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD consoleMode = 0;
    GetConsoleMode(hStdOut, &consoleMode);
    consoleMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING | ENABLE_PROCESSED_OUTPUT;
    [[maybe_unused]] BOOL r = SetConsoleMode(hStdOut, consoleMode);
    ASSERT(r);
}

PathInfo OS::GetPathInfo(const char* path)
{
    WIN32_FILE_ATTRIBUTE_DATA fad;
    if (!GetFileAttributesExA(path, GetFileExInfoStandard, &fad)) {
        return PathInfo { .type = PathType::Invalid };
    }

    PathType type = PathType::Invalid;
    if (fad.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        type = PathType::Directory;
    else if (!(fad.dwFileAttributes & (FILE_ATTRIBUTE_DEVICE | FILE_ATTRIBUTE_SYSTEM)))
        type = PathType::File;

    LARGE_INTEGER size;
    size.HighPart = fad.nFileSizeHigh;
    size.LowPart = fad.nFileSizeLow;

    LARGE_INTEGER tm;
    tm.HighPart = fad.ftLastWriteTime.dwHighDateTime;
    tm.LowPart = fad.ftLastWriteTime.dwLowDateTime;

    return PathInfo {
        .type = type,
        .size = static_cast<uint64>(size.QuadPart),
        .lastModified = static_cast<uint64>(tm.QuadPart / 10000000 - 11644473600LL)
    };
}

                                                                                                                                                
struct OSWin32PipeInternal : OSWin32Pipe
{
    Mutex mPendingWritesMtx;
	Thread mThread;
    Array<Span<uint8>> mPendingWrites;
	String32 mName;
	HANDLE mHandle;
	size_t mInputBufferSize;
	uint8* mInputBuffer;
    uint32 mReadTimeout;
	bool mSendPing;
	bool mIsConnected;
	AtomicUint32 mQuit;

	ReadDataCallback mReadCallback;
	ConnectCallback mConnectCallback;
	DisconnectCallback mDisconnectCallback;
    TimeoutCallback mTimeoutCallback;
	
	void* mUserData;

    static int ServerThreadFn(void* userData);
};

int OSWin32PipeInternal::ServerThreadFn(void* userData)
{
	OSWin32PipeInternal* pipe = (OSWin32PipeInternal*)userData;
	ASSERT(pipe->mReadCallback);

    OVERLAPPED readOverlapped = {};
    readOverlapped.hEvent = CreateEventA(nullptr, TRUE, FALSE, nullptr);

	while (!Atomic::LoadExplicit(&pipe->mQuit, AtomicMemoryOrder::Acquire)) {
		if (!pipe->mHandle) {
			HANDLE hPipe = CreateNamedPipeA(pipe->mName.CStr(), 
											PIPE_ACCESS_DUPLEX | FILE_FLAG_OVERLAPPED, 
											PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT, 
											1, // Max instances
											(DWORD)pipe->mInputBufferSize, // output buffer size
											(DWORD)pipe->mInputBufferSize, // input buffer size
											0,
											nullptr);

			if (hPipe == INVALID_HANDLE_VALUE) {
				LOG_ERROR("CreateNamedPipe for '%s' failed (GetLastError: %u)", pipe->mName.CStr(), GetLastError());
				return -1;
			}
			pipe->mHandle = hPipe;

			LOG_VERBOSE("Waiting for pipe connection '%s' ...", pipe->mName.CStr());
			BOOL connected = ConnectNamedPipe(pipe->mHandle, nullptr) ? TRUE : (GetLastError() == ERROR_PIPE_CONNECTED);
			if (!connected) {
				CloseHandle(pipe->mHandle);
				pipe->mHandle = nullptr;
				LOG_WARNING("Client cannot connect to pipe '%s'. Aborting ...");
				return -1;
			}			
			
			LOG_INFO("Client connected to pipe");
			ASSERT(!pipe->mIsConnected);
			pipe->mIsConnected = true;
			if (pipe->mConnectCallback)
				pipe->mConnectCallback(pipe, pipe->mUserData);
		}
		else  {
			DWORD bytesRead = 0;
			DWORD bytesWritten = 0;
            bool readFailed = false;

            if (!ReadFile(pipe->mHandle, pipe->mInputBuffer, (DWORD)pipe->mInputBufferSize, &bytesRead, &readOverlapped)) {
                DWORD lastErr = GetLastError();
                if (lastErr == ERROR_IO_PENDING) {
                    DWORD waitResult = WaitForSingleObject(readOverlapped.hEvent, pipe->mReadTimeout);
                    if (waitResult == WAIT_OBJECT_0) {
                        readFailed = !GetOverlappedResult(pipe->mHandle, &readOverlapped, &bytesRead, FALSE);
                    }
					else if (waitResult == WAIT_TIMEOUT) {
                        if (pipe->mTimeoutCallback)
                            readFailed = !pipe->mTimeoutCallback(pipe, pipe->mUserData);
					}
					else {
						readFailed = true;
					}
                }
            }

			if (bytesRead) {
				pipe->mReadCallback(pipe, pipe->mInputBuffer, bytesRead, pipe->mUserData);
			}
			else if (readFailed) {
                LOG_WARNING("ReadFile failed (GetLastError: %u). Closing the pipe...", GetLastError());
				pipe->Close();
				continue;
			}

            {
                MutexScope lock(pipe->mPendingWritesMtx);
                for (Span<uint8> data : pipe->mPendingWrites) {
                    bool writeOk = WriteFile(pipe->mHandle, data.Ptr(), data.Count(), &bytesWritten, nullptr);
                    if (!writeOk) {
                        if (pipe->mHandle) {
                            LOG_WARNING("Write to pipe '%s' failed (GetLastError: %u). Closing the pipe...", pipe->mName.CStr(), GetLastError());
                            pipe->Close();
                        }
                    }
                }

				if (!pipe->mPendingWrites.IsEmpty())
					FlushFileBuffers(pipe->mHandle);
                pipe->mPendingWrites.Clear();
            }
		}
	}

    CloseHandle(readOverlapped.hEvent);
	return 0;
}

bool OSWin32Pipe::IsConnected() const
{
    OSWin32PipeInternal* pipe = (OSWin32PipeInternal*)this;
	if (!pipe->mHandle || pipe->mHandle == INVALID_HANDLE_VALUE)
		return false;

	return pipe->mIsConnected;
}

void OSWin32Pipe::Close()
{
    OSWin32PipeInternal* pipe = (OSWin32PipeInternal*)this;
	if (pipe->mHandle) {
		if (pipe->mIsConnected) {
			DisconnectNamedPipe(pipe->mHandle);
			pipe->mIsConnected = false;
		}
		else {
			HANDLE hDummyPipe = CreateFileA(pipe->mName.CStr(), GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, NULL, OPEN_EXISTING, 0, NULL);
			Thread::Sleep(5);
			if(hDummyPipe != INVALID_HANDLE_VALUE)
				CloseHandle(hDummyPipe);
		}

		CloseHandle(pipe->mHandle);
		pipe->mHandle = nullptr;

		if (pipe->mDisconnectCallback)
			pipe->mDisconnectCallback(this, pipe->mUserData);
	}
}

OSWin32Pipe* OSWin32Pipe::CreateServer(const CreateServerDesc& desc)
{
	ASSERT_MSG(desc.handlerCallback, "Hanlder callback is not set");
	ASSERT_MSG(desc.name && desc.name[0], "Name should not be empty or null");
	ASSERT(desc.inputBufferSize);
	ASSERT(desc.outputBufferSize);

	static const char* PIPE_NAME_PREFIX = "\\\\.\\pipe\\";
	String32 pipeName(PIPE_NAME_PREFIX);
	pipeName.Append(desc.name);

	MemSingleShotMalloc<OSWin32PipeInternal> mallocator;
	mallocator.AddMemberArray<uint8>(offsetof(OSWin32PipeInternal, mInputBuffer), desc.inputBufferSize);
	OSWin32PipeInternal* pipe = mallocator.Calloc();

    pipe->mPendingWritesMtx.Initialize();
	pipe->mName = pipeName;
	pipe->mInputBufferSize = desc.inputBufferSize;
	pipe->mReadCallback = desc.handlerCallback;
	pipe->mConnectCallback = desc.connectCallback;
	pipe->mDisconnectCallback = desc.disconnectCallback;
    pipe->mTimeoutCallback = desc.timeoutCallback;
    
	pipe->mUserData = desc.handlerCallbackUserData;
    pipe->mReadTimeout = desc.readTimeout;
    pipe->mPendingWrites.SetAllocator(Mem::GetDefaultAlloc());
	pipe->mSendPing = desc.sendPing;

	String32 threadName(desc.name);
	threadName.Append("_Pipe");
	ThreadDesc thrdDesc {
		.entryFn = OSWin32PipeInternal::ServerThreadFn,
		.userData = pipe,
		.name = threadName.CStr(),
	};

	if (!pipe->mThread.Start(thrdDesc)) {
		MemSingleShotMalloc<OSWin32Pipe>::Free(pipe);
		return nullptr;		
	}

	return pipe;
}

void OSWin32Pipe::Write(const void* data, uint32 size)
{
    OSWin32PipeInternal* pipe = (OSWin32PipeInternal*)this;
	ASSERT(pipe->mHandle);
	ASSERT(size);

    uint8* dataCopy = Mem::AllocCopyRawBytes<uint8>((const uint8*)data, size);

    MutexScope lock(pipe->mPendingWritesMtx);
    pipe->mPendingWrites.Push(Span<uint8>(dataCopy, size));
}

void OSWin32Pipe::Destroy(OSWin32Pipe* pipe)
{
    OSWin32PipeInternal* pipeInternal = (OSWin32PipeInternal*)pipe;
	ASSERT(pipeInternal);

	Atomic::StoreExplicit(&pipeInternal->mQuit, 1, AtomicMemoryOrder::Release);
	pipeInternal->Close();

	pipeInternal->mThread.Stop();
    pipeInternal->mPendingWritesMtx.Release();
    pipeInternal->mPendingWrites.Free();

	MemSingleShotMalloc<OSWin32PipeInternal>::Free(pipeInternal);
}

static MemVirtualStats gVMStats;

void* Mem::VirtualReserve(size_t size, MemVirtualFlags flags)
{
    DWORD extraFlags = (flags & MemVirtualFlags::Watch) == MemVirtualFlags::Watch ? MEM_WRITE_WATCH : 0;
    void* ptr = VirtualAlloc(NULL, size, MEM_RESERVE | extraFlags, PAGE_READWRITE);
    if (!ptr) {
        MEM_FAIL();
    }

    Atomic::FetchAdd(&gVMStats.reservedBytes, size);
    return ptr;
}

void* Mem::VirtualCommit(void* ptr, size_t size)
{
    ASSERT(ptr);
    ptr = VirtualAlloc(ptr, size, MEM_COMMIT, PAGE_READWRITE);
    if (!ptr) {
        MEM_FAIL();
    }

    Atomic::FetchAdd(&gVMStats.commitedBytes, size);
    return ptr;
}

void Mem::VirtualDecommit(void* ptr, size_t size)
{
    [[maybe_unused]] BOOL r = VirtualFree(ptr, size, MEM_DECOMMIT);
    ASSERT(r);

    ASSERT(size <= gVMStats.commitedBytes);
    Atomic::FetchSub(&gVMStats.commitedBytes, size);
}

void Mem::VirtualRelease(void* ptr, size_t size)
{
    [[maybe_unused]] BOOL r = VirtualFree(ptr, 0, MEM_RELEASE);
    ASSERT(r);

    ASSERT(size <= gVMStats.reservedBytes);
    Atomic::FetchSub(&gVMStats.reservedBytes, size);
}

MemVirtualStats Mem::VirtualGetStats()
{
    return gVMStats;
}

bool Mem::VirtualEnableLargePages(size_t* largePageSize)
{
    ASSERT(largePageSize);
    if (!OS::Win32SetPrivilege("SeLockMemoryPrivilege"))
        return false;

    *largePageSize = GetLargePageMinimum();
    return true;
}

struct FileWin
{
    HANDLE      handle;
    FileOpenFlags flags;
    uint64      size;
    uint64      lastModifiedTime;
};
static_assert(sizeof(FileWin) <= sizeof(File));

static inline bool _GetFileInfo(HANDLE hFile, uint64* outFileSize, uint64* outModifiedTime)
{
    BY_HANDLE_FILE_INFORMATION fileInfo {};
    if (!GetFileInformationByHandle(hFile, &fileInfo)) 
        return false;

    *outFileSize = (uint64(fileInfo.nFileSizeHigh)<<32) | uint64(fileInfo.nFileSizeLow);
    *outModifiedTime = uint64(fileInfo.ftLastAccessTime.dwHighDateTime)<<32 | uint64(fileInfo.ftLastAccessTime.dwLowDateTime);
    return true;
}

File::File()
{
    FileWin* f = (FileWin*)mData;

    f->handle = INVALID_HANDLE_VALUE;
    f->flags = FileOpenFlags::None;
    f->size = 0;
    f->lastModifiedTime = 0;
}

bool File::Open(const char* filepath, FileOpenFlags flags)
{
    ASSERT((flags & (FileOpenFlags::Read|FileOpenFlags::Write)) != (FileOpenFlags::Read|FileOpenFlags::Write));
    ASSERT((flags & (FileOpenFlags::Read|FileOpenFlags::Write)) != FileOpenFlags::None);

    FileWin* f = (FileWin*)mData;

    uint32 accessFlags = 0;
    uint32 attrs = FILE_ATTRIBUTE_NORMAL;
    uint32 createFlags = 0;
    uint32 shareFlags = 0;

    if ((flags & FileOpenFlags::Read) == FileOpenFlags::Read) {
        accessFlags |= GENERIC_READ;
        createFlags = OPEN_EXISTING;
        shareFlags |= FILE_SHARE_READ;
    } else if ((flags & FileOpenFlags::Write) == FileOpenFlags::Write) {
        accessFlags |= GENERIC_WRITE;
        createFlags |= (flags & FileOpenFlags::Append) == FileOpenFlags::Append ? OPEN_EXISTING : CREATE_ALWAYS;
        shareFlags |= FILE_SHARE_WRITE;
    }

    if ((flags & FileOpenFlags::NoCache) == FileOpenFlags::NoCache)             attrs |= FILE_FLAG_NO_BUFFERING;
    if ((flags & FileOpenFlags::Writethrough) == FileOpenFlags::Writethrough)   attrs |= FILE_FLAG_WRITE_THROUGH;
    if ((flags & FileOpenFlags::SeqScan) == FileOpenFlags::SeqScan)             attrs |= FILE_FLAG_SEQUENTIAL_SCAN;
    if ((flags & FileOpenFlags::RandomAccess) == FileOpenFlags::RandomAccess)   attrs |= FILE_FLAG_RANDOM_ACCESS;
    if ((flags & FileOpenFlags::Temp) == FileOpenFlags::Temp)                   attrs |= FILE_ATTRIBUTE_TEMPORARY;

    HANDLE hfile = CreateFileA(filepath, accessFlags, shareFlags, NULL, createFlags, attrs, NULL);
    if (hfile == INVALID_HANDLE_VALUE)
        return false;

    f->handle = hfile;
    f->flags = flags;
    
    return _GetFileInfo(hfile, &f->size, &f->lastModifiedTime);
}

void File::Close()
{
    FileWin* f = (FileWin*)mData;

    if (f->handle != INVALID_HANDLE_VALUE) {
        CloseHandle(f->handle);
        f->handle = INVALID_HANDLE_VALUE;
    }
}

size_t File::Read(void* dst, size_t size)
{
    FileWin* f = (FileWin*)mData;
    ASSERT(f->handle != INVALID_HANDLE_VALUE);

    if ((f->flags & FileOpenFlags::NoCache) == FileOpenFlags::NoCache) {
        static size_t pagesz = 0;
        if (pagesz == 0) {
            pagesz = OS::GetPageSize();
        }
        ASSERT_ALWAYS((uintptr_t)dst % pagesz == 0, "buffers must be aligned with NoCache flag");
    }

    DWORD bytesRead;
    if (!ReadFile(f->handle, dst, (DWORD)size, &bytesRead, NULL))
        return 0;

    return size_t(bytesRead);
}

size_t File::Write(const void* src, size_t size)
{
    ASSERT(size);
    FileWin* f = (FileWin*)mData;
    ASSERT(f->handle != INVALID_HANDLE_VALUE);

    DWORD bytesWritten;
    if (!WriteFile(f->handle, src, (DWORD)size, &bytesWritten, NULL))
        return 0;
    f->size += bytesWritten;

    return bytesWritten;
}

size_t File::Seek(size_t offset, FileSeekMode mode)
{
    FileWin* f = (FileWin*)mData;
    ASSERT(f->handle != INVALID_HANDLE_VALUE);

    DWORD moveMethod = 0;
    switch (mode) {
    case FileSeekMode::Start:
        moveMethod = FILE_BEGIN;
        break;
    case FileSeekMode::Current:
        moveMethod = FILE_CURRENT;
        break;
    case FileSeekMode::End:
        ASSERT(offset <= f->size);
        moveMethod = FILE_END;
        break;
    }

    LARGE_INTEGER largeOff;
    LARGE_INTEGER largeRet;
    largeOff.QuadPart = (LONGLONG)offset;

    if (SetFilePointerEx(f->handle, largeOff, &largeRet, moveMethod))
        return (int64_t)largeRet.QuadPart;

    return SIZE_MAX;
}

size_t File::GetSize() const
{
    FileWin* f = (FileWin*)mData;
    return size_t(f->size);    
}

uint64 File::GetLastModified() const
{
    FileWin* f = (FileWin*)mData;
    return f->lastModifiedTime;
}

bool File::IsOpen() const
{
    FileWin* f = (FileWin*)mData;
    return f->handle != INVALID_HANDLE_VALUE;
}

struct alignas(4096) AsyncFileWin
{
    OVERLAPPED overlapped;
    AsyncFile f;
    HANDLE hFile;
    MemAllocator* alloc;
    AsyncFileCallback readFn;
    uint8 _reserved[4096 - 352];
};

struct AsyncContext
{
    Semaphore submitSem;
    Mutex requestsMtx;
    HANDLE completionPort;
    Thread* threads;
    Thread* submitThreads;
    Array<AsyncFileWin*> requests;
    uint32 numThreads;
    AtomicUint32 quit;
};

static AsyncContext gAsyncCtx;

namespace Async
{
    static int _IOThreadCallback(void* userData)
    {
        HANDLE completionPort = (HANDLE)userData;

        while (!Atomic::Load(&gAsyncCtx.quit)) {
            DWORD dwNumberOfBytesTransfered;
            ULONG_PTR completionKey;
            AsyncFileWin* file;
            if (GetQueuedCompletionStatus(completionPort, &dwNumberOfBytesTransfered, &completionKey, (LPOVERLAPPED*)&file, INFINITE)) {
                ASSERT(file->readFn);
                file->readFn(&file->f, dwNumberOfBytesTransfered != file->f.size);
            }
        }

        return 0;
    }

    static int _IOSubmitCallback(void*)
    {
        while (!Atomic::Load(&gAsyncCtx.quit)) {
            gAsyncCtx.submitSem.Wait();
            
            AsyncFileWin* file = nullptr;
            {
                MutexScope lock(gAsyncCtx.requestsMtx);
                if (!gAsyncCtx.requests.IsEmpty())
                    file = gAsyncCtx.requests.PopLast();
            }

            if (file) {
                HANDLE completionPort = CreateIoCompletionPort(file->hFile, gAsyncCtx.completionPort, 0, 0);
                ASSERT(completionPort == gAsyncCtx.completionPort);

                ASSERT(uintptr_t(file->f.data) % 4096 == 0);
                DWORD dwNumberOfBytesTransfered = 0;
                BOOL r = ReadFile(file->hFile, file->f.data, DWORD(AlignValue(file->f.size, 4096u)), nullptr, &file->overlapped);
                if (!r) {
                    if (GetLastError() != ERROR_IO_PENDING) {
                        CloseHandle(file->hFile);
                        MemSingleShotMalloc<AsyncFileWin>::Free(file, file->alloc);
                        ASSERT_MSG(0, "Unexpected ReadFile error with file: %s", file->f.filepath.CStr());
                    }
                }
                else {
                    file->readFn(&file->f, dwNumberOfBytesTransfered != file->f.size);
                }
            }
        }

        return 0;
    }

    FORCE_INLINE AsyncFileWin* _GetInternalFilePtr(AsyncFile* file)
    {
        return (AsyncFileWin*)((uint8*)file - offsetof(AsyncFileWin, f));
    }
} // Async

bool Async::Initialize()
{
    gAsyncCtx.completionPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, nullptr, 0, 0);
    if (!gAsyncCtx.completionPort) {
        LOG_ERROR("Creating async completion port failed");
        return false;
    }
    
    SysInfo info {};
    OS::GetSysInfo(&info);
    ASSERT(info.coreCount);

    gAsyncCtx.submitSem.Initialize();
    gAsyncCtx.requestsMtx.Initialize();
    
    gAsyncCtx.threads = NEW_ARRAY(Mem::GetDefaultAlloc(), Thread, info.coreCount);
    gAsyncCtx.submitThreads = NEW_ARRAY(Mem::GetDefaultAlloc(), Thread, info.coreCount);
    gAsyncCtx.numThreads = info.coreCount;

    for (uint32 i = 0; i < gAsyncCtx.numThreads; i++) {
        String<32> name = String<32>::Format("IO_%u", i+1);
        ThreadDesc tdesc {
            .entryFn = Async::_IOThreadCallback,
            .userData = gAsyncCtx.completionPort,
            .name = name.CStr(),
            .stackSize = 64*SIZE_KB
        };
        
        gAsyncCtx.threads[i].Start(tdesc);
    }

    for (uint32 i = 0; i < gAsyncCtx.numThreads; i++) {
        String<32> name = String<32>::Format("IOSubmit_%u", i+1);
        ThreadDesc tdesc {
            .entryFn = Async::_IOSubmitCallback,
            .name = name.CStr(),
            .stackSize = 64*SIZE_KB
        };
        
        gAsyncCtx.submitThreads[i].Start(tdesc);
    }

    LOG_INFO("(init) Initialized %u Async IO Threads", gAsyncCtx.numThreads);

    return true;
}

void Async::Release()
{
    Atomic::Store(&gAsyncCtx.quit, 1);
    if (gAsyncCtx.completionPort) {
        CloseHandle(gAsyncCtx.completionPort);
        gAsyncCtx.completionPort = nullptr;
    }
    gAsyncCtx.submitSem.Post(gAsyncCtx.numThreads);

    for (uint32 i = 0; i < gAsyncCtx.numThreads; i++) {
        gAsyncCtx.threads[i].Stop();
        gAsyncCtx.submitThreads[i].Stop();
    }
    Mem::Free(gAsyncCtx.threads, Mem::GetDefaultAlloc());
    Mem::Free(gAsyncCtx.submitThreads, Mem::GetDefaultAlloc());

    gAsyncCtx.requestsMtx.Release();
    gAsyncCtx.submitSem.Release();

    gAsyncCtx.threads = nullptr;
    gAsyncCtx.submitThreads = nullptr;
}

AsyncFile* Async::ReadFile(const char* filepath, const AsyncFileRequest& request)
{
    ASSERT(request.readFn);

    HANDLE hFile = CreateFileA(filepath, GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL|FILE_FLAG_SEQUENTIAL_SCAN|FILE_FLAG_OVERLAPPED, NULL);
    if (hFile == INVALID_HANDLE_VALUE)
        return nullptr;
    
    uint64 fileSize = request.sizeHint;
    uint64 fileModificationTime = 0;
    if (!fileSize) {
        if (!_GetFileInfo(hFile, &fileSize, &fileModificationTime) || fileSize == 0) {
            CloseHandle(hFile);
            return nullptr;
        }
    }
    ASSERT_MSG(fileSize < UINT32_MAX, "Large file sizes are not supported by win32 overlapped API");
    ASSERT_MSG(!request.userDataAllocateSize || (request.userData && request.userDataAllocateSize), 
               "`userDataAllocatedSize` should be accompanied with a valid `userData` pointer");

    MemSingleShotMalloc<AsyncFileWin> mallocator;
    uint8* data;
    uint8* userData = nullptr;
    if (request.userDataAllocateSize) 
        mallocator.AddExternalPointerField<uint8>(&userData, request.userDataAllocateSize);
    mallocator.AddExternalPointerField<uint8>(&data, fileSize, 4096);
    
    AsyncFileWin* file = mallocator.Malloc(request.alloc);
    memset(file, 0x0, sizeof(*file));
    file->f.filepath = filepath;
    file->f.data = data;
    file->f.size = uint32(fileSize);
    file->f.lastModifiedTime = fileModificationTime;
    if (request.userData) {
        if (request.userDataAllocateSize) {
            memcpy(userData, request.userData, request.userDataAllocateSize);
            file->f.userData = userData;
        }
        else {
            file->f.userData = request.userData;
        }
    }

    file->hFile = hFile;
    file->alloc = request.alloc;
    file->readFn = request.readFn;

    MutexScope lock(gAsyncCtx.requestsMtx);
    gAsyncCtx.requests.Push(file);
    gAsyncCtx.submitSem.Post(1);

    return &file->f;
}

void Async::Close(AsyncFile* file)
{
    if (!file)
        return;

    AsyncFileWin* fw = Async::_GetInternalFilePtr(file);
    if (fw->hFile != INVALID_HANDLE_VALUE) {
        DWORD numBytesTransfered;
        if (!GetOverlappedResult(fw->hFile, &fw->overlapped, &numBytesTransfered, FALSE) && GetLastError() == ERROR_IO_PENDING)
            CancelIo(fw->hFile);

        CloseHandle(fw->hFile);
        fw->hFile = INVALID_HANDLE_VALUE;

        MemSingleShotMalloc<AsyncFileWin>::Free(fw, fw->alloc);
    }    
}

bool Async::Wait(AsyncFile* file)
{
    ASSERT(file);
    AsyncFileWin* fw = Async::_GetInternalFilePtr(file);
    ASSERT(fw->hFile != INVALID_HANDLE_VALUE);

    DWORD numBytesTransfered;
    BOOL r = GetOverlappedResult(fw->hFile, &fw->overlapped, &numBytesTransfered, TRUE);
    return r && numBytesTransfered == fw->f.size;
}

bool Async::IsFinished(AsyncFile* file, bool* outError)
{
    ASSERT(file);
    AsyncFileWin* fw = Async::_GetInternalFilePtr(file);
    ASSERT(fw->hFile != INVALID_HANDLE_VALUE);

    DWORD numBytesTransfered;
    BOOL r = GetOverlappedResult(fw->hFile, &fw->overlapped, &numBytesTransfered, FALSE);

    if (outError)
        *outError = GetLastError() != ERROR_IO_PENDING;
    return r;
}

namespace _private
{
    static bool gSocketInitialized;
    static void socketInitializeWin32()
    {
        if (!gSocketInitialized) {
            LOG_DEBUG("SocketTCP: Initialize");
            WSADATA wsaData;
            if (WSAStartup(MAKEWORD(1, 0), &wsaData) != 0) {
                ASSERT_ALWAYS(false, "Windows sockets initialization failed");
                return;
            }
        
            gSocketInitialized = true;
        }
    }

    static SocketErrorCode::Enum socketTranslatePlatformErrorCode()
    {
        int errorCode = WSAGetLastError();
        switch (errorCode) {
        case WSAEADDRINUSE:     return SocketErrorCode::AddressInUse;
        case WSAECONNREFUSED:   return SocketErrorCode::ConnectionRefused;
        case WSAEISCONN:        return SocketErrorCode::AlreadyConnected;
        case WSAENETUNREACH: 
        case WSAENETDOWN:
        case WSAEHOSTUNREACH:   return SocketErrorCode::HostUnreachable;
        case WSAETIMEDOUT:      return SocketErrorCode::Timeout;
        case WSAECONNRESET:
        case WSAEINTR:
        case WSAENETRESET:      return SocketErrorCode::ConnectionReset;
        case WSAEADDRNOTAVAIL:  return SocketErrorCode::AddressNotAvailable;
        case WSAEAFNOSUPPORT:   return SocketErrorCode::AddressUnsupported;
        case WSAESHUTDOWN:      return SocketErrorCode::SocketShutdown;
        case WSAEMSGSIZE:       return SocketErrorCode::MessageTooLarge;
        case WSAENOTCONN:       return SocketErrorCode::NotConnected;
        default:                ASSERT_MSG(0, "Unknown socket error: %d", WSAGetLastError()); return SocketErrorCode::Unknown;
        }
    }
} // namespace _private


#define SOCKET_INVALID INVALID_SOCKET
SocketTCP::SocketTCP() :
    mSock(SOCKET_INVALID),
    mErrCode(SocketErrorCode::None),
    mLive(0)
{
}

void SocketTCP::Close()
{
    if (mSock != SOCKET_INVALID) {
        if (mLive)
            shutdown(mSock, SD_BOTH);
        closesocket(mSock);

        mSock = SOCKET_INVALID;
        mErrCode = SocketErrorCode::None;
        mLive = false;
    }
}

SocketTCP SocketTCP::CreateListener()
{
    _private::socketInitializeWin32();

    SocketTCP sock;

    sock.mSock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock.mSock == SOCKET_INVALID) {
        sock.mErrCode = _private::socketTranslatePlatformErrorCode();
        LOG_ERROR("SocketTCP: Opening the socket failed");
        return sock;
    }
    return sock;    
}

bool SocketTCP::Listen(uint16 port, uint32 maxConnections)
{
    ASSERT(IsValid());

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);

    if (bind(mSock, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        mErrCode = _private::socketTranslatePlatformErrorCode();
        LOG_ERROR("SocketTCP: failed binding the socket to port: %d", port);
        return false;
    }

    LOG_VERBOSE("SocketTCP: Listening on port '%d' for incoming connections ...", port);
    int _maxConnections = maxConnections > INT32_MAX ? INT32_MAX : static_cast<int>(maxConnections);
    bool success = listen(mSock, _maxConnections) >= 0;
    
    if (!success) 
        mErrCode = _private::socketTranslatePlatformErrorCode();
    else
        mLive = true;

    return success;
}

SocketTCP SocketTCP::Accept(char* clientUrl, uint32 clientUrlSize)
{
    ASSERT(IsValid());

    SocketTCP newSock;

    struct sockaddr_in addr;
    socklen_t addrlen = sizeof(addr);
    newSock.mSock = accept(mSock, (struct sockaddr*)&addr, &addrlen);
    if (mLive && newSock.mSock == SOCKET_INVALID) {
        newSock.mErrCode = _private::socketTranslatePlatformErrorCode();
        LOG_ERROR("SocketTCP: failed to accept the new socket");
        return newSock;
    }

    if (clientUrl && clientUrlSize) {
        char ip[256];
        inet_ntop(AF_INET, &addr.sin_addr, ip, sizeof(ip));
        uint16 port = htons(addr.sin_port);
        
        Str::PrintFmt(clientUrl, clientUrlSize, "%s:%d", ip, port);
    }

    newSock.mLive = true;
    return newSock;
}

SocketTCP SocketTCP::Connect(const char* url)
{
    _private::socketInitializeWin32();

    SocketTCP sock;

    char address[256];
    char port[16];
    if (!SocketTCP::ParseUrl(url, address, sizeof(address), port, sizeof(port))) {
        LOG_ERROR("SocketTCP: failed parsing the url: %s", url);
        return sock;
    }

    struct addrinfo hints;
    memset(&hints, 0x0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_flags = AI_PASSIVE;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    struct addrinfo* addri = nullptr;
    if (getaddrinfo(address, port, &hints, &addri) != 0) {
        LOG_ERROR("SocketTCP: failed to resolve url: %s", url);
        return sock;
    }

    sock.mSock = socket(addri->ai_family, addri->ai_socktype, addri->ai_protocol);
    if (sock.mSock == SOCKET_INVALID) {
        freeaddrinfo(addri);
        LOG_ERROR("SocketTCP: failed to create socket");
        return sock;
    }

    if (connect(sock.mSock, addri->ai_addr, (int)addri->ai_addrlen) == -1) {
        freeaddrinfo(addri);
        sock.mErrCode = _private::socketTranslatePlatformErrorCode();
        LOG_ERROR("SocketTCP: failed to connect to url: %s", url);
        sock.Close();
        return sock;
    }

    freeaddrinfo(addri);

    sock.mLive = true;
    return sock;
}

uint32 SocketTCP::Write(const void* src, uint32 size)
{
    ASSERT(IsValid());
    ASSERT(mLive);
    uint32 totalBytesSent = 0;

    while (size > 0) {
        int bytesSent = send(mSock, reinterpret_cast<const char*>(src) + totalBytesSent, size, 0);
        if (bytesSent == 0) {
            break;
        }
        else if (bytesSent == -1) {
            mErrCode = _private::socketTranslatePlatformErrorCode();
            if (mErrCode == SocketErrorCode::SocketShutdown ||
                mErrCode == SocketErrorCode::NotConnected)
            {
                LOG_DEBUG("SocketTCP: socket connection closed forcefully by the peer");
                mLive = false;
            }
            return UINT32_MAX;
        }

        totalBytesSent += static_cast<uint32>(bytesSent);
        size -= static_cast<uint32>(bytesSent);
    }

    return totalBytesSent;
}

uint32 SocketTCP::Read(void* dst, uint32 dstSize)
{
    ASSERT(IsValid());
    ASSERT(mLive);

    int bytesRecv = recv(mSock, reinterpret_cast<char*>(dst), dstSize, 0);
    if (bytesRecv == -1) {
        mErrCode = _private::socketTranslatePlatformErrorCode();
        if (mErrCode == SocketErrorCode::SocketShutdown ||
            mErrCode == SocketErrorCode::NotConnected)
        {
            LOG_DEBUG("SocketTCP: socket connection closed forcefully by the peer");
            mLive = false;
        }
        return UINT32_MAX;
    }

    return static_cast<uint32>(bytesRecv);
}

bool SocketTCP::IsValid() const
{
    return mSock != SOCKET_INVALID;
}

#endif // PLATFORM_WINDOWS

    #elif PLATFORM_ANDROID
//----------------------------------------------------------------------------------------------------------------------
// SystemAndroid.cpp


#if PLATFORM_ANDROID

#include <android/log.h>
#include <android/native_activity.h>
#include <jni.h>

//----------------------------------------------------------------------------------------------------------------------
// External/cpufeatures/cpu-features.h

/*
 * Copyright (C) 2010 The Android Open Source Project
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */
#ifndef CPU_FEATURES_H
#define CPU_FEATURES_H

#include <sys/cdefs.h>
#include <stdint.h>

__BEGIN_DECLS

/* A list of valid values returned by android_getCpuFamily().
 * They describe the CPU Architecture of the current process.
 */
typedef enum {
    ANDROID_CPU_FAMILY_UNKNOWN = 0,
    ANDROID_CPU_FAMILY_ARM,
    ANDROID_CPU_FAMILY_X86,
    ANDROID_CPU_FAMILY_MIPS,
    ANDROID_CPU_FAMILY_ARM64,
    ANDROID_CPU_FAMILY_X86_64,
    ANDROID_CPU_FAMILY_MIPS64,

    ANDROID_CPU_FAMILY_MAX  /* do not remove */

} AndroidCpuFamily;

/* Return the CPU family of the current process.
 *
 * Note that this matches the bitness of the current process. I.e. when
 * running a 32-bit binary on a 64-bit capable CPU, this will return the
 * 32-bit CPU family value.
 */
extern AndroidCpuFamily android_getCpuFamily(void);

/* Return a bitmap describing a set of optional CPU features that are
 * supported by the current device's CPU. The exact bit-flags returned
 * depend on the value returned by android_getCpuFamily(). See the
 * documentation for the ANDROID_CPU_*_FEATURE_* flags below for details.
 */
extern uint64_t android_getCpuFeatures(void);

/* The list of feature flags for ANDROID_CPU_FAMILY_ARM that can be
 * recognized by the library (see note below for 64-bit ARM). Value details
 * are:
 *
 *   VFPv2:
 *     CPU supports the VFPv2 instruction set. Many, but not all, ARMv6 CPUs
 *     support these instructions. VFPv2 is a subset of VFPv3 so this will
 *     be set whenever VFPv3 is set too.
 *
 *   ARMv7:
 *     CPU supports the ARMv7-A basic instruction set.
 *     This feature is mandated by the 'armeabi-v7a' ABI.
 *
 *   VFPv3:
 *     CPU supports the VFPv3-D16 instruction set, providing hardware FPU
 *     support for single and double precision floating point registers.
 *     Note that only 16 FPU registers are available by default, unless
 *     the D32 bit is set too. This feature is also mandated by the
 *     'armeabi-v7a' ABI.
 *
 *   VFP_D32:
 *     CPU VFP optional extension that provides 32 FPU registers,
 *     instead of 16. Note that ARM mandates this feature is the 'NEON'
 *     feature is implemented by the CPU.
 *
 *   NEON:
 *     CPU FPU supports "ARM Advanced SIMD" instructions, also known as
 *     NEON. Note that this mandates the VFP_D32 feature as well, per the
 *     ARM Architecture specification.
 *
 *   VFP_FP16:
 *     Half-width floating precision VFP extension. If set, the CPU
 *     supports instructions to perform floating-point operations on
 *     16-bit registers. This is part of the VFPv4 specification, but
 *     not mandated by any Android ABI.
 *
 *   VFP_FMA:
 *     Fused multiply-accumulate VFP instructions extension. Also part of
 *     the VFPv4 specification, but not mandated by any Android ABI.
 *
 *   NEON_FMA:
 *     Fused multiply-accumulate NEON instructions extension. Optional
 *     extension from the VFPv4 specification, but not mandated by any
 *     Android ABI.
 *
 *   IDIV_ARM:
 *     Integer division available in ARM mode. Only available
 *     on recent CPUs (e.g. Cortex-A15).
 *
 *   IDIV_THUMB2:
 *     Integer division available in Thumb-2 mode. Only available
 *     on recent CPUs (e.g. Cortex-A15).
 *
 *   iWMMXt:
 *     Optional extension that adds MMX registers and operations to an
 *     ARM CPU. This is only available on a few XScale-based CPU designs
 *     sold by Marvell. Pretty rare in practice.
 *
 *   AES:
 *     CPU supports AES instructions. These instructions are only
 *     available for 32-bit applications running on ARMv8 CPU.
 *
 *   CRC32:
 *     CPU supports CRC32 instructions. These instructions are only
 *     available for 32-bit applications running on ARMv8 CPU.
 *
 *   SHA2:
 *     CPU supports SHA2 instructions. These instructions are only
 *     available for 32-bit applications running on ARMv8 CPU.
 *
 *   SHA1:
 *     CPU supports SHA1 instructions. These instructions are only
 *     available for 32-bit applications running on ARMv8 CPU.
 *
 *   PMULL:
 *     CPU supports 64-bit PMULL and PMULL2 instructions. These
 *     instructions are only available for 32-bit applications
 *     running on ARMv8 CPU.
 *
 * If you want to tell the compiler to generate code that targets one of
 * the feature set above, you should probably use one of the following
 * flags (for more details, see technical note at the end of this file):
 *
 *   -mfpu=vfp
 *   -mfpu=vfpv2
 *     These are equivalent and tell GCC to use VFPv2 instructions for
 *     floating-point operations. Use this if you want your code to
 *     run on *some* ARMv6 devices, and any ARMv7-A device supported
 *     by Android.
 *
 *     Generated code requires VFPv2 feature.
 *
 *   -mfpu=vfpv3-d16
 *     Tell GCC to use VFPv3 instructions (using only 16 FPU registers).
 *     This should be generic code that runs on any CPU that supports the
 *     'armeabi-v7a' Android ABI. Note that no ARMv6 CPU supports this.
 *
 *     Generated code requires VFPv3 feature.
 *
 *   -mfpu=vfpv3
 *     Tell GCC to use VFPv3 instructions with 32 FPU registers.
 *     Generated code requires VFPv3|VFP_D32 features.
 *
 *   -mfpu=neon
 *     Tell GCC to use VFPv3 instructions with 32 FPU registers, and
 *     also support NEON intrinsics (see <arm_neon.h>).
 *     Generated code requires VFPv3|VFP_D32|NEON features.
 *
 *   -mfpu=vfpv4-d16
 *     Generated code requires VFPv3|VFP_FP16|VFP_FMA features.
 *
 *   -mfpu=vfpv4
 *     Generated code requires VFPv3|VFP_FP16|VFP_FMA|VFP_D32 features.
 *
 *   -mfpu=neon-vfpv4
 *     Generated code requires VFPv3|VFP_FP16|VFP_FMA|VFP_D32|NEON|NEON_FMA
 *     features.
 *
 *   -mcpu=cortex-a7
 *   -mcpu=cortex-a15
 *     Generated code requires VFPv3|VFP_FP16|VFP_FMA|VFP_D32|
 *                             NEON|NEON_FMA|IDIV_ARM|IDIV_THUMB2
 *     This flag implies -mfpu=neon-vfpv4.
 *
 *   -mcpu=iwmmxt
 *     Allows the use of iWMMXt instrinsics with GCC.
 *
 * IMPORTANT NOTE: These flags should only be tested when
 * android_getCpuFamily() returns ANDROID_CPU_FAMILY_ARM, i.e. this is a
 * 32-bit process.
 *
 * When running a 64-bit ARM process on an ARMv8 CPU,
 * android_getCpuFeatures() will return a different set of bitflags
 */
enum {
    ANDROID_CPU_ARM_FEATURE_ARMv7       = (1 << 0),
    ANDROID_CPU_ARM_FEATURE_VFPv3       = (1 << 1),
    ANDROID_CPU_ARM_FEATURE_NEON        = (1 << 2),
    ANDROID_CPU_ARM_FEATURE_LDREX_STREX = (1 << 3),
    ANDROID_CPU_ARM_FEATURE_VFPv2       = (1 << 4),
    ANDROID_CPU_ARM_FEATURE_VFP_D32     = (1 << 5),
    ANDROID_CPU_ARM_FEATURE_VFP_FP16    = (1 << 6),
    ANDROID_CPU_ARM_FEATURE_VFP_FMA     = (1 << 7),
    ANDROID_CPU_ARM_FEATURE_NEON_FMA    = (1 << 8),
    ANDROID_CPU_ARM_FEATURE_IDIV_ARM    = (1 << 9),
    ANDROID_CPU_ARM_FEATURE_IDIV_THUMB2 = (1 << 10),
    ANDROID_CPU_ARM_FEATURE_iWMMXt      = (1 << 11),
    ANDROID_CPU_ARM_FEATURE_AES         = (1 << 12),
    ANDROID_CPU_ARM_FEATURE_PMULL       = (1 << 13),
    ANDROID_CPU_ARM_FEATURE_SHA1        = (1 << 14),
    ANDROID_CPU_ARM_FEATURE_SHA2        = (1 << 15),
    ANDROID_CPU_ARM_FEATURE_CRC32       = (1 << 16),
};

/* The bit flags corresponding to the output of android_getCpuFeatures()
 * when android_getCpuFamily() returns ANDROID_CPU_FAMILY_ARM64. Value details
 * are:
 *
 *   FP:
 *     CPU has Floating-point unit.
 *
 *   ASIMD:
 *     CPU has Advanced SIMD unit.
 *
 *   AES:
 *     CPU supports AES instructions.
 *
 *   CRC32:
 *     CPU supports CRC32 instructions.
 *
 *   SHA2:
 *     CPU supports SHA2 instructions.
 *
 *   SHA1:
 *     CPU supports SHA1 instructions.
 *
 *   PMULL:
 *     CPU supports 64-bit PMULL and PMULL2 instructions.
 */
enum {
    ANDROID_CPU_ARM64_FEATURE_FP      = (1 << 0),
    ANDROID_CPU_ARM64_FEATURE_ASIMD   = (1 << 1),
    ANDROID_CPU_ARM64_FEATURE_AES     = (1 << 2),
    ANDROID_CPU_ARM64_FEATURE_PMULL   = (1 << 3),
    ANDROID_CPU_ARM64_FEATURE_SHA1    = (1 << 4),
    ANDROID_CPU_ARM64_FEATURE_SHA2    = (1 << 5),
    ANDROID_CPU_ARM64_FEATURE_CRC32   = (1 << 6),
};

/* The bit flags corresponding to the output of android_getCpuFeatures()
 * when android_getCpuFamily() returns ANDROID_CPU_FAMILY_X86 or
 * ANDROID_CPU_FAMILY_X86_64.
 */
enum {
    ANDROID_CPU_X86_FEATURE_SSSE3  = (1 << 0),
    ANDROID_CPU_X86_FEATURE_POPCNT = (1 << 1),
    ANDROID_CPU_X86_FEATURE_MOVBE  = (1 << 2),
    ANDROID_CPU_X86_FEATURE_SSE4_1 = (1 << 3),
    ANDROID_CPU_X86_FEATURE_SSE4_2 = (1 << 4),
    ANDROID_CPU_X86_FEATURE_AES_NI = (1 << 5),
    ANDROID_CPU_X86_FEATURE_AVX =    (1 << 6),
    ANDROID_CPU_X86_FEATURE_RDRAND = (1 << 7),
    ANDROID_CPU_X86_FEATURE_AVX2 =   (1 << 8),
    ANDROID_CPU_X86_FEATURE_SHA_NI = (1 << 9),
};

/* The bit flags corresponding to the output of android_getCpuFeatures()
 * when android_getCpuFamily() returns ANDROID_CPU_FAMILY_MIPS
 * or ANDROID_CPU_FAMILY_MIPS64.  Values are:
 *
 *   R6:
 *     CPU executes MIPS Release 6 instructions natively, and
 *     supports obsoleted R1..R5 instructions only via kernel traps.
 *
 *   MSA:
 *     CPU supports Mips SIMD Architecture instructions.
 */
enum {
    ANDROID_CPU_MIPS_FEATURE_R6    = (1 << 0),
    ANDROID_CPU_MIPS_FEATURE_MSA   = (1 << 1),
};


/* Return the number of CPU cores detected on this device. */
static int android_getCpuCount(void);

/* The following is used to force the CPU count and features
 * mask in sandboxed processes. Under 4.1 and higher, these processes
 * cannot access /proc, which is the only way to get information from
 * the kernel about the current hardware (at least on ARM).
 *
 * It _must_ be called only once, and before any android_getCpuXXX
 * function, any other case will fail.
 *
 * This function return 1 on success, and 0 on failure.
 */
static int android_setCpu(int      cpu_count,
                          uint64_t cpu_features);

#ifdef __arm__
/* Retrieve the ARM 32-bit CPUID value from the kernel.
 * Note that this cannot work on sandboxed processes under 4.1 and
 * higher, unless you called android_setCpuArm() before.
 */
static uint32_t android_getCpuIdArm(void);

/* An ARM-specific variant of android_setCpu() that also allows you
 * to set the ARM CPUID field.
 */
static int android_setCpuArm(int      cpu_count,
                             uint64_t cpu_features,
                             uint32_t cpu_id);
#endif

__END_DECLS

#endif /* CPU_FEATURES_H */

PRAGMA_DIAGNOSTIC_PUSH()
PRAGMA_DIAGNOSTIC_IGNORED_CLANG_GCC("-Wunused-function")
//----------------------------------------------------------------------------------------------------------------------
// External/cpufeatures/cpu-features.c

/*
 * Copyright (C) 2010 The Android Open Source Project
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

/* ChangeLog for this library:
 *
 * NDK r10e?: Add MIPS MSA feature.
 *
 * NDK r10: Support for 64-bit CPUs (Intel, ARM & MIPS).
 *
 * NDK r8d: Add android_setCpu().
 *
 * NDK r8c: Add new ARM CPU features: VFPv2, VFP_D32, VFP_FP16,
 *          VFP_FMA, NEON_FMA, IDIV_ARM, IDIV_THUMB2 and iWMMXt.
 *
 *          Rewrite the code to parse /proc/self/auxv instead of
 *          the "Features" field in /proc/cpuinfo.
 *
 *          Dynamically allocate the buffer that hold the content
 *          of /proc/cpuinfo to deal with newer hardware.
 *
 * NDK r7c: Fix CPU count computation. The old method only reported the
 *           number of _active_ CPUs when the library was initialized,
 *           which could be less than the real total.
 *
 * NDK r5: Handle buggy kernels which report a CPU Architecture number of 7
 *         for an ARMv6 CPU (see below).
 *
 *         Handle kernels that only report 'neon', and not 'vfpv3'
 *         (VFPv3 is mandated by the ARM architecture is Neon is implemented)
 *
 *         Handle kernels that only report 'vfpv3d16', and not 'vfpv3'
 *
 *         Fix x86 compilation. Report ANDROID_CPU_FAMILY_X86 in
 *         android_getCpuFamily().
 *
 * NDK r4: Initial release
 */


#include <dlfcn.h>
#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/system_properties.h>
#include <unistd.h>

static  pthread_once_t     g_once;
static  int                g_inited;
static  AndroidCpuFamily   g_cpuFamily;
static  uint64_t           g_cpuFeatures;
static  int                g_cpuCount;

#ifdef __arm__
static  uint32_t           g_cpuIdArm;
#endif

static const int android_cpufeatures_debug = 0;

#define  D(...) \
    do { \
        if (android_cpufeatures_debug) { \
            printf(__VA_ARGS__); fflush(stdout); \
        } \
    } while (0)

#ifdef __i386__
static __inline__ void x86_cpuid(int func, int values[4])
{
    int a, b, c, d;
    /* We need to preserve ebx since we're compiling PIC code */
    /* this means we can't use "=b" for the second output register */
    __asm__ __volatile__ ( \
      "push %%ebx\n"
      "cpuid\n" \
      "mov %%ebx, %1\n"
      "pop %%ebx\n"
      : "=a" (a), "=r" (b), "=c" (c), "=d" (d) \
      : "a" (func) \
    );
    values[0] = a;
    values[1] = b;
    values[2] = c;
    values[3] = d;
}
#elif defined(__x86_64__)
static __inline__ void x86_cpuid(int func, int values[4])
{
    int64_t a, b, c, d;
    /* We need to preserve ebx since we're compiling PIC code */
    /* this means we can't use "=b" for the second output register */
    __asm__ __volatile__ ( \
      "push %%rbx\n"
      "cpuid\n" \
      "mov %%rbx, %1\n"
      "pop %%rbx\n"
      : "=a" (a), "=r" (b), "=c" (c), "=d" (d) \
      : "a" (func) \
    );
    values[0] = a;
    values[1] = b;
    values[2] = c;
    values[3] = d;
}
#endif

/* Get the size of a file by reading it until the end. This is needed
 * because files under /proc do not always return a valid size when
 * using fseek(0, SEEK_END) + ftell(). Nor can they be mmap()-ed.
 */
static int
get_file_size(const char* pathname)
{

   int fd, result = 0;
    char buffer[256];

    fd = open(pathname, O_RDONLY);
    if (fd < 0) {
        D("Can't open %s: %s\n", pathname, strerror(errno));
        return -1;
    }

    for (;;) {
        int ret = read(fd, buffer, sizeof buffer);
        if (ret < 0) {
            if (errno == EINTR)
                continue;
            D("Error while reading %s: %s\n", pathname, strerror(errno));
            break;
        }
        if (ret == 0)
            break;

        result += ret;
    }
    close(fd);
    return result;
}

/* Read the content of /proc/cpuinfo into a user-provided buffer.
 * Return the length of the data, or -1 on error. Does *not*
 * zero-terminate the content. Will not read more
 * than 'buffsize' bytes.
 */
static int
read_file(const char*  pathname, char*  buffer, size_t  buffsize)
{
    int  fd, count;

    fd = open(pathname, O_RDONLY);
    if (fd < 0) {
        D("Could not open %s: %s\n", pathname, strerror(errno));
        return -1;
    }
    count = 0;
    while (count < (int)buffsize) {
        int ret = read(fd, buffer + count, buffsize - count);
        if (ret < 0) {
            if (errno == EINTR)
                continue;
            D("Error while reading from %s: %s\n", pathname, strerror(errno));
            if (count == 0)
                count = -1;
            break;
        }
        if (ret == 0)
            break;
        count += ret;
    }
    close(fd);
    return count;
}

#ifdef __arm__
/* Extract the content of a the first occurence of a given field in
 * the content of /proc/cpuinfo and return it as a heap-allocated
 * string that must be freed by the caller.
 *
 * Return NULL if not found
 */
static char*
extract_cpuinfo_field(const char* buffer, int buflen, const char* field)
{
    int  fieldlen = strlen(field);
    const char* bufend = buffer + buflen;
    char* result = NULL;
    int len;
    const char *p, *q;

    /* Look for first field occurence, and ensures it starts the line. */
    p = buffer;
    for (;;) {
        p = memmem(p, bufend-p, field, fieldlen);
        if (p == NULL)
            goto EXIT;

        if (p == buffer || p[-1] == '\n')
            break;

        p += fieldlen;
    }

    /* Skip to the first column followed by a space */
    p += fieldlen;
    p  = memchr(p, ':', bufend-p);
    if (p == NULL || p[1] != ' ')
        goto EXIT;

    /* Find the end of the line */
    p += 2;
    q = memchr(p, '\n', bufend-p);
    if (q == NULL)
        q = bufend;

    /* Copy the line into a heap-allocated buffer */
    len = q-p;
    result = malloc(len+1);
    if (result == NULL)
        goto EXIT;

    memcpy(result, p, len);
    result[len] = '\0';

EXIT:
    return result;
}

/* Checks that a space-separated list of items contains one given 'item'.
 * Returns 1 if found, 0 otherwise.
 */
static int
has_list_item(const char* list, const char* item)
{
    const char*  p = list;
    int itemlen = strlen(item);

    if (list == NULL)
        return 0;

    while (*p) {
        const char*  q;

        /* skip spaces */
        while (*p == ' ' || *p == '\t')
            p++;

        /* find end of current list item */
        q = p;
        while (*q && *q != ' ' && *q != '\t')
            q++;

        if (itemlen == q-p && !memcmp(p, item, itemlen))
            return 1;

        /* skip to next item */
        p = q;
    }
    return 0;
}
#endif /* __arm__ */

/* Parse a number starting from 'input', but not going further
 * than 'limit'. Return the value into '*result'.
 *
 * NOTE: Does not skip over leading spaces, or deal with sign characters.
 * NOTE: Ignores overflows.
 *
 * The function returns NULL in case of error (bad format), or the new
 * position after the decimal number in case of success (which will always
 * be <= 'limit').
 */
static const char*
parse_number(const char* input, const char* limit, int base, int* result)
{
    const char* p = input;
    int val = 0;
    while (p < limit) {
        int d = (*p - '0');
        if ((unsigned)d >= 10U) {
            d = (*p - 'a');
            if ((unsigned)d >= 6U)
              d = (*p - 'A');
            if ((unsigned)d >= 6U)
              break;
            d += 10;
        }
        if (d >= base)
          break;
        val = val*base + d;
        p++;
    }
    if (p == input)
        return NULL;

    *result = val;
    return p;
}

static const char*
parse_decimal(const char* input, const char* limit, int* result)
{
    return parse_number(input, limit, 10, result);
}

#ifdef __arm__
static const char*
parse_hexadecimal(const char* input, const char* limit, int* result)
{
    return parse_number(input, limit, 16, result);
}
#endif /* __arm__ */

/* This small data type is used to represent a CPU list / mask, as read
 * from sysfs on Linux. See http://www.kernel.org/doc/Documentation/cputopology.txt
 *
 * For now, we don't expect more than 32 cores on mobile devices, so keep
 * everything simple.
 */
typedef struct {
    uint32_t mask;
} CpuList;

static __inline__ void
cpulist_init(CpuList* list) {
    list->mask = 0;
}

static __inline__ void
cpulist_and(CpuList* list1, CpuList* list2) {
    list1->mask &= list2->mask;
}

static __inline__ void
cpulist_set(CpuList* list, int index) {
    if ((unsigned)index < 32) {
        list->mask |= (uint32_t)(1U << index);
    }
}

static __inline__ int
cpulist_count(CpuList* list) {
    return __builtin_popcount(list->mask);
}

/* Parse a textual list of cpus and store the result inside a CpuList object.
 * Input format is the following:
 * - comma-separated list of items (no spaces)
 * - each item is either a single decimal number (cpu index), or a range made
 *   of two numbers separated by a single dash (-). Ranges are inclusive.
 *
 * Examples:   0
 *             2,4-127,128-143
 *             0-1
 */
static void
cpulist_parse(CpuList* list, const char* line, int line_len)
{
    const char* p = line;
    const char* end = p + line_len;
    const char* q;

    /* NOTE: the input line coming from sysfs typically contains a
     * trailing newline, so take care of it in the code below
     */
    while (p < end && *p != '\n')
    {
        int val, start_value, end_value;

        /* Find the end of current item, and put it into 'q' */
        q = (const char*)memchr(p, ',', end-p);
        if (q == NULL) {
            q = end;
        }

        /* Get first value */
        p = parse_decimal(p, q, &start_value);
        if (p == NULL)
            goto BAD_FORMAT;

        end_value = start_value;

        /* If we're not at the end of the item, expect a dash and
         * and integer; extract end value.
         */
        if (p < q && *p == '-') {
            p = parse_decimal(p+1, q, &end_value);
            if (p == NULL)
                goto BAD_FORMAT;
        }

        /* Set bits CPU list bits */
        for (val = start_value; val <= end_value; val++) {
            cpulist_set(list, val);
        }

        /* Jump to next item */
        p = q;
        if (p < end)
            p++;
    }

BAD_FORMAT:
    ;
}

/* Read a CPU list from one sysfs file */
static void
cpulist_read_from(CpuList* list, const char* filename)
{
    char   file[64];
    int    filelen;

    cpulist_init(list);

    filelen = read_file(filename, file, sizeof file);
    if (filelen < 0) {
        D("Could not read %s: %s\n", filename, strerror(errno));
        return;
    }

    cpulist_parse(list, file, filelen);
}
#if defined(__aarch64__)
#define HWCAP_FP                (1 << 0)
#define HWCAP_ASIMD             (1 << 1)
#define HWCAP_AES               (1 << 3)
#define HWCAP_PMULL             (1 << 4)
#define HWCAP_SHA1              (1 << 5)
#define HWCAP_SHA2              (1 << 6)
#define HWCAP_CRC32             (1 << 7)
#endif

#if defined(__arm__)

#define HWCAP_VFP       (1 << 6)
#define HWCAP_IWMMXT    (1 << 9)
#define HWCAP_NEON      (1 << 12)
#define HWCAP_VFPv3     (1 << 13)
#define HWCAP_VFPv3D16  (1 << 14)
#define HWCAP_VFPv4     (1 << 16)
#define HWCAP_IDIVA     (1 << 17)
#define HWCAP_IDIVT     (1 << 18)

#define HWCAP2_AES     (1 << 0)
#define HWCAP2_PMULL   (1 << 1)
#define HWCAP2_SHA1    (1 << 2)
#define HWCAP2_SHA2    (1 << 3)
#define HWCAP2_CRC32   (1 << 4)

#define HWCAP_SET_FOR_ARMV8  \
  ( HWCAP_VFP | \
    HWCAP_NEON | \
    HWCAP_VFPv3 | \
    HWCAP_VFPv4 | \
    HWCAP_IDIVA | \
    HWCAP_IDIVT )
#endif

#if defined(__mips__)
#define HWCAP_MIPS_R6           (1 << 0)
#define HWCAP_MIPS_MSA          (1 << 1)
#endif

#if defined(__arm__) || defined(__aarch64__) || defined(__mips__)

#define AT_HWCAP 16
#define AT_HWCAP2 26

static uint32_t
get_elf_hwcap_from_getauxval(int hwcap_type) {
    typedef unsigned long getauxval_func_t(unsigned long);

    dlerror();
    void* libc_handle = dlopen("libc.so", RTLD_NOW);
    if (!libc_handle) {
        D("Could not dlopen() C library: %s\n", dlerror());
        return 0;
    }

    uint32_t ret = 0;
    getauxval_func_t* func = (getauxval_func_t*)
            dlsym(libc_handle, "getauxval");
    if (!func) {
        D("Could not find getauxval() in C library\n");
    } else {
        ret = (uint32_t)(*func)(hwcap_type);
    }
    dlclose(libc_handle);
    return ret;
}
#endif

#if defined(__arm__)
static uint32_t
get_elf_hwcap_from_proc_self_auxv(void) {
    const char filepath[] = "/proc/self/auxv";
    int fd = TEMP_FAILURE_RETRY(open(filepath, O_RDONLY));
    if (fd < 0) {
        D("Could not open %s: %s\n", filepath, strerror(errno));
        return 0;
    }

    struct { uint32_t tag; uint32_t value; } entry;

    uint32_t result = 0;
    for (;;) {
        int ret = TEMP_FAILURE_RETRY(read(fd, (char*)&entry, sizeof entry));
        if (ret < 0) {
            D("Error while reading %s: %s\n", filepath, strerror(errno));
            break;
        }
        if (ret == 0 || (entry.tag == 0 && entry.value == 0))
          break;
        if (entry.tag == AT_HWCAP) {
          result = entry.value;
          break;
        }
    }
    close(fd);
    return result;
}

/* Compute the ELF HWCAP flags from the content of /proc/cpuinfo.
 * This works by parsing the 'Features' line, which lists which optional
 * features the device's CPU supports, on top of its reference
 * architecture.
 */
static uint32_t
get_elf_hwcap_from_proc_cpuinfo(const char* cpuinfo, int cpuinfo_len) {
    uint32_t hwcaps = 0;
    long architecture = 0;
    char* cpuArch = extract_cpuinfo_field(cpuinfo, cpuinfo_len, "CPU architecture");
    if (cpuArch) {
        architecture = strtol(cpuArch, NULL, 10);
        free(cpuArch);

        if (architecture >= 8L) {
            D("Faking 32-bit ARM HWCaps on ARMv%ld CPU\n", architecture);
            return HWCAP_SET_FOR_ARMV8;
        }
    }

    char* cpuFeatures = extract_cpuinfo_field(cpuinfo, cpuinfo_len, "Features");
    if (cpuFeatures != NULL) {
        D("Found cpuFeatures = '%s'\n", cpuFeatures);

        if (has_list_item(cpuFeatures, "vfp"))
            hwcaps |= HWCAP_VFP;
        if (has_list_item(cpuFeatures, "vfpv3"))
            hwcaps |= HWCAP_VFPv3;
        if (has_list_item(cpuFeatures, "vfpv3d16"))
            hwcaps |= HWCAP_VFPv3D16;
        if (has_list_item(cpuFeatures, "vfpv4"))
            hwcaps |= HWCAP_VFPv4;
        if (has_list_item(cpuFeatures, "neon"))
            hwcaps |= HWCAP_NEON;
        if (has_list_item(cpuFeatures, "idiva"))
            hwcaps |= HWCAP_IDIVA;
        if (has_list_item(cpuFeatures, "idivt"))
            hwcaps |= HWCAP_IDIVT;
        if (has_list_item(cpuFeatures, "idiv"))
            hwcaps |= HWCAP_IDIVA | HWCAP_IDIVT;
        if (has_list_item(cpuFeatures, "iwmmxt"))
            hwcaps |= HWCAP_IWMMXT;

        free(cpuFeatures);
    }
    return hwcaps;
}
#endif  /* __arm__ */

/* Return the number of cpus present on a given device.
 *
 * To handle all weird kernel configurations, we need to compute the
 * intersection of the 'present' and 'possible' CPU lists and count
 * the result.
 */
static int
get_cpu_count(void)
{
    CpuList cpus_present[1];
    CpuList cpus_possible[1];

    cpulist_read_from(cpus_present, "/sys/devices/system/cpu/present");
    cpulist_read_from(cpus_possible, "/sys/devices/system/cpu/possible");

    /* Compute the intersection of both sets to get the actual number of
     * CPU cores that can be used on this device by the kernel.
     */
    cpulist_and(cpus_present, cpus_possible);

    return cpulist_count(cpus_present);
}

static void
android_cpuInitFamily(void)
{
#if defined(__arm__)
    g_cpuFamily = ANDROID_CPU_FAMILY_ARM;
#elif defined(__i386__)
    g_cpuFamily = ANDROID_CPU_FAMILY_X86;
#elif defined(__mips64)
/* Needs to be before __mips__ since the compiler defines both */
    g_cpuFamily = ANDROID_CPU_FAMILY_MIPS64;
#elif defined(__mips__)
    g_cpuFamily = ANDROID_CPU_FAMILY_MIPS;
#elif defined(__aarch64__)
    g_cpuFamily = ANDROID_CPU_FAMILY_ARM64;
#elif defined(__x86_64__)
    g_cpuFamily = ANDROID_CPU_FAMILY_X86_64;
#else
    g_cpuFamily = ANDROID_CPU_FAMILY_UNKNOWN;
#endif
}

static void
android_cpuInit(void)
{
    char* cpuinfo = NULL;
    int   cpuinfo_len;

    android_cpuInitFamily();

    g_cpuFeatures = 0;
    g_cpuCount    = 1;
    g_inited      = 1;

    cpuinfo_len = get_file_size("/proc/cpuinfo");
    if (cpuinfo_len < 0) {
      D("cpuinfo_len cannot be computed!");
      return;
    }
    cpuinfo = (char*)malloc(cpuinfo_len);
    if (cpuinfo == NULL) {
      D("cpuinfo buffer could not be allocated");
      return;
    }
    cpuinfo_len = read_file("/proc/cpuinfo", cpuinfo, cpuinfo_len);
    D("cpuinfo_len is (%d):\n%.*s\n", cpuinfo_len,
      cpuinfo_len >= 0 ? cpuinfo_len : 0, cpuinfo);

    if (cpuinfo_len < 0)  /* should not happen */ {
        free(cpuinfo);
        return;
    }

    /* Count the CPU cores, the value may be 0 for single-core CPUs */
    g_cpuCount = get_cpu_count();
    if (g_cpuCount == 0) {
        g_cpuCount = 1;
    }

    D("found cpuCount = %d\n", g_cpuCount);

#ifdef __arm__
    {
        /* Extract architecture from the "CPU Architecture" field.
         * The list is well-known, unlike the the output of
         * the 'Processor' field which can vary greatly.
         *
         * See the definition of the 'proc_arch' array in
         * $KERNEL/arch/arm/kernel/setup.c and the 'c_show' function in
         * same file.
         */
        char* cpuArch = extract_cpuinfo_field(cpuinfo, cpuinfo_len, "CPU architecture");

        if (cpuArch != NULL) {
            char*  end;
            long   archNumber;
            int    hasARMv7 = 0;

            D("found cpuArch = '%s'\n", cpuArch);

            /* read the initial decimal number, ignore the rest */
            archNumber = strtol(cpuArch, &end, 10);

            /* Note that ARMv8 is upwards compatible with ARMv7. */
            if (end > cpuArch && archNumber >= 7) {
                hasARMv7 = 1;
            }

            /* Unfortunately, it seems that certain ARMv6-based CPUs
             * report an incorrect architecture number of 7!
             *
             * See http://code.google.com/p/android/issues/detail?id=10812
             *
             * We try to correct this by looking at the 'elf_format'
             * field reported by the 'Processor' field, which is of the
             * form of "(v7l)" for an ARMv7-based CPU, and "(v6l)" for
             * an ARMv6-one.
             */
            if (hasARMv7) {
                char* cpuProc = extract_cpuinfo_field(cpuinfo, cpuinfo_len,
                                                      "Processor");
                if (cpuProc != NULL) {
                    D("found cpuProc = '%s'\n", cpuProc);
                    if (has_list_item(cpuProc, "(v6l)")) {
                        D("CPU processor and architecture mismatch!!\n");
                        hasARMv7 = 0;
                    }
                    free(cpuProc);
                }
            }

            if (hasARMv7) {
                g_cpuFeatures |= ANDROID_CPU_ARM_FEATURE_ARMv7;
            }

            /* The LDREX / STREX instructions are available from ARMv6 */
            if (archNumber >= 6) {
                g_cpuFeatures |= ANDROID_CPU_ARM_FEATURE_LDREX_STREX;
            }

            free(cpuArch);
        }

        /* Extract the list of CPU features from ELF hwcaps */
        uint32_t hwcaps = 0;
        hwcaps = get_elf_hwcap_from_getauxval(AT_HWCAP);
        if (!hwcaps) {
            D("Parsing /proc/self/auxv to extract ELF hwcaps!\n");
            hwcaps = get_elf_hwcap_from_proc_self_auxv();
        }
        if (!hwcaps) {
            D("Parsing /proc/cpuinfo to extract ELF hwcaps!\n");
            hwcaps = get_elf_hwcap_from_proc_cpuinfo(cpuinfo, cpuinfo_len);
        }

        if (hwcaps != 0) {
            int has_vfp = (hwcaps & HWCAP_VFP);
            int has_vfpv3 = (hwcaps & HWCAP_VFPv3);
            int has_vfpv3d16 = (hwcaps & HWCAP_VFPv3D16);
            int has_vfpv4 = (hwcaps & HWCAP_VFPv4);
            int has_neon = (hwcaps & HWCAP_NEON);
            int has_idiva = (hwcaps & HWCAP_IDIVA);
            int has_idivt = (hwcaps & HWCAP_IDIVT);
            int has_iwmmxt = (hwcaps & HWCAP_IWMMXT);


            if (has_vfpv4)
                g_cpuFeatures |= ANDROID_CPU_ARM_FEATURE_VFPv3    |
                                 ANDROID_CPU_ARM_FEATURE_VFP_FP16 |
                                 ANDROID_CPU_ARM_FEATURE_VFP_FMA;

            if (has_vfpv3 || has_vfpv3d16)
                g_cpuFeatures |= ANDROID_CPU_ARM_FEATURE_VFPv3;

            if (has_vfp) {
              if (g_cpuFeatures & ANDROID_CPU_ARM_FEATURE_ARMv7)
                  g_cpuFeatures |= ANDROID_CPU_ARM_FEATURE_VFPv3;
              else
                  g_cpuFeatures |= ANDROID_CPU_ARM_FEATURE_VFPv2;
            }

            if (has_neon) {
                g_cpuFeatures |= ANDROID_CPU_ARM_FEATURE_VFPv3 |
                                 ANDROID_CPU_ARM_FEATURE_NEON |
                                 ANDROID_CPU_ARM_FEATURE_VFP_D32;
              if (has_vfpv4)
                  g_cpuFeatures |= ANDROID_CPU_ARM_FEATURE_NEON_FMA;
            }

            if (g_cpuFeatures & ANDROID_CPU_ARM_FEATURE_VFPv3)
                g_cpuFeatures |= ANDROID_CPU_ARM_FEATURE_VFPv2 |
                                 ANDROID_CPU_ARM_FEATURE_ARMv7;

            if (has_idiva)
                g_cpuFeatures |= ANDROID_CPU_ARM_FEATURE_IDIV_ARM;
            if (has_idivt)
                g_cpuFeatures |= ANDROID_CPU_ARM_FEATURE_IDIV_THUMB2;

            if (has_iwmmxt)
                g_cpuFeatures |= ANDROID_CPU_ARM_FEATURE_iWMMXt;
        }

        /* Extract the list of CPU features from ELF hwcaps2 */
        uint32_t hwcaps2 = 0;
        hwcaps2 = get_elf_hwcap_from_getauxval(AT_HWCAP2);
        if (hwcaps2 != 0) {
            int has_aes     = (hwcaps2 & HWCAP2_AES);
            int has_pmull   = (hwcaps2 & HWCAP2_PMULL);
            int has_sha1    = (hwcaps2 & HWCAP2_SHA1);
            int has_sha2    = (hwcaps2 & HWCAP2_SHA2);
            int has_crc32   = (hwcaps2 & HWCAP2_CRC32);

            if (has_aes)
                g_cpuFeatures |= ANDROID_CPU_ARM_FEATURE_AES;
            if (has_pmull)
                g_cpuFeatures |= ANDROID_CPU_ARM_FEATURE_PMULL;
            if (has_sha1)
                g_cpuFeatures |= ANDROID_CPU_ARM_FEATURE_SHA1;
            if (has_sha2)
                g_cpuFeatures |= ANDROID_CPU_ARM_FEATURE_SHA2;
            if (has_crc32)
                g_cpuFeatures |= ANDROID_CPU_ARM_FEATURE_CRC32;
        }
        /* Extract the cpuid value from various fields */
        static const struct CpuIdEntry {
            const char* field;
            char        format;
            char        bit_lshift;
            char        bit_length;
        } cpu_id_entries[] = {
            { "CPU implementer", 'x', 24, 8 },
            { "CPU variant", 'x', 20, 4 },
            { "CPU part", 'x', 4, 12 },
            { "CPU revision", 'd', 0, 4 },
        };
        size_t i;
        D("Parsing /proc/cpuinfo to recover CPUID\n");
        for (i = 0;
             i < sizeof(cpu_id_entries)/sizeof(cpu_id_entries[0]);
             ++i) {
            const struct CpuIdEntry* entry = &cpu_id_entries[i];
            char* value = extract_cpuinfo_field(cpuinfo,
                                                cpuinfo_len,
                                                entry->field);
            if (value == NULL)
                continue;

            D("field=%s value='%s'\n", entry->field, value);
            char* value_end = value + strlen(value);
            int val = 0;
            const char* start = value;
            const char* p;
            if (value[0] == '0' && (value[1] == 'x' || value[1] == 'X')) {
              start += 2;
              p = parse_hexadecimal(start, value_end, &val);
            } else if (entry->format == 'x')
              p = parse_hexadecimal(value, value_end, &val);
            else
              p = parse_decimal(value, value_end, &val);

            if (p > (const char*)start) {
              val &= ((1 << entry->bit_length)-1);
              val <<= entry->bit_lshift;
              g_cpuIdArm |= (uint32_t) val;
            }

            free(value);
        }

        static const struct CpuFix {
            uint32_t  cpuid;
            uint64_t  or_flags;
        } cpu_fixes[] = {
            /* The Nexus 4 (Qualcomm Krait) kernel configuration
             * forgets to report IDIV support. */
            { 0x510006f2, ANDROID_CPU_ARM_FEATURE_IDIV_ARM |
                          ANDROID_CPU_ARM_FEATURE_IDIV_THUMB2 },
            { 0x510006f3, ANDROID_CPU_ARM_FEATURE_IDIV_ARM |
                          ANDROID_CPU_ARM_FEATURE_IDIV_THUMB2 },
        };
        size_t n;
        for (n = 0; n < sizeof(cpu_fixes)/sizeof(cpu_fixes[0]); ++n) {
            const struct CpuFix* entry = &cpu_fixes[n];

            if (g_cpuIdArm == entry->cpuid)
                g_cpuFeatures |= entry->or_flags;
        }

        char* hardware = extract_cpuinfo_field(cpuinfo,
                                               cpuinfo_len,
                                               "Hardware");
        if (hardware) {
            if (!strcmp(hardware, "Goldfish") &&
                g_cpuIdArm == 0x4100c080 &&
                (g_cpuFamily & ANDROID_CPU_ARM_FEATURE_ARMv7) != 0) {
                g_cpuFeatures |= ANDROID_CPU_ARM_FEATURE_IDIV_ARM;
            }
            free(hardware);
        }
    }
#endif /* __arm__ */
#ifdef __aarch64__
    {
        /* Extract the list of CPU features from ELF hwcaps */
        uint32_t hwcaps = 0;
        hwcaps = get_elf_hwcap_from_getauxval(AT_HWCAP);
        if (hwcaps != 0) {
            int has_fp      = (hwcaps & HWCAP_FP);
            int has_asimd   = (hwcaps & HWCAP_ASIMD);
            int has_aes     = (hwcaps & HWCAP_AES);
            int has_pmull   = (hwcaps & HWCAP_PMULL);
            int has_sha1    = (hwcaps & HWCAP_SHA1);
            int has_sha2    = (hwcaps & HWCAP_SHA2);
            int has_crc32   = (hwcaps & HWCAP_CRC32);

            if(has_fp == 0) {
                D("ERROR: Floating-point unit missing, but is required by Android on AArch64 CPUs\n");
            }
            if(has_asimd == 0) {
                D("ERROR: ASIMD unit missing, but is required by Android on AArch64 CPUs\n");
            }

            if (has_fp)
                g_cpuFeatures |= ANDROID_CPU_ARM64_FEATURE_FP;
            if (has_asimd)
                g_cpuFeatures |= ANDROID_CPU_ARM64_FEATURE_ASIMD;
            if (has_aes)
                g_cpuFeatures |= ANDROID_CPU_ARM64_FEATURE_AES;
            if (has_pmull)
                g_cpuFeatures |= ANDROID_CPU_ARM64_FEATURE_PMULL;
            if (has_sha1)
                g_cpuFeatures |= ANDROID_CPU_ARM64_FEATURE_SHA1;
            if (has_sha2)
                g_cpuFeatures |= ANDROID_CPU_ARM64_FEATURE_SHA2;
            if (has_crc32)
                g_cpuFeatures |= ANDROID_CPU_ARM64_FEATURE_CRC32;
        }
    }
#endif /* __aarch64__ */

#if defined(__i386__) || defined(__x86_64__)
    int regs[4];

/* According to http://en.wikipedia.org/wiki/CPUID */
#define VENDOR_INTEL_b  0x756e6547
#define VENDOR_INTEL_c  0x6c65746e
#define VENDOR_INTEL_d  0x49656e69

    x86_cpuid(0, regs);
    int vendorIsIntel = (regs[1] == VENDOR_INTEL_b &&
                         regs[2] == VENDOR_INTEL_c &&
                         regs[3] == VENDOR_INTEL_d);

    x86_cpuid(1, regs);
    if ((regs[2] & (1 << 9)) != 0) {
        g_cpuFeatures |= ANDROID_CPU_X86_FEATURE_SSSE3;
    }
    if ((regs[2] & (1 << 23)) != 0) {
        g_cpuFeatures |= ANDROID_CPU_X86_FEATURE_POPCNT;
    }
    if ((regs[2] & (1 << 19)) != 0) {
        g_cpuFeatures |= ANDROID_CPU_X86_FEATURE_SSE4_1;
    }
    if ((regs[2] & (1 << 20)) != 0) {
        g_cpuFeatures |= ANDROID_CPU_X86_FEATURE_SSE4_2;
    }
    if (vendorIsIntel && (regs[2] & (1 << 22)) != 0) {
        g_cpuFeatures |= ANDROID_CPU_X86_FEATURE_MOVBE;
    }
    if ((regs[2] & (1 << 25)) != 0) {
        g_cpuFeatures |= ANDROID_CPU_X86_FEATURE_AES_NI;
    }
    if ((regs[2] & (1 << 28)) != 0) {
        g_cpuFeatures |= ANDROID_CPU_X86_FEATURE_AVX;
    }
    if ((regs[2] & (1 << 30)) != 0) {
        g_cpuFeatures |= ANDROID_CPU_X86_FEATURE_RDRAND;
    }

    x86_cpuid(7, regs);
    if ((regs[1] & (1 << 5)) != 0) {
        g_cpuFeatures |= ANDROID_CPU_X86_FEATURE_AVX2;
    }
    if ((regs[1] & (1 << 29)) != 0) {
        g_cpuFeatures |= ANDROID_CPU_X86_FEATURE_SHA_NI;
    }


#endif
#if defined( __mips__)
    {   /* MIPS and MIPS64 */
        /* Extract the list of CPU features from ELF hwcaps */
        uint32_t hwcaps = 0;
        hwcaps = get_elf_hwcap_from_getauxval(AT_HWCAP);
        if (hwcaps != 0) {
            int has_r6      = (hwcaps & HWCAP_MIPS_R6);
            int has_msa     = (hwcaps & HWCAP_MIPS_MSA);
            if (has_r6)
                g_cpuFeatures |= ANDROID_CPU_MIPS_FEATURE_R6;
            if (has_msa)
                g_cpuFeatures |= ANDROID_CPU_MIPS_FEATURE_MSA;
        }
    }
#endif /* __mips__ */

    free(cpuinfo);
}


AndroidCpuFamily
android_getCpuFamily(void)
{
    pthread_once(&g_once, android_cpuInit);
    return g_cpuFamily;
}


uint64_t
android_getCpuFeatures(void)
{
    pthread_once(&g_once, android_cpuInit);
    return g_cpuFeatures;
}


int
android_getCpuCount(void)
{
    pthread_once(&g_once, android_cpuInit);
    return g_cpuCount;
}

static void
android_cpuInitDummy(void)
{
    g_inited = 1;
}

int
android_setCpu(int cpu_count, uint64_t cpu_features)
{
    /* Fail if the library was already initialized. */
    if (g_inited)
        return 0;

    android_cpuInitFamily();
    g_cpuCount = (cpu_count <= 0 ? 1 : cpu_count);
    g_cpuFeatures = cpu_features;
    pthread_once(&g_once, android_cpuInitDummy);

    return 1;
}

#ifdef __arm__
uint32_t
android_getCpuIdArm(void)
{
    pthread_once(&g_once, android_cpuInit);
    return g_cpuIdArm;
}

int
android_setCpuArm(int cpu_count, uint64_t cpu_features, uint32_t cpu_id)
{
    if (!android_setCpu(cpu_count, cpu_features))
        return 0;

    g_cpuIdArm = cpu_id;
    return 1;
}
#endif  /* __arm__ */

/*
 * Technical note: Making sense of ARM's FPU architecture versions.
 *
 * FPA was ARM's first attempt at an FPU architecture. There is no Android
 * device that actually uses it since this technology was already obsolete
 * when the project started. If you see references to FPA instructions
 * somewhere, you can be sure that this doesn't apply to Android at all.
 *
 * FPA was followed by "VFP", soon renamed "VFPv1" due to the emergence of
 * new versions / additions to it. ARM considers this obsolete right now,
 * and no known Android device implements it either.
 *
 * VFPv2 added a few instructions to VFPv1, and is an *optional* extension
 * supported by some ARMv5TE, ARMv6 and ARMv6T2 CPUs. Note that a device
 * supporting the 'armeabi' ABI doesn't necessarily support these.
 *
 * VFPv3-D16 adds a few instructions on top of VFPv2 and is typically used
 * on ARMv7-A CPUs which implement a FPU. Note that it is also mandated
 * by the Android 'armeabi-v7a' ABI. The -D16 suffix in its name means
 * that it provides 16 double-precision FPU registers (d0-d15) and 32
 * single-precision ones (s0-s31) which happen to be mapped to the same
 * register banks.
 *
 * VFPv3-D32 is the name of an extension to VFPv3-D16 that provides 16
 * additional double precision registers (d16-d31). Note that there are
 * still only 32 single precision registers.
 *
 * VFPv3xD is a *subset* of VFPv3-D16 that only provides single-precision
 * registers. It is only used on ARMv7-M (i.e. on micro-controllers) which
 * are not supported by Android. Note that it is not compatible with VFPv2.
 *
 * NOTE: The term 'VFPv3' usually designate either VFPv3-D16 or VFPv3-D32
 *       depending on context. For example GCC uses it for VFPv3-D32, but
 *       the Linux kernel code uses it for VFPv3-D16 (especially in
 *       /proc/cpuinfo). Always try to use the full designation when
 *       possible.
 *
 * NEON, a.k.a. "ARM Advanced SIMD" is an extension that provides
 * instructions to perform parallel computations on vectors of 8, 16,
 * 32, 64 and 128 bit quantities. NEON requires VFPv32-D32 since all
 * NEON registers are also mapped to the same register banks.
 *
 * VFPv4-D16, adds a few instructions on top of VFPv3-D16 in order to
 * perform fused multiply-accumulate on VFP registers, as well as
 * half-precision (16-bit) conversion operations.
 *
 * VFPv4-D32 is VFPv4-D16 with 32, instead of 16, FPU double precision
 * registers.
 *
 * VPFv4-NEON is VFPv4-D32 with NEON instructions. It also adds fused
 * multiply-accumulate instructions that work on the NEON registers.
 *
 * NOTE: Similarly, "VFPv4" might either reference VFPv4-D16 or VFPv4-D32
 *       depending on context.
 *
 * The following information was determined by scanning the binutils-2.22
 * sources:
 *
 * Basic VFP instruction subsets:
 *
 * #define FPU_VFP_EXT_V1xD 0x08000000     // Base VFP instruction set.
 * #define FPU_VFP_EXT_V1   0x04000000     // Double-precision insns.
 * #define FPU_VFP_EXT_V2   0x02000000     // ARM10E VFPr1.
 * #define FPU_VFP_EXT_V3xD 0x01000000     // VFPv3 single-precision.
 * #define FPU_VFP_EXT_V3   0x00800000     // VFPv3 double-precision.
 * #define FPU_NEON_EXT_V1  0x00400000     // Neon (SIMD) insns.
 * #define FPU_VFP_EXT_D32  0x00200000     // Registers D16-D31.
 * #define FPU_VFP_EXT_FP16 0x00100000     // Half-precision extensions.
 * #define FPU_NEON_EXT_FMA 0x00080000     // Neon fused multiply-add
 * #define FPU_VFP_EXT_FMA  0x00040000     // VFP fused multiply-add
 *
 * FPU types (excluding NEON)
 *
 * FPU_VFP_V1xD (EXT_V1xD)
 *    |
 *    +--------------------------+
 *    |                          |
 * FPU_VFP_V1 (+EXT_V1)       FPU_VFP_V3xD (+EXT_V2+EXT_V3xD)
 *    |                          |
 *    |                          |
 * FPU_VFP_V2 (+EXT_V2)       FPU_VFP_V4_SP_D16 (+EXT_FP16+EXT_FMA)
 *    |
 * FPU_VFP_V3D16 (+EXT_Vx3D+EXT_V3)
 *    |
 *    +--------------------------+
 *    |                          |
 * FPU_VFP_V3 (+EXT_D32)     FPU_VFP_V4D16 (+EXT_FP16+EXT_FMA)
 *    |                          |
 *    |                      FPU_VFP_V4 (+EXT_D32)
 *    |
 * FPU_VFP_HARD (+EXT_FMA+NEON_EXT_FMA)
 *
 * VFP architectures:
 *
 * ARCH_VFP_V1xD  (EXT_V1xD)
 *   |
 *   +------------------+
 *   |                  |
 *   |             ARCH_VFP_V3xD (+EXT_V2+EXT_V3xD)
 *   |                  |
 *   |             ARCH_VFP_V3xD_FP16 (+EXT_FP16)
 *   |                  |
 *   |             ARCH_VFP_V4_SP_D16 (+EXT_FMA)
 *   |
 * ARCH_VFP_V1 (+EXT_V1)
 *   |
 * ARCH_VFP_V2 (+EXT_V2)
 *   |
 * ARCH_VFP_V3D16 (+EXT_V3xD+EXT_V3)
 *   |
 *   +-------------------+
 *   |                   |
 *   |         ARCH_VFP_V3D16_FP16  (+EXT_FP16)
 *   |
 *   +-------------------+
 *   |                   |
 *   |         ARCH_VFP_V4_D16 (+EXT_FP16+EXT_FMA)
 *   |                   |
 *   |         ARCH_VFP_V4 (+EXT_D32)
 *   |                   |
 *   |         ARCH_NEON_VFP_V4 (+EXT_NEON+EXT_NEON_FMA)
 *   |
 * ARCH_VFP_V3 (+EXT_D32)
 *   |
 *   +-------------------+
 *   |                   |
 *   |         ARCH_VFP_V3_FP16 (+EXT_FP16)
 *   |
 * ARCH_VFP_V3_PLUS_NEON_V1 (+EXT_NEON)
 *   |
 * ARCH_NEON_FP16 (+EXT_FP16)
 *
 * -fpu=<name> values and their correspondance with FPU architectures above:
 *
 *   {"vfp",               FPU_ARCH_VFP_V2},
 *   {"vfp9",              FPU_ARCH_VFP_V2},
 *   {"vfp3",              FPU_ARCH_VFP_V3}, // For backwards compatbility.
 *   {"vfp10",             FPU_ARCH_VFP_V2},
 *   {"vfp10-r0",          FPU_ARCH_VFP_V1},
 *   {"vfpxd",             FPU_ARCH_VFP_V1xD},
 *   {"vfpv2",             FPU_ARCH_VFP_V2},
 *   {"vfpv3",             FPU_ARCH_VFP_V3},
 *   {"vfpv3-fp16",        FPU_ARCH_VFP_V3_FP16},
 *   {"vfpv3-d16",         FPU_ARCH_VFP_V3D16},
 *   {"vfpv3-d16-fp16",    FPU_ARCH_VFP_V3D16_FP16},
 *   {"vfpv3xd",           FPU_ARCH_VFP_V3xD},
 *   {"vfpv3xd-fp16",      FPU_ARCH_VFP_V3xD_FP16},
 *   {"neon",              FPU_ARCH_VFP_V3_PLUS_NEON_V1},
 *   {"neon-fp16",         FPU_ARCH_NEON_FP16},
 *   {"vfpv4",             FPU_ARCH_VFP_V4},
 *   {"vfpv4-d16",         FPU_ARCH_VFP_V4D16},
 *   {"fpv4-sp-d16",       FPU_ARCH_VFP_V4_SP_D16},
 *   {"neon-vfpv4",        FPU_ARCH_NEON_VFP_V4},
 *
 *
 * Simplified diagram that only includes FPUs supported by Android:
 * Only ARCH_VFP_V3D16 is actually mandated by the armeabi-v7a ABI,
 * all others are optional and must be probed at runtime.
 *
 * ARCH_VFP_V3D16 (EXT_V1xD+EXT_V1+EXT_V2+EXT_V3xD+EXT_V3)
 *   |
 *   +-------------------+
 *   |                   |
 *   |         ARCH_VFP_V3D16_FP16  (+EXT_FP16)
 *   |
 *   +-------------------+
 *   |                   |
 *   |         ARCH_VFP_V4_D16 (+EXT_FP16+EXT_FMA)
 *   |                   |
 *   |         ARCH_VFP_V4 (+EXT_D32)
 *   |                   |
 *   |         ARCH_NEON_VFP_V4 (+EXT_NEON+EXT_NEON_FMA)
 *   |
 * ARCH_VFP_V3 (+EXT_D32)
 *   |
 *   +-------------------+
 *   |                   |
 *   |         ARCH_VFP_V3_FP16 (+EXT_FP16)
 *   |
 * ARCH_VFP_V3_PLUS_NEON_V1 (+EXT_NEON)
 *   |
 * ARCH_NEON_FP16 (+EXT_FP16)
 *
 */

PRAGMA_DIAGNOSTIC_POP()


static thread_local JNIEnv* gJniEnv = nullptr;
static AtomicUint32 gJniAttachedThreadCount;

#if CONFIG_ENABLE_ASSERT
static constexpr uint32 kJniMaxAttachedThreadCount = 5;
#endif

void OS::GetSysInfo(SysInfo* info)
{
    info->coreCount = android_getCpuCount();
    info->pageSize = OS::GetPageSize();

    switch (android_getCpuFamily()) {
    case ANDROID_CPU_FAMILY_ARM:        info->cpuFamily = SysInfo::CpuFamily::ARM;    break;
    case ANDROID_CPU_FAMILY_ARM64:      info->cpuFamily = SysInfo::CpuFamily::ARM64;  break;
    case ANDROID_CPU_FAMILY_X86:        
    case ANDROID_CPU_FAMILY_X86_64:     info->cpuFamily = SysInfo::CpuFamily::x86_64; break;
    default:                            
        ASSERT_MSG(0, "Hardware not supported"); info->cpuFamily = SysInfo::CpuFamily::Unknown; break;
    }

    uint64 features  = android_getCpuFeatures();
    if (info->cpuFamily == SysInfo::CpuFamily::ARM || info->cpuFamily == SysInfo::CpuFamily::ARM64) {
        if (features & ANDROID_CPU_ARM_FEATURE_NEON)
            info->cpuCapsNeon = true;
    }
    else if (info->cpuFamily == SysInfo::CpuFamily::x86_64) {
        if (features & ANDROID_CPU_X86_FEATURE_SSSE3)
            info->cpuCapsSSE3 = true;
        if (features & ANDROID_CPU_X86_FEATURE_SSE4_1)
            info->cpuCapsSSE41 = true;
        if (features & ANDROID_CPU_X86_FEATURE_SSE4_2)
            info->cpuCapsSSE42 = true;
        if (features & ANDROID_CPU_X86_FEATURE_AVX)
            info->cpuCapsAVX = true;
        if (features & ANDROID_CPU_X86_FEATURE_AVX2)
            info->cpuCapsAVX2 = true;
    }

    {
        File f;
        if (f.Open("/proc/meminfo", FileOpenFlags::Read|FileOpenFlags::SeqScan)) {
            Blob data;
            data.SetGrowPolicy(Blob::GrowPolicy::Linear);
            size_t numChars;
            char bulk[512];

            while ((numChars = f.Read<char>(bulk, sizeof(bulk))) > 0) {
                data.Write(bulk, numChars);
            }
            data.Write<char>('\0');
            f.Close();

            char* text;
            data.Detach((void**)&text, &numChars);
            
            const char* memTotalLine = Str::FindStr(text, "MemTotal:");
            if (memTotalLine) {
               memTotalLine += 9;
               char memText[32];
               uint32 memTextSize = 0;

               while (Str::IsWhitespace(*memTotalLine))
                   memTotalLine++;
               
               while (Str::IsNumber(*memTotalLine)) {
                   memText[memTextSize++] = *memTotalLine;
                   memTotalLine++;
               }
               memText[memTextSize] = '\0';
               info->physicalMemorySize = Str::ToUint64(memText)*SIZE_KB;
            }

            Mem::Free(text);
        }
    }

    {
        File f;
        if (f.Open("/proc/cpuinfo", FileOpenFlags::Read|FileOpenFlags::SeqScan)) {
            Blob data;
            data.SetGrowPolicy(Blob::GrowPolicy::Linear);
            size_t numChars;
            char bulk[512];

            while ((numChars = f.Read<char>(bulk, sizeof(bulk))) > 0) {
                data.Write(bulk, numChars);
            }
            data.Write<char>('\0');
            f.Close();

            char* text;
            data.Detach((void**)&text, &numChars);
            Str::Trim(text, numChars, text, '\n');
            
            const char* lastNewline = Str::FindCharRev(text, '\n');
            if (lastNewline) {
                const char* lastLine = lastNewline + 1;
                if (Str::IsEqualCount(lastLine, "Hardware", 8)) {
                    const char* colon = Str::FindChar(lastLine, ':');
                    if (colon) {
                        Str::Copy(info->cpuModel, sizeof(info->cpuModel), colon + 1);
                        Str::Trim(info->cpuModel, sizeof(info->cpuModel), info->cpuModel, ' ');
                    }
                }
            }

            Mem::Free(text);

        }
    }
}

char* OS::GetMyPath(char*, size_t)
{
    ASSERT_MSG(0, "Exe path is not implemented on android");
    return nullptr;
}

void OS::SetCurrentDir(const char*)
{
    ASSERT_MSG(0, "SetCurrentDir is not implemented on android");
}

char* OS::GetCurrentDir(char*, size_t)
{
    ASSERT_MSG(0, "GetCurrentDir is not implemented on android");
    return nullptr;
}

void OS::AndroidPrintToLog(OSAndroidLogType logType, const char* tag, const char* text)
{
    static_assert(OSAndroidLogType::Unknown == static_cast<OSAndroidLogType>(ANDROID_LOG_UNKNOWN));
    static_assert(OSAndroidLogType::Default == static_cast<OSAndroidLogType>(ANDROID_LOG_DEFAULT));
    static_assert(OSAndroidLogType::Verbose == static_cast<OSAndroidLogType>(ANDROID_LOG_VERBOSE));
    static_assert(OSAndroidLogType::Debug == static_cast<OSAndroidLogType>(ANDROID_LOG_DEBUG));
    static_assert(OSAndroidLogType::Info == static_cast<OSAndroidLogType>(ANDROID_LOG_INFO));
    static_assert(OSAndroidLogType::Warn == static_cast<OSAndroidLogType>(ANDROID_LOG_WARN));
    static_assert(OSAndroidLogType::Error == static_cast<OSAndroidLogType>(ANDROID_LOG_ERROR));
    static_assert(OSAndroidLogType::Fatal == static_cast<OSAndroidLogType>(ANDROID_LOG_FATAL));
    static_assert(OSAndroidLogType::Silent == static_cast<OSAndroidLogType>(ANDROID_LOG_SILENT));

    __android_log_write(static_cast<int>(logType), tag, text);
}

JNIEnv* OS::AndroidAcquireJniEnv(ANativeActivity* activity)
{
    if (gJniEnv)
        return gJniEnv;
    ASSERT(activity);

    [[maybe_unused]] jint ret = activity->vm->AttachCurrentThread(&gJniEnv, nullptr);	// required to call JNIEnv functions on this thread
    ASSERT(ret == JNI_OK);
    [[maybe_unused]] uint32 activeThreadCount = Atomic::FetchAdd(&gJniAttachedThreadCount, 1);
    ASSERT_MSG(activeThreadCount <= kJniMaxAttachedThreadCount, "Too many AcquireJniEnv in several threads");
    return gJniEnv;
}

void OS::AndroidReleaseJniEnv(ANativeActivity* activity)
{
    ASSERT(activity);
    activity->vm->DetachCurrentThread();		// jni cleanup
    Atomic::FetchSub(&gJniAttachedThreadCount, 1);
}

JNIEnv* OS::AndroidGetJniEnv()
{
    ASSERT_MSG(gJniEnv != nullptr, "JNI not attached. Call sysAndroidAcquireJniEnv/sysAndroidReleaseJniEnv on the calling thread");
    return gJniEnv;
}

bool OS::IsDebuggerPresent()
{
    JNIEnv* jniEnv = OS::AndroidGetJniEnv();
    jclass clz = jniEnv->FindClass("android/os/Debug");
    ASSERT(clz);
    jmethodID funcId = jniEnv->GetStaticMethodID(clz, "isDebuggerConnected", "()Z");
    ASSERT(funcId);
    jboolean isConnected = jniEnv->CallStaticBooleanMethod(clz, funcId);
    jniEnv->DeleteLocalRef(clz);
    
    return isConnected;
}

Path OS::AndroidGetCacheDirectory(ANativeActivity* activity)
{
    JNIEnv* jniEnv = OS::AndroidGetJniEnv();

    jobject context = activity->clazz;
    jclass contextClass = jniEnv->GetObjectClass(context);

    jmethodID getCacheDirMethod = jniEnv->GetMethodID(contextClass, "getCacheDir", "()Ljava/io/File;");
    jobject cacheDir = jniEnv->CallObjectMethod(context, getCacheDirMethod);

    jclass fileClass = jniEnv->GetObjectClass(cacheDir);
    jmethodID getPathMethod = jniEnv->GetMethodID(fileClass, "getPath", "()Ljava/lang/String;");
    jstring pathString = (jstring) jniEnv->CallObjectMethod(cacheDir, getPathMethod);

    const char* path = jniEnv->GetStringUTFChars(pathString, nullptr);
    Path r(path);
    jniEnv->ReleaseStringUTFChars(pathString, path);

    return r;
}

#endif // PLATFORM_ANDROID
    #elif PLATFORM_OSX
//----------------------------------------------------------------------------------------------------------------------
// SystemMac.cpp


#if PLATFORM_APPLE

#include <mach/mach_time.h>
#include <mach-o/dyld.h>        // _NSGetExecutablePath
#include <unistd.h>             // sysconf
#include <dlfcn.h>              // dlopen, dlclose, dlsym
#include <dispatch/dispatch.h>
#include <mach/mach.h>
#include <pthread.h>            // pthread_t and family
#include <sys/sysctl.h>
#include <pthread.h>
#include <stdio.h>              // puts

struct SemaphoreImpl
{
    dispatch_semaphore_t handle;
};

struct TimerState 
{
    bool init;
    mach_timebase_info_data_t timebase;
    uint64 start;
};

static TimerState gTimer;

static_assert(sizeof(SemaphoreImpl) <= sizeof(Semaphore), "Sempahore size mismatch");

void Semaphore::Initialize()
{
    SemaphoreImpl* sem = (SemaphoreImpl*)mData;
    sem->handle = dispatch_semaphore_create(0);
    ASSERT_MSG(sem->handle != NULL, "dispatch_semaphore_create failed");

    _private::CountersAddSemaphore();
}

void Semaphore::Release()
{
    SemaphoreImpl* sem = (SemaphoreImpl*)mData;
    if (sem->handle) {
        sem->handle = NULL;

        _private::CountersRemoveSemaphore();
    }
}

void Semaphore::Post(uint32 count)
{
    SemaphoreImpl* sem = (SemaphoreImpl*)mData;
    if (sem->handle) {
        for (int i = 0; i < count; i++)
            dispatch_semaphore_signal(sem->handle);
    }
}

bool Semaphore::Wait(uint32 msecs)
{
    SemaphoreImpl* sem = (SemaphoreImpl*)mData;
    if (sem->handle) {
        dispatch_time_t dt = msecs < 0 ? DISPATCH_TIME_FOREVER
                                       : dispatch_time(DISPATCH_TIME_NOW, (int64_t)msecs * 1000000ll);
        return !dispatch_semaphore_wait(sem->handle, dt);
    }
    else {
        return false;
    }
}

namespace Timer
{
    FORCE_INLINE int64_t _Int64MulDiv(int64_t value, int64_t numer, int64_t denom)
    {
        int64_t q = value / denom;
        int64_t r = value % denom;
        return q * numer + r * numer / denom;
    }
} // Timer

void Timer::Initialize() 
{
    gTimer.init = true;
    mach_timebase_info(&gTimer.timebase);
    gTimer.start = mach_absolute_time();
}

uint64 Timer::GetTicks() 
{
    ASSERT_MSG(gTimer.init, "Timer not initialized. call Timer::Initialize()");
    const uint64 machNow = mach_absolute_time() - gTimer.start;
    return _Int64MulDiv(machNow, gTimer.timebase.numer, gTimer.timebase.denom);
}

char* OS::GetMyPath(char* dst, size_t dstSize)
{
    uint32 size32 = (uint32)dstSize;
    _NSGetExecutablePath(dst, (uint32_t*)&size32);
    return dst;
}

char* OS::GetCurrentDir(char* dst, size_t dstSize)
{
    return getcwd(dst, dstSize);
}

void OS::SetCurrentDir(const char* path)
{
    chdir(path);
}

void OS::GetSysInfo(SysInfo* info)
{
    memset(info, 0x0, sizeof(*info));
    
    {
        int ncpu;
        size_t ncpuLen = sizeof(ncpu);
        if (sysctlbyname("hw.ncpu", &ncpu, &ncpuLen, nullptr, 0) == 0)
            info->coreCount = (uint32)ncpu;
    }
    
    {
        uint64 physMem;
        size_t physMemSize = sizeof(physMem);
        if (sysctlbyname("hw.memsize", &physMem, &physMemSize, nullptr, 0) == 0)
            info->physicalMemorySize = physMem;
    }
        
    info->pageSize = OS::GetPageSize();
    
}

bool OS::IsDebuggerPresent()
{
    int mib[4];
    struct kinfo_proc info;
    size_t size = sizeof(info);

    mib[0] = CTL_KERN;
    mib[1] = KERN_PROC;
    mib[2] = KERN_PROC_PID;
    mib[3] = getpid();

    if (sysctl(mib, 4, &info, &size, NULL, 0) == -1) {
        puts("Failed to retrieve process information.");
        return false;
    }

    return (info.kp_proc.p_flag & P_TRACED) != 0;
}

char* OS::GetHomeDir(char* dst, size_t dstSize)
{
    #if PLATFORM_OSX
        const char* homeDir = getenv("HOME");
        ASSERT(homeDir);
        Str::Copy(dst, (uint32)dstSize, homeDir);
        return dst;
    #else
        ASSERT(0, "Not implemented in iOS");
        return nullptr;
    #endif
}

char* OS::GetCacheDir(char* dst, size_t dstSize, const char* appName)
{
    #if PLATFORM_OSX
        const char* homeDir = getenv("HOME");
        ASSERT(homeDir);
        Str::Copy(dst, (uint32)dstSize, homeDir);
        Str::Concat(dst, (uint32)dstSize, "/Library/Application Support/");
        Str::Concat(dst, (uint32)dstSize, appName);
        return dst;
    #else
        ASSERT(0, "Not implemented");
        return nullptr;
    #endif
}

#define USE_AIO 0
#define USE_LIBDISPATCH 0
#if USE_AIO
#include <aio.h>
#include <errno.h>

struct AsyncContext
{
};

struct AsyncFileMac
{
    aiocb cb;
    AsyncFile f;
    MemAllocator* alloc;
    int fd;
    AsyncFileCallback readFn;
};

static AsyncContext gAsyncCtx;

bool Async::Initialize()
{
    return true;
}

void Async::Release()
{
}

namespace Async
{
    static void _AIOCompletionHandler(sigval val)
    {
        AsyncFileMac* file = (AsyncFileMac*)val.sival_ptr;
        ASSERT(file->readFn);
        file->readFn(&file->f, aio_error(&file->cb) != 0);
    }

    static inline AsyncFileMac* _GetInternalFilePtr(AsyncFile* f)
    {
        return (AsyncFileMac*)((uint8*)f - offsetof(AsyncFileMac, f));
    }
}

AsyncFile* Async::ReadFile(const char* filepath, const AsyncFileRequest& request)
{
    int fd = open(filepath, O_RDONLY, 0);
    if (fd == -1)
        return nullptr;
    
    uint64 fileSize = request.sizeHint;
    uint64 fileModificationTime = 0;
    
    if (!fileSize) {
        PathInfo info = OS::GetPathInfo(filepath);
        if (info.type != PathType::File) {
            close(fd);
            return nullptr;
        }
        
        fileSize = info.size;
        fileModificationTime = info.lastModified;
    }
    
    MemSingleShotMalloc<AsyncFileMac> mallocator;
    uint8* data;
    uint8* userData = nullptr;
    if (request.userDataAllocateSize)
        mallocator.AddExternalPointerField<uint8>(&userData, request.userDataAllocateSize);
    mallocator.AddExternalPointerField<uint8>(&data, fileSize);
    
    AsyncFileMac* file = mallocator.Malloc(request.alloc);
    memset(file, 0x0, sizeof(*file));
    
    file->cb.aio_fildes = fd;
    file->cb.aio_buf = data;
    file->cb.aio_nbytes = fileSize;
    file->cb.aio_offset = 0;
    file->cb.aio_sigevent.sigev_notify = SIGEV_THREAD;
    file->cb.aio_sigevent.sigev_notify_function = Async::_AIOCompletionHandler;
    file->cb.aio_sigevent.sigev_value.sival_ptr = &file;
    
    file->f.filepath = filepath;
    file->f.data = data;
    file->f.size = uint32(fileSize);
    file->f.lastModifiedTime = fileModificationTime;
    if (request.userData) {
        if (request.userDataAllocateSize) {
            memcpy(userData, request.userData, request.userDataAllocateSize);
            file->f.userData = userData;
        }
        else {
            file->f.userData = request.userData;
        }
    }

    file->fd = fd;
    file->alloc = request.alloc;
    file->readFn = request.readFn;

    if (aio_read(&file->cb) == -1) {
        LOG_ERROR("AIO failed reading file (Code: %u)", errno);
        close(fd);
        MemSingleShotMalloc<AsyncFileMac>::Free(file, request.alloc);
        return nullptr;
        if (aio_error(&file->cb) != EINPROGRESS) {
        }
    }

    return &file->f;
}

void Async::Close(AsyncFile* file)
{
    AsyncFileMac* fm = _GetInternalFilePtr(file);
    if (fm->fd)
        close(fm->fd);
    MemSingleShotMalloc<AsyncFileMac>::Free(fm, fm->alloc);
}

bool Async::Wait(AsyncFile* file)
{
    ASSERT_MSG(0, "Not implemented");
    return false;
}

bool Async::IsFinished(AsyncFile* file, bool* outError)
{
    ASSERT_MSG(0, "Not implemented");
    return false;
}

#elif USE_LIBDISPATCH
struct AsyncContext
{
    dispatch_queue_t queue;
};

struct AsyncFileMac
{
    AsyncFile f;
    MemAllocator* alloc;
    dispatch_io_t io;
    AsyncFileCallback readFn;
    AtomicUint32 done;
};

bool Async::Initialize()
{
    gAsyncCtx.queue = dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0);
    if (!gAsyncCtx.queue)
        return false;
    
    return true;
}

void Async::Release()
{
}

AsyncFile* Async::ReadFile(const char* filepath, const AsyncFileRequest& request)
{
    PathInfo info = OS::GetPathInfo(filepath);
    if (info.type != PathType::File)
        return nullptr;
    
    dispatch_io_t io = dispatch_io_create_with_path(DISPATCH_IO_STREAM, filepath, O_RDONLY, 0, gAsyncCtx.queue, ^(int error) {
        ASSERT_MSG(error == 0, "Unexpected open file: %s (error: %u)", filepath, error);
    });
    
    ASSERT(io);
    ASSERT(request.readFn);

    uint64 fileSize = request.sizeHint;
    if (!fileSize)
        fileSize = info.size;
    
    ASSERT_MSG(fileSize < UINT32_MAX, "Large file sizes are not supported by win32 overlapped API");
    ASSERT_MSG(!request.userDataAllocateSize || (request.userData && request.userDataAllocateSize),
               "`userDataAllocatedSize` should be accompanied with a valid `userData` pointer");
    
    MemSingleShotMalloc<AsyncFileMac> mallocator;
    uint8* data;
    uint8* userData = nullptr;
    if (request.userDataAllocateSize)
        mallocator.AddExternalPointerField<uint8>(&userData, request.userDataAllocateSize);
    mallocator.AddExternalPointerField<uint8>(&data, fileSize);
    
    AsyncFileMac* file = mallocator.Malloc(request.alloc);
    memset(file, 0x0, sizeof(*file));
    file->f.filepath = filepath;
    file->f.data = data;
    file->f.size = uint32(fileSize);
    file->f.lastModifiedTime = info.lastModified;
    if (request.userData) {
        if (request.userDataAllocateSize) {
            memcpy(userData, request.userData, request.userDataAllocateSize);
            file->f.userData = userData;
        }
        else {
            file->f.userData = request.userData;
        }
    }

    file->io = io;
    file->alloc = request.alloc;
    file->readFn = request.readFn;
    
    dispatch_io_read(io, 0, fileSize, gAsyncCtx.queue, ^(bool done, dispatch_data_t data, int error) {
        if (done) {
            if (error == 0) {
                const void* buffer;
                size_t size;
                dispatch_data_t newData = dispatch_data_create_map(data, &buffer, &size);
                ASSERT(buffer);
                memcpy(file->f.data, buffer, size);
                dispatch_release(newData);
            }
            
            file->readFn(&file->f, error == 0);
            dispatch_release(data);
            
            Atomic::StoreExplicit(&file->done, 1, AtomicMemoryOrder::Release);
        }
    });

    return &file->f;
}

void Async::Close(AsyncFile* file)
{
    ASSERT(file);
    AsyncFileMac* f = (AsyncFileMac*)file;
    if (f->io)
        dispatch_release(f->io);
    if (f->alloc)
        Mem::Free(f, f->alloc);
}

bool Async::Wait(AsyncFile* file)
{
    ASSERT_MSG(0, "Not implemented");
    return false;
}

bool Async::IsFinished(AsyncFile* file, bool* outError)
{
    ASSERT(file);
    AsyncFileMac* f = (AsyncFileMac*)file;
    return Atomic::LoadExplicit(&f->done, AtomicMemoryOrder::Acquire);
}
#endif

#endif // PLATFORM_APPLE




    #elif PLATFORM_LINUX
//----------------------------------------------------------------------------------------------------------------------
// SystemLinux.cpp


#if PLATFORM_LINUX

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

char* OS::GetMyPath(char* dst, size_t dstSize)
{
    ssize_t len = readlink("/proc/self/exe", dst, dstSize - 1);
    ASSERT(len != -1);
    dst[len] = '\0';
    return dst;
}

char* OS::GetCurrentDir(char* dst, size_t dstSize)
{
    return getcwd(dst, dstSize);
}

void OS::SetCurrentDir(const char* path)
{
    [[maybe_unused]] int r = chdir(path);
    ASSERT(r != -1);
}

void OS::GetSysInfo(SysInfo* sysInfo)
{
    auto cpuid = [](int func, int subfunc, int *eax, int *ebx, int *ecx, int *edx) 
    {
        int a, b, c, d;
        __asm__ volatile (
            "push %%rbx\n"      // Save rbx (callee-saved)
            "cpuid\n"
            "movl %%ebx, %1\n"   // Move 32-bit ebx to output variable
            "pop %%rbx\n"       // Restore original rbx
            : "=a"(a), "=r"(b), "=c"(c), "=d"(d)
            : "a"(func), "c"(subfunc)
            : "memory"
        );
        *eax = a;
        *ebx = b;
        *ecx = c;
        *edx = d;
    };
    
    {
        constexpr int CPUID_GET_FEATURES = 1;
        int eax, ebx, ecx, edx;
        cpuid(CPUID_GET_FEATURES, 0, &eax, &ebx, &ecx, &edx);
        sysInfo->cpuCapsSSE = edx & (1 << 25);
        sysInfo->cpuCapsSSE2 = edx & (1 << 26);
        sysInfo->cpuCapsSSE3 = (ecx & (1 << 0));
        sysInfo->cpuCapsSSE41 = (ecx & (1 << 19));
        sysInfo->cpuCapsSSE42 = (ecx & (1 << 20));
        sysInfo->cpuCapsAVX = (ecx & (1 << 28));
        sysInfo->cpuCapsAVX2 = (ebx & (1 << 5));
    }

    sysInfo->pageSize = sysconf(_SC_PAGESIZE);

    {
        struct CoreInfo {
            int physical_id;
            int core_id;
        };

        uint32 count = 0;
        int curPhysicalCore = -1, curCore = -1;
        CoreInfo cores[256];

        FILE *fp = fopen("/proc/cpuinfo", "r");
        if (fp != nullptr) {
            char line[256];
            char model[128] = "";
            char name[128] = "";
            
            while (fgets(line, sizeof(line), fp)) {
                if (!name[0] && strncmp(line, "vendor_id", 9) == 0)
                    sscanf(line, "vendor_id : %[^\n]", name);
                if (!model[0] && strncmp(line, "model name", 10) == 0)
                    sscanf(line, "model name : %[^\n]", model);
                if (strncmp(line, "physical id", 11) == 0) {
                    sscanf(line, "physical id : %d", &curPhysicalCore);
                } else if (strncmp(line, "core id", 7) == 0) {
                    sscanf(line, "core id : %d", &curCore);
                } else if (line[0] == '\n') { // blank line indicates end of one processor block
                    if (curPhysicalCore != -1 && curCore != -1) {
                        bool exists = false;
                        for (uint32 i = 0; i < count; i++) {
                            if (cores[i].physical_id == curPhysicalCore && cores[i].core_id == curCore) {
                                exists = true;
                                break;
                            }
                        }
                        if (!exists) {
                            cores[count].physical_id = curPhysicalCore;
                            cores[count].core_id = curCore;
                            count++;
                        }
                    }
                    curPhysicalCore = -1;
                    curCore = -1;
                }                
            }

            fclose(fp);

            sysInfo->coreCount = count;
            Str::Copy(sysInfo->cpuName, sizeof(sysInfo->cpuName), name);
            Str::Copy(sysInfo->cpuModel, sizeof(sysInfo->cpuModel), model);
        }

        #if CPU_ARM && ARCH_64BIT
            sysInfo->cpuFamily = SysInfo::CpuFamily::ARM64;
        #elif CPU_X86 && ARCH_64BIT
            sysInfo->cpuFamily = SysInfo::CpuFamily::x86_64;
        #elif CPU_ARM && ARCH_32BIT
            sysInfo->cpuFamily = SysInfo::CpuFamily::ARM;
        #endif
    }

    {
        FILE *fp = fopen("/proc/meminfo", "r");
        if (fp != nullptr) {
            char line[256];
            while (fgets(line, sizeof(line), fp)) {
                if (strncmp(line, "MemTotal:", 9) == 0) {
                    uint64 memTotal;
                    sscanf(line, "MemTotal: %lu kB", &memTotal);
                    sysInfo->physicalMemorySize = memTotal*SIZE_KB;
                    break;
                }
            }
        
            fclose(fp);
        }
    }
}

#endif // PLATFORM_LINUX

    #else
        #error "Not implemented"
    #endif
#endif

#if defined(__SSE2__)
#include <emmintrin.h>    // _mm_pause
#endif

#if CPU_ARM
#include <arm_acle.h>     // __yield
#endif 

#if PLATFORM_WINDOWS
    #if ARCH_32BIT && CPU_X86
        #if !COMPILER_MSVC
            #include <x86intrin.h>
        #endif
    #endif
    #include <intrin.h>
    #if COMPILER_MSVC
        #pragma intrinsic(_mm_pause)
        #pragma intrinsic(__rdtsc)
    #endif
#elif PLATFORM_APPLE
    #include <mach/mach_time.h>
#endif

#if !PLATFORM_WINDOWS
    #include <sys/time.h>
#endif

struct SysCounters
{
    AtomicUint32 numThreads;
    AtomicUint32 numMutexes;
    AtomicUint32 numSemaphores;
    AtomicUint32 numSignals;
    AtomicUint64 threadStackSize;
};

static SysCounters gSysCounters;

struct TimerInitializer
{
    TimerInitializer()
    {
        Timer::Initialize();
    }
};

static TimerInitializer gTimerInit;

char* PathUtils::ToUnix(const char *path, char *dst, size_t dstSize)
{
    size_t len = Str::Len(path);
    len = Min<size_t>(len, dstSize - 1);

    for (int i = 0; i < len; i++) {
        if (path[i] != '\\')
            dst[i] = path[i];
        else
            dst[i] = '/';
    }
    dst[len] = '\0';
    return dst;
}

char* PathUtils::ToWin(const char *path, char *dst, size_t dstSize)
{
    size_t len = Str::Len(path);
    len = Min<size_t>(len, dstSize - 1);

    for (int i = 0; i < len; i++) {
        if (path[i] != '/')
            dst[i] = path[i];
        else
            dst[i] = '\\';
    }
    dst[len] = '\0';
    return dst;
}

char* PathUtils::GetFileExtension(const char *path, char *dst, size_t dstSize)
{
    ASSERT(dstSize > 0);

    int len = Str::Len(path);
    if (len > 0) {
        const char *start = strrchr(path, '/');
        #if PLATFORM_WINDOWS
        if (!start)
            start = strrchr(path, '\\');
        #endif
        if (!start)
            start = path;
        const char *end = &path[len - 1];
        for (const char *e = start; e < end; ++e) {
            if (*e != '.')
                continue;
            Str::Copy(dst, (uint32)dstSize, e);
            return dst;
        }
    }

    dst[0] = '\0'; // no extension
    return dst;
}

char* PathUtils::GetFilenameAndExtension(const char *path, char *dst, size_t dstSize)
{
    const char *r = strrchr(path, '/');
    #if PLATFORM_WINDOWS
    if (!r)
        r = strrchr(path, '\\');
    #endif
    if (r) {
        Str::Copy(dst, (uint32)dstSize, r + 1);
    }
    else if (dst != path) {
        Str::Copy(dst, (uint32)dstSize, path);
    }
    return dst;
}

char* PathUtils::GetFilename(const char* path, char* dst, size_t dstSize)
{
    const char *r = strrchr(path, '/');
    #if PLATFORM_WINDOWS
    if (!r)
        r = strrchr(path, '\\');
    #endif
    if (r) {
        Str::Copy(dst, (uint32)dstSize, r + 1);
    }
    else if (dst != path) {
        Str::Copy(dst, (uint32)dstSize, path);
    }

    char* dot = strrchr(dst, '.');
    if (dot) 
        *dot = '\0';

    return dst;
}

char* PathUtils::GetDirectory(const char *path, char *dst, size_t dstSize)
{
    const char *r = strrchr(path, '/');
    #if PLATFORM_WINDOWS
    if (!r)
        r = strrchr(path, '\\');
    #endif
    if (r) {
        int o = (int)(intptr_t)(r - path);
        if (dst == path) {
            dst[o] = '\0';
        }
        else {
            Str::CopyCount(dst, (uint32)dstSize, path, o);
        }

        #if PLATFORM_WINDOWS
        #endif
    }
    else if (dst != path) {
        *dst = '\0';
    }
    return dst;
}

namespace PathUtils
{
    static char* Join(char *dst, size_t dstSize, const char *sep, const char *pathA, const char *pathB)
    {
        ASSERT(dst != pathB);
        int len = Str::Len(pathA);
        if (dst != pathA) {
            if (len > 0 && pathA[len - 1] == sep[0]) {
                Str::Copy(dst, (uint32)dstSize, pathA);
            }
            else if (len > 0) {
                Str::Copy(dst, (uint32)dstSize, pathA);
                Str::Concat(dst, (uint32)dstSize, sep);
            }
            else {
                dst[0] = '\0';
            }
        }
        else if (len > 0 && pathA[len - 1] != sep[0]) {
            Str::Concat(dst, (uint32)dstSize, sep);
        }

        if (pathB[0] == sep[0])
            ++pathB;
        Str::Concat(dst, (uint32)dstSize, pathB);
        return dst;
    }
}

char* PathUtils::Join(char *dst, size_t dstSize, const char *pathA, const char *pathB)
{
    #if PLATFORM_WINDOWS
    const char *kSep = "\\";
    #else
    const char *kSep = "/";
    #endif

    return PathUtils::Join(dst, dstSize, kSep, pathA, pathB);
}

char* PathUtils::JoinUnixStyle(char *dst, size_t dstSize, const char *pathA, const char *pathB)
{
    return PathUtils::Join(dst, dstSize, "/", pathA, pathB);
}

uint64 Timer::LapTime(uint64* lastTime)
{
    ASSERT(lastTime);
    uint64 dt = 0;
    uint64 now = Timer::GetTicks();
    if (*lastTime != 0) 
        dt = Timer::Diff(now, *lastTime);
    *lastTime = now;
    return dt;
}

void OS::GenerateCmdLineFromArgcArgv(int argc, const char* argv[], char** outString, uint32* outStringLen, 
                                    MemAllocator* alloc, const char* prefixCmd)
{
    ASSERT(outString);
    ASSERT(outStringLen);

    Blob blob(alloc);
    blob.SetGrowPolicy(Blob::GrowPolicy::Linear, 256);

    if (prefixCmd) {
        blob.Write(prefixCmd, Str::Len(prefixCmd));
        blob.Write<char>(32);
    }

    for (int i = 0; i < argc; i++) {
        blob.Write(argv[i], Str::Len(argv[i]));
        if (i != argc - 1)
            blob.Write<char>(32);
    }
    blob.Write<char>(0);

    size_t len;
    blob.Detach((void**)outString, &len);
    *outStringLen = static_cast<uint32>(len);
}

void OS::PauseCPU()
{
#if CPU_X86
    _mm_pause();
#elif CPU_ARM 
    __yield();
#else
    #error "Not implemented"
#endif
}

uint64 OS::GetCPUClock()
{
#if PLATFORM_APPLE  // TODO: maybe we can get rid of this and use the asm one
    return mach_absolute_time();
#elif PLATFORM_WINDOWS && CPU_X86
    return __rdtsc();
#elif CPU_ARM && ARCH_64BIT
    uint64 vtm;
    asm volatile("mrs %0, cntvct_el0" : "=r"(vtm));
    return vtm;
#elif CPU_X86 && ARCH_64BIT
    uint64 low, high;
    __asm__ volatile("rdtsc" : "=a"(low), "=d"(high));
    return (high << 32) | low;
#else
    #error "Not implemented for this platform"
#endif
}

bool SocketTCP::ParseUrl(const char* url, char* address, size_t addressSize, char* port, size_t portSize, const char** pResource)
{
    uint32 urlLen = Str::Len(url);
    
    if (const char* addressBegin = Str::FindStr(url, "://"); addressBegin)
        url = addressBegin + 2;
    
    char const* addressEnd = Str::FindChar(url, ':');
    if (!addressEnd) addressEnd = Str::FindChar(url, '/');
    if (!addressEnd) addressEnd = url + urlLen;
        
    uint32 addressLen = PtrToInt<uint32>((void*)(addressEnd - url));
    if(addressLen >= addressSize) 
        return false;
    memcpy(address, url, addressLen);
    address[addressLen] = '\0';
        
    char const* portEnd = addressEnd;
    if (*addressEnd == ':') {
        ++addressEnd;
        portEnd = Str::FindChar(addressEnd, '/');
        if (!portEnd) 
            portEnd = addressEnd + Str::Len(addressEnd);
        uint32 portLen = PtrToInt<uint32>((void*)(portEnd - addressEnd));
        if (portLen >= portSize) 
            return false;
        memcpy(port, addressEnd, portLen);
        port[portLen] = '\0';
    }
    else {
        return false;
    }    
    
    if (pResource)
        *pResource = portEnd;    
    return true;    
}

void _private::CountersAddThread(size_t stackSize)
{
    Atomic::FetchAddExplicit(&gSysCounters.numThreads, 1, AtomicMemoryOrder::Relaxed);
    Atomic::FetchAddExplicit(&gSysCounters.threadStackSize, stackSize, AtomicMemoryOrder::Relaxed);
}

void _private::CountersRemoveThread(size_t stackSize)
{
    Atomic::FetchSubExplicit(&gSysCounters.numThreads, 1, AtomicMemoryOrder::Relaxed);
    Atomic::FetchSubExplicit(&gSysCounters.threadStackSize, stackSize, AtomicMemoryOrder::Relaxed);
}

void _private::CountersAddMutex()
{
    Atomic::FetchAddExplicit(&gSysCounters.numMutexes, 1, AtomicMemoryOrder::Relaxed);
}

void _private::CountersRemoveMutex()
{
    Atomic::FetchSubExplicit(&gSysCounters.numMutexes, 1, AtomicMemoryOrder::Relaxed);
}

void _private::CountersAddSignal()
{
    Atomic::FetchAddExplicit(&gSysCounters.numSignals, 1, AtomicMemoryOrder::Relaxed);
}

void _private::CountersRemoveSignal()
{
    Atomic::FetchSubExplicit(&gSysCounters.numSignals, 1, AtomicMemoryOrder::Relaxed);
}

void _private::CountersAddSemaphore()
{
    Atomic::FetchAddExplicit(&gSysCounters.numSemaphores, 1, AtomicMemoryOrder::Relaxed);
}

void _private::CountersRemoveSemaphore()
{
    Atomic::FetchSubExplicit(&gSysCounters.numSemaphores, 1, AtomicMemoryOrder::Relaxed);
}

SysPrimitiveStats GetSystemPrimitiveStats()
{
    return SysPrimitiveStats {
        .numMutexes = gSysCounters.numMutexes,
        .numSignals = gSysCounters.numSignals,
        .numSemaphores = gSysCounters.numSemaphores,
        .numThreads = gSysCounters.numThreads,
        .threadStackSize = gSysCounters.threadStackSize
    };
}


void SpinLockMutex::Enter()
{
    while (Atomic::ExchangeExplicit(&mLocked, 1, AtomicMemoryOrder::Acquire) == 1) {
        uint32 spinCount = 1;
        do {
            if (spinCount++ & 1023)
                OS::PauseCPU();
            else
                Thread::SwitchContext();
        } while (Atomic::LoadExplicit(&mLocked, AtomicMemoryOrder::Relaxed));
    }
}

void SpinLockMutex::Exit()
{
    Atomic::StoreExplicit(&mLocked, 0, AtomicMemoryOrder::Release);
}

bool SpinLockMutex::TryEnter()
{
    return Atomic::LoadExplicit(&mLocked, AtomicMemoryOrder::Relaxed) == 0 &&
           Atomic::ExchangeExplicit(&mLocked, 1, AtomicMemoryOrder::Acquire) == 0;
}




#ifdef TRACY_ENABLE

#define TRACY_DBGHELP_LOCK DebugDbgHelp
PRAGMA_DIAGNOSTIC_PUSH()
PRAGMA_DIAGNOSTIC_IGNORED_MSVC(4530)   // C4530: C++ exception handler used, but unwind semantics are not enabled. Specify /EHsc
PRAGMA_DIAGNOSTIC_IGNORED_CLANG_GCC("-Wsometimes-uninitialized")
PRAGMA_DIAGNOSTIC_IGNORED_CLANG_GCC("-Wunused-variable")

#if PLATFORM_WINDOWS
    #define fileno _fileno
#endif

#pragma push_macro("PLATFORM_WINDOWS")
#pragma push_macro("PLATFORM_POSIX")
#undef PLATFORM_POSIX
#undef PLATFORM_WINDOWS


#include "External/tracy/TracyClient.cpp"
PRAGMA_DIAGNOSTIC_POP()

#pragma pop_macro("PLATFORM_WINDOWS")
#pragma pop_macro("PLATFORM_POSIX")

static TracyZoneEnterCallback gZoneEnterCallback;
static TracyZoneExitCallback gZoneExitCallback;

void Tracy::SetZoneCallbacks(TracyZoneEnterCallback zoneEnterCallback, TracyZoneExitCallback zoneExitCallback)
{
    gZoneEnterCallback = zoneEnterCallback;
    gZoneExitCallback = zoneExitCallback;
}

bool Tracy::RunZoneExitCallback(TracyCZoneCtx* ctx)
{
    if (gZoneExitCallback)
        return gZoneExitCallback(ctx);
    else
        return false;
}

void Tracy::RunZoneEnterCallback(TracyCZoneCtx* ctx, const ___tracy_source_location_data* sourceLoc)
{
    if (gZoneEnterCallback)
        gZoneEnterCallback(ctx, sourceLoc);
}


int64 Tracy::GetTime()
{
    return tracy::Profiler::GetTime();
}

Tracy::CpuProfilerScope::CpuProfilerScope(const ___tracy_source_location_data* sourceLoc, int callstackDepth, bool isActive, bool isAlloc)
{ 
    mCtx = {};

    if (callstackDepth > 0) {
        if (isAlloc) {
            mCtx = ___tracy_emit_zone_begin_alloc_callstack(
                ___tracy_alloc_srcloc_name(sourceLoc->line, sourceLoc->file, Str::Len(sourceLoc->file), 
                                           sourceLoc->function, Str::Len(sourceLoc->function), sourceLoc->name, Str::Len(sourceLoc->name),
                                           sourceLoc->color), callstackDepth, isActive);
        }
        else {
            mCtx = ___tracy_emit_zone_begin_callstack(sourceLoc, callstackDepth, isActive);
        }
    }
    else {
        if (isAlloc) {
            mCtx = ___tracy_emit_zone_begin_alloc(
                ___tracy_alloc_srcloc_name(sourceLoc->line, sourceLoc->file, Str::Len(sourceLoc->file), 
                                           sourceLoc->function, Str::Len(sourceLoc->function), sourceLoc->name, Str::Len(sourceLoc->name),
                                           sourceLoc->color), isActive);
        }
        else {
            mCtx = ___tracy_emit_zone_begin(sourceLoc, isActive);
        }
    }

    Tracy::RunZoneEnterCallback(&mCtx, sourceLoc); 
}

Tracy::CpuProfilerScope::~CpuProfilerScope() 
{ 
    if (!Tracy::RunZoneExitCallback(&mCtx)) 
        ___tracy_emit_zone_end(mCtx); 
}


#endif  // TRACY_ENABLE

