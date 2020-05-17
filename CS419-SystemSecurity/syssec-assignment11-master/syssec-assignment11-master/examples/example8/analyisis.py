#!/usr/bin/env python

import angr

p = angr.Project("./example8")

state = p.factory.entry_state()

sm = p.factory.simulation_manager(state)

sm.explore(find=[0x004006f5], avoid=[0x004006db, 0x004006ee, 0x004006b5, 0x004006c8, 0x004006b5])


s = sm.found[0]


print(s.posix.dumps(1))
print(s.posix.dumps(0))
