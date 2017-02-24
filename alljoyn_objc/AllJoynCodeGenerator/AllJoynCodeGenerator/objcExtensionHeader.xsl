<!--
////////////////////////////////////////////////////////////////////////////////
//    Copyright (c) Open Connectivity Foundation (OCF), AllJoyn Open Source
//    Project (AJOSP) Contributors and others.
//    
//    SPDX-License-Identifier: Apache-2.0
//    
//    All rights reserved. This program and the accompanying materials are
//    made available under the terms of the Apache License, Version 2.0
//    which accompanies this distribution, and is available at
//    http://www.apache.org/licenses/LICENSE-2.0
//    
//    Copyright (c) Open Connectivity Foundation and Contributors to AllSeen
//    Alliance. All rights reserved.
//    
//    Permission to use, copy, modify, and/or distribute this software for
//    any purpose with or without fee is hereby granted, provided that the
//    above copyright notice and this permission notice appear in all
//    copies.
//    
//    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
//    WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
//    WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
//    AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
//    DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
//    PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
//    TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
//    PERFORMANCE OF THIS SOFTWARE.
////////////////////////////////////////////////////////////////////////////////
-->
<xsl:stylesheet version="1.0"
                xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:param name="fileName"/>
<xsl:param name="baseFileName"/>

<xsl:output method="text" version="1.0" encoding="UTF-8" indent="no" omit-xml-declaration="yes"/>

<xsl:variable name="vLower" select="'abcdefghijklmnopqrstuvwxyz'"/>
<xsl:variable name="vUpper" select="'ABCDEFGHIJKLMNOPQRSTUVWXYZ'"/>

<xsl:template match="/">////////////////////////////////////////////////////////////////////////////////
//    Copyright (c) Open Connectivity Foundation (OCF), AllJoyn Open Source
//    Project (AJOSP) Contributors and others.
//    
//    SPDX-License-Identifier: Apache-2.0
//    
//    All rights reserved. This program and the accompanying materials are
//    made available under the terms of the Apache License, Version 2.0
//    which accompanies this distribution, and is available at
//    http://www.apache.org/licenses/LICENSE-2.0
//    
//    Copyright (c) Open Connectivity Foundation and Contributors to AllSeen
//    Alliance. All rights reserved.
//    
//    Permission to use, copy, modify, and/or distribute this software for
//    any purpose with or without fee is hereby granted, provided that the
//    above copyright notice and this permission notice appear in all
//    copies.
//    
//    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
//    WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
//    WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
//    AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
//    DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
//    PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
//    TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
//    PERFORMANCE OF THIS SOFTWARE.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
//  ALLJOYN MODELING TOOL - GENERATED CODE
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
//  <xsl:value-of select="$baseFileName"/>.h
//
////////////////////////////////////////////////////////////////////////////////

#import "AJN<xsl:value-of select="$baseFileName"/>.h"

<xsl:apply-templates match=".//node" mode="objc-category-declaration"/>

</xsl:template>

<xsl:template match="node" mode="objc-category-declaration">
////////////////////////////////////////////////////////////////////////////////
//
//  <xsl:value-of select="./annotation[@name='org.alljoyn.lang.objc']/@value"/>
//
////////////////////////////////////////////////////////////////////////////////

@interface <xsl:value-of select="./annotation[@name='org.alljoyn.lang.objc']/@value" /> : AJN<xsl:value-of select="./annotation[@name='org.alljoyn.lang.objc']/@value" />

@end

////////////////////////////////////////////////////////////////////////////////

</xsl:template>

<xsl:template match="interface" mode="objc-interface-list">
    <xsl:if test="position() > 1">, </xsl:if>
    <xsl:value-of select="./annotation[@name='org.alljoyn.lang.objc']/@value"/>
</xsl:template>

<xsl:template match="method" mode="objc-declaration">
    <xsl:text>- (</xsl:text>
    <xsl:choose>
        <xsl:when test="count(./arg[@direction='out']) > 1 or count(./arg[@direction='out']) = 0">
            <xsl:text>void</xsl:text>
        </xsl:when>
        <xsl:otherwise>
            <xsl:apply-templates select="./arg[@direction='out']" mode="objc-argType"/>
        </xsl:otherwise>
    </xsl:choose>
    <xsl:text>)</xsl:text>
    <xsl:choose>
        <xsl:when test="count(./arg) = 0 or (count(./arg) = 1 and count(./arg[@direction='out']) = 1)">
            <xsl:call-template name="uncapitalizeFirstLetterOfNameAttr"/>
            <xsl:text>:(AJNMessage *)message</xsl:text>
        </xsl:when>
        <xsl:when test="count(./arg[@direction='out']) > 1">
            <xsl:apply-templates select="./arg[@direction='in']" mode="objc-messageParam"/>
            <xsl:if test="count(./arg[@direction='in']) > 1">
                <xsl:text>&#32;</xsl:text>
            </xsl:if>
            <xsl:apply-templates select="./arg[@direction='out']" mode="objc-messageParam"/>
            <xsl:text> message:(AJNMessage *)message</xsl:text>
        </xsl:when>
        <xsl:otherwise>
            <xsl:apply-templates select="./arg[@direction='in']" mode="objc-messageParam"/>
            <xsl:text> message:(AJNMessage *)message</xsl:text>
        </xsl:otherwise>
    </xsl:choose>
    <xsl:text>;&#10;</xsl:text>
