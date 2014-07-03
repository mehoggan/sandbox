/*  
    COMP-565 Spring 2011
    Group members:
    Matthew Hoggan, mehoggan@gmail.com
    Roman Zulauf, rzulauf@gmail.com
*/

using System;
using System.Collections.Generic;

namespace SK565v3 {
    public class Graph {
        private LinkedList<Node> nodes;
        private Scene scene;

        public class Edge {
            public Node adjacent;
            public Edge (Node adj) {
                adjacent = adj;
            }
        }

        public class Node : IComparable<Node> {
            public OrderedPair data;
            public LinkedList<Edge> edges;
            public float h;
            public float g;
            public float f;
            public Node(OrderedPair op) {
                data = op;
                edges = new LinkedList<Edge>();
                f = 0f;
                g = 0f;
                h = 0f;
            }

            public int CompareTo(Node obj) {
                return f.CompareTo(obj.f);
            }

            public string printSelf() {
                return "(" + data.X + ", " + data.Z +")";
            }
        }

        public Graph(Scene aScene) {
            nodes = new LinkedList<Node>();
            scene = aScene;
        }

        private Node findOrderedPair(float X, float Z) {
            Node retrn = null;
            foreach (Node N in nodes) {
                if(N.data.X == X && N.data.Z == Z) {
                    retrn = N;
                }
            }
            return retrn;
        }

        public void testData(Node myloc_node, Node tresloc_node, OrderedPair myloc, OrderedPair tresloc) {
            if(myloc_node == null) {
                System.Console.WriteLine("Could not find myloc node @ (" + myloc.X + ", " + myloc.Z + ")");
            }
            if(tresloc_node == null) {
                System.Console.WriteLine("Could not find tresloc node @ (" + tresloc.X + ", " + tresloc.Z + ")");
            }
        }

        public Queue<OrderedPair> findShortestPath(OrderedPair myloc, OrderedPair tresloc) {
            myloc.X = (float)Math.Floor(myloc.X);
            if(myloc.X%2 != 0) {
                myloc.X += 1;
            }
            myloc.Z = (float)Math.Floor(myloc.Z);
            if(myloc.Z%2 != 0) {
                myloc.Z += 1;
            }
            Node myloc_node = findOrderedPair(myloc.X, myloc.Z);
            Node tresloc_node = findOrderedPair(tresloc.X, tresloc.Z);
            testData(myloc_node, tresloc_node, myloc, tresloc);

            Queue<OrderedPair> retrn = null;
            List<Node> closed_set = null;
            List<Node> open_set = null;

            if(myloc_node != null && tresloc_node != null) {
                bool done = false;
                closed_set = new List<Node>();
                open_set = new List<Node>();
                myloc_node.g = 0.0f;
                myloc_node.h = findDistanceBetweenNodes(myloc_node, tresloc_node);
                myloc_node.f = myloc_node.g + myloc_node.h;
                open_set.Add(myloc_node);

                retrn = new Queue<OrderedPair>();

                while(open_set.Count != 0 && !done) {

                    Node min_node = findMinimumNodeInList(open_set);
                    if (min_node == tresloc_node) {
                        closed_set.Add(min_node);                     
                        done = true;
                    }
                    if(!done) {
                        open_set.Remove(min_node);
                        closed_set.Add(min_node);
                        float tentative_g_score = 0;
                        bool tentative_is_better = false;

                        foreach(Edge E in min_node.edges) {
                            if(closed_set.Contains(E.adjacent)) {
                                continue;
                            }
                            tentative_g_score = min_node.g + findDistanceBetweenNodes(min_node,E.adjacent);
                            if(!open_set.Contains(E.adjacent)) {
                                open_set.Add(E.adjacent);
                                tentative_is_better = true;
                            } else if(tentative_g_score < E.adjacent.g) {
                                tentative_is_better = true;
                            } else {
                                tentative_is_better = false;
                            }
                            if(tentative_is_better) {
                                E.adjacent.g = tentative_g_score;
                                E.adjacent.h = findDistanceBetweenNodes(E.adjacent, tresloc_node);
                                E.adjacent.f = E.adjacent.g + E.adjacent.h;
                            }
                        }
                    }
                }
            }
            if (closed_set != null) {
                loadQueue(retrn,  new List<Node>(), closed_set, tresloc_node, myloc_node);
            }
            resetGraph();
            return retrn;
        }

