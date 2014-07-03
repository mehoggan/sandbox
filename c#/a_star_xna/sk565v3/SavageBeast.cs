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
    public class SavageBeast : MovableModel3D {
        protected Avatar packLeader;
        protected float OriginalXoffset;
        protected float OriginalYoffset;
        protected float OriginalZoffset;
        protected float Xoffset;
        protected float Yoffset;
        protected float Zoffset;
        protected int badgeNumber;
        protected int number_of_frames = 0;
        protected float currentOrientation;
        protected float previousFlocking;
        protected Vector3 packLeaderPreviousLocation;
        protected float prevDistance = 0;
        protected float timer = 0;
        protected float dist;
        protected Vector3 old_Location;
        protected float probabilityToFlock;
        public SavageBeast(Scene aScene, string label, Vector3 position, Vector3 orientAxis, float radians, string meshFile, Avatar leader,
                            int badgenumber)
                : base(aScene, label, position, orientAxis, radians, meshFile) {
            packLeader = leader;
            pitch = roll = yaw = 0;
            step = vertical = 0;
            stepSize = 50;
            OriginalXoffset = position.X;
            OriginalYoffset = position.Y;
            OriginalZoffset = position.Z;
            Xoffset = OriginalXoffset;
            Yoffset = OriginalYoffset;
            Zoffset = OriginalZoffset;
            badgeNumber = badgenumber;
            Orientation = packLeader.Orientation;
            Vector3 translateBack = Orientation.Translation;
            Orientation *= Matrix.CreateTranslation(-Orientation.Translation);
            Orientation *= Matrix.CreateRotationY((float)(6*scene.R.NextDouble() * scene.R.Next(-1, 1)));
            Orientation *= Matrix.CreateTranslation(translateBack);
            Orientation *= Matrix.CreateTranslation(Xoffset, Yoffset, Zoffset);
        }

        public float XOffset {
            get { return Xoffset; }
        }
        public float YOffset {
            get { return Yoffset; }
        }
        public float ZOffset {
            get { return Zoffset; }
        }

        private bool packLeaderMoved() {
            bool retn = false;
            if( packLeader.Moving ) {
                retn = true;
            } else {
                retn = false;
            }
            return retn;
        }

        private float distanceToPackLeader() {
            float distance = 0;
            float Xo = packLeader.X*scene.Spacing;
            float Zo = packLeader.Z*scene.Spacing;
            float Xf = Orientation.Translation.X;
            float Zf = Orientation.Translation.Z;
            distance = (float)Math.Sqrt((Xf-Xo)*(Xf-Xo) + (Zf-Zo)*(Zf-Zo));
            if(++timer == 100) {
                timer = 0;
            }
            if(float.IsNaN(distance)) {
                distance = 0;
            }
            return distance;
        }

        private void breakThePack() {
            Vector3 old = Orientation.Translation;
            Orientation *= Matrix.CreateTranslation(-Orientation.Translation);
            Orientation *= Matrix.CreateRotationY((float)((scene.R.NextDouble() / 15) * scene.R.Next(-6, 6)));
            Orientation *= Matrix.CreateTranslation(old);
        }

        private void flockAroundPackLeader() {
            Vector3 old = Orientation.Translation;
            Orientation *= Matrix.CreateTranslation(-Orientation.Translation);
            Orientation *= Matrix.CreateRotationY((float)((scene.R.NextDouble() / 15) * scene.R.Next(-1, 1)));
            if (dist <= 1000) {
                old.X += Orientation.Backward.X*(float)(scene.Spacing);
                old.Z += Orientation.Backward.Z*(float)(scene.Spacing);
            }
            Orientation *= Matrix.CreateTranslation(old);
        }

        private void flockAroundPackLeaderMoving() {
            Vector3 old = Orientation.Translation;
            Orientation *= Matrix.CreateTranslation(-Orientation.Translation);
            Orientation *= Matrix.CreateRotationY((float)((scene.R.NextDouble() / 15) * scene.R.Next(-1, 1)));
            if (dist <= 1000) {
                if(badgeNumber%2 == 0) {
                    old.X +=    (  
                                    Orientation.Backward.X * (float)(scene.R.NextDouble() * scene.Spacing) +
                                    Orientation.Left.X * (float)(scene.R.NextDouble() * scene.Spacing)
                                );
                    old.Z +=    (
                                    Orientation.Backward.Z * (float)(scene.R.NextDouble() * scene.Spacing) +
                                    Orientation.Left.Z * (float)(scene.R.NextDouble() * scene.Spacing)
                                );
                } else {
                    old.X +=    (
                                    Orientation.Backward.X * (float)(scene.R.NextDouble() * scene.Spacing) +
                                    Orientation.Right.X * (float)(scene.R.NextDouble() * scene.Spacing)
                                );
                    old.Z +=    (
                                    Orientation.Backward.Z * (float)(scene.R.NextDouble() * scene.Spacing) +
                                    Orientation.Right.Z * (float)(scene.R.NextDouble() * scene.Spacing)
                                );
                }
            }
            Orientation *= Matrix.CreateTranslation(old);
        }

        private void trapedFlockMenuver() {
            float MeanCenterX = packLeader.Orientation.Translation.X;
            float MeanCenterZ = packLeader.Orientation.Translation.Z;
            Vector3 u = Vector3.Normalize(Orientation.Forward);
            float randX = MeanCenterX;// + scene.R.Next(-500, 500);
            float randZ = MeanCenterZ;// + scene.R.Next(-500, 500);
            Vector3 offCenter = new Vector3(randX, packLeader.Orientation.Translation.Y, randZ);
            Vector3 v = Vector3.Normalize(offCenter - Orientation.Translation);
            Vector3 r = Vector3.Normalize(Orientation.Right);
            Vector3 l = Vector3.Normalize(Orientation.Left);
            float angle = (float)Math.Acos(Vector3.Dot(u, v));
            float angleR = (float)Math.Acos(Vector3.Dot(r, v));
            float angleL = (float)Math.Acos(Vector3.Dot(l, v));
            if (angleL < angleR) {
                yaw = angle;
            }
            else if (angleR < angleL) {
                yaw = -angle;
            }
            step = (int)(stepSize / 40);
        }

        private void rotateToPackLeader() {
            Vector3 u = Vector3.Normalize(Orientation.Forward);
            Vector3 v = Vector3.Normalize(packLeader.Orientation.Translation - Orientation.Translation);
            Vector3 r = Vector3.Normalize(Orientation.Right);
            Vector3 l = Vector3.Normalize(Orientation.Left);
            float angle = (float)Math.Acos(Vector3.Dot(u,v));
            float angleR = (float)Math.Acos(Vector3.Dot(r,v));
            float angleL = (float)Math.Acos(Vector3.Dot(l,v));
            if(angleL < angleR) {
                yaw = angle;
            }else if(angleR < angleL) {
                yaw = -angle;
            }
        }

        private bool outOfBounds() {
            bool check = false;
            int zlocation = (int)(Orientation.Translation.Z / scene.Spacing);
            int xlocation = (int)(Orientation.Translation.X / scene.Spacing);
            if(zlocation >= 8 && zlocation < scene.Range - 7 && xlocation >= 8 && xlocation < scene.Range - 7) {
                check = false;
            } else {
                check = true;
            }
            return check;
        }

        private bool isCollision() {
            bool collision = false;
            if(!outOfBounds()) {
                int zlocationF = (int)(Orientation.Translation.Z/scene.Spacing + 1 * Orientation.Forward.Z);
                int xlocationF = (int)(Orientation.Translation.X/scene.Spacing + 1 * Orientation.Forward.X);
                int zlocationR = (int)(Orientation.Translation.Z / scene.Spacing + 1 * Orientation.Right.Z);
                int xlocationR = (int)(Orientation.Translation.X / scene.Spacing + 1 * Orientation.Right.X);
                int zlocationL = (int)(Orientation.Translation.Z / scene.Spacing + 1 * Orientation.Left.Z);
                int xlocationL = (int)(Orientation.Translation.X / scene.Spacing + 1 * Orientation.Left.X);
                int zlocationB = (int)(Orientation.Translation.Z / scene.Spacing + 1 * Orientation.Backward.Z);
                int xlocationB = (int)(Orientation.Translation.X / scene.Spacing + 1 * Orientation.Backward.X);
                if(scene.GridMap[(int)zlocationF + 1,xlocationF + 1] == 'b') {
                    collision = true;
                }
                if (scene.GridMap[zlocationR + 1, xlocationR + 1] == 'b') {
                    collision = true;
                }
                if (scene.GridMap[zlocationL + 1, xlocationL + 1] == 'b') {
                    collision = true;
                }
                if(scene.GridMap[zlocationB + 1, xlocationB + 1] == 'b') {
                    collision = true;
                }
            }else {
                collision = true;
            }
            return collision;
        }

        private void changeFacing() {
            Vector3 old = Orientation.Translation;
            Orientation *= Matrix.CreateTranslation(-Orientation.Translation);
            Orientation *= Matrix.CreateRotationY((float)((scene.R.NextDouble() / 12) * scene.R.Next(-1, 1)));
            Orientation *= Matrix.CreateTranslation(old);
        }

        private void shiftForward() {
            Orientation *= Matrix.CreateTranslation(scene.R.Next(-60 ,40)*Orientation.Forward);
        }

        private void shiftRight() {
            Orientation *= Matrix.CreateTranslation(scene.R.Next(-60, 60)*Orientation.Right);
        }

        public override void Update(GameTime gameTime) {
            step = 0;
            yaw = 0;
            if(scene.FlockProb != 1.0f) {
                probabilityToFlock = (float)scene.R.NextDouble();
            } else {
                probabilityToFlock = 1.0f;
            }
            dist = distanceToPackLeader();      //Calculate the distance once
            flockingAlgorithm();
            if(!outOfBounds() /*&& !isCollision()*/) {
                previousFlocking = scene.FlockProb;
                packLeaderPreviousLocation = packLeader.Orientation.Translation;
                prevDistance = distanceToPackLeader();
                step = (int)(stepSize / 40);
            }else {
                Orientation *= Matrix.CreateTranslation(-Orientation.Translation);
                Orientation *= Matrix.CreateTranslation(new Vector3(packLeader.X*scene.Spacing,
                                                            50/*(float)scene.Terrain.surfaceHeight((int)packLeader.X, (int)packLeader.Z)*/,
                                                            packLeader.Z * scene.Spacing));
            }
            this.x_Prev = this.X;
            this.z_Prev = this.Z;
            base.Update(gameTime);
        }
 
        private void flockingAlgorithm() {
            slowDown = 1;           // I DIVIDE THE SPEED BY SLOW DOWN SPEED/1 => SPEED
            old_Location = Orientation.Translation;
            if( outOfBounds() ) {
                rotateToPackLeader();
                trapedFlockMenuver();
            }else {
                if(probabilityToFlock == 1.0f) {
                    if(dist <= (8 * scene.Spacing)) {
                        rotateToPackLeader();
                        if(!packLeaderMoved()) {
                            flockAroundPackLeader();
                            slowDown = 10;
                            step = 0;
                        }else {
                            flockAroundPackLeaderMoving();
                            changeFacing();
                            shiftForward();
                            shiftRight();
                            slowDown = 1.0f;
                        }
                    }else {
                        rotateToPackLeader();
                        if (!packLeaderMoved()) {
                            flockAroundPackLeader();
                            slowDown = 10;
                        }else {
                            flockAroundPackLeaderMoving();
                            changeFacing();
                            shiftForward();
                            shiftRight();
                            slowDown = 1.0f;
                        }
                    }
                } else if(scene.ProbabilityToMoveOutOfRadius > probabilityToFlock) {
                    breakThePack();
                    slowDown = 5;    
                } else if(scene.ProbabilityToMoveOutOfRadius < probabilityToFlock) {
                    if(dist <= (8 * scene.Spacing)) {
                        rotateToPackLeader();
                        if(!packLeaderMoved()) {
                            flockAroundPackLeader();
                            slowDown = 10;
                            step = 0;
                        }else {
                            flockAroundPackLeaderMoving();
                            changeFacing();
                            shiftForward();
                            shiftRight();
                            slowDown = 1.0f;
                        }
                    }else {
                        rotateToPackLeader();
                        if (!packLeaderMoved()) {
                            flockAroundPackLeader();
                            slowDown = 5;
                        }else {
                            flockAroundPackLeaderMoving();
                            changeFacing();
                            shiftForward();
                            shiftRight();
                            slowDown = 1.0f;
                        }
                    }
                }
            }
        }
    }
}
