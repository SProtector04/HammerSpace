import random

compliments = [ "Have a great day!", "God bless your business!", 
               "Don't kill or be killed!", "You're our pride and joy!", 
               "The light in your heart shines so powerful! We're getting erradiated!",
               "You're strong, tough and infinite!", "You're all capable!",
               "KEEEP ON LIVIN' NO MATTER WHAT!!!", "The meaning of life is you!"]

def main():
    global acceptance
    acceptance = input("Do you want a compliment? (Answer Yes or No) ")
    output_compliment = random.choice(compliments)
    if acceptance == "Yes":
        print(f"With love: {output_compliment}")
    elif acceptance == "No":
        print("Then go awaaaaaaaaayyy, byyyyyyyyyeee!!!")
    else:
        print("What's wrong with you kiddo?")
        main()
        


main()