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
    /// Defines the Update(GameTime) method for moving a model.  
    /// Movements: 
    ///   step (forward), stepSize, vertical (+ up, - down), 
    ///   yaw, pitch, and roll.
    /// While abstract, subclasses invoke their base.Update(GameTime) to apply
    /// the inherited movement step values.
    /// </summary>

    public abstract class MovableModel3D : Model3D {

        protected Double pitch, roll, yaw;
        protected int step, vertical; 
        protected int stepSize; 
        protected float slowDown;
        protected float x;
        protected float z;
        protected float x_Prev;
        protected float z_Prev;

        public MovableModel3D(Scene aScene, string label, Vector3 position, Vector3 orientAxis, float radians, string meshFile)
                : base(aScene, label, position, orientAxis, radians, meshFile) {
            reset();
            slowDown = 1;
        }      
      
        public void reset() {
            pitch = roll = yaw = 0;
            step = vertical = 0;
        }

        public float SlowDown {
            get { return slowDown; }
            set { slowDown = value; }
        }

        public float X_Movable {
            get { return x; }
        }

        public float Z_Movable {
            get { return z; }
        }

        public float X_Prev {
            get { return x_Prev; }
        }

        public float Z_Prev {
            get { return z_Prev; }
        }
   
        /// <summary>
        /// The model's orientation matrix will be updated based on movement variable
        /// values.  Note how the location is first saved and the model is translated
        /// to the origin before any rotations are applied.  Models rotate about their
        /// center.  After rotations, the location is reset and updated iff it is not
        /// outside the range of the scene (scene.withinRange(String name, Vector3 location)).  
        /// When movement would exceed the scene's boundaries the model is not moved 
        /// and a message is displayed.
        /// </summary>      
        public override void Update(GameTime gameTime) {
            if (!scene.GameOver) {
                Vector3 startLocation, stopLocation;
                startLocation = stopLocation = Translation;
                Orientation *= Matrix.CreateTranslation(-1 * Translation);        // move to origin
                   
                if(!double.IsNaN(yaw)) {
                    Orientation *= Matrix.CreateRotationY((float)yaw);                       // rotate
                }
                if(!double.IsNaN(pitch)) {
                    Orientation *= Matrix.CreateRotationX((float)pitch);
                }
                if(!double.IsNaN(roll)) {
                    Orientation *= Matrix.CreateRotationZ((float)roll);
                }
                stopLocation += (((step * stepSize)/slowDown) * Forward);                    // move forward
                stopLocation += ((vertical * 100) * Up);                                  // move vertical                           
                if (    scene.withinRange(this.Name, stopLocation) && 
                        scene.GridMap[(int)(stopLocation.Z/scene.Spacing),(int)(stopLocation.X/scene.Spacing)]!='b') {
                    Orientation *= Matrix.CreateTranslation(stopLocation);         // move forward
                }
                else {
                    Orientation *= Matrix.CreateTranslation(startLocation);        // don't move
                }
                x_Prev = x;
                z_Prev = z;
                x = Orientation.Translation.X;
                z = Orientation.Translation.Z;
            }
            base.Update(gameTime);
        } 
    }
}
