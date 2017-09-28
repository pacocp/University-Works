#!/bin/bash/

echo "CHANGING THE FILE..." 

sudo sed -i "PasswordAuthentication yes\c/PasswordAuthentication no" /etc/ssh/sshd_config

echo "RESTARTING THE SERVICE..."

service ssh restart 

echo "WAITING FOR YOU..."

sleep 300

echo "CHANGING THE FILE AGAIN..."

sudo sed -i "PasswordAuthentication no\c/PasswordAuthentication yes" /etc/ssh/sshd_config

echo "RESTARTING THE SERVICE..."

service ssh restart 

echo "GOODBYE!"




