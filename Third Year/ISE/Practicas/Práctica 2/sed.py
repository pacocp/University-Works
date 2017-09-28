#!/usr/bin/env python
# -*- coding:utf-8 -*-
from sys import argv
import subprocess

print("CHANGING THE FILE...\n")

subprocess.call(['sudo','sed', '-i', "PasswordAuthentication yes\c/PasswordAuthentication no", '/etc/ssh/sshd_config'])

print("RESTARTING THE SERVICE...\n")


subprocess.call(['servive','ssh','restart'])

print("WAITING FOR YOU...\n")

subprocess.call(['sleep','300'])

print("CHANGING THE FILE AGAIN...\n")

subprocess.call(['sudo','sed', '-i', "PasswordAuthentication no\c/PasswordAuthentication yes", '/etc/ssh/sshd_config'])

print("RESTARTING THE SERVICE...\n")


subprocess.call(['servive','ssh','restart'])

print("GOODBYE!\n")
