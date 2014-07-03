/*  
    COMP-565 Spring 2011
    Group members:
    Matthew Hoggan, mehoggan@gmail.com
    Roman Zulauf, rzulauf@gmail.com
*/

using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Audio;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.GamerServices;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;
using Microsoft.Xna.Framework.Media;
using Microsoft.Xna.Framework.Net;
using Microsoft.Xna.Framework.Storage;

namespace SK565v3 {
    public class NPAvatar : Avatar {
        private const int INDEX_ERROR = 1;
        private const int DIST_ERROR = 100;
        private const float percentERROR = .5f;
        private const int validSnipingRange = 4000;
        protected Random random;
        private Boolean goToNextTreasure = true;
        private Boolean[,] cellsVisited;
        public enum MovementMethod { NONE, EXPLORER, RETURN_TO_EXPLORER_PATH, INVERSE_EXPLORER_PATH, BUILD_PATH, TRESSURE };
        private MovementMethod currentMovementMethod;
        private MovementMethod previousMovementMethod;
        private enum PathBuildMethod { A_STAR_PATH, EXPLORER_PATH, SET_RETURN_TO_EXPLORER_PATH, NONE };
        private PathBuildMethod path_builder;
        private Queue<OrderedPair> explore_path;
        private Queue<OrderedPair> inverse_explore_path;
        private Queue<OrderedPair> tressure_path;
        private Stack<Queue<OrderedPair>> inverse_tressure_path;
        private Queue<OrderedPair> queue;
        private float zlocation;
        private float xlocation;
        private OrderedPair bearing;
        private OrderedPair previous;
        private Queue<Model3D> targetTreasures;
        private float distanceToWayPoint;
        private Model3D currentTreasure;
        private Model3D previousTreasure = null;
        private string status = "";
        private string status_temp = null;
        private int countT = 0;
        private bool treasuresChanged;
        private bool returnedToOrigin;
        private OrderedPair[] wayPointsToExplore;
        private bool direction;
        private int currentWayPoint;
        private bool wayPointReached;
        private OrderedPair destinationExploring;

        public NPAvatar(Scene scene, string label, Vector3 pos, Vector3 orientAxis,float radians, string meshFile)
                        : base(scene, label, pos, orientAxis, radians, meshFile) {  
            first.Name =  "npFirst";
            follow.Name = "npFollow";
            above.Name =  "npAbove";
            stepSize = 40;
            random = new Random();
            move = true;
            cellsVisited = new Boolean[512,512];
            for (int row = 0; row < scene.Range; row++) {
                for(int col = 0; col < scene.Range; col++) {
                    cellsVisited[row, col] = false;
                }
            }
            Vector3 oldTranslation = Orientation.Translation;
            Orientation *= Matrix.CreateTranslation(-1 * Orientation.Translation);
            Orientation *= Matrix.CreateRotationY(90 * MathHelper.Pi / 180);
            Orientation *= Matrix.CreateTranslation(oldTranslation);
            targetTreasures = null;
            bearing = null;
            targetTreasures = new Queue<Model3D>();
            inverse_tressure_path = new Stack<Queue<OrderedPair>>();
            scene.PAUSE = false;
            currentTreasure = null;
            previousTreasure = null;
            destinationExploring = null;
            currentWayPoint = 1;
            direction = true;
            wayPointsToExplore = new OrderedPair [] {
                                                        new OrderedPair(504,0,504),
                                                        new OrderedPair(352,0,496),
                                                        new OrderedPair(16,0,496),
                                                        new OrderedPair(16,0,16),
                                                        new OrderedPair(32,0,16),
                                                        new OrderedPair(32,0,488),
                                                        new OrderedPair(48,0,488),
                                                        new OrderedPair(48,0,16),
                                                        new OrderedPair(64,0,16),
                                                        new OrderedPair(64,0,488),
                                                        new OrderedPair(80,0,488),
                                                        new OrderedPair(80,0,16),
                                                        new OrderedPair(96,0,16),
                                                        new OrderedPair(96,0,488),
                                                        new OrderedPair(112,0,488),
                                                        new OrderedPair(112,0,16),

                                                        new OrderedPair(128,0,16),
                                                        new OrderedPair(128,0,488),

                                                        new OrderedPair(144,0,488),
                                                        new OrderedPair(144,0,16),

                                                        new OrderedPair(160,0,16),
                                                        new OrderedPair(160,0,488),

                                                        new OrderedPair(176,0,488),
                                                        new OrderedPair(176,0,16),

                                                        new OrderedPair(192,0,16),
                                                        new OrderedPair(192,0,488),

                                                        new OrderedPair(208,0,488),
                                                        new OrderedPair(208,0,16),

                                                        new OrderedPair(224,0,16),
                                                        new OrderedPair(225,0,488),
                                                    };

            /*  STATE VARIABLES */
            previousMovementMethod = MovementMethod.NONE;
            currentMovementMethod = MovementMethod.NONE;
            path_builder = PathBuildMethod.NONE;
            wayPointReached = false;
            treasuresChanged = false;
            returnedToOrigin = true;
        }

