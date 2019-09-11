import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import seaborn as sb

def run():
    a = np.random.rand(16, 16)
    print(a)
    sb.heatmap(a)
    	
    plt.show()

if __name__ == "__main__":
    run()