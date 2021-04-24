#include <iostream>
#include "user.h"
#include "dataSource.h"

/* function prototype */
static void dataSource_cbf(uint32_t* data);

/* subscribe to data source notification */
void user_force_subscribe(void)
{
    std::cout << "user1: subscribing\n\r";
    dataSource_subscribe(dataSource_cbf);
}

void user_force_unsubscribe(void)
{
    std::cout << "user1: unsubscribing\n\r";
    dataSource_unsubscribe(dataSource_cbf);
}

/* function that gets called when the data source sends data.
 * 
 * this function would typically transform and non-blockingly use the data
 * 
 * note: this function runs in notifier's thread */
static void dataSource_cbf(uint32_t* data)
{
    unsigned int myData = *(unsigned int*)data;
    /* in our example, we'll just print. */
    std::cout << "user1: data sent: " << myData << "\n\r";
}
