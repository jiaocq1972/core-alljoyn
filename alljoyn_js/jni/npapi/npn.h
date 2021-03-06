/*
 *    Copyright (c) Open Connectivity Foundation (OCF), AllJoyn Open Source
 *    Project (AJOSP) Contributors and others.
 *
 *    SPDX-License-Identifier: Apache-2.0
 *
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Copyright (c) Open Connectivity Foundation and Contributors to AllSeen
 *    Alliance. All rights reserved.
 *
 *    Permission to use, copy, modify, and/or distribute this software for
 *    any purpose with or without fee is hereby granted, provided that the
 *    above copyright notice and this permission notice appear in all
 *    copies.
 *
 *    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 *    WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 *    WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 *    AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 *    DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 *    PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 *    TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 *    PERFORMANCE OF THIS SOFTWARE.
 */
#ifndef _NPN_H
#define _NPN_H

#include <qcc/Thread.h>
#if defined(QCC_OS_LINUX)
#include <prtypes.h>
#endif
#include <npapi.h>
#include <npfunctions.h>
#include <npruntime.h>

#undef STRINGZ_TO_NPVARIANT
#define STRINGZ_TO_NPVARIANT(_val, _v)                  \
    NP_BEGIN_MACRO                                      \
        (_v).type = NPVariantType_String;               \
    NPString str = { _val, (uint32_t)strlen(_val) };    \
    (_v).value.stringValue = str;                       \
    NP_END_MACRO

#ifndef NPVARIANT_VOID
#define NPVARIANT_VOID { NPVariantType_Void, { 0 } }
#endif

extern qcc::Thread* gPluginThread;
#if defined(QCC_OS_GROUP_WINDOWS)
extern HINSTANCE gHinstance;
#endif

void NPN_RetainVariantValue(const NPVariant*variant, NPVariant* retained);
void NPN_PluginThreadAsyncCall(NPP instance, void (*func)(void*), void* userData);

#endif // _NPN_H
