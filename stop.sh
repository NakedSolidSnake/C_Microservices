#!/bin/bash

echo Killing c_service...
kill -9 `pgrep c_service`

echo Killing go_service...
kill -9 `pgrep go_service`

echo Killing python_service...
kill -9 `pgrep python`

echo Killing ruby_service...
kill -9 `pgrep ruby`

echo Killing rust_service...
kill -9 `pgrep rust_service`

echo Killing java_service...
kill -9 `pgrep java`

echo Killing gateway...
kill -9 `pgrep gateway`