<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" 
xmlns:xs="http://www.w3.org/2001/XMLSchema" xmlns:fn="http://www.w3.org/2005/xpath-functions" exclude-result-prefixes="xs fn xsl">
	<!--output format close to xquery-->
	<xsl:output method="text" encoding="utf-8" omit-xml-declaration="no"/>

	<xsl:template name="GenerateFile" match="/">
  		<xsl:param name="outputFile" />
  		<xsl:param name="xsltFile" />
  		<xsl:param name="inputFile" />
  		
  		<xsl:choose>
	  		<xsl:when test="//system/node/hostPlatform/@value='win32'">
	  			<xsl:text>	$(XALAN) -o </xsl:text> <xsl:value-of select="$outputFile"/><xsl:text> </xsl:text><xsl:value-of select="$inputFile"/><xsl:text> </xsl:text><xsl:value-of select="$xsltFile"/> <xsl:text>&#10;</xsl:text>
  			</xsl:when>
  			<xsl:when test="//system/node/hostPlatform/@value='posix32'">
	  			<xsl:text>	$(XALAN) -o </xsl:text> <xsl:value-of select="$outputFile"/><xsl:text> </xsl:text><xsl:value-of select="$inputFile"/><xsl:text> </xsl:text><xsl:value-of select="$xsltFile"/> <xsl:text>&#10;</xsl:text>
  			</xsl:when>
  			<xsl:when test="//system/node/hostPlatform/@value='macosx'">
	  			<xsl:text>	rm -f </xsl:text> <xsl:value-of select="$outputFile"/><xsl:text>&#10;</xsl:text>
	  			<xsl:text>	touch </xsl:text> <xsl:value-of select="$outputFile"/><xsl:text>&#10;</xsl:text>
	  			<xsl:text>	$(XALAN) -o </xsl:text> <xsl:value-of select="$outputFile"/><xsl:text> </xsl:text><xsl:value-of select="$xsltFile"/><xsl:text> </xsl:text><xsl:value-of select="$inputFile"/> <xsl:text>&#10;</xsl:text>
  			</xsl:when>
		</xsl:choose>
	</xsl:template>




	<xsl:template name="genarateMakefile">
		<xsl:text>OCR_PLATFORM_DIR=</xsl:text>
		<xsl:value-of select="//system/@rtosDir"/>

		<xsl:text>&#10;OCR_PLATFORM_NAME=</xsl:text>
		<xsl:value-of select="//system/node/@type"/>

		<xsl:text>&#10;NODE_NAME=</xsl:text>
		<xsl:value-of select="//system/node/@name"/>

		<xsl:text>&#10;NODE_NUM=</xsl:text>
		<xsl:value-of select="//system/node/nodeID/@value"/>

		<xsl:text>&#10;OCR_VARIANT=</xsl:text>
		<xsl:choose>
	  		<xsl:when test="//system/netLink">
				<xsl:text>MP&#10;</xsl:text>
  			</xsl:when>
	  		<xsl:otherwise>
	    			<xsl:text>SP&#10;</xsl:text>
			</xsl:otherwise>
		</xsl:choose>

		<xsl:choose>
	  		<xsl:when test="//system/node/hostPlatform/@value='win32'">
                <xsl:text>CURRENT_DIR=%CD%&#10;</xsl:text>
                <xsl:text>CMAKE_GENERATOR="MinGW Makefiles"&#10;</xsl:text>
                <xsl:text>MKDIR =mkdir&#10;</xsl:text>
                <xsl:text>RMDIR =rmdir /S /Q&#10;</xsl:text>
                <xsl:text>CD    =cd&#10;</xsl:text>
				<xsl:text>CHAIN =&amp;&amp;&#10;</xsl:text>
  			</xsl:when>
	  		<xsl:otherwise>
                <xsl:text>CURRENT_DIR="`pwd`/.."&#10;</xsl:text>
                <xsl:text>CMAKE_GENERATOR="Unix Makefiles"&#10;</xsl:text>
                <xsl:text>MKDIR =mkdir&#10;</xsl:text>
                <xsl:text>RMDIR =rm -rf&#10;</xsl:text>
                <xsl:text>CD    =cd&#10;</xsl:text>
				<xsl:text>CHAIN =;&#10;</xsl:text>
			</xsl:otherwise>
		</xsl:choose>

		<xsl:text>&#10;CMAKE_TOOLCHAIN="</xsl:text>
		<xsl:text>$(CURRENT_DIR)/toolchain/</xsl:text>
		<xsl:value-of select="//system/node/@type"/>
		<xsl:text>.cmake"&#10;</xsl:text>


		<xsl:text>&#10;PROJECT="</xsl:text>
		<xsl:value-of select="//system/node/projectDir/@value"/>
		<xsl:text>/</xsl:text>
		<xsl:value-of select="//system/node/@name"/>
		<xsl:text>/</xsl:text>
		<xsl:value-of select="//system/node/@name"/>
		<xsl:text>.ove"</xsl:text>

		<xsl:choose>
	  		<xsl:when test="//system/node/hostPlatform/@value='win32'">
                       		<xsl:text>&#10;XALAN=$(OCR_PLATFORM_DIR)\bin\Xalan.exe</xsl:text>
  			</xsl:when>
  			<xsl:when test="//system/node/hostPlatform/@value='posix32'">
                       		<xsl:text>&#10;XALAN=$(OCR_PLATFORM_DIR)/bin/Xalan</xsl:text>
  			</xsl:when>
  			<xsl:when test="//system/node/hostPlatform/@value='macosx'">
                       		<xsl:text>&#10;XALAN=xsltproc</xsl:text>
  			</xsl:when>
		</xsl:choose>

		<xsl:if test="//system/node/toolchainDir">
			<xsl:text>&#10;TOOLCHAIN_DIR=</xsl:text>
			<xsl:value-of select="//system/node/toolchainDir/@value"/>
			<xsl:text>\..</xsl:text>
        </xsl:if>

        <!-- Detecting whether or not this Node utilises a Core Support Package, i.e. the attribute `csp' is present. -->
        <xsl:choose>
	        <!-- CSP utilised -->
	        <xsl:when test="//system/node/@csp">
                <!-- Execution Platform specific adjustments of the Path -->
                <xsl:choose>
                    <xsl:when test="//system/node/hostPlatform/@value='win32'">
                        <xsl:text>&#10;XSLT_DIR="$(OCR_PLATFORM_DIR)\$(OCR_PLATFORM_NAME)\XSLT\bsp\</xsl:text>
                        <xsl:value-of select="//system/node/@csp"/>
                        <xsl:text>"</xsl:text>            
                    </xsl:when>
                    <xsl:otherwise>
                        <xsl:text>&#10;XSLT_DIR="$(OCR_PLATFORM_DIR)/$(OCR_PLATFORM_NAME)/XSLT/bsp/</xsl:text>
                        <xsl:value-of select="//system/node/@csp"/>
                        <xsl:text>"</xsl:text>            
                    </xsl:otherwise>
                </xsl:choose>
	        </xsl:when>
	
	        <!-- CSP not utilised (default way)-->
	        <xsl:otherwise>
                <!-- Execution Platform specific adjustments of the Path -->
		        <xsl:choose>
		            <xsl:when test="//system/node/hostPlatform/@value='win32'">
		                            <xsl:text>&#10;XSLT_DIR="$(OCR_PLATFORM_DIR)\$(OCR_PLATFORM_NAME)\XSLT"</xsl:text>
		            </xsl:when>
		            <xsl:otherwise>
		                            <xsl:text>&#10;XSLT_DIR="$(OCR_PLATFORM_DIR)/$(OCR_PLATFORM_NAME)/XSLT"</xsl:text>
		            </xsl:otherwise>
		        </xsl:choose>
	        </xsl:otherwise>
        </xsl:choose>
		

		<xsl:text>&#10;&#10;</xsl:text>
		<xsl:call-template name="platformDefines"/>

		<xsl:text>all: generate build&#10;&#10;</xsl:text>
		<xsl:text>generate: builddir&#10;</xsl:text>

<!--
		<xsl:text>	$(XALAN) -o src/CMakeLists.txt tmp$(NODE_NAME).xml $(XSLT_DIR)/</xsl:text>
		<xsl:text>CMakeLists2.xslt&#10;</xsl:text>
  -->
	
		<xsl:call-template name="GenerateFile">
    		<xsl:with-param name="outputFile">src/CMakeLists.txt</xsl:with-param>
    		<xsl:with-param name="inputFile">tmp$(NODE_NAME).xml</xsl:with-param>
    		<xsl:with-param name="xsltFile">$(XSLT_DIR)/CMakeLists2.xslt</xsl:with-param>
  		</xsl:call-template>

<!--	
		<xsl:text>	$(XALAN) -o CMakeLists.txt tmp$(NODE_NAME).xml $(XSLT_DIR)/</xsl:text>
		<xsl:text>CMakeLists1.xslt&#10;</xsl:text>
  -->
	
		<xsl:call-template name="GenerateFile">
    		<xsl:with-param name="outputFile">CMakeLists.txt</xsl:with-param>
    		<xsl:with-param name="inputFile">tmp$(NODE_NAME).xml</xsl:with-param>
    		<xsl:with-param name="xsltFile">$(XSLT_DIR)/CMakeLists1.xslt</xsl:with-param>
  		</xsl:call-template>
  		
<!--
		<xsl:text>	$(XALAN) -o toolchain/$(OCR_PLATFORM_NAME).cmake tmp$(NODE_NAME).xml $(XSLT_DIR)/</xsl:text>
		<xsl:text>toolchain.xslt&#10;</xsl:text>
  -->
		<xsl:call-template name="GenerateFile">
    		<xsl:with-param name="outputFile">toolchain/$(OCR_PLATFORM_NAME).cmake</xsl:with-param>
    		<xsl:with-param name="inputFile">tmp$(NODE_NAME).xml</xsl:with-param>
    		<xsl:with-param name="xsltFile">$(XSLT_DIR)/toolchain.xslt</xsl:with-param>
  		</xsl:call-template>
	
		<xsl:call-template name="platformSpecificFiles"/>

		<xsl:text>&#10;builddir: src/.dir include/.dir toolchain/.dir ../bin/.dir&#10;&#10;</xsl:text>
		
	
		

		<xsl:text>src/.dir include/.dir toolchain/.dir ../bin/.dir:&#10;</xsl:text>
		<xsl:text>	$(MKDIR) "$(subst /.dir,,$@)"&#10;</xsl:text>
		<xsl:text>	echo > "$@"&#10;&#10;</xsl:text>


		<xsl:text>build: force&#10;</xsl:text>
		<xsl:text>	${RMDIR} Build&#10;</xsl:text>
		<xsl:text>	${MKDIR} Build&#10;</xsl:text>
		<xsl:call-template name="call_cmake"/>
		<xsl:text>${CD} Build ${CHAIN} cmake ../ -G ${CMAKE_GENERATOR} -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN}&#10;</xsl:text>
		<xsl:call-template name="call_cmake"/>
		<xsl:text>${CD} Build ${CHAIN} ${MAKE} all install&#10;&#10;</xsl:text>

		<xsl:call-template name="platformSpecificBuild"/>

		<xsl:text>force:&#10;</xsl:text>
	</xsl:template>

	<xsl:template name="call_cmake">
		<xsl:text>&#9;</xsl:text>
		<xsl:if test="//system/node/compilerEnvironment/@value != ''">
			<xsl:if test="//system/node/environmentDir/@value != ''">
				<xsl:text>${CD} /D </xsl:text>
				<xsl:value-of select="//system/node/environmentDir/@value"/>
				<xsl:text> ${CHAIN} </xsl:text>
			</xsl:if>
			<xsl:value-of select="//system/node/compilerEnvironment/@value"/>
			<xsl:text> ${CHAIN} </xsl:text>
			<xsl:if test="//system/node/environmentDir/@value != ''">
				<xsl:text>${CD} /D $(CURRENT_DIR)</xsl:text>
				<xsl:text> ${CHAIN} </xsl:text>
			</xsl:if>
		</xsl:if>
	</xsl:template>

</xsl:stylesheet>
