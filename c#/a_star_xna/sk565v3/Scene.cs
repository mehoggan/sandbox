/*  
    COMP-565 Spring 2011
    Group members:
    Matthew Hoggan, mehoggan@gmail.com
    Roman Zulauf, rzulauf@gmail.com
*/

using System;
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
using System.IO; 

namespace SK565v3 {
    public class Scene : Game {
        private const int range = 512;   
        private const int spacing = 150;  // x and z spaces between vertices in the terrain
        private const int terrainSize = range * spacing;
        private GraphicsDeviceManager graphics;  
        private GraphicsDevice display;    // graphics context -- how to draw
        private BasicEffect effect;        // default effects (shaders)
        private SpriteBatch spriteBatch;   // for Trace's displayStrings
        private SpriteBatch scoreSprite;   // for Trace's displayStrings
        private SpriteFont inspectorFont;
        private SpriteFont scoreFont;
        private Model boundingSphere3D;    // a  bounding sphere model
        private bool drawBoundingSpheres = false;
        private bool fog = false;
        private bool fixedStepRendering = true;     // 60 updates / second
        private Viewport defaultViewport;
        private Viewport inspectorViewport, sceneViewport;     // top and bottom "windows"
        private Matrix sceneProjection, inspectorProjection;   
        private const int InfoPaneSize = 5;   // number of lines / info display pane
        private const int InfoDisplayStrings = 20;  // number of total display strings
        private Matrix projection;
        private float fov = (float) Math.PI / 4;
        private float hither = 5.0f, yon = terrainSize / 5.0f , farYon = terrainSize *  1.3f;
        private float fogStart = 1000;
        private float fogEnd = 10000;   
        private bool yonFlag = true;
        private GamePadState oldGamePadState;
        private KeyboardState oldKeyboardState; 
        private Vector3 lightDirection, ambientColor, diffuseColor;
        private Avatar avatar = null;
        private NPAvatar npAvatar = null;
        private Terrain terrain = null;
        private List<Camera> camera = new List<Camera>();  // collection of cameras
        private List<Object3D> treasures = new List<Object3D>();
        private Camera currentCamera, topDownCamera;
        private int cameraIndex = 0;
        private bool gameOver = false; 
        int frames = 0;
        double fpsSecond;
        int draws, updates;
        private bool[,] WallPositionX;
        private bool[,] WallPositionZ;
        private bool[,] WallPositionLowerLeftCorner;
        private bool[,] WallPositionUpperLeftCorner;
        private bool[,] WallPositionLowerRightCorner;
        private bool[,] WallPositionUpperRightCorner;
        private VertexBox[,] wayPoints;
        private char[,] gridMap;
        private SavageBeast [] savagePack;
        private float flockProb = .33f;
        private Random r = new Random((int)DateTime.Now.Ticks);
        private float flockRadius = 8*spacing;
        private float probToMoveOutOfRadius = 0.33f;
        private int dogId;
        private Graph graph;
        public Boolean PAUSE = false;

        public Scene() {
            graphics = new GraphicsDeviceManager(this);
            //graphics.PreferredBackBufferHeight = 900;
            //graphics.PreferredBackBufferWidth = 1000;
            //graphics.ApplyChanges();
            Content.RootDirectory = "Content";
            graphics.SynchronizeWithVerticalRetrace = false;  // allow faster FPS
            lightDirection = new Vector3(-1.0f, -2.0f, -1.0f);
            ambientColor = new Vector3(0.3f, 0.3f, 0.3f);
            diffuseColor = new Vector3(0.3f, 0.3f, 0.3f);
            IsMouseVisible = true;  // make mouse cursor visible
            fpsSecond = 0.0;
            draws = updates = 0;
            WallPositionX = new bool [512,512];
            WallPositionZ = new bool [512,512];
            WallPositionLowerLeftCorner = new bool[512, 512];
            WallPositionUpperLeftCorner = new bool[512, 512];
            WallPositionLowerRightCorner = new bool[512, 512];
            WallPositionUpperRightCorner = new bool[512, 512];
            wayPoints = new VertexBox[512, 512];
            gridMap = new char[512, 512];
            graph = new Graph(this);
        }

        // Properties
        public int DogID {
            get { return dogId; } 
        }
        public float FlockRadius {
            get { return flockRadius; }
        }
        public Random R {
            get { return r; }
        }
        public SavageBeast[] SavagePack {
            get { return savagePack; }
        }
        public float ProbabilityToMoveOutOfRadius {
            get { return probToMoveOutOfRadius; }
        }
        public float FlockProb {
            get { return flockProb; }
        }
        public bool GameOver {
            get { return gameOver; }
            set { gameOver = value; }
        }
        public char [,] GridMap {
            get { return gridMap; }
        }
        public int Range {
            get { return range; }
        }
        public List<Object3D> Treasures {
            get { return treasures; }
        }
        public int Spacing {
            get { return spacing; }
        }
        public int TerrainSize {
            get { return terrainSize; }
        }
        public GraphicsDevice Display {
            get { return display; }
        }
        public BasicEffect SceneEffect {
            get { return effect; }
        }
        public Vector3 DiffuseLight {
            get { return diffuseColor; }
        }
        public Vector3 AmbientLight {
            get { return ambientColor;}
        }
        public Vector3 LightDirection {
            get { return lightDirection;}
        }
        public float FogStart {
            get { return fogStart; }
        }
        public float FogEnd {
            get { return fogEnd; }
        }
        public Matrix View {
            get { return currentCamera.ViewMatrix;}
        }
        public Matrix Projection {
            get { return projection; }
        }
        public Terrain Terrain {
            get { return terrain; }
        }
        public Model BoundingSphere3D {
            get { return boundingSphere3D; }
        }
        public bool DrawBoundingSpheres {
            get { return drawBoundingSpheres; }
            set { drawBoundingSpheres = value;}
        }
        public bool FixedStepRendering {
            get { return fixedStepRendering; }
            set { fixedStepRendering = value;
            IsFixedTimeStep = fixedStepRendering; }
        }
        public bool Fog {
            get { return fog; }
            set { fog = value; }
        }
        public float FarYon {
            get { return farYon; }
        }
        public VertexBox [,] WayPoints {
            get { return wayPoints; }
        }
        public bool YonFlag {
            get { return yonFlag; }
            set { yonFlag = value;
                if (yonFlag) { 
                    //setProjection(yon);
                    setProjection(farYon);
                } else {
                    setProjection(farYon); 
                }
            }
        }
        public Graph Map {
            get { return graph; }
        }
        public bool withinRange(String aName, Vector3 newLocation) {
            if (newLocation.X < 0 || newLocation.X >= (terrainSize) ||
                newLocation.Z < 0 || newLocation.Z >= (terrainSize)) {
                return false;
            }else {
                return true; 
            }
        }

