#include "user.h"
#include "dataSource.h"

int main()
{
    /* initialize the source of the data. the data source (notifier) initializes its
     * list that will hold all of the users of the data (subscribers) */
    dataSource_module_initialize();
    /* this is where the user subscribes to the data source notifications */
    user_initialize_rtos();


    /* feed the data source data. this could be from a bus, interrupt, etc. */
    dataSource_feedData(5);
    dataSource_feedData(9);
    dataSource_feedData(14040);


}

