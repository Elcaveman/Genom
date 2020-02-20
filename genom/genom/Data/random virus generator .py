from random import choice , randint

NUCLE = ['A' ,'C' , 'G' , 'T']

MAX_LIGNES = 40

MAX_LENGTH = 200

MIN_LENGTH = 100

elements = []

for i in range(MAX_LIGNES):
    lent = randint(MIN_LENGTH,MAX_LENGTH);
    st = ""
    for j in range(lent):
        st += choice(NUCLE)
    elements.append(st)

elements.sort()
f = open("virus db.txt","w")
i=0
for elt in elements:
    f.write(elt+"\n")
    i+=1
f.close()
