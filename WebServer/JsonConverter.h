/**
 * @file
 *
 * This file provides all the JSON encoding/decoding functionality
 *
 */

#ifndef JSONCONVERTER_H
#define JSONCONVERTER_H

#include "ServerObjects.h"
#include "Message.h"
#include <json.hpp>   // json parsing

#include <vector>
#include <memory>     // for std::unique_ptr
#include <set>

// convenience alias for json
using JSON = nlohmann::json;

// types of messages
#define MESSAGE_VERIFY_ORDER "verify order"
#define MESSAGE_VERIFY_ORDER_RESPONSE "order report"
#define MESSAGE_REQUEST_INVENTORY "request inventory"
#define MESSAGE_REQUEST_INVENTORY_RESPONSE "inventory"


// other keys
#define MESSAGE_TYPE "msg"
#define MESSAGE_PRODUCT "product"
#define MESSAGE_PRODUCT_NAME "name"
#define MESSAGE_PRODUCT_ID "product ID"
#define MESSAGE_PRODUCT "price"
#define MESSAGE_ORDER_ID "order ID"

/**
 * Handles all conversions to and from JSON
 */
class JsonConverter {
 public:
  /**
   * Converts the song to a JSON object
   * @param song song to jsonify
   * @return JSON object representation
   */
  static JSON toJSON(const ServerProduct &product) {
    JSON j;
    j[MESSAGE_SONG_ARTIST] = song.artist;
    j[MESSAGE_SONG_TITLE] = song.title;
    return j;
  }

  /**
   * Converts a vector of songs to a JSON array of objects
   * @param songs vector of songs to jsonify
   * @return JSON array representation
   */
  static JSON toJSON(const std::vector<Song> &songs) {
    JSON j;
    for (const auto& song : songs) {
      j.push_back(toJSON(song));
    }
    return j;
  }

  /**
   * Converts a vector of songs to a JSON array of objects
   * @param songs vector of songs to jsonify
   * @return JSON array representation
   */
  static JSON toJSON(const std::set<Song> &songs) {
    JSON j;
    for (const auto& song : songs) {
      j.push_back(toJSON(song));
    }
    return j;
  }

  /**
   * Converts an "add" message to a JSON object
   * @param add message
   * @return JSON object representation
   */
  static JSON toJSON(const AddMessage &add) {
    JSON j;
    j[MESSAGE_TYPE] = MESSAGE_ADD;
    j[MESSAGE_SONG] = toJSON(add.song);
    return j;
  }

  /**
   * Converts an "add" response message to a JSON object
   * @param add_response message
   * @return JSON object representation
   */
  static JSON toJSON(const AddResponseMessage &add_response) {
    JSON j;
    j[MESSAGE_TYPE] = MESSAGE_ADD_RESPONSE;
    j[MESSAGE_STATUS] = add_response.status;
    j[MESSAGE_INFO] = add_response.info;
    j[MESSAGE_ADD] = toJSON(add_response.add);
    return j;
  }
  //======================================================
  // TODO: Convert "remove" and response message to JSON
  //======================================================
  //ADDED FUNCTIONS
  //============================================================================================================

  /**
  * Converts an "add" message to a JSON object
  * @param add message
  * @return JSON object representation
  */
  static JSON toJSON(const RemoveMessage &rem) {
	  JSON j;
	  j[MESSAGE_TYPE] = MESSAGE_REMOVE;
	  j[MESSAGE_SONG] = toJSON(rem.song);
	  return j;
  }

  /**
  * Converts a "Remove" response message to a JSON object
  * @param remove_response message
  * @return JSON object representation
  */
  static JSON toJSON(const RemoveResponseMessage &rem_response) {
	  JSON j;
	  j[MESSAGE_TYPE] = MESSAGE_REMOVE_RESPONSE;
	  j[MESSAGE_STATUS] = rem_response.status;
	  j[MESSAGE_INFO] = rem_response.info;
	  j[MESSAGE_REMOVE] = toJSON(rem_response.remove);
	  return j;
  }
  //============================================================================================================
  

  /**
   * Converts a "search" message to a JSON object
   * @param search message
   * @return JSON object representation
   */
  static JSON toJSON(const SearchMessage &search) {
    JSON j;
    j[MESSAGE_TYPE] = MESSAGE_SEARCH;
    j[MESSAGE_SONG_ARTIST_REGEX] = search.artist_regex;
    j[MESSAGE_SONG_TITLE_REGEX] = search.title_regex;
    return j;
  }

