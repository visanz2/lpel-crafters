<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" 
xmlns:xs="http://www.w3.org/2001/XMLSchema" xmlns:fn="http://www.w3.org/2005/xpath-functions" exclude-result-prefixes="xs fn xsl">
	<!--output format close to xquery-->
	<xsl:output method="text" encoding="utf-8" omit-xml-declaration="no"/>

	<xsl:template name="generateRoutingTable">
		<xsl:param name="core"/>
		<xsl:if test="//system/node/routingTable or $core/routingTable">
			<xsl:call-template name="routingTable">
				<xsl:with-param name="core" select="$core"/>
			</xsl:call-template>
		</xsl:if>
		<xsl:text>&#10;</xsl:text>
		<xsl:if test="//system/node/linkPortRoutingTable or $core/routingTable">
			<xsl:call-template name="linkPortRoutingTable">
				<xsl:with-param name="core" select="$core"/>
			</xsl:call-template>
		</xsl:if>
	</xsl:template>

	<xsl:template name="routingTable">
		<xsl:param name="core"/>
		<xsl:text>L1_TaskControlRecord *L1_</xsl:text>
		<xsl:call-template name="core_name"/>
		<xsl:text>RoutingTable[</xsl:text>
		<xsl:choose>
			<xsl:when test="$core">
				<xsl:value-of select="count($core/routingTable/field)"/>
				<xsl:text>] =&#10;{&#10;</xsl:text>
				<xsl:apply-templates select="$core/routingTable/field"/>
			</xsl:when>
			<xsl:otherwise>
				<xsl:value-of select="count(//system/node/routingTable/field)"/>
				<xsl:text>] =&#10;{&#10;</xsl:text>
				<xsl:apply-templates select="//system/node/routingTable/field"/>
			</xsl:otherwise>
		</xsl:choose>
		<xsl:text>};&#10;</xsl:text>
	</xsl:template>
	
	<xsl:template match="routingTable/field">
		<xsl:choose>
			<xsl:when test="@value!=0">
				<xsl:text>&#9;&amp;L1_</xsl:text>
				<xsl:call-template name="platform_name"/>
				<xsl:text>TaskControlBlock[</xsl:text><xsl:value-of select="@value"/>
				<xsl:text>],&#10;</xsl:text>
			</xsl:when>
			<xsl:otherwise>
				<xsl:text>&#9;NULL,&#10;</xsl:text>
			</xsl:otherwise>
		</xsl:choose>
	</xsl:template>

	<xsl:template name="linkPortRoutingTable">
		<xsl:param name="core"/>
		<xsl:text>void* linkPort_</xsl:text>
		<xsl:call-template name="core_name"/>
		<xsl:text>RoutingTable[</xsl:text>
		<xsl:choose>
			<xsl:when test="$core">
				<xsl:value-of select="count($core/linkPortRoutingTable/field)"/>
				<xsl:text>] =&#10;{&#10;</xsl:text>
				<xsl:apply-templates select="$core/linkPortRoutingTable/field"/>
			</xsl:when>
			<xsl:otherwise>
				<xsl:value-of select="count(//system/node/linkPortRoutingTable/field)"/>
				<xsl:text>] =&#10;{&#10;</xsl:text>
				<xsl:apply-templates select="//system/node/linkPortRoutingTable/field"/>
			</xsl:otherwise>
		</xsl:choose>
		<xsl:text>};&#10;</xsl:text>
	</xsl:template>
	
	<xsl:template match="linkPortRoutingTable/field">
		<xsl:choose>
			<xsl:when test="@value!=0">
				<xsl:text>&#9;&amp;</xsl:text><xsl:value-of select="@value"/>
				<xsl:text>,&#10;</xsl:text>
			</xsl:when>
			<xsl:otherwise>
				<xsl:text>&#9;NULL,&#10;</xsl:text>
			</xsl:otherwise>
		</xsl:choose>
	</xsl:template>

</xsl:stylesheet>

