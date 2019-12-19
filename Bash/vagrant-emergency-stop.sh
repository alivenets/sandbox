#!/bin/sh -e

echo "Performing emergency stop of vagrant box..."

VBoxManage startvm $(cat ./.vagrant/machines/default/virtualbox/id) --type emergencystop
