from ctypes import *

class HELLO:
	def run(self,program):
		MEMORY = []
		for i in range(0x100):
			MEMORY.append('\x00')
		idx = 0
		f = open(program,'rb')
		code = f.read()
		f.close()

		while(True):
			if(idx >= len(code)):
				exit(1)
			if(code[idx]^0xFF != 0x20):
				exit(1)

			idx += 1
			A = code[idx]
			idx += 1

			if(A == 1):
				B = code[idx]
				idx += 1
				C = code[idx]
				idx += 1
				MEMORY[B] = chr(C)
			elif(A == 2):
				B = code[idx]
				idx += 1
				C = code[idx]
				idx += 1
				temp = MEMORY[B] 
				MEMORY[B] = MEMORY[C]
				MEMORY[C] = temp
			elif(A == 3):
				B = code[idx]
				idx += 1
				C = code[idx]
				idx += 1
				MEMORY[B] = chr(c_ubyte(ord(MEMORY[B])+C).value)
			elif(A == 4):
				B = code[idx]
				idx += 1
				C = code[idx]
				idx += 1 
				MEMORY[B] = chr(c_ubyte(ord(MEMORY[B])).value + ord(c_ubyte(MEMORY[C])).value)
			elif(A == 5):
				B = code[idx]
				idx += 1
				C = code[idx]
				idx += 1
				MEMORY[B] = chr(c_ubyte(ord(MEMORY[B])-C).value)
			elif(A == 6):
				B = code[idx]
				idx += 1
				C = code[idx]
				idx += 1 
				MEMORY[B] = chr(c_ubyte(ord(MEMORY[B])).value - ord(c_ubyte(MEMORY[C])).value)	
			elif(A == 7):
				B = code[idx]
				idx += 1
				C = code[idx]
				idx += 1 
				D = code[idx]
				idx += 1 
				if(MEMORY[B:B+D] == MEMORY[C:C+D]):
					pass
				else:
					print("Incoreect :(")
					exit(1)
			elif(A == 8):
				B = code[idx]
				idx += 1
				C = code[idx]
				idx += 1
				string = ''
				for i in range(C):
					string += MEMORY[B+i]
				print(string)
			elif(A == 9):
				B = code[idx]
				idx += 1
				C = code[idx]
				idx += 1
				data = input()[:C]
				for i in range(len(data)):
					MEMORY[B+i] = data[i]
			else:
				exit(1)

if __name__ == '__main__':
	hello = HELLO()
	hello.run("./program")