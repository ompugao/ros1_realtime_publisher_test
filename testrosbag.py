import rosbag
import itertools
import pandas as pd
bag = rosbag.Bag('./2021-08-26-18-22-54.bag')
readmsg = bag.read_messages()
readmsg1, readmsg2 = itertools.tee(readmsg, 2)
next(readmsg2) #drop first msg

realintervals = []
receivedintervals = []
for msg1, msg2 in zip(readmsg1, readmsg2):
    realinterval = (msg2.message.data - msg1.message.data).to_nsec() / 1000.0 # msec
    receivedinterval = (msg2.timestamp - msg1.timestamp).to_nsec() / 1000.0
    realintervals.append(realinterval)
    receivedintervals.append(receivedinterval)
dfreal = pd.DataFrame(realintervals)
dfreceived = pd.DataFrame(receivedintervals)
print("sent msg interval")
print("min: %f, max: %f, median: %f"%(dfreal.min(), dfreal.max(), dfreal.median()))
print("received msg interval")
print("min: %f, max: %f, median: %f"%(dfreceived.min(), dfreceived.max(), dfreceived.median()))
from IPython.terminal import embed; ipshell=embed.InteractiveShellEmbed(config=embed.load_default_config())(local_ns=locals())

#from IPython.terminal import embed; ipshell=embed.InteractiveShellEmbed(config=embed.load_default_config())(local_ns=locals())

