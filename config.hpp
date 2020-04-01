/*
 * config.h
 *
 * Created: 3/30/2020 11:32:47 AM
 *  Author: Asus
 */ 


#ifndef CONFIG_H_
#define CONFIG_H_


#ifndef CONFIG_DEBUG_EVENT
	#define CONFIG_DEBUG_EVENT
	#define CONFIG_DEBUG_EVENT_NAME_LEGTH			10
	#define CONFIG_DEBUG_EVENT_DEFAULT_ID			0	
#endif

#define CONFIG_EVENT_DEFAULT_PRIORITY				0
#define CONFIG_EVENT_MAX_PRIORITY					3


#define CONFIG_TIMER_TICK_PERIOD_MS					5


#define CONFIG_FIFO_SIZE							30



#endif /* CONFIG_H_ */