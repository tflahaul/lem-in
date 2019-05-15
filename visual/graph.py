import networkx as nx
import matplotlib.pyplot as plt
import matplotlib.animation as animation

def get_options(G, vertices, ax):
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

def get_ants_per_path(paths, init):
    dic = {}
    _del_ = []
    for i in range(len(paths)):
        if (i > 0):
            if (i == 1):
                dic[i] = init - 1
                length = len(paths[i])
                prev_size = length
            else:
                size = len(paths[i])

                if (prev_size != size):
                    dic[i] = init - (size - prev_size) - 1
                else:
                    if (prev_ant == init - 1 and prev_ant % 2 != 0):
                        dic[i] = prev_ant - 1
                    else:
                        dic[i] = prev_ant
                size = prev_size
            prev_ant = dic[i]
            if (dic[i] <= 0):
                _del_.append(i)
    for i in range(len(_del_)):
        del dic[_del_[i]]
        paths.pop(_del_[i]) 
    return (dic, paths)


def graph(G, paths, data):

    #reset paths accounting for data['init'], set animation data
    ants, paths = get_ants_per_path(paths, data['init'])
    shrtlen = len(paths[0])
    frames = shrtlen + len(paths[len(paths) - 1])
    steps = data['init'] + len(paths[1])
    interval = 10 if (data['vertices'] >= 1000) else 500

    # set subplots
    fig, ax = plt.subplots(figsize=(23, 13))
    options = get_options(G, data['vertices'], ax)

    def update(i):
        ax.clear()
        plt.gca().invert_yaxis()

        # draw background graph
        nx.draw_networkx_edges(G, **options, edge_color="#0D7D84")
        nx.draw_networkx_nodes(G, **options, node_color="#07B2B4")
        
        # draw shortest path
        if (i and i < shrtlen):
            nodelist = paths[0][(i - i):(i + 1)]
            edgelist = [nodelist[k:k+2] for k in range(len(nodelist) - 1)]
            nx.draw_networkx_nodes(G, **options, nodelist=nodelist, node_color='yellow')
            nx.draw_networkx_edges(G, **options, edgelist=edgelist, edge_color='yellow')
            ax.set_title("SHORTEST PATH")

        # draw optimal paths 
        if (i and shrtlen <= i < frames):
            idx = i - shrtlen
            for n in range(len(paths) - 1):
                nodelist = paths[n + 1][(idx - idx):(idx + 1)]
                edgelist = [nodelist[k:k+2] for k in range(len(nodelist) - 1)]
                nx.draw_networkx_nodes(G, **options, nodelist=nodelist, node_color='orange')
                nx.draw_networkx_edges(G, **options, edgelist=edgelist, edge_color='orange')
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
                nx.draw_networkx_nodes(G, **options, nodelist=nodelist, node_color='green')
                nx.draw_networkx_edges(G, **options, edgelist=edgelist, edge_color='green')
            ax.set_title("MOVES :" + str(i - frames + 1))
        ax.set_facecolor("#94DAD5")
        

    # animation
    ani = animation.FuncAnimation(fig, update, frames=frames + steps, interval=interval, repeat=True)
    plt.show()