        public void toggleFullScreen() {
            graphics.ToggleFullScreen(); 
        }

        public void addCamera(Camera aCamera) {
            camera.Add(aCamera);
            cameraIndex++;
        }

        private void setProjection(float yonValue) {
            projection = Matrix.CreatePerspectiveFieldOfView(fov,
            graphics.GraphicsDevice.Viewport.AspectRatio, hither, yonValue);
        }

        public void nextCamera() {
            cameraIndex = (cameraIndex + 1) % camera.Count;
            currentCamera = camera[cameraIndex];
            // set the appropriate projection matrix
            if (currentCamera == topDownCamera) {
                yonFlag = false;
                setProjection(farYon); 
            }else {
                yonFlag = true;
                setProjection(yon); 
                avatar.AvatarCamera = currentCamera; 
            }
        }
 
        public int surfaceHeight(int x, int z) {
            return terrain.surfaceHeight(x/spacing, z/spacing); 
        }
      
        public void setBlendingState(bool state) {
            display.RenderState.AlphaBlendEnable = state; 
        }
      
        protected override void Initialize() {
            // TODO: Add your initialization logic here
            base.Initialize();
        }
        
        protected override void LoadContent() {
            initContent();
            buildTerrain();
            initializeGridMap();
            buildWalls();
            //placeTrees();
            placeTreasure();
            blockOffEdges();
            placeWayPointBoxes();
            outPutGridToFile();
            placeCharacters();
            placeSavageBeasts();
            graph.buildGraph();   
            topDownCamera = new Camera(this, Camera.CameraEnum.TopDownCamera);
            camera.Add(topDownCamera);
            nextCamera();  // select the first camera
        }

        protected override void UnloadContent() {
            // TODO: Unload any non ContentManager content here
        }
        
        private void initContent() {
            display = graphics.GraphicsDevice;
            effect = new BasicEffect(display, null);
            // Set up Inspector display
            spriteBatch = new SpriteBatch(display);      // Create a new SpriteBatch
            scoreSprite = new SpriteBatch(display);      // Create a new SpriteBatch
            inspectorFont = Content.Load<SpriteFont>("Courier New");  // load font
            scoreFont = Content.Load<SpriteFont>("Courier New");  // load font
            // viewports
            defaultViewport = GraphicsDevice.Viewport;
            inspectorViewport = defaultViewport;
            sceneViewport = defaultViewport;
            inspectorViewport.Height = InfoPaneSize * inspectorFont.LineSpacing;
            inspectorProjection = Matrix.CreatePerspectiveFieldOfView((float)Math.PI / 4.0f,
            inspectorViewport.Width / inspectorViewport.Height, 1.0f, 200.0f);
            sceneViewport.Height = defaultViewport.Height - inspectorViewport.Height;
            sceneViewport.Y = inspectorViewport.Height;
            sceneProjection = Matrix.CreatePerspectiveFieldOfView((float)Math.PI / 4.0f,
            sceneViewport.Width / sceneViewport.Height, 1.0f, 1000.0f);
            display.RenderState.SourceBlend = Blend.SourceAlpha;
            display.RenderState.DestinationBlend = Blend.InverseSourceAlpha;
            display.RenderState.BlendFunction = BlendFunction.Add;
            boundingSphere3D = Content.Load<Model>("boundingSphereV3");
        }

        private void buildTerrain() {
            terrain = new Terrain(this, "terrain", new Vector3(), Vector3.Up, 0.0f, "heightTexture", "colorTexture");
            Components.Add(terrain);
        }

        private void initializeGridMap() {
            /*
             *      SET UP GRID MAP
             */
            for(int x = 0; x < 512; x++) {
                for(int z = 0; z < 512; z++) {
                    gridMap[z, x] = 'f';
                }
            }
        }

        private void placeSavageBeasts() {
            /*
             *      PLACE THE DOGS BASED ON PLAYER POSITION
             */
            dogId = 0;  // give dogs unique names
            int totalDogs = 12;
            float initialZ = avatar.Orientation.Translation.Z;
            float initialY = avatar.Orientation.Translation.Y;
            float initialX = avatar.Orientation.Translation.X;
            Random rand = new Random((int)DateTime.Now.Ticks);
            if(totalDogs > 0) {
                savagePack = new SavageBeast[totalDogs];
                savagePack[dogId] = new SavageBeast(this, "dog " + dogId, new Vector3(initialX, initialY, initialZ),
                                                    new Vector3(0, 1, 0), 0.0f, "dogV3", avatar, dogId);
                Components.Add(savagePack[dogId]);
                dogId++;
                while (dogId < totalDogs) {
                    Vector3 pos = new Vector3(r.Next(-6,0)*spacing,initialY,r.Next(-6,0)*spacing);
                    for(int x = 0; x < dogId; x++) {
                        while(savagePack[x].Orientation.Translation == pos) {
                            pos = new Vector3(r.Next(-6, 0)*spacing, initialY, r.Next(-6, 0)*spacing);
                        }
                    }
                    savagePack[dogId] = new SavageBeast(   this, "dog " + dogId,
                                                            pos,
                                                            new Vector3(0, 1, 0), 0.0f, "dogV3", avatar, dogId
                                                        );
                    Components.Add(savagePack[dogId]);
                    dogId++;
                }

                
            }
        }

