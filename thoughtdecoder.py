import time

x = input("Choose  a number between 1 - 10: ")

for i in range(10):
    print("Wait, decoding thoughts....." + str(10-i) + " seconds left")
    time.sleep(1)
    
print("You thought about " + str(x))