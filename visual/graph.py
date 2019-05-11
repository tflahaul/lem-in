import networkx as nx
import matplotlib.pyplot as plt
import matplotlib.animation as animation

def get_options(G, vertices, ax):
    options = {
        'pos': nx.nx_pydot.pydot_layout(G, prog='sfdp') if vertices > 100
           else nx.get_node_attributes(G, 'pos'),
        'node_size': 500 if vertices < 50 
            else 10,
        'alpha': 0.60,
        'width': 10.0 if vertices < 50
            else 1.0,
        'ax': ax,
    }
    return (options)

def graph(G, paths, data):
    shrtlen = len(paths[0])
    frames = shrtlen + len(paths[len(paths) - 1])

    # set subplots
    fig, ax = plt.subplots(figsize=(6, 4))
    options = get_options(G, data['vertices'], ax)

    def update(i):
        ax.clear()
        plt.gca().invert_yaxis()

        # draw background graph
        nx.draw_networkx_edges(G, **options, edge_color="#0D7D84")
        nx.draw_networkx_nodes(G, **options, node_color="#07B2B4")
        
        # draw shortest path
        if (i and i <= shrtlen):
            nodelist = paths[0][(i - i):(i + 1)]
            edgelist = [nodelist[k:k+2] for k in range(len(nodelist) - 1)]
            nx.draw_networkx_nodes(G, **options, nodelist=nodelist, node_color='yellow')
            nx.draw_networkx_edges(G, **options, edgelist=edgelist, edge_color='yellow')
            ax.set_title("SHORTEST PATH")

        # draw any other needed paths 
        if (i and i > shrtlen):
            idx = i - shrtlen
            for n in range(len(paths) - 1):
                nodelist = paths[n + 1][(idx - idx):(idx + 1)]
                edgelist = [nodelist[k:k+2] for k in range(len(nodelist) - 1)]
                nx.draw_networkx_nodes(G, **options, nodelist=nodelist, node_color='orange')
                nx.draw_networkx_edges(G, **options, edgelist=edgelist, edge_color='orange')
            ax.set_title("ALTERNATE PATHS") 
        ax.set_facecolor("#94DAD5")

    # animation
    ani = animation.FuncAnimation(fig, update, frames=frames, interval=1000, repeat=True)
    ani.save('big.mp4', fps=1, extra_args=['-vcodec', 'libx264'])
    plt.show()