        private void placeCharacters() {
            /*
             *      PLACE THE PLAYERS AND NPCS
             */
            avatar = new Player(this, "Chaser",
                                new Vector3(504 * spacing, 0, 504 * spacing),
                                new Vector3(0, 1, 0), 0.0f, "redAvatarV3");
            Components.Add(avatar);
            npAvatar = new NPAvatar(this, "Evader",
                                    new Vector3(504 * spacing, 0, 504 * spacing),
                                    new Vector3(0, 1, 0), 0.0f, "magentaAvatarV3");
            Components.Add(npAvatar);
        }

        private void placeWayPointBoxes() {
            /*
             *      ADD BOXES TO THE SCENE
             */
            for (int z = 0; z < Range; z++) {
                for (int x = 0; x < Range; x++) {
                    if (((x) % 8) == 0 && ((z) % 8) == 0) {
                        Vector3 box_position = new Vector3(x, ((terrain.surfaceHeight(x, z)) / spacing + .8f), z);
                        adjustVerticalToTerrain(box_position);
                        Vector3 box_color = new Vector3(0f, 0f, 1f);
                        if (gridMap[z, x] == 'b')
                        {
                            box_position.Y = 1000;
                        }
                        VertexBox box = new VertexBox(this, box_position, Vector3.Up, Color.Blue, 0.40f);
                        wayPoints[z, x] = box;
                        Components.Add(box);
                        if (gridMap[z, x] == 'f')
                        {
                            gridMap[z, x] = 'w';
                        }
                    }
                }
            }
        }

        private void blockOffEdges() {
            /*
             *      SET THE EDGES TO BLOCKED -> 'b'
             */
            for(int z = 0; z < Range; z++) {
                for (int x = 0; x < Range; x++) {
                    if(z == 0 || z == Range-1 || x == 0 || x == Range-1) {
                        gridMap[z, x] = 'b';
                        if(z == 0) {
                            for(int o = 0; o < 8; o++) {
                                gridMap[z+o, x] = 'b';
                            }
                        }
                        if(x == 0) {
                            for(int o = 0; o < 8; o++) {
                                gridMap[z, x+o] = 'b';
                            }
                        }
                        if(z == Range - 1) {
                            for(int o = 0; o < 8 - 1; o++) {
                                gridMap[z-o, x] = 'b';
                            }
                        }
                        if(x == Range - 1) {
                            for(int o = 0; o < 8 - 1; o++) {
                                gridMap[z, x-o] = 'b';
                            }
                        }
                    }
                }
            }
        }

        private void placeTrees() {
            /*
             *      PLACE THE TREES
             */ 
            Random r = new Random();
            int treeId = 0;
            for (int x = 5; x < 475; x += r.Next(20, 50)) {
                for (int z = 0; z < 475; z += r.Next(20, 50)) {
                    if (terrain.surfaceHeight(x, z) < 128 * 20) {
                        Vector3 position = new Vector3((x+r.Next(-5,25))*spacing,-(0.1f*spacing),(z+12+r.Next(-5,25))*spacing);
                        if(position.Z >= 0 && position.Z < range && position.X >=0 && position.X < range && gridMap[(int)position.Z,(int)position.X] != 'b') {
                            Components.Add(new Model3D(this, "tree" + treeId,
                                    position,
                                    new Vector3(0, 1, 0), 0.79f, "tree"));
                            if (position.Z < 512 && position.X < 512) {
                                gridMap[(int)position.Z, (int)position.X] = 'b';
                            }
                            treeId++;
                        }
                    }
                }
            }
        }

        private void placeTreasure() {
            Model3D treasure1 = new Model3D(this, "penguin1", new Vector3(472 * spacing, 0 * spacing, 496 * spacing), 
                                                new Vector3(0, 1, 0), 0.0f, "Penguin");
            Model3D treasure2 = new Model3D(this, "penguin2", new Vector3(432 * spacing, 0 * spacing, 496 * spacing),
                                                new Vector3(0, 1, 0), 0.0f, "Penguin");
            Model3D treasure3 = new Model3D(this, "penguin3", new Vector3(368 * spacing, 0 * spacing, 496 * spacing),
                                                new Vector3(0, 1, 0), 0.0f, "Penguin");
            Model3D treasure4 = new Model3D(this, "penguin4", new Vector3(504 * spacing, 0 * spacing, 424 * spacing),
                                               new Vector3(0, 1, 0), 0.0f, "Penguin");
           
            Model3D treasure5 = new Model3D(this, "penguin5", new Vector3(224 * spacing, 0 * spacing, 8 * spacing),
                                                new Vector3(0, 1, 0), 0.0f, "Penguin");
            

            Components.Add(treasure1);
            Components.Add(treasure2);
            Components.Add(treasure3);
            Components.Add(treasure4);
            Components.Add(treasure5);
            treasures.Add(treasure1);
            treasures.Add(treasure2);
            treasures.Add(treasure3);
            treasures.Add(treasure4);
            treasures.Add(treasure5);

            Model3D dogparksign = new Model3D(this, "DogPark", new Vector3(488 * spacing, 0 * spacing, 413 * spacing),
                                                new Vector3(0, 1, 0), 0.0f, "DogPark");
            Components.Add(dogparksign);
        }


