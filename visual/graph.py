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

import matplotlib
matplotlib.rcParams["toolbar"] = "toolmanager"
import matplotlib.pyplot as plt
import color as c
from options import get_options
from draw import draw_graph
from class_obj import Optimum, Shortest, Ants

def set_colors(color):
    if color == 'holy_graph':
        return (c.holy_graph)
    elif color == 'city':
        return (c.city)
    else:
        return (c.default)

def graph(G, coord, paths, data, color):
    colors = set_colors(color)
    interval = 10 if (data['vertices'] >= 1000) else 500

    # set plots
    fig, ax = plt.subplots(figsize=(12, 7))
    options = get_options(G, data['vertices'], ax, coord)
    ax.set_facecolor(colors['background'])
    plt.gca().invert_yaxis()
    #add paths tools
    tm = fig.canvas.manager.toolmanager
    tb = fig.canvas.manager.toolbar
    #create tools
    tm.add_tool('Shortest', Shortest, paths=paths, G=G, options=options, colors=colors)
    tm.add_tool('Optimum', Optimum, paths=paths, G=G, options=options, colors=colors)
    tm.add_tool('Ants', Ants, fig=fig, interval=interval, paths=paths, G=G, options=options, colors=colors)
    #add tools to navigation bar
    tb.add_tool('Shortest', 'Navigation')
    tb.add_tool('Optimum', 'Navigation')
    tb.add_tool('Ants', 'Navigation')
    #remove unused tools
    tm.remove_tool('subplots')
    #draw base graph
    draw_graph(0, G, options, None, None, colors)
    plt.show()
