#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <stack>
#include <cstdio>
#include <cmath>
#include <cstring>
using namespace std;

#define INT_MIN (1<<31)
#define INT_MAX (~INT_MIN)
#define UNREACHABLE (INT_MAX>>2)
#define INF (1e300)
#define eps (1e-9)
#define MODULO 1000000007

ifstream fin("11512_input.txt");
#define cin fin
#define MAX_CHAR 256

typedef struct SuffixTreeNode {
  struct SuffixTreeNode * children[MAX_CHAR];
  struct SuffixTreeNode * suffixLink;
  int start;
  int * end;
  int suffixIndex;
} Node;

class SuffixTree {
public:
  Node * root;
  Node * lastNewNode;
  Node * activeNode;
  int activeEdge;
  int activeLength;
  int remainingSuffixCount;
  int leafEnd;
  int * rootEnd;
  int * splitEnd;
  int size;
  string text;

  SuffixTree(string s) {
    root = NULL;
    lastNewNode = NULL;
    activeNode = NULL;
    activeEdge = -1;
    activeLength = 0;
    remainingSuffixCount = 0;
    leafEnd = -1;
    rootEnd = NULL;
    splitEnd = NULL;
    size = -1;
    text = s;
    buildSuffixTree();
  }

  Node *newNode(int start, int *end)
  {
      Node *node =(Node*) malloc(sizeof(Node));
      int i;
      for (i = 0; i < MAX_CHAR; i++)
            node->children[i] = NULL;
    
      /*For root node, suffixLink will be set to NULL
      For internal nodes, suffixLink will be set to root
      by default in  current extension and may change in
      next extension*/
      node->suffixLink = root;
      node->start = start;
      node->end = end;
    
      /*suffixIndex will be set to -1 by default and
        actual suffix index will be set later for leaves
        at the end of all phases*/
      node->suffixIndex = -1;
      return node;
  }
    
  int edgeLength(Node *n) {
      if(n == root)
          return 0;
      return *(n->end) - (n->start) + 1;
  }
    
  int walkDown(Node *currNode)
  {
      /*activePoint change for walk down (APCFWD) using
       Skip/Count Trick  (Trick 1). If activeLength is greater
       than current edge length, set next  internal node as
       activeNode and adjust activeEdge and activeLength
       accordingly to represent same activePoint*/
      if (activeLength >= edgeLength(currNode))
      {
          activeEdge += edgeLength(currNode);
          activeLength -= edgeLength(currNode);
          activeNode = currNode;
          return 1;
      }
      return 0;
  }
    
