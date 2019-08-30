#!/bin/sh
protoc -I=./ --cpp_out=./ addressbook.proto
