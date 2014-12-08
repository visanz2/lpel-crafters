<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" 
xmlns:xs="http://www.w3.org/2001/XMLSchema" xmlns:fn="http://www.w3.org/2005/xpath-functions" exclude-result-prefixes="xs fn xsl">
	<!--output format close to xquery-->
	<xsl:import href="../../share/XSLT/id_generation.xslt"/>
	<xsl:output method="text" encoding="utf-8" omit-xml-declaration="yes"/>

	<xsl:template match="/">
		<xsl:call-template name="generateIDs"/>
		<xsl:text>&lt;/node&gt;&#10;</xsl:text>
	</xsl:template>

</xsl:stylesheet>
