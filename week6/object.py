from cs50 import get_int

class Student():

    def __init__(self, name, id):
        self.name = name
        self.id = id

    def change_ID(self, id):
        self.id = id

    def change_name(self, name):
        self.name = name

    def printO(self):
        print("This is {} with the id: {}".format(self.name, self.id))

student_1 = Student("estudiante", 150)
student_1.printO()
student_1.change_name(input("A name for the student: "))
student_1.change_ID(get_int("An id for the student: "))
student_1.printO()
