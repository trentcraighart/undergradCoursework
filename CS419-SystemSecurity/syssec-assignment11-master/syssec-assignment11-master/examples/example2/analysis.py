#!/usr/bin/env python

import angr

p = angr.Project("./example2")

state = p.factory.entry_state()

sm = p.factory.simulation_manager(state)

"""
      |||   0x004006ba      b800000000     mov eax, 0                  ; example2.c:30     return 0;
      ```-> 0x004006bf      488b4df8       mov rcx, qword [rbp - 8]    ; example2.c:32 }
            0x004006c3      6448330c2528.  xor rcx, qword fs:[0x28]
        ,=< 0x004006cc      7405           je 0x4006d3
        |   0x004006ce      e8edfdffff     call sym.imp.__stack_chk_fail

            0x00400674      3c40           cmp al, 0x40                ; '@' ; 64
        ,=< 0x00400676      7e08           jle 0x400680
        |   0x00400678      0fb645f5       movzx eax, byte [rbp - 0xb]
        |   0x0040067c      3c5a           cmp al, 0x5a                ; 'Z' ; 90
       ,==< 0x0040067e      7e07           jle 0x400687
       |`-> 0x00400680      b8ffffffff     mov eax, 0xffffffff         ; -1
       |,=< 0x00400685      eb38           jmp 0x4006bf
       `--> 0x00400687      0fb645f6       movzx eax, byte [rbp - 0xa] ; example2.c:25     if (b < 'A' || b > 'Z') return -1;
        |   0x0040068b      3c40           cmp al, 0x40                ; '@' ; 64
       ,==< 0x0040068d      7e08           jle 0x400697
       ||   0x0040068f      0fb645f6       movzx eax, byte [rbp - 0xa]
       ||   0x00400693      3c5a           cmp al, 0x5a                ; 'Z' ; 90
      ,===< 0x00400695      7e07           jle 0x40069e
      |`--> 0x00400697      b8ffffffff     mov eax, 0xffffffff         ; -1
      |,==< 0x0040069c      eb21           jmp 0x4006bf
      `---> 0x0040069e      0fb645f7       movzx eax, byte [rbp - 9]   ; example2.c:26     if (c < 'A' || c > 'Z') return -1;
       ||   0x004006a2      3c40           cmp al, 0x40                ; '@' ; 64
      ,===< 0x004006a4      7e08           jle 0x4006ae
      |||   0x004006a6      0fb645f7       movzx eax, byte [rbp - 9]
      |||   0x004006aa      3c5a           cmp al, 0x5a                ; 'Z' ; 90
     ,====< 0x004006ac      7e07           jle 0x4006b5
     |`---> 0x004006ae      b8ffffffff     mov eax, 0xffffffff         ; -1
     |,===< 0x004006b3      eb0a           jmp 0x4006bf
     `----> 0x004006b5      e80dffffff     call sym.bug                ; example2.c:28     bug();
      |||   0x004006ba      b800000000     mov eax, 0                  ; example2.c:30     return 0;
      ```-> 0x004006bf      488b4df8       mov rcx, qword [rbp - 8]    ; example2.c:32 }
            0x004006c3      6448330c2528.  xor rcx, qword fs:[0x28]
        ,=< 0x004006cc      7405           je 0x4006d3
        |   0x004006ce      e8edfdffff     call sym.imp.__stack_chk_fail

"""

sm.explore(find=0x4006b5, avoid=[0x4004bf])

s = sm.found[0]

print(s.posix.dumps(1))
print(s.posix.dumps(0))
