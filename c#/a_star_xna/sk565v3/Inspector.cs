/* Copyright (C) 2010 G. Michael Barnes
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
    /// Provides a top 5 line  viewport information display.  
    /// This display can be used for help, game feedback, visual debugging.
    /// Inspector is used with a XNA application designed to have two viewports:
    ///     top viewport for displaying Inspector information
    ///     bottom viewport for display a graphic scene
    ///  
    /// Inspector's client must provide viewport and font values.
    ///  
    /// Inspector manages 20 lines of information display:
    ///    help     5 lines displayed with infoCount == 0 && showHelp, set with setInfo()
    ///    info     5 lines displayed with infoCount == 0 && !showHelp, set with setInfo();
    ///    matrix   5 lines displayed with infoCount == 1, set with setMatrix();
    ///    misc     5 lines displayed with infoCount == 2 && showMisc, set with setInfo();
    ///    
    /// Inspector expects its client's to respond to the following key events:
    ///    H, h  showHelp()  -- toggles between help and info displays for Draw
    ///    I, i  toggles between  help/info, matrix, or misc displays for Draw();
    ///          The display of misc can be enabled/disabled with ShowMisc property.
    /// 
    /// Mike Barnes
    /// 1/ 25 /2010  last updated
    /// </summary>
    public class Inspector {
        // Display constants
        private const int InfoPaneSize = 5;   // number of lines / info display pane
        private const int InfoDisplayStrings = 20;  // number of total display strings
        private const int InfoBase = 5;    // base to offset for display strings
        private const int MatrixBase = 10;
        private const int MiscBase =  15;
        // Screen Viewport and text fonts and display information variables
        private Viewport infoViewport;
        private SpriteFont infoFont;
        private Vector2[] FontPos;
        private string[] infoString;  // first 5 are for help 
        private int infoCount, infoBase;
        private bool showHelp = true;  // initially show help
        private bool showMisc = true;  // initially show miscellaneous

        /// <summary>
        /// Set the boolean flag to show help or information in the first pane
        /// </summary>
        public bool ShowHelp {
            get { return showHelp; }
            set { showHelp = value; 
                if (showHelp) {
                    infoCount = 0;
                }
            }
        }
        /// <summary>
        /// Set the boolean flag to show the third, miscellaneous, pane or not
        /// </summary>      
        public bool ShowMisc {
            get { return showMisc; }
            set { showMisc = value; }
        }
        /// <summary>
        /// Inspector's constructor
        /// </summary>
        /// <param name="aDisplay"> the client's GraphicsDevice</param>
        /// <param name="aViewport"> the client's inspector viewport</param>
        /// <param name="informationFont"> font to use -- Courier New</param>     
        public Inspector(GraphicsDevice aDisplay,Viewport aViewport, SpriteFont informationFont) {
            infoFont = informationFont;
            infoCount = 0;
            // create and initialize display strings
            infoString = new string[InfoDisplayStrings];
            for (int i = 0; i < InfoDisplayStrings; i++){
                infoString[i] = " ";
            }
            // initialize font and display strings values
            FontPos = new Vector2[InfoPaneSize];
            for (int i = 0; i < InfoPaneSize; i++){
                FontPos[i] = new Vector2(infoViewport.X + 10.0f,
                infoViewport.Y + (i * infoFont.LineSpacing));
            }
         }    
      
        /// <summary>
        /// showInfo() is an event handler for the client's 'I', 'i' 
        /// user input.  Toggles the information display pane to be drawn.
        /// </summary>
        public void showInfo() {
            if (showMisc) {
                infoCount = (infoCount + 1) % 3;  // infoCount values == {0, 1, 2}
            }else {
                infoCount = (infoCount + 1) % 2;  // don't show miscellaneous strings
            }
        }
      
        /// <summary>
        /// setInfo used to set individual string values for display.
        /// Can be used to set any of 20 (0..19) string values.
        /// Help is considered to be strings 0..4
        /// Info in strings 5..9
        /// Matrix in strings 10..14
        /// Miscellaneous in strings 15..19
        /// </summary>
        /// <param name="stringIndex"> 0..19 index of string to set</param>
        /// <param name="str"> value of string</param>
        public void setInfo(int stringIndex, string str) {
            if (stringIndex >= 0 && stringIndex < InfoDisplayStrings) {
                infoString[stringIndex] = str;
            }
        }   

        /// <summary>
        /// setMatrices displays two labelled matrices in the second info pane.
        /// Usually this is a "player's" or "NPavatar's" world, and current camera matrices.
        /// </summary>
        /// <param name="label1"> Description of first matrix</param>
        /// <param name="label2"> Description of second matrix</param>
        /// <param name="m1"> first matrix</param>
        /// <param name="m2"> second matrix</param>
        public void setMatrices(string label1, string label2, Matrix m1, Matrix m2) {
            infoBase = MatrixBase;
            infoString[infoBase++] = string.Format("      | {0,-43:s} |  {1,-43:s}", label1, label2);
            infoString[infoBase++] = string.Format("right | {0,10:f2} {1,10:f2} {2,10:f2} {3,10:f2} |  {4,10:f2} {5,10:f2} {6,10:f2} {7,10:f2}",
                                                    m1.M11, m1.M12, m1.M13, m1.M14,     m2.M11, m2.M12, m2.M13, m2.M14);
            infoString[infoBase++] = string.Format("   up | {0,10:f2} {1,10:f2} {2,10:f2} {3,10:f2} |  {4,10:f2} {5,10:f2} {6,10:f2} {7,10:f2}",
                                                    m1.M21, m1.M22, m1.M23, m1.M24,     m2.M21, m2.M22, m2.M23, m2.M24);
            infoString[infoBase++] = string.Format(" back | {0,10:f2} {1,10:f2} {2,10:f2} {3,10:f2} |  {4,10:f2} {5,10:f2} {6,10:f2} {7,10:f2}",
                                                    m1.M31, m1.M32, m1.M33, m1.M34,     m2.M31, m2.M32, m2.M33, m2.M34);
            infoString[infoBase++] = string.Format("  pos | {0,10:f2} {1,10:f2} {2,10:f2} {3,10:f2} |  {4,10:f2} {5,10:f2} {6,10:f2} {7,10:f2}",
                                                    m1.M41, m1.M42, m1.M43, m1.M44,     m2.M41, m2.M42, m2.M43, m2.M44);
        }
      
        /// <summary>
        /// Draw the current information pane in the inspector display.
        /// Called by the client's Draw(...) method.
        /// </summary>
        /// <param name="spriteBatch"> needed to set display strings</param>
        public void Draw(SpriteBatch spriteBatch) {
            //Vector2 FontOrigin;
            //if (infoCount == 0 && showHelp) {// strings 0..4
            //    for (int i = 0; i < InfoPaneSize; i++) {
            //        FontOrigin = infoFont.MeasureString(infoString[i]);
            //        spriteBatch.DrawString(infoFont, infoString[i], FontPos[i], Color.Black); 
            //    }
            //}
            //else if (infoCount == 0 && !showHelp) { // show info  display strings 5..9
            //    infoBase = InfoBase;
            //    for (int i = 0; i < InfoPaneSize; i++) {
            //        FontOrigin = infoFont.MeasureString(infoString[infoBase + i]);
            //        spriteBatch.DrawString(infoFont, infoString[infoBase + i], FontPos[i], Color.Black); 
            //    }
            //}
            //else if (infoCount == 1) { // show matrix information strings 10..14
            //    int infoBase = MatrixBase;
            //    for (int i = 0; i < InfoPaneSize; i++) {
            //        FontOrigin = infoFont.MeasureString(infoString[infoBase + i]);
            //        spriteBatch.DrawString(infoFont, infoString[infoBase + i], FontPos[i], Color.Black); 
            //    }
            //}
            //else if (infoCount == 2 && showMisc) { // show miscellaneous info stings 15..19
            //    int infoBase = MiscBase;
            //    for (int i = 0; i < InfoPaneSize; i++) {
            //        FontOrigin = infoFont.MeasureString(infoString[infoBase + i]);
            //        spriteBatch.DrawString(infoFont, infoString[infoBase + i], FontPos[i], Color.Black); 
            //    }
            //}
        }
    }
 }
