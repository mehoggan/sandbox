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
    /// Terrain represents a ground.
    /// The vertices have position and color.  Terrain width = height.  
    /// Reads two textures to set terrain height and color values.
    /// You might want to pre-compute and store heights of surfaces to be 
    /// returned by the surfaceHeight(x, z) method.
    /// </summary>
    /// 
    public class VertexBox : IndexVertexBuffers {
        protected VertexPositionColor[] vertex;  // scene vertices    
        private BasicEffect effect;
        private GraphicsDevice display;
        private float size;
        private float spacing;
        private Color color;
        private Vector3 pos;

        public VertexBox(Scene aScene, Vector3 position,Vector3 orientAxis, Color oColor ,float fSize) 
                        : base (aScene, "box", position, orientAxis, 10) {
            nVertices = range * range;
            vertex = new VertexPositionColor[36];
            nIndices = (range -1) * (range - 1) * 6;
            indices = new int[nIndices];  // there are 6 indices 2 faces / 4 vertices 
            spacing = scene.Spacing;
            display = scene.Display;
            effect = scene.SceneEffect;
            color = oColor;
            vertexDeclaration = new VertexDeclaration(display, VertexPositionColor.VertexElements);
            size = fSize;
            pos = position;
            changeCubeColor(oColor);
        }
        
        /*  PROPERTIES  */
        public int Range {
            get { return range; }
        }

        public void changeCubeColor(Color c) {
            int i = 0;
            color = c;
            //FRONT TRIANGLES
            vertex[i++]=new VertexPositionColor(new Vector3((pos.X)*spacing, (pos.Y)*spacing, (pos.Z)*spacing),color);
            vertex[i++]=new VertexPositionColor(new Vector3((pos.X+size)*spacing, (pos.Y)*spacing, (pos.Z)*spacing),color);
            vertex[i++]=new VertexPositionColor(new Vector3((pos.X+size)*spacing, (pos.Y+size)*spacing, (pos.Z)*spacing),color);

            vertex[i++]=new VertexPositionColor(new Vector3((pos.X)*spacing, (pos.Y)*spacing, (pos.Z)*spacing),color);
            vertex[i++]=new VertexPositionColor(new Vector3((pos.X+size)*spacing, (pos.Y+size)*spacing, (pos.Z)*spacing),color);
            vertex[i++]=new VertexPositionColor(new Vector3((pos.X)*spacing, (pos.Y+size)*spacing, (pos.Z)*spacing),color);

            //BACK TRIANGLES
            vertex[i++]=new VertexPositionColor(new Vector3((pos.X)*spacing, (pos.Y)*spacing, (pos.Z)*spacing),color);
            vertex[i++]=new VertexPositionColor(new Vector3((pos.X+size)*spacing, (pos.Y)*spacing, (pos.Z)*spacing),color);
            vertex[i++]=new VertexPositionColor(new Vector3((pos.X+size)*spacing, (pos.Y+size)*spacing, (pos.Z)*spacing),color);

            vertex[i++]=new VertexPositionColor(new Vector3((pos.X)*spacing, (pos.Y)*spacing, (pos.Z+size)*spacing),color);
            vertex[i++]=new VertexPositionColor(new Vector3((pos.X+size)*spacing, (pos.Y+size)*spacing, (pos.Z+size)*spacing),color);
            vertex[i++]=new VertexPositionColor(new Vector3((pos.X)*spacing, (pos.Y+size)*spacing, (pos.Z+size)*spacing),color);

            //LEFT TRIANGLES
            vertex[i++]=new VertexPositionColor(new Vector3((pos.X)*spacing, (pos.Y)*spacing, (pos.Z+size)*spacing),color);
            vertex[i++]=new VertexPositionColor(new Vector3((pos.X)*spacing, (pos.Y)*spacing, (pos.Z)*spacing),color);
            vertex[i++]=new VertexPositionColor(new Vector3((pos.X)*spacing, (pos.Y+size)*spacing, (pos.Z)*spacing),color);

            vertex[i++]=new VertexPositionColor(new Vector3((pos.X)*spacing, (pos.Y)*spacing, (pos.Z+size)*spacing),color);
            vertex[i++]=new VertexPositionColor(new Vector3((pos.X)*spacing, (pos.Y+size)*spacing, (pos.Z)*spacing),color);
            vertex[i++]=new VertexPositionColor(new Vector3((pos.X)*spacing, (pos.Y+size)*spacing, (pos.Z+size)*spacing),color);

            //RIGHT TRAINGLES
            vertex[i++]=new VertexPositionColor(new Vector3((pos.X+size)*spacing, (pos.Y)*spacing, (pos.Z+size)*spacing),color);
            vertex[i++]=new VertexPositionColor(new Vector3((pos.X+size)*spacing, (pos.Y)*spacing, (pos.Z)*spacing),color);
            vertex[i++]=new VertexPositionColor(new Vector3((pos.X+size)*spacing, (pos.Y+size)*spacing, (pos.Z)*spacing),color);

            vertex[i++]=new VertexPositionColor(new Vector3((pos.X+size)*spacing, (pos.Y)*spacing, (pos.Z+size)*spacing),color);
            vertex[i++]=new VertexPositionColor(new Vector3((pos.X+size)*spacing, (pos.Y+size)*spacing, (pos.Z)*spacing),color);
            vertex[i++]=new VertexPositionColor(new Vector3((pos.X+size)*spacing, (pos.Y+size)*spacing, (pos.Z+size)*spacing),color);

            //BOTTOM TRIANGLES
            vertex[i++]=new VertexPositionColor(new Vector3((pos.X)*spacing, (pos.Y)*spacing, (pos.Z)*spacing),color);
            vertex[i++]=new VertexPositionColor(new Vector3((pos.X+size)*spacing, (pos.Y)*spacing, (pos.Z)*spacing),color);
            vertex[i++]=new VertexPositionColor(new Vector3((pos.X+size)*spacing, (pos.Y)*spacing, (pos.Z+size)*spacing),color);

            vertex[i++]=new VertexPositionColor(new Vector3((pos.X)*spacing, (pos.Y)*spacing, (pos.Z)*spacing),color);
            vertex[i++]=new VertexPositionColor(new Vector3((pos.X+size)*spacing, (pos.Y)*spacing, (pos.Z+size)*spacing),color);
            vertex[i++]=new VertexPositionColor(new Vector3((pos.X)*spacing, (pos.Y)*spacing, (pos.Z+size)*spacing),color);

            //TOP TRIANGLES
            vertex[i++]=new VertexPositionColor(new Vector3((pos.X)*spacing, (pos.Y+size)*spacing, (pos.Z)*spacing),color);
            vertex[i++]=new VertexPositionColor(new Vector3((pos.X+size)*spacing, (pos.Y+size)*spacing, (pos.Z)*spacing),color);
            vertex[i++]=new VertexPositionColor(new Vector3((pos.X+size)*spacing, (pos.Y+size)*spacing, (pos.Z+size)*spacing),color);

            vertex[i++]=new VertexPositionColor(new Vector3((pos.X)*spacing, (pos.Y+size)*spacing, (pos.Z)*spacing),color);
            vertex[i++]=new VertexPositionColor(new Vector3((pos.X+size)*spacing, (pos.Y+size)*spacing, (pos.Z+size)*spacing),color);
            vertex[i++]=new VertexPositionColor(new Vector3((pos.X)*spacing, (pos.Y+size)*spacing, (pos.Z+size)*spacing),color);

            vb = new VertexBuffer(display, VertexPositionColor.SizeInBytes * vertex.Length, BufferUsage.WriteOnly);
            vb.SetData<VertexPositionColor>(vertex, 0, vertex.Length);
        }

        public override void  Draw(GameTime gameTime) {
            effect.VertexColorEnabled = true;
            if (scene.Fog) {
                effect.FogColor = Color.CornflowerBlue.ToVector3();
                effect.FogStart = scene.FogStart;
                effect.FogEnd = scene.FogEnd;
                effect.FogEnabled = true;
            }
            else {
                effect.FogEnabled = false;
            }
            effect.DirectionalLight0.DiffuseColor = scene.DiffuseLight;
            effect.AmbientLightColor = scene.AmbientLight;
            effect.DirectionalLight0.Direction = scene.LightDirection;
            effect.DirectionalLight0.Enabled = true;             
            effect.View = scene.View;
            effect.Projection = scene.Projection;
            effect.World = Matrix.Identity;
            effect.Begin();
            foreach (EffectPass pass in effect.CurrentTechnique.Passes) {
                pass.Begin();
                display.VertexDeclaration = vertexDeclaration;
                display.Vertices[0].SetSource(vb, 0,VertexPositionColor.SizeInBytes);
                //display.Indices = ib;
                display.DrawPrimitives(PrimitiveType.TriangleList,0,12);
                pass.End();
            }
            effect.End();
        }
    }
}
