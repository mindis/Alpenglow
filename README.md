# Alpenglow

### Requirements:
- Anaconda + python3 environment

### Installation:
- `cd Alpenglow`
- `conda install libgcc`
- `pip install .`

### Development:
- For faster recompilation, use `export CC="ccache cc"`
- To enable compilation on 4 threads for example, use `echo 4 > .parallel`
- Reinstall modified version using `pip install --upgrade --force-reinstall --no-deps .`
- To build and use in the current folder, use `pip install --upgrade --force-reinstall --no-deps -e .` and `export PYTHONPATH="$(pwd)/python:$PYTHONPATH"`

### Example usage:
- Sample dataset: http://info.ilab.sztaki.hu/~fbobee/alpenglow/alpenglow_sample_dataset

```python
import alpenglow as ag
from alpenglow.experiments import FactorModelExperiment
import pandas as pd
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt

data = pd.read_csv("/path/to/sample_dataset")

factor_model_experiment = FactorModelExperiment(
    top_k=100,
    seed=254938879,
    dimension=10,
    learning_rate=0.14,
    negative_rate=100
)
fac_rankings = factor_model_experiment.run(data, verbose=True)
fac_results = ag.NdcgScore(fac_rankings)
fac_results.time_frame(60 * 60 * 24).plot()
plt.savefig("factor.png")
```
