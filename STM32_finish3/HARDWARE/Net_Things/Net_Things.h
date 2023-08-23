#ifndef __Net_Things_H
#define __Net_Things_H

#include "sys.h"
#define A    0


void Net_Things_Init(void);
//void Property_Post(u8 LightSwitch,u8 OutputWaterTemputer,u8 WaterOutletSwitch1,u8 WaterOutletSwitch2,u8 HeatingSwitch,u8 FairSwitch);
void Property_Post(u8 LightSwitch,u8 OutputWaterTemputer,u8 WaterOutletSwitch1);
void PubTopic(u8 *msg);
void PubTopicinfo(u8 OutputWaterTemputer,u8 LightSwitch);
void UnConnect(void);
void Property_Post2(u8 WaterOutletSwitch2,u8 HeatingSwitch,u8 FairSwitch);
void PubTopicinfo2(u8 OutputWaterTemputer,u8 TASK,u8 sta1,u8 sta2);
#endif
