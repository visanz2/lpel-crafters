<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:xs="http://www.w3.org/2001/XMLSchema"
	xmlns:fn="http://www.w3.org/2005/xpath-functions"
	exclude-result-prefixes="xs fn xsl">
	<!--output format close to xquery -->
	<xsl:import href="../../share/XSLT/entity_names_to_ids.xslt" />
	<xsl:output method="text" encoding="utf-8"
		omit-xml-declaration="no" />

	<xsl:template match="/">
        <xsl:text>#ifndef NODE_ID_MAPPING&#10;</xsl:text>
        <xsl:text>#define NODE_ID_MAPPING&#10;</xsl:text>
        <xsl:text>&#10;</xsl:text>
        <xsl:text>#include &lt;L1_types.h&gt;&#10;</xsl:text>
        <xsl:text>#include &lt;L1_nodes_data.h&gt;&#10;</xsl:text>
        <xsl:text>#include &lt;L1_node_config.h&gt;&#10;</xsl:text>
		<xsl:call-template name="EntityNamesToIds" />
        <xsl:text>&#10;#endif /* NODE_ID_MAPPING */&#10;</xsl:text>
	</xsl:template>
</xsl:stylesheet>