</xsl:template>

<xsl:template match="signal" mode="objc-declaration">
    <xsl:text>- (void)send</xsl:text>
    <xsl:value-of select="@name"/>
    <xsl:text>:</xsl:text>
    <xsl:if test="count(./arg) > 0">
        <xsl:apply-templates select="./arg" mode="objc-messageParam"/>
        <xsl:text> </xsl:text>
    </xsl:if>
    <xsl:text>inSession:(AJNSessionId)sessionId toDestination:(NSString *)destinationPath</xsl:text>
    <xsl:text>;&#10;</xsl:text>
</xsl:template>

<xsl:template match="property" mode="objc-declaration">
    <xsl:text>@property (nonatomic,</xsl:text>
    <xsl:choose>
        <xsl:when test="@access='readwrite'">
            <xsl:if test="@type!='b'">
                <xsl:text> strong</xsl:text>
            </xsl:if>
        </xsl:when>
        <xsl:when test="@access='read'">
            <xsl:text> readonly</xsl:text>
        </xsl:when>
    </xsl:choose>
    <xsl:text>) </xsl:text>
    <xsl:call-template name="objcArgType"/>
    <xsl:text> </xsl:text>
    <xsl:value-of select="@name"/>
    <xsl:text>;&#10;</xsl:text>
</xsl:template>

<xsl:template match="arg" mode="objc-messageParam">
    <xsl:if test="position() > 1">
        <xsl:text>&#32;</xsl:text>
    </xsl:if>
    <xsl:value-of select="./annotation[@name='org.alljoyn.lang.objc']/@value" />
    <xsl:text>(</xsl:text>
        <xsl:apply-templates select="." mode="objc-argType"/>
        <xsl:if test="@direction='out'">
            <xsl:text>*</xsl:text>
        </xsl:if>
    <xsl:text>)</xsl:text>
    <xsl:value-of select="@name"/>
</xsl:template>

<xsl:template match="arg" mode="objc-argType">
    <xsl:call-template name="objcArgType"/>
</xsl:template>

<xsl:template name="objcArgType">
    <xsl:choose>
        <xsl:when test="@type='y'">
            <xsl:text>NSNumber *</xsl:text>
        </xsl:when>
        <xsl:when test="@type='b'">
            <xsl:text>BOOL</xsl:text>
        </xsl:when>
        <xsl:when test="@type='n'">
            <xsl:text>NSNumber *</xsl:text>
        </xsl:when>
        <xsl:when test="@type='q'">
            <xsl:text>NSNumber *</xsl:text>
        </xsl:when>
        <xsl:when test="@type='i'">
            <xsl:text>NSNumber *</xsl:text>
        </xsl:when>
        <xsl:when test="@type='u'">
            <xsl:text>NSNumber *</xsl:text>
        </xsl:when>
        <xsl:when test="@type='x'">
            <xsl:text>NSNumber *</xsl:text>
        </xsl:when>
        <xsl:when test="@type='t'">
            <xsl:text>NSNumber *</xsl:text>
        </xsl:when>
        <xsl:when test="@type='d'">
            <xsl:text>NSNumber *</xsl:text>
        </xsl:when>
        <xsl:when test="@type='s'">
            <xsl:text>NSString *</xsl:text>
        </xsl:when>
        <xsl:when test="@type='o'">
            <xsl:text>NString *</xsl:text>
        </xsl:when>
        <xsl:when test="@type='a'">
            <xsl:text>NSArray *</xsl:text>
        </xsl:when>
        <xsl:otherwise>
            <xsl:text>AJNMessageArgument *</xsl:text>
        </xsl:otherwise>
    </xsl:choose>
</xsl:template>

<xsl:template name="capitalizeFirstLetterOfNameAttr">
   <xsl:variable name="value">
        <xsl:value-of select="@name"/>
   </xsl:variable>
    <xsl:variable name= "ufirstChar" select="translate(substring($value,1,1),$vLower,$vUpper)"/>
    <xsl:value-of select="concat($ufirstChar,substring($value,2))"/>
</xsl:template>

<xsl:template name="uncapitalizeFirstLetterOfNameAttr">
   <xsl:variable name="value">
        <xsl:value-of select="@name"/>
   </xsl:variable>
    <xsl:variable name= "lfirstChar" select="translate(substring($value,1,1),$vUpper,$vLower)"/>
    <xsl:value-of select="concat($lfirstChar,substring($value,2))"/>
</xsl:template>

</xsl:stylesheet>