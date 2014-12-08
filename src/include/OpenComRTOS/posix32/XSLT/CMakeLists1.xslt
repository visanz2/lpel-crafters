<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" 
xmlns:xs="http://www.w3.org/2001/XMLSchema" xmlns:fn="http://www.w3.org/2005/xpath-functions" exclude-result-prefixes="xs fn xsl">
	<!--output format close to xquery-->
	<xsl:import href="../../share/XSLT/globalCMakeLists.xslt"/>
	<xsl:output method="text" encoding="utf-8" omit-xml-declaration="no"/>

	<xsl:template match="/">
		<xsl:call-template name="genarateGlobalConent"/>
	</xsl:template>	

	<xsl:template name="compiler_options">
	</xsl:template>
	
	<xsl:template name="platform_includes">
	    <!-- Making examples with the Graphcis Host Server link on Ubuntu 12.04.1  -->
	    <xsl:text>SET(CMAKE_C_LINK_FLAGS "-Wl,--no-as-needed")&#10;</xsl:text>
        <!--   <xsl:text>LINK_LIBRARIES(gtk-x11-2.0)&#10;</xsl:text>-->
        <xsl:text>include(FindPkgConfig)&#10;</xsl:text>
        <xsl:text>pkg_check_modules (GTK3 gtk+-3.0)&#10;</xsl:text>
        <xsl:text>message(STATUS "inc: -${GTK3_INCLUDE_DIRS}")&#10;</xsl:text>
        <xsl:text>message(STATUS "link flags: -${GTK3_LDFLAGS}")&#10;</xsl:text>
        <xsl:text>message(STATUS "cflags: -${GTK3_CFLAGS}")&#10;</xsl:text>
        <xsl:text>message(STATUS "link dir: -${GTK3_LINK_DIR}")&#10;</xsl:text>
        <xsl:text>include_directories(${GTK3_INCLUDE_DIRS})&#10;</xsl:text>
        <xsl:text>link_directories(${GTK3_LIBRARY_DIRS})&#10;</xsl:text>
        <xsl:text>LINK_LIBRARIES(${GTK3_LIBRARIES})&#10;</xsl:text>
		<xsl:text>LINK_LIBRARIES(pthread)&#10;</xsl:text>
	</xsl:template>
		
</xsl:stylesheet>
