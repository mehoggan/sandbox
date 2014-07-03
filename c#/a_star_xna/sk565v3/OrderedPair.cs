/*  
    COMP-565 Spring 2011
    Group members:
    Matthew Hoggan, mehoggan@gmail.com
    Roman Zulauf, rzulauf@gmail.com
*/

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace SK565v3 {
    public class OrderedPair {
        private float coordX;
        private float coordY;
        private float coordZ;

        public OrderedPair(float x, float y, float z) {
            coordX = x;
            coordY = y;
            coordZ = z;
        }

        public float X {
            get { return coordX; }
            set { coordX = value; }
        }

        public float Y {
            get { return coordY; }
            set { coordY = value; }
        }

        public float Z {
            get { return coordZ; }
            set { coordZ = value; }
        }
    }
}