        public void STATE_MACHINE_FUNCTION_TO_DETERMINE_MOVEMENT_METHOD_THIS_IS_KEY() {
            if(currentWayPoint == wayPointsToExplore.Length && wayPointReached) {
                direction = false;
                currentWayPoint=wayPointsToExplore.Length-2;
            }
            if(currentWayPoint == -1 && WayPointReached) {
                direction = true;
                currentWayPoint = 1;
            }
            //if (treasureCount() == 0){
            //    treasuresChanged = false;
            //}

            /*
             *  WHEN THE GAME STARTS FIRST STATE IS TO BUILD EXPLORER PATH
             *  THIS IS ALSO THE STATE WHERE YOU RETURN WHEN YOU HIT A WAY
             *  POINT IN THE EXPLORER PATH
             */
            if  ( 
                    treasureCount() == 0 &&
                    path_builder == PathBuildMethod.NONE &&
                    previousMovementMethod == MovementMethod.NONE &&
                    currentMovementMethod == MovementMethod.NONE && 
                    !(WayPointReached || treasuresChanged) &&
                    returnedToOrigin
                ) {
                
                status = "FIRST STATE";
                path_builder = PathBuildMethod.EXPLORER_PATH;
                previousMovementMethod = MovementMethod.BUILD_PATH;
                currentMovementMethod = MovementMethod.BUILD_PATH;
                //printStateVariables(1);
            } 
            
            /*
             *  STATES THAT DEAL IF YOU GO INTO EXPLORER PATH FIRST
             */
            else if (
		                treasureCount() == 0 &&
                        path_builder == PathBuildMethod.EXPLORER_PATH &&
                        previousMovementMethod == MovementMethod.BUILD_PATH &&
                        currentMovementMethod == MovementMethod.BUILD_PATH &&
                        !(wayPointReached || treasuresChanged) &&
                        returnedToOrigin
                    ) {
                status = "SWITCHING TO EXPLORER";
                path_builder = PathBuildMethod.NONE;
                previousMovementMethod = currentMovementMethod;
                currentMovementMethod = MovementMethod.EXPLORER;
                //printStateVariables(2);
            } else if(  treasureCount() == 0 &&
                        path_builder == PathBuildMethod.NONE && 
                        previousMovementMethod == MovementMethod.BUILD_PATH && 
                        currentMovementMethod == MovementMethod.EXPLORER &&
                        !(wayPointReached || treasuresChanged) &&
                        returnedToOrigin
                     ) {
                status = "FIRST STEP EVER -- GOING TO EXPLORE";
                path_builder = PathBuildMethod.NONE;
                previousMovementMethod = currentMovementMethod;
                currentMovementMethod = MovementMethod.EXPLORER;
                //printStateVariables(3);                     
            } else if(  treasureCount() == 0 &&
                        path_builder == PathBuildMethod.NONE && 
                        previousMovementMethod == MovementMethod.EXPLORER && 
                        currentMovementMethod == MovementMethod.EXPLORER &&
                        !(wayPointReached || treasuresChanged) &&
                        returnedToOrigin
                     ) {
                status = "EXPLORING";
                path_builder = PathBuildMethod.NONE;
                previousMovementMethod = currentMovementMethod;
                currentMovementMethod = MovementMethod.EXPLORER;
                //printStateVariables(3);                     
            } else if(  treasureCount() == 0 && 
                        path_builder == PathBuildMethod.NONE && 
                        previousMovementMethod == MovementMethod.EXPLORER && 
                        currentMovementMethod == MovementMethod.EXPLORER && 
                        wayPointReached &&
                        !treasuresChanged &&
                        returnedToOrigin
                     ) {
                status = "RENEW EXPLORER PATH";
                path_builder = PathBuildMethod.NONE;
                previousMovementMethod = MovementMethod.NONE;
                currentMovementMethod = MovementMethod.NONE;
                wayPointReached = false;
                //printStateVariables(4);
            }

            /*
            *  STATES THAT DEAL WITH IF YOU HAVE TREASURES SITED
            */
            else if(    treasureCount() != 0 && 
                        path_builder == PathBuildMethod.NONE &&
                        previousMovementMethod == MovementMethod.EXPLORER &&
                        currentMovementMethod == MovementMethod.EXPLORER &&
                        !(wayPointReached || treasuresChanged) &&
                        returnedToOrigin
                    ) {
                status = "FOUND TREASURE BUILDING PATH";
                path_builder = PathBuildMethod.A_STAR_PATH;
                previousMovementMethod = MovementMethod.BUILD_PATH;
                currentMovementMethod = MovementMethod.BUILD_PATH;
                //printStateVariables(5);
            } else if(  treasureCount() != 0 && 
                        path_builder == PathBuildMethod.A_STAR_PATH &&
                        previousMovementMethod == MovementMethod.BUILD_PATH &&
                        currentMovementMethod == MovementMethod.BUILD_PATH &&
                        !(wayPointReached || treasuresChanged) &&
                        returnedToOrigin
                    ) {
                status = "SWITCHING TO TREASURE PATH";
                path_builder = PathBuildMethod.NONE;
                previousMovementMethod = currentMovementMethod;
                currentMovementMethod = MovementMethod.TRESSURE;
                //printStateVariables(6);
            } else if(  treasureCount() != 0 && 
                        path_builder == PathBuildMethod.NONE &&
                        previousMovementMethod == MovementMethod.BUILD_PATH &&
                        currentMovementMethod == MovementMethod.TRESSURE &&
                        !(wayPointReached || treasuresChanged) &&
                        returnedToOrigin
                    ) {
                status = "FIRST STEP TOWARDS -- TREASURE";
                path_builder = PathBuildMethod.NONE;
                previousMovementMethod = currentMovementMethod;
                currentMovementMethod = MovementMethod.TRESSURE;
                //printStateVariables(7);
            } else if(  treasureCount() != 0 && 
                        path_builder == PathBuildMethod.NONE &&
                        previousMovementMethod == MovementMethod.TRESSURE &&
                        currentMovementMethod == MovementMethod.TRESSURE &&
                        !(wayPointReached || treasuresChanged) &&
                        returnedToOrigin
                    ) {
                status = "GETTING TREASURE";
                path_builder = PathBuildMethod.NONE;
                previousMovementMethod = currentMovementMethod;
                currentMovementMethod = MovementMethod.TRESSURE;
                //printStateVariables(8);
            } else if(  treasureCount() != 0 && 
                        path_builder == PathBuildMethod.NONE &&
                        previousMovementMethod == MovementMethod.TRESSURE &&
                        currentMovementMethod == MovementMethod.TRESSURE &&
                        !(wayPointReached || !treasuresChanged) &&
                        returnedToOrigin
                    ) {
                status = "ANOTHER TREASURE FOUND -- SETTING PATH";
                path_builder = PathBuildMethod.A_STAR_PATH;
                previousMovementMethod = MovementMethod.BUILD_PATH;
                currentMovementMethod = MovementMethod.BUILD_PATH;
                //printStateVariables(9);
            }

           /*
            *  STATES THAT DEAL WITH IF YOU HAVE TREASURES OBTAINED
            *  ALL SITED TREASURE AND NEED TO RETURN TO EXPLORER PATH
            */
            else if(    treasureCount() == 0 && 
                        path_builder == PathBuildMethod.NONE &&
                        previousMovementMethod == MovementMethod.TRESSURE &&
                        currentMovementMethod == MovementMethod.TRESSURE &&
                        !(wayPointReached || !treasuresChanged) &&
                        returnedToOrigin//RETURNED TO ORIGING SET AFTER THIS
                    ) {
                status = "SETTING UP RETURN PATH";
                path_builder = PathBuildMethod.SET_RETURN_TO_EXPLORER_PATH;
                previousMovementMethod = MovementMethod.BUILD_PATH;
                currentMovementMethod = MovementMethod.BUILD_PATH;
                //printStateVariables(10);
            } else if(  treasureCount() == 0 && 
                        path_builder == PathBuildMethod.SET_RETURN_TO_EXPLORER_PATH &&
                        previousMovementMethod == MovementMethod.BUILD_PATH &&
                        currentMovementMethod == MovementMethod.BUILD_PATH && 
                        !wayPointReached &&
                        treasuresChanged &&
                        !returnedToOrigin
                    ) {
                status = "FIRST STEP BACK TO RETURN PATH";
                path_builder = PathBuildMethod.NONE;
                previousMovementMethod = currentMovementMethod;
                currentMovementMethod = MovementMethod.RETURN_TO_EXPLORER_PATH;
                //printStateVariables(11);
            }else if(  treasureCount() == 0 && 
                        path_builder == PathBuildMethod.NONE &&
                        previousMovementMethod == MovementMethod.BUILD_PATH &&
                        currentMovementMethod == MovementMethod.RETURN_TO_EXPLORER_PATH &&
                        !wayPointReached &&
                        treasuresChanged &&
                        !returnedToOrigin
                    ) {
                status = "ON RETURN PATH";
                path_builder = PathBuildMethod.NONE;
                previousMovementMethod = currentMovementMethod;
                currentMovementMethod = MovementMethod.RETURN_TO_EXPLORER_PATH;
                //printStateVariables(12);
            }else if(  treasureCount() == 0 && 
                        path_builder == PathBuildMethod.NONE &&
                        previousMovementMethod == MovementMethod.RETURN_TO_EXPLORER_PATH &&
                        currentMovementMethod == MovementMethod.RETURN_TO_EXPLORER_PATH &&
                        !wayPointReached &&
                        treasuresChanged &&
                        !returnedToOrigin
                    ) {
                status = "ON RETURN PATH";
                path_builder = PathBuildMethod.NONE;
                previousMovementMethod = currentMovementMethod;
                currentMovementMethod = MovementMethod.RETURN_TO_EXPLORER_PATH;
                //printStateVariables(13);
            }else if(  treasureCount() == 0 && 
                        path_builder == PathBuildMethod.NONE &&
                        previousMovementMethod == MovementMethod.RETURN_TO_EXPLORER_PATH &&
                        currentMovementMethod == MovementMethod.RETURN_TO_EXPLORER_PATH &&
                        !wayPointReached &&
                        treasuresChanged &&
                        returnedToOrigin
                    ) {
                status = "BACK AT WHERE I LEFT OFF IN EXPLORER PATH";
                path_builder = PathBuildMethod.NONE;
                previousMovementMethod = MovementMethod.EXPLORER;
                currentMovementMethod = MovementMethod.EXPLORER;
                treasuresChanged = false;
                foreach(OrderedPair O in queue) {
                    scene.WayPoints[(int)O.Z, (int)O.X].changeCubeColor(Color.Green);
                }
                //printStateVariables(14);
            }

            /*  
             *  THIS IS JUST IN THE "CASE" THAT I MISSED A TRANSITION
             *  IN MY STATE MACHINE
             */
            else {
                scene.PAUSE = true;
                printStateVariables(-1);
            }

        }

