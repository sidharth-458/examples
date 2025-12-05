savedcmd_/root/rtc_try/test/time.mod := printf '%s\n'   time.o | awk '!x[$$0]++ { print("/root/rtc_try/test/"$$0) }' > /root/rtc_try/test/time.mod
