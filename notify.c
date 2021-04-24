#include "notify.h"
#include <stdbool.h>
#include <stddef.h>
#include <malloc.h>

#define MAX_LIST_ITEMS 1024

/****************************************************************************
 SUBSCRIBER FUNCTIONS
 ****************************************************************************/

/* wrapper to set the subscriber's function that gets called back when the 
 * notification is ready */
void notify_initializeSubscription(notify_subscription* sub, void (*cbf)(void*))
{
    sub->cbf = cbf;
    sub->enabled = false;
    sub->_nextNotify = NULL;
}

/* wrapper to set the subscriber's function that gets called back when the 
 * notification is ready */
void notify_setCallback(notify_subscription* sub, void (*cbf)(void*))
{
    sub->cbf = cbf;
}

/* wrapper to enable the subscription */
void notify_enableSubscription(notify_subscription* sub)
{
    sub->enabled = true;
}

/* wrapper to disable the subscription */
void notify_disableSubscription(notify_subscription* sub)
{
    sub->enabled = false;
}


/****************************************************************************
 NOTIFIER FUNCTIONS
 ****************************************************************************/

/* initialize list */
void notify_initializeList(notify_subscriberList* list)
{
    *list = NULL;
}

/* called by notifier when the subscriber sends a subscription request. This
 * function adds the subscription to the list */
bool notify_addSubscriptionToList(notify_subscriberList* list, notify_cb sub_cbf)
{
    int listIndex=0;
    notify_subscription* subInList;
    bool success = false;

    /* if the list is empty, add new sub to list */
    if(*list == NULL){
        void* newSubMalloc = malloc(sizeof(notify_subscription));
        if(newSubMalloc == NULL){
            return false;
        }
        subInList = (notify_subscription*)newSubMalloc;
        subInList->_nextNotify = NULL;
        subInList->cbf = sub_cbf;
        subInList->enabled = true;
        *list = (notify_subscription*)subInList;
    }
    /* else find the last subscriber in the list and set its address to newSub */
    else{
        subInList = *list;
        while( (listIndex > MAX_LIST_ITEMS) ){
            /* if this sub is the last element in the list, add new sub to it and exit */
            if(subInList->_nextNotify == NULL){
                void* newSubMalloc = malloc(sizeof(notify_subscription));
                if(newSubMalloc == NULL){
                    return false;
                }                
                notify_subscription* newSub = (notify_subscription*)newSubMalloc;
                newSub->_nextNotify = NULL;
                newSub->cbf = sub_cbf;
                newSub->enabled = true;
                subInList->_nextNotify = newSub;
                success = true;
                break;
            }
            /* else increment to the next element in the list */
            else{
                subInList = subInList->_nextNotify;
            }
            listIndex++;
        }
    }
    return success;
}

/* called by notifier when the data is received. This function calls all of the 
 * subscribers' callback functions, sending them the requested data.  */
void notify_notifySubscribers(notify_subscriberList* list, void* data)
{
    int listIndex=0;
    notify_subscription* subInList = *list;

//    if(*list == NULL){
//        return;
//    }

    while( (listIndex < MAX_LIST_ITEMS) && (subInList != NULL) ){
        if(subInList->enabled){
            subInList->cbf(data);
            subInList = subInList->_nextNotify;
        }
    }   
}

