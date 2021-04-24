/****************************************************************************
 * NOTIFY
 * 
 * lightweight subscription-notification wrapper for users to subscribe to a 
 * data source's notification. 
 * 
 * supports multiple subscriptions by multiple users to a single notification
 * 
 * the subscriber's callback function is called directly from the notifier's
 * thread, so make sure that the subscriber does not block or perform any 
 * other non-thread-safe opearations
 * 
 * the notifier's list must be initialized before the subscriber registers 
 * itself with it.
 * 
 * github.com/ryanmerlshort/notify
 * 
 ***************************************************************************/


#ifndef NOTIFY_H
#define NOTIFY_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif


/****************************************************************************
 OBJECTS
 ****************************************************************************/

/*******************************************************************************
 T Y P E S
 ******************************************************************************/
/* object put on the heap when a new subscription is registered. */
typedef struct notify_subscription_s{
    /* subscriber's function that gets called back by notifier */
    void (*cbf)(void*);
    /* enable or disable a subscription */
    bool enabled;
    /* private variable - for internal use only */
    struct notify_subscription_s* _nextNotify;
} notify_subscription;

/* object owned by notifier that contains all of the subscribers. */
typedef notify_subscription* notify_subscriberList;

/* notify callback function type */
typedef void(*notify_cb)(void*);

/****************************************************************************
 NOTIFIER FUNCTIONS
 ****************************************************************************/

/* called by notifier to intialize the list */
void notify_initializeList(notify_subscriberList*);

/* called by notifier when the subscriber sends a subscription request. This
 * function adds the subscription to the list */
bool notify_addSubscriptionToList(notify_subscriberList* list, notify_cb newSub);

/* called by notifier when the subscriber sends an unsubscribe  request. This
 * function removes the subscription from the list */
bool notify_removeSubscriptionFromList(notify_subscriberList* list, notify_cb newSub);

/* called by notifier when the data is received. This function calls the user's
 * callback function, returning the requested data. */
void notify_notifySubscribers(notify_subscriberList*, void*);


#ifdef __cplusplus
}
#endif


#endif //SUBNOTIFY_H