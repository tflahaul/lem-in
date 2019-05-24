# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    graph.py                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abrunet <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/17 20:16:57 by abrunet           #+#    #+#              #
#    Updated: 2019/05/24 20:23:47 by abrunet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

import networkx as nx
import matplotlib.pyplot as plt
import matplotlib.animation as animation

def set_colors():
    default = {
        'background'  : "#94DAD5",
        'edge_std'    : "#0D7D84",
        'node_std'    : "#07B2B4",
        'short'       : "yellow",
        'opti'        : "orange",
        'ants'        : "green",
    }

    holy_graph = {
        'background'  : "#051B26",
        'edge_std'    : "#4C4C4E",
        'node_std'    : "#4C4C4E",
        'short'       : "#19BFBC",
        'opti'        : "#19BFBC",
        'ants'        : "#19BFBC",
    }

    city = {
        'background'  : "#424242",
        'edge_std'    : "#100805",
        'node_std'    : "#100805",
        'short'       : "#37D7FD",
        'opti'        : "#37D7FD",
        'ants'        : "#37D7FD",
    }
    return (holy_graph)

def set_options(G, ax, node_size, width, pos):
    options = {
        'pos': pos,
        'node_size': node_size,
        'alpha': 0.60,
        'width': width,
        'ax': ax,
    }
    return (options)

def get_options(G, vertices, ax, coord):
    #set edges width
    if vertices < 50:
        width = 10.0
    elif 50 <= vertices <= 1000:
        width = 5.0
    else:
        width = 3.0

    if vertices < 50:
        node_size = 500
    elif 50 <= vertices <= 1000:
        node_size = 150
    else:
        node_size = 100

    options = {
        'pos': nx.nx_pydot.pydot_layout(G, prog='sfdp') if vertices > 100
           else nx.get_node_attributes(G, 'pos'),
        'node_size': node_size,
        'alpha': 0.60,
        'width': width,
        'ax': ax,
    }
    return (options)

def get_ants_per_path():
    dic = {}
    i = 1
    with open('ants.txt', 'r') as f:
        lines = f.readlines()
        for line in lines:
            dic[i] = int(line)
            i += 1
    return (dic)

def graph(G, paths, data):

    #reset paths accounting for data['init'], set animation data
    ants = get_ants_per_path()
    colors = set_colors()
    print(colors)
    shrtlen = len(paths[0])
    frames = shrtlen + len(paths[len(paths) - 1])
    steps = ants[1] + len(paths[1])
    interval = 10 if (data['vertices'] >= 1000) else 500

    # set subplots
    fig, ax = plt.subplots(figsize=(23, 13))
    options = get_options(G, data['vertices'], ax)

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
    ani = animation.FuncAnimation(fig, update, frames=frames + steps, interval=interval, repeat=True)
    plt.show()
