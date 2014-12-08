<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:xs="http://www.w3.org/2001/XMLSchema"
	xmlns:fn="http://www.w3.org/2005/xpath-functions"
	exclude-result-prefixes="xs fn xsl">
	<!--output format close to xquery -->
	<xsl:output method="text" encoding="utf-8"
		omit-xml-declaration="yes" />

	<xsl:template name="EntityNamesToIds">
		<xsl:text>&#10;</xsl:text>
		<xsl:text>&#10;</xsl:text>
		<xsl:text>L1_TaskNameToID L1_TaskNamesToIDs[L1_NODE_NUMBER_OF_TASKS] = {&#10;</xsl:text>
		<xsl:apply-templates select="//*[@taskId]">
			<xsl:sort select="@taskId" data-type="number" />
		</xsl:apply-templates>
		<xsl:text>};&#10;</xsl:text>

		<xsl:text>&#10;</xsl:text>
		<xsl:text>&#10;</xsl:text>

		<xsl:text>L1_HubNameToID L1_HubNameToIDs[L1_NODE_NUMBER_OF_HUBS] = {&#10;</xsl:text>
		<xsl:apply-templates select="//*[@hubId]">
			<xsl:sort select="@hubId" data-type="number" />
		</xsl:apply-templates>
		<xsl:text>};&#10;</xsl:text>
	</xsl:template>


	<xsl:template match="//*[@taskId]">
		<xsl:text>    {&#10;        .name = &quot;</xsl:text>
		<xsl:value-of select="@name" />
		<xsl:text>&quot;,&#10;        .id   = ((</xsl:text>
		<xsl:value-of select="@taskId" />
		<xsl:text> &lt;&lt; 0) | (L1_PRESENT_NODE_ID &lt;&lt; L1_NODE_ID_SIZE))&#10;    }, &#10;</xsl:text>
	</xsl:template>

	<xsl:template name="hubType">
		<xsl:param name="entity" />
		<xsl:choose>
			<xsl:when test="$entity='port'">
				<xsl:text>L1_PORT</xsl:text>
			</xsl:when>
			<xsl:when test="$entity='event'">
				<xsl:text>L1_EVENT</xsl:text>
			</xsl:when>
			<xsl:when test="$entity='event'">
				<xsl:text>L1_DATAEVENT</xsl:text>
			</xsl:when>
			<xsl:when test="$entity='semaphore'">
				<xsl:text>L1_SEMAPHORE</xsl:text>
			</xsl:when>
			<xsl:when test="$entity='resource'">
				<xsl:text>L1_RESOURCE</xsl:text>
			</xsl:when>
			<xsl:when test="$entity='fifo'">
				<xsl:text>L1_FIFO</xsl:text>
			</xsl:when>
			<xsl:when test="$entity='memoryPool'">
				<xsl:text>L1_MEMORYPOOL</xsl:text>
			</xsl:when>
			<xsl:when test="$entity='packetPool'">
				<xsl:text>L1_PACKETPOOL</xsl:text>
			</xsl:when>
            <xsl:when test="$entity='blackBoard'">
                <xsl:text>L1_BLACKBOARD</xsl:text>
            </xsl:when>
		</xsl:choose>
	</xsl:template>



	<xsl:template match="//*[@hubId]">
		<xsl:text>    {&#10;        .name = &quot;</xsl:text>
		<xsl:value-of select="@name" />
		<xsl:text>&quot;,&#10;        .id   = ((</xsl:text>
		<xsl:value-of select="@hubId" />
		<xsl:text> &lt;&lt; 0) | (L1_PRESENT_NODE_ID &lt;&lt; L1_NODE_ID_SIZE)),&#10;</xsl:text>
		<xsl:text>        .type = </xsl:text>
		<!-- <xsl:value-of select="@type" /> -->
		<xsl:call-template name="hubType">
			<xsl:with-param name="entity" select="local-name()" />
		</xsl:call-template>
		<xsl:text>&#10;    }, &#10;</xsl:text>
	</xsl:template>



</xsl:stylesheet>
