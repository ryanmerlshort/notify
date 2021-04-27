#include "dataSource.h"
#include "../notify.h"
#include <stdint.h>
#include <iostream>
#include <malloc.h>


notify_subscriberList dataSourceSubscribers;

/* initializer that gets called before the RTOS runs */
void dataSource_module_initialize(void)
{
    notify_initializeList(&dataSourceSubscribers, (mallocType)malloc, (freeType)free);
}

/* called when the subscriber wants to register for notifications */
bool dataSource_subscribe(void(*cbf)(uint32_t*))
{
    return notify_addSubscriptionToList(&dataSourceSubscribers, (notify_cb)cbf);
}

/* called when the subscriber wants to unregister for notifications */
bool dataSource_unsubscribe(void(*cbf)(uint32_t*))
{
    return notify_removeSubscriptionFromList(&dataSourceSubscribers, (notify_cb)cbf);
}

/* when the data comes in, notify the subscribers */
void dataSource_feedData(uint32_t newData)
{
    std::cout << "dataSource: "<< (unsigned int)newData << " sent to data source\n\r";
    notify_notifySubscribers(&dataSourceSubscribers, (void*)&newData);
}

