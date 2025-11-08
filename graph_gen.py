import networkx as nx
import matplotlib.pyplot as plt
import random
import argparse

def generate_graph(n_nodes=5, n_edges=7, graph_type='random', directed=False, weighted=False, p=0.5, save_path='graph.png'):
    """
    Generates different types of graphs and saves as an image.

    Parameters:
        n_nodes: number of nodes
        n_edges: number of edges (for random type)
        graph_type: 'random', 'complete', 'cycle', 'tree', 'erdos_renyi'
        directed: True/False
        weighted: True/False
        p: probability for Erdos-Renyi
        save_path: output file path
    """
    
    # Create graph object
    if directed:
        G = nx.DiGraph()
    else:
        G = nx.Graph()

    # Build graph based on type
    if graph_type == 'random':
        G.add_nodes_from(range(n_nodes))
        possible_edges = [(i, j) for i in range(n_nodes) for j in range(n_nodes) if i != j]
        if not directed:
            possible_edges = [(i, j) for i, j in possible_edges if i < j]
        edges = random.sample(possible_edges, min(n_edges, len(possible_edges)))
        if weighted:
            weighted_edges = [(u, v, random.randint(1, 10)) for u, v in edges]
            G.add_weighted_edges_from(weighted_edges)
        else:
            G.add_edges_from(edges)

    elif graph_type == 'complete':
        if directed:
            G.add_nodes_from(range(n_nodes))
            for i in range(n_nodes):
                for j in range(n_nodes):
                    if i != j:
                        G.add_edge(i, j)
        else:
            G = nx.complete_graph(n_nodes)
            if directed:
                G = G.to_directed()
        if weighted:
            for u, v in G.edges():
                G[u][v]['weight'] = random.randint(1, 10)

    elif graph_type == 'cycle':
        G = nx.cycle_graph(n_nodes)
        if directed:
            G = G.to_directed()
        if weighted:
            for u, v in G.edges():
                G[u][v]['weight'] = random.randint(1, 10)

    elif graph_type == 'tree':
        G = nx.random_tree(n_nodes)
        if directed:
            G = G.to_directed()
        if weighted:
            for u, v in G.edges():
                G[u][v]['weight'] = random.randint(1, 10)

    elif graph_type == 'erdos_renyi':
        G = nx.erdos_renyi_graph(n_nodes, p, directed=directed)
        if weighted:
            for u, v in G.edges():
                G[u][v]['weight'] = random.randint(1, 10)
    else:
        raise ValueError(f"Unknown graph type: {graph_type}")

    # Draw the graph
    pos = nx.spring_layout(G)
    plt.figure(figsize=(6,6))
    
    if weighted:
        labels = nx.get_edge_attributes(G, 'weight')
        nx.draw(G, pos, with_labels=True, node_color='skyblue', node_size=800, font_weight='bold')
        nx.draw_networkx_edge_labels(G, pos, edge_labels=labels)
    else:
        nx.draw(G, pos, with_labels=True, node_color='lightgreen', node_size=800, font_weight='bold')
    
    plt.title(f"{graph_type.capitalize()} {'Directed' if directed else 'Undirected'} Graph")
    plt.axis('off')
    plt.savefig(save_path)
    plt.close()
    print(f"Graph saved to {save_path}")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Generate different types of graph images")
    parser.add_argument('--nodes', type=int, default=5, help="Number of nodes")
    parser.add_argument('--edges', type=int, default=7, help="Number of edges (for random graph)")
    parser.add_argument('--type', type=str, default='random', choices=['random', 'complete', 'cycle', 'tree', 'erdos_renyi'], help="Type of graph")
    parser.add_argument('--directed', type=bool, default=False, help="Directed graph? True/False")
    parser.add_argument('--weighted', type=bool, default=False, help="Weighted edges? True/False")
    parser.add_argument('--prob', type=float, default=0.5, help="Probability for Erdos-Renyi graph")
    parser.add_argument('--output', type=str, default='graph.png', help="Output file path")
    
    args = parser.parse_args()

    generate_graph(
        n_nodes=args.nodes,
        n_edges=args.edges,
        graph_type=args.type,
        directed=args.directed,
        weighted=args.weighted,
        p=args.prob,
        save_path=args.output
    )
