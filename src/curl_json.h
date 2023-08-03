// Copyright (c) 2009-2014 The Bitcoin developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef PRCYCOIN_CURLJSON_H
#define PRCYCOIN_CURLJSON_H

#include "fs.h"

#include <curl/curl.h>

#include <archive.h>
#include <archive_entry.h>

#include <string>

#define TIME_IN_US 1
#define TIMETYPE curl_off_t
#define TIMEOPT CURLINFO_TOTAL_TIME_T
#define MINIMAL_PROGRESS_FUNCTIONALITY_INTERVAL     3000000

struct CurlProgress {
  TIMETYPE lastruntime; /* type depends on version, see above */
  CURL *curl;
};

enum JsonDownloadHeaders {
    STANDARD_HEADERS,
    CG_HEADERS,
    GITHUB_HEADERS
};

struct ParamFile {
    std::string name;
    std::string URL;
    std::string hash;
    bool verified;
    bool complete = false;
    fs::path path;
    FILE *file;
    int64_t dlnow;
    int64_t dltotal;
    int64_t dlretrytotal = 0;
    CURL *curl;
    CurlProgress prog;
};

struct JsonDownload {
    std::string URL = "";
    std::string response = "";
    bool failed = false;
    bool complete = false;
    CURL *curl;
    CurlProgress prog;
};

extern std::map<std::string, ParamFile> mapParams;

extern bool checkParams();
extern void initalizeMapParamBootstrap();
extern void initalizeMapParam();
static size_t writer(char *in, size_t size, size_t nmemb, std::string *out);
static size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream);
extern bool downloadFiles(std::string title);
extern void getHttpsJson(std::string url, JsonDownload* reply, int headerType);
extern bool getBootstrap();
static bool extract(fs::path filename);
static int copy_data(struct archive *ar, struct archive *aw);

static int verbose = 0;

#endif
