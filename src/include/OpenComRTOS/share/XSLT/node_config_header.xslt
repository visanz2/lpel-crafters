<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" 
xmlns:xs="http://www.w3.org/2001/XMLSchema" xmlns:fn="http://www.w3.org/2005/xpath-functions" exclude-result-prefixes="xs fn xsl">
	<!--output format close to xquery-->
	<xsl:output method="text" encoding="utf-8" omit-xml-declaration="no"/>

	<xsl:template name="generateHeader">
		<xsl:param name="core"/>

		<xsl:text>#define </xsl:text><xsl:value-of select="//system/node/@name"/>
		<xsl:value-of select="$core"/>
<!--
		<xsl:choose>
			<xsl:when test="$core=''">-->
				<xsl:text>&#10;#define L1_NODE_NUMBER_OF_TASKS </xsl:text>
				<xsl:value-of select="//system/node/tasksNumber/@value"/>
				<xsl:text>&#10;#define L1_NODE_NUMBER_OF_HUBS </xsl:text>
				<xsl:value-of select="//system/node/hubsNumber/@value"/>
				<xsl:text>&#10;&#10;#include "L1_nodes_data.h"&#10;</xsl:text>
<!--			</xsl:when>
			<xsl:otherwise>
				<xsl:text>&#10;#define L1_NODE_NUMBER_OF_TASKS </xsl:text>
				<xsl:value-of select="//system/node/core[@name=substring-after($core,'_')]/tasksNumber/@value"/>
				<xsl:text>&#10;#define L1_NODE_NUMBER_OF_HUBS </xsl:text>
				<xsl:value-of select="//system/node/core[@name=substring-after($core,'_')]/hubsNumber/@value"/>
				<xsl:text>&#10;&#10;#include "L1_nodes_data.h"&#10;</xsl:text>
			</xsl:otherwise>
		</xsl:choose>-->
		<xsl:text>
#include &lt;L1_api.h&gt;
#include &lt;L1_hub_api.h&gt;
#include &lt;L1_kernel_data.h&gt;
#include &lt;L1_memory_api.h&gt;
#include &lt;L1_driver_api.h&gt;
#include &lt;L1_trace_api.h&gt;&#10;&#10;</xsl:text>

		<xsl:apply-templates select="//*[@taskId]">
			<xsl:sort select="@taskId" data-type="number"/>
		</xsl:apply-templates>
		<xsl:apply-templates select="//system/node/component"/>
	</xsl:template>
 	
	<xsl:template match="//*[@taskId]">
		<xsl:for-each select="entrypoint/@value[not(.=preceding::entrypoint/@value)]">
			<xsl:text>extern void </xsl:text><xsl:value-of select="."/>
			<xsl:text>(L1_TaskArguments Arguments);&#10;</xsl:text>
		</xsl:for-each>
	</xsl:template>
	<xsl:template match="//system/node/component">
		<xsl:for-each select="isr/@name[not(.=preceding::isr/@name)]">
			<xsl:text>extern void </xsl:text><xsl:value-of select="."/>
			<xsl:text>(L1_TaskArguments Arguments);&#10;</xsl:text>
		</xsl:for-each>
	</xsl:template>
</xsl:stylesheet>
