#ifndef CC_HTTP_H
#define CC_HTTP_H
#include "Constants.h"
#include "Utils.h"
/* Aysnchronously performs http GET, HEAD, and POST requests.
   Typically this is used to download skins, texture packs, etc.
   Copyright 2014-2019 ClassiCube | Licensed under BSD-3
*/
struct IGameComponent;
struct ScheduledTask;
#define URL_MAX_SIZE (STRING_SIZE * 2)

extern struct IGameComponent Http_Component;

enum HttpRequestType { REQUEST_TYPE_GET, REQUEST_TYPE_HEAD, REQUEST_TYPE_POST };
enum HttpProgress {
	ASYNC_PROGRESS_NOTHING        = -3,
	ASYNC_PROGRESS_MAKING_REQUEST = -2,
	ASYNC_PROGRESS_FETCHING_DATA  = -1
};

struct HttpRequest {
	char URL[URL_MAX_SIZE]; /* URL data is downloaded from/uploaded to. */
	char ID[URL_MAX_SIZE];  /* Unique identifier for this request. */
	TimeMS TimeAdded;       /* Time this request was added to queue of requests. */
	TimeMS TimeDownloaded;  /* Time response contents were completely downloaded. */
	int StatusCode;         /* HTTP status code returned in the response. */
	uint32_t ContentLength; /* HTTP content length returned in the response. */

	ReturnCode Result; /* 0 on success, otherwise platform-specific error. */
	uint8_t*   Data;   /* Contents of the response. (i.e. result data) */
	uint32_t   Size;   /* Size of the contents. (may still be non-zero for non 200 status codes) */

	char LastModified[STRING_SIZE]; /* Time item cached at (if at all) */
	char Etag[STRING_SIZE];         /* ETag of cached item (if any) */
	uint8_t RequestType;            /* See the various REQUEST_TYPE_ */
	bool Success;                   /* Whether Result is 0, status is 200, and data is not NULL */
	struct EntryList* Cookies;      /* Cookie list sent in requests. May be modified by the response. */
};

/* Frees data from a HTTP request. */
void HttpRequest_Free(struct HttpRequest* request);

/* Aschronously performs a http GET request to download a skin. */
/* If url is a skin, downloads from there. (if not, http://static.classicube.net/skins/[skinName].png) */
/* ID of the request is set to skinName. */
void Http_AsyncGetSkin(const String* skinName);
/* Asynchronously performs a http GET request. (e.g. to download data) */
void Http_AsyncGetData(const String* url, bool priority, const String* id);
/* Asynchronously performs a http HEAD request. (e.g. to get Content-Length header) */
void Http_AsyncGetHeaders(const String* url, bool priority, const String* id);
/* Asynchronously performs a http POST request. (e.g. to submit data) */
/* NOTE: You don't have to persist data, a copy is made of it. */
void Http_AsyncPostData(const String* url, bool priority, const String* id, const void* data, uint32_t size, struct EntryList* cookies);
/* Asynchronously performs a http GET request. (e.g. to download data) */
/* Also sets the If-Modified-Since and If-None-Match headers. (if not NULL)  */
void Http_AsyncGetDataEx(const String* url, bool priority, const String* id, const String* lastModified, const String* etag, struct EntryList* cookies);

/* Encodes data using % or URL encoding. */
void Http_UrlEncode(String* dst, const uint8_t* data, int len);
/* Converts characters to UTF8, then calls Http_URlEncode on them. */
void Http_UrlEncodeUtf8(String* dst, const String* src);
/* Outputs more detailed information about errors with http requests. */
bool Http_DescribeError(ReturnCode res, String* dst);

/* Attempts to retrieve a fully completed request. */
/* NOTE: You MUST check Success for whether it completed successfully. */
/* (Data may still be non NULL even on error, e.g. on a http 404 error) */
bool Http_GetResult(const String* id, struct HttpRequest* item);
/* Retrieves information about the request currently being processed. */
bool Http_GetCurrent(struct HttpRequest* request, int* progress);
/* Clears the list of pending requests. */
void Http_ClearPending(void);
#endif
