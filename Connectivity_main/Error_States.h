


#ifndef ERROR_STATES_H_
#define ERROR_STATES_H_

typedef enum
{
	ES_OK,
	ES_ERROR,
	ES_NULL_POINTER,
	ES_OUT_OF_RANGE
}ES_t;

#define ERROR_STATE_SIZE				3
#define ERROR_STATE_MASK				7


#endif /* ERROR_STATES_H_ */