  /**
   * Converts a "search" response message to a JSON object
   * @param search_response message
   * @return JSON object representation
   */
  static JSON toJSON(const SearchResponseMessage &search_response) {
    JSON j;
    j[MESSAGE_TYPE] = MESSAGE_SEARCH_RESPONSE;
    j[MESSAGE_STATUS] = search_response.status;
    j[MESSAGE_INFO] = search_response.info;
    j[MESSAGE_SEARCH] = toJSON(search_response.search);
    j[MESSAGE_SEARCH_RESULTS] = toJSON(search_response.results);
    return j;
  }

  /**
   * Converts a "goodbye" message to a JSON object
   * @param goodbye message
   * @return JSON object representation
   */
  static JSON toJSON(const GoodbyeMessage &goodbye) {
    JSON j;
    j[MESSAGE_TYPE] = MESSAGE_GOODBYE;
    return j;
  }

  /**
   * Converts a message to a JSON object, automatically detecting the type
   * @param message
   * @return JSON object representation, {"status"="ERROR", "info"=...} if not recognized
   */
  static JSON toJSON(const Message &msg) {

    //=============================================================
    // TODO: Convert "remove" and its response to JSON
    //=============================================================

    switch(msg.type()) {
      case ADD: {
        return toJSON((AddMessage &) msg);
      }
      case ADD_RESPONSE: {
        return toJSON((AddResponseMessage &) msg);
      }
      case SEARCH: {
        return toJSON((SearchMessage &) msg);
      }
      case SEARCH_RESPONSE: {
        return toJSON((SearchResponseMessage &) msg);
      }
      case GOODBYE: {
        return toJSON((GoodbyeMessage &) msg);
      }
      default: {

      }
    }

    // unknown message type
    JSON err;
    err[MESSAGE_STATUS] = MESSAGE_STATUS_ERROR;
    err[MESSAGE_INFO] = std::string("Unknown message type");
    return err;
  }

  /**
   * Converts a JSON object representing a song to a Song object
   * @param j JSON object
   * @return Song
   */
  static Song parseSong(const JSON &j) {
    return Song(j[MESSAGE_SONG_ARTIST], j[MESSAGE_SONG_TITLE]);
  }

  /**
   * Converts a JSON array representing a list of songs to a
   * vector of Song objects
   * @param jsongs JSON array
   * @return resulting vector of Song
   */
  static std::vector<Song> parseSongs(const JSON &jsongs) {
    std::vector<Song> out;

    for (const auto& song : jsongs) {
      out.push_back(parseSong(song));
    }

    return out;
  }

  /**
   * Converts a JSON object representing an AddMessage to an AddMessage object
   * @param j JSON object
   * @return AddMessage
   */
  static AddMessage parseAdd(const JSON &jadd) {
    Song song = parseSong(jadd[MESSAGE_SONG]);
    return AddMessage(song);
  }

  /**
   * Converts a JSON object representing an AddResponseMessage to an AddResponseMessage object
   * @param j JSON object
   * @return AddResponseMessage
   */
  static AddResponseMessage parseAddResponse(const JSON &jaddr) {
    AddMessage add = parseAdd(jaddr[MESSAGE_ADD]);
    std::string status = jaddr[MESSAGE_STATUS];
    std::string info = jaddr[MESSAGE_INFO];
    return AddResponseMessage(add, status, info);
  }

  //======================================================
  // TODO: Parse "remove" and response message from JSON
  //======================================================
  //ADDED FUNCTIONS
  //============================================================================================================
  /**
  * Converts a JSON object representing a RemoveMessage to a RemoveMessage object
  * @param j JSON object
  * @return RemoveMessage
  */
  static RemoveMessage parseRemove(const JSON &jrem) {
	  Song song = parseSong(jrem[MESSAGE_SONG]);
	  return RemoveMessage(song);
  }

