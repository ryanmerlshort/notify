#include <iostream>
#include <vector>
#include <string>

#include "user3.h"
#include "dataSource.h"

/* function prototype */
static void dataSource_cbf(uint32_t* data);

/* initializer function that is called once the RTOS is started */
void user3_initialize_rtos(void)
{
    dataSource_subscribe(dataSource_cbf);
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
    std::cout << "data sent to user 3: " << myData << "\n\r";
}
