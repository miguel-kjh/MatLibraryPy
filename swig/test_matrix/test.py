import matrix
import sys
# Probamos funcionalidad de la clase base_matrix
a = matrix.matrix(5,3)
x = a.getFractionalDigits()
print(x)
a.setFractionalDigits(5)
print(a)
print(a.getFractionalDigits())

print(a.getFormat())
a.setFormat(matrix.scientific)
print(a.getFormat())

# Probamos las funcionalidades de la clase matrix
print("El tamaño de la matriz a: ", a.size())
print("Las filas de la matriz a: ", a.rows())
print("Las columnas de la matriz a: ", a.columns())

b = matrix.matrix([1.0,2.5,3.3])

print("El tamaño de la matriz b: ", b.size())
print("Las filas de la matriz b: ", b.rows())
print("Las columnas de la matriz b: ", b.columns())

c = matrix.matrix([[1,2,4,2],[2,3,1,1]])

print("El tamaño de la matriz c: ", c.size())
print("Las filas de la matriz c: ", c.rows())
print("Las columnas de la matriz c: ", c.columns())

c_sum = matrix.matrix([[10,10,10,10],[10,10,10,10]])
c_subs = matrix.matrix([[100,100,100,100],[100,100,100,100]])

matrix.output(c)

c += c_sum

matrix.output(c)

c -= c_subs

matrix.output(c)

c_sum *= 2

matrix.output(c_sum)


c = c_subs

matrix.output(c)

print(c == c)
print(c == c_sum)
print(c == c_subs)

c.save_as("output.txt")