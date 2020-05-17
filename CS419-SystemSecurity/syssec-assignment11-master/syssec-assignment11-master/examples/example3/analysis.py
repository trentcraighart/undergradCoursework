#!/usr/bin/env python

import angr

p = angr.Project("./example3")

state = p.factory.entry_state()

sm = p.factory.simulation_manager(state)

"""
            0x00400674      3c40           cmp al, 0x40                ; '@' ; 64
        ,=< 0x00400676      7e08           jle 0x400680
        |   0x00400678      0fb645f5       movzx eax, byte [rbp - 0xb]
        |   0x0040067c      3c5a           cmp al, 0x5a                ; 'Z' ; 90
       ,==< 0x0040067e      7e07           jle 0x400687
       |`-> 0x00400680      b8ffffffff     mov eax, 0xffffffff         ; -1
       |,=< 0x00400685      eb4f           jmp 0x4006d6
       `--> 0x00400687      0fb645f6       movzx eax, byte [rbp - 0xa] ; example3.c:25     if (b < 'A' || b > 'Z') return -1;
        |   0x0040068b      3c40           cmp al, 0x40                ; '@' ; 64
       ,==< 0x0040068d      7e08           jle 0x400697
       ||   0x0040068f      0fb645f6       movzx eax, byte [rbp - 0xa]
       ||   0x00400693      3c5a           cmp al, 0x5a                ; 'Z' ; 90
      ,===< 0x00400695      7e07           jle 0x40069e
      |`--> 0x00400697      b8ffffffff     mov eax, 0xffffffff         ; -1
      |,==< 0x0040069c      eb38           jmp 0x4006d6
      `---> 0x0040069e      0fb645f7       movzx eax, byte [rbp - 9]   ; example3.c:26     if (c < 'A' || c > 'Z') return -1;
       ||   0x004006a2      3c40           cmp al, 0x40                ; '@' ; 64
      ,===< 0x004006a4      7e08           jle 0x4006ae
      |||   0x004006a6      0fb645f7       movzx eax, byte [rbp - 9]
      |||   0x004006aa      3c5a           cmp al, 0x5a                ; 'Z' ; 90
     ,====< 0x004006ac      7e07           jle 0x4006b5
     |`---> 0x004006ae      b8ffffffff     mov eax, 0xffffffff         ; -1
     |,===< 0x004006b3      eb21           jmp 0x4006d6
     `----> 0x004006b5      0fb645f6       movzx eax, byte [rbp - 0xa] ; example3.c:28     if (b - a == 3) {
      |||   0x004006b9      0fbed0         movsx edx, al
      |||   0x004006bc      0fb645f5       movzx eax, byte [rbp - 0xb]
      |||   0x004006c0      0fbec0         movsx eax, al
      |||   0x004006c3      29c2           sub edx, eax
      |||   0x004006c5      89d0           mov eax, edx
      |||   0x004006c7      83f803         cmp eax, 3                  ; 3
     ,====< 0x004006ca      7505           jne 0x4006d1
     ||||   0x004006cc      e8f6feffff     call sym.bug                ; example3.c:29         bug();
     `----> 0x004006d1      b800000000     mov eax, 0                  ; example3.c:32     return 0;

"""
sm.explore(find=0x4006cc, avoid=[0x004006ae, 0x00400697, 0x00400680])


s = sm.found[0]


print(s.posix.dumps(1))
print(s.posix.dumps(0))