  /**
  * Converts a JSON object representing a RemoveResponseMessage to a RemoveResponseMessage object
  * @param j JSON object
  * @return RemoveResponseMessage
  */
  static RemoveResponseMessage parseRemoveResponse(const JSON &jrem) {
	  RemoveMessage rem = parseRemove(jrem[MESSAGE_REMOVE]);
	  std::string status = jrem[MESSAGE_STATUS];
	  std::string info = jrem[MESSAGE_INFO];
	  return RemoveResponseMessage(rem, status, info);
  }
  //============================================================================================================
  

  /**
   * Converts a JSON object representing a SearchMessage to a SearchMessage object
   * @param j JSON object
   * @return SearchMessage
   */
  static SearchMessage parseSearch(const JSON &jsearch) {
    std::string artist_regex = jsearch[MESSAGE_SONG_ARTIST_REGEX];
    std::string title_regex = jsearch[MESSAGE_SONG_TITLE_REGEX];
    return SearchMessage(artist_regex, title_regex);
  }

  /**
   * Converts a JSON object representing a SearchResponseMessage to a SearchResponseMessage object
   * @param j JSON object
   * @return SearchResponseMessage
   */
  static SearchResponseMessage parseSearchResponse(const JSON &jsearchr) {
    SearchMessage search = parseSearch(jsearchr[MESSAGE_SEARCH]);
    std::vector<Song> results = parseSongs(jsearchr[MESSAGE_SEARCH_RESULTS]);
    std::string status = jsearchr[MESSAGE_STATUS];
    std::string info = jsearchr[MESSAGE_INFO];
    return SearchResponseMessage(search, results, status, info);
  }

  /**
   * Converts a JSON object representing a GoodbyeMessage to a GoodbyeMessage object
   * @param j JSON object
   * @return GoodbyeMessage
   */
  static GoodbyeMessage parseGoodbye(const JSON &jbye) {
    return GoodbyeMessage();
  }

  /**
   * Detects the message type from a JSON object
   * @param jmsg JSON object
   * @return message type
   */
  static MessageType parseType(const JSON &jmsg) {
    std::string msg = jmsg[MESSAGE_TYPE];
    if (MESSAGE_ADD == msg) {
      return MessageType::ADD;
    } else if (MESSAGE_ADD_RESPONSE == msg) {
      return MessageType::ADD_RESPONSE;
    } else if (MESSAGE_REMOVE == msg) {
      return MessageType::REMOVE;
    } else if (MESSAGE_REMOVE_RESPONSE == msg) {
      return MessageType::REMOVE_RESPONSE;
    } else if (MESSAGE_SEARCH == msg) {
      return MessageType::SEARCH;
    } else if (MESSAGE_SEARCH_RESPONSE == msg) {
      return MessageType::SEARCH_RESPONSE;
    } else if (MESSAGE_GOODBYE == msg) {
      return MessageType::GOODBYE;
    }
    return MessageType::UNKNOWN;
  }

  /**
   * Parses a Message object from JSON, returning in a smart pointer
   * to preserve polymorphism.
   *
   * @param jmsg JSON object
   * @return parsed Message object, or nullptr if invalid
   */
  static std::unique_ptr<Message> parseMessage(const JSON &jmsg) {

    //=============================================================
    // TODO: Add parsing of "remove" and its response
    //=============================================================

    MessageType type = parseType(jmsg);
    switch(type) {
	  case REMOVE: {
			return std::unique_ptr<Message>(new RemoveMessage(parseRemove(jmsg)));
		}
	  case REMOVE_RESPONSE: {
		  return std::unique_ptr<Message>(new RemoveResponseMessage(parseRemoveResponse(jmsg)));
	  }
      case ADD: {
        return std::unique_ptr<Message>(new AddMessage(parseAdd(jmsg)));
      }
      case ADD_RESPONSE: {
        return std::unique_ptr<Message>(new AddResponseMessage(parseAddResponse(jmsg)));
      }
      case SEARCH: {
        return std::unique_ptr<Message>(new SearchMessage(parseSearch(jmsg)));
      }
      case SEARCH_RESPONSE: {
        return std::unique_ptr<Message>(new SearchResponseMessage(parseSearchResponse(jmsg)));
      }
      case GOODBYE: {
        return std::unique_ptr<Message>(new GoodbyeMessage(parseGoodbye(jmsg)));
      }
    }

    return std::unique_ptr<Message>(nullptr);
  }

};

#endif //LAB4_MUSIC_LIBRARY_JSON_H
