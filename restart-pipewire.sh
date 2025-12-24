#!/bin/dash
pkill pipewire
sleep 1
pipewire &
sleep 2 # for some reason it takes long to stop and start
pkill -RTMIN+6 dwmblocks
