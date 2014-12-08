<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" 
xmlns:xs="http://www.w3.org/2001/XMLSchema" xmlns:fn="http://www.w3.org/2005/xpath-functions" exclude-result-prefixes="xs fn xsl">
	<!--output format close to xquery-->
	<xsl:output method="text" encoding="utf-8" omit-xml-declaration="no"/>

	<xsl:template name="debug">
		<xsl:text>#ifdef L1_ALLOW_TRACE&#10;</xsl:text>
		<xsl:choose>
			<xsl:when test="//system/node/traceBufferSize">
				<xsl:text>const int L1_Trace_NumberOfTraceElements=</xsl:text><xsl:value-of select="//system/node/traceBufferSize/@value"/><xsl:text>;&#10;</xsl:text>
				<xsl:text>L1_Trace_TraceBufferElement L1_Trace_TraceBuffer&#91;</xsl:text><xsl:value-of select="//system/node/traceBufferSize/@value"/><xsl:text>&#93;;&#10;</xsl:text>
			</xsl:when>
			<xsl:otherwise>
				<xsl:text>const int L1_Trace_NumberOfTraceElements=1024;&#10;</xsl:text>
				<xsl:text>L1_Trace_TraceBufferElement L1_Trace_TraceBuffer&#91;1024&#93;;&#10;</xsl:text>
			</xsl:otherwise>
		</xsl:choose>
		<xsl:text>#endif /* L1_ALLOW_TRACE */&#10;</xsl:text>
	</xsl:template>

</xsl:stylesheet>

