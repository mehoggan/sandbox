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
    public class Terrain : IndexVertexBuffers {
        protected VertexPositionColor[] vertex;  // scene vertices    
        private int height, width, multiplier = 20, spacing;
        private int[,] terrainHeight;
        private BasicEffect effect;
        private GraphicsDevice display;
        private Texture2D heightTexture, colorTexture;
        private Microsoft.Xna.Framework.Graphics.Color[] heightMap, colorMap;
        
        public Terrain(Scene aScene, string label, Vector3 position,Vector3 orientAxis, float radians, string heightFile, string colorFile) 
                        : base (aScene, label, position, orientAxis, radians) {
            int i;
            range = scene.Range;
            width = height = range;
            nVertices = width * height;
            terrainHeight = new int[width, height];
            vertex = new VertexPositionColor[nVertices];
            nIndices = (width -1) * (height - 1) * 6;
            indices = new int[nIndices];  // there are 6 indices 2 faces / 4 vertices 
            spacing = scene.Spacing;
            // set display information 
            display = scene.Display;
            effect = scene.SceneEffect;
            vertexDeclaration = new VertexDeclaration(display, VertexPositionColor.VertexElements);
            // create heightMap values from heightTexture
            heightTexture = scene.Content.Load<Texture2D>(heightFile);
            heightMap = new Microsoft.Xna.Framework.Graphics.Color[width * height];
            heightTexture.GetData<Microsoft.Xna.Framework.Graphics.Color>(heightMap);
            // create colorMap values from colorTexture
            colorTexture = scene.Content.Load<Texture2D>(colorFile);
            colorMap = new Microsoft.Xna.Framework.Graphics.Color[width * height];
            colorTexture.GetData<Microsoft.Xna.Framework.Graphics.Color>(colorMap);
            // create  vertices for terrain
            Vector4 vector4;
            int vertexHeight;
            i = 0;
            for (int z = 0; z < height; z++) {
                for (int x = 0; x < width; x++) {
                    vector4 = heightMap[i].ToVector4();       // convert packed Rgba32 values to floats
                    vertexHeight = (int)(vector4.X * 255);   // scale vertexHeight 0..255
                    vertexHeight *= multiplier;               // multiply height
                    terrainHeight[x, z] = vertexHeight;       // save height for navigation
                    vertex[i] = new VertexPositionColor (    
                                                            new Vector3(x * spacing, vertexHeight, z * spacing),
                                                            new Color(colorMap[i].ToVector4())
                                                        );
                    i++;
                }
            }
            // free up unneeded maps
            colorMap = null;
            heightMap = null; 
            // set indices clockwise from point of view
            i = 0;
            for (int z = 0; z < height - 1; z++) {
                for (int x = 0; x < width - 1; x++) {
                    indices[i++] = z * width + x;
                    indices[i++] = z * width + x + 1;
                    indices[i++] = (z + 1) * width + x;
                    indices[i++] = (z + 1) * width + x;
                    indices[i++] = z * width + x + 1;
                    indices[i++] = (z + 1) * width + x + 1;
                }
            }
      
            // create VertexBuffer and store on GPU
            vb = new VertexBuffer(display,VertexPositionColor.SizeInBytes * vertex.Length,BufferUsage.WriteOnly);
            vb.SetData<VertexPositionColor>(vertex, 0, vertex.Length);
            // create IndexBuffer and store on GPU
            ib = new IndexBuffer(display,typeof(int), indices.Length, BufferUsage.WriteOnly);
            IB.SetData<int>(indices);     
        }
        
        /*  PROPERTIES  */
        public int Range {
            get { return range; }
        }

        ///<summary>
        /// Height of  surface containing position (x,z) terrain coordinates.
        /// This method is a "stub" for the correct get code.
        /// How would you determine a surface's height at (x,?,z) ? 
        /// </summary>
        /// <param name="x"> left -- right terrain position </param>
        /// <param name="z"> forward -- backward terrain position</param>
        /// <returns> vertical height of surface containing position (x,z)</returns>
        public int surfaceHeight(int x, int z) {
            int ret = 0;
            if(x >= 0 && x < range && z >= 0 && z < range) {
                ret = terrainHeight[x,z];
            }else {
                ret = 0;
            }
            return ret;
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
            effect.World = orientation;
            effect.Begin();
            foreach (EffectPass pass in effect.CurrentTechnique.Passes) {
                pass.Begin();
                display.VertexDeclaration = vertexDeclaration;
                display.Vertices[0].SetSource(vb, 0,VertexPositionColor.SizeInBytes);
                display.Indices = ib;
                display.DrawIndexedPrimitives(PrimitiveType.TriangleList,0,0,nVertices,0, nIndices/3);
                pass.End();
            }
            effect.End();
        }
    }
}
