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

namespace SK565v3{

    public class Camera{
        public enum CameraEnum { TopDownCamera, FirstCamera, FollowCamera, AboveCamera }
        Avatar avatar;
        private int terrainCenter;
        private Matrix viewMatrix;
        private string name;
        private Scene scene;
        CameraEnum cameraCase;

        public Camera(Scene aScene, CameraEnum cameraType) {
            name = "Whole scene";
            scene = aScene;
            cameraCase = cameraType;
            terrainCenter = scene.TerrainSize / 2;
            updateViewMatrix();
        }

        public Camera(Scene aScene, Avatar anAvatar, CameraEnum cameraType) {
            scene = aScene;
            avatar = anAvatar;
            cameraCase = cameraType;
        }

        // Properties
        public string Name {
            get { return name; }
            set { name = value; }
        }

        public Matrix ViewMatrix {
            get { return viewMatrix; }
        }

        public void updateViewMatrix(){
            switch (cameraCase){
                case CameraEnum.TopDownCamera:{
                    viewMatrix = Matrix.CreateLookAt(   new Vector3(terrainCenter, scene.FarYon - 50, terrainCenter),
                                                        new Vector3(terrainCenter, 0, terrainCenter),
                                                        new Vector3(0, 0, -1));
                    break;
                }
                case CameraEnum.FirstCamera: {
                    viewMatrix = Matrix.CreateLookAt(   avatar.Translation, 
                                                        avatar.Translation + avatar.Forward, 
                                                        avatar.Orientation.Up);
                    viewMatrix *= Matrix.CreateTranslation(0, -300, 0);
                    break;
                }
                case CameraEnum.FollowCamera: {
                    viewMatrix = Matrix.CreateLookAt(   avatar.Translation, avatar.Translation + avatar.Forward,
                                                        avatar.Orientation.Up);
                    viewMatrix *= Matrix.CreateTranslation(0, -1300, -4000);
                    break;
                }
                case CameraEnum.AboveCamera: {
                    viewMatrix = Matrix.CreateLookAt(   new Vector3(avatar.Translation.X, avatar.Translation.Y + 6000,
                                                        avatar.Translation.Z),
                                                        avatar.Translation, new Vector3(0, 0, -1));
                    break;
                }
            }
        }
    }
}
