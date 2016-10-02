def hello():
    print("Hello, world!")

class Vector3D: 
    def __init__(self, x, y, z):
        self.x = x # Записываем значение переданных аргументов в наш объект
        self.y = y
        self.z = z
    def __str__(self):
        return "({0};{1};{2})".format(self.x, self.y, self.z)
    def __add__(self, other): # обрабатывает ситуацию self + other
        newx = self.x + other.x
        newy = self.y + other.y
        newz = self.z + other.z
        return Vector3D(newx, newy, newz)
    def __mul__(self, other): # умножение
        return Vector3D(self.x * other, self.y * other, self.z * other)
    def __rmul__(self, other):
        return Vector3D(self.x * other, self.y * other, self.z * other)
    def __imul__(self, other): # переопределяем *=
        self.x *= other
        self.y *= other
        self.z *= other
        print("I was multyplied by {0}".format(other))
        return self
    def __sub__(self, other): 
        return self + (other * (-1)) # использование ранее определенных операторов
    def __xor__(self, other): # self ^ other
        return self.x*other.x + self.y*other.y + self.z*other.z
    def __and__(self, other): # self & other
        newx = self.y*other.z-self.z*other.y
        newy = self.z*other.z-self.x*other.z
        newz = self.x*other.y-self.y*other.x
        return Vector3D(newx, newy, newz)
    def lenght(self):
        return (self ^ self) ** (0.5)
    
def tripleProduct(a, b, c):
    return a ^ (b & c)

if __name__ == "__main__":
    print("Это модуль для работы с трехмерным вектором")