        public override void Update(GameTime gameTime) {
            yaw = 0;
            step = 0;
            if(!scene.PAUSE) {
                findTreasure();
                STATE_MACHINE_FUNCTION_TO_DETERMINE_MOVEMENT_METHOD_THIS_IS_KEY();
                updateLocationCompressedCoord();

                switch(currentMovementMethod) {
                    case (MovementMethod.BUILD_PATH) : {
                        switch(path_builder) {
                            case (PathBuildMethod.EXPLORER_PATH) : {
                                explorerPathBuilder();
                                break;
                            }
                            case (PathBuildMethod.A_STAR_PATH) : {
                                aStarPathBuilder();
                                break;
                            }
                            case (PathBuildMethod.SET_RETURN_TO_EXPLORER_PATH) : {
                                setUpPathReturn();
                                break;
                            }
                        }      
                        break;
                    }
                    case (MovementMethod.EXPLORER) : {
                        if(!queueIsEmpty()) {
                            standardPathToFollow();
                        }
                        checkIfNearNextWayPoint();
                        break;
                    }
                    case (MovementMethod.TRESSURE) : {
                        moveToTreassure();
                        break;
                    }
                    case (MovementMethod.RETURN_TO_EXPLORER_PATH) : {
                        if(!queueIsEmpty()) {
                            standardPathToFollow();
                        } else if(numberOfReturnPaths() != 0) {
                            setUpPathReturn();
                        } else {
                            returnedToOrigin = true;
                            queue = explore_path;
                        }
                        break;
                    }   
                }
            }
            base.Update(gameTime);
        }
        
