#!/bin/bash

kill -9 `pgrep gateway`
killall ./service
