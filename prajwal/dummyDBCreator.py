import random 
                                        # removes or add last couple numbers in the password
def generateAccs(filename , numOfAccs , makeItCollidable = True):
    
    fNames = ["Walter" , "Jesse" , "Rick" , "Hank" , "Jhon", "Elliot" , "Martha" , "Summer" , "Morty" , "Jerry" , "Beth" , "Peter", "Bruce" , "Mark" , "Elon" , "Epstien" ]
    lNames = ["White" , "Pinkman" , "Sanchez" , "Schrader" , "Doe", "Alderson" , "Huffman" , "Smith" , "Parker", "Wayne" , "Zuckerber" , "Musk" , "Jeffery"]
    passwords = ["8008135" , "password" , "strongPassword" , "winterIsComing" , "qwerty", "0000" , "11111" , "qwertyuiop" , "Avengers" ,]

    with open(filename , "w") as f:
        for i in range(numOfAccs):
            
            # Username = firstname + lastname + XX
            userName = f"{random.choice(fNames)}{random.choice(lNames)}{random.randint(0,99)}"
            
            if makeItCollidable:
                passwrd = f"{random.choice(passwords)}"
            else:
                passwrd = f"{random.choice(passwords)}{random.randint(0,99)}"

            line = userName + ":"+ passwrd
            f.write(f"{line}\n")
            print(f"username : {userName} : password {passwrd}")

generateAccs("foo" , 16 )