import matplotlib.pyplot as plt
import numpy as np


dimensions  = [2,        3,        4,       5,        6,        7,        8       ]
runtime_10  = [2.3e-05,  3.4e-05, 3.5e-05,  4.2e-05,  5.8e-05,  6.2e-05,  4.8e-05 ]
runtime_50  = [3e-05,    6.3e-05, 0.000186, 0.000832, 0.003005, 0.009608, 0.03245 ]
runtime_100 = [3.6e-05,  7.8e-05, 0.000298, 0.001947, 0.009298, 0.04809,  0.2151  ]
runtime_500 = [0.000116, 0.00021, 0.000907, 0.007799, 0.06736,  0.876,    9.933]        



plt.plot(dimensions, runtime_10)
plt.plot(dimensions, runtime_50)
plt.plot(dimensions, runtime_100)
plt.plot(dimensions, runtime_500)
plt.legend(["10 Datenpunkte", "50 Datenpunkte", "100 Datenpunkte",  "500 Datenpunkte"])
plt.xlabel("Dimensionen")
plt.ylabel("Laufzeit in Sekunden")
plt.show()


'''
Command zur Generierung von Daten und Berechnung der konvexen Hülle:
rbox 500 D8 | qconvex s

'''
