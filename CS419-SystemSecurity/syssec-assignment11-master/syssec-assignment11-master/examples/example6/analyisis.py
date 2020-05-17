#!/usr/bin/env python

import angr

p = angr.Project("./example6")

state = p.factory.entry_state()

sm = p.factory.simulation_manager(state)

sm.explore(find=[0x004006a1], avoid=[0x0040068e])


s = sm.found[0]


print(s.posix.dumps(1))
print(s.posix.dumps(0))
