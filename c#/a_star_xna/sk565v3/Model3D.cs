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
    /// Stationary modeled object in the scene.  The SK565 Scene class creates several examples:
    /// the temple and the four dogs.
    /// </summary>
    public class Model3D : Object3D {
        protected Model model = null; 
        protected Vector3 boundingSphereCenter;
        protected float boundingSphereRadius = 0.0f;  
        protected Matrix boundingSphereWorld;
        private float offset;
        private float Xloc;
        private float Yloc;
        private float Zloc;
      
        public Model3D(Scene aScene, string label, Vector3 position, Vector3 orientAxis, float radians, string fileOfModel) 
                            : base (aScene, label, position, orientAxis, radians) {
            model = scene.Content.Load<Model>(fileOfModel);
            offset = position.Y;
            // compute the translation to the model's bounding sphere
            // center and radius;
            float minX, minY, minZ, maxX, maxY, maxZ;      
            minX = minY = minZ = Int32.MaxValue;
            maxX = maxY = maxZ = Int32.MinValue;
            for (int i = 0; i < model.Meshes.Count; i++) {
                // See if this mesh extends the bounding sphere.
                BoundingSphere aBoundingSphere = model.Meshes[i].BoundingSphere;
                if ((aBoundingSphere.Center.X - aBoundingSphere.Radius) < minX) {
                    minX = aBoundingSphere.Center.X - aBoundingSphere.Radius;
                }
                if ((aBoundingSphere.Center.Y - aBoundingSphere.Radius) < minY) {
                    minY = aBoundingSphere.Center.Y - aBoundingSphere.Radius;
                }
                if ((aBoundingSphere.Center.Z - aBoundingSphere.Radius) < minZ) {
                    minZ = aBoundingSphere.Center.Z  - aBoundingSphere.Radius;
                }
                if ((aBoundingSphere.Center.X + aBoundingSphere.Radius) > maxX) {
                    maxX = aBoundingSphere.Center.X + aBoundingSphere.Radius;       
                }
                if ((aBoundingSphere.Center.Y  + aBoundingSphere.Radius)> maxY) {
                    maxY = aBoundingSphere.Center.Y + aBoundingSphere.Radius;
                }
                if ((aBoundingSphere.Center.Z  + aBoundingSphere.Radius)> maxZ) {
                    maxZ = aBoundingSphere.Center.Z + aBoundingSphere.Radius;
                }
            }
            // get the radius of model's bounding sphere
            // radius temporarily holds the largest diameter
            if ((maxX - minX) > boundingSphereRadius) {
                boundingSphereRadius = maxX - minX;
            }
            if ((maxY - minY) > boundingSphereRadius) {
                boundingSphereRadius = maxY - minY;
            }
            if ((maxZ - minZ) > boundingSphereRadius) {
                boundingSphereRadius = maxZ - minZ;
            }
            //boundingSphereRadius /= 2.0f;  // set the radius from largest diameter
            boundingSphereRadius /= 4.0f;  // set the radius from largest diameter
            // set the center of model's bounding sphere
            boundingSphereCenter = new Vector3(minX + boundingSphereRadius, minY + boundingSphereRadius, minZ + boundingSphereRadius);
        }
      
        /// <summary>
        /// Return the center of the model's bounding sphere
        /// </summary>
        public Vector3 BoundingSphereCenter {
            // get { return Translation * boundingSphereCenter; }}
            get { return boundingSphereCenter;}
        }
        
        public float X {
            get { return Xloc; }
        }

        public float Z {
            get { return Zloc; }
        }

        /// <summary>
        /// Return the radius of the model's bounding sphere
        /// </summary>      
        public float BoundingSphereRadius {
            get { return boundingSphereRadius; }
        }

        // override virtual DrawableGameComponent methods                   
        public override void Update(GameTime gameTime) {
            this.Xloc = Orientation.Translation.X/scene.Spacing;
            this.Zloc = Orientation.Translation.Z/scene.Spacing;
            adjustVerticalToTerrain();
            // set center to be a translation from the model's position (Translation)
            boundingSphereCenter = Translation;  // set center to be a translation from the    
            boundingSphereWorld = Matrix.CreateScale(boundingSphereRadius);
            boundingSphereWorld *= Matrix.CreateTranslation(boundingSphereCenter);
        }
            
        public override void  Draw(GameTime gameTime) {
            if (visible) {
                Matrix[] modelTransforms = new Matrix[model.Bones.Count];
                foreach (ModelMesh mesh in model.Meshes) {
                    model.CopyAbsoluteBoneTransformsTo(modelTransforms);
                    foreach (BasicEffect effect in mesh.Effects) {
                        effect.EnableDefaultLighting();
                        if (scene.Fog) {
                            //scene.DrawBoundingSpheres = false;
                            effect.FogColor = Color.CornflowerBlue.ToVector3();
                            effect.FogStart = scene.FogStart;
                            effect.FogEnd = scene.FogEnd;
                            effect.FogEnabled = true;
                        }else {
                            effect.FogEnabled = false;
                        }
                        effect.DirectionalLight0.DiffuseColor = scene.DiffuseLight;
                        effect.AmbientLightColor = scene.AmbientLight;
                        effect.DirectionalLight0.Direction = scene.LightDirection;
                        effect.DirectionalLight0.Enabled = true;
                        effect.View = scene.View;
                        effect.Projection = scene.Projection;
                        effect.World = modelTransforms[mesh.ParentBone.Index] * orientation;
                    }
                    mesh.Draw();
                }
                // draw the bounding sphere with blending ?
                if (scene.DrawBoundingSpheres) {
                    foreach (ModelMesh mesh in scene.BoundingSphere3D.Meshes) {
                        model.CopyAbsoluteBoneTransformsTo(modelTransforms);
                           foreach (BasicEffect effect in mesh.Effects) {
                            effect.EnableDefaultLighting();
                            if (scene.Fog) {
                                effect.FogColor = Color.CornflowerBlue.ToVector3();
                                effect.FogStart = 50;
                                effect.FogEnd = 500;
                                effect.FogEnabled = true;
                            }else {
                                effect.FogEnabled = false;
                            }
                            effect.DirectionalLight0.DiffuseColor = scene.DiffuseLight;
                            effect.AmbientLightColor = scene.AmbientLight;
                            effect.DirectionalLight0.Direction = scene.LightDirection;
                            effect.DirectionalLight0.Enabled = true;
                            effect.View = scene.View;
                            effect.Projection = scene.Projection;
                            effect.World = boundingSphereWorld * modelTransforms[mesh.ParentBone.Index];// *
                            // boundingSphereWorld;
                        }
                        scene.setBlendingState(true);
                        mesh.Draw();
                        scene.setBlendingState(false);
                    }
                }
            }
        }

        protected void adjustVerticalToTerrain() {
            Vector3 pos = orientation.Translation;
            int scale = 150;
            Vector3 A, B, C, D;
            A.X = (int) (pos.X / scale) * scale;
            A.Z = (int) (pos.Z / scale) * scale;
            A.Y = scene.surfaceHeight((int)A.X, (int) A.Z);
            B.X = A.X + scale;
            B.Z = A.Z;
            B.Y = scene.surfaceHeight((int)B.X, (int) B.Z);
            C.X = A.X;
            C.Z = A.Z + scale;
            C.Y = scene.surfaceHeight((int)C.X, (int)C.Z);
            D.X = A.X + scale;
            D.Z = A.Z + scale;
            D.Y = scene.surfaceHeight((int)D.X, (int)D.Z);

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
            orientation.Translation = pos;
        }
    }
}