        /*
         *  THIS FUNCTION ONLY FINDS TREASURES WITHIN 4000 UNITS
         *  IT ONLY ADDS THEM TO THE QUEUE. THE FUNCTION 'aStarPathBuilder()'
         *  GETS CURRENT TREASURE FROM TOP OF QUEUE. IT IS REMOVED
         *  IN 'movedToTreasure()' ONCE IT IS REACHED. A RETURN PATH FOR THE 
         *  TREASURE IS ADDED PER TRESURE TO A STACK INSIDE 'aStartPathBuilder()'
         */
        public void findTreasure() {
            distanceRemainingTillWayPoint();
            float distance = float.MaxValue;
            foreach(Model3D T in scene.Treasures) {
                if(T.Visible) {
                    float Xo = (T.Orientation.Translation.X / scene.Spacing);
                    float Zo = (T.Orientation.Translation.Z / scene.Spacing);
                    float distCalc = distanceToTressure(Xo,xlocation,Zo,zlocation);
                    float dist2Calc = distanceToTressure(T.Orientation.Translation.X, xlocation * scene.Spacing, T.Orientation.Translation.Z, zlocation * scene.Spacing);
                    if(distCalc < distance) {
                        distance = distCalc;
                        if(dist2Calc < validSnipingRange) {
                            if(distanceToWayPoint < DIST_ERROR) {
                                translateToWayPoint();
                                if (!targetTreasures.Contains(T) && T.Visible) {
                                    System.Console.WriteLine("Adding Treasure " + ++countT + " to List: @ (" + T.X + ", " + T.Z + ")");
                                    targetTreasures.Enqueue(T);
                                    updateLocationCompressedCoord();
                                }
                            }
                        } 
                    }
                }
            }
        }

