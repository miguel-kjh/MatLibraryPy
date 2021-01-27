from MatLibraryPy import Matrix, Vector
import numpy as np
from time import time
import pandas as pd

def test_mat():

	m = Matrix()

	m2 = Matrix(3,5)

	#m3 = Matrix([1,2,3,4])

	t = m2.transpose()
	print(m2)
	print(m2.rows())
	print(m2.columns())
	print(m2.size())
	print(t)

	m2.saveAs("test.matrix")

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

	mr = Matrix([[1.5,2],[5,6],[3,9.9]])

	print(mr == m2)

	mr2 = Matrix(mr)
	print(mr2)

	print(mr2 == mr)
	
def test_vec():
 	v1 = Vector(3)
 	v2 = Vector([1,2,3])
 	print(v2)
 	v2.saveAs("v.vector")
 	v3 = Vector("v.vector")
 	print(v3)
 	print(v3.size())
 	print(v3.isEmpty())
 	v1.define(10)
 	print(v1)
 	v1 += v2
 	print(v1)
 	print(v1.get(1))
 	v1.set(1,5)
 	print(v1)
 	print(v1 + v2)
 	print("suma numero", v1 + 6)
 	print(v1 - v2)

def test_time():

	def get_time_mult(rag):
		l = []
		repeat = 10
		for n in rag:
			m = Matrix(list(np.random.rand(n,n)))
			tr = 0
			for _ in range(repeat):
				t0 = time()
				_ = m*m
				tr += time() - t0
			l.append(tr / repeat)
		return l

	def get_time_sum(rag):
		l = []
		repeat = 10
		for n in rag:
			m = Matrix(list(np.random.rand(n,n)))
			tr = 0
			for _ in range(repeat):
				t0 = time()
				_ = m+m
				tr += time() - t0
			l.append(tr / repeat)
		return l

	def get_time_save(rag):
		l = []
		repeat = 10
		for n in rag:
			m = Matrix(list(np.random.rand(n,n)))
			tr = 0
			for _ in range(repeat):
				t0 = time()
				m.saveAs("test.matrix")
				tr += time() - t0
			l.append(tr / repeat)
		return l

	def get_time_inv(rag):
		l = []
		repeat = 10
		for n in rag:
			m = Matrix(list(get_matrix(n)))
			tr = 0
			for _ in range(repeat):
				t0 = time()
				m.inv()
				tr += time() - t0
			l.append(tr / repeat)
		return l

	def get_matrix(n):
		while True:
			m = np.random.rand(n,n)
			if np.linalg.det(m) != 0:
				break
		return m


	df = {}
	rag = list(range(5,150,5))
	df['Size'] = rag
	df['Mult'] = get_time_mult(rag)
	df['Sum']  = get_time_sum(rag)
	df['Inv']  = get_time_inv(rag)
	df['Save'] = get_time_save(rag)
	df = pd.DataFrame(df)
	df.to_csv("pruebas_boost.csv")
 	
 	
line = "#"*10 
print(line, "test vector", line)	
test_vec()
print(line, "test matrix", line)
test_mat()
test_time()
 	
 
