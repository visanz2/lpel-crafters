<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" 
xmlns:xs="http://www.w3.org/2001/XMLSchema" xmlns:fn="http://www.w3.org/2005/xpath-functions" exclude-result-prefixes="xs fn xsl">
	<!--output format close to xquery-->
	<xsl:output method="text" encoding="utf-8" omit-xml-declaration="no"/>

	<xsl:template name="generateKernelPacketPool">
		<xsl:if test="//system/netLink">
			<xsl:apply-templates select="//system/node/packetPool" mode="kernel_packetpool"/>		
		</xsl:if>
	</xsl:template>

	<xsl:template match="//system/node/packetPool" mode="kernel_packetpool">
		<xsl:if test="position() = last()-1">
			<xsl:text>&#10;
/* used in boostPriority */
const L1_HubID L1_</xsl:text>
			<xsl:value-of select="@name"/>
			<xsl:text>ID = ((</xsl:text><xsl:value-of select="@hubId"/><xsl:text> &lt;&lt; 0) | (</xsl:text>
			<xsl:value-of select="//system/node/@name"/>
			<xsl:text>_NODE_ID &lt;&lt; L1_NODE_ID_SIZE));&#10;</xsl:text>
  		</xsl:if>
    		<xsl:if test="position() = last()">
			<xsl:text>const L1_HubID L1_</xsl:text>
			<xsl:value-of select="@name"/>
			<xsl:text>ID = ((</xsl:text><xsl:value-of select="@hubId"/><xsl:text> &lt;&lt; 0) | (</xsl:text>
			<xsl:value-of select="//system/node/@name"/>
			<xsl:text>_NODE_ID &lt;&lt; L1_NODE_ID_SIZE));&#10;</xsl:text>
		</xsl:if>
		
	</xsl:template>

</xsl:stylesheet>

