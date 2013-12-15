#ifndef HCTREE_HPP
#define HCTREE_HPP

#include <queue>
#include <vector>
#include "HCNode.hpp"
class BitInputStream;
class BitOutputStream;

using namespace std;

/** A 'function class' for use as the Compare class in a
 *  priority_queue<HCNode*>.
 *  For this to work, operator< must be defined to
 *  do the right thing on HCNodes.
 */
class HCNodePtrComp {
public:
    bool operator()(HCNode*& lhs, HCNode*& rhs) const {
        return *rhs < *lhs;
    }
};

/** A Huffman Code Tree class.
 *  Not very generic:  Use only if alphabet consists
 *  of unsigned chars.
 */
class HCTree {
private:
    HCNode* root;
    HCNode* zeroNode;
    vector<HCNode*> leaves;
    vector<byte> zeroNodes;
    bool isAdaptive;
    HCNode* transform(HCNode *node);
    void splitZeroNode(int index, HCNode *node);
    void deleteHCNode(HCNode *node);
public:
    
    explicit HCTree(bool isAdaptive) :
        root(0),
        isAdaptive(isAdaptive),
        zeroNodes(0)
    {
        leaves = vector<HCNode*>(256, (HCNode*) 0);
        for (int i = 0; i < 255; i++) {
            zeroNodes.push_back(i);
        }
        
        if (isAdaptive) {
            root = new HCNode(0, 0x00);
            zeroNode = root;
        }
    }

    ~HCTree();

    /** Use the Huffman algorithm to build a Huffman coding trie.
     *  PRECONDITION: freqs is a vector of ints, such that freqs[i] is 
     *  the frequency of occurrence of byte i in the message.
     *  POSTCONDITION:  root points to the root of the trie,
     *  and leaves[i] points to the leaf node containing byte i.
     */
    void build(const vector<int>& freqs);

    /** Write to the given BitOutputStream
     *  the sequence of bits coding the given symbol.
     *  PRECONDITION: build() has been called, to create the coding
     *  tree, and initialize root pointer and leaves vector.
     */
    void encode(byte symbol, BitOutputStream& out) const;
    void adaptive_encode(byte symbol, BitOutputStream& out);
    
    /** Write to the given BitOutputStream
     *  the header of the Huffman Code for future decoding
     *  PRECONDITION: build() has been called, to create the coding
     *  tree, and initialize root pointer and leaves vector.
     */
    void writeHeader(BitOutputStream& out) const;

    /** Return symbol coded in the next sequence of bits from the stream.
     *  PRECONDITION: build() has been called, to create the coding
     *  tree, and initialize root pointer and leaves vector.
     */
    byte decode(BitInputStream& in) const;
    byte adaptive_decode(BitInputStream& in);
    
    /** Return true if the HCTree is empty,
        which indicates that original file is empty.
     */
    bool isEmpty() const;

};

#endif // HCTREE_HPP
