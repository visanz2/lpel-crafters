<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" 
xmlns:xs="http://www.w3.org/2001/XMLSchema" xmlns:fn="http://www.w3.org/2005/xpath-functions" exclude-result-prefixes="xs fn xsl">
	<!--output format close to xquery-->
	<xsl:output method="text" encoding="utf-8" omit-xml-declaration="no"/>

	<xsl:template name="genaratePreallocatedPackets">
		<xsl:param name="currentNode"/>
		<xsl:param name="beginSym"/>
		<xsl:param name="endSym"/>

		<xsl:text>static L1_Packet PreallocatedPackets&#91;L1_NODE_NUMBER_OF_TASKS&#93; =&#10;{&#10;</xsl:text>
			<xsl:apply-templates select="//*[@taskId]" mode="preallocatedPackets">
				<xsl:with-param name="currentNode" select="$currentNode"/>
				<xsl:sort select="@taskId" data-type="number"/>
				<xsl:with-param name="beginSym" select="$beginSym"/>
				<xsl:with-param name="endSym" select="$endSym"/>
			</xsl:apply-templates>
		<xsl:text>};&#10;</xsl:text>
	</xsl:template>

	<xsl:template match="//*[@taskId]" mode="preallocatedPackets">
		<xsl:param name="currentNode"/>
		<xsl:param name="beginSym"/>
		<xsl:param name="endSym"/>

		<xsl:text>&#9;{&#10;</xsl:text>
		<xsl:text>&#9;&#9;</xsl:text>
		<xsl:value-of select="$beginSym"/><xsl:text>.ListElement = </xsl:text>
		<xsl:value-of select="$endSym"/>
		<xsl:text>{NULL,NULL,</xsl:text>
		<xsl:value-of select="priority/@value"/>
		<xsl:text>},&#10;</xsl:text>
		<xsl:text>&#9;&#9;</xsl:text>
		<xsl:value-of select="$beginSym"/><xsl:text>.ServiceID = </xsl:text>
		<xsl:value-of select="$endSym"/>
		<xsl:text>0,&#10;</xsl:text>

		<xsl:text>&#9;&#9;</xsl:text>
		<xsl:value-of select="$beginSym"/><xsl:text>.RequestingTaskID = </xsl:text>
		<xsl:value-of select="$endSym"/>
		<xsl:text>((</xsl:text><xsl:value-of select="@taskId"/><xsl:text> &lt;&lt; 0) | (</xsl:text>
		<xsl:choose>
			<xsl:when test="$currentNode=''">
				<xsl:text>L1_PRESENT_NODE_ID</xsl:text>
			</xsl:when>
			<xsl:otherwise>
				<xsl:value-of select="$currentNode"/>
			</xsl:otherwise>
		</xsl:choose>
		<xsl:text> &lt;&lt; L1_NODE_ID_SIZE)),&#10;</xsl:text>

		<xsl:text>&#9;&#9;</xsl:text>
		<xsl:value-of select="$beginSym"/><xsl:text>.DestinationPortID = </xsl:text>
		<xsl:value-of select="$endSym"/>
		<xsl:text>0,&#10;</xsl:text>

		<xsl:text>&#9;&#9;</xsl:text>
		<xsl:value-of select="$beginSym"/><xsl:text>.TimeoutTimer = </xsl:text>
		<xsl:value-of select="$endSym"/>
		<xsl:text>{ { NULL, NULL, 0, 0 }, NULL },&#10;</xsl:text>
		<xsl:text>&#9;&#9;</xsl:text>
		<xsl:value-of select="$beginSym"/><xsl:text>.Timeout = </xsl:text>
		<xsl:value-of select="$endSym"/>
		<xsl:text>0,&#10;</xsl:text>

		<xsl:text>&#9;&#9;</xsl:text>
		<xsl:value-of select="$beginSym"/><xsl:text>.Status = </xsl:text>
		<xsl:value-of select="$endSym"/>
		<xsl:text>RC_OK,&#10;</xsl:text>
		<xsl:text>&#9;&#9;</xsl:text>
		<xsl:value-of select="$beginSym"/><xsl:text>.SequenceNumber = </xsl:text>
		<xsl:value-of select="$endSym"/>
		<xsl:text>0,&#10;</xsl:text>
		<xsl:text>&#9;&#9;</xsl:text>
		<xsl:value-of select="$beginSym"/><xsl:text>.DataSize = </xsl:text>
		<xsl:value-of select="$endSym"/>
		<xsl:text>0,&#10;</xsl:text>
		<xsl:text>&#9;&#9;</xsl:text>
		<xsl:value-of select="$beginSym"/><xsl:text>.OwnerPool = </xsl:text>
		<xsl:value-of select="$endSym"/>
		<xsl:text>NULL,&#10;</xsl:text>

		<xsl:text>#ifdef PENDING_REQUESTS_QUEUE&#10;</xsl:text>
		<xsl:text>&#9;&#9;</xsl:text>
		<xsl:value-of select="$beginSym"/><xsl:text>.PendingRequestListElement = </xsl:text>
		<xsl:value-of select="$endSym"/>
		<xsl:text>{NULL,NULL,</xsl:text>
		<xsl:value-of select="priority/@value"/>
		<xsl:text>},&#10;</xsl:text>
		<xsl:text>&#9;&#9;</xsl:text>
		<xsl:value-of select="$beginSym"/><xsl:text>.PendingRequestHandler = </xsl:text>
		<xsl:value-of select="$endSym"/>
		<xsl:text>NULL&#10;</xsl:text>		
		<xsl:text>#endif /* PENDING_REQUESTS_QUEUE */ &#10;</xsl:text>
		

		<xsl:text>&#9;},&#10;</xsl:text>
	</xsl:template>

</xsl:stylesheet>

