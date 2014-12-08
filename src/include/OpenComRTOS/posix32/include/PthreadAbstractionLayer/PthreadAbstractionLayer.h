/*
 * pthread_ocr.h
 *
 *  Created on: Dec 2, 2013
 *      Author: Marina
 */

#include <L1_types.h>


#ifndef PTHREADABSTRACTIONLAYER_H_
#define PTHREADABSTRACTIONLAYER_H_


/**
 * \defgroup PthreadAbstractionLayer Pthread Abstraction Layer
 *
 */

/** @defgroup Pth_Thread Threads
 *  @ingroup PthreadAbstractionLayer
 *	Thread related functions.
 */

/** @defgroup Pth_Mutex Mutexes
 *  @ingroup PthreadAbstractionLayer
 *  Mutex related functions.
 */

/** @defgroup Pth_Cond Conditional Variable
 *  @ingroup PthreadAbstractionLayer
 *  Conditional variable related functions.
 */

/** @defgroup Pth_Key Keys
 *  @ingroup PthreadAbstractionLayer
 *	Key related functions.
 */


/**
 * The L1_UINT32 value of is formatted the following way:
 * - MSByte: Major Version of the Kernel
 * - 23--16: Minor Version
 * - 15--8 : Patch-level
 * - LSByte: Release status:
 * 			- 0: Alpha
 * 			- 1: Beta
 * 			- 2: Release Candidate
 * 			- 3: Public Release
 *
 * This number is loosely associated with the OpenVE version number.
 */
#define PAL_VERSION 0x01000000  // 1.0 Alpha Patch level 0

#define OCR_PTHREAD_CREATE_JOINABLE 	0
#define OCR_PTHREAD_CREATE_DETACHED 	1

#define EINVAL 22
#define EBUSY  16
#define EAGAIN 11
#define ESRCH   3

//#undef pthread_attr_t

typedef struct _name {
	L1_BOOL initialized;
	L1_BOOL detached;
}ocr_pthread_attr_t;

typedef L1_UINT32 ocr_pthread_t;

typedef L1_UINT32 ocr_pthread_mutex_t;
typedef L1_UINT32 ocr_pthread_mutexattr_t;

typedef L1_UINT32 ocr_pthread_cond_t;
typedef L1_UINT32 ocr_pthread_condattr_t;

typedef L1_UINT32 ocr_pthread_key_t;

/**
 * \ingroup Pth_Thread
 * This function initializes the thread attributes object pointed to by attr
 * with default attribute values.
 *
 * @param *attr Pointer to the pthread_attr_t structure.
 *
 * @return 0 Attributes object was successfully initialized.
 */
int ocr_pthread_attr_init (ocr_pthread_attr_t *attr);

/**
 * \ingroup Pth_Thread
 * This function destroys a thread attributes object.
 *
 * @param *attr Pointer to the pthread_attr_t structure.
 *
 * @return 0 Attributes object was successfully destroyed.
 * @return EINVAL Attributes object was not initialized.
 */
int ocr_pthread_attr_destroy (ocr_pthread_attr_t *attr);

/**
 * \ingroup Pth_Thread
 * This function sets the detach state attribute of the thread attributes object
 * referred to by attr to the value specified in detachstate. The detach state
 * attribute determines whether a thread created using the thread attributes
 * object attr will be created in a joinable or a detached state.
 *
 * @param *attr Pointer to the pthread_attr_t structure.
 * @param detachstate It could have two values:
 * PTHREAD_CREATE_DETACHED
 * 		Threads that are created using attr will be created in a detached state.
 * PTHREAD_CREATE_JOINABLE
 *      Threads that are created using attr will be created in a joinable state.
 * The default setting of the detach state attribute in a newly initialized
 * thread attributes object is PTHREAD_CREATE_JOINABLE.
 *
 * @return EINVAL An invalid value was specified in detachstate.
 */
int ocr_pthread_attr_setdetachstate(ocr_pthread_attr_t *attr, int detachstate);

/**
 * \ingroup Pth_Thread
 * This function returns the detach state attribute of the thread attributes
 * object attr in the buffer pointed to by detachstate.
 *
 * @param *attr Pointer to the pthread_attr_t structure.
 * @param * detachstate
 *
 * @return EINVAL An invalid detachestate was stored in attr.
 */
int ocr_pthread_attr_getdetachstate(ocr_pthread_attr_t *attr, int *detachstate);

