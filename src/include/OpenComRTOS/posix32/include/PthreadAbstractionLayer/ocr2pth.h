/*
 * ocr2pth.h
 *
 *  Created on: Dec 19, 2013
 *      Author: Marina
 */

#ifndef OCR2PTH_H_
#define OCR2PTH_H_

#include <PthreadAbstractionLayer/PthreadAbstractionLayer.h>

#define PTHREAD_CREATE_JOINABLE OCR_PTHREAD_CREATE_JOINABLE
#define PTHREAD_CREATE_DETACHED OCR_PTHREAD_CREATE_DETACHED

#define pthread_attr_t ocr_pthread_attr_t
#define pthread_t      ocr_pthread_t

#define pthread_mutexattr_t ocr_pthread_mutexattr_t
#define pthread_mutex_t     ocr_pthread_mutex_t

#define pthread_condattr_t ocr_pthread_condattr_t
#define pthread_cond_t     ocr_pthread_cond_t

#define pthread_key_t ocr_pthread_key_t

#define pthread_attr_init           ocr_pthread_attr_init
#define pthread_attr_destroy        ocr_pthread_attr_destroy
#define pthread_attr_setdetachstate ocr_pthread_attr_setdetachstate
#define pthread_attr_getdetachstate ocr_pthread_attr_getdetachstate

#define pthread_create ocr_pthread_create
#define pthread_self   ocr_pthread_self
#define pthread_join   ocr_pthread_join
#define pthread_detach ocr_pthread_detach

#define pthread_mutex_init    ocr_pthread_mutex_init
#define pthread_mutex_destroy ocr_pthread_mutex_destroy
#define pthread_mutex_lock    ocr_pthread_mutex_lock
#define pthread_mutex_unlock  ocr_pthread_mutex_unlock

#define pthread_cond_init    ocr_pthread_cond_init
#define pthread_cond_destroy ocr_pthread_cond_destroy
#define pthread_cond_signal  ocr_pthread_cond_signal
#define pthread_cond_wait    ocr_pthread_cond_wait

#define pthread_key_create      ocr_pthread_key_create
#define pthread_key_delete      ocr_pthread_key_delete
#define pthread_setspecific ocr_pthread_setspecific
#define pthread_getspecific ocr_pthread_getspecific


#endif /* OCR2PTH_H_ */
