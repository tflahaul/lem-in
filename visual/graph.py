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

import networkx as nx
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import color as c
from options import get_options


def set_colors(color):
    if color == 'holy_graph':
        return (c.holy_graph)
    elif color == 'city':
        return (c.city)
    else:
        return (c.default)

def get_ants_per_path():
    dic = {}
    i = 1
    with open('ants.txt', 'r') as f:
        lines = f.readlines()
        for line in lines:
            dic[i] = int(line)
            i += 1
    return (dic)

def graph(G, coord, paths, data, color):

    #reset paths accounting for data['init'], set animation data
    ants = get_ants_per_path()
    colors = set_colors(color)
    shrtlen = len(paths[0])
    frames = shrtlen + len(paths[len(paths) - 1])
    steps = ants[1] + len(paths[1])
    interval = 10 if (data['vertices'] >= 1000) else 500

    # set subplots
    fig, ax = plt.subplots(figsize=(23, 13))
    options = get_options(G, data['vertices'], ax, coord)

    def update(i):
        ax.clear()
        plt.gca().invert_yaxis()

        # draw background graph
        nx.draw_networkx_edges(G, **options, edge_color=colors['edge_std'])
        nx.draw_networkx_nodes(G, **options, node_color=colors['node_std'])
        
        # draw shortest path
        if (i and i < shrtlen):
            nodelist = paths[0][(i - i):(i + 1)]
            edgelist = [nodelist[k:k+2] for k in range(len(nodelist) - 1)]
            nx.draw_networkx_nodes(G, **options, nodelist=nodelist, node_color=colors['short'])
            nx.draw_networkx_edges(G, **options, edgelist=edgelist, edge_color=colors['short'])
            ax.set_title("SHORTEST PATH")

        # draw optimal paths 
        if (i and shrtlen <= i < frames):
            idx = i - shrtlen
            for n in range(len(paths) - 1):
                nodelist = paths[n + 1][(idx - idx):(idx + 1)]
                edgelist = [nodelist[k:k+2] for k in range(len(nodelist) - 1)]
                nx.draw_networkx_nodes(G, **options, nodelist=nodelist, node_color=colors['opti'])
                nx.draw_networkx_edges(G, **options, edgelist=edgelist, edge_color=colors['opti'])
            ax.set_title("OPTIMAL PATHS")

        #set ants moves
        if (i and i >= frames):
            idx = i - frames
            moves = i - frames
            for n in range(len(paths) - 1):               
                if (ants[n + 1] - moves >= 0):
                    nodelist = paths[n + 1][(idx - idx):(idx + 1)]
                else:
                    nodelist = paths[n + 1][(moves - ants[n + 1] - 1):(idx + 1)]
                edgelist = [nodelist[k:k+2] for k in range(len(nodelist) - 1)]
                nx.draw_networkx_nodes(G, **options, nodelist=nodelist, node_color=colors['ants'])
                nx.draw_networkx_edges(G, **options, edgelist=edgelist, edge_color=colors['ants'])
            ax.set_title("MOVES :" + str(i - frames + 1))
        ax.set_facecolor(colors['background'])
        

    # animation
    ani = animation.FuncAnimation(fig, update, frames=frames, interval=interval, repeat=False)
    plt.show()
