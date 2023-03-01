#!/bin/sh

## Permanently-Syncing the current folder to kdabtv:root/qml (my target)
while inotifywait -r -e modify,create,delete,move .; do
    rsync -avz . kdabtv:/root/qml
done

