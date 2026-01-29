# there's keys 
# take a  array/matrix or whatver and init all the entries with 0
# take multiple hashes of the keys and depending on the hashes generated - flip the values in the matrix from 0 to 1   
# do this for all the hashes generated 


# to generate multiplpe hash - use salting instead of using the same hash - but add a value at the end of the string
    # same hash fn -> different keys

class BloomFilter:
    
    def __init__(self , size , numOfHashesToBeGenerated = 3):
        self.size = size
        self.numOfHashesToBeGenerated = numOfHashesToBeGenerated
        self.bitArray = [0] * size # number of 
        
    def getHashOf(self, item ): # uses the same hash fn , but the key is different from one another
        indeces = []
        
        for i in range(self.numOfHashesToBeGenerated):
            saltedString = item + str(i)
            hashIndex = hash(saltedString) % self.size
            print(f"hash computed for the string {saltedString} - Hash :{hash(saltedString)} - index : {hashIndex}")
            indeces.append(hashIndex)
        return indeces
    
    def updateBitArray(self , key ):
        
        for i in self.getHashOf(key):
            self.bitArray[i] = 1

        print(f"The bit array {self.bitArray}")

    def search(self, key):
        indices = self.getHashOf(key) # this is the list containing the indices of the hash
        
        for i in indices:
            if self.bitArray[i] == 0:
                return "Nope. It doesn't exist"

        return "Yeah ! that may exist"
    

# mess 
bolm = BloomFilter(size=10)

bolm.getHashOf("prajwal")
print(bolm.search("foo"))