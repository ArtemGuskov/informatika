def arifm_mean_sets_intersection(a,b):
    a_b = a & b
    c = 0
    for i in a_b:
        c+=int(i)
    return c/len(a_b)
setA = set(input().split())
setB = set(input().split())
print(arifm_mean_sets_intersection(setA,setB))