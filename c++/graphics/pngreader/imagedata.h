#ifndef IMAGE_DATA_
#define IMAGE_DATA_

 #include <stdexcept>

template <typename data_type>
class ImageData 
{
public:
  ImageData(unsigned long width, unsigned long height);
  ~ImageData();
  data_type **get_data();
  unsigned long int get_width() const
  {
    return _m_Width;
  }
  unsigned long int get_height() const
  {
    return _m_Height;
  }
protected:
  ImageData(ImageData &copy);
  ImageData& operator= (ImageData &copy);
private:
  data_type **_m_rData;
  unsigned long _m_Width;
  unsigned long _m_Height;
};

template <typename data_type>
ImageData<data_type>::ImageData(unsigned long width, unsigned long height) :
  _m_rData(NULL),
  _m_Width(width),
  _m_Height(height)
{
  if (width == 0 || height == 0)
    throw std::runtime_error("Invalid width or height");

  try {
    _m_rData = new data_type*[_m_Height]();
    for (unsigned long int i = 0; i < _m_Height; ++i) {
      _m_rData[i] = NULL;
    }
    for (unsigned long int i = 0; i < _m_Height; ++i) {
      _m_rData[i] = new data_type[_m_Width];
    }
  }
  catch (std::bad_alloc e) {
    throw std::runtime_error("Failure to create space for Image");
  }
}

template <typename data_type>
ImageData<data_type>::~ImageData()
{
  for (unsigned long i = 0; i < _m_Height; ++i) {
     delete [] _m_rData[i];
     _m_rData[i] = NULL;
  }
  delete [] _m_rData;
  _m_rData = NULL;
}

template <typename data_type>
data_type **ImageData<data_type>::get_data()
{
  return _m_rData;
}

#endif
