# 2D list 
# each list inside that list is a "bucket" - bucket number (index) is calculated with the hash function
# multiple entries in same room => collision. that'll be saved as new elements in that insider list
# 
import pprint


class hashTb:

    def __init__(self, rooms, fileName):
        self.rooms = rooms # the total number of slots availanle

        self.table = [ [] for _ in range(rooms)]

        # taking values from the file and insert into the table
        with open(fileName) as db:
            for line in db:
                parts = line.strip().split(":")

                usrName , passWrd = parts
                self.insert(usrName , passWrd) 

        print(parts)

    def _hash(self , key , returnModulo = True):
        if returnModulo:
            return hash(key) % self.rooms # this will be the index
        else:
            return hash(key)

    # Just insert by whatever means possible - doesn't care about duplicate keys or anything
                     # username , #password
    def insert(self , key , val):
        index = self._hash(key)
        bucket = self.table[index] # bucket is the nested list - 

        bucket.append((key , val)) # appends to the key-value pair to that bucket 
        print(f"Inserted : {key} -> Hash : {self._hash(key , False)} -> Index : {index} ")

    def printHT(self):
        print(f"the hash table : ")
        pprint.pprint(self.table)
        print("__________________")

    def delete(self , uName):
        index = self._hash(uName) 
        bucket = self.table[index] 

        for thatIndex , (thatUsrName , thatPasswrd) in enumerate(bucket):
            if thatUsrName == uName:
                del bucket[thatIndex]
                print(f"they username or account of {uName} has been deleted from the table \nAt index:{thatIndex} , and the value it hold {thatPasswrd}")
                return
        
        print(f"that user doesn't exist. Didn't delete ")
    
    def search(self , key):
        bucket = self.table[self._hash(key)] # this bucket may contain many entries cause of collision
        # find the correct key and then return it's value
        for thatKey,thatVal in bucket:
            if thatKey == key:
                print(f"the key {key} has found and the value it holds is {thatVal}")
                return
            
        print(f"Search for smth that exist ")



testHT = hashTb(5 ,"foo")
testHT.printHT()

targetUName = "whatever"
targetPass = "whateversPassword"

testHT.insert(targetUName , "iamBatman")
testHT.insert("whateverNormalGuy" , "iamBatman")
testHT.search(targetUName)
testHT.search("WalterWhite")
testHT.delete("prajwal-56")
testHT.delete("prajwal-56")

# testHT.printHT()
