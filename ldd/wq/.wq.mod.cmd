savedcmd_/root/wq/wq.mod := printf '%s\n'   wq.o | awk '!x[$$0]++ { print("/root/wq/"$$0) }' > /root/wq/wq.mod
