def generate_syllables(consonants, vowels):
    """ print a list of all CV pairs, given a list of consonants and a list of vowels """
    result = []
    for c in consonants:
        for v in vowels:
            result.append(c + v + "\n")
    return ''.join(result)

c_list = ["g", "n", "d", "r", "m", "b", "s", "0", "j", "ch", "k", "t", "p", "h"]
v_list = ["a", "ya", "eo", "yeo", "o", "yo", "u", "yu", "eu", "i", "ae"]

#print(generate_syllables(c_list, v_list))
with open("rokean_syllables", "w") as f:
    print(generate_syllables(c_list, v_list), file=f)
f.close()
