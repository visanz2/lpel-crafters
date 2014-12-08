<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" 
xmlns:xs="http://www.w3.org/2001/XMLSchema" xmlns:fn="http://www.w3.org/2005/xpath-functions" exclude-result-prefixes="xs fn xsl">
	<!--output format close to xquery-->
	<xsl:output method="text" encoding="utf-8" omit-xml-declaration="no"/>

	<xsl:template name="genarateGlobalConent">
		<xsl:param name="isVM"/>
		<xsl:text># As minimum version 2.6 of CMake must be used.
cmake_minimum_required(VERSION 2.6)

#For verbose output during the build process, this is the same as `make VERBOSE=1'
set( CMAKE_VERBOSE_MAKEFILE on )

#The following variables have been moved over from the Makefile
# Where the different OpenComRTOS installation images are located
</xsl:text>
		<xsl:text>SET(OCR_INSTALL_DIR "</xsl:text><xsl:value-of select="//system/@rtosDir"/><xsl:text>")&#10;&#10;</xsl:text>
		<xsl:text># Name of the Platform (win32, posix32, leon3, microblaze)
SET(OCR_PLATFORM </xsl:text><xsl:value-of select="//system/node/@type"/>
		<xsl:text>)&#10;&#10;#The variant of OpenComRTOS to compile for (OLD: RTOSVARIANT)&#10;</xsl:text>
		<xsl:if test="$isVM!='true'">
			<xsl:text>SET(OCR_VARIANT </xsl:text>
			<xsl:choose>
	  			<xsl:when test="//system/netLink">
					<xsl:text>MP</xsl:text>
	  			</xsl:when>
		  		<xsl:otherwise>
	    				<xsl:text>SP</xsl:text>
				</xsl:otherwise>
			</xsl:choose>
			<xsl:text>)&#10;&#10;</xsl:text>
			<xsl:text># Setting predefined compiler options
SET(OCR_COMPILER_OPTIONS "</xsl:text>
			<xsl:value-of select="//system/node/compilerOptions/@value"/>
			<xsl:text>")

#OLD: DBGOPT, comment it out if not used.
# Not used here hence commented out.
SET(OCR_DEBUG_OPTIONS "</xsl:text>
			<xsl:if test="//system/node/debugopt/@value!=0">
				<xsl:value-of select="//system/node/debugopt/@value"/>
			</xsl:if>
			<xsl:text>")</xsl:text>
		</xsl:if>
		<xsl:if test="//system/node/target">
			<xsl:text>&#10;SET(TARGET </xsl:text><xsl:value-of select="//system/node/target/@value"/>
			<xsl:text>)</xsl:text>
		</xsl:if>
		<xsl:text>

#include custom CMake scripts directory
SET(CMAKE_MODULE_PATH ${OCR_INSTALL_DIR}/${OCR_PLATFORM}/CMakeScripts)
MESSAGE(STATUS ${CMAKE_MODULE_PATH})
# Include OpenComRTOS definitions, similar to the config.mk files, but  more powerful
INCLUDE(OpenComRTOS)&#10;&#10;</xsl:text>
		<xsl:call-template name="compiler_options"/>
		<xsl:text>PROJECT(</xsl:text><xsl:value-of select="//system/node/@name"/>
		<xsl:text> C CXX)&#10;&#10;</xsl:text>
		<xsl:text>enable_language(ASM)&#10;&#10;</xsl:text> 
		<xsl:text>#Configure the build system for OpenComRTOS.
OpenComRTOS_Application()

# Base directory for installing anything (headers, executable).
SET(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/.. )

SET(LINKER_LANGUAGE "C")
#Setting Project include directory as additional include directory.
INCLUDE_DIRECTORIES(${OCR_INSTALL_DIR}/${OCR_PLATFORM}/include)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../include)&#10;</xsl:text>
		<xsl:if test="$isVM!='true'">
			<xsl:text>INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/include)
INCLUDE_DIRECTORIES(${OCR_INSTALL_DIR}/${OCR_PLATFORM}/include/driver)
INCLUDE_DIRECTORIES(${OCR_INSTALL_DIR}/${OCR_PLATFORM}/include/GraphicalHostService)
INCLUDE_DIRECTORIES(${OCR_INSTALL_DIR}/${OCR_PLATFORM}/include/StdioHostService)
INCLUDE_DIRECTORIES(${OCR_INSTALL_DIR}/${OCR_PLATFORM}/include/kernel)
INCLUDE_DIRECTORIES(${OCR_INSTALL_DIR}/${OCR_PLATFORM}/include/sockf)&#10;</xsl:text>
			<xsl:call-template name="platform_includes"/>
		</xsl:if>

        <xsl:for-each select="//system/node/includePath/@path">
            <xsl:text>INCLUDE_DIRECTORIES(</xsl:text><xsl:value-of select="."/><xsl:text>)&#10;</xsl:text>
        </xsl:for-each>
        <xsl:text>&#10;&#10;</xsl:text>
        <xsl:text># Additional library paths</xsl:text>
        <xsl:text>&#10;</xsl:text>
        <xsl:for-each select="//system/node/libraryPath/@path">
            <xsl:text>LINK_DIRECTORIES(</xsl:text><xsl:value-of select="."/><xsl:text>)&#10;</xsl:text>
        </xsl:for-each>
        
		<xsl:call-template name="link_lib"/>

        <!-- Here the additional CFLAGS get added -->
        <xsl:text>&#10;</xsl:text>
        <xsl:text># User defined CFLAGS &#10;</xsl:text>
        <xsl:for-each select="//system/node/CFLAGS/CFLAG">
            <xsl:text>ADD_DEFINITIONS(</xsl:text><xsl:value-of select="."/><xsl:text>)&#10;</xsl:text>
        </xsl:for-each>
        
        <!-- <xsl:value-of select="//system/node/properties/property[@name='foo']/@value"/> -->
        <xsl:text>&#10;</xsl:text>


		<xsl:text>#Tell CMake to look in these directories for further CMakeLists.txt files
