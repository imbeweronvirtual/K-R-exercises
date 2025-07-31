def check_sum(card_number):
    i = len(card_number) - 1
    sum_of_all = 0
    is_second = False

    while i >= 0:
        digit = int(card_number[i])
        if is_second:
            digit *= 2
            if digit > 9:
                digit -= 9
        sum_of_all += digit
        is_second = not is_second
        i -= 1
    
    return (sum_of_all % 10) == 0

card_number = input("Number: ")

match len(card_number):
    case 16:
        if (int(card_number[0]) == 4 and check_sum(card_number)):
            print("VISA")
        elif ((int(card_number[:2]) in range(51, 56)) and check_sum(card_number)):
            print("MASTERCARD")
        else:
            print("INVALID")
    case 15:
        if (int(card_number[:2]) in (34, 37) and check_sum(card_number)):
            print("AMEX")
        else:
            print("INVALID")
    case 13:
        if (int(card_number[:1]) == 4 and check_sum(card_number)):
            print("VISA")
        else:
            print("INVALID")
    case _:
        print("INVALID")