        public void buildWalls() {
            /*
             *      NOTE THAT IN THIS FUNCTION THE WALLS ARE PLACED AT MULTUPLES OF 16
             *      INORDER TO SPREAD THE WALLS EVENLY ACROSS MAP
             */
            string filePath = Directory.GetCurrentDirectory() + "//Content//Walls.csv";
            string line;
            if (File.Exists(filePath)) {
                StreamReader file = null;
                try {
                    file = new StreamReader(filePath); 
                    int row = 0;
                    while ((line = file.ReadLine()) != null) {
                        List<string> names = line.Split(';').ToList<string>();
                        for (int x = 0; x < names.Count; x++) {
                            //HORIZONTAL WALLS
                            if (names[x].CompareTo("1") == 0) {
                                WallPositionX[row * 8, (x * 8)] = true;
                                Model3D wallX = new Model3D(this,
                                                        "CastleWallX",
                                                        new Vector3(x * spacing * 8,            //X
                                                                    0,   //Y
                                                                    row * spacing * 8),         //Z
                                                        new Vector3(0, 1, 0),
                                                        0.0f,
                                                        "CastleWallX");
                                Components.Add(wallX);
                                for (int col = x * 8 - 8; col <= x * 8; col++) {
                                    if(row * 8-2 > 0 && row * 8-2 < range && col > 0 && col < range -1) {
                                        gridMap[row * 8-2, col] = 'b';
                                    }
                                    if(row * 8-1 > 0 && row * 8-1 < range && col > 0 && col < range -1) {
                                        gridMap[row * 8-1, col] = 'b';
                                    }
                                    if(row * 8 > 0 && row * 8 < range && col > 0 && col < range -1) {
                                        gridMap[row * 8, col] = 'b';
                                    }
                                    if(row * 8+1 > 0 && row * 8+1 < range && col > 0 && col < range -1) {
                                        gridMap[row * 8+1, col] = 'b';
                                    }
                                    if(row * 8+2 > 0 && row * 8+2 < range && col > 0 && col < range -1) {
                                        gridMap[row * 8+2, col] = 'b';
                                    }
                                }
                            }
                            else {
                                WallPositionX[row * 8, (x * 8)] = false;
                            }
                            //VERTICAL WALLS
                            if (names[x].CompareTo("2") == 0) {
                                WallPositionZ[row * 8, (x * 8)] = true;
                                Model3D wallZ = new Model3D(this,
                                                        "CastleWallZ",
                                                         new Vector3(x * spacing * 8,           //X
                                                                    0,   //Y
                                                                    row * spacing * 8),         //Z
                                                        new Vector3(0, 1, 0),
                                                        0.0f,
                                                        "CastleWallZ");
                                Components.Add(wallZ);
                                for (int level = row * 8; level < row * 8 + 8; level++) {
                                    if(x * 8 - 2 > 0 && x * 8 - 2 < range && level > 0 && level < range - 1) {
                                        gridMap[level, x * 8-2] = 'b';
                                    }
                                    if(x * 8 - 1 > 0 && x * 8 - 1 < range && level > 0 && level < range - 1) {
                                        gridMap[level, x * 8-1] = 'b';
                                    }
                                    if(x * 8 > 0 && x * 8 < range && level > 0 && level < range - 1) {
                                        gridMap[level, x * 8] = 'b';
                                    }
                                    if(x * 8 + 1 > 0 && x * 8 + 1 < range && level > 0 && level < range - 1) {
                                        gridMap[level, x * 8+1] = 'b';
                                    }
                                    if(x * 8 + 2 > 0 && x * 8 + 2 < range && level > 0 && level < range - 1) {
                                        gridMap[level, x * 8+2] = 'b';
                                    }
                                }
                            }
                            else {
                                WallPositionZ[row * 8, (x * 8)] = false;
                            }
                            if (names[x].CompareTo("3") == 0) {
                                WallPositionLowerLeftCorner[row * 8, (x * 8)] = true;
                                Model3D wallX = new Model3D(this,
                                                        "CastleWallLowerLeftCorner",
                                                        new Vector3(x * spacing * 8,            //X
                                                                    0,   //Y
                                                                    row * spacing * 8),         //Z
                                                        new Vector3(0, 1, 0),
                                                        0.0f,
                                                        "CastleWallLowerLeftCorner");
                                Components.Add(wallX);
                                for (int col = x * 8; col <= x * 8 + 8; col++) {
                                    if(row * 8-2 > 0 && row * 8-2 < range && col > 0 && col < range -1) {
                                        gridMap[row * 8-2, col] = 'b';
                                    }
                                    if(row * 8-1 > 0 && row * 8-1 < range && col > 0 && col < range -1) {
                                        gridMap[row * 8-1, col] = 'b';
                                    }
                                    if(row * 8 > 0 && row * 8 < range && col > 0 && col < range -1) {
                                        gridMap[row * 8, col] = 'b';
                                    }
                                    if(row * 8+1 > 0 && row * 8+1 < range && col > 0 && col < range -1) {
                                        gridMap[row * 8+1, col] = 'b';
                                    }
                                    if(row * 8+2 > 0 && row * 8+2 < range && col > 0 && col < range -1) {
                                        gridMap[row * 8+2, col] = 'b';
                                    }
                                }
                                for (int level = row * 8 - 8; level <= row * 8; level++) {
                                    if(x * 8 - 2 > 0 && x * 8 - 2 < range && level > 0 && level < range - 1) {
                                        gridMap[level, x * 8-2] = 'b';
                                    }
                                    if(x * 8 - 1 > 0 && x * 8 - 1 < range && level > 0 && level < range - 1) {
                                        gridMap[level, x * 8-1] = 'b';
                                    }
                                    if(x * 8 > 0 && x * 8 < range && level > 0 && level < range - 1) {
                                        gridMap[level, x * 8] = 'b';
                                    }
                                    if(x * 8 + 1 > 0 && x * 8 + 1 < range && level > 0 && level < range - 1) {
                                        gridMap[level, x * 8+1] = 'b';
                                    }
                                    if(x * 8 + 2 > 0 && x * 8 + 2 < range && level > 0 && level < range - 1) {
                                        gridMap[level, x * 8+2] = 'b';
                                    }
                                }
                            }
                            else {
                                WallPositionLowerLeftCorner[row * 8, (x * 8)] = false;
                            }
                            if (names[x].CompareTo("4") == 0) {
                                WallPositionUpperLeftCorner[row * 8, (x * 8)] = true;
                                Model3D wallULX = new Model3D(this,
                                                        "CastleWallUpperLeftCorner",
                                                        new Vector3(x * spacing * 8,            //X
                                                                    0,   //Y
                                                                    row * spacing * 8),         //Z
                                                        new Vector3(0, 1, 0),
                                                        0.0f,
                                                        "CastleWallUpperLeftCorner");
                                Components.Add(wallULX);
                                for (int col = x * 8; col <= x * 8 + 8; col++) {
                                    if(row * 8-2 > 0 && row * 8-2 < range && col > 0 && col < range -1) {
                                        gridMap[row * 8-2, col] = 'b';
                                    }
                                    if(row * 8-1 > 0 && row * 8-1 < range && col > 0 && col < range -1) {
                                        gridMap[row * 8-1, col] = 'b';
                                    }
                                    if(row * 8 > 0 && row * 8 < range && col > 0 && col < range -1) {
                                        gridMap[row * 8, col] = 'b';
                                    }
                                    if(row * 8+1 > 0 && row * 8+1 < range && col > 0 && col < range -1) {
                                        gridMap[row * 8+1, col] = 'b';
                                    }
                                    if(row * 8+2 > 0 && row * 8+2 < range && col > 0 && col < range -1) {
                                        gridMap[row * 8+2, col] = 'b';
                                    }
                                }
                                for (int level = row * 8; level <= row * 8 + 8; level++) {
                                    if(x * 8 - 2 > 0 && x * 8 - 2 < range && level > 0 && level < range - 1) {
                                        gridMap[level, x * 8-2] = 'b';
                                    }
                                    if(x * 8 - 1 > 0 && x * 8 - 1 < range && level > 0 && level < range - 1) {
                                        gridMap[level, x * 8-1] = 'b';
                                    }
                                    if(x * 8 > 0 && x * 8 < range && level > 0 && level < range - 1) {
                                        gridMap[level, x * 8] = 'b';
                                    }
                                    if(x * 8 + 1 > 0 && x * 8 + 1 < range && level > 0 && level < range - 1) {
                                        gridMap[level, x * 8+1] = 'b';
                                    }
                                    if(x * 8 + 2 > 0 && x * 8 + 2 < range && level > 0 && level < range - 1) {
                                        gridMap[level, x * 8+2] = 'b';
                                    }
                                }
                            }
                            else {
                                WallPositionUpperLeftCorner[row * 8, (x * 8)] = false;
                            }
                            if (names[x].CompareTo("5") == 0) {
                                WallPositionLowerRightCorner[row * 8, (x * 8)] = true;
                                Model3D wallX = new Model3D(this,
                                                        "CastleWallLowerRightCorner",
                                                        new Vector3(x * spacing * 8,            //X
                                                                    0,   //Y
                                                                    row * spacing * 8),         //Z
                                                        new Vector3(0, 1, 0),
                                                        0.0f,
                                                        "CastleWallLowerRightCorner");
                                Components.Add(wallX);
                                for (int col = x * 8 - 8; col <= x * 8; col++) {
                                    if(row * 8-2 > 0 && row * 8-2 < range && col > 0 && col < range -1) {
                                        gridMap[row * 8-2, col] = 'b';
                                    }
                                    if(row * 8-1 > 0 && row * 8-1 < range && col > 0 && col < range -1) {
                                        gridMap[row * 8-1, col] = 'b';
                                    }
                                    if(row * 8 > 0 && row * 8 < range && col > 0 && col < range -1) {
                                        gridMap[row * 8, col] = 'b';
                                    }
                                    if(row * 8+1 > 0 && row * 8+1 < range && col > 0 && col < range -1) {
                                        gridMap[row * 8+1, col] = 'b';
                                    }
                                    if(row * 8+2 > 0 && row * 8+2 < range && col > 0 && col < range -1) {
                                        gridMap[row * 8+2, col] = 'b';
                                    }
                                }
                                for (int level = row * 8 - 8; level <= row * 8; level++) {
                                    if(x * 8 - 2 > 0 && x * 8 - 2 < range && level > 0 && level < range - 1) {
                                        gridMap[level, x * 8-2] = 'b';
                                    }
                                    if(x * 8 - 1 > 0 && x * 8 - 1 < range && level > 0 && level < range - 1) {
                                        gridMap[level, x * 8-1] = 'b';
                                    }
                                    if(x * 8 > 0 && x * 8 < range && level > 0 && level < range - 1) {
                                        gridMap[level, x * 8] = 'b';
                                    }
                                    if(x * 8 + 1 > 0 && x * 8 + 1 < range && level > 0 && level < range - 1) {
                                        gridMap[level, x * 8+1] = 'b';
                                    }
                                    if(x * 8 + 2 > 0 && x * 8 + 2 < range && level > 0 && level < range - 1) {
                                        gridMap[level, x * 8+2] = 'b';
                                    }
                                }
                            }
                            else {
                                WallPositionLowerRightCorner[row * 8, (x * 8)] = false;
                            }
                            if (names[x].CompareTo("6") == 0) {
                                WallPositionUpperRightCorner[row * 8, (x * 8)] = true;
                                Model3D wallURX = new Model3D(this,
                                                        "CastleWallUpperRightCorner",
                                                        new Vector3(x * spacing * 8,            //X
                                                                    0,   //Y
                                                                    row * spacing * 8),         //Z
                                                        new Vector3(0, 1, 0),
                                                        0.0f,
                                                        "CastleWallUpperRightCorner");
                                Components.Add(wallURX);
                                for (int col = x * 8 - 8; col <= x * 8; col++) {
                                    if(row * 8-2 > 0 && row * 8-2 < range && col > 0 && col < range -1) {
                                        gridMap[row * 8-2, col] = 'b';
                                    }
                                    if(row * 8-1 > 0 && row * 8-1 < range && col > 0 && col < range -1) {
                                        gridMap[row * 8-1, col] = 'b';
                                    }
                                    if(row * 8 > 0 && row * 8 < range && col > 0 && col < range -1) {
                                        gridMap[row * 8, col] = 'b';
                                    }
                                    if(row * 8+1 > 0 && row * 8+1 < range && col > 0 && col < range -1) {
                                        gridMap[row * 8+1, col] = 'b';
                                    }
                                    if(row * 8+2 > 0 && row * 8+2 < range && col > 0 && col < range -1) {
                                        gridMap[row * 8+2, col] = 'b';
                                    }
                                }
                                for (int level = row * 8; level <= row * 8 + 8; level++) {
                                    if(x * 8 - 2 > 0 && x * 8 - 2 < range && level > 0 && level < range - 1) {
                                        gridMap[level, x * 8-2] = 'b';
                                    }
                                    if(x * 8 - 1 > 0 && x * 8 - 1 < range && level > 0 && level < range - 1) {
                                        gridMap[level, x * 8-1] = 'b';
                                    }
                                    if(x * 8 > 0 && x * 8 < range && level > 0 && level < range - 1) {
                                        gridMap[level, x * 8] = 'b';
                                    }
                                    if(x * 8 + 1 > 0 && x * 8 + 1 < range && level > 0 && level < range - 1) {
                                        gridMap[level, x * 8+1] = 'b';
                                    }
                                    if(x * 8 + 2 > 0 && x * 8 + 2 < range && level > 0 && level < range - 1) {
                                        gridMap[level, x * 8+2] = 'b';
                                    }
                                }
                            }
                            else {
                                WallPositionUpperRightCorner[row * 8, (x * 8)] = false;
                            }
                            if (names[x].CompareTo("7") == 0) {
                                WallPositionUpperRightCorner[row * 8, (x * 8)] = true;
                                Model3D wallURX = new Model3D(this,
                                                        "CastleWallTRight",
                                                        new Vector3(x * spacing * 8,            //X
                                                                    0,   //Y
                                                                    row * spacing * 8),         //Z
                                                        new Vector3(0, 1, 0),
                                                        0.0f,
                                                        "CastleWallTRight");
                                Components.Add(wallURX);
                                for (int col = x * 8 - 8; col <= x * 8; col++) {
                                    if(row * 8-2 > 0 && row * 8-2 < range && col > 0 && col < range -1) {
                                        gridMap[row * 8-2, col] = 'b';
                                    }
                                    if(row * 8-1 > 0 && row * 8-1 < range && col > 0 && col < range -1) {
                                        gridMap[row * 8-1, col] = 'b';
                                    }
                                    if(row * 8 > 0 && row * 8 < range && col > 0 && col < range -1) {
                                        gridMap[row * 8, col] = 'b';
                                    }
                                    if(row * 8+1 > 0 && row * 8+1 < range && col > 0 && col < range -1) {
                                        gridMap[row * 8+1, col] = 'b';
                                    }
                                    if(row * 8+2 > 0 && row * 8+2 < range && col > 0 && col < range -1) {
                                        gridMap[row * 8+2, col] = 'b';
                                    }
                                }
                                for (int level = row * 8; level <= row * 8 + 8; level++) {
                                    if(x * 8 - 2 > 0 && x * 8 - 2 < range && level > 0 && level < range - 1) {
                                        gridMap[level, x * 8-2] = 'b';
                                    }
                                    if(x * 8 - 1 > 0 && x * 8 - 1 < range && level > 0 && level < range - 1) {
                                        gridMap[level, x * 8-1] = 'b';
                                    }
                                    if(x * 8 > 0 && x * 8 < range && level > 0 && level < range - 1) {
                                        gridMap[level, x * 8] = 'b';
                                    }
                                    if(x * 8 + 1 > 0 && x * 8 + 1 < range && level > 0 && level < range - 1) {
                                        gridMap[level, x * 8+1] = 'b';
                                    }
                                    if(x * 8 + 2 > 0 && x * 8 + 2 < range && level > 0 && level < range - 1) {
                                        gridMap[level, x * 8+2] = 'b';
                                    }
                                }
                            }
                            else {
                                WallPositionUpperRightCorner[row * 8, (x * 8)] = false;
                            }
                            if (names[x].CompareTo("8") == 0) {
                                WallPositionUpperRightCorner[row * 8, (x * 8)] = true;
                                Model3D wallURX = new Model3D(this,
                                                        "CastleWallTBottom",
                                                        new Vector3(x * spacing * 8,            //X
                                                                    0,   //Y
                                                                    row * spacing * 8),         //Z
                                                        new Vector3(0, 1, 0),
                                                        0.0f,
                                                        "CastleWallTBottom");
                                Components.Add(wallURX);
                                for (int col = x * 8 - 8; col <= x * 8 + 8; col++) {
                                    if(row * 8-2 > 0 && row * 8-2 < range && col > 0 && col < range -1) {
                                        gridMap[row * 8-2, col] = 'b';
                                    }
                                    if(row * 8-1 > 0 && row * 8-1 < range && col > 0 && col < range -1) {
                                        gridMap[row * 8-1, col] = 'b';
                                    }
                                    if(row * 8 > 0 && row * 8 < range && col > 0 && col < range -1) {
                                        gridMap[row * 8, col] = 'b';
                                    }
                                    if(row * 8+1 > 0 && row * 8+1 < range && col > 0 && col < range -1) {
                                        gridMap[row * 8+1, col] = 'b';
                                    }
                                    if(row * 8+2 > 0 && row * 8+2 < range && col > 0 && col < range -1) {
                                        gridMap[row * 8+2, col] = 'b';
                                    }
                                }
                                for (int level = row * 8; level <= row * 8; level++) {
                                    if(x * 8 - 2 > 0 && x * 8 - 2 < range && level > 0 && level < range - 1) {
                                        gridMap[level, x * 8-2] = 'b';
                                    }
                                    if(x * 8 - 1 > 0 && x * 8 - 1 < range && level > 0 && level < range - 1) {
                                        gridMap[level, x * 8-1] = 'b';
                                    }
                                    if(x * 8 > 0 && x * 8 < range && level > 0 && level < range - 1) {
                                        gridMap[level, x * 8] = 'b';
                                    }
                                    if(x * 8 + 1 > 0 && x * 8 + 1 < range && level > 0 && level < range - 1) {
                                        gridMap[level, x * 8+1] = 'b';
                                    }
                                    if(x * 8 + 2 > 0 && x * 8 + 2 < range && level > 0 && level < range - 1) {
                                        gridMap[level, x * 8+2] = 'b';
                                    }
                                }
                            }
                            else {
                                WallPositionUpperRightCorner[row * 8, (x * 8)] = false;
                            }
                        }
                        row++;
                    }
                }
                finally {
                    if (file != null)
                    {
                        file.Close();
                    }
                }
            }
            else {
                System.Console.WriteLine("Error: " + filePath + " does not exist");
                Environment.Exit(0);
            }
        }

