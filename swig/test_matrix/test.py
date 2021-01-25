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

load_matrix = matrix.matrix("output.txt")

matrix.output(load_matrix)

test_sum = matrix.matrix([[0,0,0,0],[0,0,0,0]])

test_sum = matrix.__add__(c,c_subs)

print("\nSe suma una matriz con valores 100 con otra con valores 100")
matrix.output(test_sum)

test_sum = matrix.__sub__(test_sum,c)

print("\nSe resta a la matrix con valores 200, una matriz con valores 100: ")
matrix.output(test_sum)

test_mul = matrix.matrix([[5,5,5,5],[5,5,5,5]])

test_mul = matrix.__mul__(5,test_mul)

print("\nSe multiplica una matrix 2x4 definida con valor 5 por 5: ")
matrix.output(test_mul)

test_mul = matrix.__mul__(test_mul,2)

print("\nEl resultado de multiplicar la matrix anterior por 2: ")
matrix.output(test_mul)

test_mult_matrix = matrix.matrix([[2,2],[2,2],[2,2],[2,2]])

print("\nSe multiplica la matriz anterior con una matriz 4x2 con valores 2 ")
test_mul = matrix.__mul__(test_mul,test_mult_matrix)

matrix.output(test_mul)

test_div = matrix.matrix([[10,10],[10,10]])

print("\nMatriz de valores 10, dividido entre 2: ")
test_div = matrix.__div__(test_div,2)

matrix.output(test_div)

print("\nMatriz anterior, dividido entre 2: ")
test_div = matrix.__div__(2,test_div)

matrix.output(test_div)