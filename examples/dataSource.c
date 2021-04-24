#include "dataSource.h"
#include "../notify.h"
#include <stdint.h>

notify_subscriberList dataSourceSubscribers;

/* initializer that gets called before the RTOS runs */
void dataSource_module_initialize(void)
{
    notify_initializeList(&dataSourceSubscribers);
}

/* called when the subscriber wants to register for notifications */
bool dataSource_subscribe(void(*cbf)(uint32_t*))
{
    return notify_addSubscriptionToList(&dataSourceSubscribers, (notify_cb)cbf);
}

/* when the data comes in, notify the subscribers */
void dataSource_feedData(uint32_t newData)
{
    notify_notifySubscribers(&dataSourceSubscribers, (void*)&newData);
}