        protected void adjustVerticalToTerrain(Vector3 position) {
            float offset = position.Y;
            Vector3 pos = position;
            int scale = 150;
            Vector3 A, B, C, D;
            A.X = (int) (pos.X / scale) * scale;
            A.Z = (int) (pos.Z / scale) * scale;
            A.Y = surfaceHeight((int)A.X, (int) A.Z);
            B.X = A.X + scale;
            B.Z = A.Z;
            B.Y = surfaceHeight((int)B.X, (int) B.Z);
            C.X = A.X;
            C.Z = A.Z + scale;
            C.Y = surfaceHeight((int)C.X, (int)C.Z);
            D.X = A.X + scale;
            D.Z = A.Z + scale;
            D.Y = surfaceHeight((int)D.X, (int)D.Z);

            double distanceToA = Math.Sqrt(Math.Pow(A.X - pos.X, 2) + Math.Pow(A.Z - pos.Z, 2));
            double distanceToD = Math.Sqrt(Math.Pow(D.X - pos.X, 2) + Math.Pow(D.Z - pos.Z, 2));

            float zY;
            float xY;
            if (distanceToA < distanceToD) {
                float amountX = (pos.X - A.X) / scale;
                float amountZ = (pos.Z - A.Z) / scale;
                xY = Vector3.Lerp(A, B, amountX).Y;
                zY = Vector3.Lerp(A, C, amountZ).Y;
                pos.Y = A.Y + (xY - A.Y) + (zY - A.Y) + offset;
            }else {
                float amountX = 1f + ((pos.X - D.X) / scale);
                float amountZ = 1f + ((pos.Z - D.Z) / scale);
                xY = Vector3.Lerp(C, D, amountX).Y;
                zY = Vector3.Lerp(B, D, amountZ).Y;
                pos.Y = D.Y + (xY - D.Y) + (zY - D.Y) + offset;
            }
            position.Y = pos.Y;
        }
        
