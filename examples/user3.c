#include <iostream>
#include <vector>
#include <string>

#include "user3.h"
#include "dataSource.h"

/* function prototype */
static void dataSource_cbf(uint32_t* data);

/* subscribe to data source notification */
void user3_force_subscribe(void)
{
    std::cout << "user3: subscribing\n\r";
    dataSource_subscribe(dataSource_cbf);
}

void user3_force_unsubscribe(void)
{
    std::cout << "user3: unsubscribing\n\r";
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
    std::cout << "user3: data sent: " << myData << "\n\r";
}
