#!/usr/bin/env python

import angr

p = angr.Project("./example7")

state = p.factory.entry_state()

sm = p.factory.simulation_manager(state)

sm.explore(find=[0x004006bc], avoid=[0x004006b5 ,0x004006a2, 0x0040068f])


s = sm.found[0]


print(s.posix.dumps(1))
print(s.posix.dumps(0))