        public void moveToTreassure() {
            float Xo = targetTreasures.Peek().Orientation.Translation.X;
            float Zo = targetTreasures.Peek().Orientation.Translation.Z;
            float Xi = Orientation.Translation.X;
            float Zi = Orientation.Translation.Z;
            float dist = distanceToTressure(Xo,Xi,Zo,Zi);
            if( dist < DIST_ERROR ) {
                translateToTressure();
                countT--;
                bearing = null;                             //YOU WILL GET NEW BEARING WHEN QUE IS FILLED
                targetTreasures.Dequeue();                  //GET RID OF CAPTURED TREASURE
                if(treasureCount() != 0) {                  //IF MORE TREASURE FOUND THAN GET NEXT ONE
                    currentTreasure = targetTreasures.Peek();
                } else {
                    currentTreasure = null;
                }
                treasuresChanged = true;
            } else {
                if(!queueIsEmpty()) {
                    standardPathToFollow();
                }
            }
        }

        private void standardPathToFollow() {
            if (!queueIsEmpty()) {
                if( bearing != null &&
                    xlocation > bearing.X - percentERROR && xlocation < bearing.X + percentERROR &&
                    zlocation > bearing.Z - percentERROR && zlocation < bearing.Z + percentERROR) {
                    bearing = null;
                    previous = queue.Dequeue();
                    scene.WayPoints[(int)previous.Z, (int)previous.X].changeCubeColor(setColor());
                    translateToWayPoint();
                }
                if(bearing == null) {
                    if(!queueIsEmpty()) {
                        if(!scene.PAUSE) {
                            bearing = queue.Peek();
                        }
                    }
                }   
            } 
            if(bearing != null) {
                orientToPath();
                setStep();
            }
        }
        
