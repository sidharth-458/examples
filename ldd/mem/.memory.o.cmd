savedcmd_/root/mem/memory.o := x86_64-linux-gnu-ld -m elf_x86_64 -z noexecstack --no-warn-rwx-segments   -r -o /root/mem/memory.o @/root/mem/memory.mod  ; ./tools/objtool/objtool --hacks=jump_label --hacks=noinstr --hacks=skylake --ibt --orc --retpoline --rethunk --sls --static-call --uaccess --prefix=16  --link  --module /root/mem/memory.o

/root/mem/memory.o: $(wildcard ./tools/objtool/objtool)