  void extendSuffixTree(int pos)
  {
      /*Extension Rule 1, this takes care of extending all
      leaves created so far in tree*/
      leafEnd = pos;
    
      /*Increment remainingSuffixCount indicating that a
      new suffix added to the list of suffixes yet to be
      added in tree*/
      remainingSuffixCount++;
    
      /*set lastNewNode to NULL while starting a new phase,
       indicating there is no internal node waiting for
       it's suffix link reset in current phase*/
      lastNewNode = NULL;
    
      //Add all suffixes (yet to be added) one by one in tree
      while(remainingSuffixCount > 0) {
    
          if (activeLength == 0)
              activeEdge = pos; //APCFALZ
    
          // There is no outgoing edge starting with
          // activeEdge from activeNode
          if (activeNode->children[text[activeEdge]] == NULL)
          {
              //Extension Rule 2 (A new leaf edge gets created)
              activeNode->children[text[activeEdge]] =
                                            newNode(pos, &leafEnd);
    
              /*A new leaf edge is created in above line starting
               from  an existng node (the current activeNode), and
               if there is any internal node waiting for it's suffix
               link get reset, point the suffix link from that last
               internal node to current activeNode. Then set lastNewNode
               to NULL indicating no more node waiting for suffix link
               reset.*/
              if (lastNewNode != NULL)
              {
                  lastNewNode->suffixLink = activeNode;
                  lastNewNode = NULL;
              }
          }
          // There is an outgoing edge starting with activeEdge
          // from activeNode
          else
          {
              // Get the next node at the end of edge starting
              // with activeEdge
              Node *next = activeNode->children[text[activeEdge]];
              if (walkDown(next))//Do walkdown
              {
                  //Start from next node (the new activeNode)
                  continue;
              }
              /*Extension Rule 3 (current character being processed
                is already on the edge)*/
              if (text[next->start + activeLength] == text[pos])
              {
                  //If a newly created node waiting for it's 
                  //suffix link to be set, then set suffix link 
                  //of that waiting node to curent active node
                  if(lastNewNode != NULL && activeNode != root)
                  {
                      lastNewNode->suffixLink = activeNode;
                      lastNewNode = NULL;
                  }
   
                  //APCFER3
                  activeLength++;
                  /*STOP all further processing in this phase
                  and move on to next phase*/
                  break;
              }
    
              /*We will be here when activePoint is in middle of
                the edge being traversed and current character
                being processed is not  on the edge (we fall off
                the tree). In this case, we add a new internal node
                and a new leaf edge going out of that new node. This
                is Extension Rule 2, where a new leaf edge and a new
              internal node get created*/
              splitEnd = (int*) malloc(sizeof(int));
              *splitEnd = next->start + activeLength - 1;
    
              //New internal node
              Node *split = newNode(next->start, splitEnd);
              activeNode->children[text[activeEdge]] = split;
    
              //New leaf coming out of new internal node
              split->children[text[pos]] = newNode(pos, &leafEnd);
              next->start += activeLength;
              split->children[text[next->start]] = next;
    
              /*We got a new internal node here. If there is any
                internal node created in last extensions of same
                phase which is still waiting for it's suffix link
                reset, do it now.*/
              if (lastNewNode != NULL)
              {
              /*suffixLink of lastNewNode points to current newly
                created internal node*/
                  lastNewNode->suffixLink = split;
              }
    
              /*Make the current newly created internal node waiting
                for it's suffix link reset (which is pointing to root
                at present). If we come across any other internal node
                (existing or newly created) in next extension of same
                phase, when a new leaf edge gets added (i.e. when
                Extension Rule 2 applies is any of the next extension
                of same phase) at that point, suffixLink of this node
                will point to that internal node.*/
              lastNewNode = split;
          }
    
          /* One suffix got added in tree, decrement the count of
            suffixes yet to be added.*/
          remainingSuffixCount--;
          if (activeNode == root && activeLength > 0) //APCFER2C1
          {
              activeLength--;
              activeEdge = pos - remainingSuffixCount + 1;
          }
          else if (activeNode != root) //APCFER2C2
          {
              activeNode = activeNode->suffixLink;
          }
      }
  }
    
  void print(int i, int j)
  {
      int k;
      for (k=i; k<=j; k++)
          printf("%c", text[k]);
  }
    
  //Print the suffix tree as well along with setting suffix index
  //So tree will be printed in DFS manner
  //Each edge along with it's suffix index will be printed
  void setSuffixIndexByDFS(Node *n, int labelHeight)
  {
      if (n == NULL)  return;
    
      if (n->start != -1) //A non-root node
      {
          //Print the label on edge from parent to current node
          //Uncomment below line to print suffix tree
         // print(n->start, *(n->end));
      }
      int leaf = 1;
      int i;
      for (i = 0; i < MAX_CHAR; i++)
      {
          if (n->children[i] != NULL)
          {
              //Uncomment below two lines to print suffix index
             // if (leaf == 1 && n->start != -1)
               //   printf(" [%d]\n", n->suffixIndex);
    
              //Current node is not a leaf as it has outgoing
              //edges from it.
              leaf = 0;
              setSuffixIndexByDFS(n->children[i], labelHeight +
                                    edgeLength(n->children[i]));
          }
      }
      if (leaf == 1)
      {
          n->suffixIndex = size - labelHeight;
          //Uncomment below line to print suffix index
          //printf(" [%d]\n", n->suffixIndex);
      }
  }
    
  void freeSuffixTreeByPostOrder(Node *n)
  {
      if (n == NULL)
          return;
      int i;
      for (i = 0; i < MAX_CHAR; i++)
      {
          if (n->children[i] != NULL)
          {
              freeSuffixTreeByPostOrder(n->children[i]);
          }
      }
      if (n->suffixIndex == -1)
          free(n->end);
      free(n);
  }
    