        public void setUpPathReturn() {
            returnedToOrigin = false;
            queue = inverse_tressure_path.Pop();
            previous = queue.Dequeue();
            foreach(OrderedPair O in queue) {
                 scene.WayPoints[(int)O.Z, (int)O.X].changeCubeColor(Color.Cornsilk);
            }
        }

        public void loadReturnPath() {
            OrderedPair[] array_op = queue.ToArray<OrderedPair>();
            OrderedPair[] array_rev_op = array_op.Reverse<OrderedPair>().ToArray<OrderedPair>();
            Queue<OrderedPair> reverse = new Queue<OrderedPair>();
            foreach (OrderedPair o in array_rev_op) {
                reverse.Enqueue(o);
            }
            inverse_tressure_path.Push(reverse);
        }
        
        public void aStarPathBuilder() {
            treasuresChanged = false;
            currentTreasure = targetTreasures.Peek();
            OrderedPair tresLoc = generateTresurePositionAsOrderedPair();    //PEEKS AT TOP OF QUEUE
            OrderedPair myLoc = generateMyPositionAsOrderedPair();
            if (tresLoc != null && myLoc != null) {
                tressure_path = scene.Map.findShortestPath(myLoc, tresLoc);
            }
            if (tressure_path.Count != 0) {
                queue = tressure_path;
                loadReturnPath();
                previous = queue.Dequeue();
                previousMovementMethod = currentMovementMethod;
                foreach(OrderedPair O in queue) {
                    scene.WayPoints[(int)O.Z, (int)O.X].changeCubeColor(Color.Chocolate);
                }
            } else {
                System.Console.WriteLine("INDEX_ERROR: Could not build Path");
            }
        }

        public void explorerPathBuilder() {
            OrderedPair myLoc = null;
            destinationExploring = wayPointsToExplore[currentWayPoint];    //GET NEXT WAYPOINT
            myLoc = generateMyPositionAsOrderedPair();
            if(myLoc != null || destinationExploring != null) {
                explore_path = scene.Map.findShortestPath(myLoc, destinationExploring);
                queue = explore_path;
                previous = queue.Dequeue();
                foreach(OrderedPair O in queue) {
                    scene.WayPoints[(int)O.Z, (int)O.X].changeCubeColor(Color.Green);
                }
            } else {
                System.Console.WriteLine("Could Not Build Path Good Bye");
                Environment.Exit(0);
            }
        }

        public float checkIfNearNextWayPoint() {
            float Xo = destinationExploring.X*scene.Spacing;
            float Zo = destinationExploring.Z*scene.Spacing;
            float Xi = Orientation.Translation.X;
            float Zi = Orientation.Translation.Z;
            float dist = distanceToPoint(Xo,Xi,Zo,Zi);
            if( dist < DIST_ERROR ) {
                translateToExplorerWayPoint();
                wayPointReached = true;
                if(direction) {
                    currentWayPoint++;
                } else if(!direction) {
                    currentWayPoint--;
                }
            }
            return dist;
        }

