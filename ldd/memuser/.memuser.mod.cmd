savedcmd_/root/memuser/memuser.mod := printf '%s\n'   memuser.o | awk '!x[$$0]++ { print("/root/memuser/"$$0) }' > /root/memuser/memuser.mod
