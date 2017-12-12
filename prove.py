from z3 import *

r0 = BitVec('r0', 32)
r1 = BitVec('r1', 32)

cr = (r0 << 16) ^ r1

s = Solver()
s.add(ULE(r0, 0xffff))
s.add(UGE(r0, 0x0000))
s.add(ULE(r1, 0xffff))
s.add(UGE(r1, 0x0000))
s.add(ULT(r0, r1))

q = BitVec('q', 32)
s.add(UGE(q, r0))
s.add(ULE(q, r1))

cmp_cap = (q << 16) ^ q
cmp_min = (q << 16)

s.add(
  Not(
    Or(
      And(
        UGT(cr, 0xffff), ULE(cr, cmp_min), ULE(cmp_cap, cr)
      ),
      ULE(q, cr)
    )
  )
)

print(s.check())
