savedcmd_/root/mem/memory.mod := printf '%s\n'   mem.o fops.o | awk '!x[$$0]++ { print("/root/mem/"$$0) }' > /root/mem/memory.mod
