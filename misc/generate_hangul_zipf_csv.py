# Written by ECGaebler (except the function RangeLCM2, more on that later)
# 2021.05.30

def main():
    """ Generates a list of Hangul characters with their frequency in a zipf distribution """
    # This Hangul list, ordered by frequency, is from the following site:
    # https://observablehq.com/@pentacular/high-frequency-hangul-cards
    hangul_list = ["다","이","는","에","을","의","지","로","가","고",
                   "한","하","기","은","서","를","대","사","도","시",
                   "해","수","인","자","있","으","정","리","전","부",
                   "장","어","원","일","들","과","아","나","상","했",
                   "만","보","국","주","그","제","스","게","위","경",
                   "적","성","구","회","라","것","공","선","등","동",
                   "면","니","소","여","문","관","중","업","진","비",
                   "조","내","와","개","화","신","계","우","오","안",
                   "마","유","할","년","모","무","명","행","연","통",
                   "치","용","세","산","실","당","었","재","발","방",
                   "생","거","미","간","금","터","단","된","영","분",
                   "트","러","드","차","교","후","되","체","학","운",
                   "입","난","요","며","점","려","월","민","출","역",
                   "야","현","타","식","최","반","데","물","까","습",
                   "강","감","결","예","두","없","않","건","속","청",
                   "표","바","달","양","히","직","력","설","때","호",
                   "각","매","심","임","던","작","남","승","울","받",
                   "번","르","포","올","추","불","음","날","김","법",
                   "프","종","았","권","본","더","외","됐","처","투",
                   "합","말","석","약","박","록","저","따","근","배"]

    freq_multiplier = create_multiplier()
    csv_lines = []
    for i in range(len(hangul_list)):
        freq = freq_multiplier//(i+1)
        current_line = hangul_list[i] + ',' + str(freq) + '\n'
        csv_lines.append(current_line)
        #print(current_line)

    file = open("hangul_with_freq.csv", 'w')
    file.writelines(csv_lines)
    file.close
               

# I wanted the frequency of each character to be an int, so I generated a number
# appropriate for creating a zipf distribution for 200 items. I decided to build
# this multiplier by modifying the LCM of the range 1-200.
def create_multiplier():
    """ generates a multiplier from the lcm of the range 1-200, excluding the primes 11 or greater """
    exclude = [11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83,
               89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157,
               163, 167, 173, 179, 181, 191, 193, 197, 199]

    # Generate the LCM of the range 1-200
    lcm = RangeLCM2(200)
    for prime in exclude:
        while (lcm%prime == 0):
            lcm = lcm // prime

    # Factor out the 2's and 5's
    while (lcm%2 == 0):
        lcm = lcm//2
    while (lcm%5 == 0):
        lcm = lcm // 5

    # Put a few of them back
    multiplier = lcm * 2**3 * 5

    return multiplier


#I did not write RangeLCM2! I found it here:
#https://stackoverflow.com/questions/185781/finding-the-lcm-of-a-range-of-numbers
def RangeLCM2(last):
    factors = list(range(last+1))
    result = 1
    for n in range(last+1):
        if factors[n] > 1:
            result *= factors[n]
            for j in range(2*n, last+1, n):
                factors[j] //= factors[n]
    return result


main()
