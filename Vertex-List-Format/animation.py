#!/usr/bin/python

import os

def drange(start, stop, step):
  r = start
  while r < stop:
    yield r
    r += step

def principal():
  path=os.path.join(os.getcwd(),"Test")
  os.system("make clear")
  os.system("make indent")
  os.system("make")
  number=1
  lista=drange(0,8,0.02)
  for li in lista:
    os.system("./a.out "+path+"/"+str(number)+".ppm "+str(li)+" "+str(li)+" "+str(li)+" "+"540 600 400")
    number=number+1
  aux=li
  lista=drange(0,8,0.02)
  for li in lista:
    os.system("./a.out "+path+"/"+str(number)+".ppm "+str(aux+li)+" "+str(aux)+" "+str(aux)+" "+"540 600 400")
    number=number+1
  aux2=aux+li
  lista=drange(0,8,0.02)
  for li in lista:
    os.system("./a.out "+path+"/"+str(number)+".ppm "+str(aux2)+" "+str(aux+li)+" "+str(aux)+" "+"540 600 400")
    number=number+1
  lista=drange(0,8,0.02)
  for li in lista:
    os.system("./a.out "+path+"/"+str(number)+".ppm "+str(aux2)+" "+str(aux2)+" "+str(aux+li)+" "+"540 600 400")
    number=number+1
  lista2=range(400,1080,2)
  for li2 in lista2:
    os.system("./a.out "+path+"/"+str(number)+".ppm "+str(aux2)+" "+str(aux2)+" "+str(aux2)+" "+"540 600 "+str(li2))
    number=number+1
  lista2=range(1080,400,2)
  for li2 in lista2:
    os.system("./a.out "+path+"/"+str(number)+".ppm "+str(aux2)+" "+str(aux2)+" "+str(aux2)+" "+"540 600 "+str(li2))
    number=number+1
  lista2=range(540,840)
  for li2 in lista2:
    os.system("./a.out "+path+"/"+str(number)+".ppm "+str(aux2)+" "+str(aux2)+" "+str(aux2)+" "+str(li2)+" 600 400")
    number=number+1
  lista2=range(840,540)
  for li2 in lista2:
    os.system("./a.out "+path+"/"+str(number)+".ppm "+str(aux2)+" "+str(aux2)+" "+str(aux2)+" "+str(li2)+" 600 400")
    number=number+1


quit(principal())
