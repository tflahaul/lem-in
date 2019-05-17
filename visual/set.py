# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    set.py                                             :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abrunet <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/17 20:16:22 by abrunet           #+#    #+#              #
#    Updated: 2019/05/17 20:16:44 by abrunet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

import networkx as nx
from graph import graph
import subprocess 
import os

def read_data():
    data = {}
    with open('data.txt', 'r') as f:
        lines = f.readlines()
        data['ants'] = int(lines[0].strip('\n'))
        data['vertices'] = int(lines[1].strip('\n'))
        data['start'] = lines[2].strip('\n')
        data['end'] = lines[3].strip('\n')
    return (data)

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
                
def read_output(lines, G):
    for line in lines:
        if (line):
            if ('\033' in line[0]):
                raise Exception('Invalid Map')
            if (line.startswith(('#', 'L')) == False):
                if (line.find(' ') != -1):
                    data = line.split(' ')
                    name = data[0]
                    x = int(data[1])
                    y = int(data[2])
                    G.add_node(name, pos=(x, y))
                elif (line.find('-') != -1):
                    e = line.split('-')
                    e = (tuple((e[0], e[1])))
                    G.add_edge(*e)
            print (line)


def clear_files():
    if os.path.exists('paths.txt'):
        os.remove('paths.txt')
    if os.path.exists('data.txt'):
        os.remove('data.txt')
    if os.path.exists('ants.txt'):
        os.remove('ants.txt')

if __name__ == '__main__':
    clear_files()
    if (os.path.exists('../lem-in') == False):
        subprocess.call('make -C ..', shell=True)
    cmd = '../lem-in -v'
    p = subprocess.check_output(cmd, shell=True)
    output = p.decode("utf-8")
    lines = output.split('\n')
    try:
        G = nx.Graph()
        read_output(lines, G)
        data = read_data()
        paths = read_paths()
        graph(G, paths, data)    
    except Exception as e:
        print(e)
