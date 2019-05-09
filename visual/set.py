import networkx as nx
from graph import graph
import subprocess 
import os

def read_edges(G):
    with open('edges.txt', 'r') as f:
        lines = f.readlines()
        for line in lines:
            line = line.split('-')
            e = (tuple((line[0], line[1].strip('\n'))))
            G.add_edge(*e)

def read_vertices(G):
    with open('vertices.txt', 'r') as f:
        lines = f.readlines()
        for line in lines:
            data = line.split(' ')
            name = data[0]
            x = int(data[1])
            y = int(data[2].strip('\n'))
            G.node[name]['pos'] = (x, y)

def read_paths():
    paths = []
    lst = []
    with open('paths.txt', 'r') as f:
        lines = f.readlines()
        for line in lines:
            if (line.strip('\n')):
                lst.append(line.strip('\n'))
            else:
                paths.append(lst)
                lst = []
    return (paths)
                
def read_output(lines):
    for line in lines:
        if (line):
            if ('\033' in line[0]):
                raise Exception('Invalid Map')
            print (line)

def clear_files():
    if os.path.exists('vertices.txt'):
        os.remove('vertices.txt')
    if os.path.exists('edges.txt'):
        os.remove('edges.txt')
    if os.path.exists('paths.txt'):
        os.remove('paths.txt')

if __name__ == '__main__':
    clear_files()
    cmd = '../lem-in -v'
    p = subprocess.check_output(cmd, shell=True)
    output = p.decode("utf-8")
    lines = output.split('\n')
    try:
        read_output(lines)
        G = nx.Graph()
        read_edges(G)
        read_vertices(G)
        paths = read_paths()
        graph(G, paths)    
    except Exception as e:
        print(e)
