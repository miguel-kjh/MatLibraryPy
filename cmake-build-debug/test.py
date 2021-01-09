from MatLibraryPy import Matrix

m = Matrix()

m2 = Matrix(3,5)

#m3 = Matrix([1,2,3,4])

t = m2.transpose()
print(m2)
print(m2.rows())
print(m2.columns())
print(m2.size())
print(t)

m2.saveAs("v.vector")

m2 = Matrix("at.matrix")

print(m2)

print(m2 + m2)

print(m2 * m2)

print(5/m2)

inv = m2.inv()
print(inv)

print(m2.get(1,0))
m2.set(1,0,8)
print(m2.get(1,0))
