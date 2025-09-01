class human:
    def __init__(self, name, age, games, aspect, dreams, hopes):
        self.name = name
        self.age = age
        self.games = games
        self.aspect = aspect
        self.dreams = dreams
        self.hopes = hopes

    def greet(self):
        return f"Hello, my name is {self.name}."
    
    def describe(self):
        return f"I am {self.age} years old, I enjoy {self.games}, and I aspire to {self.dreams}."
    
    def aspirations(self):
        return f"My hopes are to {self.hopes} and I value {self.aspect} in life."
    
    def build(self):
        self = human(char(input("Enter your name: ")),
                     int(input("Enter your age: ")),
                     input("What games do you like? "),
                     input("How's your aspect? Describe it briefly: "),
                     input("What are your dreams? "),
                     input("What are your hopes? "))
    build()
    greet()
    describe()
    aspirations()