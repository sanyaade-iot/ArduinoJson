// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2018
// MIT License

#include <ArduinoJson.h>
#include <catch.hpp>

MsgPackError deserialize(const char* input, size_t len) {
  DynamicJsonDocument doc;

  return deserializeMsgPack(doc, input, len);
}

void checkAllSizes(const char* input, size_t len) {
  REQUIRE(deserialize(input, len) == MsgPackError::Ok);

  while (--len) {
    REQUIRE(deserialize(input, len) == MsgPackError::IncompleteInput);
  }
}

TEST_CASE("deserializeMsgPack() returns IncompleteInput") {
  SECTION("empty input") {
    checkAllSizes("\x00", 1);
  }

  SECTION("fixarray") {
    checkAllSizes("\x91\x01", 2);
  }

  SECTION("array 16") {
    checkAllSizes("\xDC\x00\x01\x01", 4);
  }

  SECTION("array 32") {
    checkAllSizes("\xDD\x00\x00\x00\x01\x01", 6);
  }

  SECTION("fixmap") {
    checkAllSizes("\x81\xA3one\x01", 6);
  }

  SECTION("map 16") {
    checkAllSizes("\xDE\x00\x01\xA3one\x01", 8);
  }

  SECTION("map 32") {
    checkAllSizes("\xDF\x00\x00\x00\x01\xA3one\x01", 10);
  }
}