        /*  PROPERTIES AND HELPER FUNCTIONS                             */
        /*  THIS SECTION DOES NOT NEED TO BE READY THE FUNCTION NAMES   */
        /*  ARE SELF EXPLANATORY                                        */
        public float DistanceToWayPoint {
            get { return distanceToWayPoint; }
        }
        public Queue<Model3D> TargetTressures {
            get { return targetTreasures; }
        }
        public Boolean GoToNextTreasure {
            get { return goToNextTreasure; }
            set { goToNextTreasure = value; }
        }
        public float iZLoc {
            get { return zlocation; }
        }
        public float iXLoc {
            get { return xlocation; }
        }
        public OrderedPair Bearing {
            get { return bearing; }
        }
        public int ExplorerQueCount {
            get { return explore_path.Count; }
        }
        public int TressureQueCount {
            get { return tressure_path.Count; }
        }
        public MovementMethod Movement {
            get { return currentMovementMethod; }
        }
        public string Status {
            get { return status; }
        }
        public string Status_Temp {
            get { return status_temp; }
        }
        public bool WayPointReached {
            get { return wayPointReached; }
        }
        public OrderedPair DesinationExploring {
            get { return destinationExploring; }
        }

        public Color setColor() {
            switch(currentMovementMethod) {
                case (MovementMethod.EXPLORER) : {
                    return Color.Red;
                }
                case (MovementMethod.TRESSURE) : {
                    return Color.Purple;
                }
                case (MovementMethod.RETURN_TO_EXPLORER_PATH) : {
                    //return Color.Orange;
                    return Color.Blue;
                }
                default : {
                    return Color.Black;
                }
            }
        }

        private int treasureCount() {
            return targetTreasures.Count;
        }

        public int numberOfReturnPaths() {
            return inverse_tressure_path.Count;
        }

        public bool treasureListEmpty() {
            bool empty = false;
            if(targetTreasures.Count == 0) {
                empty = true;
            }
            return empty;
        }

        private string displayOrderedPair(OrderedPair o) {
            return "(" + o.X + ", " + o.Z + ")";
        }

        public bool scanListofTressures(Model3D t) {
            bool foundTressure = false;
            foreach(Model3D T in targetTreasures) {
                if(T == t) {
                    foundTressure = true;
                }
            }
            return foundTressure;
        }

        public float radiansToAngle(float radians) {
            return (float)(radians * (180 / Math.PI));
        }

        public bool queueIsEmpty() {
            bool retrn = false;
            if(queue == null) {
                retrn = true;
            }
            if(queue.Count == 0) {
                retrn = true;
            }
            return retrn;
        }

        public void Message(string message) {
            System.Console.WriteLine(message);
        }

        public void distanceRemainingTillWayPoint() {
            if(bearing != null) {
                distanceToWayPoint = distanceToPoint    (   
                                                            bearing.X*scene.Spacing,Orientation.Translation.X,
                                                            bearing.Z*scene.Spacing,Orientation.Translation.Z
                                                        );
            }
        }

        public void translateToWayPoint() {
            if (bearing != null) {
                Orientation *= Matrix.CreateTranslation(-Orientation.Translation);
                Orientation *= Matrix.CreateTranslation(bearing.X * scene.Spacing, bearing.Y * scene.Spacing, bearing.Z * scene.Spacing);
            }
        }

        public void translateToExplorerWayPoint() {
            Orientation *= Matrix.CreateTranslation(-Orientation.Translation);
            Orientation *= Matrix.CreateTranslation(destinationExploring.X * scene.Spacing,
                                                    0,
                                                    destinationExploring.Z * scene.Spacing);
        }

        public void updateLocationCompressedCoord() {
            zlocation = (Orientation.Translation.Z / scene.Spacing);
            xlocation = (Orientation.Translation.X / scene.Spacing);
        }

        public void translateToTressure() {
            if (targetTreasures != null) {
                Orientation *= Matrix.CreateTranslation(-Orientation.Translation);
                Orientation *= Matrix.CreateTranslation(targetTreasures.Peek().X * scene.Spacing, 
                                                        scene.Terrain.surfaceHeight((int)(targetTreasures.Peek().X*scene.Spacing),
                                                                                    (int)(targetTreasures.Peek().Z*scene.Spacing)), 
                                                        targetTreasures.Peek().Z * scene.Spacing);
            }
        }

