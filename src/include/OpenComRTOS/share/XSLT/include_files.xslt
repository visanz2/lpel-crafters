<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0"
    xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:xs="http://www.w3.org/2001/XMLSchema"
    xmlns:fn="http://www.w3.org/2005/xpath-functions"
    exclude-result-prefixes="xs fn xsl">
    <!--output format close to xquery -->
    <xsl:output method="text" encoding="utf-8" omit-xml-declaration="no" />

    <xsl:template name="include_files">
        <xsl:text>#include "L1_node_config.h"&#10;</xsl:text>
        
        <xsl:for-each select="//*/includeFile/@name[not(.=preceding::includeFile/@name)]">
            <!-- Only add the line if the attribute value has content, which is not the case for the Idle-Task. -->
            <xsl:if test=".!=''">
                <xsl:text>#include &lt;</xsl:text><xsl:value-of select="."/><xsl:text>&gt;&#10;</xsl:text>
            </xsl:if>
        </xsl:for-each>
        
    </xsl:template>
</xsl:stylesheet>
