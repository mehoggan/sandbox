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

namespace SK565v3 {

    /// <summary>
    /// A Drawable Object in the scene.  Defines location and orientation.
    /// Object's orientation is a 4 by 4 XNA 2.0 Matrix. 
    /// Object's location is Vector3 describing it position in the scene.
    /// Has good examples of C# Properties (Location, Orientation, Right, Up, and At).
    /// These properties show how the 4 by 4 XNA 2.0 Matrix values are
    /// stored and what they represent.
    /// Properties Right, Up, and At get and set values in matrix orientation.
    /// Right, the object's local X axis, is the lateral unit vector.
    /// Up, the object's local Y axis, is the vertical unit vector.
    /// At, the object's local Z axis, is the forward unit vector.
    /// </summary>

    public abstract class Object3D : DrawableGameComponent {
        protected string name;              // string identifier
        protected static int count = 0;     // count for unique object id
        protected int id;                   // unique identifier
        protected string trace;             // result of 
        protected Scene scene;              // framework scene object
        protected Vector3 location;         // object's position
        protected Matrix orientation;       // object's orientation 
        protected Boolean visible = true;
   
        public Object3D(Scene aScene, string label) : base(aScene) {
            scene = aScene;
            name = label;
            id = count++;
            //Trace = String.Format("Loaded  {0:D2}  {1}", id, Name);
            location = new Vector3();
            orientation = Matrix.Identity;
        }

        public Object3D(Scene aScene, string label, Vector3 position, 
            Vector3 orientAxis, float radians)  : base (aScene)  {
            scene = aScene;
            name = label;
            id = count++;
            //Trace = String.Format("Loaded  {0:D2}  {1}", id, Name);
            orientation = Matrix.Identity;
            orientation *= Matrix.CreateFromAxisAngle(orientAxis, radians);
            location = position;
            orientation *= Matrix.CreateTranslation(location);
        }

        // Properties
        public string Name {
            get { return name; }
            set { name = value; }
        }
        public int Id {
            get { return id; }
        }
        public Matrix Orientation {
            get { return orientation; }
            set { orientation = value; }
        }
        public Vector3 Translation {
            get {return orientation.Translation; }
            set {orientation.Translation = value; }
        }
        public Vector3 Up {
            get { return orientation.Up; }
            set { orientation.Up = value; }
        }
        public Vector3 Down {
            get { return orientation.Down; }
            set { orientation.Down = value; } 
        }
        public Vector3 Right {
            get { return orientation.Right; }
            set { orientation.Right = value; } 
        }
        public Vector3 Left {
            get { return orientation.Left; }
            set { orientation.Left = value; }
        }
        public Vector3 Forward {
            get { return orientation.Forward; }
            set { orientation.Forward = value; } 
        }
        public Vector3 Backward {
            get { return orientation.Backward; }
            set { orientation.Forward = value; } 
        }
    }
}
