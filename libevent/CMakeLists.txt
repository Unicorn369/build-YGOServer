project (event)

#aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRC_LIBENENT)
add_library(event STATIC ${CMAKE_CURRENT_SOURCE_DIR})

target_sources(event PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/buffer.c
    ${CMAKE_CURRENT_SOURCE_DIR}/bufferevent.c
    ${CMAKE_CURRENT_SOURCE_DIR}/bufferevent_filter.c
    ${CMAKE_CURRENT_SOURCE_DIR}/bufferevent_pair.c
    ${CMAKE_CURRENT_SOURCE_DIR}/bufferevent_ratelim.c
    ${CMAKE_CURRENT_SOURCE_DIR}/bufferevent_sock.c
    ${CMAKE_CURRENT_SOURCE_DIR}/event.c
    ${CMAKE_CURRENT_SOURCE_DIR}/evmap.c
    ${CMAKE_CURRENT_SOURCE_DIR}/evthread.c
    ${CMAKE_CURRENT_SOURCE_DIR}/evutil.c
    ${CMAKE_CURRENT_SOURCE_DIR}/evutil_rand.c
    ${CMAKE_CURRENT_SOURCE_DIR}/evutil_time.c
    ${CMAKE_CURRENT_SOURCE_DIR}/listener.c
    ${CMAKE_CURRENT_SOURCE_DIR}/log.c
    ${CMAKE_CURRENT_SOURCE_DIR}/signal.c)

if(ANDROID)
    target_include_directories(event PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/android
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/compat)
    target_sources(event PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/evthread_pthread.c
        ${CMAKE_CURRENT_SOURCE_DIR}/epoll.c
        ${CMAKE_CURRENT_SOURCE_DIR}/poll.c
        ${CMAKE_CURRENT_SOURCE_DIR}/select.c
        ${CMAKE_CURRENT_SOURCE_DIR}/strlcpy.c)
elseif(APPLE)
    target_include_directories(event PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/macosx
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/compat)
    target_sources(event PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/evthread_pthread.c
        ${CMAKE_CURRENT_SOURCE_DIR}/poll.c
        ${CMAKE_CURRENT_SOURCE_DIR}/kqueue.c
        ${CMAKE_CURRENT_SOURCE_DIR}/select.c)
elseif(UNIX)
    target_include_directories(event PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/linux
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/compat)
    target_sources(event PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/evthread_pthread.c
        ${CMAKE_CURRENT_SOURCE_DIR}/epoll.c
        ${CMAKE_CURRENT_SOURCE_DIR}/poll.c
        ${CMAKE_CURRENT_SOURCE_DIR}/select.c
        ${CMAKE_CURRENT_SOURCE_DIR}/strlcpy.c)
elseif(WIN32)
    target_include_directories(event PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Win32
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/compat)
    target_sources(event PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/buffer_iocp.c
        ${CMAKE_CURRENT_SOURCE_DIR}/bufferevent_async.c
        ${CMAKE_CURRENT_SOURCE_DIR}/event_iocp.c
        ${CMAKE_CURRENT_SOURCE_DIR}/evthread_win32.c
        ${CMAKE_CURRENT_SOURCE_DIR}/strlcpy.c
        ${CMAKE_CURRENT_SOURCE_DIR}/win32select.c)
endif()
