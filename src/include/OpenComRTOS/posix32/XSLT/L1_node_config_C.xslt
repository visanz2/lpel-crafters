<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" 
xmlns:xs="http://www.w3.org/2001/XMLSchema" xmlns:fn="http://www.w3.org/2005/xpath-functions" exclude-result-prefixes="xs fn xsl">
    <xsl:import href="../../share/XSLT/include_files.xslt"/>
	<xsl:import href="../../share/XSLT/data_structure.xslt"/>
	<xsl:import href="../../share/XSLT/debug.xslt"/>
	<xsl:import href="../../share/XSLT/entities.xslt"/>
	<xsl:import href="../../share/XSLT/kernel_packetpool.xslt"/>
	<xsl:import href="../../share/XSLT/linkPort.xslt"/>
	<xsl:import href="../../share/XSLT/deviceDriver.xslt"/>
	<xsl:import href="../../share/XSLT/preallocated_packets.xslt"/>
	<xsl:import href="../../share/XSLT/routing_table.xslt"/>
	<xsl:import href="../../share/XSLT/task_input_ports.xslt"/>
	<!--output format close to xquery-->
	<xsl:output method="text" encoding="utf-8" omit-xml-declaration="no"/>

	<xsl:template match="/">

		<xsl:call-template name="include_files"/>
		<xsl:text>#include &lt;driver&#47;posix32Timer.h&gt;&#10;</xsl:text>
		<xsl:call-template name="number_of_ISR"/>

		<xsl:apply-templates select="//system/node/deviceDriver/structure"/>
		<xsl:apply-templates select="//system/node/component/structure"/>
		<xsl:apply-templates select="//system/node/deviceDriver/linkPort" mode="generate_structure"/>

		<xsl:text>
L1_Posix32_ISR L1_Posix32_ISRs[NUMBER_OF_ISRS] =
{
	{
		.entryPoint = L1_Posix32_timerThreadProc, 
		.param = NULL 
	},
        </xsl:text>
		<xsl:text>&#10;</xsl:text>
		<xsl:for-each select="//system/node/deviceDriver">
			<xsl:apply-templates select="isr" mode="reference">
				<xsl:with-param name="device" select="."/>
			</xsl:apply-templates>
		</xsl:for-each>
		<xsl:for-each select="//system/node/deviceDriver/linkPort">
			<xsl:apply-templates select="isr" mode="reference">
				<xsl:with-param name="device" select="../."/>
			</xsl:apply-templates>
		</xsl:for-each>
		<xsl:apply-templates select="//system/node/component/isr" mode="value"/>
		<xsl:text>};&#10;&#10;</xsl:text>

		<xsl:apply-templates select="//*[@hubId]" mode="dataStructure">
			<xsl:sort select="@hubId" data-type="number"/>
		</xsl:apply-templates>
        
		<xsl:call-template name="generateTaskInputPorts"/>
		<xsl:call-template name="genaratePreallocatedPackets"/>

		<xsl:call-template name="resourcesList"/>

		<xsl:text>L1_TaskControlRecord L1_TaskControlBlock&#91;L1_NODE_NUMBER_OF_TASKS&#93; =&#10;{&#10;</xsl:text>
			<xsl:apply-templates select="//*[@taskId]" mode="taskControlBlock">
				<xsl:sort select="@taskId" data-type="number"/>
			</xsl:apply-templates>
		<xsl:text>};&#10;</xsl:text>
		
		<xsl:call-template name="generateHubs"/>
		<xsl:call-template name="generateKernelPacketPool"/>
		<xsl:call-template name="debug"/>
		
		<xsl:if test="//system/netLink">
			<xsl:text>&#10;void L1_initLinkDriver(void) {
}

