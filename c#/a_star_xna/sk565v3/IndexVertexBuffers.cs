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
    public abstract class IndexVertexBuffers : Object3D  {
        protected int range, nVertices, nIndices;
        protected VertexDeclaration vertexDeclaration;
        protected VertexBuffer vb = null;
        protected IndexBuffer ib = null;
        protected int[] indices;  // indexes for IndexBuffer -- define face vertice indexes clockwise 

        public IndexVertexBuffers(Scene aScene, string label, Vector3 position,Vector3 orientAxis, float radians) 
                                : base (aScene, label, position, orientAxis, radians) { 
        }

        // Properties
        public VertexBuffer VB {
            get { return vb; }
            set { vb = value; }
        }

        public IndexBuffer IB {
            get { return ib; }
            set { ib = value; }
        }
    }
}
