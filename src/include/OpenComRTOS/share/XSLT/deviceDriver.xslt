<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" 
xmlns:xs="http://www.w3.org/2001/XMLSchema" xmlns:fn="http://www.w3.org/2005/xpath-functions" exclude-result-prefixes="xs fn xsl">
	<!--output format close to xquery-->
	<xsl:output method="text" encoding="utf-8" omit-xml-declaration="no"/>

    <xsl:template match="array">
        <xsl:param name="initStr"/>
        <xsl:value-of select="@type"/><xsl:text> </xsl:text>
        <xsl:value-of select="../@name"/>
        <xsl:text>_</xsl:text>
        <xsl:value-of select="@name"/>
        <xsl:choose>
            <xsl:when test="@label">
                <xsl:text>_</xsl:text>
                <xsl:value-of select="@label"/>
            </xsl:when>
            <xsl:otherwise>
            </xsl:otherwise>
        </xsl:choose>
        <xsl:text>[</xsl:text>
        <xsl:value-of select="@nbrOfElements"/>
        <xsl:text>];&#10;&#10;</xsl:text>
    </xsl:template>


	<xsl:template match="structure">
		<xsl:param name="initStr"/>
		<xsl:value-of select="@type"/><xsl:text> </xsl:text>
		<xsl:value-of select="@type"/><xsl:text>_</xsl:text>
		<xsl:choose>
			<xsl:when test="../@type">
				<xsl:value-of select="../@type"/>
			</xsl:when>
			<xsl:otherwise>
				<xsl:value-of select="../@name"/>
			</xsl:otherwise>
		</xsl:choose>
		<xsl:text>_</xsl:text><xsl:value-of select="../@name"/>
		<xsl:text>_</xsl:text><xsl:value-of select="@label"/>
		<xsl:choose>
			<xsl:when test="field">
				<xsl:text> =&#10;</xsl:text>
				<xsl:text>{&#10;</xsl:text>
				<xsl:for-each select="field">
				  <xsl:choose>
					<xsl:when test="@type='string'">
						<xsl:if test="@name!='localIp'">
							<xsl:text>&#9;.</xsl:text><xsl:value-of select="@name"/><xsl:text> = "</xsl:text><xsl:value-of select="@value"/><xsl:text>",&#10;</xsl:text>
						</xsl:if>
					</xsl:when>
					<xsl:when test="@type='integer'">
						<xsl:if test="@name!='localIp'">
							<xsl:text>&#9;.</xsl:text><xsl:value-of select="@name"/><xsl:text> = </xsl:text><xsl:value-of select="@value"/><xsl:text>,&#10;</xsl:text>
						</xsl:if>					
					</xsl:when>
					<xsl:when test="@type='enum'">
						<xsl:if test="@name!='localIp'">
							<xsl:text>&#9;.</xsl:text><xsl:value-of select="@name"/><xsl:text> = </xsl:text><xsl:value-of select="@value"/><xsl:text>,&#10;</xsl:text>
						</xsl:if>					
					</xsl:when>
					<xsl:when test="@type='HubID'">
						<xsl:if test="@name!='localIp'">
							<xsl:text>&#9;.</xsl:text><xsl:value-of select="@name"/><xsl:text> = </xsl:text><xsl:value-of select="@value"/><xsl:text>,&#10;</xsl:text>
						</xsl:if>					
					</xsl:when>
					<xsl:when test="@type='array'">
						<xsl:if test="@name!='localIp'">
							<xsl:text>&#9;.</xsl:text><xsl:value-of select="@name"/><xsl:text> = (L1_UINT32[</xsl:text><xsl:value-of select="@value"/><xsl:text>]){},&#10;</xsl:text>
						</xsl:if>					
					</xsl:when>
				  </xsl:choose>
				</xsl:for-each>
				<xsl:text>};&#10;&#10;</xsl:text>
			</xsl:when>
			<xsl:when test="$initStr='true'">
					<xsl:if test="substring-after(@location,':')='loadOcr'">
					<xsl:text> =&#10;</xsl:text>
					<xsl:text>{&#10;</xsl:text>

					<xsl:for-each select="../device/initFunction/channel">
						<xsl:text>&#9;.</xsl:text><xsl:value-of select="@name"/><xsl:text> = channels[</xsl:text>
						<xsl:value-of select="@num"/>
						<xsl:text>],&#10;</xsl:text>
					</xsl:for-each>
				</xsl:if>
				<xsl:text>};&#10;&#10;</xsl:text>
			</xsl:when>
			<xsl:otherwise>
				<xsl:text>;&#10;&#10;</xsl:text>
			</xsl:otherwise>
		</xsl:choose>
	</xsl:template>

</xsl:stylesheet>

