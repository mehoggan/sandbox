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
    /// An example of how to override the MovableModel3D's Update(GameTime) to 
    /// animate a model.  The actual update of values is done by calling the 
    /// base.Update(GameTime) method of MovableModel3D.
    /// </summary>
    public class Cloud : MovableModel3D {
        float angle;
        Matrix initialOrientation;

        // Constructor
        public Cloud(Scene scene, string label, Vector3 position, Vector3 orientAxis, float radians, string meshFile)
            : base(scene, label, position, orientAxis, radians, meshFile) {
            angle = (float) (2*Math.PI) / 3600.0f; // rotate once every minute
            initialOrientation = Orientation;      // save orientation so rotations don't accumulate
        } 
  
        public override void Update(GameTime gameTime) {
            Orientation = initialOrientation;      // always start with initial orientation  
            yaw += angle;
            if (yaw >= 2*Math.PI) {
                yaw = 0;
            }
            base.Update(gameTime);

        }

    }
}
