#include <iostream>
#include "user.h"
#include "user2.h"
#include "user3.h"
#include "dataSource.h"

int main()
{
    /* initialize the source of the data. the data source (notifier) initializes its
     * list that will hold all of the users of the data (subscribers) */
    dataSource_module_initialize();
    /* this is where the user subscribes to the data source notifications */
    
    user_force_subscribe();
    user2_force_subscribe();
    user3_force_subscribe();


    /* feed the data source data. this could be from a bus, interrupt, etc. */
    dataSource_feedData(5);
    dataSource_feedData(14147);

    user2_force_unsubscribe();

    dataSource_feedData(12);

    user3_force_unsubscribe();

    dataSource_feedData(414);

    user3_force_subscribe();
    user2_force_subscribe();

    dataSource_feedData(3133);

    user_force_unsubscribe();
    user2_force_unsubscribe();
    user3_force_unsubscribe();

    dataSource_feedData(7);

    user3_force_subscribe();
    user2_force_subscribe();
    user_force_subscribe();


    dataSource_feedData(900);
}