/**
 * \ingroup Pth_Thread
 * This function starts a new thread in the calling process.  The new thread
 * starts execution by invoking start_routine();
 *
 * @param *thread Thread ID used to refer it in subsequent calls to other
 * pthreads functions.
 * @param *attr Pointer to a pthread_attr_t structure whose contents are used at
 * thread creation time to determine attributes for the new thread; If attr is
 * NULL, then the thread is created with default attributes.
 * @param *start_routine
 * @param *arg Argument of start_routine().
 *
 * @return 0 Thread was successfully created.
 * @return EAGAIN Insufficient resources to create another thread, or a system-
 * imposed limit on the number of threads was encountered.
 */
int ocr_pthread_create (ocr_pthread_t *thread, const ocr_pthread_attr_t *attr,
                 void *(*start_routine)(void *), void *arg);

/**
 * \ingroup Pth_Thread
 * This function returns the ID of the calling thread. This is the same value
 * that is returned in *thread in the pthread_create(3) call that created this
 * thread.
 *
 * @return ID of the calling thread.
 */
ocr_pthread_t ocr_pthread_self (void);

/**
 * \ingroup Pth_Thread
 * This function waits for the thread specified by thread to terminate. If that
 * thread has already terminated, then pthread_join() returns immediately.  The
 * thread specified by thread must be joinable.
 *
 * @param thread Thread ID.
 * @param **value_ptr If retval is not NULL, then pthread_join() copies the exit
 * status of the target thread into the location pointed to by *retval.
 *
 * @return 0 Thread was successfully joined.
 * @return EINVAL thread is not a joinable thread.
 */
int ocr_pthread_join (ocr_pthread_t thread, void **value_ptr);

/**
 * \ingroup Pth_Thread
 * This function marks the thread identified by thread as detached.  When a
 * detached thread terminates, its resources are automatically released back to
 * the system without the need for another thread to join with the terminated
 * thread.
 *
 * @param thread Thread ID.
 *
 * @return 0 Thread was successfully marked as detached.
 * @return EINVAL thread is not a joinable thread.
 */
int ocr_pthread_detach (ocr_pthread_t thread);

/**
 * \ingroup Pth_Mutex
 * This function initialises the mutex referenced by mutex with default mutex
 * attributes. Mutex attributes object gets ignored. Upon successful
 * initialisation, the state of the mutex becomes initialised and unlocked.
 *
 * @param *m Mutex ID.
 * @param *attr Pointer to a pthread_mutexattr_t. Right now it gets ignored, so
 * the mutex is created with default attributes.
 *
 * @return 0 Mutex was successfully intialized.
 * @return EAGAIN Insufficient resources to create another mutex.
 */
int ocr_pthread_mutex_init (ocr_pthread_mutex_t *m, const ocr_pthread_mutexattr_t *attr);

/**
 * \ingroup Pth_Mutex
 * This function destroys the mutex object referenced by mutex; the mutex object
 * becomes, in effect, uninitialised. A destroyed mutex object can be
 * re-initialised using pthread_mutex_init();
 *
 * @param *m Mutex ID.
 *
 * @return 0 Mutex was successfully destroyed.
 * @return EBUSY the object referenced by mutex is locked or referenced.
 */
int ocr_pthread_mutex_destroy (ocr_pthread_mutex_t *m);

/**
 * \ingroup Pth_Mutex
 * This function locks the mutex referenced by the mutex object. If the mutex
 * is already locked, the calling thread blocks until the mutex becomes
 * available. This operation returns with the mutex object referenced by mutex
 * in the locked state with the calling thread as its owner.
 *
 * @param *m Mutex ID.
 *
 * @return 0 Mutex was successfully locked.
 * @return EINVAL The value specified by mutex does not refer to an initialised
 * mutex object.
 * @return EBUSY The mutex is locked.
 */
int ocr_pthread_mutex_lock (ocr_pthread_mutex_t *m);

/**
 * \ingroup Pth_Mutex
 * This function function releases the mutex object referenced by mutex.
 *
 * @param *m Mutex ID.
 *
 * @return 0 Mutex was successfully unlocked.
 * @return EINVAL The value specified by mutex does not refer to an initialised
 * mutex object.
 */
int ocr_pthread_mutex_unlock (ocr_pthread_mutex_t *m);

/**
 * \ingroup Pth_Cond
 * This function initialises the condition variable referenced by c with default
 * condition variable attributes. Condition variable attributes object gets
 * ignored. Upon successful initialisation, the state of the condition variable
 * becomes initialised.
 *
 * @param *c Condition variable ID.
 * @param *attr Pointer to a pthread_condattr_t data structure. Right now it gets
 * ignored, so the condition variable is created with default attributes.
 *
 * @return 0 Condition variable was successfully intialized.
 * @return EAGAIN Insufficient resources to create another condition variable.
 */
