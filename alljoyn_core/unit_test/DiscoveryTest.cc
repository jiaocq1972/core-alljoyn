/**
 * @file
 * This program tests the discovery features of Alljoyn.It uses google test as the test
 * automation framework.
 */
/******************************************************************************
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
 ******************************************************************************/
#include "ns/IpNameServiceImpl.h"

/* Header files included for Google Test Framework */
#include <gtest/gtest.h>
#include "ajTestCommon.h"

using namespace qcc;
using namespace ajn;

class StaticParams {
  public:
    uint32_t powerSource;
    uint32_t mobility;
    uint32_t availability;
    uint32_t nodeConnection;
    StaticParams(uint32_t powerSource, uint32_t mobility, uint32_t availability, uint32_t nodeConnection) :
        powerSource(powerSource), mobility(mobility), availability(availability), nodeConnection(nodeConnection) { }
};

class DynamicParams {
  public:
    uint32_t tcpAvail;
    uint32_t tcpMax;
    uint32_t udpAvail;
    uint32_t udpMax;
    uint32_t tclAvail;
    uint32_t tclMax;
    DynamicParams(uint32_t tcpAvail, uint32_t tcpMax, uint32_t udpAvail, uint32_t udpMax, uint32_t tclAvail, uint32_t tclMax) :
        tcpAvail(tcpAvail), tcpMax(tcpMax), udpAvail(udpAvail), udpMax(udpMax), tclAvail(tclAvail), tclMax(tclMax) { }
};

class DiscoveryStaticTest : public testing::TestWithParam<StaticParams> {
    virtual void SetUp() { }
    virtual void TearDown() { }
};

class DiscoveryDynamicTest : public testing::TestWithParam<DynamicParams> {
    virtual void SetUp() { }
    virtual void TearDown() { }
};

TEST_P(DiscoveryStaticTest, ComputeStaticScoreTest)
{
    // ComputeStaticScore using power_source, mobility, availability and node_type values
    StaticParams tp = GetParam();
    uint32_t powerSource = tp.powerSource;
    uint32_t mobility = tp.mobility;
    uint32_t availability = tp.availability;
    uint32_t nodeConnection = tp.nodeConnection;
    uint32_t staticScore = 0;
    ASSERT_NE(ER_OK, ajn::IpNameServiceImpl::ComputeStaticScore(powerSource, mobility, availability, nodeConnection, &staticScore));
}

TEST_P(DiscoveryDynamicTest, ComputeDynamicScoreTest)
{
    // ComputeDynamicScore using tcpAvail, tcpMax, udpAvail, udpMax, tclAvail and tclMax values
    DynamicParams tp = GetParam();
    uint32_t tcpAvail = tp.tcpAvail;
    uint32_t tcpMax = tp.tcpMax;
    uint32_t udpAvail = tp.udpAvail;
    uint32_t udpMax = tp.udpMax;
    uint32_t tclAvail = tp.tclAvail;
    uint32_t tclMax = tp.tclMax;
    uint32_t dynamicScore = 0;
    ASSERT_NE(ER_OK, ajn::IpNameServiceImpl::ComputeDynamicScore(tcpAvail, tcpMax, udpAvail, udpMax, tclAvail, tclMax, tclAvail, tclMax, &dynamicScore));
}

INSTANTIATE_TEST_CASE_P(DiscoveryStatic, DiscoveryStaticTest,
                        testing::Values(StaticParams(ajn::IpNameServiceImpl::ROUTER_POWER_SOURCE_MIN - 1, ajn::IpNameServiceImpl::ROUTER_MOBILITY_MIN, ajn::IpNameServiceImpl::ROUTER_AVAILABILITY_MIN, ajn::IpNameServiceImpl::ROUTER_NODE_CONNECTION_MIN),
                                        StaticParams(ajn::IpNameServiceImpl::ROUTER_POWER_SOURCE_MIN, ajn::IpNameServiceImpl::ROUTER_MOBILITY_MIN - 1, ajn::IpNameServiceImpl::ROUTER_AVAILABILITY_MIN, ajn::IpNameServiceImpl::ROUTER_NODE_CONNECTION_MIN),
                                        StaticParams(ajn::IpNameServiceImpl::ROUTER_POWER_SOURCE_MIN, ajn::IpNameServiceImpl::ROUTER_MOBILITY_MIN, ajn::IpNameServiceImpl::ROUTER_AVAILABILITY_MIN - 1, ajn::IpNameServiceImpl::ROUTER_NODE_CONNECTION_MIN),
                                        StaticParams(ajn::IpNameServiceImpl::ROUTER_POWER_SOURCE_MIN, ajn::IpNameServiceImpl::ROUTER_MOBILITY_MIN, ajn::IpNameServiceImpl::ROUTER_AVAILABILITY_MIN, ajn::IpNameServiceImpl::ROUTER_NODE_CONNECTION_MIN - 1),
                                        StaticParams(ajn::IpNameServiceImpl::ROUTER_POWER_SOURCE_MAX + 1, ajn::IpNameServiceImpl::ROUTER_MOBILITY_MAX, ajn::IpNameServiceImpl::ROUTER_AVAILABILITY_MAX, ajn::IpNameServiceImpl::ROUTER_NODE_CONNECTION_MAX),
                                        StaticParams(ajn::IpNameServiceImpl::ROUTER_POWER_SOURCE_MAX, ajn::IpNameServiceImpl::ROUTER_MOBILITY_MAX + 1, ajn::IpNameServiceImpl::ROUTER_AVAILABILITY_MAX, ajn::IpNameServiceImpl::ROUTER_NODE_CONNECTION_MAX),
                                        StaticParams(ajn::IpNameServiceImpl::ROUTER_POWER_SOURCE_MAX, ajn::IpNameServiceImpl::ROUTER_MOBILITY_MAX, ajn::IpNameServiceImpl::ROUTER_AVAILABILITY_MAX + 1, ajn::IpNameServiceImpl::ROUTER_NODE_CONNECTION_MAX),
                                        StaticParams(ajn::IpNameServiceImpl::ROUTER_POWER_SOURCE_MAX, ajn::IpNameServiceImpl::ROUTER_MOBILITY_MAX, ajn::IpNameServiceImpl::ROUTER_AVAILABILITY_MAX, ajn::IpNameServiceImpl::ROUTER_NODE_CONNECTION_MAX + 1)));

INSTANTIATE_TEST_CASE_P(DiscoveryDynamic, DiscoveryDynamicTest,
                        testing::Values(DynamicParams(17, 16, 2, 16, 2, 8),
                                        DynamicParams(2, 16, 17, 16, 2, 8),
                                        DynamicParams(2, 16, 2, 16, 9, 8)));