        public void loadQueue(Queue<OrderedPair> retrn, List<Node> path, List<Node> closed_set, Node reverse_engineer_node, Node myloc_node ) {
            if(reverse_engineer_node == myloc_node) {
                path.Add(reverse_engineer_node);
                for(int x = path.Count - 1; x >= 0; x--) {
                    retrn.Enqueue(new OrderedPair(path[x].data.X, path[x].data.Y, path[x].data.Z));
                }
            } else {
                //First add the node you are at to the path
                path.Add(reverse_engineer_node);

                //Find the minum F-Score in adjacent nodes
                float minimum_f_score = float.MaxValue;
                Node minimum_cost = null;
                foreach(Edge E in reverse_engineer_node.edges) {
                    if(!path.Contains(E.adjacent) && closed_set.Contains(E.adjacent)) {
                        if( E.adjacent.f < minimum_f_score) {
                            minimum_f_score = E.adjacent.f;
                            minimum_cost = E.adjacent;
                        }
                    }
                }

                //Now find the minimum node in the graph and use that in the recursive call
                if(minimum_cost != null) {
                    reverse_engineer_node = findNodeInGraph(minimum_cost);
                }

                //Make recursive call on the next node
                loadQueue(retrn, path, closed_set, reverse_engineer_node, myloc_node);
            }
        }

        public void displayFinalQueue(Queue<OrderedPair> queue) {
            if(queue != null) {
                foreach(OrderedPair op in queue) {
                    System.Console.WriteLine("(" + op.X + ", " + op.Z + ")");
                }
            }
        }

        public Node findMinimumNodeInList(List<Node> set) {
            float minimum_distance = float.MaxValue;
            Node minimum_node = null;
            foreach(Node N in set) {
                if(N.f < minimum_distance) {
                    minimum_distance = N.f;
                    minimum_node = N;
                }
            }
            return minimum_node;
        }

        public Node findNodeInGraph(Node find) {
            Node retrn = null;
            foreach(Node N in nodes) {
                if(N == find) {
                    retrn = N;
                }
            }
            return retrn;
        }

        public void displayListCount(List<Node> list) {
            System.Console.WriteLine("There are " + list.Count + " elements in sorted list");
        }

        public void displayClosedSet(List<Node> closed_set) {
            foreach(Node N in closed_set) {
                    System.Console.WriteLine(N.f + " = " + N.g + " + " + N.h + "(" + N.data.X + ", " + N.data.Z + ")");
            }
        }

        public void displayOpenSet(List<Node> open_set) {
            foreach(Node N in open_set) {
                    System.Console.WriteLine(N.f + " = " + N.g + " + " + N.h + "(" + N.data.X + ", " + N.data.Z + ")");
            }
        }

        public void displayCameFromSet(List<Node> came_from_set) {
            foreach(Node N in came_from_set) {
                    System.Console.WriteLine(N.f + " = " + N.g + " + " + N.h + "(" + N.data.X + ", " + N.data.Z + ")");
            }
        }

        public float findDistanceBetweenNodes(Node present, Node desteny) {
            return (float)Math.Sqrt(Math.Pow((desteny.data.X - present.data.X), 2.0) + Math.Pow((desteny.data.Z - present.data.Z), 2.0));
        }

        public void displayGraph() {
            foreach(Node N in nodes) {
                System.Console.Write(N.GetHashCode() + "(" + N.data.X + ", " + N.data.Z + ") -- EDGES -->");
                foreach(Edge E in N.edges) {
                    System.Console.Write(E.adjacent.GetHashCode() + "(" + E.adjacent.data.X + ", " + E.adjacent.data.Z + "), ");
                }
                System.Console.WriteLine();
            }
            System.Console.WriteLine();
        }

        public void resetGraph() {
            foreach(Node N in nodes) {
                N.f = 0f;
                N.g = 0f;
                N.h = 0f;
            }
        }

        public void buildGraph() {
            //Note you don't need a point for every vertex in the 
            //map that gets way to intensive on memory and slows things down
            for(int z = scene.Range - 8; z >= (8); z-=8) {
                for(int x = scene.Range - 8; x >= (8); x-=8) {
                    //First grab node and insert it
                    Node check_if_node_exists = findOrderedPair(x, z);
                    if(check_if_node_exists == null){
                        Node insert = new Node(new OrderedPair(x, scene.Terrain.surfaceHeight(x * scene.Spacing, z * scene.Spacing), z));
                        nodes.AddLast(insert);
                        List<Node> adjacency_List = findAjacents(x, z);
                        
                        foreach(Node N in adjacency_List) {
                            Node possibly_already_exists = findOrderedPair(N.data.X, N.data.Z);
                            if(possibly_already_exists == null) {
                                nodes.AddLast(N);
                                insert.edges.AddLast(new Edge(N));
                            } else {
                                insert.edges.AddLast(new Edge(possibly_already_exists));
                            }
                            
                        }
                    } else {
                        List<Node> adjacency_List = findAjacents((int)check_if_node_exists.data.X, (int)check_if_node_exists.data.Z);
                        foreach(Node N in adjacency_List) {
                            Node possibly_already_exists = findOrderedPair(N.data.X, N.data.Z);
                            if(possibly_already_exists == null) {
                                nodes.AddLast(N);
                                check_if_node_exists.edges.AddLast(new Edge(N));
                            } else {
                                check_if_node_exists.edges.AddLast(new Edge(possibly_already_exists));
                            }
                        }
                    }
                }
            }
        }