int ocr_pthread_cond_init (ocr_pthread_cond_t *c, const ocr_pthread_condattr_t *attr);

/**
 * \ingroup Pth_Cond
 * This function destroys the given condition variable specified by cond; the
 * object becomes, in effect, uninitialized. It shall be safe to destroy an
 * initialized condition variable upon which no threads are currently blocked.
 *
 * @param *c Condition variable ID.
 *
 * @return 0 Condition variable was successfully intialized.
 * @return EBUSY The condition variable it is still referenced.
 * @return EINVAL The value specified by c does not refer to intialised
 * object.
 */
int ocr_pthread_cond_destroy (ocr_pthread_cond_t *c);

/**
 * \ingroup Pth_Cond
 * This function unblocks at least one of the threads that are blocked on the
 * specified condition variable cond (if any threads are blocked on cond).
 *
 * @param *c Condition variable ID.
 *
 * @return 0 Condition variable was successfully intialized.
 * @return EINVAL The value specified by c does not refer to an initialised
 * condition variable object.
 */
int ocr_pthread_cond_signal (ocr_pthread_cond_t *c);

/**
 * \ingroup Pth_Cond
 * This function blocks a thread on a condition variable. They are called with
 * mutex locked by the calling thread or undefined behaviour will result.
 *
 * @param *c Condition variable ID.
 * @param *m Mutex ID.
 *
 * @return 0 Condition variable was successfully intialized.
 * @return EINVAL When:
 * - The value specified by c or m does not refer to intialised
 * objects.
 * - The mutex was not owned by the thread at the time of the call.
 * - Different mutex were supplied for concurrent waits in the same condition
 * variable.
 */
int ocr_pthread_cond_wait (ocr_pthread_cond_t *c, ocr_pthread_mutex_t *m);

/**
 * \ingroup Pth_Key
 * This function creates a thread-specific data key visible to all threads in
 * the process. Key values provided by pthread_key_create() are opaque objects
 * used to locate thread-specific data. Although the same key value may be used
 * by different threads, the values bound to the key by pthread_setspecific()
 * are maintained on a per-thread basis and persist for the life of the calling
 * thread.
 *
 * @param *key Key ID.
 * @param *destructor An optional destructor function may be associated with
 * each key value. At thread exit, if a key value has a non-NULL destructor
 * pointer, and the thread has a non-NULL value associated with that key, the
 * value of the key is set to NULL, and then the function pointed to is called
 * with the previously associated value as its sole argument.
 *
 * @return 0 Key was successfully created.
 * @return EAGAIN Insufficient resources to create another key.
 */
int ocr_pthread_key_create (ocr_pthread_key_t *key, void (*destructor) (void *));

/**
 * \ingroup Pth_Key
 * This function function associates a thread-specific value with a key
 * obtained via a previous call to pthread_key_create(). Different threads may
 * bind different values to the same key. These values are typically pointers
 * to blocks of dynamically allocated memory that have been reserved for use by
 * the calling thread.
 *
 * @param key Key ID.
 * @param *value
 *
 * @return 0 Data was successfully associated with the key.
 * @return EINVAL The key value is invalid.
 */
int ocr_pthread_setspecific (ocr_pthread_key_t key, const void *value);

/**
 * \ingroup Pth_Key
 * This function function returns the value currently bound to the specified
 * key on behalf of the calling thread.
 *
 * @param key Key ID.
 *
 * @return NULL No data was associated with the given key.
 * @return void * The thread-specific data value associated with the given key.
 */
void * ocr_pthread_getspecific (ocr_pthread_key_t key);

/**
 * \ingroup Pth_Key
 * This function deletes a thread-specific data key previously returned by
 * pthread_key_create(). The thread-specific data values associated with key
 * need not be NULL at the time pthread_key_delete() is called. It is the
 * responsibility of the application to free any application storage or perform
 * any cleanup actions for data structures related to the deleted key or
 * associated thread-specific data in any threads; this cleanup can be done
 * either before or after pthread_key_delete() is called. Any attempt to use
 * key following the call to pthread_key_delete() results in undefined behavior.
 * The pthread_key_delete() function shall be callable from within destructor
 * functions. No destructor functions shall be invoked by pthread_key_delete().
 * Any destructor function that may have been associated with key shall no
 * longer be called upon thread exit.
 *
 * @param key Key ID.
 *
 * @return 0 Key was successfully deleted.
 * @return EINVAL The key value is invalid.
 */
int ocr_pthread_key_delete (ocr_pthread_key_t key);


#endif
