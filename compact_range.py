def dump(r):
  print hex(r[0])
  print hex(r[1])
  print hex(compact(r))

def compact(r):
  return (r[0] << 16) ^ r[1]

def in_compact_range(cr, i):
  cmp_cap = (i << 16) ^ i
  cmp_min = (i << 16)
  return (cr > 65535 and cr <= cmp_min and cmp_cap <= cr) or (i <= cr)

def in_range(r, i):
  return r[0] <= i and i <= r[1]

