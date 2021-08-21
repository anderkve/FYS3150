from random import random, randint

for iteration in range(1,1001):
    result_string =  "Iteration {}: ".format(iteration)

    r1 = random()

    if 0.1 < r1 < 0.15:
        r2 = randint(1,3)
        if r2 == 1:
            result_string += "Error 1: Ran out of memory."
        elif r2 == 2:
            result_string += "Error 2: Ooops, got distracted by a cute kitten. Sorry about that. ...Oh, hi there kitty! Here kitty-kitty!"
        elif r2 == 3:
            result_string += "Error 3: Oh no."

    else:
        result = 100 * r1
        if random() < 0.5:
            result *= -1

        result_string += "{:.5e}".format(result)

    print(result_string)
