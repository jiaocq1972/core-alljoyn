/**
 * @file
 */
/******************************************************************************
 *    Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
 *    Source Project (AJOSP) Contributors and others.
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
 ******************************************************************************/

#include <alljoyn_c/AboutIconObj.h>
#include <alljoyn/AboutIconObj.h>
#include <alljoyn/BusAttachment.h>
#include <qcc/Debug.h>

#define QCC_MODULE "ALLJOYN_C"

struct _alljoyn_abouticonobj_handle {
    /* Empty by design */
};

alljoyn_abouticonobj AJ_CALL alljoyn_abouticonobj_create(alljoyn_busattachment bus,
                                                         alljoyn_abouticon icon)
{
    QCC_DbgTrace(("%s", __FUNCTION__));
    return (alljoyn_abouticonobj) new ajn::AboutIconObj(*(ajn::BusAttachment*)bus, *(ajn::AboutIcon*)icon);
}

void AJ_CALL alljoyn_abouticonobj_destroy(alljoyn_abouticonobj icon)
{
    QCC_DbgTrace(("%s", __FUNCTION__));
    delete (ajn::AboutIconObj*)icon;
}