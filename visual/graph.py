import networkx as nx
import matplotlib.pyplot as plt
import matplotlib.animation as animation

def graph(G, paths):
    shrtlen = len(paths[0])
    frames = shrtlen + len(paths[len(paths) - 1])
    options = {
        'pos': nx.get_node_attributes(G, 'pos'),
        'node_size': 500,
        'alpha': 0.60,
        'width': 10.0,
    }

    # set subplots
    fig, ax = plt.subplots(figsize=(6, 4))

    def update(i):
        ax.clear()
        plt.gca().invert_yaxis()

        # draw background graph
        nx.draw_networkx_edges(G, **options, ax=ax, edge_color="#0D7D84")
        nx.draw_networkx_nodes(G, **options, ax=ax, node_color="#07B2B4")

        # draw shortest path
        if (i and i <= shrtlen):
            nodelist = paths[0][(i - i):(i + 1)]
            edgelist = [nodelist[k:k+2] for k in range(len(nodelist) - 1)]
            nx.draw_networkx_nodes(G, **options, nodelist=nodelist, node_color='yellow', ax=ax)
            nx.draw_networkx_edges(G, **options, edgelist=edgelist, edge_color='yellow', ax=ax)
            ax.set_title("SHORTEST PATH")

        # draw any other needed paths 
        if (i and i > shrtlen):
            idx = i - shrtlen
            for n in range(len(paths) - 1):
                nodelist = paths[n + 1][(idx - idx):(idx + 1)]
                edgelist = [nodelist[k:k+2] for k in range(len(nodelist) - 1)]
                nx.draw_networkx_nodes(G, **options, nodelist=nodelist, node_color='orange', ax=ax)
                nx.draw_networkx_edges(G, **options, edgelist=edgelist, edge_color='orange', ax=ax)
            ax.set_title("ALTERNATE PATHS") 
        ax.set_facecolor("#94DAD5")

    # animation
    ani = animation.FuncAnimation(fig, update, frames=frames, interval=1000, repeat=True)
    ani.save('map_simple3.mp4', fps=1, extra_args=['-vcodec', 'libx264'])
    plt.show()
