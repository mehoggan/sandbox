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
    public abstract class Avatar : MovableModel3D {
        protected Camera avatarCamera, first, follow, above;
        public enum CameraCase { FirstCamera, FollowCamera, AboveCamera }
        private SoundEffect collectedSound;
        private int treasureCount;
        protected bool move;
        protected bool moving = true;

        public Avatar(Scene scene, string label, Vector3 position, Vector3 orientAxis, float radians, string meshFile)
                        : base(scene, label, position, orientAxis, radians, meshFile) {
            stepSize = 40;  // set as function of height original --> /*10*/
            first =  new Camera(scene, this, Camera.CameraEnum.FirstCamera); 
            follow = new Camera(scene, this, Camera.CameraEnum.FollowCamera);
            above =  new Camera(scene, this, Camera.CameraEnum.AboveCamera);
            scene.addCamera(first);
            scene.addCamera(follow);
            scene.addCamera(above);
            avatarCamera = first;
            collectedSound = scene.Content.Load<SoundEffect>("TreasureCollected");
        }

        // Properties
        public bool Moving {
            get { return moving; }
        }

        public int TreasureCount {
            get { return treasureCount; }
        }
        public bool Move {
            set { move = value; }
            get { return move; }
        }
        public Camera AvatarCamera {
            get { return avatarCamera; }
            set { avatarCamera = value;}
        }
        public Camera First {
            get { return first; }
        }
        public Camera Follow {
            get { return follow; }
        }
        public Camera Above {
            get { return above; }
        }
        // Methods
        public override string ToString() {
            return Name;
        }
        public void updateCamera() {
            avatarCamera.updateViewMatrix();
        }
      
        public override void Update(GameTime gameTime) {       
            base.Update(gameTime);
            tagTreasure();
        }

        void tagTreasure() {
            Vector3 position = orientation.Translation;
            foreach (Object3D treasure in scene.Treasures) {
                if (treasure.Visible) {
                    Vector3 treasurePosition = treasure.Translation;
                    double distance = Math.Sqrt(Math.Pow(position.X - treasurePosition.X, 2) + Math.Pow(position.Z - treasurePosition.Z, 2));
                    if (distance < 1000) {
                        collectedSound.Play();
                        treasure.Visible = false;
                        treasureCount++;
                    }
                }
            }
        }

        bool checkCollisionAgainstAllObjects() {
            return true;
        }
   }              
}
