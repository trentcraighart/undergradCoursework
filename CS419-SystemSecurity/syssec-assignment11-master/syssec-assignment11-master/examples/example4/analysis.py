#!/usr/bin/env python

import angr

p = angr.Project("./example4")

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
        |   0x004006ce      0fb645f5       movzx eax, byte [rbp - 0xb]
        |   0x004006d2      0fbec0         movsx eax, al
        |   0x004006d5      29c2           sub edx, eax
        |   0x004006d7      89d0           mov eax, edx
        |   0x004006d9      83f803         cmp eax, 3                  ; 3
       ,==< 0x004006dc      7407           je 0x4006e5
       ||   0x004006de      b8ffffffff     mov eax, 0xffffffff         ; example4.c:33         return -1; ; -1
      ,===< 0x004006e3      eb28           jmp 0x40070d
      |`--> 0x004006e5      0fb645f7       movzx eax, byte [rbp - 9]   ; example4.c:36     if (c - b != 3) {
      | |   0x004006e9      0fbed0         movsx edx, al
      | |   0x004006ec      0fb645f6       movzx eax, byte [rbp - 0xa]
      | |   0x004006f0      0fbec0         movsx eax, al
      | |   0x004006f3      29c2           sub edx, eax
      | |   0x004006f5      89d0           mov eax, edx
      | |   0x004006f7      83f803         cmp eax, 3                  ; 3
      |,==< 0x004006fa      7407           je 0x400703
      |||   0x004006fc      b8ffffffff     mov eax, 0xffffffff         ; example4.c:37         return -1; ; -1
     ,====< 0x00400701      eb0a           jmp 0x40070d
     ||`--> 0x00400703      e8bffeffff     call sym.bug                ; example4.c:40     bug();
     || |   0x00400708      b800000000     mov eax, 0                  ; example4.c:41     return 0;
     ``-`-> 0x0040070d      488b4df8       mov rcx, qword [rbp - 8]    ; example4.c:43 }
            0x00400711      6448330c2528.  xor rcx, qword fs:[0x28]
        ,=< 0x0040071a      7405           je 0x400721
        |   0x0040071c      e89ffdffff     call sym.imp.__stack_chk_fail

"""
sm.explore(find=[0x00400703, 0x004006cc], avoid=[0x00400680, 0x00400697, 0x004006ae, 0x004006de, 0x004006fc])


s = sm.found[0]


print(s.posix.dumps(1))
print(s.posix.dumps(0))
