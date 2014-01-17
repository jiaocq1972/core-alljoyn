/**
 * @file
 *
 * StreamPump moves data bidirectionally between two Streams.
 */

/******************************************************************************
 *
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
 *     THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 *     WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 *     WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 *     AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 *     DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 *     PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 *     TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 *     PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

#ifndef _QCC_STREAMPUMP_H
#define _QCC_STREAMPUMP_H

#include <qcc/platform.h>
#include <qcc/Stream.h>
#include <qcc/Thread.h>
#include <Status.h>

namespace qcc {

class StreamPump : public qcc::Thread {
  public:

    /** Construct a bi-directional stream pump */
    StreamPump(Stream* streamA, Stream* streamB, size_t chunkSize, const char* name = "pump", bool isManaged = false);

    /** Destructor */
    virtual ~StreamPump()
    {
        delete streamA;
        delete streamB;
    }

    /**
     * Start the data pump.
     *
     * @return ER_OK if successful.
     */
    QStatus Start();

  protected:

    /**
     *  Worker thread used to move data from streamA to streamB
     *
     * @param arg  unused.
     */
    ThreadReturn STDCALL Run(void* arg);

  private:

    StreamPump(const StreamPump& other) : chunkSize(0), isManaged(false) { }
    StreamPump& operator=(const StreamPump& other) { return *this; }

    Stream* streamA;
    Stream* streamB;
    const size_t chunkSize;
    const bool isManaged;
};

}  /* namespace */

#endif