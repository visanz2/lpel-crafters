<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
	<xsl:output method="text" indent="yes" name="text"/>

	<xsl:param name="nodeName"/>

	<xsl:template match="/">
		<xsl:apply-templates select="/systemRoutingTable/nodes/node[@name=$nodeName]"/>
	</xsl:template>

	<xsl:template match="/systemRoutingTable/nodes/node[@name=$nodeName]">
		<xsl:text>#include &lt;kernel_data.h&gt;&#10;&#10;</xsl:text>
		<xsl:text>extern L1_TaskControlRecord L1_TaskControlBlock[];&#10;&#10;</xsl:text>
		<xsl:apply-templates select="linkPorts/linkPort" mode="extern"/>
		<xsl:apply-templates select="routingTable/destination" mode="fatlinks">
			<xsl:sort select="@nodeId" data-type="number"/>
		</xsl:apply-templates>

		<xsl:text>L1_FatLink *L1_RoutingTable</xsl:text>
		<xsl:text>[</xsl:text><xsl:value-of select="count(routingTable/destination)"/><xsl:text>] =&#10;</xsl:text>
		<xsl:text>{&#10;</xsl:text>
		<xsl:apply-templates select="routingTable/destination" mode="routingTable"/>
		<xsl:text>};&#10;&#10;</xsl:text>

		<xsl:text>void L1_initializePlatformNodeSockets(void)&#10;</xsl:text>
		<xsl:text>{&#10;</xsl:text>
		<xsl:apply-templates select="routingTable/destination/route" mode="init"/>
		<xsl:text>}&#10;</xsl:text>
	</xsl:template>

	<xsl:template match="routingTable/destination" mode="fatlinks">
		<xsl:variable name="nodeId" select="../../@id"/>
		<xsl:if test="not($nodeId=@nodeId)">
			<xsl:text>L1_TaskControlRecord *Scheduler_</xsl:text>
			<xsl:value-of select="@name"/>
			<xsl:text>[</xsl:text><xsl:value-of select="count(route)"/><xsl:text>] =&#10;</xsl:text>
			<xsl:text>{&#10;</xsl:text>
			<xsl:apply-templates select="route" mode="TCB"/>
			<xsl:text>};&#10;&#10;</xsl:text>

			<xsl:text>L1_FatLink FatLink_</xsl:text>
			<xsl:value-of select="@name"/><xsl:text> =&#10;</xsl:text>
			<xsl:text>{&#10;</xsl:text>
			<xsl:text>&#9;.schedule = Scheduler_</xsl:text><xsl:value-of select="@name"/><xsl:text>,&#10;</xsl:text>
			<xsl:text>&#9;.scheduleLength = </xsl:text><xsl:value-of select="count(route)"/><xsl:text>,&#10;</xsl:text>
			<xsl:text>&#9;.nextScheduledLink = 0,&#10;</xsl:text>
			<xsl:text>};&#10;&#10;</xsl:text>
		</xsl:if>
	</xsl:template>

	<xsl:template match="routingTable/destination" mode="routingTable">
		<xsl:variable name="nodeId" select="../../@id"/>
		<xsl:choose>
			<xsl:when test="not($nodeId=@nodeId)">
				<xsl:text>&#9;&amp;FatLink_</xsl:text>
				<xsl:value-of select="@name"/>
				<xsl:text>,&#10;</xsl:text>
			</xsl:when>
			<xsl:otherwise>
				<xsl:text>&#9;NULL,&#10;</xsl:text>
			</xsl:otherwise>
		</xsl:choose>
	</xsl:template>

	<xsl:template match="route" mode="TCB">
		<xsl:text>&#9;&#38;L1_TaskConrolBlock[</xsl:text>
		<xsl:variable name="ref" select="@ref"/>
		<xsl:for-each select="../../../linkPorts/linkPort">
			<xsl:if test="$ref=@label">
				<xsl:value-of select="@txTaskId"/>
			</xsl:if>		
		</xsl:for-each>
		<xsl:text>],&#10;</xsl:text>
	</xsl:template>

	<xsl:template match="routingTable/destination/route" mode="init">
		<xsl:text>&#9;if(L1_FALSE == </xsl:text>
		<xsl:variable name="ref" select="@ref"/>
		<xsl:for-each select="../../../linkPorts/linkPort">
			<xsl:if test="$ref=@label">
				<xsl:choose>
					<xsl:when test="@commType='server'">
						<xsl:value-of select="initFunctionServer/@name"/>
					</xsl:when>
					<xsl:when test="@commType='client'">
						<xsl:value-of select="initFunctionClient/@name"/>
					</xsl:when>
				</xsl:choose>
			</xsl:if>		
		</xsl:for-each>
		<xsl:text>(&amp;</xsl:text><xsl:value-of select="@ref"/><xsl:text>)){&#10;</xsl:text>
		<xsl:text>&#9;&#9;exit(-1);&#10;</xsl:text>
		<xsl:text>&#9;}&#10;</xsl:text>
	</xsl:template>

	<xsl:template match="linkPorts/linkPort" mode="extern">
		<xsl:text>extern </xsl:text><xsl:value-of select="@type"/>
		<xsl:text> </xsl:text><xsl:value-of select="@label"/><xsl:text>;&#10;</xsl:text>
	</xsl:template>

</xsl:stylesheet>

