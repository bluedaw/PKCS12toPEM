// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
#define VC_EXTRALEAN             // Exclude rarely-used stuff from Windows headers

#include <windows.h>

#include <openssl/pem.h>
#include <openssl/err.h>
#include <openssl/pkcs12.h>
#include <openssl/x509.h>
#include <openssl/pkcs7.h>
#include <openssl/asn1_mac.h>
#pragma comment(lib,"libeay32")
//#pragma comment(lib,"ssleay32")

#include <string>
using namespace std;
