import matplotlib
matplotlib.rcParams["toolbar"] = "toolmanager"
import matplotlib.pyplot as plt
from matplotlib.backend_tools import ToolBase, ToolToggleBase

class Ants(ToolToggleBase):
    description = "ants"
    default_toggled = False
    image = r"fire-ant-png-4.png"

    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        
    def enable(self, *args):
        self.prt_new(True)

    def disable(self, *args):
        self.prt_new(False)

    def prt_new(self, state):
        if state == True:
            print("click!")
            self.disable()

fig = plt.figure()
ax = fig.add_subplot(111)
ax.plot([1, 2, 3], label="legend")
ax.legend()
tm = fig.canvas.manager.toolmanager
tb = fig.canvas.manager.toolbar
tm.add_tool('Ants', Ants)
tm.remove_tool('subplots')
tb.add_tool('Ants', 'navigation', 1)

plt.show()