ADD_SUBDIRECTORY(src)</xsl:text>
	</xsl:template>
<!-- 
	<xsl:template name="include_information">
		<xsl:for-each select="//system/node/deviceDriver/linkPort/includeFile/@name[not(.=preceding::includeFile/@name)]">
			<xsl:text>INCLUDE_DIRECTORIES(</xsl:text><xsl:value-of select="."/><xsl:text>)&#10;</xsl:text>
		</xsl:for-each>
	</xsl:template>
	-->
<!--  BSP: To be purged.
	<xsl:template name="link_lib">
		<xsl:for-each select="//system/node/deviceDriver/lib/@name[not(.=preceding::lib/@name)]">
			<xsl:text>LINK_LIBRARIES(</xsl:text><xsl:value-of select="."/><xsl:text>)&#10;</xsl:text>
		</xsl:for-each>
		<xsl:for-each select="//system/node/deviceDriver/ocrLib/@name[not(.=preceding::ocrLib/@name)]">
			<xsl:text>LINK_OCR_LIB(</xsl:text><xsl:value-of select="."/><xsl:text>)&#10;</xsl:text>
		</xsl:for-each>
		<xsl:for-each select="//system/node/deviceDriver/linkPort/lib/@name[not(.=preceding::lib/@name)]">
			<xsl:text>LINK_LIBRARIES(</xsl:text><xsl:value-of select="."/><xsl:text>)&#10;</xsl:text>
		</xsl:for-each>
		<xsl:for-each select="//system/node/deviceDriver/linkPort/ocrLib/@name[not(.=preceding::ocrLib/@name)]">
			<xsl:text>LINK_OCR_LIB(</xsl:text><xsl:value-of select="."/><xsl:text>)&#10;</xsl:text>
		</xsl:for-each>
		<xsl:for-each select="//system/node/lib/@name[not(.=preceding::lib/@name)]">
			<xsl:text>LINK_LIBRARIES(</xsl:text><xsl:value-of select="."/><xsl:text>)&#10;</xsl:text>
		</xsl:for-each>
		<xsl:for-each select="//system/node/ocrLib/@name[not(.=preceding::ocrLib/@name)]">
			<xsl:text>LINK_OCR_LIB(</xsl:text><xsl:value-of select="."/><xsl:text>)&#10;</xsl:text>
		</xsl:for-each>
		<xsl:for-each select="//system/node/component/lib/@name[not(.=preceding::lib/@name)]">
			<xsl:text>LINK_LIBRARIES(</xsl:text><xsl:value-of select="."/><xsl:text>)&#10;</xsl:text>
		</xsl:for-each>
		<xsl:for-each select="//system/node/component/ocrLib/@name[not(.=preceding::ocrLib/@name)]">
			<xsl:text>LINK_OCR_LIB(</xsl:text><xsl:value-of select="."/><xsl:text>)&#10;</xsl:text>
		</xsl:for-each>
		<xsl:for-each select="//system/ocrGlobalLib">
			<xsl:text>LINK_OCR_LIB(</xsl:text><xsl:value-of select="@name"/><xsl:text>)&#10;</xsl:text>
		</xsl:for-each>
		<xsl:for-each select="//system/globalLib">
			<xsl:text>LINK_LIBRARIES(</xsl:text><xsl:value-of select="@name"/><xsl:text>)&#10;</xsl:text>
		</xsl:for-each>
	</xsl:template>	
 -->		
    <xsl:template name="link_lib">
        <xsl:for-each select="//*/lib/@name[not(.=preceding::lib/@name)]">
            <xsl:text>LINK_LIBRARIES(</xsl:text><xsl:value-of select="."/><xsl:text>)&#10;</xsl:text>
        </xsl:for-each>
        <xsl:for-each select="//*/ocrLib/@name[not(.=preceding::ocrLib/@name)]">
            <xsl:text>LINK_OCR_LIB(</xsl:text><xsl:value-of select="."/><xsl:text>)&#10;</xsl:text>
        </xsl:for-each>
        <xsl:for-each select="//*/ocrGlobalLib">
            <xsl:text>LINK_OCR_LIB(</xsl:text><xsl:value-of select="@name"/><xsl:text>)&#10;</xsl:text>
        </xsl:for-each>
        <xsl:for-each select="//*/globalLib">
            <xsl:text>LINK_LIBRARIES(</xsl:text><xsl:value-of select="@name"/><xsl:text>)&#10;</xsl:text>
        </xsl:for-each>
    </xsl:template> 
</xsl:stylesheet>
