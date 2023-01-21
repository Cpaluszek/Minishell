#!/bin/bash
NAME=minishell

# Find the process ID
PID=$(ps -ef | grep ./$NAME | grep -v grep | awk '{print $2}')

# Use the PID to list all the open file descriptors for the process
lsof -p $PID