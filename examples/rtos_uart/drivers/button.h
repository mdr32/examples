#ifndef _DRIVERS_BUTTON_H
#define _DRIVERS_BUTTON_H

#ifdef __cplusplus
 extern "C" {
#endif

void vButtonInit (void);
BaseType_t xButtonReadPortSwitch (void);

#ifdef __cplusplus
}
#endif
#endif