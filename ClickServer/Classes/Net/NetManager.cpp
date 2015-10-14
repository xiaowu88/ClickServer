//
//  NetManager.cpp
//  ClickServer
//
//  Created by qianmengxi on 15-10-14.
//  Copyright (c) 2015年 qianmengxi. All rights reserved.
//

#include "NetManager.h"
#include <event2/event_struct.h>
#include <event2/event.h>
#include <event2/http.h>
#include <event2/buffer.h>

#define LISTEN_PORT 10000
#define LISTEN_IP "127.0.0.1"

static void dump_request_cb(struct evhttp_request *req, void *arg)
{
    const char *cmdtype;
    struct evkeyvalq *headers;
    struct evkeyvalq *params;
    struct evkeyval *header;
    struct evbuffer *buf;
    
    switch (evhttp_request_get_command(req)) {
        case EVHTTP_REQ_GET: cmdtype = "GET"; break;
        case EVHTTP_REQ_POST: cmdtype = "POST"; break;
        case EVHTTP_REQ_HEAD: cmdtype = "HEAD"; break;
        case EVHTTP_REQ_PUT: cmdtype = "PUT"; break;
        case EVHTTP_REQ_DELETE: cmdtype = "DELETE"; break;
        case EVHTTP_REQ_OPTIONS: cmdtype = "OPTIONS"; break;
        case EVHTTP_REQ_TRACE: cmdtype = "TRACE"; break;
        case EVHTTP_REQ_CONNECT: cmdtype = "CONNECT"; break;
        case EVHTTP_REQ_PATCH: cmdtype = "PATCH"; break;
        default: cmdtype = "unknown"; break;
    }
    
    printf("Received a %s request for %s\nHeaders:\n",
           cmdtype, evhttp_request_get_uri(req));
    
    headers = evhttp_request_get_input_headers(req);
    for (header = headers->tqh_first; header;
         header = header->next.tqe_next) {
        printf("  %s: %s\n", header->key, header->value);
    }
    
    //params = evhttp_request_get_input_headers(req);
    printf("params:\n");
    int result = evhttp_parse_query(evhttp_request_get_uri(req), headers);
    for (header = headers->tqh_first; header;
         header = header->next.tqe_next) {
        printf("  %s: %s\n", header->key, header->value);
    }
    
    buf = evhttp_request_get_input_buffer(req);
    puts("Input data: <<<");
    while (evbuffer_get_length(buf)) {
        int n;
        char cbuf[128];
        n = evbuffer_remove(buf, cbuf, sizeof(cbuf));
        if (n > 0)
            (void) fwrite(cbuf, 1, n, stdout);
    }
    puts(">>>");
    
    evhttp_send_reply(req, 200, "OK", NULL);
}

static void send_document_cb(struct evhttp_request *req, void *arg)
{
    const char* uri = evhttp_request_get_uri(req);
    printf("get uri:%s", uri);
}

static NetManager* s_netManagerIns = nullptr;
NetManager* NetManager::getInstance()
{
    if (!s_netManagerIns)
    {
        s_netManagerIns = new NetManager();
    }
    
    return s_netManagerIns;
}

bool NetManager::start()
{
    struct event_base *base;
    struct evhttp *http;
    struct evhttp_bound_socket *handle;
    
    base = event_base_new();
    if (!base)
    {
        fprintf(stderr, "Couldn't create an event_base: exiting\n");
        return false;
    }
    
    http = evhttp_new(base);
    if (!http)
    {
        fprintf(stderr, "couldn't create evhttp. Exiting.\n");
        return false;
    }
    
    evhttp_set_cb(http, "/dump", dump_request_cb, NULL);
    evhttp_set_gencb(http, send_document_cb, NULL);
    
    handle = evhttp_bind_socket_with_handle(http, LISTEN_IP, LISTEN_PORT);
    if (!handle)
    {
        fprintf(stderr, "couldn't bind to port %d. Exiting.\n", LISTEN_PORT);
        return false;
    }
    
    event_base_dispatch(base);
    
    return true;
}