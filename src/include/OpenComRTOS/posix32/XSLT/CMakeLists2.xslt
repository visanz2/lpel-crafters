<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" 
xmlns:xs="http://www.w3.org/2001/XMLSchema" xmlns:fn="http://www.w3.org/2005/xpath-functions" exclude-result-prefixes="xs fn xsl">
    <!--output format close to xquery-->
    <xsl:import href="../../share/XSLT/srcCMakeLists.xslt"/>
    <xsl:output method="text" encoding="utf-8" omit-xml-declaration="no"/>

    <xsl:template match="/">
        <xsl:text># Configure an Executable, `</xsl:text><xsl:value-of select="//system/node/@name"/>
        <xsl:text>' is the name of the executable without any extensions.
ADD_EXECUTABLE(</xsl:text><xsl:value-of select="//system/node/@name"/><xsl:text>
    L1_node_config.c&#10;</xsl:text>
        <xsl:call-template name="node_sourceFile"/>
        <xsl:call-template name="task_sourceFile"/>
        <xsl:text>)
# Forcing the compiler and linker to generate 32bit binaries.
set_target_properties(</xsl:text><xsl:value-of select="//system/node/@name"/><xsl:text> PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")

#Where to install the generated target
INSTALL(TARGETS </xsl:text><xsl:value-of select="//system/node/@name"/><xsl:text> RUNTIME DESTINATION bin)</xsl:text>
    </xsl:template>
</xsl:stylesheet>