        private void outPutGridToFile() {
            /*
             *      OUTPUT THE CONTENTS OF GRID TO A FILE
             */
            TextWriter tw = new StreamWriter(".\\grid.txt");
            int count = 0;
            for (int z = 0; z < Range; z++) {
                tw.Write("{0,5:D}", count);
                for (int x = 0; x < Range; x++) {   
                    try {                 
                        tw.Write("" + gridMap[z, x]);
                    }catch(System.IndexOutOfRangeException) {
                    }
                }
                tw.WriteLine();
                count++;
            }
            tw.Close();
        }
        // GAMEOVER SEARCH FOR ME or gameover
        protected override void Update(GameTime gameTime) {
            if((frames++) > 150) {
                probToMoveOutOfRadius = (float)r.NextDouble();
                frames = 0;
            }
            if ((npAvatar.TreasureCount + avatar.TreasureCount) == 5) {
                gameOver = true;
            }
            // set info pane values
            fpsSecond += gameTime.ElapsedGameTime.TotalSeconds;
            updates++;
            TimeSpan ts = gameTime.TotalRealTime;
            GamePadState gamePadState = GamePad.GetState(PlayerIndex.One);
            if (gamePadState.IsConnected) {
                if (gamePadState.Buttons.X == ButtonState.Pressed) {
                    Exit();
                }else if (  gamePadState.Buttons.Y == ButtonState.Pressed && 
                            oldGamePadState.Buttons.Y != ButtonState.Pressed){
                    toggleFullScreen();
                }else if (  gamePadState.Buttons.A == ButtonState.Pressed &&
                            oldGamePadState.Buttons.A != ButtonState.Pressed){
                    nextCamera();
                }else if (  gamePadState.Buttons.B == ButtonState.Pressed &&
                            oldGamePadState.Buttons.B != ButtonState.Pressed) {
                    Fog = ! Fog;
                }else if (  gamePadState.Buttons.RightShoulder == ButtonState.Pressed &&
                            oldGamePadState.Buttons.RightShoulder != ButtonState.Pressed){
                    FixedStepRendering = ! FixedStepRendering;
                }
                oldGamePadState = gamePadState;
            }else { // no gamepad assume use of keyboard
                KeyboardState keyboardState = Keyboard.GetState();
                if (keyboardState.IsKeyDown(Keys.Escape)) { 
                    Exit();
                }else if (keyboardState.IsKeyDown(Keys.B) && !oldKeyboardState.IsKeyDown(Keys.B)){
                    DrawBoundingSpheres = ! DrawBoundingSpheres;
                }else if (keyboardState.IsKeyDown(Keys.C) && !oldKeyboardState.IsKeyDown(Keys.C)){
                    nextCamera();
                }else if (keyboardState.IsKeyDown(Keys.F) && !oldKeyboardState.IsKeyDown(Keys.F)){
                    Fog = ! Fog;
                }else if (keyboardState.IsKeyDown(Keys.N) && !oldKeyboardState.IsKeyDown(Keys.N)){
                    npAvatar.GoToNextTreasure = !npAvatar.GoToNextTreasure;
                }else if (Keyboard.GetState().IsKeyDown(Keys.S) && !oldKeyboardState.IsKeyDown(Keys.C)){
                    toggleFullScreen();
                }else if (keyboardState.IsKeyDown(Keys.T) && !oldKeyboardState.IsKeyDown(Keys.T)){
                    FixedStepRendering = ! FixedStepRendering;
                }else if (keyboardState.IsKeyDown(Keys.Y) && !oldKeyboardState.IsKeyDown(Keys.Y)){
                    YonFlag = !YonFlag;  // toggle Yon clipping value.
                }
                if (keyboardState.IsKeyDown(Keys.M) && npAvatar.Move){
                    npAvatar.Move = false;
                }
                else if (keyboardState.IsKeyDown(Keys.M)){
                    npAvatar.Move = true;
                }
                if (keyboardState.IsKeyDown(Keys.D) && !oldKeyboardState.IsKeyDown(Keys.D)) {
                    foreach (Model3D D in savagePack) {
                        D.Orientation = avatar.Orientation;
                    }
                }
                if(keyboardState.IsKeyDown(Keys.P) && !oldKeyboardState.IsKeyDown(Keys.P)) {
                    if(flockProb == 0.00f) {
                        flockProb = 0.33f;
                    }else if(flockProb == 0.33f) {
                        flockProb = 0.67f;
                    }else if(flockProb == 0.67f) {
                        flockProb = 1.00f;
                    }else if(flockProb == 1.00f) {
                        flockProb = 0.00f;
                    }
                }
                oldKeyboardState = keyboardState;    // Update saved state.
            }
            base.Update(gameTime);  // update all GameComponents and DrawableGameComponents
            currentCamera.updateViewMatrix();
        }

