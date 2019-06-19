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

def draw_graph(mode, G, options, nodelist, edgelist, colors):
    if mode == 0:
        nx.draw_networkx_edges(G, **options, edge_color=colors['edge_std'])
        nx.draw_networkx_nodes(G, **options, node_color=colors['node_std'])
    elif mode == 1:
        nx.draw_networkx_nodes(G, **options, nodelist=nodelist, node_color=colors['short'])
        nx.draw_networkx_edges(G, **options, edgelist=edgelist, edge_color=colors['short'])
    elif mode == 2:
        nx.draw_networkx_nodes(G, **options, nodelist=nodelist, node_color=colors['opti'])
        nx.draw_networkx_edges(G, **options, edgelist=edgelist, edge_color=colors['opti'])
    else:
        nx.draw_networkx_nodes(G, **options, nodelist=nodelist, node_color=colors['ants'])
        nx.draw_networkx_edges(G, **options, edgelist=edgelist, edge_color=colors['ants'])
