<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" 
xmlns:xs="http://www.w3.org/2001/XMLSchema" xmlns:fn="http://www.w3.org/2005/xpath-functions" exclude-result-prefixes="xs fn xsl">
	<!--output format close to xquery-->
	<xsl:import href="../../share/XSLT/makefile_generator.xslt"/>
	<xsl:output method="text" encoding="utf-8" omit-xml-declaration="no"/>

	<xsl:template match="/">
		<xsl:call-template name="genarateMakefile"/>
	</xsl:template>	

	<xsl:template name="platformSpecificFiles">
		<xsl:text>&#09;$(XALAN) -o ../bin/OpenComRTOS_Node$(NODE_NUM).entities tmp$(NODE_NAME).xml $(XSLT_DIR)/</xsl:text>
		<xsl:text>nodeIDxml.xslt&#10;</xsl:text>
		<xsl:text>&#09;$(XALAN) -o ../include/L1_$(NODE_NAME)_data.h tmp$(NODE_NAME).xml $(XSLT_DIR)/</xsl:text>
		<xsl:text>L1_node_data_H.xslt&#10;</xsl:text>
		<xsl:text>&#09;$(XALAN) -o src/L1_node_config.c tmp$(NODE_NAME).xml $(XSLT_DIR)/</xsl:text>
		<xsl:text>L1_node_config_C.xslt&#10;</xsl:text>
		<xsl:text>&#09;$(XALAN) -o include/L1_node_config.h tmp$(NODE_NAME).xml $(XSLT_DIR)/</xsl:text>
		<xsl:text>L1_node_config_H.xslt&#10;</xsl:text>
		<xsl:text>&#09;$(XALAN) -o include/L1_node_id_mapping.h tmp$(NODE_NAME).xml $(XSLT_DIR)/</xsl:text>
        <xsl:text>L1_node_id_mapping_H.xslt&#10;</xsl:text>
		<xsl:text>&#09;$(XALAN) -o ../bin/$(NODE_NAME).xml tmp$(NODE_NAME).xml $(XSLT_DIR)/</xsl:text>
		<xsl:text>debugger.xslt&#10;</xsl:text>
	</xsl:template>	

	<xsl:template name="platformSpecificBuild">
	</xsl:template>	

	<xsl:template name="platformDefines">
	</xsl:template>	

</xsl:stylesheet>