        protected override void Draw(GameTime gameTime) {
            draws++;
            display.Viewport = sceneViewport;
            display.Clear(Color.CornflowerBlue);
            // Draw into inspectorViewport
            display.Viewport = inspectorViewport;
            display.Clear(Color.CornflowerBlue);
            spriteBatch.Begin();
                scoreSprite.Begin();
                scoreSprite.DrawString(scoreFont, "Player 1 Score: " + avatar.TreasureCount, new Vector2(10, 5), Color.Black);
                scoreSprite.DrawString(scoreFont, "Player 2 Score: " + npAvatar.TreasureCount, new Vector2(590, 5), Color.Black);
                scoreSprite.DrawString(scoreFont, "Flocking Probability: " + flockProb, new Vector2(275, 5), Color.Black);
                scoreSprite.DrawString(scoreFont, "Way Point Status: " + npAvatar.WayPointReached, new Vector2(10,20), Color.Black);
                scoreSprite.DrawString(scoreFont, "NPC: (" + npAvatar.iXLoc + ", " + npAvatar.iZLoc + ")", new Vector2(590, 20), Color.Black);
                //if(npAvatar.Bearing != null) {
                //    scoreSprite.DrawString(scoreFont, "WP: (" + npAvatar.Bearing.X + ", " + npAvatar.Bearing.Z + ")", new Vector2(590, 35), Color.Red);
                //}else {
                //    scoreSprite.DrawString(scoreFont, "WP: (" + npAvatar.iXLoc + ", " + npAvatar.iZLoc + ")", new Vector2(590, 35), Color.Blue);
                //}
                if(npAvatar.DesinationExploring != null) {
                    scoreSprite.DrawString(scoreFont, "WP: (" + npAvatar.DesinationExploring.X + ", " + npAvatar.DesinationExploring.Z + ")", new Vector2(590, 35), Color.Red);
                }else {
                    scoreSprite.DrawString(scoreFont, "WP: (" + npAvatar.iXLoc + ", " + npAvatar.iZLoc + ")", new Vector2(590, 35), Color.Blue);
                }
                scoreSprite.DrawString(scoreFont, "Distance to WP: (" + npAvatar.DistanceToWayPoint + ")", new Vector2(590, 50), Color.Red);
                if(npAvatar.TargetTressures.Count != 0) {
                    scoreSprite.DrawString(scoreFont, "Target Tressure Position (" + npAvatar.TargetTressures.Peek().X + ", " + npAvatar.TargetTressures.Peek().Z + ")", new Vector2(10, 50), Color.Red);
                }else {
                    scoreSprite.DrawString(scoreFont, "Target Tressure Position (XXX.XX,ZZZ.ZZ)", new Vector2(10,50),Color.Blue);
                }
                if(npAvatar.Status_Temp != null) {
                    scoreSprite.DrawString(scoreFont, npAvatar.Status_Temp, new Vector2(10, 65), Color.Crimson);
                }
                if (gameOver) {
                    scoreSprite.DrawString(scoreFont, "Game Over!", new Vector2(325, 35), Color.Crimson);
                } else {
                    scoreSprite.DrawString(scoreFont, npAvatar.Status, new Vector2(10, 35), Color.Crimson);
                }
                scoreSprite.End();
            spriteBatch.End();

            // need to restore render state changed by spriteBatch
            // see documentation on SpriteBatch.End() -- all of these probably not needed.
            display.RenderState.DepthBufferEnable = true;
            display.RenderState.AlphaBlendEnable = false;
            display.RenderState.AlphaTestEnable = false;
            display.SamplerStates[0].AddressU = TextureAddressMode.Wrap;
            display.SamplerStates[0].AddressV = TextureAddressMode.Wrap;
            // draw objects in scene 
            display.Viewport = sceneViewport;
            display.RenderState.CullMode = CullMode.None;
            base.Draw(gameTime);  // draw all GameComponents and DrawableGameComponents
        }

        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        static void Main(string[] args) {
            using (Scene scene = new Scene()){ scene.Run(); }
        }
    }
}
