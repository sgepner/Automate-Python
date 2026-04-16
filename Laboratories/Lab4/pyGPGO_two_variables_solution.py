import numpy as np
from pyGPGO.covfunc import squaredExponential
from pyGPGO.acquisition import Acquisition
from pyGPGO.surrogates.GaussianProcess import GaussianProcess
from pyGPGO.GPGO import GPGO

# pyGPGO maximises, so negate zval if you want the minimum
def f(x, y):
    zval = (x - 45.68) * (x + 85.45) + (y - 58.84) * (y - 25.55)
    return -zval

sexp = squaredExponential()
gp = GaussianProcess(sexp)
acq = Acquisition(mode='ExpectedImprovement')

# Choose bounds that contain the extremum you want to find
param = {
    'x': ('cont', [-100, 100]),
    'y': ('cont', [-100, 100])
}

np.random.seed(23)
gpgo = GPGO(gp, acq, f, param)
gpgo.run(max_iter=20, resume=False)

print("Best parameters found:", gpgo.best)