        private List<Node> findAjacents(int x, int z) {
            /*
             *  Then grab edges (edges) contain Nodes
             *  if no 'b' between then add edge. Note
             *  Negative implies up because we start
             *  in lower right corner
             */
            List<Node> retrn = new List<Node>();
            if(scene.GridMap[z,x] == 'w') {
                bool addUp = true;
                for(int up = z - 8; up < z; up++) {
                    if(up >= 0) {
                        if(scene.GridMap[up,x] == 'b') {
                            addUp = false;
                        }
                    }else {
                        addUp = false;
                    }
                }
                bool addUpLeft = true;
                for (int up = z - 8, left = x - 8; up < z && left < x; up++, left++){
                    if(up >= 0 && left >= 0) {
                        if(scene.GridMap[up,left] == 'b') {
                            addUpLeft = false;
                        }
                    }else {
                        addUpLeft = false;
                    }
                }
                bool addLeft = true;
                for(int left = x - 8; left < x; left++) {
                    if(left >= 0) {
                        if(scene.GridMap[z,left] == 'b') {
                            addLeft = false;
                        }
                    }else {
                        addLeft = false;
                    }
                }
                bool addDownLeft = true;
                for(int down = z + 8, left = x - 8; down > z && left < z; down--, left++) {
                    if(down < scene.Range && left >= 0) {
                        if(scene.GridMap[down,left] == 'b') {
                            addDownLeft = false;
                        }
                    }else {
                        addDownLeft = false;
                    }
                }
                bool addDown = true;
                for(int down = z + 8; down > z; down--) {
                    if(down < scene.Range) {
                        if(scene.GridMap[down,x] == 'b') {
                            addDown = false;
                        }
                    }else {
                        addDown = false;
                    }
                }
                bool addDownRight = true;
                for(int down = z + 8, right = x + 8; down > z && right > x; down-- ,right--) {
                    if(down < scene.Range && right < scene.Range) {
                        if(scene.GridMap[down,right] == 'b') {
                            addDownRight = false;
                        }
                    }else {
                        addDownRight = false;
                    }
                }
                bool addRight = true;
                for(int right = x + 8; right > x; right--) {
                    if(right < scene.Range) {
                        if(scene.GridMap[z,right] == 'b') {
                            addRight = false;
                        }
                    }else {
                        addRight = false;
                    }
                }
                bool addUpRight = true;
                for(int up = z - 8, right = x + 8; up < z && right > x; up++, right--) {
                    if(up >= 0 && right < scene.Range) {
                        if(scene.GridMap[up,right] == 'b') {
                            addUpRight = false;
                        }
                    }else {
                        addUpRight = false;
                    }
                }
                if(addUp) {
                    Node Up = new Node(new OrderedPair(x,scene.Terrain.surfaceHeight(x,z-8),z-8));
                    retrn.Add(Up);
                }
                if(addUpLeft) {
                    Node UpLeft = new Node(new OrderedPair(x - 8,scene.Terrain.surfaceHeight(x-8,z-8), z - 8));
                    retrn.Add(UpLeft);
                }
                if(addLeft) {
                    Node Left = new Node(new OrderedPair(x - 8, scene.Terrain.surfaceHeight(x-8,x-8),z));
                    retrn.Add(Left);
                }
                if(addDownLeft) {
                    Node DownLeft = new Node(new OrderedPair(x - 8,scene.Terrain.surfaceHeight(x-8,z+8),z + 8));
                    retrn.Add(DownLeft);
                }
                if(addDown) {
                    Node Down = new Node(new OrderedPair(x,scene.Terrain.surfaceHeight(x,z+8),z + 8));
                    retrn.Add(Down);
                }
                if(addDownRight) {
                    Node DownRight = new Node(new OrderedPair(x + 8, scene.Terrain.surfaceHeight(x+8,z+8), z + 8));
                    retrn.Add(DownRight);
                }
                if(addRight) {
                    Node Right = new Node(new OrderedPair(x + 8, scene.Terrain.surfaceHeight(x+8,z), z));
                    retrn.Add(Right);
                }
                if(addUpRight) {
                    Node UpRight = new Node(new OrderedPair(x + 8, scene.Terrain.surfaceHeight(x+8,z-8), z - 8));
                    retrn.Add(UpRight);
                }
            }
            return retrn;
        }

        public void Message(string message) {
            System.Console.WriteLine(message);
        }
    }
}
