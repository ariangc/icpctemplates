// Interval tree implemented as a gnu pb_ds extension
// O(logn) per operation
// (Intervals are represented as ((x, y), id)
// Uses tri = pair<ii,int>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/detail/standard_policies.hpp>

using namespace __gnu_pbds;
const int INF = 2e9;

// Node_Itr is of type T**
template<class Node_CItr, class Node_Itr, class Cmp_Fn, 
			class _Alloc> 
struct my_node_update{
	typedef int metadata_type;
	
	// Maintains metadata: Highest endpoint in subtree
	void operator()(Node_Itr it, Node_CItr end_it){
		auto l = it.get_l_child();
		auto r = it.get_r_child();
		int left = -INF, right = -INF;
		if (l!=end_it) left = l.get_metadata();
		if (r!=end_it) right = r.get_metadata();
		const_cast<int&>(it.get_metadata()) = 
			max((*it)->itm2, max(left, right));
	}

	virtual Node_CItr node_begin() const = 0;
	virtual Node_CItr node_end() const = 0;
	
	// Returns the maximum endpoint for nodes (x,y,id) 
	// in subtree it such that x < low
	int max_endpoint(Node_Itr it, int low) {
		if (it == node_end()) return -INF;
		auto l = it.get_l_child();
		auto r = it.get_r_child();
		int ans = -INF;
		if ((*it)->itm1 < low) {
			int left = -INF;
			if (l!=node_end()) ans = max(ans, l.get_metadata());
			ans = max(ans, (*it)->itm2);
			ans = max(ans, max_endpoint(r, low));
			return ans;
		}
		else return max_endpoint(l, low);
	}

	// Returns the interval (y0,y1) CONTAINING x with highest y0.
	// (To prevent edge cases, add interval (-INF, INF) )
	tri max_intersection(tri x){
		auto it = node_begin();
      while(it!=node_end())
      {
      	auto l=it.get_l_child();
      	auto r=it.get_r_child();
			if (max_endpoint(r, x.itm1) > x.itm2) it = r;
			else if ((*it)->itm1 < x.itm1 && x.itm2 < (*it)->itm2) 
				return **it;
			else it = l;
		}
	}

  // Checks whether some interval in the tree OVERLAPS interval x
   bool overlaps(const interval& x)
   {
		auto it = node_begin();
    	while (it != node_end())
   	{
			if (x.itm2 >= (*it).itm1 && x.itm1 <= (*it)->itm2) 
				return true;
			auto l = it.get_l_child();
			int left = -INF;
			if (l!=node_end()) left = l.get_metadata();
			if (left >= x.itm1) it = l;
			else it = it.get_r_child();
      }
		return false;
  }
};

tree<tri, null_type, less<tri>, rb_tree_tag, my_node_update> lines;
