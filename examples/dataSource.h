#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

void dataSource_module_initialize(void);
bool dataSource_subscribe(void(*cbf)(uint32_t*));
bool dataSource_unsubscribe(void(*cbf)(uint32_t*));
void dataSource_feedData(uint32_t newData);

#ifdef __cplusplus
}
#endif
