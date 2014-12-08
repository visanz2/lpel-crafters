<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" 
xmlns:xs="http://www.w3.org/2001/XMLSchema" xmlns:fn="http://www.w3.org/2005/xpath-functions" exclude-result-prefixes="xs fn xsl">
	<!--output format close to xquery-->
	<xsl:output method="text" encoding="utf-8" omit-xml-declaration="no"/>

	<xsl:template match="//*[@hubId]" mode="dataStructure">
		<xsl:choose>
			<xsl:when test="local-name()='fifo'">
				<xsl:text>L1_FifoData FIFO_</xsl:text><xsl:value-of select="@name"/>
				<xsl:text>_Data&#91;</xsl:text>
				<xsl:value-of select="size/@value"/><xsl:text>&#93;;&#10;</xsl:text>	
			</xsl:when>
			<xsl:when test="local-name()='memoryPool'">
				<xsl:text>L1_BYTE MemoryPool_</xsl:text><xsl:value-of select="@name"/>
				<xsl:text>_Memory&#91;</xsl:text><xsl:value-of select="numOfBlocks/@value"/>
				<xsl:text>&#93;&#91;</xsl:text><xsl:value-of select="sizeOfBlocks/@value"/>
				<xsl:text>&#93;;&#10;</xsl:text>
				<xsl:text>L1_MemoryBlock MemoryPool_</xsl:text><xsl:value-of select="@name"/>
				<xsl:text>_MemoryBlocks&#91;</xsl:text>
				<xsl:value-of select="numOfBlocks/@value"/><xsl:text>&#93; =&#10;</xsl:text>
				<xsl:text>{&#10;</xsl:text>
				<xsl:call-template name="mp-loop">
					<xsl:with-param name="i" select="1"/>
					<xsl:with-param name="count" select="numOfBlocks/@value"/>
					<xsl:with-param name="size" select="sizeOfBlocks/@value"/>
					<xsl:with-param name="name" select="@name"/>
				</xsl:call-template>
				<xsl:text>};&#10;&#10;</xsl:text>
			</xsl:when>
			<xsl:when test="local-name()='packetPool'">
				<xsl:text>L1_Packet PacketPool_</xsl:text><xsl:value-of select="@name"/>
				<xsl:text>_Data&#91;</xsl:text>
				<xsl:value-of select="size/@value"/><xsl:text>&#93;;&#10;</xsl:text>	
			</xsl:when>
		</xsl:choose>
	</xsl:template>

	<xsl:template name="mp-loop">
		<xsl:param name="i"/>
		<xsl:param name="count"/>
		<xsl:param name="size"/>
		<xsl:param name="name"/>

		<xsl:if test="$i &lt;= $count">
			<xsl:variable name="idec" select="$i - 1"/>
			<xsl:text>&#9;{&#10;</xsl:text>
			<xsl:text>&#9;&#9;.Header =&#10;</xsl:text>
			<xsl:text>&#9;&#9;{&#10;</xsl:text>
			<xsl:text>&#9;&#9;&#9;.ListElement = { NULL, NULL, 1 },&#10;</xsl:text>
			<xsl:text>&#9;&#9;&#9;.BlockSize = </xsl:text><xsl:value-of select="$size"/><xsl:text>,&#10;</xsl:text>
			<xsl:text>&#9;&#9;},&#10;</xsl:text>
			<xsl:text>&#9;&#9;.Data = MemoryPool_</xsl:text><xsl:value-of select="$name"/><xsl:text>_Memory&#91;</xsl:text>
			<xsl:value-of select="$idec"/>
			<xsl:text>&#93;&#10;</xsl:text>
			<xsl:text>&#9;},&#10;</xsl:text>
		</xsl:if>

		<xsl:if test="$i &lt;= $count">
			<xsl:call-template name="mp-loop">
				<xsl:with-param name="i" select="$i + 1"/>
				<xsl:with-param name="count" select="$count"/>
				<xsl:with-param name="size" select="$size"/>
				<xsl:with-param name="name" select="$name"/>
			</xsl:call-template>
		</xsl:if>
	</xsl:template>
</xsl:stylesheet>

