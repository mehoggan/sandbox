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

    public class Player : Avatar {
        private GamePadState oldGamePadState;
        private KeyboardState oldKeyboardState;
        private int rotate;
        private float angle;
        private Matrix initialOrientation;
        
        public Player(Scene scene, string label, Vector3 pos, Vector3 orientAxis, float radians, string meshFile)
                        : base(scene, label, pos, orientAxis, radians, meshFile) {  // change names for on-screen display of current camera
            first.Name = "First";
            follow.Name = "Follow";
            above.Name = "Above";
            rotate = 0;
            angle = 0.01f;
            Vector3 oldTranslation = Orientation.Translation;
            Orientation *= Matrix.CreateTranslation(-1 * Orientation.Translation);
            Orientation *= Matrix.CreateRotationY(90 * MathHelper.Pi / 180);
            Orientation *= Matrix.CreateTranslation(oldTranslation);
            initialOrientation = orientation;
        }

        public override void Update(GameTime gameTime) {
            if (!scene.GameOver)
            {
                GamePadState gamePadState = GamePad.GetState(PlayerIndex.One);
                if (gamePadState.IsConnected) {
                    if (gamePadState.Buttons.X == ButtonState.Pressed) {
                        scene.Exit();
                    }
                    else if (gamePadState.Buttons.Y == ButtonState.Pressed &&
                                oldGamePadState.Buttons.Y != ButtonState.Pressed) {
                        scene.toggleFullScreen();
                    }
                    else if (gamePadState.Buttons.A == ButtonState.Pressed &&
                               oldGamePadState.Buttons.A != ButtonState.Pressed) {
                        scene.nextCamera();
                    }
                    else if (gamePadState.Buttons.B == ButtonState.Pressed &&
                               oldGamePadState.Buttons.B != ButtonState.Pressed) {
                        scene.Fog = !scene.Fog;
                    }
                    else if (gamePadState.Buttons.RightShoulder == ButtonState.Pressed &&
                               oldGamePadState.Buttons.RightShoulder != ButtonState.Pressed) {
                        scene.FixedStepRendering = !scene.FixedStepRendering;
                    }
                    if (gamePadState.DPad.Up == ButtonState.Pressed) {
                        step++;
                        moving = true;
                    }else {
                        moving = false;
                    }
                    if (gamePadState.DPad.Down == ButtonState.Pressed) {
                        step--;
                        moving = true;
                    }else {
                        moving = false;
                    }
                    if (gamePadState.DPad.Left == ButtonState.Pressed) {
                        rotate++;
                    }
                    if (gamePadState.DPad.Right == ButtonState.Pressed) {
                        rotate--;
                    }
                    oldGamePadState = gamePadState;
                }
                else
                { // no gamepad assume use of keyboard
                    KeyboardState keyboardState = Keyboard.GetState();
                    if (keyboardState.IsKeyDown(Keys.R) && !oldKeyboardState.IsKeyDown(Keys.R)) {
                        orientation = initialOrientation;
                    }
                    if (keyboardState.IsKeyDown(Keys.Up) || keyboardState.IsKeyDown(Keys.Down)) {
                        moving = true;
                        if (keyboardState.IsKeyDown(Keys.Up)) {
                            int zlocation = (int)(Orientation.Translation.Z / scene.Spacing + 1 * Orientation.Forward.Z);
                            int xlocation = (int)(Orientation.Translation.X / scene.Spacing + 1 * Orientation.Forward.X);
                            //8 - 1 to get a 63 row in
                            if (zlocation >= 8 && zlocation <= scene.Range - (8 - 1)
                                && xlocation >= 8 && xlocation <= scene.Range - (8 - 1) &&
                                (scene.GridMap[(int)zlocation, (int)xlocation] == 'f' || scene.GridMap[(int)zlocation, (int)xlocation] == 'w')) {
                                step++;
                                
                            }
                        }
                        if (keyboardState.IsKeyDown(Keys.Down)) {
                            int zlocation = (int)(Orientation.Translation.Z / scene.Spacing - 1 * Orientation.Forward.Z);
                            int xlocation = (int)(Orientation.Translation.X / scene.Spacing - 1 * Orientation.Forward.X);
                            if (zlocation >= 8 && zlocation <= scene.Range - (8 - 1) &&
                                xlocation >= 8 && xlocation <= scene.Range - (8 - 1) &&
                                (scene.GridMap[(int)zlocation, (int)xlocation] == 'f' || scene.GridMap[(int)zlocation, (int)xlocation] == 'w')) {
                                step--;
                            }
                        }
                    } else {
                        moving = false;
                    }
                    if (keyboardState.IsKeyDown(Keys.Left)) {
                        rotate++;
                    }
                    if (keyboardState.IsKeyDown(Keys.Right)) {
                        rotate--;
                    }
                    if (keyboardState.IsKeyDown(Keys.PageUp)) {
                        vertical++;
                    }
                    if (keyboardState.IsKeyDown(Keys.PageDown)) {
                        vertical--;
                    }
                    oldKeyboardState = keyboardState;    // Update saved state.
                }
                yaw = rotate * angle;
                base.Update(gameTime);
                rotate = step = vertical = 0;
            }
        }
    }
}
