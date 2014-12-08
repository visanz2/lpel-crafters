<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" 
xmlns:xs="http://www.w3.org/2001/XMLSchema" xmlns:fn="http://www.w3.org/2005/xpath-functions" exclude-result-prefixes="xs fn xsl">
	<!--output format close to xquery-->
	<xsl:output method="text" encoding="utf-8" omit-xml-declaration="no"/>

	<xsl:template name="generatePlatformInitialization">
		<xsl:if test="//system/node/deviceDriver/linkPort">
			<xsl:call-template name="platform_initialization"/>
		</xsl:if>
	</xsl:template>

	<xsl:template match="deviceDriver/linkPort" mode="generate_structure">
		<xsl:value-of select="structure/@type"/><xsl:text> </xsl:text>
		<xsl:value-of select="structure/@type"/>
		<xsl:text>_</xsl:text><xsl:value-of select="../@name"/>
		<xsl:text>_</xsl:text><xsl:value-of select="@name"/>
		<xsl:text>_</xsl:text><xsl:value-of select="structure/@label"/>
		<xsl:choose>
			<xsl:when test="structure/field">
				<xsl:text> =&#10;</xsl:text>
				<xsl:text>{&#10;</xsl:text>
				<xsl:for-each select="structure/field">
					<xsl:if test="@type='string'">
						<xsl:if test="@name!='localIp'">
							<xsl:text>&#9;.</xsl:text><xsl:value-of select="@name"/><xsl:text> = "</xsl:text><xsl:value-of select="@value"/><xsl:text>",&#10;</xsl:text>
						</xsl:if>
					</xsl:if>
					<xsl:if test="@type='integer'">
						<xsl:if test="@name!='localIp'">
							<xsl:text>&#9;.</xsl:text><xsl:value-of select="@name"/><xsl:text> = </xsl:text><xsl:value-of select="@value"/><xsl:text>,&#10;</xsl:text>
						</xsl:if>					
					</xsl:if>
					<xsl:if test="@type='enum'">
						<xsl:if test="@name!='localIp'">
							<xsl:text>&#9;.</xsl:text><xsl:value-of select="@name"/><xsl:text> = </xsl:text><xsl:value-of select="@value"/><xsl:text>,&#10;</xsl:text>
						</xsl:if>					
					</xsl:if>
					<xsl:if test="@type='HubID'">
						<xsl:if test="@name!='localIp'">
							<xsl:text>&#9;.</xsl:text><xsl:value-of select="@name"/><xsl:text> = </xsl:text><xsl:value-of select="@value"/><xsl:text>,&#10;</xsl:text>
						</xsl:if>					
					</xsl:if>
					<xsl:if test="@type='array'">
						<xsl:if test="@name!='localIp'">
							<xsl:text>&#9;.</xsl:text><xsl:value-of select="@name"/><xsl:text> = (L1_UINT32[</xsl:text><xsl:value-of select="@value"/><xsl:text>]){},&#10;</xsl:text>
						</xsl:if>					
					</xsl:if>
				</xsl:for-each>
				<xsl:text>};&#10;&#10;</xsl:text>
			</xsl:when>
			<xsl:otherwise>
				<xsl:text>;&#10;&#10;</xsl:text>
			</xsl:otherwise>
		</xsl:choose>
	</xsl:template>

	<xsl:template name="platform_initialization">
		<xsl:apply-templates select="//system/node/deviceDriver/initFunctionDevice" mode="initDrivers"/>
		<xsl:for-each select="//system/node/deviceDriver/linkPort">
			<xsl:sort select="@orderNum" data-type="number"/>
			<xsl:if test="@commType='server'">
				<xsl:text>&#9;if(L1_FALSE == </xsl:text>
				<xsl:value-of select="initFunctionServer/@name"/><xsl:text>(&amp;</xsl:text>
				<xsl:value-of select="../structure/@type"/><xsl:text>_</xsl:text><xsl:value-of select="../@type"/>
				<xsl:text>_</xsl:text><xsl:value-of select="../@name"/>
				<xsl:text>_</xsl:text><xsl:value-of select="../structure/@label"/>
				<xsl:text>, &amp;</xsl:text>
				<xsl:value-of select="structure/@type"/>
				<xsl:text>_</xsl:text><xsl:value-of select="../@name"/>
				<xsl:text>_</xsl:text><xsl:value-of select="@name"/>
				<xsl:text>_</xsl:text><xsl:value-of select="structure/@label"/>
				<xsl:text>)){&#10;&#9;&#9;</xsl:text>
					<xsl:call-template name="platform_exit"/>
				<xsl:text>&#10;&#9;}&#10;</xsl:text>
			</xsl:if>
			<xsl:if test="@commType='client'">
				<xsl:text>&#9;if(L1_FALSE == </xsl:text>
				<xsl:value-of select="initFunctionClient/@name"/><xsl:text>(&amp;</xsl:text>
				<xsl:value-of select="../structure/@type"/><xsl:text>_</xsl:text><xsl:value-of select="../@type"/>
				<xsl:text>_</xsl:text><xsl:value-of select="../@name"/>
				<xsl:text>_</xsl:text><xsl:value-of select="../structure/@label"/>
				<xsl:text>, &amp;</xsl:text>
				<xsl:value-of select="structure/@type"/>
				<xsl:text>_</xsl:text><xsl:value-of select="../@name"/>
				<xsl:text>_</xsl:text><xsl:value-of select="@name"/>
				<xsl:text>_</xsl:text><xsl:value-of select="structure/@label"/>
				<xsl:text>)){&#10;&#9;&#9;</xsl:text>
					<xsl:call-template name="platform_exit"/>
				<xsl:text>&#10;&#9;}&#10;</xsl:text>
			</xsl:if>
		</xsl:for-each>
	</xsl:template>

	<xsl:template match="deviceDriver/initFunctionDevice" mode="initDrivers">
		<xsl:text>&#9;if(RC_FAIL == </xsl:text>
		<xsl:value-of select="@name"/><xsl:text>(&amp;</xsl:text>
		<xsl:value-of select="../structure/@type"/><xsl:text>_</xsl:text><xsl:value-of select="../@type"/>
		<xsl:text>_</xsl:text><xsl:value-of select="../@name"/>
		<xsl:text>_</xsl:text><xsl:value-of select="../structure/@label"/>
			<xsl:text>)){&#10;&#9;&#9;</xsl:text>
				<xsl:call-template name="platform_exit"/>
			<xsl:text>&#10;&#9;}&#10;</xsl:text>
	</xsl:template>

</xsl:stylesheet>

