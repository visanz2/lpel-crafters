<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" 
xmlns:xs="http://www.w3.org/2001/XMLSchema" xmlns:fn="http://www.w3.org/2005/xpath-functions" exclude-result-prefixes="xs fn xsl">
	<!--output format close to xquery-->
	<xsl:output method="text" encoding="utf-8" omit-xml-declaration="no"/>

	<xsl:template name="node_sourceFile">
	<!--
		<xsl:for-each select="//system/node/sourceFile/@value[not(.=preceding::sourceFile/@value)]">
			<xsl:text>&#9;${CMAKE_CURRENT_SOURCE_DIR}/../../../</xsl:text><xsl:value-of select="."/><xsl:text>&#10;</xsl:text>
		</xsl:for-each>

		<xsl:for-each select="//system/node/core/sourceFile/@value[not(.=preceding::sourceFile/@value)]">
			<xsl:text>&#9;${CMAKE_CURRENT_SOURCE_DIR}/../../../</xsl:text><xsl:value-of select="."/><xsl:text>&#10;</xsl:text>
		</xsl:for-each> -->
		<!-- Take all occurences of <sourceFile> into account -->
        <xsl:for-each select="//*/sourceFile/@value[not(.=preceding::sourceFile/@value)]">
			<!-- Only add the line if the attribute value has content, which is not the case for the Idle-Task. -->
            <xsl:if test=".!=''">
            	<xsl:text>&#9;${CMAKE_CURRENT_SOURCE_DIR}/../../../</xsl:text><xsl:value-of select="."/><xsl:text>&#10;</xsl:text>
        	</xsl:if>
		</xsl:for-each>
	</xsl:template>

	<xsl:template name="task_sourceFile">
	<!--  
	    <xsl:for-each select="//system/node/task/sourceFile/@value[not(.=preceding::sourceFile/@value)]">
		<xsl:if test="not(.='')">
			  <xsl:text>&#9;${CMAKE_CURRENT_SOURCE_DIR}/../../../</xsl:text><xsl:value-of select="."/><xsl:text>&#10;</xsl:text>
		</xsl:if>
	    </xsl:for-each>
	    <xsl:for-each select="//system/node/core/task/sourceFile/@value[not(.=preceding::sourceFile/@value)]">
		<xsl:if test="not(.='')">
			  <xsl:text>&#9;${CMAKE_CURRENT_SOURCE_DIR}/../../../</xsl:text><xsl:value-of select="."/><xsl:text>&#10;</xsl:text>
		</xsl:if>
	    </xsl:for-each>
	    -->
	</xsl:template>

</xsl:stylesheet>