        private void displayQueue() {
            System.Console.WriteLine("\nTHE QUEUE:");
            foreach(OrderedPair O in queue) {
                System.Console.WriteLine("(" + O.X + ", " + O.Z + ")");
            }
            System.Console.WriteLine("");
        }

        private float distanceToPoint(float Xo, float Xi, float Zo, float Zi) {
            return (float)Math.Sqrt(Math.Pow((Xi - Xo), 2.0) + Math.Pow((Zi - Zo), 2.0));
        }

        private float distanceToTressure(float Xo, float Xi, float Zo, float Zi) {
            return distanceToPoint(Xo, Xi, Zo, Zi);
        }

        public OrderedPair generateMyPositionAsOrderedPair() {
            return new OrderedPair(xlocation, scene.Terrain.surfaceHeight((int)xlocation, (int)zlocation), zlocation);
        }

        public OrderedPair generateTresurePositionAsOrderedPair() {
            OrderedPair top = null;
            Model3D T = targetTreasures.Peek();
            if(treasureCount() != 0) {
                top = new OrderedPair(  T.X, scene.Terrain.surfaceHeight((int)T.X,(int)T.Z), T.Z );
            }
            return top;
        }

        private bool checkForCollisionFront() {
            bool collision = false;
            int checkForwardX = (int)(xlocation + .5 * Orientation.Forward.X);
            int checkForwardZ = (int)(zlocation + .5 * Orientation.Forward.Z);
            if(scene.GridMap[checkForwardZ,checkForwardX] == 'b') {
                collision = true;
            }
            return collision;
        }

        private void setStep() {
            if(!checkForCollisionFront() && bearing != null) {
                step = (int)(stepSize / 40);
            }else {
                Matrix old = Orientation;
                Orientation *= Matrix.CreateTranslation(
                                                            scene.Spacing * Orientation.Right.X,
                                                            0,
                                                            scene.Spacing * Orientation.Right.Z
                                                        );
                step = 0;
            }
        }

        private void orientToPath() {
            float radians = orientToWayPoint(bearing);
            yaw = radians;
        }

         private float orientToWayPoint(OrderedPair direction) {
            float yaw_retn = 0; ;
            Vector3 point = new Vector3(direction.X*scene.Spacing,0,direction.Z*scene.Spacing);
            Vector3 forward = Orientation.Forward;
            forward.Y = 0;
            Vector3 position = Orientation.Translation;
            position.Y = 0;
            Vector3 right = Orientation.Right;
            right.Y = 0;
            Vector3 left = Orientation.Left;
            left.Y = 0;
            
            Vector3 u = Vector3.Normalize(forward);
            Vector3 v = Vector3.Normalize(point - position);
            Vector3 r = Vector3.Normalize(right);
            Vector3 l = Vector3.Normalize(left);
            float angle = (float)Math.Acos(Vector3.Dot(u,v));
            float angleR = (float)Math.Acos(Vector3.Dot(r,v));
            float angleL = (float)Math.Acos(Vector3.Dot(l,v));
            if(angleL < angleR) {
                yaw_retn = angle;
            }else if(angleR < angleL) {
                yaw_retn = -angle;
            }else if(angleR == angleL) {
                yaw_retn = angle;
            }
            if(double.IsNaN(yaw)) {
                yaw_retn = (float)Math.PI;
            }
            return yaw_retn;
        }

        public void printStateVariables(int state) {
            System.Console.WriteLine    (
                                            state + 
                                            ") " + treasureCount() + 
                                            " -- " + path_builder + 
                                            " -- " + previousMovementMethod +
                                            " -- " + currentMovementMethod + 
                                            " -- " + wayPointReached +
                                            " -- " + treasuresChanged +
                                            " -- " + returnedToOrigin +
                                            " -- " + status
                                        );
        }
    }   /*  CLASS   */
}   /*  NAMESPACE   */