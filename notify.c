/****************************************************************************
 * notify
 * 
 * this implementation is heap based:
 *  - a new subscription into an empty list gets a notify_subscription malloc'd
 *  and inserted into the list
 *  - an unsubscription gets its contents set to null, but the empty shell 
 *  remains in the list, to be used by another subscriber later
 *  - a new subscription that comes in when there's an empty slot in the list 
 *  (from a previous unsubscription) uses the null container instead of malloc'ing
 *  a new one.
 ***************************************************************************/ 


/*******************************************************************************
 I N C L U D E S
 ******************************************************************************/
#include "notify.h"
#include <stdbool.h>
#include <stddef.h>
#include <malloc.h>


/*******************************************************************************
 D E F I N E S
 ******************************************************************************/
#define MAX_LIST_ITEMS 1024


/*******************************************************************************
 T Y P E S
 ******************************************************************************/



/*******************************************************************************
 P U B L I C   F U N C T I O N S
 ******************************************************************************/

/* wrapper to set the subscriber's function that gets called back when the 
 * notification is ready */
void notify_initializeSubscription(notify_subscription* sub, void (*cbf)(void*))
{
    sub->cbf = cbf;
    sub->enabled = false;
    sub->_nextNotify = NULL;
}

/* initialize list */
void notify_initializeList(notify_subscriberList* list)//,
//        void(*localMalloc)(size_t), 
//        void(*localFree)(size_t))
{

    list->firstSub = NULL;
//    list->localMalloc = localMalloc;
//    list->localFree = localFree;
}

/* called by notifier when the subscriber sends a subscription request. This
 * function adds the subscription to the list */
bool notify_addSubscriptionToList(notify_subscriberList* list, notify_cb sub_cbf)
{
    int listIndex=0;
    notify_subscription* subInList;
    bool success = false;

    /* if the list is empty, add new sub to list */
    if(list->firstSub == NULL){
        void* newSubMalloc = malloc(sizeof(notify_subscription));
        if(newSubMalloc == NULL){
            return false;
        }
        subInList = (notify_subscription*)newSubMalloc;
        subInList->_nextNotify = NULL;
        subInList->cbf = sub_cbf;
        subInList->enabled = true;
        list->firstSub = (notify_subscription*)subInList;
    }
    /* else find the last subscriber in the list and set its address to newSub */
    else{
        subInList = list->firstSub;
        while( (listIndex < MAX_LIST_ITEMS) ){
            /* if this element in the list is empty, put data in here and exit */
            if(subInList->cbf == NULL){
                subInList->cbf = sub_cbf;
                subInList->enabled = true;
                success = true;
                break;
            }
            /* else if this sub is the last element in the list, add new sub to it and exit */
            else if(subInList->_nextNotify == NULL){
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

/* called by notifier when the subscriber sends an unsubscribe  request. This
 * function removes the subscription from the list */
bool notify_removeSubscriptionFromList(notify_subscriberList* list, notify_cb unsub_cbf)
{
    int listIndex=0;
    notify_subscription* subInList;
    bool success = false;

    /* if the list is empty, return */
    if(list->firstSub == NULL){
        return false;
    }

    /* find the matching cbf subscriber in the list and set nullify its package */
    subInList = list->firstSub;
    while( (listIndex < MAX_LIST_ITEMS) ){
        /* if this element in the list is empty, nullify its data and exit */
        if(subInList->cbf == unsub_cbf){
            subInList->cbf = NULL;
            subInList->enabled = false;
            success = true;
            break;
        }
        /* else increment to the next element in the list */
        else{
            subInList = subInList->_nextNotify;
        }
        listIndex++;
    }

    return success;
}


/* called by notifier when the data is received. This function calls all of the 
 * subscribers' callback functions, sending them the requested data.  */
void notify_notifySubscribers(notify_subscriberList* list, void* data)
{
    int listIndex=0;
    notify_subscription* subInList = list->firstSub;

    while( (listIndex < MAX_LIST_ITEMS) && (subInList != NULL) ){
        if(subInList->enabled){
            if(subInList->cbf){
                subInList->cbf(data);
            }
        }
        subInList = subInList->_nextNotify;
    }   
}