void L1_initializePlatformNodeSockets(void) {&#10;</xsl:text>
			<xsl:call-template name="generatePlatformInitialization"/>
			<xsl:text>}&#10;&#10;</xsl:text>
			<xsl:call-template name="generateRoutingTable"/>
		</xsl:if>
	</xsl:template>

	<xsl:template match="//*[@taskId]"  mode="taskControlBlock">
			<xsl:text>&#9;/*---TASK ID = </xsl:text>
			<xsl:value-of select="@taskId"/>
			<xsl:text> */&#10;</xsl:text>
			<xsl:text>&#9;{&#10;</xsl:text>
			<xsl:text>&#9;&#9;.ListElement = {NULL,NULL,</xsl:text><xsl:value-of select="priority/@value"/>
			<xsl:text>},     /* ListElement */&#10;</xsl:text>
			<xsl:text>&#9;&#9;.TaskID      = ((</xsl:text><xsl:value-of select="@taskId"/>
			<xsl:text> &lt;&lt; 0) | (L1_PRESENT_NODE_ID &lt;&lt; L1_NODE_ID_SIZE)), /* TaskID; */&#10;</xsl:text>
			<xsl:text>&#9;&#9;.EntryPoint  = </xsl:text>
			<xsl:value-of select="entrypoint/@value"/><xsl:text>,     /* entrypoint */&#10;</xsl:text>
			<xsl:text>&#9;&#9;.Arguments   = (L1_TaskArguments)</xsl:text><xsl:value-of select="arguments/@value"/>
			<xsl:text>, /* arguments */&#10;</xsl:text>
			<xsl:text>&#9;&#9;.TaskState   = </xsl:text>
			<xsl:value-of select="status/@value"/><xsl:text>,     /* status */&#10;</xsl:text>
			<xsl:text>#ifdef L1_PRIO_INHERITANCE&#10;</xsl:text>
			<xsl:text>&#9;&#9;.CriticalSectionWaitingList =&#10;</xsl:text>
			<xsl:text>&#9;&#9;{&#10;</xsl:text>
			<xsl:text>&#9;&#9;&#9;.SentinelElement = {NULL,NULL,255}, /* CriticalSectionWaitingList */&#10;</xsl:text>
			<xsl:text>&#9;&#9;},&#10;</xsl:text>
			<xsl:text>&#9;&#9;.IntrinsicPriority = </xsl:text>
			<xsl:value-of select="priority/@value"/><xsl:text>,     /* IntrinsicPriority */&#10;</xsl:text>
			<xsl:text>#endif /* L1_PRIO_INHERITANCE */&#10;&#9;&#9;.isSuspended   = L1_FALSE,                        /* isSuspended */&#10;</xsl:text>
			<xsl:text>&#9;&#9;.TaskInputPort = &amp;L1_TaskInputPorts&#91;</xsl:text><xsl:value-of select="@taskId"/>
			<xsl:text>&#93;,                 /* TaskInputPort */&#10;</xsl:text>
			<xsl:text>&#9;&#9;.RequestPacket = &amp;PreallocatedPackets&#91;</xsl:text><xsl:value-of select="@taskId"/>
			<xsl:text>&#93;,          /* RequestPacket */&#10;</xsl:text>
			<xsl:text>&#9;&#9;.Context       = NULL&#10;</xsl:text>
			<xsl:text>&#9;},&#10;</xsl:text>
	</xsl:template>

	<xsl:template name="include_information">
		<xsl:text>#include "L1_node_config.h"&#10;</xsl:text>
		<xsl:text>#include &lt;stdio.h&gt;&#10;</xsl:text>
		<xsl:text>#include &lt;driver/posix32Timer.h&gt;&#10;&#10;</xsl:text>

		<xsl:for-each select="//system/node/deviceDriver/includeFile/@name[not(.=preceding::includeFile/@name)]">
			<xsl:text>#include &lt;</xsl:text><xsl:value-of select="."/><xsl:text>&gt;&#10;</xsl:text>
		</xsl:for-each>
		
		<xsl:for-each select="//system/node/deviceDriver/linkPort/includeFile/@name[not(.=preceding::includeFile/@name)]">
			<xsl:text>#include &lt;</xsl:text><xsl:value-of select="."/><xsl:text>&gt;&#10;</xsl:text>
		</xsl:for-each>

		<xsl:for-each select="//system/node/component/includeFile/@name[not(.=preceding::includeFile/@name)]">
			<xsl:text>#include &lt;</xsl:text><xsl:value-of select="."/><xsl:text>&gt;&#10;</xsl:text>
		</xsl:for-each>
	</xsl:template>

 	
	<xsl:template name="number_of_ISR">
		<xsl:text>&#10;&#10;</xsl:text>
		<xsl:text>#define NUMBER_OF_ISRS  (1</xsl:text>
		<xsl:if test="//system/node/deviceDriver/linkPort/isr">
			<xsl:text> + </xsl:text>
			<xsl:value-of select="count(//system/node/deviceDriver/linkPort/isr)"/>
		</xsl:if>
		<xsl:if test="//system/node/deviceDriver/isr">
			<xsl:text> + </xsl:text>
			<xsl:value-of select="count(//system/node/deviceDriver/isr)"/>
		</xsl:if>
		<xsl:if test="//system/node/driver/isr">
			<xsl:text> + </xsl:text>
			<xsl:value-of select="count(//system/node/driver/isr)"/>
		</xsl:if>
		<xsl:if test="//system/node/component/isr">
			<xsl:text> + </xsl:text>
			<xsl:value-of select="count(//system/node/component/isr)"/>
		</xsl:if>
		<xsl:text>)&#10;</xsl:text>
		<xsl:text>
L1_UINT32 L1_Posix32_NbrOfIsrs = NUMBER_OF_ISRS;
/*
 * The size of the array is `NUMBER_OF_ISRS + 1' because the last entry is used
 * to store the handle of the current task!
 */
//HANDLE threadSuspendEvents[NUMBER_OF_ISRS + 1];</xsl:text>
		<xsl:text>&#10;&#10;</xsl:text>
	</xsl:template>

	<xsl:template match="isr" mode="reference">
		<xsl:param name="device" select="''"/>

		<xsl:text>&#9;{&#10;</xsl:text>
		<xsl:text>&#9;&#9;.entryPoint = </xsl:text>
		<xsl:value-of select="@name"/><xsl:text>,&#10;</xsl:text>
		<xsl:text>&#9;&#9;.param = &amp;</xsl:text>
		<xsl:value-of select="../structure/@type"/>
		<xsl:if test="$device!=''">
			<xsl:text>_</xsl:text><xsl:value-of select="$device/@name"/>
		</xsl:if>
		<xsl:text>_</xsl:text><xsl:value-of select="../@name"/>
		<xsl:text>_</xsl:text><xsl:value-of select="arguments/@reference"/>
		<xsl:text>&#10;&#9;},&#10;</xsl:text>
	</xsl:template>

	<xsl:template match="isr" mode="value">
		<xsl:text>&#9;{&#10;</xsl:text>
		<xsl:text>&#9;&#9;.entryPoint = </xsl:text>
		<xsl:value-of select="@name"/><xsl:text>,&#10;</xsl:text>
		<xsl:text>&#9;&#9;.param = (L1_TaskArguments)</xsl:text>
		<xsl:value-of select="arguments/@value"/>
		<xsl:text>&#10;&#9;},&#10;</xsl:text>
	</xsl:template>

	<xsl:template name="platform_exit">
		<xsl:text>exit(-1);</xsl:text>
	</xsl:template>

	<xsl:template name="platform_name">
	</xsl:template>
	
	<xsl:template name="core_name">
	</xsl:template>

</xsl:stylesheet>

