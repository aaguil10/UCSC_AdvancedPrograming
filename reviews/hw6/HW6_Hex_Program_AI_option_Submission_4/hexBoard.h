//Alexander Sadeghi, Delan Diaz

#ifndef HEXBOARD_H
#define	HEXBOARD_H

#include <cstdlib>
#include <vector>

using namespace std;

enum Space {EMPTY, BLACK, RED};
class hexBoard {
	public:
      	        hexBoard(int thisSideLength): sideLength(thisSideLength){
          		spaces = new vector<Space>(sideLength * sideLength, EMPTY);
      		};
      		// Copy constructor
      		hexBoard(hexBoard const &oldBoard): sideLength(oldBoard.sideLength){
          		spaces = new vector<Space>(*(oldBoard.spaces));
      		}
      		inline int getSize() const {return spaces->size();}
      		int getIndex(unsigned int x, unsigned int y) const;
      		pair<int, int> getCoords(unsigned int index) const;
      		Space getSpace(unsigned int index) const;
      		Space getSpace(unsigned int x, unsigned int y) const;
      		void setSpace(unsigned int index, Space sp);
      		void setSpace(unsigned int x, unsigned int y, Space sp);
      		bool isValidMove(unsigned int x, unsigned int y, bool piRule = false) const;
      		bool isValidMove(unsigned int index, bool piRule = false) const;
      		bool isValidSpace(unsigned int index) const;
      		bool isValidSpace(unsigned int x, unsigned int y) const;
      		const unsigned int sideLength;
    	private:
      		vector<Space>* spaces;
};

inline bool hexBoard::isValidSpace(unsigned int index) const {
    return index < spaces->size();
}

inline bool hexBoard::isValidSpace(unsigned int x, unsigned int y) const {
    return x < sideLength && y < sideLength;
}

inline bool hexBoard::isValidMove(unsigned int x, unsigned int y, bool piRule) const {
    return isValidSpace(x, y) && (getSpace(x, y) == EMPTY || piRule);
}

inline bool hexBoard::isValidMove(unsigned int index, bool piRule) const {
    return isValidSpace(index) && (getSpace(index) == EMPTY || piRule);
}

inline int hexBoard::getIndex(unsigned int x, unsigned int y) const {
    return sideLength*y + x;
}

inline pair<int, int> hexBoard::getCoords(unsigned int index) const {
    int x = index % sideLength;
    int y = index / sideLength;
    return pair<int, int>(x, y);
}

inline Space hexBoard::getSpace(unsigned int index) const {
    return (*spaces)[index];
}

inline Space hexBoard::getSpace(unsigned int x, unsigned int y) const {
    return getSpace(getIndex(x, y));
}

inline void hexBoard::setSpace(unsigned int index, Space sp) {
    (*spaces)[index] = sp;
 }
inline void hexBoard::setSpace(unsigned int x, unsigned int y, Space sp) {
    setSpace(getIndex(x, y), sp);
}
#endif	/* HEXBOARD_H */
