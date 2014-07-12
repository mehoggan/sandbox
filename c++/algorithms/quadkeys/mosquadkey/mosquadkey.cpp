#include <iostream>
#include <iomanip>
#include <utility>
#include <cassert>

std::ostream &operator<<(std::ostream &out,
  const std::pair<unsigned int, unsigned int> &data)
{
  out << std::hex << std::uppercase << std::setfill('0') << std::setw(8)
    << data.first;

  out << std::dec << " ";

  out << std::hex << std::uppercase << std::setfill('0') << std::setw(8)
    << data.second;

  return out;
}

std::ostream &operator<<(std::ostream &out,
  const std::pair<double, double> &data)
{
  out << std::setw(8) << std::setfill(' ') << data.first;

  out << std::dec << " ";

  out << std::setw(8) << std::setfill(' ') << data.second;

  return out;
}

namespace MosQuadBlock
{
  typedef std::pair<double, double> pointd;
  typedef std::pair<unsigned int, unsigned int> pointi;
  typedef std::pair<pointd, pointd> selectiond;
  typedef std::pair<pointi, pointi> selectioni;
  typedef short LOD;

  pointi GenMosGeoPoint(const pointd &geoCoord)
  {
    assert(geoCoord.first >= -180.0 && geoCoord.first <= 180.0);
    assert(geoCoord.second >= -90.0 && geoCoord.second <= 90.0);

    pointi mosGeoCoord;

    unsigned int longitude = (geoCoord.first + 180) / 360.0 * 0xFFFFFFFF;
    unsigned int latitude = (geoCoord.second + 90) / 360.0 * 0xFFFFFFFF;

    mosGeoCoord = std::make_pair(longitude, latitude);

    return mosGeoCoord;
  }

  selectiond SelcetedMosQuadBlocks(const selectiond &sel, LOD lod)
  {
    std::cout << "Selecting by " << sel.first << ", " << sel.second
      << std::endl;

    assert(sel.first.first >= -180.0 && sel.first.second >= -90.0);
    assert(sel.second.first <= 180.0 && sel.second.second <= 90.0);

    pointi se = GenMosGeoPoint(sel.first);
    pointi nw = GenMosGeoPoint(sel.second);

    // Snap sw corner to nearest GeoCoord based on LOD
    // Each LOD divides the previous LOD in half so powers of two work here
    unsigned int pow2_to_divide_by = 32 - lod;
    unsigned int MASK = (~0) << pow2_to_divide_by;
    std::cout << "Previous se corner now " << se << std::endl;
    se.first &= MASK; // Divide then multiply to snap
    se.second &= MASK; // Divide then multiply to snap
    std::cout << "Adjusted se corner now " << se << std::endl;
    std::cout << "Adjusted nw corner now " << nw << std::endl;

    unsigned int deltax = nw.first - se.first;
    unsigned int deltay = nw.second - se.second;

    // Normalize by the appropiate power of two
    deltax = ((deltax & MASK) >> pow2_to_divide_by) + 1;
    deltay = ((deltay & MASK) >> pow2_to_divide_by) + 1;

    std::cout << "The number of columns is " << std::dec << deltax << std::endl;
    std::cout << "The number of rows is " << std::dec << deltay << std::endl;
  }
}

int main (int argc, char *argv[])
{
  MosQuadBlock::pointd se = std::make_pair(-180.0, -90.0);
  MosQuadBlock::pointd nw = std::make_pair(-179.9999999, -89.999999);
  MosQuadBlock::selectiond selb = std::make_pair(se, nw);
  MosQuadBlock::selectiond sela = MosQuadBlock::SelcetedMosQuadBlocks(selb, 31);

  //std::cout << MosQuadBlock::GenMosGeoPoint(std::make_pair(45.0, -90.0)) << std::endl;
}
