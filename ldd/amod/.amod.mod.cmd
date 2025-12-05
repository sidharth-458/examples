savedcmd_/root/amod/amod.mod := printf '%s\n'   amod.o | awk '!x[$$0]++ { print("/root/amod/"$$0) }' > /root/amod/amod.mod
