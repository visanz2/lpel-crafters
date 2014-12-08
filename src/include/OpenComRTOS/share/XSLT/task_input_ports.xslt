<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" 
xmlns:xs="http://www.w3.org/2001/XMLSchema" xmlns:fn="http://www.w3.org/2005/xpath-functions" exclude-result-prefixes="xs fn xsl">
	<!--output format close to xquery-->
	<xsl:output method="text" encoding="utf-8" omit-xml-declaration="no"/>

	<xsl:template name="generateTaskInputPorts">
		<xsl:param name="beginSym"/>
		<xsl:param name="endSym"/>

		<xsl:text>L1_InputPort L1_</xsl:text>
		<xsl:call-template name="platform_name"/>
		<xsl:text>TaskInputPorts&#91;L1_NODE_NUMBER_OF_TASKS&#93; =&#10;{&#10;</xsl:text>
			<xsl:apply-templates select="//*[@taskId]" mode="taskInputPorts">
				<xsl:sort select="@taskId" data-type="number"/>
				<xsl:with-param name="beginSym" select="$beginSym"/>
				<xsl:with-param name="endSym" select="$endSym"/>
			</xsl:apply-templates>
		<xsl:text>};&#10;</xsl:text>
	</xsl:template>

	<xsl:template match="//*[@taskId]" mode="taskInputPorts">
		<xsl:param name="beginSym"/>
		<xsl:param name="endSym"/>

		<xsl:text>&#9;{&#10;</xsl:text>
		<xsl:text>&#9;&#9;</xsl:text>
		<xsl:value-of select="$beginSym"/><xsl:text>.WaitingList = </xsl:text>
		<xsl:value-of select="$endSym"/>
		<xsl:text>&#10;</xsl:text>
		<xsl:text>&#9;&#9;{&#10;</xsl:text>
		<xsl:text>&#9;&#9;&#9;</xsl:text>
		<xsl:value-of select="$beginSym"/><xsl:text>.SentinelElement = </xsl:text>
		<xsl:value-of select="$endSym"/>
		<xsl:text>{NULL, NULL, </xsl:text>
		<xsl:value-of select="priority/@value"/>
		<xsl:text>}&#10;</xsl:text>
		<xsl:text>&#9;&#9;}&#10;</xsl:text>
		<xsl:text>&#9;},&#10;</xsl:text>
	</xsl:template>

</xsl:stylesheet>

