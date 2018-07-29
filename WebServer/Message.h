/**
 * @file
 *
 * This file contains all message-related objects, independent of the specific API
 *
 * This middle layer allows us to abstract away many of the communication details,
 * allowing us to focus on the core functional implementation.
 *
 */

#ifndef MESSAGE_H
#define MESSAGE_H

#include "ServerObjects.h"
#include <string>

/**
 * Types of messages that can be sent between client/server
 */
enum MessageType {
  VERIFY_ORDER,
  VERIFY_ORDER_RESPONSE,
  REQUEST_INVENTORY,
  REQUEST_INVENTORY_RESPONSE,
  GOODBYE,
  UNKNOWN
};

// status messages for response objects
#define MESSAGE_STATUS_OK "OK"
#define MESSAGE_STATUS_ERROR "ERROR"

/**
 * Base class for messages
 */
class Message {
 public:
  virtual MessageType type() const = 0;
};

class ResponseMessage : public Message {
 public:
};

/**
 * Verify an Order
 */
class VerifyOrderMessage : public Message {
 public:
  ServerOrder order_;

  VerifyOrderMessage(const ServerOrder& order)  : order_(order) {}

  MessageType type() const {
    return MessageType::VERIFY_ORDER;
  }
};

/**
 * Response to Verifying order
 */
class VerifyOrderResponseMessage : public ResponseMessage {
 public:
	 const ServerReport report_;
  VerifyOrderResponseMessage(const ServerReport report): report_(report) {}

  MessageType type() const {
    return MessageType::VERIFY_ORDER_RESPONSE;
  }
};

/**
 * Remove a song from the library
 */
class RequestInventoryMessage : public Message {
 public:

  MessageType type() const {
    return MessageType::REQUEST_INVENTORY;
  }
};

/**
 * Response to removing a song from the library
 */
class RequestInventoryResponseMessage : public ResponseMessage {
 public:
  ServerProduct products_[MAX_NUM_PRODUCTS];

  MessageType type() const {
    return MessageType::REQUEST_INVENTORY_RESPONSE;
  }
};

/**
 * Goodbye message
 */
class GoodbyeMessage : public Message {
 public:
  MessageType type() const {
    return MessageType::GOODBYE;
  }
};

#endif 
