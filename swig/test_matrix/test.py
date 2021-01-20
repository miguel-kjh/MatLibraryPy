import matrix

a = matrix.base_matrix(1)
x = a.getFractionalDigits()
print(x)
a.setFractionalDigits(5)
print(a)
print(a.getFractionalDigits())

print(a.getFormat())
a.setFormat(matrix.scientific)
print(a.getFormat())