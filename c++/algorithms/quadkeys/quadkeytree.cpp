/**
 * Serves as the main data source for all the tests below.
 */
struct QuadKeyTree
{
	static const unsigned short cMaxDepth = 4;

	template <unsigned short DEPTH>
	class QuadKeyHeap
	{
	public:
		/**
		 * ctor
		 */
		explicit QuadKeyHeap(const std::string& startKey = "")
			: m_StartKey(startKey)
		{
			const unsigned short numberOfNodes = NumberOfNodesAtDepth(DEPTH);
			m_QuadHeap.resize(numberOfNodes);
			GenerateQuadHeap();
		}

		const std::vector<std::string>& GetQuadKeyHeap() const
		{
			return m_QuadHeap;
		}

		void ChildrenAtDepthN(std::vector<std::string>& input, unsigned short depth)
		{
			assert(depth <= cMaxDepth);

			std::pair<unsigned short, unsigned short> firstAndLast = FirstAndLastNodeIndexesAtDepthN(depth);

			input.clear();

			input = std::vector<std::string>(m_QuadHeap.begin() + firstAndLast.first,
				m_QuadHeap.begin() + firstAndLast.second);
		}

	private:
		void GenerateQuadHeap()
		{
			m_QuadHeap[0] = m_StartKey;

			for (unsigned short index = 1; index < m_QuadHeap.size(); index += 4)
			{
				unsigned short parentIndex = GetParentIndex(index);
				std::string parentKey = m_QuadHeap[parentIndex];

				unsigned short child0Index = GetChildIndex(parentIndex, 1);
				m_QuadHeap[child0Index] = parentKey + '0';

				unsigned short child1Index = GetChildIndex(parentIndex, 2);
				m_QuadHeap[child1Index] = parentKey + '1';

				unsigned short child2Index = GetChildIndex(parentIndex, 3);
				m_QuadHeap[child2Index] = parentKey + '2';

				unsigned short child3Index = GetChildIndex(parentIndex, 4);
				m_QuadHeap[child3Index] = parentKey + '3';
			}
		}

		unsigned short GetChildIndex(unsigned short parentIndex, unsigned short quadrant)
		{
			return 4 * parentIndex + quadrant;
		}

		unsigned short GetParentIndex(unsigned short index)
		{
			return (index - 1)/ 4;
		}

		/**
		 * Explanation of math:
		 * Note the sum of 4^0 + 4^1 + ... + 4^d uses the geometric sequence formula
		 * sum = 4^(start d) * ((1 - 4^(d + 1)) / (1 - 4))
		 * Where d == depth pased into function.
		 */
		unsigned short NumberOfNodesAtDepth(unsigned short depth)
		{
			signed int numerator =
				static_cast<signed int>(1 - std::pow(4.0f, static_cast<float>(depth + 1)));
			signed int denominator = 1 - 4;

			assert(numerator <= 0 && denominator < 0);

			return numerator / denominator;
		}

		/**
		 * Explanation of math:
		 * Subtract all the nodes above your depth from the last nodes index at that depth
		 */
		std::pair<unsigned short, unsigned short> FirstAndLastNodeIndexesAtDepthN(unsigned short depth)
		{
			if (depth == 0)
			{
				return std::make_pair(0, 1);
			}

			unsigned short firstIndex = NumberOfNodesAtDepth(depth - 1);
			unsigned short lastIndex = NumberOfNodesAtDepth(depth);

			return std::make_pair(firstIndex, lastIndex);
		}

		std::vector<std::string> m_QuadHeap;
		std::string m_StartKey;
	};

	QuadKeyHeap<4> m_QuadKeyHeap;
};

