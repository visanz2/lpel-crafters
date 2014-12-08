/*******************************************************************************
 * OpenComRTOS
 * Copyright Altreonic NV, 2005-2008
 * www.Altreonic.com
 * Module name: ($Path/$Filename) 
 * Synopsis: This module defines the platform dependent macros used into
 *   OpenComRTOS Layer L1_ API and provide context switch in ISR. 
 * 
 * $LastChangedDate: 2010-09-30 19:41:18 +0200 (Thu, 30 Sep 2010) $
 * $Revision: 1896 $
 * $LastChangedBy: bernhard.sputh $
 *******************************************************************************/

extern void L1_enterCriticalSection(void);
extern void L1_leaveCriticalSection(void);
extern L1_INTERRUPT_STATUS L1_saveStatusRegister(void);
extern void L1_restoreStatusRegister(L1_INTERRUPT_STATUS status);
