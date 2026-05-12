import osmnx as ox

G = ox.graph_from_place("London, United Kingdom", network_type="drive")

ox.save_graphml(G, "london_road_network.graphml")

print("Файл london_road_network.graphml создан")