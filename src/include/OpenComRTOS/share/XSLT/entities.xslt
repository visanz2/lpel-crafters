<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0"
    xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:xs="http://www.w3.org/2001/XMLSchema"
    xmlns:fn="http://www.w3.org/2005/xpath-functions"
    exclude-result-prefixes="xs fn xsl">
    <!--output format close to xquery -->
    <xsl:output method="text" encoding="utf-8"
        omit-xml-declaration="no" />

    <xsl:template name="resourcesList">
        <xsl:text>#ifdef L1_PRIO_INHERITANCE&#10;&#10;</xsl:text>
        <xsl:text>#define NUMBER_OF_USED_RESOURCES </xsl:text>
        <xsl:value-of select="//system/node/resourceNumbers/@value" />
        <xsl:text>&#10;</xsl:text>

        <xsl:if test="//system/node/@type!='xmos'">
            <xsl:text>L1_UINT32 </xsl:text>
        </xsl:if>

        <xsl:text>L1_</xsl:text><xsl:call-template name="platform_name"/><xsl:text>NumberOfUsedResources = NUMBER_OF_USED_RESOURCES;&#10;</xsl:text>
        <xsl:text>L1_KeyedListElement L1_</xsl:text><xsl:call-template name="platform_name"/>
        <xsl:if test="//system/node/@type='xmos'">
            <xsl:text>XMOS_</xsl:text>
        </xsl:if>
        <xsl:text>KeyListElements[NUMBER_OF_USED_RESOURCES];&#10;&#10;</xsl:text>
        <xsl:if test="//system/node/@type='xmos'">
            <xsl:text>L1_KeyListElements = L1_XMOS_KeyListElements;&#10;&#10;</xsl:text>
        </xsl:if>

        <xsl:text>#endif /* L1_PRIO_INHERITANCE */&#10;</xsl:text>
    </xsl:template>

    <xsl:template name="generateHubs">
        <xsl:param name="beginSym" />
        <xsl:param name="endSym" />

        <xsl:text>&#10;</xsl:text>
        <xsl:apply-templates select="//*[@hubId]" mode="hubStateStructure">
            <xsl:sort select="@hubId" data-type="number" />
            <xsl:with-param name="beginSym" select="$beginSym" />
            <xsl:with-param name="endSym" select="$endSym" />
        </xsl:apply-templates>
        
        <xsl:text>&#10;L1_Hub L1_</xsl:text>
        <xsl:call-template name="platform_name" />
        <xsl:text>LocalHubs&#91;L1_NODE_NUMBER_OF_HUBS&#93; =&#10;{&#10;</xsl:text>
        <xsl:apply-templates select="//*[@hubId]" mode="entities">
            <xsl:sort select="@hubId" data-type="number" />
            <xsl:with-param name="beginSym" select="$beginSym" />
            <xsl:with-param name="endSym" select="$endSym" />
        </xsl:apply-templates>
        <xsl:text>};&#10;</xsl:text>
    </xsl:template>
    <!--  "//*[@hubId]" triggers on any element with the attribute `hubId' being present -->
    <xsl:template match="//*[@hubId]" mode="hubStateStructure">
        <xsl:param name="beginSym" />
        <xsl:param name="endSym" />
        
        <!--  Debugging aid: <xsl:value-of select="local-name()"/> -->
        
        <xsl:if test="local-name()!='port'">
            <xsl:if test="local-name()!='hub'">
                <xsl:choose>
                    <xsl:when test="local-name()='event'">
                        <xsl:text>L1_Event</xsl:text>
                    </xsl:when>
                    <xsl:when test="local-name()='dataEvent'">
                        <xsl:text>L1_DataEvent</xsl:text>
                    </xsl:when>
                    <xsl:when test="local-name()='semaphore'">
                        <xsl:text>L1_Semaphore</xsl:text>
                    </xsl:when>
                    <xsl:when test="local-name()='resource'">
                        <xsl:text>L1_Resource</xsl:text>
                    </xsl:when>
                    <xsl:when test="local-name()='fifo'">
                        <xsl:text>L1_Fifo</xsl:text>
                    </xsl:when>
                    <xsl:when test="local-name()='memoryPool'">
                        <xsl:text>L1_MemoryPool</xsl:text>
                    </xsl:when>
                    <xsl:when test="local-name()='packetPool'">
                        <xsl:text>L1_PacketPool</xsl:text>
                    </xsl:when>
                    <xsl:when test="local-name()='blackBoard'">
                        <xsl:text>L1_BlackBoard</xsl:text>
                    </xsl:when>
                </xsl:choose>

                <xsl:text>_HubState </xsl:text>
                <xsl:value-of select="@name" />
                <xsl:text>_HubState =&#10;{&#10;</xsl:text>
                <xsl:choose>
                    <xsl:when test="local-name()='event'">
                        <xsl:text>&#9;</xsl:text>
                        <xsl:value-of select="$beginSym" />
                        <xsl:text>.isSet = </xsl:text>
                        <xsl:value-of select="$endSym" />
                        <xsl:text>L1_FALSE,&#10;</xsl:text>
                    </xsl:when>
                    <xsl:when test="local-name()='dataEvent'">
                        <xsl:text>&#9;</xsl:text>
                        <xsl:value-of select="$beginSym" />
                        <xsl:text>.isSet = </xsl:text>
                        <xsl:value-of select="$endSym" />
                        <xsl:text>L1_FALSE,&#10;</xsl:text>
                    </xsl:when>
                    <xsl:when test="local-name()='semaphore'">
                        <xsl:text>&#9;</xsl:text>
                        <xsl:value-of select="$beginSym" />
                        <xsl:text>.Count = </xsl:text>
                        <xsl:value-of select="$endSym" />
                        <xsl:text>0,&#10;</xsl:text>
                    </xsl:when>
                    <xsl:when test="local-name()='resource'">
                        <xsl:text>&#9;</xsl:text>
                        <xsl:value-of select="$beginSym" />
                        <xsl:text>.Locked = </xsl:text>
                        <xsl:value-of select="$endSym" />
                        <xsl:text>L1_FALSE,&#10;</xsl:text>
                        <xsl:text>&#9;</xsl:text>
                        <xsl:value-of select="$beginSym" />
                        <xsl:text>.OwningTaskID = </xsl:text>
                        <xsl:value-of select="$endSym" />
                        <xsl:text>0,&#10;</xsl:text>
                        <xsl:text>#ifdef L1_PRIO_INHERITANCE&#10;</xsl:text>
                        <xsl:text>&#9;</xsl:text>
                        <xsl:value-of select="$beginSym" />
                        <xsl:text>.OwnerBoostedToPriority = </xsl:text>
                        <xsl:value-of select="$endSym" />
                        <xsl:text>255,&#10;</xsl:text>
                        <xsl:text>&#9;</xsl:text>
                        <xsl:value-of select="$beginSym" />
                        <xsl:text>.CeilingPriority = </xsl:text>
                        <xsl:value-of select="$endSym" />
                        <xsl:value-of select="ceilingPriority/@value" />
                        <xsl:text>,&#10;</xsl:text>
                        <xsl:text>#endif /* L1_PRIO_INHERITANCE */&#10;</xsl:text>
                    </xsl:when>
                    <xsl:when test="local-name()='fifo'">
                        <xsl:text>&#9;</xsl:text>
                        <xsl:value-of select="$beginSym" />
                        <xsl:text>.Size = </xsl:text>
                        <xsl:value-of select="$endSym" />
                        <xsl:value-of select="size/@value" />
                        <xsl:text>,&#10;</xsl:text>
                        <xsl:text>&#9;</xsl:text>
                        <xsl:value-of select="$beginSym" />
                        <xsl:text>.Count = </xsl:text>
                        <xsl:value-of select="$endSym" />
                        <xsl:text>0,&#10;</xsl:text>
                        <xsl:text>&#9;</xsl:text>
                        <xsl:value-of select="$beginSym" />
                        <xsl:text>.Head = </xsl:text>
                        <xsl:value-of select="$endSym" />
                        <xsl:text>0,&#10;</xsl:text>
                        <xsl:text>&#9;</xsl:text>
                        <xsl:value-of select="$beginSym" />
                        <xsl:text>.Buffer = </xsl:text>
                        <xsl:value-of select="$endSym" />
                        <xsl:text>FIFO_</xsl:text>
                        <xsl:value-of select="@name" />
                        <xsl:text>_Data,&#10;</xsl:text>
                    </xsl:when>
                    <xsl:when test="local-name()='memoryPool'">
                        <xsl:text>&#9;</xsl:text>
                        <xsl:value-of select="$beginSym" />
                        <xsl:text>.NumberOfBlocks = </xsl:text>
                        <xsl:value-of select="$endSym" />
                        <xsl:value-of select="numOfBlocks/@value" />
                        <xsl:text>,&#10;</xsl:text>
                        <xsl:text>&#9;</xsl:text>
                        <xsl:value-of select="$beginSym" />
                        <xsl:text>.BlockSize = </xsl:text>
                        <xsl:value-of select="$endSym" />
                        <xsl:value-of select="sizeOfBlocks/@value" />
                        <xsl:text>,&#10;</xsl:text>
                        <xsl:text>&#9;</xsl:text>
                        <xsl:value-of select="$beginSym" />
                        <xsl:text>.MemoryBlockPool = </xsl:text>
                        <xsl:value-of select="$endSym" />
                        <xsl:text>MemoryPool_</xsl:text>
                        <xsl:value-of select="@name" />
                        <xsl:text>_MemoryBlocks,&#10;</xsl:text>
                        <xsl:text>&#9;</xsl:text>
                        <xsl:value-of select="$beginSym" />
                        <xsl:text>.FreeMemoryBlockList = </xsl:text>
                        <xsl:value-of select="$endSym" />
                        <xsl:text>{ .SentinelElement = {NULL, NULL, 1} },&#10;</xsl:text>
                        <xsl:text>&#9;</xsl:text>
                        <xsl:value-of select="$beginSym" />
                        <xsl:text>.OccupiedMemoryBlockList = </xsl:text>
                        <xsl:value-of select="$endSym" />
                        <xsl:text>{ .SentinelElement = {NULL, NULL, 1} },&#10;</xsl:text>
                    </xsl:when>
                    <xsl:when test="local-name()='packetPool'">
                        <xsl:text>&#9;</xsl:text>
                        <xsl:value-of select="$beginSym" />
                        <xsl:text>.Size = </xsl:text>
                        <xsl:value-of select="$endSym" />
                        <xsl:value-of select="size/@value" />
                        <xsl:text>,&#10;</xsl:text>
                        <xsl:text>#ifdef L1_OSI&#10;</xsl:text>
                        <xsl:text>&#9;</xsl:text>
                        <xsl:value-of select="$beginSym" />
                        <xsl:text>.maxUtilisation = </xsl:text>
                        <xsl:value-of select="$endSym" />
                        <xsl:text>0,&#10;</xsl:text>
                        <xsl:text>&#9;</xsl:text>
                        <xsl:value-of select="$beginSym" />
                        <xsl:text>.currentUtilisation = </xsl:text>
                        <xsl:value-of select="$endSym" />
                        <xsl:text>0,&#10;</xsl:text>
                        <xsl:text>#endif /* L1_OSI */&#10;</xsl:text>
                        <xsl:text>&#9;</xsl:text>
                        <xsl:value-of select="$beginSym" />
                        <xsl:text>.PacketPool = </xsl:text>
                        <xsl:value-of select="$endSym" />
                        <xsl:text>(L1_Packet*) PacketPool_</xsl:text>
                        <xsl:value-of select="@name" />
                        <xsl:text>_Data,&#10;</xsl:text>
                    </xsl:when>
                    <xsl:when test="local-name()='blackBoard'">
                        <xsl:text>&#9;</xsl:text>
                        <xsl:value-of select="$beginSym" />
                        <xsl:text>.board = </xsl:text>
                        <xsl:value-of select="$endSym" />
                        <xsl:text>{ .messageNumber = 0 },&#10;</xsl:text>
                        <xsl:text>&#9;</xsl:text>
                        <xsl:value-of select="$beginSym" />
                        <xsl:text>.dataSize = </xsl:text>
                        <xsl:value-of select="$endSym" />
                        <xsl:text>0,&#10;</xsl:text>
                        <xsl:text>&#9;</xsl:text>
                        <xsl:value-of select="$beginSym" />
                        <xsl:text>.messageNumber = </xsl:text>
                        <xsl:value-of select="$endSym" />
                        <xsl:text>0,&#10;</xsl:text>
                    </xsl:when>
                </xsl:choose>
                <xsl:text>};&#10;&#10;</xsl:text>
            </xsl:if>
            <!-- Here comes the handling code for the <hub> element -->
            <xsl:if test="local-name()='hub'">
                <!--  Call the template defined in the bottom with match="*/structure" -->
               <xsl:apply-templates select="hubState/structure" mode="structure"/>
            </xsl:if>
            
            
        </xsl:if>
    </xsl:template>

    <xsl:template match="//*[@hubId]" mode="entities">
        <xsl:param name="beginSym" />
        <xsl:param name="endSym" />

        <xsl:text>&#9;/* </xsl:text>
        <xsl:value-of select="local-name()" />
        <xsl:text> NAME = </xsl:text>
        <xsl:value-of select="@name" />
        <xsl:text> */&#10;</xsl:text>
        <xsl:text>&#9;{&#10;</xsl:text>
        <xsl:text>&#9;&#9;</xsl:text>
        <xsl:value-of select="$beginSym" />
        <xsl:text>.WaitingList = </xsl:text>
        <xsl:value-of select="$endSym" />
        <xsl:text>&#10;</xsl:text>
        <xsl:text>&#9;&#9;{&#10;</xsl:text>
        <xsl:text>&#9;&#9;&#9;</xsl:text>
        <xsl:value-of select="$beginSym" />
        <xsl:text>.SentinelElement = </xsl:text>
        <xsl:value-of select="$endSym" />
        <xsl:text>{ NULL, NULL, 255 }, /* WaitingList */&#10;</xsl:text>
        <xsl:text>&#9;&#9;},&#10;</xsl:text>
    
        <!--HubType -->
        <xsl:if test="local-name()!='hub'">      
            <xsl:text>&#9;&#9;</xsl:text>
            <xsl:value-of select="$beginSym" />
            <xsl:text>.HubType = </xsl:text>
            <xsl:value-of select="$endSym" />
            <xsl:call-template name="hubType">
                <xsl:with-param name="entity" select="local-name()" />
            </xsl:call-template>
        </xsl:if>
        <xsl:if test="local-name()='hub'">      
            <xsl:text>&#9;&#9;</xsl:text>
            <xsl:value-of select="$beginSym" />
            <xsl:text>.HubType = </xsl:text>
            <xsl:value-of select="$endSym" />
            <xsl:value-of select="localHubEntry/hubType/@value" />
        </xsl:if>
        <xsl:text>, /* HubType */&#10;</xsl:text>

        <!--HubStateUpdateFunctions -->
        <xsl:if test="local-name()!='hub'">        
            <xsl:call-template name="hubStateUpdateFunction">
                <xsl:with-param name="entity" select="local-name()" />
                <xsl:with-param name="beginSym" select="$beginSym" />
                <xsl:with-param name="endSym" select="$endSym" />
            </xsl:call-template>
        </xsl:if>
        <xsl:if test="local-name()='hub'">      
            <xsl:text>&#9;&#9;</xsl:text>
            <xsl:value-of select="$beginSym" />
            <xsl:text>.HubUpdateFunction = </xsl:text>
            <xsl:value-of select="$endSym" />
            <!-- This extracts the value of the attribute `value' in element localHubEntry->updateFunctions. -->
            <xsl:value-of select="localHubEntry/updateFunction/@name" />
            <xsl:text>, /* HubStateUpdateFunctions */&#10;</xsl:text>
        </xsl:if>
        
        
        <xsl:if test="local-name()!='hub'">      
            <xsl:text>&#9;&#9;</xsl:text>
            <xsl:value-of select="$beginSym" />
            <xsl:text>.HubSyncConditionFunction = </xsl:text>
            <xsl:value-of select="$endSym" />
            <!--HubSyncConditionFunction -->
            <xsl:call-template name="hubSyncConditionFunction">
                <xsl:with-param name="entity" select="local-name()" />
            </xsl:call-template>
            <xsl:text>, /* HubSyncConditionFunction */&#10;</xsl:text>
        </xsl:if>

        <xsl:if test="local-name()='hub'">      
            <xsl:text>&#9;&#9;</xsl:text>
            <xsl:value-of select="$beginSym" />
            <xsl:text>.HubSyncConditionFunction = </xsl:text>
            <xsl:value-of select="$endSym" />
            <xsl:value-of select="localHubEntry/synchronizeFunction/@name" />
            <xsl:text>, /* HubSyncConditionFunction */&#10;</xsl:text>
        </xsl:if>


        <xsl:if test="local-name()!='hub'">      
	        <xsl:text>&#9;&#9;</xsl:text>
	        <xsl:value-of select="$beginSym" />
	        <xsl:text>.HubControlFunction = </xsl:text>
	        <xsl:value-of select="$endSym" />
	        <!--HubControlFunction -->
	        <xsl:call-template name="hubControlFunction">
	            <xsl:with-param name="entity" select="local-name()" />
	        </xsl:call-template>
	        <xsl:text>, /* HubControlFunction */&#10;</xsl:text>
        </xsl:if>
        
        <xsl:if test="local-name()='hub'">      
            <xsl:text>&#9;&#9;</xsl:text>
            <xsl:value-of select="$beginSym" />
            <xsl:text>.HubControlFunction = </xsl:text>
            <xsl:value-of select="$endSym" />
            <xsl:value-of select="localHubEntry/controlFunction/@name" />
            <xsl:text>, /* HubControlFunction */&#10;</xsl:text>
        </xsl:if>
        
        
        
        <xsl:if test="local-name()!='hub'">      
	        <xsl:text>&#9;&#9;</xsl:text>
	        <xsl:value-of select="$beginSym" />
	        <xsl:text>.HubState = </xsl:text>
	        <xsl:value-of select="$endSym" />
	        <xsl:choose>
	            <xsl:when test="local-name()='port'">
	                <xsl:text>NULL&#10;</xsl:text>
	            </xsl:when>
	            <xsl:otherwise>
	                <xsl:text>(void*) &amp;</xsl:text>
	                <xsl:value-of select="@name" />
	                <xsl:text>_HubState&#10;</xsl:text>
	            </xsl:otherwise>
	        </xsl:choose>
        </xsl:if>
        
        <xsl:if test="local-name()='hub'">      
            <xsl:text>&#9;&#9;</xsl:text>
            <xsl:value-of select="$beginSym" />
            <xsl:text>.HubState = (void*) </xsl:text>
            <xsl:value-of select="$endSym" />
            <xsl:value-of select="localHubEntry/state/@value" />
            <xsl:text>, /* HubState */&#10;</xsl:text>
        </xsl:if>
        
        <xsl:text>&#9;}, /* L1 </xsl:text>
        <xsl:value-of select="local-name()" />
        <xsl:text> */&#10;</xsl:text>
    </xsl:template>

    <xsl:template name="hubType">
        <xsl:param name="entity" />

        <xsl:choose>
            <xsl:when test="$entity='port'">
                <xsl:text>L1_PORT</xsl:text>
            </xsl:when>
            <xsl:when test="$entity='event'">
                <xsl:text>L1_EVENT</xsl:text>
            </xsl:when>
            <xsl:when test="$entity='dataEvent'">
                <xsl:text>L1_DATAEVENT</xsl:text>
            </xsl:when>
            <xsl:when test="$entity='semaphore'">
                <xsl:text>L1_SEMAPHORE</xsl:text>
            </xsl:when>
            <xsl:when test="$entity='resource'">
                <xsl:text>L1_RESOURCE</xsl:text>
            </xsl:when>
            <xsl:when test="$entity='fifo'">
                <xsl:text>L1_FIFO</xsl:text>
            </xsl:when>
            <xsl:when test="$entity='memoryPool'">
                <xsl:text>L1_MEMORYPOOL</xsl:text>
            </xsl:when>
            <xsl:when test="$entity='packetPool'">
                <xsl:text>L1_PACKETPOOL</xsl:text>
            </xsl:when>
            <xsl:when test="$entity='blackBoard'">
                <xsl:text>L1_BLACKBOARD</xsl:text>
            </xsl:when>
        </xsl:choose>
    </xsl:template>

    <xsl:template name="hubStateUpdateFunction">
        <xsl:param name="entity" />
        <xsl:param name="beginSym" />
        <xsl:param name="endSym" />

        <xsl:choose>
            <xsl:when test="$entity='port'">
                <xsl:text>#ifdef L1_DEBUG&#10;</xsl:text>
                <xsl:text>&#9;&#9;</xsl:text>
                <xsl:value-of select="$beginSym" />
                <xsl:text>.HubUpdateFunction = </xsl:text>
                <xsl:value-of select="$endSym" />
                <xsl:text>LocalPortUpdate, /* HubStateUpdateFunctions */&#10;</xsl:text>
                <xsl:text>#else&#10;</xsl:text>
                <xsl:text>&#9;&#9;</xsl:text>
                <xsl:value-of select="$beginSym" />
                <xsl:text>.HubUpdateFunction = </xsl:text>
                <xsl:value-of select="$endSym" />
                <xsl:text>NULL, /* HubStateUpdateFunctions */&#10;</xsl:text>
                <xsl:text>#endif /* L1_DEBUG */&#10;</xsl:text>
            </xsl:when>
            <xsl:otherwise>
                <xsl:text>&#9;&#9;</xsl:text>
                <xsl:value-of select="$beginSym" />
                <xsl:text>.HubUpdateFunction = </xsl:text>
                <xsl:value-of select="$endSym" />
                <xsl:choose>
                    <xsl:when test="$entity='event'">
                        <xsl:text>EventUpdate</xsl:text>
                    </xsl:when>
                    <xsl:when test="$entity='dataEvent'">
                        <xsl:text>DataEventHub_Update</xsl:text>
                    </xsl:when>
                    <xsl:when test="$entity='semaphore'">
                        <xsl:text>SemaphoreUpdate</xsl:text>
                    </xsl:when>
                    <xsl:when test="$entity='resource'">
                        <xsl:text>ResourceUpdate</xsl:text>
                    </xsl:when>
                    <xsl:when test="$entity='fifo'">
                        <xsl:text>FifoUpdate</xsl:text>
                    </xsl:when>
                    <xsl:when test="$entity='memoryPool'">
                        <xsl:text>MemoryPoolUpdate</xsl:text>
                    </xsl:when>
                    <xsl:when test="$entity='packetPool'">
                        <xsl:text>PacketPoolUpdate</xsl:text>
                    </xsl:when>
                    <xsl:when test="$entity='blackBoard'">
                        <xsl:text>BlackBoardHub_Update</xsl:text>
                    </xsl:when>
                </xsl:choose>
                <xsl:text>, /* HubStateUpdateFunctions */&#10;</xsl:text>
            </xsl:otherwise>
        </xsl:choose>
    </xsl:template>

    <xsl:template name="hubSyncConditionFunction">
        <xsl:param name="entity" />

        <xsl:choose>
            <xsl:when test="$entity='port'">
                <xsl:text>LocalPortSyncCondition</xsl:text>
            </xsl:when>
            <xsl:when test="$entity='event'">
                <xsl:text>EventSyncCondition</xsl:text>
            </xsl:when>
            <xsl:when test="$entity='dataEvent'">
                <xsl:text>DataEventHub_SyncCondition</xsl:text>
            </xsl:when>
            <xsl:when test="$entity='semaphore'">
                <xsl:text>SemaphoreSyncCondition</xsl:text>
            </xsl:when>
            <xsl:when test="$entity='resource'">
                <xsl:text>ResourceSyncCondition</xsl:text>
            </xsl:when>
            <xsl:when test="$entity='fifo'">
                <xsl:text>FifoSyncCondition</xsl:text>
            </xsl:when>
            <xsl:when test="$entity='memoryPool'">
                <xsl:text>MemoryPoolSyncCondition</xsl:text>
            </xsl:when>
            <xsl:when test="$entity='packetPool'">
                <xsl:text>PacketPoolSyncCondition</xsl:text>
            </xsl:when>
            <xsl:when test="$entity='blackBoard'">
                <xsl:text>BlackBoardHub_SyncCondition</xsl:text>
            </xsl:when>
        </xsl:choose>
    </xsl:template>

    <xsl:template name="hubControlFunction">
        <xsl:param name="entity" />

        <xsl:choose>
            <xsl:when test="$entity='port'">
                <xsl:text>NULL</xsl:text>
            </xsl:when>
            <xsl:when test="$entity='event'">
                <xsl:text>NULL</xsl:text>
            </xsl:when>
            <xsl:when test="$entity='dataEvent'">
                <xsl:text>DataEventHub_Ioctl</xsl:text>
            </xsl:when>
            <xsl:when test="$entity='semaphore'">
                <xsl:text>NULL</xsl:text>
            </xsl:when>
            <xsl:when test="$entity='resource'">
                <xsl:text>NULL</xsl:text>
            </xsl:when>
            <xsl:when test="$entity='fifo'">
                <xsl:text>NULL</xsl:text>
            </xsl:when>
            <xsl:when test="$entity='memoryPool'">
                <xsl:text>MemoryPoolIoctl</xsl:text>
            </xsl:when>
            <xsl:when test="$entity='packetPool'">
                <xsl:text>PacketPoolIoctl</xsl:text>
            </xsl:when>
            <xsl:when test="$entity='blackBoard'">
                <xsl:text>NULL</xsl:text>
            </xsl:when>
        </xsl:choose>
    </xsl:template>



    <xsl:template match="array">
        <xsl:value-of select="@type"/><xsl:text> </xsl:text>
        <xsl:value-of select="@name"/>
        <xsl:text>[</xsl:text>
        <xsl:value-of select="@nbrOfElements"/>
        <xsl:text>];&#10;&#10;</xsl:text>
    </xsl:template>


    <xsl:template match="*/structure" mode="structure">
        <xsl:value-of select="@type"/><xsl:text> </xsl:text>
        <xsl:value-of select="@name"/>
        <xsl:choose>
            <xsl:when test="field">
                <xsl:text> =&#10;</xsl:text>
                <xsl:text>{&#10;</xsl:text>
                <!-- Iterating over all fields of the structure. -->
                <xsl:for-each select="field">
                  <xsl:choose>
                    <xsl:when test="@type='string'">
                        <xsl:text>&#9;.</xsl:text><xsl:value-of select="@name"/><xsl:text> = "</xsl:text><xsl:value-of select="@value"/><xsl:text>",&#10;</xsl:text>
                    </xsl:when>
                    <xsl:when test="@type='integer'">
                        <xsl:text>&#9;.</xsl:text><xsl:value-of select="@name"/><xsl:text> = </xsl:text><xsl:value-of select="@value"/><xsl:text>,&#10;</xsl:text>
                    </xsl:when>
                    <xsl:when test="@type='enum'">
                        <xsl:text>&#9;.</xsl:text><xsl:value-of select="@name"/><xsl:text> = </xsl:text><xsl:value-of select="@value"/><xsl:text>,&#10;</xsl:text>
                    </xsl:when>
                    <xsl:when test="@type='HubID'">
                        <xsl:text>&#9;.</xsl:text><xsl:value-of select="@name"/><xsl:text> = </xsl:text><xsl:value-of select="@value"/><xsl:text>,&#10;</xsl:text>
                    </xsl:when>
                    <xsl:when test="@type='array'">
                        <xsl:text>&#9;.</xsl:text><xsl:value-of select="@name"/><xsl:text> = (L1_UINT32[</xsl:text><xsl:value-of select="@value"/><xsl:text>]){},&#10;</xsl:text>
                    </xsl:when>
                  </xsl:choose>
                </xsl:for-each>
                <xsl:text>};&#10;&#10;</xsl:text>
            </xsl:when>
            <xsl:otherwise>
                <xsl:text>;&#10;&#10;</xsl:text>
            </xsl:otherwise>
        </xsl:choose>
    </xsl:template>



</xsl:stylesheet>
