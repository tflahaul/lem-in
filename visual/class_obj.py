# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    graph.py                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abrunet <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/17 20:16:57 by abrunet           #+#    #+#              #
#    Updated: 2019/05/31 16:44:06 by abrunet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

from matplotlib.backend_tools import ToolBase, ToolToggleBase
import matplotlib.animation as animation
import matplotlib.pyplot as plt
from draw import draw_graph

def get_ants_per_path():
    dic = {}
    i = 1
    with open('ants.txt', 'r') as f:
        lines = f.readlines()
        for line in lines:
            dic[i] = int(line)
            i += 1
    return (dic)

class Ants(ToolToggleBase):
    description = "Ants"
    default_toggled = False
    image = r"fire-ant-png-4.png"

    def __init__(self, *args, fig, interval, paths, G, options, colors, **kwargs):
        self.paths = paths
        self.colors = colors
        self.G = G
        self.options = options
        self.ants = get_ants_per_path()
        self.length = self.ants[1] + len(paths[1]) + 2
        self.fig = fig
        self.interval = interval
        super().__init__(*args, **kwargs)
    
    def enable(self, *args):
        self.optimum_path(True)

    def disable(self, *args):
        self.optimum_path(False)

    def optimum_path(self, state):
        for ax in self.figure.get_axes():
            ax.clear()
        if state == True:
            def update(i):
                for ax in self.figure.get_axes():
                    ax.clear()
                    ax.set_title(self.description)
                draw_graph(0, self.G, self.options, None, None, self.colors)
                for n in range(len(self.paths)):
                    if self.ants[n + 1] - i >= 0:
                        nodelist = self.paths[n][(i - i):(i + 1)]
                    else:
                        nodelist = self.paths[n][(i - self.ants[n + 1] - 1):(i + 1)]
                    edgelist = [nodelist[k:k+2] for k in range(len(nodelist) - 1)]
                    draw_graph(3, self.G, self.options, nodelist, edgelist, self.colors)
                plt.gca().invert_yaxis()
                self.figure.canvas.draw()
            ani = animation.FuncAnimation(self.fig, update, frames=self.length, interval=self.interval, repeat=False)
        else: 
            draw_graph(0, self.G, self.options, None, None, self.colors)
        plt.gca().invert_yaxis()
        self.figure.canvas.draw()

class Optimum(ToolToggleBase):
    description = "optimum paths"
    default_toggled = False

    def __init__(self, *args, paths, G, options, colors, **kwargs):
        self.length = len(paths[len(paths) - 1])
        self.paths = paths
        self.colors = colors
        self.G = G
        self.options = options
        super().__init__(*args, **kwargs)
    
    def enable(self, *args):
        self.optimum_path(True)

    def disable(self, *args):
        self.optimum_path(False)

    def optimum_path(self, state):
        for ax in self.figure.get_axes():
            ax.clear()
        if state == True:
            ax.set_title(self.description)
            draw_graph(0, self.G, self.options, None, None, self.colors)
            i = self.length
            for n in range(len(self.paths)):
       #     for n in range(len(self.paths) - 1):
                nodelist = self.paths[n][(i - i):(i + 1)]
                edgelist = [nodelist[k:k+2] for k in range(len(nodelist) - 1)]
                draw_graph(2, self.G, self.options, nodelist, edgelist, self.colors)
        else: 
            draw_graph(0, self.G, self.options, None, None, self.colors)
        plt.gca().invert_yaxis()
        self.figure.canvas.draw()


        

class Shortest(ToolToggleBase):
    description = "shortest path"
    default_toggled = False

    def __init__(self, *args, paths, G, options, colors, **kwargs):
        self.length = len(paths[0])
        self.paths = paths
        self.colors = colors
        self.G = G
        self.options = options
        super().__init__(*args, **kwargs)

    def enable(self, *args):
        self.shortest_path(True)

    def disable(self, *args):
        self.shortest_path(False)

    def shortest_path(self, state):
        for ax in self.figure.get_axes():
            ax.clear()
        if state == True:
            ax.set_title(self.description)
            draw_graph(0, self.G, self.options, None, None, self.colors)
            i = self.length
            nodelist = self.paths[0][(i - i):(i + 1)]
            edgelist = [nodelist[k:k+2] for k in range(len(nodelist) - 1)]
            draw_graph(1, self.G, self.options, nodelist, edgelist, self.colors)
        else: 
            draw_graph(0, self.G, self.options, None, None, self.colors)
        plt.gca().invert_yaxis()
        self.figure.canvas.draw()
