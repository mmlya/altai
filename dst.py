#!/usr/bin/python

from ete2 import Tree

print("\n\n Starting tree processing\n\n")
f=open('res','a')
t = Tree("tree.tre")
t1 = Tree("samplAA.phy_phyml_tree.txt")
nms = t.get_leaf_names()
nms1 = t1.get_leaf_names()
s1 = []
s2 = []
s11 = []
s12 = []
for s in nms:
  if s[2] == '_':
    s1.append(s)
  if s[2] == 'e':
    s2.append(s)
for s in nms1:
  if s[2] == '_':
    s11.append(s)
  if s[2] == 'e':
    s12.append(s)
n1=t.get_common_ancestor(s1)
n2=t.get_common_ancestor(s2)
n11=t1.get_common_ancestor(s11)
n12=t1.get_common_ancestor(s12)
d1=t.get_distance(n1,n2)
d11=t1.get_distance(n11,n12)
d2=t.get_distance(n1,'OUTGROUP')
d3=t.get_distance(n2,'OUTGROUP')
d12=t1.get_distance(n11,'OUTGROUP')
d13=t1.get_distance(n12,'OUTGROUP')
f.write("%f\t%f\t%f\t%f\t%f\t%f\n" %(d1,d2,d3,d11,d12,d13))
f.close()
