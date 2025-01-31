import pandas as pd
import matplotlib.pyplot as plt

data = pd.read_csv("results.csv")

plt.figure(figsize=(10, 6))
plt.plot(data['x'], data['f(x)'], label='f(x) = log10(x)', color='blue')
plt.plot(data['x'], data['P(x)'], label='Lagrange Polynomial', linestyle='--', color='red')
plt.xlabel('x')
plt.ylabel('y')
plt.title('Інтерполяція за методом Лагранжа')
plt.legend()
plt.grid()
plt.show()
