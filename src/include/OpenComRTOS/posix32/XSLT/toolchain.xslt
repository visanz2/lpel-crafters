<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" 
xmlns:xs="http://www.w3.org/2001/XMLSchema" xmlns:fn="http://www.w3.org/2005/xpath-functions" exclude-result-prefixes="xs fn xsl">
	<!--output format close to xquery-->
	<xsl:output method="text" encoding="utf-8" omit-xml-declaration="no"/>

	<xsl:template match="/">

		<xsl:text># the name of the target operating system
SET(CMAKE_SYSTEM_NAME posix32)

# which compilers to use for C and C++
SET(CMAKE_C_COMPILER "</xsl:text><xsl:value-of select="//system/node/compiler/@value"/><xsl:text>")

SET(CMAKE_ASM_COMPILER "</xsl:text><xsl:value-of select="//system/node/compiler/@value"/><xsl:text>")

# adjust the default behavior of the FIND_XXX() commands:
# search headers and libraries in the target environment, search 
# programs in the host environment
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM LAST)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

SET(OCR_PLATFORM "</xsl:text><xsl:value-of select="//system/node/@type"/><xsl:text>")
ADD_DEFINITIONS(-DL1_GLOBALID_SIZE=32)&#10;</xsl:text>
		<xsl:apply-templates select="//system/node/compilerArgument"/>
		<xsl:text>
INCLUDE_DIRECTORIES(${OCR_INSTALL_DIR}/../../src/platforms/${OCR_PLATFORM}/include)
INCLUDE_DIRECTORIES(${OCR_INSTALL_DIR}/../../include)</xsl:text>

	</xsl:template>

	<xsl:template match="compilerArgument">
		<xsl:text>ADD_DEFINITIONS(</xsl:text><xsl:value-of select="@value"/><xsl:text>)&#10;</xsl:text>
	</xsl:template>
	
</xsl:stylesheet>
