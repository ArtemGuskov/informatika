import array

def positive_ell(arr):
    count = 0
    for i in arr:
        if int(i) > 0:
            count += 1  
    return count

massivA = list(input().split(","))
massivB = list(input().split(","))

count_positive_el_A = positive_ell(massivA)
count_positive_el_B = positive_ell(massivB)
 
if massivA > massivB:
    print(massivB, count_positive_el_B)
    print(massivA, count_positive_el_A)
elif massivA < massivB:
    print(massivA, count_positive_el_A)
    print(massivB, count_positive_el_B)
else:
    print(massivA or massivB, count_positive_el_A or count_positive_el_B) 