savedcmd_/root/chard/charu.mod := printf '%s\n'   charu.o | awk '!x[$$0]++ { print("/root/chard/"$$0) }' > /root/chard/charu.mod