  /*Build the suffix tree and print the edge labels along with
  suffixIndex. suffixIndex for leaf edges will be >= 0 and
  for non-leaf edges will be -1*/
  void buildSuffixTree()
  {
      size = text.length();
      int i;
      rootEnd = (int*) malloc(sizeof(int));
      *rootEnd = - 1;
    
      /*Root is a special node with start and end indices as -1,
      as it has no parent from where an edge comes to root*/
      root = newNode(-1, rootEnd);
    
      activeNode = root; //First activeNode will be root
      for (i=0; i<size; i++)
          extendSuffixTree(i);
      int labelHeight = 0;
      setSuffixIndexByDFS(root, labelHeight);
  }

  int traverseEdge(const string & str, int idx, int start, int end)
  {
      int k = 0;
      //Traverse the edge with character by character matching
      for(k=start; k<=end && idx < str.length(); k++, idx++)
      {
          if(text[k] != str[idx])
              return -1;  // mo match
      }
      if(str.length() == idx)
          return 1;  // match
      return 0;  // more characters yet to match
  }
   
  int doTraversalToCountLeaf(Node *n)
  {
      if(n == NULL)
          return 0;
      if(n->suffixIndex > -1)
      {
          // printf("\nFound at position: %d", n->suffixIndex);
          return 1;
      }
      int count = 0;
      int i = 0;
      for (i = 0; i < MAX_CHAR; i++)
      {
          if(n->children[i] != NULL)
          {
              count += doTraversalToCountLeaf(n->children[i]);
          }
      }
      return count;
  }
   
  int countLeaf(Node *n)
  {
      if(n == NULL)
          return 0;
      return doTraversalToCountLeaf(n);
  }
   
  void doTraversal(Node *n, int labelHeight, int* maxHeight, 
  int* substringStartIndex)
  {
      if(n == NULL)
      {
          return;
      }
      int i=0;
      if(n->suffixIndex == -1) //If it is internal node
      {
          for (i = 0; i < MAX_CHAR; i++)
          {
              if(n->children[i] != NULL)
              {
                  doTraversal(n->children[i], labelHeight +
                                  edgeLength(n->children[i]), maxHeight,
                                   substringStartIndex);
              }
          }
      }
      else if(n->suffixIndex > -1 && 
                  (*maxHeight < labelHeight - edgeLength(n)))
      {
          *maxHeight = labelHeight - edgeLength(n);
          *substringStartIndex = n->suffixIndex;
      }
  }
   
  string getLongestRepeatedSubstring()
  {
      int maxHeight = 0;
      int substringStartIndex = 0;
      doTraversal(root, 0, &maxHeight, &substringStartIndex);
  //  printf("maxHeight %d, substringStartIndex %d\n", maxHeight,
  //           substringStartIndex);
      // printf("Longest Repeated Substring in %s is: ", text.c_str());
      // int k;
      // for (k=0; k<maxHeight; k++)
      //     printf("%c", text[k + substringStartIndex]);
      // if(k == 0)
      //     printf("No repeated substring");
      // printf("\n");
      // cout << maxHeight << endl;
      return text.substr(substringStartIndex, maxHeight);
  }
};

void preKMP(string pattern, int f[])
{
    int m = pattern.length(), k;
    f[0] = -1;
    for (int i = 1; i < m; i++)
    {
        k = f[i - 1];
        while (k >= 0)
        {
            if (pattern[k] == pattern[i - 1])
                break;
            else
                k = f[k];
        }
        f[i] = k + 1;
    }
}
 
//check whether target string contains pattern 
int KMP(string pattern, string target)
{
    int m = pattern.length();
    int n = target.length();
    int f[m];
    preKMP(pattern, f);     
    int i = 0;
    int k = 0;        
    int res = 0;
    while (i < n)
    {
        // printf("i: %d\tk: %d\n", i, k);
        if (k == -1)
        {
            i++;
            k = 0;
        }
        else if (target[i] == pattern[k])
        {
            i++;
            k++;
            if (k == m) {
              res++;
              k--;
              i--;
              k = f[k];
            }
        }
        else
            k = f[k];
    }
    return res;
}

int main()
{
  int tttt;
  cin >> tttt;
  while (tttt--) {
    string s;
    cin >> s;
    s = s + "$";
    SuffixTree st(s);
    string rs = st.getLongestRepeatedSubstring();
    if (rs.length() == 0)
      cout << "No repetitions found!" << endl;
    else {
      cout << rs << ' ';
      cout << KMP(rs, s) << endl;
    }
  }
  return 0;
}
