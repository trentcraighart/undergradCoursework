#!/usr/bin/env python

import angr

p = angr.Project("./example1")

state = p.factory.entry_state()

sm = p.factory.simulation_manager(state)

"""
        ,=< 0x00400676      7515           jne 0x40068d
        |   0x00400678      0fb645f6       movzx eax, byte [rbp - 0xa] ; example1.c:24         if (b == 'B') {
        |   0x0040067c      3c42           cmp al, 0x42                ; 'B' ; 66
       ,==< 0x0040067e      750d           jne 0x40068d
       ||   0x00400680      0fb645f7       movzx eax, byte [rbp - 9]   ; example1.c:25             if(c == 'C') {
       ||   0x00400684      3c43           cmp al, 0x43                ; 'C' ; 67
      ,===< 0x00400686      7505           jne 0x40068d
      |||   0x00400688      e83affffff     call sym.bug                ; example1.c:26                 bug();
"""
sm.explore(find=0x400688, avoid=[0x40068d])
# found this with rd ./example1 main
# 0x00400688
s = sm.found[0]

print(s.posix.dumps(1))
print(s.posix.dumps(0))
