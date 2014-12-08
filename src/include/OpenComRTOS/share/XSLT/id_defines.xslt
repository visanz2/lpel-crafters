<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" 
xmlns:xs="http://www.w3.org/2001/XMLSchema" xmlns:fn="http://www.w3.org/2005/xpath-functions" exclude-result-prefixes="xs fn xsl">
	<!--output format close to xquery-->
	<xsl:output method="text" encoding="utf-8" omit-xml-declaration="no"/>

	<xsl:template name="generateTaskIdDefines">
		<xsl:param name="core_name"/>
		<xsl:apply-templates select="//*[@taskId]">
			<xsl:with-param name="core_name" select="$core_name"/>
			<xsl:sort select="@taskId" data-type="number"/>
		</xsl:apply-templates>
	</xsl:template>

	<xsl:template name="generateHubIdDefines">
		<xsl:param name="core_name"/>
		<xsl:apply-templates select="//*[@hubId]">
			<xsl:with-param name="core_name" select="$core_name"/>
			<xsl:sort select="@hubId" data-type="number"/>
		</xsl:apply-templates>
	</xsl:template>

	<xsl:template match="//*[@taskId]">
		<xsl:param name="core_name"/>
		<xsl:call-template name="generateID"> 
			<xsl:with-param name="entity" select="."/> 
			<xsl:with-param name="id" select="@taskId"/> 
			<xsl:with-param name="core_name" select="$core_name"/>
		</xsl:call-template>
	</xsl:template>

	<xsl:template match="//*[@hubId]">
		<xsl:param name="core_name"/>
		<xsl:call-template name="generateID"> 
			<xsl:with-param name="entity" select="."/> 
			<xsl:with-param name="id" select="@hubId"/> 
			<xsl:with-param name="core_name" select="$core_name"/>
		</xsl:call-template>
	</xsl:template>

	<xsl:template name="generateID"> 
		<xsl:param name="entity"/>
		<xsl:param name="id"/>
		<xsl:param name="core_name"/>

		<xsl:if test="$entity/@origin!='system' or not($entity/@origin)"> 
			<xsl:text>#define </xsl:text>
			<xsl:choose>
				<xsl:when test="$entity/../../@commType">
					<xsl:value-of select="$entity/@name"/>
					<xsl:text>_</xsl:text>
					<xsl:value-of select="//system/node/@name"/>
					<xsl:text>_</xsl:text>
					<xsl:value-of select="$entity/../../@name"/>
				</xsl:when>
				<xsl:otherwise>
					<xsl:value-of select="$entity/@name"/>
				</xsl:otherwise>
			</xsl:choose>

			<xsl:text> ((</xsl:text><xsl:value-of select="$id"/><xsl:text> &lt;&lt; 0) | (</xsl:text>
			<xsl:value-of select="//system/node/@name"/><xsl:value-of select="$core_name"/>
			<xsl:text>_NODE_ID &lt;&lt; L1_NODE_ID_SIZE))&#10;</xsl:text>
		</xsl:if>
	</xsl:template>

</xsl:stylesheet>

