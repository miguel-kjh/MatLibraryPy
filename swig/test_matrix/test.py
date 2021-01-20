import matrix

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