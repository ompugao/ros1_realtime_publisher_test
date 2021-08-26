import pandas as pd

df = pd.read_csv('./timepoints.csv', header=None)
from IPython.terminal import embed; ipshell=embed.InteractiveShellEmbed(config=embed.load_default_config())(local_ns=locals())

# received
tsreceived = []
for t1, t2 in zip(df[0], df[0][1:]):
    tsreceived.append(t2 - t1)
dfreceived = pd.DataFrame(tsreceived)

tsreal = []
for t1, t2 in zip(df[1], df[1][1:]):
    tsreal.append(t2 - t1)
dfreal = pd.DataFrame(tsreal)
print("sent msg interval")
print("min: %f, max: %f, median: %f"%(dfreal.min(), dfreal.max(), dfreal.median()))
print("received msg interval")
print("min: %f, max: %f, median: %f"%(dfreceived.min(), dfreceived.max(), dfreceived.median()))
