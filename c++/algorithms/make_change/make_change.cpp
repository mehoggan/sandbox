#include <vector>
#include <algorithm>
#include <list>
#include <iostream>
typedef std::vector<int>::iterator monetary_finder;

/*!
 * Change System class: Responsible for
 * keeping track of value to make change for
 * and the actual monetary values of our system.
 * To avoid round off error multiply everything by
 * 100 and type cast it to an integer.
 */
class change_system
{
public:
  change_system(float money) :
    m_C(money * 100),
    m_RemainingChange(money * 100)
  {
    m_MonetaryValues.push_back(0.00 * 100);

    /* TODO -- MH Allow for other monetary systems
     * this will require a sort on the values. And
     * allowing the users to pass in a vector.
     */ 
    m_MonetaryValues.push_back(0.01 * 100);
    m_MonetaryValues.push_back(0.05 * 100);
    m_MonetaryValues.push_back(0.10 * 100);
    m_MonetaryValues.push_back(0.25 * 100);
    m_MonetaryValues.push_back(0.50 * 100);
    m_MonetaryValues.push_back(1.00 * 100);
    m_MonetaryValues.push_back(5.00 * 100);
    m_MonetaryValues.push_back(10.00 * 100);
    m_MonetaryValues.push_back(20.00 * 100);
    m_MonetaryValues.push_back(50.00 * 100);
    m_MonetaryValues.push_back(100.00 * 100);

    /*
     * Don't assume that users will give you currency values
     * in order. O(nlgn)
     */
    std::sort(m_MonetaryValues.begin(), m_MonetaryValues.end());
  }
  float money() const {return m_C;}
  float remaining_change() const {return m_RemainingChange;}
  std::vector<int> &get_m_MonetaryValue() { return m_MonetaryValues; }
  float make_change();
private:
  monetary_finder find_largest_smallest_value();
  std::vector<int> m_MonetaryValues; // v(1),v(2),...,v(n)
  float m_C;
  float m_RemainingChange;
};

/*!
 * Find the largest value just below the change
 * remaining. Binary search results in O(lg n) look up
 * complexity
 */
monetary_finder change_system::find_largest_smallest_value()
{
  /*
   * If you know that your largest currency is smaller
   * than what is remaining then just return that
   */
  if(m_MonetaryValues[m_MonetaryValues.size() - 1] < m_RemainingChange) {
    return m_MonetaryValues.end() - 1;
  }

  monetary_finder left = m_MonetaryValues.begin();
  monetary_finder right = m_MonetaryValues.end();

  unsigned int index = std::distance(left, right)/2;
  monetary_finder loc = m_MonetaryValues.begin() + index;

  /*
   * A binary search to find largest value less than
   * the remaining change
   */
  int distance = std::distance(left, right);
  while (distance > 1 && (*loc) != m_RemainingChange) {
    if ((*loc) < m_RemainingChange) {
      left = loc;
    } else if ((*loc) > m_RemainingChange) {
      right = loc;
    }
    distance = std::distance(left, right);
    index = std::distance(left, right)/2;
    loc = left + index;
  }
  /*
   * When left with two elements in the array the choice should
   * be to take the largest. But if it is larger than what is remaining
   * then take the other.
   */
  if ((*loc) != m_RemainingChange) {
    loc = std::max_element(left, right);
    if ((*loc) > m_RemainingChange) {
      loc = left;
    }
  }
  return loc;
}

/*!
 * Method that finds the exact change for the value
 * specified in the constructor of the object. This will
 * be printed to the screen.
 */
float change_system::make_change()
{
  monetary_finder find = find_largest_smallest_value();
  float largest_less_than = (*find);
  while (largest_less_than != 0) {
    while (m_RemainingChange > 0) {
      m_RemainingChange -= largest_less_than;
      if (m_RemainingChange >= 0) {
        std::cout << "You get " << (largest_less_than/100) << std::endl;
      }
    }
    if (m_RemainingChange != 0) {
      m_RemainingChange += largest_less_than;
    }
    find = find_largest_smallest_value();
    largest_less_than = (*find);
  }
  return 0.0;
}

int main (int argc, char *argv[])
{
  std::vector<int> test_value;
  test_value.push_back(6);
  test_value.push_back(8);
  test_value.push_back(11);
  test_value.push_back(12);
  test_value.push_back(13);
  test_value.push_back(16);
  test_value.push_back(19);
  test_value.push_back(21);
  test_value.push_back(22);

  for (std::vector<int>::iterator i = test_value.begin(); i < test_value.end(); ++i) {
    change_system change_for_10cents(*i);
    change_for_10cents.make_change();
    std::cout << "Is what you get back for: " << (*i) << std::endl;
  }
}
