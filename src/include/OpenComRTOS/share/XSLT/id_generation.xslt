<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" 
xmlns:xs="http://www.w3.org/2001/XMLSchema" xmlns:fn="http://www.w3.org/2005/xpath-functions" exclude-result-prefixes="xs fn xsl">
	<!--output format close to xquery-->
	<xsl:output method="text" encoding="utf-8" omit-xml-declaration="yes"/>

	<xsl:template name="generateIDs">
		<xsl:text>&lt;node name=&quot;</xsl:text>
		<xsl:value-of select="//system/node/@name"/>
		<xsl:text>&quot; id=&quot;</xsl:text>		
		<xsl:value-of select="//system/node/nodeID/@value"/>
		<xsl:text>&quot; type=&quot;</xsl:text>		
		<xsl:value-of select="//system/node/@type"/>
		<xsl:text>&quot;&gt;&#10;</xsl:text>
		<xsl:text>    &lt;tasks&gt;&#10;</xsl:text>
			<xsl:apply-templates select="//*[@taskId]">
				<xsl:sort select="@taskId" data-type="number"/>
			</xsl:apply-templates>
		<xsl:text>    &lt;/tasks&gt;&#10;</xsl:text>
		
		<xsl:text>    &lt;hubs&gt;&#10;</xsl:text>
			<xsl:apply-templates select="//*[@hubId]">
				<xsl:sort select="@hubId" data-type="number"/>
			</xsl:apply-templates>
		<xsl:text>    &lt;/hubs&gt;&#10;</xsl:text>
	</xsl:template>

	<xsl:template match="//*[@taskId]">
		<xsl:text>        &lt;task name=&quot;</xsl:text>
		<xsl:value-of select="@name"/>
		<xsl:text>&quot; id=&quot;</xsl:text>		
		<xsl:value-of select="@taskId"/>
		<xsl:text>&quot; type=&quot;</xsl:text>		
		<xsl:value-of select="@type"/>
		<xsl:text>&quot;/&gt;&#10;</xsl:text>
	</xsl:template>

	<xsl:template match="//*[@hubId]">
		<xsl:text>        &lt;hub name=&quot;</xsl:text>
		<xsl:value-of select="@name"/>
		<xsl:text>&quot; id=&quot;</xsl:text>		
		<xsl:value-of select="@hubId"/>
		<xsl:text>&quot; type=&quot;</xsl:text>		
		<xsl:value-of select="@type"/>
		<xsl:text>&quot; hubType=&quot;</xsl:text>		
		<xsl:value-of select="local-name()"/>
		<xsl:if test="@serverType">
			<xsl:text>&quot; serverType=&quot;</xsl:text>		
			<xsl:value-of select="@serverType"/>
			<xsl:if test="@serverType='tldClient'">
				<xsl:text>&quot; portNumber=&quot;</xsl:text>
				<xsl:value-of select="../structure/field[@name='portNumber']/@value"/>
			</xsl:if>
		</xsl:if>
		<xsl:text>&quot;/&gt;&#10;</xsl:text>
	</xsl:template>

</xsl:stylesheet>
