/**
* @file
*
* This file contains all message-related objects, independent of the specific API
*
* This middle layer allows us to abstract away many of the communication details,
* allowing us to focus on the core functional implementation.
*/

#ifndef MESSAGES_H
#define MESSAGES_H

/**
* Types of messages that can be sent to/from warehouse
*/
enum MessageType {
	ADD,
	ADD_RESPONSE,
	REMOVE,
	REMOVE_RESPONSE,
	SEARCH,
	SEARCH_RESPONSE,
	GOODBYE,
	UNKNOWN
};

#endif